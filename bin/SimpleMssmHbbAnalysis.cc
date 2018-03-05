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
   
   analysis.addTree<Jet> ("Jets","MssmHbb/Events/slimmedJetsPuppi");
   
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
   
   std::map<std::string, TH1F*> h1;
   h1["n"]        = new TH1F("n" , "" , 30, 0, 30);
   h1["n_csv"]    = new TH1F("n_csv" , "" , 30, 0, 30);
   h1["n_ptmin20"]= new TH1F("n_ptmin20" , "" , 30, 0, 30);
   h1["n_ptmin20_csv"] = new TH1F("n_ptmin20_csv" , "" , 30, 0, 30);
   for ( int i = 0 ; i < njetsmin_ ; ++i )
   {
      h1[Form("pt_%i",i)]         = new TH1F(Form("pt_%i",i) , "" , 100, 0, 1000);
      h1[Form("eta_%i",i)]        = new TH1F(Form("eta_%i",i) , "" , 100, -5, 5);
      h1[Form("phi_%i",i)]        = new TH1F(Form("phi_%i",i) , "" , 100, -4, 4);
      h1[Form("btag_%i",i)]       = new TH1F(Form("btag_%i",i) , "" , 500, 0, 1);
      
      h1[Form("pt_%i_csv",i)]     = new TH1F(Form("pt_%i_csv",i) , "" , 100, 0, 1000);
      h1[Form("eta_%i_csv",i)]    = new TH1F(Form("eta_%i_csv",i) , "" , 100, -5, 5);
      h1[Form("phi_%i_csv",i)]    = new TH1F(Form("phi_%i_csv",i) , "" , 100, -4, 4);
      h1[Form("btag_%i_csv",i)]   = new TH1F(Form("btag_%i_csv",i) , "" , 500, 0, 1);
   }
   h1["m12"]     = new TH1F("m12"     , "" , 50, 0, 1000);
   h1["m12_csv"] = new TH1F("m12_csv" , "" , 50, 0, 1000);
   
   
   double mbb;
   double weight;
   TTree *tree = new TTree("MssmHbb_13TeV","");
   tree->Branch("mbb",&mbb,"mbb/D");
   tree->Branch("weight",&weight,"weight/D");
   
   // Analysis of events
   std::cout << "This analysis has " << analysis.size() << " events" << std::endl;
   
   // Cut flow
   // 0: triggered events
   // 1: 3+ idloose jets
   // 2: kinematics
   // 3: matched to online
   // 4: delta R
   // 5: delta eta
   // 6: btag (bbnb)
   int nsel[10] = { };
   int nmatch[10] = { };

   if ( nevtmax_ < 0 ) nevtmax_ = analysis.size();
   for ( int i = 0 ; i < nevtmax_ ; ++i )
   {
      int njets = 0;
      int njets_csv = 0;
      bool goodEvent = true;
      
      if ( i > 0 && i%100000==0 ) std::cout << i << "  events processed! " << std::endl;
      
      analysis.event(i);
      if (! isMC_ )
      {
         if (!analysis.selectJson() ) continue; // To use only goodJSonFiles
      }
      
      int triggerFired = analysis.triggerResult(hltPath_);
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
            const Jet & jet2 = *selectedJets[j2];
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
      for ( int j = 0; j < njetsmin_; ++j )
      {
         Jet * jet = selectedJets[j];
         h1[Form("pt_%i",j)]   -> Fill(jet->pt());
         h1[Form("eta_%i",j)]  -> Fill(jet->eta());
         h1[Form("phi_%i",j)]  -> Fill(jet->phi());
         h1[Form("btag_%i",j)] -> Fill(jet->btag());
         
         if ( j < 2 && jet->btag() < btagmin[j] )     goodEvent = false;
         if ( ! signalregion_ )
         {
            if ( j == 2 && jet->btag() > nonbtagwp_ )    goodEvent = false; 
         }
         else
         {
            if ( j == 2 && jet->btag() < btagmin[j] ) goodEvent = false; 
         }
      }
      
      h1["m12"] -> Fill((selectedJets[0]->p4() + selectedJets[1]->p4()).M());
      
      if ( ! goodEvent ) continue;
      
      ++nsel[5];

//            std::cout << "oioi" << std::endl;
      
      
      // Is matched?
      bool matched[10] = {true,true,true,true,true,true,true,true,true,true};
      for ( int j = 0; j < 2; ++j )
      {
         Jet * jet = selectedJets[j];
//         for ( auto & obj : triggerObjects_ )   matched = (matched && jet->matched(obj));
         for ( size_t io = 0; io < triggerObjects_.size() ; ++io )
         {       
            if ( ! jet->matched(triggerObjects_[io]) ) matched[io] = false;
         }
      }
      
      for ( size_t io = 0; io < triggerObjects_.size() ; ++io )
      {
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
      }
      mbb = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      if ( !signalregion_ )
      { 
         h1["m12_csv"] -> Fill(mbb);
         weight = 1;
         tree -> Fill();
      }
         
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
   // 2: matched to online
   // 3: kinematics
   // 4: delta R
   // 5: delta eta
   // 6: btag (bbnb)
   
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
   for ( int i = 0; i < 7; ++i )
   {
      fracAbs[i] = double(nsel[i])/nsel[0];
      if ( i>0 )
         fracRel[i] = double(nsel[i])/nsel[i-1];
      else
         fracRel[i] = fracAbs[i];
      printf ("%-23s  %10d  %10.3f  %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] ); 
   }
   // CSV output
   printf ("%-23s , %10s , %10s , %10s \n", std::string("Cut flow").c_str(), std::string("# events").c_str(), std::string("absolute").c_str(), std::string("relative").c_str() ); 
   for ( int i = 0; i < 7; ++i )
      printf ("%-23s , %10d , %10.3f , %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] ); 

   // Trigger objects counts   
   std::cout << std::endl;
   printf ("%-40s  %10s \n", std::string("Trigger object").c_str(), std::string("# events").c_str() ); 
//   for ( size_t io = 0; io < triggerObjects_.size() ; ++io )
//   {
//      printf ("%-40s  %10d \n", triggerObjects_[io].c_str(), nmatch[io] ); 
//   }
   
   
   
   
      
   
} //end main

