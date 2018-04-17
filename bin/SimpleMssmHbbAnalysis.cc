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

#include "Analysis/Tools/interface/Analysis.h"
#include "Analysis/Tools/bin/macro_config.h"

using namespace std;
using namespace analysis;
using namespace analysis::tools;

// =============================================================================================   
int main(int argc, char * argv[])
{
  if ( macro_config(argc, argv) != 0 ) return -1;
   
  TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
  // Cuts
  float btagmin[3] = { btagwp_, btagwp_, btagwp_};
   
  // Input files list
  Analysis analysis(inputlist_);

  string btagalgo = btagalgo_;
  string reco = reco_;
   
  if (reco == "prompt"){
    analysis.addTree<Jet> ("Jets","MssmHbb/Events/slimmedJetsPuppi");
    analysis.addTree<Muon>("Muons","MssmHbb/Events/slimmedMuons");
  }
  else if (reco == "rereco"){
    analysis.addTree<Jet> ("Jets","MssmHbb/Events/updatedPatJetsPuppi");
    analysis.addTree<Muon>("Muons","MssmHbb/Events/slimmedMuons");
  }
  else{
    cout << "Neither prompt nor rereco data selected. Aborting." << endl;
    return -1;
  }
   
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
   
  std::string sr_s = "SR";
  if ( ! signalregion_ ) sr_s = "CR";
  boost::algorithm::replace_last(outputRoot_, ".root", "_"+sr_s+".root"); 
   
  TFile hout(outputRoot_.c_str(),"recreate");
  ofstream txtoutputfile;
  txtoutputfile.open("output.txt",ios::app);
   
  std::map<std::string, TH1F*> h1;
  h1["n"]        = new TH1F("n" , "" , 30, 0, 30);
  h1["n_csv"]    = new TH1F("n_csv" , "" , 30, 0, 30);
  h1["n_ptmin20"]= new TH1F("n_ptmin20" , "" , 30, 0, 30);
  h1["n_ptmin20_csv"] = new TH1F("n_ptmin20_csv" , "" , 30, 0, 30);

  h1["jetswomu"] = new TH1F("jetswomu" , "" , 30, 0, 30);
  
  h1["n_muons"] = new TH1F("n_muons" , "" , 30, 0, 30);
  h1["pt_mu"] = new TH1F("pt_mu" , "" , 100, 0, 1000);
  h1["eta_mu"] = new TH1F("eta_mu" , "" , 100, -5, 5);
  
  h1["dR_muj"] = new TH1F("dR_muj", "" , 100, 0, 0.5);
  h1["dR_muj0"] = new TH1F("dR_muj0", "" , 100, 0, 0.5);
  h1["dR_muj1"] = new TH1F("dR_muj1", "" , 100, 0, 0.5);
   
  for ( int i = 0 ; i < njetsmin_ ; ++i )
    {
      h1[Form("pt_%i",i)]         = new TH1F(Form("pt_%i",i) , "" , 100, 0, 1000);
      h1[Form("eta_%i",i)]        = new TH1F(Form("eta_%i",i) , "" , 100, -5, 5);
      h1[Form("phi_%i",i)]        = new TH1F(Form("phi_%i",i) , "" , 100, -4, 4);
      h1[Form("btag_%i",i)]       = new TH1F(Form("btag_%i",i) , "" , 500, 0, 1);
      h1[Form("deepcsvbtag_%i",i)]       = new TH1F(Form("deepcsvbtag_%i",i) , "" , 500, 0, 1);
      
      h1[Form("pt_%i_csv",i)]     = new TH1F(Form("pt_%i_csv",i) , "" , 100, 0, 1000);
      h1[Form("eta_%i_csv",i)]    = new TH1F(Form("eta_%i_csv",i) , "" , 100, -5, 5);
      h1[Form("phi_%i_csv",i)]    = new TH1F(Form("phi_%i_csv",i) , "" , 100, -4, 4);
      h1[Form("btag_%i_csv",i)]   = new TH1F(Form("btag_%i_csv",i) , "" , 500, 0, 1);
      h1[Form("deepcsvbtag_%i_csv",i)]   = new TH1F(Form("deepcsvbtag_%i_csv",i) , "" , 500, 0, 1);
    }
  h1["m12"]     = new TH1F("m12"     , "" , 50, 0, 1000);
  h1["m12_csv"] = new TH1F("m12_csv" , "" , 50, 0, 1000);
   
   
  double mbb;
  double weight;
  TTree *tree = new TTree("MssmHbb_13TeV","");
  tree->Branch("mbb",&mbb,"mbb/D");
  tree->Branch("weight",&weight,"weight/D");
   
  // Analysis of events
  cout << "This analysis has " << analysis.size() << " events" << endl;
  cout << nevtmax_ << " events have been selected." << endl;
  cout << "btag algorithm: " << btagalgo << endl;
  cout << "region: " << sr_s << endl;
  cout << "reco: " << reco << endl;
  cout << "output file: " << outputRoot_.c_str() <<endl;
  txtoutputfile << "This analysis has " << analysis.size() << " events" << endl;
  txtoutputfile << nevtmax_ << " events have been selected." << endl;
  txtoutputfile << "btag algorithm: " << btagalgo << endl;
  txtoutputfile << "region: " << sr_s << endl;
  txtoutputfile << "reco: " << reco << endl;
  txtoutputfile << "output file: " << outputRoot_.c_str() << endl;
  
  // Cut flow
  // 0: triggered events
  // 1: 3+ idloose jets
  // 2: kinematics
  // 3: delta R
  // 4: delta eta (up to this point: purely kinematics)
  // 3 and 4 are only applied to the leading two jets
  // 5: btag (bbnb)
  // 6: matching
  int nsel[10] = { };
  int nmatch[10] = { };

  if ( nevtmax_ < 0 ) nevtmax_ = analysis.size();
  for ( int i = 0 ; i < nevtmax_ ; ++i )
    {
      int njets = 0;
      int njets_csv = 0;
      int nmuons = 0;
      int nomujet = 0;
      bool goodEvent = true;
      bool muonpresent = false;

      if ( i > 0 && i%1000000==0 ){
	std::cout << i << " events processed!" << std::endl;
	txtoutputfile << i << " events processed!" << endl;
	  }
      int run = analysis.run();
      int run_crit = 304508;

      /*if (analysis.run() > 304508){
        triggerObjects_[0] = triggerObjects_[5];
	}*/
  
      //cout << "run number of event " << i << ": " << analysis.run() << endl; 
      /*for (unsigned int i = 0; i < triggerObjects_.size(); i++){
	cout << triggerObjects_[i] << endl;
	}*/
     
      analysis.event(i);
      if (! isMC_ )
	{
	  if (!analysis.selectJson() ) continue; // To use only goodJSonFiles
	}
      
      int triggerFired = analysis.triggerResult(hltPath_);
      //int triggerFiredL1; //here should be a reference to the L1 path (i.e. 100, 100or112) // check with JSON: should give same result with proper JSON file (with removed lumi sections in which L1_100 is prescaled to 0) and with this L1 check
      //if ( !(triggerFired && triggerFiredL1) ) continue;
      if ( !triggerFired ) continue;
      
      ++nsel[0];
      
      // match offline to online
      analysis.match<Jet,TriggerObject>("Jets",triggerObjects_,0.5);
      
      // Jets - std::shared_ptr< Collection<Jet> >
      auto slimmedJets = analysis.collection<Jet>("Jets");
      std::vector<Jet *> selectedJets;
      for ( int j = 0 ; j < slimmedJets->size() ; ++j )
	{
	  if ( slimmedJets->at(j).idLoose() ) selectedJets.push_back(&slimmedJets->at(j));
	}
      if ( (int)selectedJets.size() < njetsmin_ ) continue;
      
      ++nsel[1];
      
      // Kinematic selection - 3 leading jets
      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet * jet = selectedJets[j];
	  if ( jet->pt() < jetsptmin_[j] || fabs(jet->eta()) > jetsetamax_[j] )
	    {
	      goodEvent = false;
	      break;
	    }
	}
      
      if ( ! goodEvent ) continue;
      
      ++nsel[2];
      
      for ( int j1 = 0; j1 < njetsmin_-1; ++j1 )
	{
	  const Jet & jet1 = *selectedJets[j1];
	  for ( int j2 = j1+1; j2 < njetsmin_; ++j2 )
	    {
	      const Jet & jet2 = *selectedJets[j2];//if the two leading jets are too close together: no good event
	      if ( jet1.deltaR(jet2) < drmin_ ) goodEvent = false;
	    }
	}
      
      if ( ! goodEvent ) continue;
      
      ++nsel[3];
      
      if ( fabs(selectedJets[0]->eta() - selectedJets[1]->eta()) > detamax_ ) continue;
      
      ++nsel[4];
      
      
      // Fill histograms of kinematic passed events
      for ( int j = 0 ; j < (int)selectedJets.size() ; ++j )
	{
	  if ( selectedJets[j]->pt() < 20. ) continue;
	  ++njets;
	}
      
      h1["n"] -> Fill(selectedJets.size());
      h1["n_ptmin20"] -> Fill(njets);

      //b tagging
      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet * jet = selectedJets[j];
	  h1[Form("pt_%i",j)]   -> Fill(jet->pt());
	  h1[Form("eta_%i",j)]  -> Fill(jet->eta());
	  h1[Form("phi_%i",j)]  -> Fill(jet->phi());
	  h1[Form("btag_%i",j)] -> Fill(jet->btag());
	  h1[Form("deepcsvbtag_%i",j)] -> Fill(jet->btag("btag_deepb")+jet->btag("btag_deepbb"));
	 
	  float btagdisc;

	  if (btagalgo == "csv") btagdisc = jet->btag();
	  else if (btagalgo == "deep_csv") btagdisc = jet->btag("btag_deepb") + jet->btag("btag_deepbb");
	  else return -1;
         
	  if ( j < 2 && btagdisc < btagmin[j] )     goodEvent = false;
	  if ( ! signalregion_ )
	    {
	      if ( j == 2 && btagdisc > nonbtagwp_ )    goodEvent = false; 
	    }
	  else
	    {
	      if ( j == 2 && btagdisc < btagmin[j] ) goodEvent = false; 
	    }
	}
      
      h1["m12"] -> Fill((selectedJets[0]->p4() + selectedJets[1]->p4()).M());
      
      if ( ! goodEvent ) continue;
      
      ++nsel[5];
      
      
      // Is matched?
      bool matched[12] = {true,true,true,true,true,true,true,true,true,true,true,true};//for both leading jets: five objects to be tested
      
      //if (run > run_crit) triggerObjects_.;
      //else if (run <= run_crit) triggerObjects_.;
      //else cout << "What the fuck is happening here?" << endl;
      
      for ( int j = 0; j < 2; ++j )
	{
	  Jet * jet = selectedJets[j];
	  for ( size_t io = 0; io < triggerObjects_.size(); ++io )
	    {
	      if (run > run_crit && io == 0) continue;
	      else if (run <= run_crit && io == 1) continue;
	      if ( ! jet->matched(triggerObjects_[io]) ) matched[io] = false;
	    }
	}
      
      for ( size_t io = 0; io < triggerObjects_.size(); ++io )
	{
	  if (run > run_crit && io == 0) continue;
	  else if (run <= run_crit && io == 1) continue;
	  if ( matched[io] ) ++nmatch[io];
	  goodEvent = ( goodEvent && matched[io] );
	}
      
      if ( ! goodEvent ) continue;
      
      ++nsel[6];
     
      // Fill histograms of passed bbnb btagging selection
      for ( int j = 0 ; j < (int)selectedJets.size() ; ++j )
	{
	  if ( selectedJets[j]->pt() < 20. ) continue;
	  ++njets_csv;
	}
      h1["n_csv"] -> Fill(selectedJets.size());
      h1["n_ptmin20_csv"] -> Fill(njets_csv);
      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet * jet = selectedJets[j];
	  h1[Form("pt_%i_csv",j)]   -> Fill(jet->pt());
	  h1[Form("eta_%i_csv",j)]  -> Fill(jet->eta());
	  h1[Form("phi_%i_csv",j)]  -> Fill(jet->phi());
	  h1[Form("btag_%i_csv",j)] -> Fill(jet->btag());
	  h1[Form("deepcsvbtag_%i_csv",j)] -> Fill(jet->btag("btag_deepb")+jet->btag("btag_deepbb"));
	}
      mbb = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      if ( !signalregion_ )//blinding
	{ 
	  h1["m12_csv"] -> Fill(mbb);
	  weight = 1;
	  tree -> Fill();
	}


      // Check for muons in the jets
      
      std::vector<Muon *> selectedMuons;
      auto slimmedMuons = analysis.collection<Muon>("Muons");
      for ( int m = 0 ; m < slimmedMuons->size() ; ++m )
	{
	  if ( slimmedMuons->at(m).isMediumMuon() ){
	    selectedMuons.push_back(&slimmedMuons->at(m));
	    ++nmuons;
	  }
	}
      if ( (int)selectedMuons.size() < 1 ) continue;
      h1["n_muons"] -> Fill(selectedMuons.size());
      
      std::vector<Muon *> MuonsinJet;
      for ( size_t m = 0; m < selectedMuons.size(); ++m )      
	{
	  Muon* muon = selectedMuons[m];
	  //if ( muon->pt() < muonsptmin_[m] || fabs(muon->eta()) > muonsetamax_[m] ) continue;
	  float dR_muj0 = selectedJets[0]->deltaR(*muon) ;
	  float dR_muj1 = selectedJets[1]->deltaR(*muon) ;
	  
	  if ( dR_muj0 < drmax_  || dR_muj1 < drmax_) //at least 1 muon in a jet originating from the Higgs
            {
	      muonpresent  = true;
	      h1["pt_mu"]  -> Fill( muon->pt());
              h1["eta_mu"] -> Fill( muon->eta());
	      h1["dR_muj"] -> Fill( (dR_muj0 < dR_muj1) ? dR_muj0 : dR_muj1 );//only the two leading jets
	      if       (dR_muj0 < drmax_)  h1["dR_muj0"] -> Fill( dR_muj0 );
	      else if  (dR_muj1 < drmax_)  h1["dR_muj1"] -> Fill( dR_muj1 );

	      MuonsinJet.push_back(muon);
	      break;
	    }
	  if (!muonpresent) ++nomujet;
	}//end: loop over muons
    }
   
  for (auto & ih1 : h1)
    {
      ih1.second -> Write();
    }
   
  hout.Write();
  hout.Close();
   
  // PRINT OUTS


  // Cut flow
  // 0: triggered events
  // 1: 3+ idloose jets
  // 2: kinematics
  // 3: delta R
  // 4: delta eta (up to this point: purely kinematics)
  // 5: btag (bbnb)
  // 6: matching
   
  double fracAbs[10];
  double fracRel[10];
  std::string cuts[10];
  cuts[0] = "Triggered";
  cuts[1] = "Triple idloose-jet";
  cuts[2] = "Triple jet kinematics";
  cuts[3] = "Delta R(i;j)";
  cuts[4] = "Delta eta(j1;j2)";
  cuts[5] = "btagged (bbnb)";
  if ( signalregion_ ) cuts[5] = "btagged (bbb)";
  cuts[6] = "Matched to online j1;j2";
   
  printf ("%-23s  %10s  %10s  %10s \n", std::string("Cut flow").c_str(), std::string("# events").c_str(), std::string("absolute").c_str(), std::string("relative").c_str() ); 
  txtoutputfile << "Cut flow " << "# events " << "absolute " << "relative" << endl;;
  for ( int i = 0; i < 7; ++i )
    {
      fracAbs[i] = double(nsel[i])/nsel[0];
      if ( i>0 )
	fracRel[i] = double(nsel[i])/nsel[i-1];
      else
	fracRel[i] = fracAbs[i];
      printf ("%-23s  %10d  %10.3f  %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] ); 
      txtoutputfile << cuts[i].c_str() << " " << nsel[i] << " " << fracAbs[i] << " " << fracRel[i] << endl;
    }
  // CSV output
  printf ("%-23s , %10s , %10s , %10s \n", std::string("Cut flow").c_str(), std::string("# events").c_str(), std::string("absolute").c_str(), std::string("relative").c_str() ); 
  for ( int i = 0; i < 7; ++i )
    printf ("%-23s , %10d , %10.3f , %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] );

  // Trigger objects counts   
  //std::cout << std::endl;
  //printf ("%-40s  %10s \n", std::string("Trigger object").c_str(), std::string("# events").c_str() ); 
  //   for ( size_t io = 0; io < triggerObjects_.size() ; ++io )
  //   {
  //      printf ("%-40s  %10d \n", triggerObjects_[io].c_str(), nmatch[io] ); 
  //   }   
} //end main

