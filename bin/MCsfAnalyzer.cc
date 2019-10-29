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

  for ( int i = 0 ; i < njetsmin_ ; ++i )
    {
      h1[Form("pt_%i_PFJet60xOffl_eta0to1",i)] = new TH1F(Form("pt_%i_PFJet60xOffl_eta0to1",i), "", 210, 0, 2100);
      h1[Form("pt_%i_PFJet60xOffl_eta1to1p4",i)] = new TH1F(Form("pt_%i_PFJet60xOffl_eta1to1p4",i), "", 210, 0, 2100);
      h1[Form("pt_%i_PFJet60xOffl_eta1p4to2p2",i)] = new TH1F(Form("pt_%i_PFJet60xOffl_eta1p4to2p2",i), "", 210, 0, 2100);

      h1[Form("pt_%i_PFJet100xOffl_eta0to1",i)] = new TH1F(Form("pt_%i_PFJet100xOffl_eta0to1",i), "", 210, 0, 2100);
      h1[Form("pt_%i_PFJet100xOffl_eta1to1p4",i)] = new TH1F(Form("pt_%i_PFJet100xOffl_eta1to1p4",i), "", 210, 0, 2100);
      h1[Form("pt_%i_PFJet100xOffl_eta1p4to2p2",i)] = new TH1F(Form("pt_%i_PFJet100xOffl_eta1p4to2p2",i), "", 210, 0, 2100);
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
  
  if ( nevtmax_ < 0 ) nevtmax_ = analysis.size();
  
  for ( int i = 0 ; i < nevtmax_ ; ++i )
    {
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

      //Trigger Objects
      std::vector<TriggerObject*> usedobjects_L1, usedobjects_Calo, usedobjects_PF;
      auto L1Obj = analysis.collection<TriggerObject>(triggerObjects_[0].c_str());
      auto CaloObj = analysis.collection<TriggerObject>(triggerObjects_[1].c_str());
      auto PFObj = analysis.collection<TriggerObject>(triggerObjects_[2].c_str());

      for (int a = 0; a < L1Obj -> size(); ++a){
	usedobjects_L1.push_back(&L1Obj->at(a));
      }
      for (int b = 0; b < CaloObj -> size(); ++b){
	usedobjects_Calo.push_back(&CaloObj->at(b));
      }
      for (int c = 0; c < PFObj -> size(); ++c){
	usedobjects_PF.push_back(&PFObj->at(c));
      }
      

      if (isMC_ && sgweight == 0){
	cout << "Neither positive nor negative weight detected for MC. This can not be right." << endl;
	return -1;
      }
      
      int triggerFired = analysis.triggerResult(hltPath_);
      if ( !triggerFired ) continue;//all events need to fire the HLT

      std::vector<Jet*> selectedJets;

      for ( int j = 0 ; j < slimmedJets->size() ; ++j )
	{
	  if (slimmedJets->at(j).pileupJetIdFullId("loose") && slimmedJets->at(j).idTight() ) selectedJets.push_back(&slimmedJets->at(j));
	}

      //at least n jets present
      if ( (int)selectedJets.size() < njetsmin_ ) continue; //just a cross check, should never be less than required by the trigger; but if there are no jets, everything will be weird and useless

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
      
      bool matched[6] = {true,true,true,true,true,true};//three objects times two jets: all need to be matched
      bool goodEvent = true;
      for (int i = 0; i < njetsmin_; i++){
	Jet* jet = selectedJets[i];
	for ( size_t io = 0; io < triggerObjects_.size(); ++io ){
	  if ( ! jet->matched(triggerObjects_[io]) ) matched[io] = false;
	  goodEvent = (goodEvent && matched[io]);
	}
	if ( !(jet->pt() >= jetsptmin_[i] && fabs(jet->eta()) <= jetsetamax_[i]) ) goodEvent = false;
      }
      if (!goodEvent) continue;
      //NOW: Jet60 and offline are checked. Histograms may be filled for the denominator.
      //IF INDIVIDUAL TRIGGER LEVELS WANTED: Go for entries 0, 1, and 2 of triggerObjects_, respectively and step by step, filling histograms/vectors for these steps

      for (int j = 0; j < njetsmin_; j++){
	Jet* jet = selectedJets[j];
	double jeteta = jet->eta();
	Jets_full_60_offl.push_back(jet);
	if (fabs(jeteta) < 1){
	  h1[Form("pt_%i_PFJet60xOffl_eta0to1",j)] -> Fill(jet->pt());
	}
	else if (fabs(jeteta) > 1 && fabs(jeteta) < 1.4){
	  h1[Form("pt_%i_PFJet60xOffl_eta1to1p4",j)] -> Fill(jet->pt());
	}
	else if (fabs(jeteta) > 1.4 && fabs(jeteta) < 2.2){
	  h1[Form("pt_%i_PFJet60xOffl_eta1p4to2p2",j)] -> Fill(jet->pt());
	}
      }
      
      //AFTER: Emulate 100 on trigger objects for numerator. Offline is already checked above.
      
      double L1pt = usedobjects_L1[0] -> pt();
      double L1eta = usedobjects_L1[0] -> eta();
      double Calopt = usedobjects_Calo[0] -> pt();
      double Caloeta = usedobjects_Calo[0] -> eta();
      double PFpt = usedobjects_PF[0] -> pt();
      double PFeta = usedobjects_PF[0] -> eta();

      if ( L1pt < 100 || fabs(L1eta) > 2.3 ) goodEvent = false;
      if ( Calopt < 100 || fabs(Caloeta) > 2.3 ) goodEvent = false;
      if ( PFpt < 100 || fabs(PFeta) > 2.3 ) goodEvent = false;
      if (!goodEvent) continue;

      for (int j = 0; j < njetsmin_; j++){
	Jet* jet = selectedJets[j];
	double jeteta = jet->eta();
	Jets_full_100_offl.push_back(jet);
	if (fabs(jeteta) < 1){
	  h1[Form("pt_%i_PFJet100xOffl_eta0to1",j)] -> Fill(jet->pt());
	}
	else if (fabs(jeteta) > 1 && fabs(jeteta) < 1.4){
	  h1[Form("pt_%i_PFJet100xOffl_eta1to1p4",j)] -> Fill(jet->pt());
	}
	else if (fabs(jeteta) > 1.4 && fabs(jeteta) < 2.2){
	  h1[Form("pt_%i_PFJet100xOffl_eta1p4to2p2",j)] -> Fill(jet->pt());
	}
      }
    }//end: event loop
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
