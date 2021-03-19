#include "TH1.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"
#include "tdrstyle.C"

using namespace std;

void CombineAndNormSignalTemplates(){

  vector<string> subranges = { "SR1" , "SR2" , "SR3" , "SR4" };
  vector<string> binning = { "1" , "1" , "5" , "10"};
  vector<vector<string>> masses = { {"300","350","400"} , {"400","450","500","600","700"} , {"700","800","900","1000"} , {"1000","1200","1400","1600"} };
  vector<vector<double>> lumisf = { {142.9,69.29,75.24} , {75.24,75.45,64.51,77.85,70.42} , {70.42,72.21,75.66,74.27} , {74.27,71.75,73.48,75.7} };

  vector<TH1F*> finalhists = {};

  for (int sr = 0; sr<subranges.size(); sr++){
    string subrange = subranges[sr];
    vector<string> srmasses = masses[sr];
    vector<double> srsf = lumisf[sr];
    string binningsr = binning[sr];
    for (int mass = 0; mass<srmasses.size(); mass++){
      double sf = 1./srsf[mass];
      cout << srsf[mass] << " --> " << sf << endl;
      TFile* f_signal_in = new TFile(("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/central/mcsig/mc-sig-" + srmasses[mass]  + "-NLO-deep-SR-3j.root").c_str(),"READ");
      TH1F* frhist_in = (TH1F*)f_signal_in->Get(("m12_"+subrange+"_"+binningsr+"GeV").c_str());
      frhist_in -> SetName(("m12_"+srmasses[mass]+"GeV_"+subrange+"_"+binningsr+"GeVbinning").c_str());
      frhist_in -> Scale(sf);
      TH1F* tothist_in = (TH1F*)f_signal_in->Get("m12_aac");
      string totname = ("m12_"+srmasses[mass]+"GeV_20GeVbinning").c_str();
      tothist_in -> SetName(totname.c_str());
      tothist_in -> Scale(sf);
      finalhists.push_back(frhist_in);
      bool write = true;
      for (int i = 0; i < finalhists.size(); i++){
	if ( (finalhists[i] -> GetName()) == totname ){
	  write = false;
	}
      }
      if (write) finalhists.push_back(tothist_in);
    }
  }

  TFile* fOut = new TFile("AllSignals.root","RECREATE");
  for (int i = 0; i < finalhists.size(); i++){
    finalhists[i] -> Write();
  }
}

