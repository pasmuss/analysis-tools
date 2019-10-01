#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h" 
#include "TFileCollection.h"
#include "TChain.h"
#include "TH1.h" 
#include "TRandom3.h"
#include "TLorentzVector.h"

#include "Analysis/Tools/interface/Analysis.h"
#include "Analysis/Tools/bin/KinSF_config.h"

using namespace std;
using namespace analysis;
using namespace analysis::tools;

//Function declarations
void correctJetpt ( Jet& , const float& );

// =============================================================================================   
int main(int argc, char * argv[])
{
  if ( KinSF_config(argc, argv) != 0 ) return -1;
   
  TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
  // Input files list
  Analysis analysis(inputlist_);

  analysis.addTree<Jet> ("Jets","MssmHbb/Events/updatedPatJets");
  if (isMC_) analysis.addTree<GenJet>("GenJets","MssmHbb/Events/slimmedGenJets");

  auto jerinfo = analysis.jetResolutionInfo("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/Fall17_V3_MC_PtResolution_AK4PFchs.txt", "/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/Fall17_V3_MC_SF_AK4PFchs.txt");
  
  std::shared_ptr <PileupWeight> puweights = analysis.pileupWeights(pufile_);
   
  for ( auto & obj : triggerObjects_ )
    {
      analysis.addTree<TriggerObject> (obj,Form("MssmHbb/Events/slimmedPatTrigger/%s",obj.c_str()));
    }
  
  analysis.triggerResults("MssmHbb/Events/TriggerResults");
   
  if( !isMC_ )
    {
      int json_status = analysis.processJsonFile(json_);
      if ( json_status < 0 ) 
	{
	  std::cout << "Error from processing json. Please check your json file." << std::endl;
	  return -1;
	}
    }
  
  TFile hout(outputRoot_.c_str(),"recreate");
  ofstream txtoutputfile;
  txtoutputfile.open("output.txt",ios::app);

  std::map<std::string, TH1F*> h1;
  h1["noofevents_h"]      = new TH1F("noofevents_h"     , "" ,   10,  0,    10);
  h1["noofevents_w_nlo"]  = new TH1F("noofevents_w_nlo" , "" ,   10,  0,    10);
  h1["nentries"]          = new TH1F("nentries"         , "" ,    2,  0,     2);

  for ( int i = 0 ; i < njetsmin_ ; ++i )
    {
      h1[Form("pt_%i_PFJet60xOffl_eta0to1",i)] = new TH1F(Form("pt_%i_PFJet60xOffl_eta0to1",i), "", 210, 0, 2100);
      h1[Form("pt_%i_PFJet60xOffl_eta1to1p4",i)] = new TH1F(Form("pt_%i_PFJet60xOffl_eta1to1p4",i), "", 210, 0, 2100);
      h1[Form("pt_%i_PFJet60xOffl_eta1p4to2p2",i)] = new TH1F(Form("pt_%i_PFJet60xOffl_eta1p4to2p2",i), "", 210, 0, 2100);

      h1[Form("pt_%i_emulPFJet100xOffl_eta0to1",i)] = new TH1F(Form("pt_%i_emulPFJet100xOffl_eta0to1",i), "", 210, 0, 2100);
      h1[Form("pt_%i_emulPFJet100xOffl_eta1to1p4",i)] = new TH1F(Form("pt_%i_emulPFJet100xOffl_eta1to1p4",i), "", 210, 0, 2100);
      h1[Form("pt_%i_emulPFJet100xOffl_eta1p4to2p2",i)] = new TH1F(Form("pt_%i_emulPFJet100xOffl_eta1p4to2p2",i), "", 210, 0, 2100);

      h1[Form("pt_%i_eff_eta0to1",i)] = new TH1F(Form("pt_%i_eff_eta0to1",i), "", 210, 0, 2100);
      h1[Form("pt_%i_eff_eta1to1p4",i)] = new TH1F(Form("pt_%i_eff_eta1to1p4",i), "", 210, 0, 2100);
      h1[Form("pt_%i_eff_eta1p4to2p2",i)] = new TH1F(Form("pt_%i_eff_eta1p4to2p2",i), "", 210, 0, 2100);
    }
   
  // Analysis of events
  cout << "This analysis has " << analysis.size() << " events" << endl;
  cout << nevtmax_ << " events have been selected." << endl;
  cout << "Selected number of jets: " << njetsmin_ << endl;
  cout << "output file: " << outputRoot_.c_str() << endl;
  cout << "ntuples file: " << inputlist_.c_str() << endl;
  cout << "PU file: " << pufile_.c_str() << endl;
  txtoutputfile << "This analysis has " << analysis.size() << " events" << endl;
  txtoutputfile << nevtmax_ << " events have been selected." << endl;
  txtoutputfile << "Selected number of jets: " << njetsmin_ << endl;
  txtoutputfile << "output file: " << outputRoot_.c_str() << endl;
  txtoutputfile << "ntuples file: " << inputlist_.c_str() << endl;
  txtoutputfile << "PU file: " << pufile_.c_str() << endl;
  
  int nsel[10] = { };
  int nweigh[10] = { };

  int noofeventsstart = 0;

  if ( nevtmax_ < 0 ) nevtmax_ = analysis.size();
  
  for ( int i = 0 ; i < nevtmax_ ; ++i )
    {
      noofeventsstart ++;
      float eventweight = 1.0;

      if (isMC_){
	float puweight = puweights->weight(analysis.nTruePileup(),0);//0: central; replace by +-1/2 for +- 1/2 sigma variation (up/down); should use specific values (puup, pudown) for that purpose!
	eventweight *= puweight;
      }

      if ( i > 0 && i%100000==0 ){
	std::cout << i << " events processed!" << std::endl;
	txtoutputfile << i << " events processed!" << endl;
      }
     
      analysis.event(i);
      if (! isMC_ )
	{
	  if (!analysis.selectJson() ) continue; // To use only goodJSonFiles
	}

      // Jets - std::shared_ptr< Collection<Jet> >
      auto slimmedJets = analysis.collection<Jet>("Jets");
      float sgweight = 0;
      if (isMC_){
	auto genjets = analysis.collection<GenJet>("GenJets");
	slimmedJets->addGenJets(genjets);
	sgweight = analysis.genWeight()/fabs(analysis.genWeight()); //just include sign of MC weight
	eventweight *= sgweight;
	h1["nentries"] -> Fill((sgweight+1.)/2.);
      }

      if (isMC_ && sgweight == 0){
	cout << "Neither positive nor negative weight detected for MC. This can not be right." << endl;
	return -1;
      }

      ++nsel[1];
      if(isMC_ && sgweight > 0) ++nweigh[1];
      else if(isMC_ && sgweight < 0) --nweigh[1];
      
      int triggerFired = analysis.triggerResult(hltPath_);
      if ( !triggerFired ) continue;//all events need to fire the HLT

      ++nsel[2];
      if(isMC_ && sgweight > 0) ++nweigh[2];
      else if(isMC_ && sgweight < 0) --nweigh[2];

      std::vector<Jet*> selectedJets;

      for ( int j = 0 ; j < slimmedJets->size() ; ++j )
	{
	  if (slimmedJets->at(j).pileupJetIdFullId("loose") && slimmedJets->at(j).idTight() ) selectedJets.push_back(&slimmedJets->at(j));
	}

      //at least n jets present
      if ( (int)selectedJets.size() < njetsmin_ ) continue; //just a cross check, should never be less than required by the trigger; but if there are no jets, everything will be weird and useless

      ++nsel[3];
      if(isMC_ && sgweight > 0) ++nweigh[3];
      else if(isMC_ && sgweight < 0) --nweigh[3];      

      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet* jet = selectedJets[j];
	  //Perform JER (jet energy resolution) matching and calculate corrections ("up"/"down" are +- 1 sigma uncertainties)
	  if (isMC_ && useJER_){
	    jet->jerInfo(*jerinfo,0.2);
	    float correctResolution = jet->jerCorrection();
	    correctJetpt(*jet,correctResolution);
	  }
	}

      /// Matching to respective trigger objects (those with 100 to emulate the less inclusive trigger; all using same HLT)
      std::vector<Jet*> Jets_l1_60, Jets_calo_60, Jets_pf_60, Jets_full_60, Jets_full_60_offl, Jets_l1_100, Jets_calo_100, Jets_pf_100, Jets_full_100, Jets_full_100_offl;

      analysis.match<Jet,TriggerObject>("Jets",triggerObjects_,0.5);
      bool l1_60 = false, calo_60 = false, pf_60 = false, l1_100 = false, calo_100 = false, pf_100 = false, offline = false;
      bool full_60 = true, full_100 = true, num_100xoffl = true, den_60xoffl = true;

      for ( int j = 0; j < njetsmin_; ++j )
        {
          Jet * jet = selectedJets[j];
	  double jeteta = jet->eta();
	  if ( jet->matched(triggerObjects_[1]) ){
	    l1_60 = true;
	    full_60 = (full_60 && l1_60);
	    den_60xoffl = (den_60xoffl && l1_60);
	    Jets_l1_60.push_back(jet);
	  }
	  if ( jet->matched(triggerObjects_[2]) ){
	    calo_60 = true;
	    full_60 = (full_60 && calo_60);
	    den_60xoffl = (den_60xoffl && calo_60);
	    Jets_calo_60.push_back(jet);
	  }
	  if ( jet->matched(triggerObjects_[3]) ){
	    pf_60 = true;
	    full_60 = (full_60 && pf_60);
	    den_60xoffl = (den_60xoffl && pf_60);
	    Jets_pf_60.push_back(jet);
	  }
	  if ( jet->matched(triggerObjects_[4]) ){
	    l1_100 = true;
	    full_100 = (full_100 && l1_100);
	    num_100xoffl = (num_100xoffl && l1_100);
	    Jets_l1_100.push_back(jet);
	  }
	  if ( jet->matched(triggerObjects_[5]) ){
	    calo_100 = true;
	    full_100 = (full_100 && calo_100);
	    num_100xoffl = (num_100xoffl && calo_100);
	    Jets_calo_100.push_back(jet);
	  }
	  if ( jet->matched(triggerObjects_[6]) ){
	    pf_100 = true;
	    full_100 = (full_100 && pf_100);
	    num_100xoffl = (num_100xoffl && pf_100);
	    Jets_pf_100.push_back(jet);
	  }
	  if (full_60) Jets_full_60.push_back(jet);
	  if (full_100) Jets_full_100.push_back(jet);
	  if ( (jet->pt() <= jetsptmin_[j] || fabs(jet->eta()) >= jetsetamax_[j]) ){
	    offline = true;
	    den_60xoffl = (den_60xoffl && offline);
	    num_100xoffl = (num_100xoffl && offline);
	  }
	  //fill numerator (100 && offl; 60 implicitly included via HLT) and denominator (60 && offl) histograms
	  if (den_60xoffl){
	    Jets_full_60_offl.push_back(jet);
	    if (fabs(jeteta) < 1){
	      h1[Form("pt_%i_PFJet60xOffl_eta0to1",i)] -> Fill(jet->pt());
	    }
	    else if (fabs(jeteta) > 1 && fabs(jeteta) < 1.4){
	      h1[Form("pt_%i_PFJet60xOffl_eta1to1p4",i)] -> Fill(jet->pt());
	    }
	    else if (fabs(jeteta) > 1.4 && fabs(jeteta) < 2.2){
	      h1[Form("pt_%i_PFJet60xOffl_eta1p4to2p2",i)] -> Fill(jet->pt());
	    }
	    else{
	      cout << "Absolute value of eta (PFJet60) not in range. Please check." << endl;
	      return -1;
	    }
	  }
	  if (num_100xoffl){
	    Jets_full_100_offl.push_back(jet);
	    if (fabs(jeteta) < 1){
	      h1[Form("pt_%i_PFJet100xOffl_eta0to1",i)] -> Fill(jet->pt());
	    }
	    else if (fabs(jeteta) > 1 && fabs(jeteta) < 1.4){
	      h1[Form("pt_%i_PFJet100xOffl_eta1to1p4",i)] -> Fill(jet->pt());
	    }
	    else if (fabs(jeteta) > 1.4 && fabs(jeteta) < 2.2){
	      h1[Form("pt_%i_PFJet100xOffl_eta1p4to2p2",i)] -> Fill(jet->pt());
	    }
	    else{
	      cout << "Absolute value of eta (PFJet100) not in range. Please check." << endl;
	      return -1;
	    }
	  }
	  h1[Form("pt_%i_eff_eta0to1",i)] -> Divide(h1[Form("pt_%i_PFJet100xOffl_eta0to1",i)], h1[Form("pt_%i_PFJet60xOffl_eta0to1",i)]);
	  h1[Form("pt_%i_eff_eta1to1p4",i)]-> Divide(h1[Form("pt_%i_PFJet100xOffl_eta1to1p4",i)], h1[Form("pt_%i_PFJet60xOffl_eta1to1p4",i)]);
	  h1[Form("pt_%i_eff_eta1p4to2p2",i)]-> Divide(h1[Form("pt_%i_PFJet100xOffl_eta1p4to2p2",i)], h1[Form("pt_%i_PFJet60xOffl_eta1p4to2p2",i)]);
	}
    }//end: event loop
  
  h1["noofevents_h"] -> SetBinContent(1,noofeventsstart); //total number of events
  h1["noofevents_h"] -> SetBinContent(2,nsel[0]);
  h1["noofevents_h"] -> SetBinContent(3,nsel[1]);
  h1["noofevents_h"] -> SetBinContent(4,nsel[2]);
  h1["noofevents_h"] -> SetBinContent(5,nsel[3]);

  if(isMC_){//weighted number of events (important only for NLO) after each step of the cutflow
    h1["noofevents_w_nlo"] -> SetBinContent(1,noofeventsstart); //total number of events
    h1["noofevents_w_nlo"] -> SetBinContent(2,nweigh[0]);
    h1["noofevents_w_nlo"] -> SetBinContent(3,nweigh[1]);
    h1["noofevents_w_nlo"] -> SetBinContent(4,nweigh[2]);
    h1["noofevents_w_nlo"] -> SetBinContent(5,nweigh[3]);
  }

  for (auto & ih1 : h1)
    {
      ih1.second -> Write();
    }
  hout.Write();
  hout.Close();
  
} //end main

void correctJetpt ( Jet& jet , const float& cor )
{
  TLorentzVector CorJet;
  CorJet.SetPtEtaPhiM(jet.pt()*cor , jet.eta(), jet.phi(), (jet.p4()).M());
  jet.p4(CorJet);
}
