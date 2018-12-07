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
#include "TLorentzVector.h"

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
   
  // Input files list
  Analysis analysis(inputlist_);

  string btagalgo = btagalgo_;
  string reco = reco_;

  string regions = regions_;

  if (reco == "prompt"){
    analysis.addTree<Jet> ("Jets","MssmHbb/Events/slimmedJetsPuppi");
    analysis.addTree<Muon>("Muons","MssmHbb/Events/slimmedMuons");
  }
  else if (reco == "rereco"){//this is the default and also applicable for MC!
    analysis.addTree<Jet> ("Jets","MssmHbb/Events/updatedPatJets");
    analysis.addTree<Muon>("Muons","MssmHbb/Events/slimmedMuons");
    if (isMC_) analysis.addTree<GenJet>("GenJets","MssmHbb/Events/slimmedGenJets");
  }
  else{
    cout << "Neither prompt nor rereco data selected. Aborting." << endl;
    return -1;
  }

  auto jerinfo = analysis.jetResolutionInfo("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt", "/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/Summer16_25nsV1_MC_SF_AK4PFchs.txt");
  auto bsf_reader = analysis.btagCalibration("deepcsv", "/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/DeepCSV_94XSF_V3_B_F.csv", "medium");
     
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
  h1["noofevents_h"]      = new TH1F("noofevents_h"    , "" , 10, 0, 10);
  h1["n"]                 = new TH1F("n"               , "" , 30, 0, 30);
  h1["n_csv"]             = new TH1F("n_csv"           , "" , 30, 0, 30);
  h1["n_ptmin20"]         = new TH1F("n_ptmin20"       , "" , 30, 0, 30);
  h1["n_ptmin20_csv"]     = new TH1F("n_ptmin20_csv"   , "" , 30, 0, 30);

  h1["jetswomu"] = new TH1F("jetswomu" , "" , 30, 0, 30);
  
  h1["n_muons"] = new TH1F("n_muons" , "" , 30, 0, 30);
  h1["pt_mu"]   = new TH1F("pt_mu"   , "" , 150, 0, 1500);
  h1["eta_mu"]  = new TH1F("eta_mu"  , "" , 120, -6, 6);

  h1["pt_corrected_comp"] = new TH1F("pt_corrected_comp", "" , 210, 0, 2100);
  
  h1["dR_muj"]  = new TH1F("dR_muj" , "" , 120, 0, 0.6);
  h1["dR_muj0"] = new TH1F("dR_muj0", "" , 120, 0, 0.6);
  h1["dR_muj1"] = new TH1F("dR_muj1", "" , 120, 0, 0.6);

  h1["cutflow"]              = new TH1F("cutflow"  , "", 10, 0, 10);
   
  for ( int i = 0 ; i < njetsmin_ ; ++i )
    {
      h1[Form("pt_%i",i)]          = new TH1F(Form("pt_%i",i)          , "" , 210, 0, 2100);
      h1[Form("eta_%i",i)]         = new TH1F(Form("eta_%i",i)         , "" , 120, -6, 6);
      h1[Form("phi_%i",i)]         = new TH1F(Form("phi_%i",i)         , "" , 120, -6, 6);
      h1[Form("btag_%i",i)]        = new TH1F(Form("btag_%i",i)        , "" , 600, 0, 1.2);
      h1[Form("deepcsvbtag_%i",i)] = new TH1F(Form("deepcsvbtag_%i",i) , "" , 600, 0, 1.2);
      
      h1[Form("pt_%i_csv",i)]     = new TH1F(Form("pt_%i_csv",i)               , "" , 210, 0, 2100);
      h1[Form("eta_%i_csv",i)]    = new TH1F(Form("eta_%i_csv",i)              , "" , 120, -6, 6);
      h1[Form("phi_%i_csv",i)]    = new TH1F(Form("phi_%i_csv",i)              , "" , 120, -6, 6);
      h1[Form("btag_%i_csv",i)]   = new TH1F(Form("btag_%i_csv",i)             , "" , 600, 0, 1.2);
      h1[Form("deepcsvbtag_%i_csv",i)] = new TH1F(Form("deepcsvbtag_%i_csv",i) , "" , 600, 0, 1.2);

      h1[Form("pt_corrected_comp_%i",i)] = new TH1F(Form("pt_corrected_comp_%i",i), "" , 210, 0, 2100);
    }
  h1["m12"]               = new TH1F("m12"               , "" , 150, 0, 3000);
  h1["m12_csv"]           = new TH1F("m12_csv"           , "" , 150, 0, 3000);
  h1["pt_HiggsCand"]      = new TH1F("pt_HiggsCand"      , "" , 210, 0, 2100);
   
  double mbb;
  double ptH;
  double weight;
  TTree *tree = new TTree("MssmHbb_13TeV","");
  tree->Branch("mbb",&mbb,"mbb/D");
  tree->Branch("weight",&weight,"weight/D");
   
  // Analysis of events
  cout << "This analysis has " << analysis.size() << " events" << endl;
  cout << nevtmax_ << " events have been selected." << endl;
  cout << "Selected category: " << regions << endl;
  cout << "Selected number of jets: " << njetsmin_ << endl;
  cout << "btag algorithm: " << btagalgo << endl;
  cout << "region: " << sr_s << endl;
  cout << "reco: " << reco << endl;
  cout << "output file: " << outputRoot_.c_str() << endl;
  txtoutputfile << "This analysis has " << analysis.size() << " events" << endl;
  txtoutputfile << nevtmax_ << " events have been selected." << endl;
  txtoutputfile << "Selected category: "<< regions << endl;
  txtoutputfile << "Selected number of jets: " << njetsmin_ << endl;
  txtoutputfile << "btag algorithm: " << btagalgo << endl;
  txtoutputfile << "region: " << sr_s << endl;
  txtoutputfile << "reco: " << reco << endl;
  txtoutputfile << "output file: " << outputRoot_.c_str() << endl;
  
  // Cut flow
  // 0: triggered events (no. events for MC)
  // 1: 3+ idtight jets
  // 2: kinematics
  // 3: delta R(ij)
  // 4: delta eta(12) (up to this point: purely kinematics)
  // 5: btag (bbnb)
  // 6: matching
  // 7: only MC: triggered events
  int nsel[10] = { };
  int nmatch[10] = { };

  int noofeventsstart = 0;

  if ( nevtmax_ < 0 ) nevtmax_ = analysis.size();

  for ( int i = 0 ; i < nevtmax_ ; ++i )
    {
      noofeventsstart ++;
      int njets = 0;
      int njets_csv = 0;
      //int nmuons = 0;
      //int nomujet = 0;
      bool goodEvent = true;
      bool muonpresent = false;
      float eventweight = 1.0;

      if ( i > 0 && i%100000==0 ){
	std::cout << i << " events processed!" << std::endl;
	txtoutputfile << i << " events processed!" << endl;
      }
      int run = analysis.run();
      int run_crit = 304508;
     
      analysis.event(i);
      if (! isMC_ )
	{
	  if (!analysis.selectJson() ) continue; // To use only goodJSonFiles
	}
      
      if(!isMC_ && !invertCutflow_){
	int triggerFired = analysis.triggerResult(hltPath_);
	//int triggerFiredL1 = analysis.triggerResult(l1Seed_);
	//if ( !(triggerFired && triggerFiredL1) ) continue;
	if ( !triggerFired ) continue;
      } //for MC, the trigger should be the last step of cutflow

      if (!invertCutflow_) ++nsel[0]; //also for MC: equals no. of events then
      
      // Jets - std::shared_ptr< Collection<Jet> >
      auto slimmedJets = analysis.collection<Jet>("Jets");
      if (isMC_){
	auto genjets = analysis.collection<GenJet>("GenJets");
	slimmedJets->addGenJets(genjets);
      }
      
      std::vector<Jet*> selectedJets;

      for ( int j = 0 ; j < slimmedJets->size() ; ++j )
	{
	  if (slimmedJets->at(j).pileupJetIdFullId("loose") && slimmedJets->at(j).idTight() ) selectedJets.push_back(&slimmedJets->at(j));
	}

      //at least 3/4 jets present
      if ( (int)selectedJets.size() < njetsmin_ ) continue;

      ++nsel[1];
      
      // Kinematic selection - 3/4 leading jets
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
	      const Jet & jet2 = *selectedJets[j2];//if two jets are too close together: no good event
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
      float storedisc = -1;
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
	  
	  if (isMC_){
	    if (usebtagsf_){
	      float jet_btag_sf = jet->btagSF(bsf_reader);
	      eventweight *= jet_btag_sf;
	    }
	    if (j==0){
	      float signgenweight = analysis.genWeight()/fabs(analysis.genWeight());
	      eventweight *= signgenweight;
	    }
	  }

	  if ( j < 2 && btagdisc < jetsbtagmin_[j] ) goodEvent = false;// 0/1: 1st/2nd jet: always to be b tagged
	  /*
	  if ( ! signalregion_ )//CR 3 jet categroy: bbnb (3rd must not be b tagged); 4 jet cat: bbnbb
	    {
	      if ( j == 2 && btagdisc > nonbtagwp_ ) goodEvent = false;//3rd jet must never be b tagged in CR
	      if ( njetsmin_ > 3 ){
		if ( j == 3 && btagdisc < jetsbtagmin_[j] ) goodEvent = false;//4th jet should be b tagged again
	      }
	    }
	  else//SR: all 3/4 jets b tagged
	    {
	      if ( j >= 2 && btagdisc < jetsbtagmin_[j] ) goodEvent = false; 
	    }
	  */
	  if (regions == "3j"){
	    if (! signalregion_){//CR 3j: bbnb
	      if (j == 2 && btagdisc > nonbtagwp_) goodEvent = false;
	    }
	    else{//SR 3j: bbb
	      if (j == 2 && btagdisc < jetsbtagmin_[j]) goodEvent = false;
	    }
	  }
	  else if (regions == "4j3"){
	    if (! signalregion_){//CR 4j3: bbnbb
	      if ( (j == 2 && btagdisc > nonbtagwp_) || (j == 3 && btagdisc < jetsbtagmin_[j])) goodEvent = false;
	    }
	    else{//SR 4j3 bbbb
	      if ( j >= 2 && btagdisc < jetsbtagmin_[j] ) goodEvent = false;
	    }
	  }
	  else if (regions == "4j4"){
            if (! signalregion_){//CR 4j4: bbbnb
	      if ( (j == 3 && btagdisc > nonbtagwp_) || (j == 2 && btagdisc < jetsbtagmin_[j])) goodEvent = false;
            }
            else{//SR 4j4: bbbb
	      if ( j >= 2 && btagdisc < jetsbtagmin_[j] ) goodEvent = false;
            }
	  }
	  else if (regions == "3jor"){
            if (! signalregion_){//CR 3jor: bbnbnb
	      if ( j >= 2 && btagdisc > nonbtagwp_ ) goodEvent = false;
            }
            else{//SR 3jor: bbbnb || bbnbb (3rd or 4th jet may be third b-jet)
	      if (j == 2) storedisc = btagdisc;
	      if (j == 2 && (btagdisc > nonbtagwp_ && btagdisc < jetsbtagmin_[j]) ) goodEvent = false;//if larger than veto and smaller than btag: bad anyhow (neither nb nor b)
	      if (j == 3 && (storedisc >= jetsbtagmin_[2] && btagdisc > nonbtagwp_) ) goodEvent = false;//if third b -> fourth must be nb
	      if (j == 3 && (storedisc <= nonbtagwp_ && btagdisc < jetsbtagmin_[j]) ) goodEvent= false;//if third nb, fourth must be b
            }
	  }
	}//end of loop over jets for b tagging
      
      h1["m12"] -> Fill((selectedJets[0]->p4() + selectedJets[1]->p4()).M(),eventweight);
      
      if ( ! goodEvent ) continue;
      ++nsel[5];
      
      
      // Is matched?
      analysis.match<Jet,TriggerObject>("Jets",triggerObjects_,0.5);
      bool matched[12] = {true,true,true,true,true,true,true,true,true,true,true,true};//for both leading jets: five objects to be tested
      
      //last step of cutflow for MC: trigger
      if(isMC_ || invertCutflow_){
	int triggerFired = analysis.triggerResult(hltPath_);
	if ( !triggerFired ) continue;
	//++nsel[7];
      }

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
	  if ((run > run_crit && io == 0) || isMC_) continue;
	  else if (run <= run_crit && io == 1) continue;
	  if ( matched[io] ) ++nmatch[io];
	  goodEvent = ( goodEvent && matched[io] );
	}
      
      if ( ! goodEvent ) continue;
      ++nsel[6];//for MC and inverted cutflow: matching and trigger in one common step

      // Fill histograms of passed bbnb btagging selection
      for ( int j = 0 ; j < (int)selectedJets.size() ; ++j )
	{
	  if ( selectedJets[j]->pt() < 20. ) continue;
	  ++njets_csv;
	}

      h1["n_csv"] -> Fill(selectedJets.size());
      h1["n_ptmin20_csv"] -> Fill(njets_csv);
      std::vector<TLorentzVector> Corjet;
      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet* jet = selectedJets[j];
	  //Apply Jet Energy Corrections
	  TLorentzVector corJet;
	  float regressionfactor = 1.0;
	  if (useregression_){
	    regressionfactor = jet->bRegCorr();
	  }
	  float jetpt = jet->pt();
	  float corpt = jetpt * regressionfactor;
	  //Perform JER (jet energy resolution) matching and calculate corrections ("up"/"down" are +- 1 sigma uncertainties)
	  if (isMC_ && useJER_){
	    jet->jerInfo(*jerinfo,0.2);
	    float correctResolution = jet->jerCorrection();
	    corpt *= correctResolution;
	    //float correctResolutionUp = selectedJets[i].jerCorrection("up");
	    //float correctResolutionDown = selectedJets[i].jerCorrection("down");
	  }
	  float jetmass = (jet->p4()).M();
	  float jeteta = jet->eta();
	  float jetphi = jet->phi();
	  corJet.SetPtEtaPhiM(corpt,jeteta,jetphi,jetmass);
	  jet->p4(corJet);
	  Corjet.push_back(corJet);
	  //cout << "For jet " << j+1 << ": " << "pt without correction: " << jet->pt() << ", eta/phi (from TLV): " << jet->eta() << "/" << jet->phi() << " (" << corJet.Eta()  << "/" << corJet.Phi() << ")" << "; pt with correction (calc): " << corpt << " and from new TLV: " << corJet.Pt() << endl;
	  //cout << "Mass from TLV: " << corJet.M() << endl;
	  h1[Form("pt_corrected_comp_%i",j)] -> Fill(corpt,eventweight);
	  h1[Form("pt_%i_csv",j)]   -> Fill(corJet.Pt(),eventweight);
	  //h1[Form("pt_%i_csv",j)]   -> Fill(jet->pt(),eventweight);
	  h1[Form("eta_%i_csv",j)]  -> Fill(jet->eta(),eventweight);
	  h1[Form("phi_%i_csv",j)]  -> Fill(jet->phi(),eventweight);
	  h1[Form("btag_%i_csv",j)] -> Fill(jet->btag(),eventweight);
	  h1[Form("deepcsvbtag_%i_csv",j)] -> Fill(jet->btag("btag_deepb")+jet->btag("btag_deepbb"),eventweight);
	}

      /*cout << "left loop" << endl;
	for (int j = 0; j < (int)Corjet.size(); ++j){
	cout << "For jet " << j+1 << ": " << Corjet[j].Eta()  << "/" << Corjet[j].Phi() << "; pt from new TLV: " << Corjet[j].Pt() << endl;
	cout << "Mass from TLV: " << Corjet[j].M() << endl;
	}*/
      mbb = (Corjet[0] + Corjet[1]).M();
      if ( !signalregion_ || isMC_)//blinding
	{ 
	  h1["m12_csv"] -> Fill(mbb,eventweight);
	  weight = eventweight;
	  tree -> Fill();
	}

      if (isMC_){
	ptH = (Corjet[0] + Corjet[1]).Pt();
	h1["pt_HiggsCand"] -> Fill(ptH,eventweight);
      }


      // Check for muons in the jets
      if (muonveto_){
	std::vector<Muon*> selectedMuons;
	const char muID = muonsid_.at(0);
	auto slimmedMuons = analysis.collection<Muon>("Muons");
	for ( int m = 0 ; m < slimmedMuons->size() ; ++m )
	  {
	    if ( (muID == 'M' && slimmedMuons->at(m).isMediumMuon()) || (muID == 'T' && slimmedMuons->at(m).isTightMuon())){
	      selectedMuons.push_back(&slimmedMuons->at(m));
	    }
	  }
      
	std::vector<Muon*> MuonsinJet;
	for ( size_t m = 0; m < selectedMuons.size(); ++m )      
	  {
	    Muon* muon = selectedMuons[m];
	    if ( muon->pt() < muonsptmin_[m] || fabs(muon->eta()) > muonsetamax_[m] ){
	      float dR_muj0 = selectedJets[0]->deltaR(*muon);
	      float dR_muj1 = selectedJets[1]->deltaR(*muon);
	    
	      if ( dR_muj0 < drmax_  || dR_muj1 < drmax_) //at least 1 muon in a jet originating from the Higgs
		{
		  muonpresent  = true;
		  MuonsinJet.push_back(muon);
		  break;
		}
	    }
	  } //end: loop over muons
	if ( muonpresent ) continue;
	nsel[7]++;
      }
    }//end: event loop

  h1["noofevents_h"] -> SetBinContent(1,noofeventsstart); //total number of events
  h1["noofevents_h"] -> SetBinContent(2,nsel[0]); //triggered
  h1["noofevents_h"] -> SetBinContent(3,nsel[1]); //3/4 jets (tight)
  h1["noofevents_h"] -> SetBinContent(4,nsel[2]); //kin
  h1["noofevents_h"] -> SetBinContent(5,nsel[3]); //dR
  h1["noofevents_h"] -> SetBinContent(6,nsel[4]); //deta
  h1["noofevents_h"] -> SetBinContent(7,nsel[5]); //btag
  h1["noofevents_h"] -> SetBinContent(8,nsel[6]); //final selection (perhaps trigger; matching)
  if(muonveto_) h1["noofevents_h"] -> SetBinContent(9,nsel[7]); //including muon veto

  for (auto & ih1 : h1)
    {
      ih1.second -> Write();
    }
   
  // PRINT OUTS

  // Cut flow
  // 0: triggered events (MC: no. of events)
  // 1: 3+ or 4+ idtight jets
  // 2: kinematics
  // 3: delta R(ij)
  // 4: delta eta(12) (up to this point: purely kinematics)
  // 5: btag (bbnb)
  // 6: matching
  // 7: ONLY MC: trigger

  double fracAbs[10];
  double fracRel[10];
  std::string cuts[10];
  cuts[0] = "Triggered";
  if (isMC_) cuts[0] = "Number of events";
  cuts[1] = "Triple/quadruple idtight-jet";
  cuts[2] = "Triple/quadruple jet kinematics";
  cuts[3] = "Delta R(i;j)";
  cuts[4] = "Delta eta(j1;j2)";
  cuts[5] = "btagged (bbnb/bbnbnb)";
  if (signalregion_) cuts[5] = "btagged (bbb/bbbb)";
  cuts[6] = "Matched to online j1;j2";
  if (invertCutflow_) cuts[6] = "Trigger and matching j1;j2";
  if(muonveto_) cuts[7] = "Muon veto";
  //if (isMC_ || invertCutflow_) cuts[7] = "Triggered";

  printf ("%-23s  %10s  %10s  %10s \n", std::string("Cut flow").c_str(), std::string("# events").c_str(), std::string("absolute").c_str(), std::string("relative").c_str() ); 
  txtoutputfile << "Cut flow " << "# events " << "absolute " << "relative" << endl;
  //if (!isMC_){
  if (!invertCutflow_){
    if(muonveto_) {
      for ( int i = 0; i < 8; ++i )
	{
	  fracAbs[i] = double(nsel[i])/nsel[0];
	  if ( i>0 ){
	    fracRel[i] = double(nsel[i])/nsel[i-1];
	  }
	  else{
	    fracRel[i] = fracAbs[i];
	  }
	  printf ("%-23s  %10d  %10.3f  %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] ); 
	  txtoutputfile << cuts[i].c_str() << " " << nsel[i] << " " << fracAbs[i] << " " << fracRel[i] << endl;
	  h1["cutflow"] -> SetBinContent(i+1,fracAbs[i]);
	}
    }
    else{
      for ( int i = 0; i < 7; ++i )
        {
          fracAbs[i] = double(nsel[i])/nsel[0];
          if ( i>0 ){
            fracRel[i] = double(nsel[i])/nsel[i-1];
          }
          else{
            fracRel[i] = fracAbs[i];
          }
          printf ("%-23s  %10d  %10.3f  %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] );
          txtoutputfile << cuts[i].c_str() << " " << nsel[i] << " " << fracAbs[i] << " " << fracRel[i] << endl;
          h1["cutflow"] -> SetBinContent(i+1,fracAbs[i]);
        }
    }
  }
  /* else if (isMC_){
     for ( int i = 0; i < 8; ++i )
     {
     fracAbs[i] = double(nsel[i])/nsel[0];
     if ( i>0 )
     fracRel[i] = double(nsel[i])/nsel[i-1];
     else
     fracRel[i] = fracAbs[i];
     printf ("%-23s  %10d  %10.3f  %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] ); 
     txtoutputfile << cuts[i].c_str() << " " << nsel[i] << " " << fracAbs[i] << " " << fracRel[i] << endl;
     h1["cutflow"] -> SetBinContent(i+1,fracAbs[i]);
     }
     }*/
  else if (invertCutflow_){
    for ( int i = 1; i < 8; ++i )
      {
	fracAbs[i] = double(nsel[i])/nsel[1];
	if ( i>1 )
	  fracRel[i] = double(nsel[i])/nsel[i-1];
	else
	  fracRel[i] = fracAbs[i];
	printf ("%-23s  %10d  %10.3f  %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] ); 
	txtoutputfile << cuts[i].c_str() << " " << nsel[i] << " " << fracAbs[i] << " " << fracRel[i] << endl;
	h1["cutflow"] -> SetBinContent(i+1,fracAbs[i]);
      }
  }

  hout.Write();
  hout.Close();
  
  // CSV output
  //printf ("%-23s , %10s , %10s , %10s \n", std::string("Cut flow").c_str(), std::string("# events").c_str(), std::string("absolute").c_str(), std::string("relative").c_str() ); 
  //for ( int i = 0; i < 7; ++i )
  //printf ("%-23s , %10d , %10.3f , %10.3f \n", cuts[i].c_str(), nsel[i], fracAbs[i], fracRel[i] );

} //end main
