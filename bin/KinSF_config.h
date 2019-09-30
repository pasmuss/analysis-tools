#ifndef Analysis_Tools_KinSF_config_h_
#define Analysis_Tools_KinSF_config_h_

#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int KinSF_config(int argc, char * argv[]);

std::string cfg_;

int nevtmax_;
int nlumis_;
int runmin_;
int runmax_;
bool isMC_;
bool invertCutflow_;
std::string inputlist_;
std::string outputRoot_;
std::string json_;
std::string pufile_;
std::string reco_;

//
bool matchonoff_;
float matchonoffdrmax_;
bool matchonoffref_;
bool psweight_;
float psnorm_;
bool trigemul_;


// triggerobjects emulation
int tonmin_[10];
std::vector<float> toptmin_[10];
std::vector<float> toetamax_[10];

int torefnmin_[10];
std::vector<float> torefptmin_[10];
std::vector<float> torefetamax_[10];


// jets
bool useregression_;
bool useJER_;

int njetsmin_;
int njetsmax_;
std::vector<float> jetsptmin_;
std::vector<float> jetsptmax_;
std::vector<float> jetsetamax_;
std::string jetsid_;

int l1tjetsnmin_;
std::vector<float> l1tjetsptmin_;
std::vector<float> l1tjetsetamax_;

int l1tjetsrefnmin_;
std::vector<float> l1tjetsrefptmin_;
std::vector<float> l1tjetsrefetamax_;

// JER resolution and scale factors from txt file
std::string jerpt_;
std::string jersf_;


// muons
bool muonveto_;

int nmuonsmin_;
std::vector<float> muonsptmin_;
std::vector<float> muonsptmax_;
std::vector<float> muonsetamax_;
std::string muonsid_;

int l1tmuonsnmin_;
std::vector<float> l1tmuonsptmin_;
std::vector<float> l1tmuonsetamax_;

int l1tmuonsrefnmin_;
std::vector<float> l1tmuonsrefptmin_;
std::vector<float> l1tmuonsrefetamax_;


// additional cuts of unidentified objects or for extra selections
int nmin_;
int nmax_;
std::vector<float> ptmin_;
std::vector<float> ptmax_;
std::vector<float> etamax_;
float massdepptcut_;

float drmin_;
float drmax_;
float detamax_;
float dphimin_;
float m12min_;

float ptimbalmax_;

//for selection of jets which go into HT calculation
float etaHT_;
float ptHT_;

std::string hltPath_;
std::string l1Seed_;
std::string hltPathRef_;
std::string l1SeedRef_;
std::vector<std::string> triggerObjects_;
std::vector<int> triggerObjectsMatches_;
std::vector<int> triggerObjectsMatchesRank_;
std::vector<std::string> triggerObjectsRef_;
std::vector<std::string> hltPaths_;
std::string hltPathsLogic_;
std::vector<std::string> hltPaths2_;
std::string hltPathsLogic2_;
std::vector<std::string> triggerObjectsJets_;
std::vector<std::string> triggerObjectsMuons_;

// ntuples collections
std::string treePath_;
std::string jetsCol_; 
std::string muonsCol_; 
std::string l1tjetsCol_; 
std::string l1tmuonsCol_; 
std::string triggerCol_;
std::string genParticleCol_;
std::string genjetsCol_;
std::string triggerObjDir_;

int KinSF_config(int argc, char * argv[])
{
  try
    {
      namespace po = boost::program_options;
      po::options_description desc("Options");
      desc.add_options()
	("help,h","Show help messages")
	("config,c",po::value<std::string>(&cfg_),"Configuration file name");
      
      po::options_description config("Configuration");
      config.add_options()
	("reco",po::value <std::string> (&reco_)->default_value("rereco"),"prompt or rereco")
	("ntuplesList",po::value <std::string> (&inputlist_)->default_value("rootFileList.txt"),"File with list of ntuples")
	("nEventsMax",po::value <int> (&nevtmax_)->default_value(-1), "Maximum number of events")
	("nLumiSections",po::value <int> (&nlumis_)->default_value(-1), "Number of lumi sections processed")
	("runMin",po::value <int> (&runmin_)->default_value(-1), "Minimum run number")
	("runMax",po::value <int> (&runmax_)->default_value(-1), "Minimum run number")
	("output",po::value <std::string> (&outputRoot_)->default_value("histograms.root"),"Output root file")
	("json",po::value <std::string> (&json_)->default_value("no_json.txt"), "JSON file for data")
	("PUfile",po::value <std::string> (&pufile_)->default_value("pileup_weights.root"), "root file containing weights for pileup corrections")
	("jerPT",po::value <std::string> (&jerpt_)->default_value("JERPT.txt"),"JER pt resolution in txt format")
	("jerSF",po::value <std::string> (&jersf_)->default_value("JERSF.txt"),"JER scale factor in txt format")
	//
	("useJER",po::value <bool> (&useJER_)->default_value(true),"Use smearing (Jet Energy Resolution) for MC")
	("useRegression",po::value <bool> (&useregression_)->default_value(true),"Apply Jet Energy Regression (for b jets)")
	("nJetsMin",po::value <int> (&njetsmin_)->default_value(0),"Minimum number of jets")
	("nJetsMax",po::value <int> (&njetsmax_)->default_value(100),"Maximum number of jets")
	("jetsPtMin", po::value<std::vector<float> >(&jetsptmin_)->multitoken(),"Mimium pt of the jets")
	("jetsPtMax", po::value<std::vector<float> >(&jetsptmax_)->multitoken(),"Maximum pt of the jets")
	("jetsEtaMax", po::value<std::vector<float> >(&jetsetamax_)->multitoken(),"Maximum |eta| of the jets")
	("jetsId",po::value <std::string> (&jetsid_)->default_value("TIGHT"),"Jets id criteria for all jets")
	//
	("l1tJetsNMin",po::value <int> (&l1tjetsnmin_)->default_value(0),"Minimum number of L1T jets")
	("l1tJetsPtMin", po::value<std::vector<float> >(&l1tjetsptmin_)->multitoken(),"Mimium pt of the L1T jets")
	("l1tJetsEtaMax", po::value<std::vector<float> >(&l1tjetsetamax_)->multitoken(),"Maximum |eta| of the L1T jets")
	("l1tJetsRefNMin",po::value <int> (&l1tjetsrefnmin_)->default_value(0),"Minimum number of L1T jets for reference trigger")
	("l1tJetsRefPtMin", po::value<std::vector<float> >(&l1tjetsrefptmin_)->multitoken(),"Mimium pt of the L1T jets for reference trigger")
	("l1tJetsRefEtaMax", po::value<std::vector<float> >(&l1tjetsrefetamax_)->multitoken(),"Maximum |eta| of the L1T jets for reference trigger")         
	//
	("MuonVeto",po::value <bool> (&muonveto_)->default_value(true),"Use veto on muons")
	("nMuonsMin",po::value <int> (&nmuonsmin_)->default_value(0),"Minimum number of muons")
	("muonsPtMin", po::value<std::vector<float> >(&muonsptmin_)->multitoken(),"Mimium pt of the muons")
	("muonsPtMax", po::value<std::vector<float> >(&muonsptmax_)->multitoken(),"Maximum pt of the muons")
	("muonsEtaMax", po::value<std::vector<float> >(&muonsetamax_)->multitoken(),"Maximum |eta| of the muons")
	("muonsId",po::value <std::string> (&muonsid_)->default_value("LOOSE"),"muons id criteria for all muons")
	//
	("l1tMuonsNMin",po::value <int> (&l1tmuonsnmin_)->default_value(0),"Minimum number of L1T muons")
	("l1tMuonsPtMin", po::value<std::vector<float> >(&l1tmuonsptmin_)->multitoken(),"Mimium pt of the L1T muons")
	("l1tMuonsEtaMax", po::value<std::vector<float> >(&l1tmuonsetamax_)->multitoken(),"Maximum |eta| of the L1T muons")
	("l1tMuonsRefNMin",po::value <int> (&l1tmuonsrefnmin_)->default_value(0),"Minimum number of L1T muons for reference trigger")
	("l1tMuonsRefPtMin", po::value<std::vector<float> >(&l1tmuonsrefptmin_)->multitoken(),"Mimium pt of the L1T muons for reference trigger")
	("l1tMuonsRefEtaMax", po::value<std::vector<float> >(&l1tmuonsrefetamax_)->multitoken(),"Maximum |eta| of the L1T muons for reference trigger")         
	//
	("nMin",po::value <int> (&nmin_)->default_value(0),"Minimum number objects")
	("nMax",po::value <int> (&nmax_)->default_value(0),"Maximum number objects")
	("ptMin", po::value<std::vector<float> >(&ptmin_)->multitoken(),"Mimium pt of an object")
	("ptMax", po::value<std::vector<float> >(&ptmax_)->multitoken(),"Maximum pt of an object")
	("etaMax", po::value<std::vector<float> >(&etamax_)->multitoken(),"Maximum |eta| of an object")
	//
	("dRMin",po::value <float> (&drmin_)->default_value(0.),"Minimum delta R between candidates")
	("dRMax",po::value <float> (&drmax_)->default_value(0.),"Maximum delta R between candidates")
	("dEtaMax",po::value <float> (&detamax_)->default_value(10.),"Maximum delta eta between candidates")
	("dPhiMin",po::value <float> (&dphimin_)->default_value(0.),"Minimum delta phi between candidates")
	("ptImbalanceMax",po::value <float> (&ptimbalmax_)->default_value(1000.),"Maximum relative imbalance between two candidates")
	("MassDepPtCut",po::value <float> (&massdepptcut_)->default_value(-9999.),"Using mass dependent pT cut on leading two jets if > 0; value is then used fraction")
	("m12Min",po::value <float> (&m12min_)->default_value(-9999.),"Minimum value of m12 (mass of leading two jets)")
	("ptHT",po::value <float> (&ptHT_)->default_value(30.),"Minimum pT of a jet to be added to HT calculation")
	("etaHT",po::value <float> (&etaHT_)->default_value(2.4),"Maximum value for abs(eta) of a jet to be added to HT calculation")
	//      
	("isMC",po::value <bool> (&isMC_)->default_value(true),"Flag for MC dataset")
	("invertCutflow",po::value <bool> (&invertCutflow_)->default_value(false),"Flag for inverting Cutflow (placing trigger as last step)")
	("hltPath",po::value <std::string> (&hltPath_),"HLT path name")
	("l1Seed",po::value <std::string> (&l1Seed_)->default_value(""),"L1 seed name")
	("hltPathReference",po::value <std::string> (&hltPathRef_),"HLT path name for reference trigger for trigger efficiency")
	("l1SeedReference",po::value <std::string> (&l1SeedRef_)->default_value(""),"L1 seed name for reference trigger")
	("triggerObjects", po::value<std::vector<std::string> >(&triggerObjects_)->multitoken(),"Trigger objects")
	("triggerObjectsMatches", po::value<std::vector<int> >(&triggerObjectsMatches_)->multitoken(),"Number of trigger objects matches")
	("triggerObjectsMatchesRank", po::value<std::vector<int> >(&triggerObjectsMatchesRank_)->multitoken(),"Rank of offline object the trigger objects matches")
	("triggerObjectsReference", po::value<std::vector<std::string> >(&triggerObjectsRef_)->multitoken(),"Trigger objects reference trigger")
	("hltPathsList", po::value<std::vector<std::string> >(&hltPaths_)->multitoken(),"HLT paths list")
	("hltPathsLogic",po::value <std::string> (&hltPathsLogic_)->default_value("OR"),"HLT paths logic (OR/AND)")
	("hltPathsList2", po::value<std::vector<std::string> >(&hltPaths2_)->multitoken(),"HLT paths second list")
	("hltPathsLogic2",po::value <std::string> (&hltPathsLogic2_)->default_value("OR"),"HLT paths logic (OR/AND) for second list")
	("triggerObjectsJets", po::value<std::vector<std::string> >(&triggerObjectsJets_)->multitoken(),"Trigger objects for jets")
	("triggerObjectsMuons", po::value<std::vector<std::string> >(&triggerObjectsMuons_)->multitoken(),"Trigger objects for muons")
	//
	("matchOnlineOffline",po::value <bool> (&matchonoff_)->default_value(true),"Flag for doing matching online offline objects")
	("matchOnlineOfflineDeltaRMax",po::value <float> (&matchonoffdrmax_)->default_value(0.4),"DeltaR max for matching online-offline")
	("matchOnlineOfflineReference",po::value <bool> (&matchonoffref_)->default_value(true),"Flag for doing matching online offline objects when using a reference trigger")
	("prescaleWeight",po::value <bool> (&psweight_)->default_value(false),"Flag for weighting histograms with prescale")
	("prescaleNormalisation",po::value <float> (&psnorm_)->default_value(1.),"Normalisation factor of prescale weight")
	("triggerEmulation",po::value <bool> (&trigemul_)->default_value(false),"Flag for using trigger emulation")
         
	("jetsCollection",po::value <std::string> (&jetsCol_)->default_value("slimmedJets"),"Name of the jets collection")
	("muonsCollection",po::value <std::string> (&muonsCol_)->default_value("slimmedMuons"),"Name of the muons collection")
	("l1tJetsCollection",po::value <std::string> (&l1tjetsCol_)->default_value("l1tJets"),"Name of the L1T jets collection")
	("l1tMuonsCollection",po::value <std::string> (&l1tmuonsCol_)->default_value("l1tMuons"),"Name of the L1T muons collection")
	("genParticleCollection",po::value <std::string> (&genParticleCol_)->default_value("prunedGenParticles"),"Name of the gen particle collection")
	("genjetsCollection",po::value <std::string> (&genjetsCol_)->default_value("slimmedGenJets"),"Name of the gen jets collection")

	("triggerResultsCollection",po::value <std::string> (&triggerCol_)->default_value("TriggerResults"),"Name of the trigger results collection")
	("triggerObjectsDirectory",po::value <std::string> (&triggerObjDir_)->default_value("slimmedPatTrigger"),"Name of the trigger objects directory")
	("collectionsTreePath",po::value <std::string> (&treePath_)->default_value("Events"),"Name of the tree path for the event collections.");

      for ( int i = 0 ; i < 10 ; ++i )
	{
	  config.add_options()
	    (Form("triggerObject%dNMin",i),po::value <int> (&(tonmin_[i]))->default_value(0),Form("Minimum number of trigger objects #%d",i))
	    (Form("triggerObject%dPtMin",i),po::value<std::vector<float> >(&(toptmin_[i]))->multitoken(),Form("Minimum pT of trigger objects #%d",i))
	    (Form("triggerObject%dEtaMax",i),po::value<std::vector<float> >(&(toetamax_[i]))->multitoken(),Form("Minimum eta of trigger objects #%d",i))
	    (Form("triggerObject%dRefNMin",i),po::value <int> (&(torefnmin_[i]))->default_value(0),Form("Minimum number of trigger objects #%d for reference trigger",i))
	    (Form("triggerObject%dRefPtMin",i),po::value<std::vector<float> >(&(torefptmin_[i]))->multitoken(),Form("Minimum pT of trigger objects #%d for reference trigger",i))
	    (Form("triggerObject%dRefEtaMax",i),po::value<std::vector<float> >(&(torefetamax_[i]))->multitoken(),Form("Minimum eta of trigger objects #%d for reference trigger",i));
	}
      
      po::variables_map vm; 
      try
	{
	  po::store(po::parse_command_line(argc, argv, desc), vm); // can throw
	  // --help option
         
	  if ( vm.count("help") )
	    {
	      std::cout << "SimpleBjetsAnalysis macro" << std::endl
			<< desc << std::endl
			<< config << std::endl;
	      return 1;
	    }
	  po::notify(vm);
         
	  std::ifstream cfg_s(cfg_.c_str());
	  po::store(po::parse_config_file(cfg_s, config), vm); // can throw
	  if ( vm.count("config") )
	    {

	    }
	  po::notify(vm);
	  boost::algorithm::to_upper(jetsid_);
	  if ( (int)jetsptmin_.size() != njetsmin_ )
	    {
	      std::cout << "Config Error *** Jet minimum pt were not defined or the definition does not match the minimum number of jets" <<std::endl;
	      return -1;
	    }
	  if ( (int)jetsptmax_.size() != njetsmin_ && !jetsptmax_.empty() )
	    {
	      std::cout << "Config Error *** Jet maximum pt has been defined and does not match the minimum number of jets" <<std::endl;
	      return -1;
	    }
	  if ( (int)jetsetamax_.size() != njetsmin_ )
	    {
	      std::cout << "Config Error *** Jet maximum |eta| were not defined or the definition does not match the minimum number of jets" <<std::endl;
	      return -1;
	    }
	  if ( (int)muonsptmin_.size() != nmuonsmin_ )
	    {
	      std::cout << "Config Error *** Muon minimum pt were not defined or the definition does not match the minimum number of muons" <<std::endl;
	      return -1;
	    }
	  if ( (int)muonsptmax_.size() != nmuonsmin_ && !muonsptmax_.empty() )
	    {
	      std::cout << "Config Error *** Muon maximum pt has been defined and does not match the minimum number of muons" <<std::endl;
	      return -1;
	    }
	  if ( (int)muonsetamax_.size() != nmuonsmin_ )
	    {
	      std::cout << "Config Error *** Muon maximum |eta| were not defined or the definition does not match the minimum number of muons" <<std::endl;
	      return -1;
	    }
	}
      catch(po::error& e)
	{ 
	  std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
	  std::cerr << desc << std::endl; 
	  return -1; 
	} 
      
    }
  catch(std::exception& e) 
    { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      return -1; 
    } 
   
  return 0;
}
   
#endif
