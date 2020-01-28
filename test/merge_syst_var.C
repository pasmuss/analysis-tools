#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>

#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

using namespace std;

void merge_syst_var(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  vector<string> masses = {"250", "300", "350", "400", "450", "500", "600", "700", "800", "900", "1000", "1200", "1400", "1600"};
  vector<string> weightuncerts = {"PU", "SFbtag", "jet_trigeff", "onlSFbtag"};
  vector<string> ptuncerts = {"JER", "JES"};
  vector<string> vars = {"up", "down"};

  for (unsigned int a = 0; a < masses.size(); a++){
    cout << masses[a] << endl;
    TFile* infile0  = new TFile(("Configs_diffBTags_allmedium/Syst_Variations/Central/rootfiles/mcsig/mc-sig-" + masses[a] + "-NLO-deep-SR-3j.root").c_str(),"READ");
    TFile* infile1  = new TFile(("Configs_diffBTags_allmedium/Syst_Variations/JER_up/rootfiles/mcsig/mc-sig-" + masses[a] + "-NLO-deep-SR-3j.root").c_str(),"READ");
    TFile* infile2  = new TFile(("Configs_diffBTags_allmedium/Syst_Variations/JER_down/rootfiles/mcsig/mc-sig-" + masses[a] + "-NLO-deep-SR-3j.root").c_str(),"READ");
    TFile* infile3  = new TFile(("Configs_diffBTags_allmedium/Syst_Variations/JES_up/rootfiles/mcsig/mc-sig-" + masses[a] + "-NLO-deep-SR-3j.root").c_str(),"READ");
    TFile* infile4  = new TFile(("Configs_diffBTags_allmedium/Syst_Variations/JES_down/rootfiles/mcsig/mc-sig-" + masses[a] + "-NLO-deep-SR-3j.root").c_str(),"READ");
    TFile* outputfile = new TFile(("Configs_diffBTags_allmedium/Syst_Variations/MergedFiles/mc-sig-" + masses[a] + "-NLO-deep-SR-3j.root").c_str(),"RECREATE");
    for (unsigned int b = 0; b < weightuncerts.size(); b++){
      cout << weightuncerts[b] << endl;
      for (unsigned int c = 0; c < vars.size(); c++){
	cout << vars[c] << endl;
	string varname = ("m12_aac_" + weightuncerts[b] + "_" + vars[c]).c_str();
	cout << varname << endl;
	const char* charname = varname.c_str();
	TH1F* copyhist = (TH1F*) infile1 -> Get( charname );
	TH1F* storehist = (TH1F*) copyhist -> Clone();
	storehist -> Write();
      }
    }
    TH1F* jerupcopyhist = (TH1F*) infile1 -> Get("m12_aac");
    TH1F* m12_aac_JER_up = (TH1F*) jerupcopyhist -> Clone("m12_aac_JER_up");
    m12_aac_JER_up -> Write();
    TH1F* jerdowncopyhist = (TH1F*) infile2 -> Get("m12_aac");
    TH1F* m12_aac_JER_down = (TH1F*) jerdowncopyhist -> Clone("m12_aac_JER_down");
    m12_aac_JER_down -> Write();
    TH1F* jesupcopyhist = (TH1F*) infile3 -> Get("m12_aac");
    TH1F* m12_aac_JES_up = (TH1F*) jesupcopyhist -> Clone("m12_aac_JES_up");
    m12_aac_JES_up -> Write();
    TH1F* jesdowncopyhist = (TH1F*) infile4 -> Get("m12_aac");
    TH1F* m12_aac_JES_down = (TH1F*) jesdowncopyhist -> Clone("m12_aac_JES_down");
    m12_aac_JES_down -> Write();
    TH1F* centralhist = (TH1F*) infile0 -> Get("m12_aac");
    TH1F* m12_aac = (TH1F*) centralhist -> Clone();
    m12_aac -> Write();
  }
}
