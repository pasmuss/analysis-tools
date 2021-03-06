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
#include "TH2.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"

#include "Analysis/Tools/interface/Analysis.h"
#include "Analysis/Tools/bin/macro_config.h"

using namespace std;
using namespace analysis;
using namespace analysis::tools;

//Function declarations
void correctJetpt ( Jet& , const float& );
void copyJetpt    ( Jet & , Jet & );
void applyPrescale ( const int& run, const double& random, float& prescaleEra, const int nsubsamples, int& window );
void calculateEventHT ( const std::vector<Jet*> jets, const double pt, const double eta, double& targetHT );
void addBtagWeight (Jet* jet, float& weight);

// Systematic variations
std::vector<std::string> systematics = { "PU", "SFbtag", "onlSFbtag", "JER", "JES", "jet_trigeff" };
std::vector<std::string> vars = { "up", "down" };
std::vector<std::string> flavors = { "b", "bb", "c", "cc", "udsg" };

// b tag weight file
TFile* btagweightfile = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/btag_eff_deepflavour_medium_pt_eta_flavour.root","READ");

// =============================================================================================   
int main(int argc, char * argv[])
{
  if ( macro_config(argc, argv) != 0 ) return -1;
   
  TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
  TH2::SetDefaultSumw2();
   
  // Input files list
  Analysis analysis(inputlist_);

  string btagalgo = btagalgo_;
  string reco = reco_;

  string regions = regions_;

  float ptHT = ptHT_;
  float etaHT = etaHT_;

  float border_other_wp = BorderOtherWP_;//to enable setting
  float other_wp = OtherWP_;//another btag wp above a certain pt

  if (reco == "prompt"){
    analysis.addTree<Jet> ("Jets","MssmHbb/Events/slimmedJetsPuppi");
    analysis.addTree<Muon>("Muons","MssmHbb/Events/slimmedMuons");
  }
  else if (reco == "rereco"){//this is the default and also applicable for MC!
    analysis.addTree<Jet> ("Jets","MssmHbb/Events/updatedPatJets");
    analysis.addTree<Muon>("Muons","MssmHbb/Events/slimmedMuons");
    if (isMC_){
      analysis.addTree<GenJet>("GenJets","MssmHbb/Events/slimmedGenJets");
      analysis.addTree<GenParticle>("GenParticles","MssmHbb/Events/prunedGenParticles");
    }
  }
  else{
    cout << "Neither prompt nor rereco data selected. Aborting." << endl;
    return -1;
  }

  auto jerinfo = analysis.jetResolutionInfo("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/Fall17_V3_MC_PtResolution_AK4PFchs.txt", "/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/Fall17_V3_MC_SF_AK4PFchs.txt");
  
  auto bsf_reader = analysis.btagCalibration("deepflavour", "/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/DeepFlavour_94XSF_V3_B_F.csv", "medium");

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
  
  float prescaleEra = (float)prescale_;
  int nsubsamples = prescale_;
  
  std::string sr_s = "SR";
  if ( ! signalregion_ ) sr_s = "CR";
  boost::algorithm::replace_last(outputRoot_, ".root", "_"+sr_s+".root"); 
   
  TFile hout(outputRoot_.c_str(),"recreate");
  ofstream txtoutputfile;
  txtoutputfile.open("output.txt",ios::app);

  TH2F* th2_pT_onlbtagsf = new TH2F("th2_pT_onlbtagsf", "", 2100, 0, 2100, 400, -2, 2);
  TH2F* th2_pT_offlbtagsf = new TH2F("th2_pT_offlbtagsf", "", 2100, 0, 2100, 400, -2, 2);
   
  std::map<std::string, TH1F*> h1;
  std::map<std::string, TH2F*> h2;

  h1["noofevents_h"]      = new TH1F("noofevents_h"     , "" ,   10,  0,    10);
  h1["noofevents_w_nlo"]  = new TH1F("noofevents_w_nlo" , "" ,   10,  0,    10);
  h1["n"]                 = new TH1F("n"                , "" ,   30,  0,    30);
  h1["n_csv"]             = new TH1F("n_csv"            , "" ,   30,  0,    30);
  h1["n_ptmin20"]         = new TH1F("n_ptmin20"        , "" ,   30,  0,    30);
  h1["n_ptmin20_csv"]     = new TH1F("n_ptmin20_csv"    , "" ,   30,  0,    30);
  h1["nentries"]          = new TH1F("nentries"         , "" ,    2,  0,     2);

  h1["deltaeta12"]        = new TH1F("deltaeta12"       , "" ,  120, -6,     6);

  h1["nentries_SR1"]      = new TH1F("nentries_SR1"     , "" ,    1,  0,     1);
  h1["nentries_SR2"]      = new TH1F("nentries_SR2"     , "" ,    1,  0,     1);
  h1["nentries_SR3"]      = new TH1F("nentries_SR3"     , "" ,    1,  0,     1);
  h1["nentries_SR4"]      = new TH1F("nentries_SR4"     , "" ,    1,  0,     1);

  h1["HT_bef_cuts"]       = new TH1F("HT_bef_cuts"      , "" , 1080,  0, 10800);
  h1["HT"]                = new TH1F("HT"               , "" , 1080,  0, 10800);
  h1["HT_after_bTag"]     = new TH1F("HT_after_bTag"    , "" , 1080,  0, 10800);
  h1["HT_csv"]            = new TH1F("HT_csv"           , "" , 1080,  0, 10800);
  h1["HT_aac"]            = new TH1F("HT_aac"           , "" , 1080,  0, 10800);

  h1["jetswomu"]          = new TH1F("jetswomu"         , "" ,   30,  0,    30);
  
  h1["n_muons"]           = new TH1F("n_muons"          , "" ,   30,  0,    30);
  h1["pt_mu"]             = new TH1F("pt_mu"            , "" ,  150,  0,  1500);
  h1["eta_mu"]            = new TH1F("eta_mu"           , "" ,  120, -6,     6);

  h1["pt_corrected_comp"] = new TH1F("pt_corrected_comp", "" ,  210,  0,  2100);
  
  h1["dR_muj"]            = new TH1F("dR_muj"           , "" ,  120,  0,     0.6);
  h1["dR_muj0"]           = new TH1F("dR_muj0"          , "" ,  120,  0,     0.6);
  h1["dR_muj1"]           = new TH1F("dR_muj1"          , "" ,  120,  0,     0.6);

  h1["deltaeta12_aac"]    = new TH1F("deltaeta12_aac"   , "" ,  120, -6,     6);
  h1["deltaphi12_aac"]    = new TH1F("deltaphi12_aac"   , "" ,  120, -6,     6);

  h1["pt_softjet"]        = new TH1F("pt_softjet"       , "",   210,  0,  2100);
  h1["dR_jsoftjet"]       = new TH1F("dR_jsoftjet"      , "",   120,  0,     0.6);
  h1["rank_softjet"]      = new TH1F("rank_softjet"     , "",    20,  0,    20);

  h1["cutflow"]           = new TH1F("cutflow"          , "",    10,  0,    10);

  h1["onl_btag_sf"]       = new TH1F("onl_btag_sf"      , "",  400 , -2,     2);
   
  for ( int i = 0 ; i < njetsmin_ ; ++i )
    {
      //after kinematic cuts, before b tagging
      h1[Form("pt_%i",i)]          = new TH1F(Form("pt_%i",i)          , "" , 210, 0, 2100);
      h1[Form("eta_%i",i)]         = new TH1F(Form("eta_%i",i)         , "" , 120, -6, 6);
      h1[Form("phi_%i",i)]         = new TH1F(Form("phi_%i",i)         , "" , 120, -6, 6);
      h1[Form("btag_%i",i)]        = new TH1F(Form("btag_%i",i)        , "" , 600, 0, 1.2);
      h1[Form("deepcsvbtag_%i",i)] = new TH1F(Form("deepcsvbtag_%i",i) , "" , 600, 0, 1.2);
      h1[Form("deepflavourbtag_%i",i)] = new TH1F(Form("deepflavourbtag_%i",i) , "" , 600, 0, 1.2);

      h2[Form("pt_eta_%i",i)] = new TH2F(Form("pt_eta_%i",i), "" , 210, 0, 2100, 120, -6, 6);
      
      //after b tagging
      h1[Form("pt_%i_csv",i)]     = new TH1F(Form("pt_%i_csv",i)               , "" , 210, 0, 2100);
      h1[Form("eta_%i_csv",i)]    = new TH1F(Form("eta_%i_csv",i)              , "" , 120, -6, 6);
      h1[Form("phi_%i_csv",i)]    = new TH1F(Form("phi_%i_csv",i)              , "" , 120, -6, 6);
      h1[Form("btag_%i_csv",i)]   = new TH1F(Form("btag_%i_csv",i)             , "" , 600, 0, 1.2);
      h1[Form("deepcsvbtag_%i_csv",i)] = new TH1F(Form("deepcsvbtag_%i_csv",i) , "" , 600, 0, 1.2);
      h1[Form("deepflavourbtag_%i_csv",i)] = new TH1F(Form("deepflavourbtag_%i_csv",i) , "" , 600, 0, 1.2);

      h2[Form("pt_eta_%i_csv",i)] = new TH2F(Form("pt_eta_%i_csv",i), "" , 210, 0, 2100, 120, -6, 6);

      //after all cuts (including m12)
      h1[Form("pt_%i_aac",i)]              = new TH1F(Form("pt_%i_aac",i)              , "" , 210,  0, 2100);
      h1[Form("eta_%i_aac",i)]             = new TH1F(Form("eta_%i_aac",i)             , "" , 120, -6,    6);
      h1[Form("deepflavourbtag_%i_aac",i)] = new TH1F(Form("deepflavourbtag_%i_aac",i) , "" , 600,  0,  1.2);

      h1[Form("pt_corrected_comp_%i",i)] = new TH1F(Form("pt_corrected_comp_%i",i), "" , 210, 0, 2100);

      h1[Form("eta_%i_aac_pTbelowMax",i)]  = new TH1F(Form("eta_%i_aac_pTbelowMax",i)  , "" , 120, -6,    6);

      h2[Form("pt_eta_%i_aac",i)] = new TH2F(Form("pt_eta_%i_aac",i), "" , 210, 0, 2100, 120, -6, 6);

      //for flavors
      for (unsigned int f = 0; f < flavors.size(); f++){
	h1[Form("pt_%i_%s",i,(flavors[f]).c_str())]                  = new TH1F(Form("pt_%i_%s",i,(flavors[f]).c_str())                  , "" , 210, 0, 2100);
	h1[Form("eta_%i_%s",i,(flavors[f]).c_str())]                 = new TH1F(Form("eta_%i_%s",i,(flavors[f]).c_str())                 , "" , 120, -6, 6);
	h1[Form("phi_%i_%s",i,(flavors[f]).c_str())]                 = new TH1F(Form("phi_%i_%s",i,(flavors[f]).c_str())                 , "" , 120, -6, 6);
	h1[Form("deepflavourbtag_%i_%s",i,(flavors[f]).c_str())]     = new TH1F(Form("deepflavourbtag_%i_%s",i,(flavors[f]).c_str())     , "" , 600, 0, 1.2);
	h1[Form("pt_%i_%s_csv",i,(flavors[f]).c_str())]              = new TH1F(Form("pt_%i_%s_csv",i,(flavors[f]).c_str())              , "" , 210, 0, 2100);
	h1[Form("eta_%i_%s_csv",i,(flavors[f]).c_str())]             = new TH1F(Form("eta_%i_%s_csv",i,(flavors[f]).c_str())             , "" , 120, -6, 6);
	h1[Form("phi_%i_%s_csv",i,(flavors[f]).c_str())]             = new TH1F(Form("phi_%i_%s_csv",i,(flavors[f]).c_str())             , "" , 120, -6, 6);
	h1[Form("deepflavourbtag_%i_%s_csv",i,(flavors[f]).c_str())] = new TH1F(Form("deepflavourbtag_%i_%s_csv",i,(flavors[f]).c_str()) , "" , 600, 0, 1.2);
	h1[Form("pt_%i_%s_aac",i,(flavors[f]).c_str())]              = new TH1F(Form("pt_%i_%s_aac",i,(flavors[f]).c_str())              , "" , 210,  0, 2100);
	h1[Form("eta_%i_%s_aac",i,(flavors[f]).c_str())]             = new TH1F(Form("eta_%i_%s_aac",i,(flavors[f]).c_str())             , "" , 120, -6,    6);
	h1[Form("phi_%i_%s_aac",i,(flavors[f]).c_str())]             = new TH1F(Form("phi_%i_%s_aac",i,(flavors[f]).c_str())             , "" , 120, -6, 6);
	h1[Form("deepflavourbtag_%i_%s_aac",i,(flavors[f]).c_str())] = new TH1F(Form("deepflavourbtag_%i_%s_aac",i,(flavors[f]).c_str()) , "" , 600,  0,  1.2);

	h2[Form("pt_eta_%i_%s",i,(flavors[f]).c_str())]     = new TH2F(Form("pt_eta_%i_%s",i,(flavors[f]).c_str()), "" , 210, 0, 2100, 120, -6, 6);
	h2[Form("pt_eta_%i_%s_csv",i,(flavors[f]).c_str())] = new TH2F(Form("pt_eta_%i_%s_csv",i,(flavors[f]).c_str()), "" , 210, 0, 2100, 120, -6, 6);
	h2[Form("pt_eta_%i_%s_aac",i,(flavors[f]).c_str())] = new TH2F(Form("pt_eta_%i_%s_aac",i,(flavors[f]).c_str()), "" , 210, 0, 2100, 120, -6, 6);
      }
      
    }
  h1["m12_noCuts"]        = new TH1F("m12_noCuts"        , "" , 150, 0, 3000);
  h1["m12"]               = new TH1F("m12"               , "" , 150, 0, 3000);
  h1["m12_aac"]           = new TH1F("m12_aac"           , "" , 150, 0, 3000);
  h1["pt_HiggsCand"]      = new TH1F("pt_HiggsCand"      , "" , 210, 0, 2100);

  //SR histograms 3b category (intended for aac, only final selection for combine tool use)
  h1["m12_SR1_1GeV"]            = new TH1F("m12_SR1_1GeV"           , "" ,300, 200,  500);// 1 GeV binning 
  h1["m12_SR1_2GeV"]            = new TH1F("m12_SR1_2GeV"           , "" ,150, 200,  500);// 2 GeV binning 
  h1["m12_SR1_5GeV"]            = new TH1F("m12_SR1_5GeV"           , "" , 60, 200,  500);// 5 GeV binning
  h1["m12_SR1_10GeV"]           = new TH1F("m12_SR1_10GeV"          , "" , 30, 200,  500);//10 GeV binning

  h1["m12_SR2_1GeV"]            = new TH1F("m12_SR2_1GeV"           , "" , 525,260,  785);// 1 GeV binning
  h1["m12_SR2_3GeV"]            = new TH1F("m12_SR2_3GeV"           , "" , 175,260,  785);// 3 GeV binning
  h1["m12_SR2_5GeV"]            = new TH1F("m12_SR2_5GeV"           , "" , 105,260,  785);// 5 GeV binning
  h1["m12_SR2_15GeV"]           = new TH1F("m12_SR2_15GeV"          , "" , 35, 260,  785);//15 GeV binning

  h1["m12_SR3_5GeV"]            = new TH1F("m12_SR3_5GeV"           , "" , 176,390, 1270);// 5 GeV binning
  h1["m12_SR3_20GeV"]           = new TH1F("m12_SR3_20GeV"          , "" , 44, 390, 1270);//20 GeV binning

  h1["m12_SR4_5GeV"]            = new TH1F("m12_SR4_5GeV"           , "" , 300,500, 2000);// 5 GeV binning
  h1["m12_SR4_10GeV"]           = new TH1F("m12_SR4_10GeV"          , "" , 150,500, 2000);//10 GeV binning
  h1["m12_SR4_25GeV"]           = new TH1F("m12_SR4_25GeV"          , "" , 60, 500, 2000);//25 GeV binning

  //cutflow: m12 histograms including event weights after each step of cutflow
  //and for each fit range with respective (1/1/5/10 GeV) binning
  //plu total with 20 GeV binning
  //float mbb = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
  //steps: 15
  
  for (unsigned int stepnumber = 1; stepnumber <= 15; stepnumber ++){
    h1[Form("m12_SR1_1GeV_step%i",stepnumber)]       = new TH1F(Form("m12_SR1_1GeV_step%i",stepnumber)           , "" ,300,200,  500);
    h1[Form("m12_SR2_1GeV_step%i",stepnumber)]       = new TH1F(Form("m12_SR2_1GeV_step%i",stepnumber)           , "" ,525,260,  785);
    h1[Form("m12_SR3_5GeV_step%i",stepnumber)]       = new TH1F(Form("m12_SR3_5GeV_step%i",stepnumber)           , "" ,176,390, 1270);
    h1[Form("m12_SR4_10GeV_step%i",stepnumber)]      = new TH1F(Form("m12_SR4_10GeV_step%i",stepnumber)          , "" ,150,500, 2000);
    h1[Form("m12_total_step%i",stepnumber)]          = new TH1F(Form("m12_total_step%i",stepnumber)              , "" ,150,  0, 3000);
}

  h1["pt_0_JER_up"]                    = new TH1F("pt_0_JER_up"                    , "" , 210,  0, 2100);
  h1["pt_0_JER_down"]                  = new TH1F("pt_0_JER_down"                  , "" , 210,  0, 2100);
  h1["j0_JER_diff"]                    = new TH1F("j0_JER_diff"                    , "" , 210,  0, 2100);
  h1["j1_JER_diff"]                    = new TH1F("j1_JER_diff"                    , "" , 210,  0, 2100);
  h1["pt_1_JER_up"]                    = new TH1F("pt_1_JER_up"                    , "" , 210,  0, 2100);
  h1["pt_1_JER_down"]                  = new TH1F("pt_1_JER_down"                  , "" , 210,  0, 2100);
  h1["pt_0_JES_up"]                    = new TH1F("pt_0_JES_up"                    , "" , 210,  0, 2100);
  h1["pt_0_JES_down"]                  = new TH1F("pt_0_JES_down"                  , "" , 210,  0, 2100);
  h1["pt_1_JES_up"]                    = new TH1F("pt_1_JES_up"                    , "" , 210,  0, 2100);
  h1["pt_1_JES_down"]                  = new TH1F("pt_1_JES_down"                  , "" , 210,  0, 2100);

  //for each: additional, properly (1/1/5/10 GeV) binned FR hist
  //loop over systematics and vars
  for (unsigned int varentry = 0; varentry < vars.size(); varentry++){
    for (unsigned int systentry = 0; systentry < systematics.size(); systentry++){
      h1[Form("m12_aac_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str())] = new TH1F(Form("m12_aac_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str()), "", 150, 0, 3000);
      h1[Form("m12_SR1_1GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str())] = new TH1F(Form("m12_SR1_1GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str()), "", 300, 200,  500);
      h1[Form("m12_SR2_1GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str())] = new TH1F(Form("m12_SR2_1GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str()), "", 525, 260,  785);
      h1[Form("m12_SR3_5GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str())] = new TH1F(Form("m12_SR3_5GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str()), "", 176, 390, 1270);
      h1[Form("m12_SR4_10GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str())] = new TH1F(Form("m12_SR4_10GeV_%s_%s",(systematics[systentry]).c_str(),(vars[varentry]).c_str()), "", 150, 500, 2000);
    }
  }
  /*h1["m12_aac_PU_up"]            = new TH1F("m12_aac_PU_up", "", 150, 0, 3000);
  h1["m12_aac_PU_down"]          = new TH1F("m12_aac_PU_down", "", 150, 0, 3000);
  h1["m12_aac_SFbtag_up"]        = new TH1F("m12_aac_SFbtag_up", "", 150, 0, 3000);
  h1["m12_aac_SFbtag_down"]      = new TH1F("m12_aac_SFbtag_down", "", 150, 0, 3000);
  h1["m12_aac_onlSFbtag_up"]     = new TH1F("m12_aac_onlSFbtag_up", "", 150, 0, 3000);
  h1["m12_aac_onlSFbtag_down"]   = new TH1F("m12_aac_onlSFbtag_down", "", 150, 0, 3000);
  h1["m12_aac_jet_trigeff_up"]   = new TH1F("m12_aac_jet_trigeff_up", "", 150, 0, 3000);
  h1["m12_aac_jet_trigeff_down"] = new TH1F("m12_aac_jet_trigeff_down", "", 150, 0, 3000);
  h1["m12_aac_JER_up"]           = new TH1F("m12_aac_JER_up", "", 150, 0, 3000);
  h1["m12_aac_JER_down"]         = new TH1F("m12_aac_JER_down", "", 150, 0, 3000);
  h1["m12_aac_JES_up"]           = new TH1F("m12_aac_JES_up", "", 150, 0, 3000);
  h1["m12_aac_JES_down"]         = new TH1F("m12_aac_JES_down", "", 150, 0, 3000);*/
  h1["m12_JER_diff"]             = new TH1F("m12_JER_diff", "", 150, 0, 3000);
  
  for ( int i = 0 ; i < nsubsamples ; ++i )
    h1[Form("m12_sel_%i",i)]  = new TH1F(Form("m12_sel_%i",i) , "" , 150, 0, 3000);

  double mbb;
  double mbb_sel;
  double ptH;
  double weight;
  double mbbw[nsubsamples];

  TTree *tree = new TTree("MssmHbb_13TeV","");
  tree->Branch("mbb",&mbb,"mbb/D");
  tree->Branch("weight",&weight,"weight/D");
  tree->Branch("nsubsamples",&nsubsamples,"nsubsamples/I");

  TTree *tree0 = new TTree("MssmHbb_13TeV_0","");
  tree0->Branch("mbb",&mbb,"mbb/D");
  tree0->Branch("weight",&weight,"weight/D");

  TTree *tree1 = new TTree("MssmHbb_13TeV_1","");
  tree1->Branch("mbb",&mbb,"mbb/D");
  tree1->Branch("weight",&weight,"weight/D");

  TTree *tree2 = new TTree("MssmHbb_13TeV_2","");
  tree2->Branch("mbb",&mbb,"mbb/D");
  tree2->Branch("weight",&weight,"weight/D");

  TTree *tree3 = new TTree("MssmHbb_13TeV_3","");
  tree3->Branch("mbb",&mbb,"mbb/D");
  tree3->Branch("weight",&weight,"weight/D");

  TTree *tree4 = new TTree("MssmHbb_13TeV_4","");
  tree4->Branch("mbb",&mbb,"mbb/D");
  tree4->Branch("weight",&weight,"weight/D");

  TTree *tree5 = new TTree("MssmHbb_13TeV_5","");
  tree5->Branch("mbb",&mbb,"mbb/D");
  tree5->Branch("weight",&weight,"weight/D");

  TTree *tree6 = new TTree("MssmHbb_13TeV_6","");
  tree6->Branch("mbb",&mbb,"mbb/D");
  tree6->Branch("weight",&weight,"weight/D");

  std::map<std::string, TTree *> m12_vars;

  for ( auto & sys : systematics)
    {
      for ( auto & var : vars )
	{
	  m12_vars[("m12_"+sys+"_"+var).c_str()] = new TTree( ("MssmHbb_13TeV_"+ sys +"_" + var).c_str() ,"" );
	  m12_vars[("m12_"+sys+"_"+var).c_str()] ->Branch("mbb",&mbb,"mbb/D");
	  m12_vars[("m12_"+sys+"_"+var).c_str()] ->Branch("weight",&weight,"weight/D");
	}
    }

  // Analysis of events
  cout << "This analysis has " << analysis.size() << " events" << endl;
  cout << nevtmax_ << " events have been selected." << endl;
  cout << "Selected category: " << regions << endl;
  cout << "Selected number of jets: " << njetsmin_ << endl;
  cout << "btag algorithm: " << btagalgo << endl;
  if (border_other_wp > 0 && other_wp > 0){
    cout << "Above pT of " << border_other_wp << " GeV (j1,j2) using btag discriminant > " << other_wp << endl;
    txtoutputfile << "Above pT of " << border_other_wp << " GeV (j1,j2) using btag discriminant > " << other_wp << endl;
  }
  if (massdepptcut_ > 0){
    cout << "pT of j1,j2 has to be above " << massdepptcut_ << "*m12." << endl;
    txtoutputfile << "pT of j1,j2 has to be above " << massdepptcut_ << "*m12." << endl;
  }
  cout << "region: " << sr_s << endl;
  cout << "reco: " << reco << endl;
  cout << "output file: " << outputRoot_.c_str() << endl;
  cout << "ntuples file: " << inputlist_.c_str() << endl;
  cout << "PU file: " << pufile_.c_str() << endl;
  cout << "JER variations: " << jervar_.c_str() << ", JES: " << jecsigma_ << " sigmas" << endl;
  txtoutputfile << "This analysis has " << analysis.size() << " events" << endl;
  txtoutputfile << nevtmax_ << " events have been selected." << endl;
  txtoutputfile << "Selected category: "<< regions << endl;
  txtoutputfile << "Selected number of jets: " << njetsmin_ << endl;
  txtoutputfile << "btag algorithm: " << btagalgo << endl;
  txtoutputfile << "region: " << sr_s << endl;
  txtoutputfile << "reco: " << reco << endl;
  txtoutputfile << "output file: " << outputRoot_.c_str() << endl;
  txtoutputfile << "ntuples file: " << inputlist_.c_str() << endl;
  txtoutputfile << "PU file: " << pufile_.c_str() << endl;
  txtoutputfile << "JER variations: " << jervar_.c_str() << ", JES: " << jecsigma_ << " sigmas" << endl;
  
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
  int nweigh[10] = { };
  int nmatch[10] = { };
  int n_SR[10] = { };

  int noofeventsstart = 0;

  //seed reading and random generator for prescaling
  int seed = analysis.seed("seed.txt");
  TRandom3 *R = new TRandom3( seed );

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
      float puweight = 0;
      float pudown = 0;
      float puup = 0;

      analysis.event(i);

      //load jet collection
      auto slimmedJets = analysis.collection<Jet>("Jets");

      // Jets - std::shared_ptr< Collection<Jet> >
      float sgweight = 0;
      if (isMC_){
	auto genjets = analysis.collection<GenJet>("GenJets");
	slimmedJets->addGenJets(genjets);

	/*std::vector<Jet*> slimmedGenJets;//get a vector of GenJets
	  for (int a = 0; a < genjets->size(); a++){
	  slimmedGenJets.push_back(&genjets->at(a));
	  }*/

	//Assigning flavor to jets
	auto particles = analysis.collection<GenParticle>("GenParticles");
	slimmedJets->associatePartons(particles,0.4,5);

	float signgenweight = analysis.genWeight()/fabs(analysis.genWeight());
	eventweight *= signgenweight;
      }

      if (slimmedJets->size() < 2) continue;

      //step 1: effective events (including negative generator weights), no trigger, full collection (events with at least any two jets)
      float mbbstep1 = (slimmedJets->at(0).p4() + slimmedJets->at(1).p4()).M();
      h1["m12_total_step1"] -> Fill(mbbstep1,eventweight);
      if (mbbstep1 > 200 && mbbstep1 < 500){
        h1["m12_SR1_1GeV_step1"] -> Fill(mbbstep1,eventweight);
      }
      if (mbbstep1 > 260 && mbbstep1 < 785){
        h1["m12_SR2_1GeV_step1"] -> Fill(mbbstep1,eventweight);
      }
      if (mbbstep1 > 390 && mbbstep1 < 1270){
	h1["m12_SR3_5GeV_step1"] -> Fill(mbbstep1,eventweight);
      }
      if (mbbstep1 > 500 && mbbstep1 < 2000){
	h1["m12_SR4_10GeV_step1"] -> Fill(mbbstep1,eventweight);
      }
      
      if (isMC_){
	puweight = puweights->weight(analysis.nTruePileup(),0);//0: central; replace by +-1/2 for +- 1/2 sigma variation (up/down); should use specific values (puup, pudown) for that purpose!
	eventweight *= puweight;
	pudown = puweights->weight(analysis.nTruePileup(),-1);
	puup = puweights->weight(analysis.nTruePileup(),+1);
      }

      int window = 0;
      
      if ( i > 0 && i%100000==0 ){
	std::cout << i << " events processed!" << std::endl;
	txtoutputfile << i << " events processed!" << endl;
      }
      int run = analysis.run();
      int run_crit = 304508;
     
      if (! isMC_ )
	{
	  if (!analysis.selectJson() ) continue; // To use only goodJSonFiles
	}

      //step 2: json (only data)
      //step 2: include PU weight (only MC)
      float mbbstep2 = (slimmedJets->at(0).p4() + slimmedJets->at(1).p4()).M();
      h1["m12_total_step2"] -> Fill(mbbstep2,eventweight);
      if (mbbstep2 > 200 && mbbstep2 < 500){
        h1["m12_SR1_1GeV_step2"] -> Fill(mbbstep2,eventweight);
      }
      if (mbbstep2 > 260 && mbbstep2 < 785){
        h1["m12_SR2_1GeV_step2"] -> Fill(mbbstep2,eventweight);
      }
      if (mbbstep2 > 390 && mbbstep2 < 1270){
	h1["m12_SR3_5GeV_step2"] -> Fill(mbbstep2,eventweight);
      }
      if (mbbstep2 > 500 && mbbstep2 < 2000){
	h1["m12_SR4_10GeV_step2"] -> Fill(mbbstep2,eventweight);
      }
      
      if(!isMC_ && !invertCutflow_){
	cout << "entered data trigger check" << endl;
	int triggerFired = analysis.triggerResult(hltPath_);
	//int triggerFiredL1 = analysis.triggerResult(l1Seed_);
	//if ( !(triggerFired && triggerFiredL1) ) continue;
	cout << triggerFired << endl;
	if ( !triggerFired ) continue;
      } //for MC, the trigger should be the last step of cutflow

      if (isMC_){
	sgweight = analysis.genWeight()/fabs(analysis.genWeight());
	h1["nentries"] -> Fill((sgweight+1.)/2.);
      }
      
      //step 3: trigger (only data)
      //step 3: gen weight (only MC)
      float mbbstep3 = (slimmedJets->at(0).p4() + slimmedJets->at(1).p4()).M();
      h1["m12_total_step3"] -> Fill(mbbstep3,eventweight);
      if (mbbstep3 > 200 && mbbstep3 < 500){
        h1["m12_SR1_1GeV_step3"] -> Fill(mbbstep3,eventweight);
      }
      if (mbbstep3 > 260 && mbbstep3 < 785){
        h1["m12_SR2_1GeV_step3"] -> Fill(mbbstep3,eventweight);
      }
      if (mbbstep3 > 390 && mbbstep3 < 1270){
	h1["m12_SR3_5GeV_step3"] -> Fill(mbbstep3,eventweight);
      }
      if (mbbstep3 > 500 && mbbstep3 < 2000){
	h1["m12_SR4_10GeV_step3"] -> Fill(mbbstep3,eventweight);
      }

      if (isMC_ && sgweight == 0){
	cout << "Neither positive nor negative weight detected for MC. This can not be right." << endl;
	return -1;
      }

      if (!invertCutflow_){
	++nsel[0]; //also for MC: equals no. of events then
	if(isMC_ && sgweight > 0) ++nweigh[0];//this equals the initial number of events
	else if(isMC_ && sgweight < 0) --nweigh[0];//for nlo, i.e. including the negative weights
      }
      
      std::vector<Jet*> selectedJets;

      for ( int j = 0 ; j < slimmedJets->size() ; ++j )
	{
	  if (slimmedJets->at(j).pileupJetIdFullId("loose") && slimmedJets->at(j).idTight() ) selectedJets.push_back(&slimmedJets->at(j));
	}

      double HT_before_any_cut = 0;
      calculateEventHT ( selectedJets, ptHT, etaHT, HT_before_any_cut );
      h1["HT_bef_cuts"] -> Fill(HT_before_any_cut);

      //at least 3/4 jets present
      if ( (int)selectedJets.size() < njetsmin_ ) continue;

      //step 4: 3 id-tight jets
      float mbbstep4 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step4"] -> Fill(mbbstep4,eventweight);
      if (mbbstep4 > 200 && mbbstep4 < 500){
        h1["m12_SR1_1GeV_step4"] -> Fill(mbbstep4,eventweight);
      }
      if (mbbstep4 > 260 && mbbstep4 < 785){
        h1["m12_SR2_1GeV_step4"] -> Fill(mbbstep4,eventweight);
      }
      if (mbbstep4 > 390 && mbbstep4 < 1270){
	h1["m12_SR3_5GeV_step4"] -> Fill(mbbstep4,eventweight);
      }
      if (mbbstep4 > 500 && mbbstep4 < 2000){
	h1["m12_SR4_10GeV_step4"] -> Fill(mbbstep4,eventweight);
      }

      ++nsel[1];
      if(isMC_ && sgweight > 0) ++nweigh[1];
      else if(isMC_ && sgweight < 0) --nweigh[1];

      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet* jet = selectedJets[j];
	  //Apply Jet Energy Corrections
	  float regressionfactor = 1.0;
	  if (useregression_){
	    regressionfactor = jet->bRegCorr();
	    correctJetpt(*jet,regressionfactor);
	  }
	  //Perform JER (jet energy resolution) matching and calculate corrections ("up"/"down" are +- 1 sigma uncertainties)
	  if (isMC_ && useJER_){
	    jet->jerInfo(*jerinfo,0.2);
	    if      ( jervar_ == "up"   ) correctJetpt( *jet, jet->jerCorrection("up") );
            else if ( jervar_ == "down" ) correctJetpt( *jet, jet->jerCorrection("down") );
            else    correctJetpt( *jet, jet->jerCorrection() );
	  }
	  //For JES up and down variation
	  if (isMC_ && jecsigma_ != 0 ) correctJetpt( *jet, 1.0 + jecsigma_*jet->jecUncert() );
	}

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

      //step 5: pT/eta
      float mbbstep5 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step5"] -> Fill(mbbstep5,eventweight);
      if (mbbstep5 > 200 && mbbstep5 < 500){
        h1["m12_SR1_1GeV_step5"] -> Fill(mbbstep5,eventweight);
      }
      if (mbbstep5 > 260 && mbbstep5 < 785){
        h1["m12_SR2_1GeV_step5"] -> Fill(mbbstep5,eventweight);
      }
      if (mbbstep5 > 390 && mbbstep5 < 1270){
	h1["m12_SR3_5GeV_step5"] -> Fill(mbbstep5,eventweight);
      }
      if (mbbstep5 > 500 && mbbstep5 < 2000){
	h1["m12_SR4_10GeV_step5"] -> Fill(mbbstep5,eventweight);
      }

      ++nsel[2];
      if(isMC_ && sgweight > 0) ++nweigh[2];
      else if(isMC_ && sgweight < 0) --nweigh[2];
      
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

      double deltaetavalue = selectedJets[0]->eta() - selectedJets[1]->eta();
      h1["deltaeta12"] -> Fill(deltaetavalue,eventweight);

      //step 6: delta R
      float mbbstep6 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step6"] -> Fill(mbbstep6,eventweight);
      if (mbbstep6 > 200 && mbbstep6 < 500){
        h1["m12_SR1_1GeV_step6"] -> Fill(mbbstep6,eventweight);
      }
      if (mbbstep6 > 260 && mbbstep6 < 785){
        h1["m12_SR2_1GeV_step6"] -> Fill(mbbstep6,eventweight);
      }
      if (mbbstep6 > 390 && mbbstep6 < 1270){
	h1["m12_SR3_5GeV_step6"] -> Fill(mbbstep6,eventweight);
      }
      if (mbbstep6 > 500 && mbbstep6 < 2000){
	h1["m12_SR4_10GeV_step6"] -> Fill(mbbstep6,eventweight);
      }

      ++nsel[3];
      if(isMC_ && sgweight > 0) ++nweigh[3];
      else if(isMC_ && sgweight < 0) --nweigh[3];
      
      if ( fabs(selectedJets[0]->eta() - selectedJets[1]->eta()) > detamax_ ) continue;

      //step 7: delta eta
      float mbbstep7 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step7"] -> Fill(mbbstep7,eventweight);
      if (mbbstep7 > 200 && mbbstep7 < 500){
        h1["m12_SR1_1GeV_step7"] -> Fill(mbbstep7,eventweight);
      }
      if (mbbstep7 > 260 && mbbstep7 < 785){
        h1["m12_SR2_1GeV_step7"] -> Fill(mbbstep7,eventweight);
      }
      if (mbbstep7 > 390 && mbbstep7 < 1270){
	h1["m12_SR3_5GeV_step7"] -> Fill(mbbstep7,eventweight);
      }
      if (mbbstep7 > 500 && mbbstep7 < 2000){
	h1["m12_SR4_10GeV_step7"] -> Fill(mbbstep7,eventweight);
      }

      ++nsel[4];
      if(isMC_ && sgweight > 0) ++nweigh[4];
      else if(isMC_ && sgweight < 0) --nweigh[4];
      
      // Fill histograms of kinematic passed events
      for ( int j = 0 ; j < (int)selectedJets.size() ; ++j )
	{
	  if ( selectedJets[j]->pt() < 20. ) continue;
	  ++njets;
	}

      h1["n"] -> Fill(selectedJets.size());
      h1["n_ptmin20"] -> Fill(njets);

      double HT_AftKinCuts_BefBtag = 0;
      calculateEventHT ( selectedJets, ptHT, etaHT, HT_AftKinCuts_BefBtag );
      h1["HT"] -> Fill(HT_AftKinCuts_BefBtag);

      //b tagging
      float storedisc = -1;
      float jet_offl_sf_cent = 1.0;
      float jet_offl_sf_up = 1.0;
      float jet_offl_sf_down = 1.0;
      float jet_onl_sf_cent = 1.0;
      float jet_onl_sf_up = 1.0;
      float jet_onl_sf_down = 1.0;

      //check for 4th b jet; selectedJets ordered by pt and only checked for leading 3/4
      //--> only [3] needs to be tested
      //in 3b cat: veto 4th but only exclude those events which are caught in 4b cat in order not to lose stat
      if (regions == "3jveto" && selectedJets.size() > 3){
	Jet *j4 = selectedJets[3];
	float btag4 = j4->btag("btag_dfb") + j4->btag("btag_dfbb") + j4->btag("btag_dflepb");
	if (btag4 > btagwp_) goodEvent = false;
      }
      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet * jet = selectedJets[j];
	  h1[Form("pt_%i",j)]   -> Fill(jet->pt());
	  h1[Form("eta_%i",j)]  -> Fill(jet->eta());
	  h1[Form("phi_%i",j)]  -> Fill(jet->phi());
	  h1[Form("btag_%i",j)] -> Fill(jet->btag("btag_csvivf"));
	  h1[Form("deepcsvbtag_%i",j)] -> Fill(jet->btag("btag_deepb")+jet->btag("btag_deepbb"));
	  h1[Form("deepflavourbtag_%i",j)] -> Fill(jet->btag("btag_dfb") + jet->btag("btag_dfbb") + jet->btag("btag_dflepb"));
	  h1["m12"] -> Fill((selectedJets[0]->p4() + selectedJets[1]->p4()).M());
	  h2[Form("pt_eta_%i",j)] -> Fill(jet->pt(),jet->eta());
	  for (unsigned int f = 0; f < flavors.size(); f++){
	    if (jet->extendedFlavour() == (flavors[f]).c_str()) {
	      h1[Form("pt_%i_%s",j,(flavors[f]).c_str())] -> Fill(jet->pt());
	      h1[Form("eta_%i_%s",j,(flavors[f]).c_str())] -> Fill(jet->eta());
	      h1[Form("phi_%i_%s",j,(flavors[f]).c_str())] -> Fill(jet->phi());
	      h1[Form("deepflavourbtag_%i_%s",j,(flavors[f]).c_str())] -> Fill(jet->btag("btag_dfb") + jet->btag("btag_dfbb") + jet->btag("btag_dflepb"));
	      h2[Form("pt_eta_%i_%s",j,(flavors[f]).c_str())] -> Fill(jet->pt(),jet->eta());
	    }
	  }

	  float btagdisc;

	  if (btagalgo == "csv") btagdisc = jet->btag("btag_csvivf");
	  else if (btagalgo == "deep_csv") btagdisc = jet->btag("btag_deepb") + jet->btag("btag_deepbb");
	  else if (btagalgo == "deepflavour") btagdisc = jet->btag("btag_dfb") + jet->btag("btag_dfbb") + jet->btag("btag_dflepb");
	  else return -1;

	  if (!usebtagweights_){
	    if ( j < 2 && btagdisc < btagwp_ ) goodEvent = false;// 0/1: 1st/2nd jet: always to be b tagged
	    if (regions == "3j"){
	      if (validationregion_ && j == 2){//VR: third jet between nb and b --> should not test SR vs CR
		if (btagdisc < nonbtagwp_ || btagdisc > btagwp_) goodEvent = false;
	      }
	      else{//not validation --> normal SR/CR
		//cout << "checking SR/CR" << endl;
		if (! signalregion_){//CR 3j: bbnb
		  if (j == 2 && btagdisc > nonbtagwp_) goodEvent = false;
		}
		else{//SR 3j: bbb
		  if (j == 2 && btagdisc < btagwp_) goodEvent = false;
		}
	      }
	    }//3j
	    else if (regions == "4j3"){
	      if (! signalregion_){//CR 4j3: bbnbb
		if ( (j == 2 && btagdisc > nonbtagwp_) || (j == 3 && btagdisc < btagwp_)) goodEvent = false;
	      }
	      else{//SR 4j3 bbbb
		if ( j >= 2 && btagdisc < btagwp_ ) goodEvent = false;
	      }
	    }//4j3
	    else if (regions == "4j4"){
	      if (! signalregion_){//CR 4j4: bbbnb
		if ( (j == 3 && btagdisc > nonbtagwp_) || (j == 2 && btagdisc < btagwp_)) goodEvent = false;
	      }
	      else{//SR 4j4: bbbb
		if ( j >= 2 && btagdisc < btagwp_ ) goodEvent = false;
	      }
	    }//4j4
	    else if (regions == "3jor"){
	      if (! signalregion_){//CR 3jor: bbnbnb
		if ( j >= 2 && btagdisc > nonbtagwp_ ) goodEvent = false;
	      }
	      else{//SR 3jor: bbbnb || bbnbb (3rd or 4th jet may be third b-jet)
		if (j == 2) storedisc = btagdisc;
 		if (j == 2 && (btagdisc > nonbtagwp_ && btagdisc < btagwp_) ) goodEvent = false;//if larger than veto and smaller than btag: bad anyhow (neither nb nor b)
		if (j == 3 && (storedisc >= jetsbtagmin_[2] && btagdisc > nonbtagwp_) ) goodEvent = false;//if third b -> fourth must be nb
		if (j == 3 && (storedisc <= nonbtagwp_ && btagdisc < btagwp_) ) goodEvent= false;//if third nb, fourth must be b
	      }
	    }//3jor
	    else if (regions == "4jor"){
	      if (!signalregion_){//CR 4jor: bbbnb || bbnbb (3rd or 4th jet may be reversed)
		if (j == 2) storedisc = btagdisc;
		if (j == 2 && (btagdisc > nonbtagwp_ && btagdisc < btagwp_) ) goodEvent = false;//if larger than veto and smaller than btag: bad anyhow (neither nb nor b)
		if (j == 3 && (storedisc >= jetsbtagmin_[2] && btagdisc > nonbtagwp_) ) goodEvent = false;//if third b -> fourth must be nb
		if (j == 3 && (storedisc <= nonbtagwp_ && btagdisc < btagwp_) ) goodEvent= false;//if third nb, fourth must be b
	      }
	      else{//SR 4jor:bbbb
		if ( j >= 2 && btagdisc < btagwp_ ) goodEvent = false;	      
	      }
	    }//4jor
	    else if (regions == "4jnn"){
	      if (! signalregion_){//CR 4jnn: bbnbnb
		if ( j >= 2 && btagdisc > nonbtagwp_ ) goodEvent = false;
	      }//CR 4jnn
	      else{//SR 4jnn: bbbb
		if ( j >= 2 && btagdisc < btagwp_ ) goodEvent = false;
	      }//SR 4jnn
	    }//4jnn
	    if ( border_other_wp > 0 && other_wp > 0 ){//set a different wp for leading two jets (e.g. tight instead of medium)
	      if (j < 2){//leading two jets
		if ( (jet->pt() > border_other_wp) && (btagdisc < other_wp) ) goodEvent = false;
	      }
	    }//other btag wp for leading two jets
	  }//if not usebtagweights
	  else{//if usebtagweights
	    if (!(regions == "3j" || regions == "4j3")){
	      cout << "Use of b tag weights only implemented for regions '3j' and '4j3' so far. Please use either of them or implement the use for the region you want to use. Aborting." << endl;
	      break;
	    }
	    else{//3j or 4j3
	      if (!signalregion_){//CR
		if (j == 2 && btagdisc > nonbtagwp_ ) goodEvent = false;//3rd jet must not be b tagged + no nb weight
		if (j != 2) addBtagWeight(jet, eventweight);//1st/2nd and, if it is there, 4th jet weighted (would be b tagged in cut based approach)
	      }//CR
	      else{//SR
		addBtagWeight(jet, eventweight);
	      }//SR
	    }//3j or 4j3
	  }//end: if usebtagweights
	}//end of loop over jets for b tagging
      
      if ( ! goodEvent ) continue;

      //step 8: b tagging
      float mbbstep8 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step8"] -> Fill(mbbstep8,eventweight);
      if (mbbstep8 > 200 && mbbstep8 < 500){
        h1["m12_SR1_1GeV_step8"] -> Fill(mbbstep8,eventweight);
      }
      if (mbbstep8 > 260 && mbbstep8 < 785){
        h1["m12_SR2_1GeV_step8"] -> Fill(mbbstep8,eventweight);
      }
      if (mbbstep8 > 390 && mbbstep8 < 1270){
	h1["m12_SR3_5GeV_step8"] -> Fill(mbbstep8,eventweight);
      }
      if (mbbstep8 > 500 && mbbstep8 < 2000){
	h1["m12_SR4_10GeV_step8"] -> Fill(mbbstep8,eventweight);
      }

      ++nsel[5];
      if(isMC_ && sgweight > 0) ++nweigh[5];
      else if(isMC_ && sgweight < 0) --nweigh[5];

      // Is matched?
      if (!isMC_) analysis.match<Jet,TriggerObject>("Jets",triggerObjects_,0.5);
      bool matched[12] = {true,true,true,true,true,true,true,true,true,true,true,true};//for both leading jets: five objects to be tested

      //last step of cutflow for MC: trigger
      if((isMC_ || invertCutflow_) && !usebtagweights_){
	int triggerFired = analysis.triggerResult(hltPath_);
	if ( !triggerFired ) continue;
	//++nsel[7];
      }

      //step 9 (only MC): trigger
      float mbbstep9 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step9"] -> Fill(mbbstep9,eventweight);
      if (mbbstep9 > 200 && mbbstep9 < 500){
        h1["m12_SR1_1GeV_step9"] -> Fill(mbbstep9,eventweight);
      }
      if (mbbstep9 > 260 && mbbstep9 < 785){
        h1["m12_SR2_1GeV_step9"] -> Fill(mbbstep9,eventweight);
      }
      if (mbbstep9 > 390 && mbbstep9 < 1270){
	h1["m12_SR3_5GeV_step9"] -> Fill(mbbstep9,eventweight);
      }
      if (mbbstep9 > 500 && mbbstep9 < 2000){
	h1["m12_SR4_10GeV_step9"] -> Fill(mbbstep9,eventweight);
      }

      if (!usebtagweights_){//for data: fine; for MC: not to be used with b tag weights (not using trigger)
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
      }

      if ( ! goodEvent ) continue;

      //step 10: trigger matching
      float mbbstep10 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step10"] -> Fill(mbbstep10,eventweight);
      if (mbbstep10 > 200 && mbbstep10 < 500){
        h1["m12_SR1_1GeV_step10"] -> Fill(mbbstep10,eventweight);
      }
      if (mbbstep10 > 260 && mbbstep10 < 785){
        h1["m12_SR2_1GeV_step10"] -> Fill(mbbstep10,eventweight);
      }
      if (mbbstep10 > 390 && mbbstep10 < 1270){
	h1["m12_SR3_5GeV_step10"] -> Fill(mbbstep10,eventweight);
      }
      if (mbbstep10 > 500 && mbbstep10 < 2000){
	h1["m12_SR4_10GeV_step10"] -> Fill(mbbstep10,eventweight);
      }

      ++nsel[6];//for MC and inverted cutflow: matching and trigger in one common step
      if(isMC_ && sgweight > 0) ++nweigh[6];
      else if(isMC_ && sgweight < 0) --nweigh[6];

      
      // MC: b tag scale factors, online and offline
      if (isMC_){
	if (usebtagsf_ && !usebtagweights_){//for b tag weights: offline b tag sf included, online cannot be included (no trigger information and bias due to [not] cutting)
	  //offline b tag sf
	  for ( int j = 0; j < njetsmin_; ++j ) {
	    Jet * jet = selectedJets[j];
	    if (j!=2 || signalregion_){//sf not known for reverse b tag
	      float jet_btag_sf = jet -> btagSF(bsf_reader);
	      eventweight *= jet_btag_sf;
	      jet_offl_sf_cent *= jet_btag_sf;
	      float jet_btag_sf_up = jet -> btagSFup(bsf_reader,1);
	      jet_offl_sf_up *= jet_btag_sf_up;
	      float jet_btag_sf_down = jet -> btagSFdown(bsf_reader,1);
	      jet_offl_sf_down *= jet_btag_sf_down;
	      float pt = jet->pt();
	      th2_pT_offlbtagsf -> Fill(pt,jet_btag_sf);
	    }
	  }
	  //step 11 (only MC): offline b tag sf
	  float mbbstep11 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
	  h1["m12_total_step11"] -> Fill(mbbstep11,eventweight);
	  if (mbbstep11 > 200 && mbbstep11 < 500){
	    h1["m12_SR1_1GeV_step11"] -> Fill(mbbstep11,eventweight);
	  }
	  if (mbbstep11 > 260 && mbbstep11 < 785){
	    h1["m12_SR2_1GeV_step11"] -> Fill(mbbstep11,eventweight);
	  }
	  if (mbbstep11 > 390 && mbbstep11 < 1270){
	    h1["m12_SR3_5GeV_step11"] -> Fill(mbbstep11,eventweight);
	  }
	  if (mbbstep11 > 500 && mbbstep11 < 2000){
	    h1["m12_SR4_10GeV_step11"] -> Fill(mbbstep11,eventweight);
	  }

	  //online b tag sf
	  //loop over jets
	  for (int j = 0; j < njetsmin_; ++j) {
	    Jet * jet = selectedJets[j];
	    if (btagalgo == "deepflavour" && (j == 0 || j == 1)){
	      float pt = jet->pt();
	      float onl_sf = 0.852 - (pt * 0.0000616);
	      float onl_sf_up = 0.860 - (pt * 0.0000065);
	      jet_onl_sf_up *= onl_sf_up;
	      float onl_sf_down = 0.845 - (pt * 0.0001167);
	      jet_onl_sf_down *= onl_sf_down;
	      h1["onl_btag_sf"] -> Fill(onl_sf);
	      jet_onl_sf_cent *= onl_sf;
	      eventweight *= onl_sf;
	      th2_pT_onlbtagsf -> Fill(pt,onl_sf);
	    }
	  }

	  //step 12 (only MC): online b tag sf
	  float mbbstep12 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
	  h1["m12_total_step12"] -> Fill(mbbstep12,eventweight);
	  if (mbbstep12 > 200 && mbbstep12 < 500){
	    h1["m12_SR1_1GeV_step12"] -> Fill(mbbstep12,eventweight);
	  }
	  if (mbbstep12 > 260 && mbbstep12 < 785){
	    h1["m12_SR2_1GeV_step12"] -> Fill(mbbstep12,eventweight);
	  }
	  if (mbbstep12 > 390 && mbbstep12 < 1270){
	    h1["m12_SR3_5GeV_step12"] -> Fill(mbbstep12,eventweight);
	  }
	  if (mbbstep12 > 500 && mbbstep12 < 2000){
	    h1["m12_SR4_10GeV_step12"] -> Fill(mbbstep12,eventweight);
	  }
	}
      }

      double HT_after_bTag = 0;
      calculateEventHT ( selectedJets, ptHT, etaHT, HT_after_bTag );
      h1["HT_after_bTag"] -> Fill(HT_after_bTag);
      
      //FSR recovery
      
      for ( size_t s = njetsmin_; s < selectedJets.size() ; ++s )  //soft jet loop - from 4th/5th jet (depending on region)
	{
	  Jet & softjet = *selectedJets[s];
	  //Cut on DeltaR softjet - b jet
	  float dRminsoft_bj = std::min({softjet.deltaR(*selectedJets[0]),softjet.deltaR(*selectedJets[1]),softjet.deltaR(*selectedJets[2])});
	  if (njetsmin_ == 4) dRminsoft_bj = std::min({softjet.deltaR(*selectedJets[0]),softjet.deltaR(*selectedJets[1]),softjet.deltaR(*selectedJets[2]),softjet.deltaR(*selectedJets[3])});
	  if ( softjet.pt() < 20.0 ) continue;
	  if ( dRminsoft_bj > 0.8 )  continue;
	  for ( int j = 0; j < njetsmin_; ++j ) //dijet loop
	    {
	      Jet & bjet = *selectedJets[j];
	      if ( dRminsoft_bj != softjet.deltaR(bjet) ) continue;
	      bjet.p4( bjet.p4() + softjet.p4() );
	      //Remove bjet and add corrected bjet
	      //No need to remove soft jet: Iterator will proceed. So if soft jet erased plus iterator proceeds: one soft jet skipped
	      selectedJets.erase(selectedJets.begin()+j);
	      selectedJets.insert(selectedJets.begin()+j, &bjet );
	      h1["pt_softjet"] -> Fill(softjet.pt());
	      h1["dR_jsoftjet"] -> Fill(softjet.deltaR(bjet));
	      h1["rank_softjet"] -> Fill(s);
	    }
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
	    if ( muon->pt() < muonsptmin_[m] || fabs(muon->eta()) > muonsetamax_[m] ) continue;
	    
	    float dR_muj0 = selectedJets[0]->deltaR(*muon);
	    float dR_muj1 = selectedJets[1]->deltaR(*muon);
	    
	    if ( dR_muj0 < drmax_ || dR_muj1 < drmax_ ) //at least 1 muon in a jet originating from the Higgs
	      {
		muonpresent  = true;
		MuonsinJet.push_back(muon);
		break;
	      }
	  } //end: loop over muons
	if ( muonpresent ) continue;
	
	//step 13: muon veto
	float mbbstep13 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
	h1["m12_total_step13"] -> Fill(mbbstep13,eventweight);
	if (mbbstep13 > 200 && mbbstep13 < 500){
	  h1["m12_SR1_1GeV_step13"] -> Fill(mbbstep13,eventweight);
	}
	if (mbbstep13 > 260 && mbbstep13 < 785){
	  h1["m12_SR2_1GeV_step13"] -> Fill(mbbstep13,eventweight);
	}
	if (mbbstep13 > 390 && mbbstep13 < 1270){
	  h1["m12_SR3_5GeV_step13"] -> Fill(mbbstep13,eventweight);
	}
	if (mbbstep13 > 500 && mbbstep13 < 2000){
	  h1["m12_SR4_10GeV_step13"] -> Fill(mbbstep13,eventweight);
	}

	nsel[7]++;
	if(isMC_ && sgweight > 0) ++nweigh[7];
	else if(isMC_ && sgweight < 0) --nweigh[7];
      } //end: muon veto

      // Fill histograms of passed bbnb btagging selection
      for ( int j = 0 ; j < (int)selectedJets.size() ; ++j )
	{
	  if ( selectedJets[j]->pt() < 20. ) continue;
	  ++njets_csv;
	}

      h1["n_csv"] -> Fill(selectedJets.size());
      h1["n_ptmin20_csv"] -> Fill(njets_csv);

      double HT_csv = 0;
      calculateEventHT ( selectedJets, ptHT, etaHT, HT_csv );
      h1["HT_csv"] -> Fill(HT_csv);


      // Add weight for trigger turn-on (MC only)
      // To be done for first TWO jets (both are triggered)

      double trigger_weight_up = 1;
      double trigger_weight_down = 1;
      double trigger_weight = 1;

      if ((isMC_ && useTO_) && !usebtagweights_){//no trigger if using weights
	for (int j = 0; j < 2; j++){//first and second jet
	  Jet* jet = selectedJets[j];
	  double jetpt = jet->pt();
	  double jetabseta = fabs(jet->eta());
	  double triggersf = 1.0;
	  double trigger_sf_down = 1.0;
	  double trigger_sf_up = 1.0;
	  if (jetabseta >= 0.0 && jetabseta <= 1.0){//central
	    triggersf = 0.999 * erf( 0.036 * ( jetpt - 89.84 ) );
	    trigger_sf_up = 1.004 * erf( 0.038 * ( jetpt - 90.95 ) );
	    trigger_sf_down = 0.994 * erf( 0.034 * ( jetpt - 88.73) );
	  }
	  else if (jetabseta > 1.0 && jetabseta <= 1.4){//overlap
	    triggersf = 0.998 * erf( 0.035 * ( jetpt - 90.96 ) );
	    trigger_sf_up = 1.006 * erf( 0.038 * ( jetpt - 92.62 ) );
	    trigger_sf_down = 0.990 * erf( 0.032 * ( jetpt - 89.30 ) );
	  }
	  else if (jetabseta > 1.4 && jetabseta <= 2.2){//endcaps
	    triggersf = 1.002 * erf( 0.038 * ( jetpt - 93.74 ) );
	    trigger_sf_up = 1.008 * erf( 0.040 * ( jetpt - 94.65 ) );
	    trigger_sf_down = 0.996 * erf( 0.036 * ( jetpt - 92.83 ) );
	  }
	  else cout << "Trigger sf: eta out of range" << endl;
	  trigger_weight_up *= trigger_sf_up;
	  trigger_weight_down *= trigger_sf_down;
	  trigger_weight *= triggersf;
	  eventweight *= triggersf;
	}
      }

      //step 14 (only MC): trigger turn-on sf
      float mbbstep14 = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();
      h1["m12_total_step14"] -> Fill(mbbstep14,eventweight);
      if (mbbstep14 > 200 && mbbstep14 < 500){
        h1["m12_SR1_1GeV_step14"] -> Fill(mbbstep14,eventweight);
      }
      if (mbbstep14 > 260 && mbbstep14 < 785){
        h1["m12_SR2_1GeV_step14"] -> Fill(mbbstep14,eventweight);
      }
      if (mbbstep14 > 390 && mbbstep14 < 1270){
	h1["m12_SR3_5GeV_step14"] -> Fill(mbbstep14,eventweight);
      }
      if (mbbstep14 > 500 && mbbstep14 < 2000){
	h1["m12_SR4_10GeV_step14"] -> Fill(mbbstep14,eventweight);
      }

      for ( int j = 0; j < njetsmin_; ++j )
	{
	  Jet* jet = selectedJets[j];
	  h1[Form("pt_%i_csv",j)]   -> Fill(jet->pt(),eventweight);
	  h1[Form("eta_%i_csv",j)]  -> Fill(jet->eta(),eventweight);
	  h1[Form("phi_%i_csv",j)]  -> Fill(jet->phi(),eventweight);
	  h1[Form("btag_%i_csv",j)] -> Fill(jet->btag("btag_csvivf"),eventweight);
	  h1[Form("deepcsvbtag_%i_csv",j)] -> Fill(jet->btag("btag_deepb")+jet->btag("btag_deepbb"),eventweight);
	  h1[Form("deepflavourbtag_%i_csv",j)] -> Fill(jet->btag("btag_dfb")+jet->btag("btag_dfbb")+jet->btag("btag_dflepb"),eventweight);
	  h2[Form("pt_eta_%i_csv",j)] -> Fill(jet->pt(),jet->eta(),eventweight);
	  for (unsigned int f = 0; f < flavors.size(); f++){
	    if (jet->extendedFlavour() == (flavors[f]).c_str()) {
	      h1[Form("pt_%i_%s_csv",j,(flavors[f]).c_str())] -> Fill(jet->pt(),eventweight);
	      h1[Form("eta_%i_%s_csv",j,(flavors[f]).c_str())] -> Fill(jet->eta(),eventweight);
	      h1[Form("phi_%i_%s_csv",j,(flavors[f]).c_str())] -> Fill(jet->phi(),eventweight);
	      h1[Form("deepflavourbtag_%i_%s_csv",j,(flavors[f]).c_str())] -> Fill(jet->btag("btag_dfb") + jet->btag("btag_dfbb") + jet->btag("btag_dflepb"),eventweight);
	      h2[Form("pt_eta_%i_%s_csv",j,(flavors[f]).c_str())] -> Fill(jet->pt(),jet->eta(),eventweight);
	    }
	  }
	}

      mbb_sel = (selectedJets[0]->p4() + selectedJets[1]->p4()).M();

      if (m12min_ > 0 && mbb_sel < m12min_) goodEvent = false;
      
      if (massdepptcut_ > 0){
	float fraccut = massdepptcut_;
	if ( (selectedJets[0]->pt() < fraccut*mbb) || (selectedJets[1]->pt() < fraccut*mbb) ) goodEvent = false;
      }

      if (!goodEvent) continue;
      nsel[8]++;

      if(isMC_ && sgweight > 0) ++nweigh[8];
      else if(isMC_ && sgweight < 0) --nweigh[8];

      double HT_aac = 0;
      calculateEventHT ( selectedJets, ptHT, etaHT, HT_aac );
      h1["HT_aac"] -> Fill(HT_aac);
      double deltaeta12_aac = fabs(selectedJets[0]->eta() - selectedJets[1]->eta());
      h1["deltaeta12_aac"] -> Fill(deltaeta12_aac,eventweight);
      double deltaphi12_aac = fabs(selectedJets[0]->phi() - selectedJets[1]->phi());
      h1["deltaphi12_aac"] -> Fill(deltaphi12_aac,eventweight);

      for ( int j = 0; j < njetsmin_; ++j )//get histograms for most important quantities after all cuts (including m12 cut)
        {
          Jet* jet = selectedJets[j];
          h1[Form("pt_%i_aac",j)]   -> Fill(jet->pt(),eventweight);
          h1[Form("eta_%i_aac",j)]  -> Fill(jet->eta(),eventweight);
	  
	  if (!jetsptmax_.empty() && jet->pt() < jetsptmax_[j])
	  h1[Form("eta_%i_aac_pTbelowMax",j)] -> Fill(jet->eta(),eventweight);
	  
          h1[Form("deepflavourbtag_%i_aac",j)] -> Fill(jet->btag("btag_dfb")+jet->btag("btag_dfbb")+jet->btag("btag_dflepb"),eventweight);

	  h2[Form("pt_eta_%i_aac",j)] -> Fill(jet->pt(),jet->eta(),eventweight);

	  for (unsigned int f = 0; f < flavors.size(); f++){
	    if (jet->extendedFlavour() == (flavors[f]).c_str()) {
	      h1[Form("pt_%i_%s_aac",j,(flavors[f]).c_str())] -> Fill(jet->pt(),eventweight);
	      h1[Form("eta_%i_%s_aac",j,(flavors[f]).c_str())] -> Fill(jet->eta(),eventweight);
	      h1[Form("phi_%i_%s_aac",j,(flavors[f]).c_str())] -> Fill(jet->phi(),eventweight);
	      h1[Form("deepflavourbtag_%i_%s_aac",j,(flavors[f]).c_str())] -> Fill(jet->btag("btag_dfb") + jet->btag("btag_dfbb") + jet->btag("btag_dflepb"),eventweight);
	      h2[Form("pt_eta_%i_%s_aac",j,(flavors[f]).c_str())] -> Fill(jet->pt(),jet->eta(),eventweight);
	    }
	  }
	}

      if ( ! isMC_ && ! signalregion_ ){
	applyPrescale ( analysis.run(), R->Rndm(), prescaleEra, nsubsamples, window  );
      }

      //Initialise tree with different windows
      for ( int i=0; i< nsubsamples; i++)
        {
          if (i != window) mbbw[i] = -1; // set other mass windows to -1 ( fixed nentries in Tree )
          else mbbw[i] = mbb_sel;
	}

      if (mbb_sel > 200 && mbb_sel < 500) n_SR[1]++;
      if (mbb_sel > 260 && mbb_sel < 785) n_SR[2]++;
      if (mbb_sel > 390 && mbb_sel < 1270) n_SR[3]++;
      if (mbb_sel > 500 && mbb_sel < 2000) n_SR[4]++;
      
      //if ( !signalregion_ || isMC_)//blinding
      //{ 
      h1["m12_aac"] -> Fill(mbb_sel,eventweight); //unprescaled
      if (mbb_sel > 200 && mbb_sel < 500){
	h1["m12_SR1_1GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR1_2GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR1_5GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR1_10GeV"] -> Fill(mbb_sel,eventweight);
      }
      if (mbb_sel > 260 && mbb_sel < 785){
	h1["m12_SR2_1GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR2_3GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR2_5GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR2_15GeV"] -> Fill(mbb_sel,eventweight);
      }
      if (mbb_sel > 390 && mbb_sel < 1270){
	h1["m12_SR3_5GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR3_20GeV"] -> Fill(mbb_sel,eventweight);
      }
      if (mbb_sel > 500 && mbb_sel < 2000){
	h1["m12_SR4_5GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR4_10GeV"] -> Fill(mbb_sel,eventweight);
	h1["m12_SR4_25GeV"] -> Fill(mbb_sel,eventweight);
      }
      mbb = mbb_sel;
      weight = eventweight;
      tree -> Fill();
      
      if     ( window == 0 ) tree0 -> Fill();
      else if( window == 1 ) tree1 -> Fill();
      else if( window == 2 ) tree2 -> Fill();
      else if( window == 3 ) tree3 -> Fill();
      else if( window == 4 ) tree4 -> Fill();
      else if( window == 5 ) tree5 -> Fill();
      else if( window == 6 ) tree6 -> Fill();
      
      if ( !isMC_ && !signalregion_) h1[Form("m12_sel_%i",window)] -> Fill(mbbw[window], eventweight);
      //}
      if (isMC_){
	ptH = (selectedJets[0]->p4() + selectedJets[1]->p4()).Pt();
	h1["pt_HiggsCand"] -> Fill(ptH,eventweight);

	//PU weight
	double eventweight_PU_up ;
	double eventweight_PU_down ;
	if ( puweight != 0 && eventweight != 0 )
	  {
	    eventweight_PU_up   = eventweight / puweight * puup   ;
	    eventweight_PU_down = eventweight / puweight * pudown ;
	  }
	else
	  {
	    eventweight_PU_up   = 0;
	    eventweight_PU_down = 0;
	  }
	//Offbtag
	double eventweight_offbtag_up   = eventweight * jet_offl_sf_up   / jet_offl_sf_cent;
	double eventweight_offbtag_down = eventweight * jet_offl_sf_down / jet_offl_sf_cent;
	//Onlbtag
	double eventweight_onlbtag_up   = eventweight * jet_onl_sf_up   / jet_onl_sf_cent;
	double eventweight_onlbtag_down = eventweight * jet_onl_sf_down / jet_onl_sf_cent;
	//jet trig eff weight
	double eventweight_jet_trigeff_up   = eventweight * trigger_weight_up   / trigger_weight;
	double eventweight_jet_trigeff_down = eventweight * trigger_weight_down / trigger_weight;
	// ONLINE B TAG AND TRIGGER SF BOTH RELATED TO CURRENTLY NOT USED TRIGGER
	//PU
	h1["m12_aac_PU_up"]   -> Fill(mbb_sel, eventweight_PU_up   );
	h1["m12_aac_PU_down"] -> Fill(mbb_sel, eventweight_PU_down );
	//Offline btag
	h1["m12_aac_SFbtag_up"]   -> Fill(mbb_sel, eventweight_offbtag_up  );
	h1["m12_aac_SFbtag_down"] -> Fill(mbb_sel, eventweight_offbtag_down);
	//Online btag
	h1["m12_aac_onlSFbtag_up"]   -> Fill(mbb_sel, eventweight_onlbtag_up  );
	h1["m12_aac_onlSFbtag_down"] -> Fill(mbb_sel, eventweight_onlbtag_down);
	//Jet trig eff
	h1["m12_aac_jet_trigeff_up"]   -> Fill(mbb_sel, eventweight_jet_trigeff_up   );
	h1["m12_aac_jet_trigeff_down"] -> Fill(mbb_sel, eventweight_jet_trigeff_down );

	//subrange histograms
	if (mbb_sel > 200 && mbb_sel < 500){
	  h1["m12_SR1_1GeV_PU_up"] -> Fill(mbb_sel,eventweight_PU_up);
	  h1["m12_SR1_1GeV_PU_down"] -> Fill(mbb_sel,eventweight_PU_down);
	  h1["m12_SR1_1GeV_SFbtag_up"] -> Fill(mbb_sel,eventweight_offbtag_up);
	  h1["m12_SR1_1GeV_SFbtag_down"] -> Fill(mbb_sel,eventweight_offbtag_down);
	  h1["m12_SR1_1GeV_onlSFbtag_up"] -> Fill(mbb_sel,eventweight_onlbtag_up);
	  h1["m12_SR1_1GeV_onlSFbtag_down"] -> Fill(mbb_sel,eventweight_onlbtag_down);
	  h1["m12_SR1_1GeV_jet_trigeff_up"] -> Fill(mbb_sel,eventweight_jet_trigeff_up);
	  h1["m12_SR1_1GeV_jet_trigeff_down"] -> Fill(mbb_sel,eventweight_jet_trigeff_down);
	}
	if (mbb_sel > 260 && mbb_sel < 785){
	  h1["m12_SR2_1GeV_PU_up"] -> Fill(mbb_sel,eventweight_PU_up);
          h1["m12_SR2_1GeV_PU_down"] -> Fill(mbb_sel,eventweight_PU_down);
          h1["m12_SR2_1GeV_SFbtag_up"] -> Fill(mbb_sel,eventweight_offbtag_up);
          h1["m12_SR2_1GeV_SFbtag_down"] -> Fill(mbb_sel,eventweight_offbtag_down);
          h1["m12_SR2_1GeV_onlSFbtag_up"] -> Fill(mbb_sel,eventweight_onlbtag_up);
          h1["m12_SR2_1GeV_onlSFbtag_down"] -> Fill(mbb_sel,eventweight_onlbtag_down);
          h1["m12_SR2_1GeV_jet_trigeff_up"] -> Fill(mbb_sel,eventweight_jet_trigeff_up);
          h1["m12_SR2_1GeV_jet_trigeff_down"] -> Fill(mbb_sel,eventweight_jet_trigeff_down);
	}
	if (mbb_sel > 390 && mbb_sel < 1270){
	  h1["m12_SR3_5GeV_PU_up"] -> Fill(mbb_sel,eventweight_PU_up);
          h1["m12_SR3_5GeV_PU_down"] -> Fill(mbb_sel,eventweight_PU_down);
          h1["m12_SR3_5GeV_SFbtag_up"] -> Fill(mbb_sel,eventweight_offbtag_up);
          h1["m12_SR3_5GeV_SFbtag_down"] -> Fill(mbb_sel,eventweight_offbtag_down);
          h1["m12_SR3_5GeV_onlSFbtag_up"] -> Fill(mbb_sel,eventweight_onlbtag_up);
          h1["m12_SR3_5GeV_onlSFbtag_down"] -> Fill(mbb_sel,eventweight_onlbtag_down);
          h1["m12_SR3_5GeV_jet_trigeff_up"] -> Fill(mbb_sel,eventweight_jet_trigeff_up);
          h1["m12_SR3_5GeV_jet_trigeff_down"] -> Fill(mbb_sel,eventweight_jet_trigeff_down);
	}
	if (mbb_sel > 500 && mbb_sel < 2000){
	  h1["m12_SR4_10GeV_PU_up"] -> Fill(mbb_sel,eventweight_PU_up);
          h1["m12_SR4_10GeV_PU_down"] -> Fill(mbb_sel,eventweight_PU_down);
          h1["m12_SR4_10GeV_SFbtag_up"] -> Fill(mbb_sel,eventweight_offbtag_up);
          h1["m12_SR4_10GeV_SFbtag_down"] -> Fill(mbb_sel,eventweight_offbtag_down);
          h1["m12_SR4_10GeV_onlSFbtag_up"] -> Fill(mbb_sel,eventweight_onlbtag_up);
          h1["m12_SR4_10GeV_onlSFbtag_down"] -> Fill(mbb_sel,eventweight_onlbtag_down);
          h1["m12_SR4_10GeV_jet_trigeff_up"] -> Fill(mbb_sel,eventweight_jet_trigeff_up);
          h1["m12_SR4_10GeV_jet_trigeff_down"] -> Fill(mbb_sel,eventweight_jet_trigeff_down);
	}

	//Fill trees
	weight = eventweight_PU_up;
	m12_vars["m12_PU_up"]->Fill();
	weight = eventweight_PU_down;
	m12_vars["m12_PU_down"]->Fill();
	weight = eventweight_offbtag_up;
	m12_vars["m12_SFbtag_up"]->Fill();
	weight = eventweight_offbtag_down;
	m12_vars["m12_SFbtag_down"]->Fill();
	weight = eventweight_onlbtag_up;
	m12_vars["m12_onlSFbtag_up"]->Fill();
	weight = eventweight_onlbtag_down;
	m12_vars["m12_onlSFbtag_down"]->Fill();
	weight = eventweight_jet_trigeff_up;
	m12_vars["m12_jet_trigeff_up"]->Fill();
	weight = eventweight_jet_trigeff_down;
	m12_vars["m12_jet_trigeff_down"]->Fill();
	weight = eventweight;
	
	//JER
	Jet * j0 = selectedJets[0];
	Jet * j1 = selectedJets[1];
	Jet * j0_beforeVars = new Jet(j0->pt(), j0->eta(), j0->phi(), j0->e());
	Jet * j1_beforeVars = new Jet(j1->pt(), j1->eta(), j1->phi(), j1->e());
	Jet * j0_JER_up   = new Jet(j0->pt(), j0->eta(), j0->phi(), j0->e());
	Jet * j0_JER_down = new Jet(j0->pt(), j0->eta(), j0->phi(), j0->e());
	Jet * j1_JER_up   = new Jet(j1->pt(), j1->eta(), j1->phi(), j1->e());
	Jet * j1_JER_down = new Jet(j1->pt(), j1->eta(), j1->phi(), j1->e());

	for ( auto & var : vars )
	  {
	    correctJetpt( *j0 , j0->jerCorrection(var.c_str())/ j0->jerCorrection() );
	    correctJetpt( *j1 , j1->jerCorrection(var.c_str())/ j1->jerCorrection() );

	    h1[Form("m12_aac_JER_%s",var.c_str())] -> Fill( (j0->p4() + j1->p4()).M() , eventweight);
	    h1[Form("pt_0_JER_%s",var.c_str())] -> Fill( j0->pt() , eventweight);
	    h1[Form("pt_1_JER_%s",var.c_str())] -> Fill( j1->pt() , eventweight);	    

	    mbb = (j0->p4() + j1->p4()).M();
	    m12_vars[("m12_JER_"+var).c_str()]->Fill();

	    //restore pT before variation
	    if ( var =="up" )
	      {
		copyJetpt( *j0_JER_up, *j0);
		copyJetpt( *j1_JER_up, *j1);
	      }
	    if ( var =="down" )
	      {
		copyJetpt( *j0_JER_down, *j0);
		copyJetpt( *j1_JER_down, *j1);
	      }
	    copyJetpt( *j0, *j0_beforeVars);
	    copyJetpt( *j1, *j1_beforeVars);
	  }

	//JES
	std::vector<std::pair<string,int>> sigmas = { {"up",1}, {"down",-1} };
	for ( auto & var : sigmas)
	  {
	    correctJetpt( *j0, 1 + var.second*j0->jecUncert()  );
	    correctJetpt( *j1, 1 + var.second*j1->jecUncert()  );
	    
	    h1[Form("m12_aac_JES_%s",var.first.c_str())] -> Fill( (j0->p4() + j1->p4()).M() , eventweight);
	    h1[Form("pt_0_JES_%s",var.first.c_str())] -> Fill( j0->pt() , eventweight);
	    h1[Form("pt_1_JES_%s",var.first.c_str())] -> Fill( j1->pt() , eventweight);

	    mbb = (j0->p4() + j1->p4()).M();
	    m12_vars[("m12_JES_"+var.first).c_str()]->Fill();

	    copyJetpt( *j0, *j0_beforeVars);
	    copyJetpt( *j1, *j1_beforeVars);
	  }
	
	h1["j0_JER_diff"] -> Fill( j0_JER_up->pt()-j0_JER_down->pt() );
	h1["j1_JER_diff"] -> Fill( j1_JER_up->pt()-j1_JER_down->pt() );
	h1["m12_JER_diff"] -> Fill( (j0_JER_up->p4() + j1_JER_up->p4()).M() - (j0_JER_down->p4() + j1_JER_down->p4()).M() );
      }
    }//end: event loop

  h1["nentries_SR1"] -> SetBinContent(1,n_SR[1]);
  h1["nentries_SR2"] -> SetBinContent(1,n_SR[2]);
  h1["nentries_SR3"] -> SetBinContent(1,n_SR[3]);
  h1["nentries_SR4"] -> SetBinContent(1,n_SR[4]);

  h1["noofevents_h"] -> SetBinContent(1,noofeventsstart); //total number of events
  h1["noofevents_h"] -> SetBinContent(2,nsel[0]); //triggered
  h1["noofevents_h"] -> SetBinContent(3,nsel[1]); //3/4 jets (tight)
  h1["noofevents_h"] -> SetBinContent(4,nsel[2]); //kin
  h1["noofevents_h"] -> SetBinContent(5,nsel[3]); //dR
  h1["noofevents_h"] -> SetBinContent(6,nsel[4]); //deta
  h1["noofevents_h"] -> SetBinContent(7,nsel[5]); //btag
  h1["noofevents_h"] -> SetBinContent(8,nsel[6]); //final selection (perhaps trigger; matching)
  if(muonveto_) h1["noofevents_h"] -> SetBinContent(9,nsel[7]); //including muon veto
  if(massdepptcut_ > 0 || (border_other_wp > 0 && other_wp > 0)) h1["noofevents_h"] -> SetBinContent(10,nsel[8]); //mass dependent pt cut and/or other btag wp for leading two jets

  if(isMC_){//weighted number of events (important only for NLO) after each step of the cutflow
    h1["noofevents_w_nlo"] -> SetBinContent(1,noofeventsstart); //total number of events
    h1["noofevents_w_nlo"] -> SetBinContent(2,nweigh[0]); //triggered/weighted
    h1["noofevents_w_nlo"] -> SetBinContent(3,nweigh[1]); //3/4 jets (tight)
    h1["noofevents_w_nlo"] -> SetBinContent(4,nweigh[2]); //kin
    h1["noofevents_w_nlo"] -> SetBinContent(5,nweigh[3]); //dR
    h1["noofevents_w_nlo"] -> SetBinContent(6,nweigh[4]); //deta
    h1["noofevents_w_nlo"] -> SetBinContent(7,nweigh[5]); //btag
    h1["noofevents_w_nlo"] -> SetBinContent(8,nweigh[6]); //final selection (perhaps trigger; matching)
    if(muonveto_) h1["noofevents_w_nlo"] -> SetBinContent(9,nweigh[7]); //including muon veto
    if(massdepptcut_ > 0 || (border_other_wp > 0 && other_wp > 0) ) h1["noofevents_w_nlo"] -> SetBinContent(10,nweigh[8]); //mass dependent pt cut and/or other btag wp for leading two jets
  }

  for (auto & ih1 : h1)
    {
      ih1.second -> Write();
    }

  for ( auto & m12_var : m12_vars )
    {
      m12_var.second->Write();
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
  cuts[5] = "btagged (bbnb/bbnbb)";
  if (signalregion_) cuts[5] = "btagged (bbb/bbbb)";
  cuts[6] = "Matched to online j1;j2";
  if (invertCutflow_) cuts[6] = "Trigger and matching j1;j2";
  if(muonveto_) cuts[7] = "Muon veto";
  if(massdepptcut_ > 0 || (border_other_wp > 0 && other_wp > 0)) cuts[8] = "Mass dep. pT cut / other wp for j1;j2";
  if(massdepptcut_ < 0 && !(border_other_wp > 0 && other_wp > 0)) cuts[8] = "No mass dep. pT cut applied and no other btag wps used.";
  //if (isMC_ || invertCutflow_) cuts[7] = "Triggered";

  printf ("%-23s  %10s  %10s  %10s \n", std::string("Cut flow").c_str(), std::string("# events").c_str(), std::string("absolute").c_str(), std::string("relative").c_str() ); 
  txtoutputfile << "Cut flow " << "# events " << "absolute " << "relative" << endl;
  //if (!isMC_){
  if (!invertCutflow_){
    if(muonveto_) {
      for ( int i = 0; i < 9; ++i )
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
  }
  /*else if (isMC_){
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

void correctJetpt ( Jet& jet , const float& cor )
{
  TLorentzVector CorJet;
  CorJet.SetPtEtaPhiE(jet.pt()*cor, jet.eta(), jet.phi(), jet.e()*cor);
  jet.p4(CorJet);
}

void copyJetpt ( Jet& jet , Jet& newjet )
{
  TLorentzVector appo ;
  appo.SetPtEtaPhiE( newjet.pt() , newjet.eta(), newjet.phi(), newjet.e());
  jet.p4( appo );
}

void calculateEventHT ( const std::vector<Jet*> jets, const double pt, const double eta, double& targetHT ){
  for(unsigned int j = 0; j < jets.size(); j++){
    Jet* jet = jets[j];
    if (jet->pt() < pt) break;
    if (fabs(jet->eta()) > eta) continue;
    targetHT += jet->pt();
  }
}

void addBtagWeight (Jet* jet, float& weight){
  double pt = jet->pt();
  double eta = jet->eta();
  string flavor = jet->extendedFlavour();

  string etarange = "0.0-0.5";
  if (eta >= 0.5 && eta < 1.0) etarange = "0.5-1.0";
  else if (eta >= 1.0 && eta < 1.4) etarange = "1.0-1.4";
  else if (eta >= 1.4 && eta < 2.2) etarange = "1.4-2.2";

  string graphname = ("btag_eff_deepflavour_medium_" + flavor + "_pt_eta_" + etarange).c_str();
  TGraphAsymmErrors* evalgraph = (TGraphAsymmErrors*)btagweightfile -> Get(graphname.c_str());

  //cout << "B tag weight: " << evalgraph->Eval(pt) << endl;

  weight *= evalgraph->Eval(pt);
}

void applyPrescale ( const int& run, const double& random, float& prescaleEra, const int nsubsamples, int& window  )
{
  //Get correct Prescale for each Era
  //  for ( size_t i = 0 ; i < eraRanges.size() ; i++ )
  //    if (run >= eraRanges[i].first && run <= eraRanges[i].second ) prescaleEra = 7.0;
  //Split bkg in nsubsamples equally likely distributions
  for ( int w=0 ; w < nsubsamples; w++ )
    {
      if ( w == nsubsamples -1 && random > (w+1)/prescaleEra ) continue; // if last window and Random Value outside maximal window range skip
      if ( w/prescaleEra < random  &&  random < (w+1)/prescaleEra )
	{
	  window = w;
	  break;
	}
    }
}
