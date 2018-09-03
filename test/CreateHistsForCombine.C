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

using namespace std;

int CreateHistsForCombine(string masspoint_, string era_){

  string era = era_;
  string masspoint = masspoint_;

  if (!(era == "CDE" || era == "CDEF" || era == "F")){
    cout << "No valid era provided. Please enter 'CDE', 'CDEF' or 'F'." << endl;
    return -1;
  }
  
  if (!(masspoint == "350" || masspoint == "600" || masspoint == "1200")){
    cout << "No valid mass point entered. Possibilities are 350, 600, and 1200." << endl;
    return -1;
  }
  
  float lumi = 36.0; //in fb^{-1}
  if (era == "CDE") lumi = 22.6;
  if (era == "F") lumi = 13.5;

  TFile* bgfile = new TFile( ("rootfiles/rereco/rereco-"+era+"-deep-CR.root").c_str(),"READ");
  TFile* datafile = new TFile( ("rootfiles/rereco/rereco-"+era+"-deep-CR.root").c_str(),"READ");
  TFile* sigfile = new TFile( ("rootfiles/mcsig/mc-sig-"+masspoint+"-deep-SR.root").c_str(),"READ");
  TFile* datasrfile = new TFile( ("rootfiles/rereco/rereco-"+era+"-deep-SR.root").c_str(),"READ");

  cout << "Opened all files." << endl;

  TH1F* bghist = (TH1F*)bgfile -> Get("m12_csv");
  TH1F* datahist = (TH1F*)datafile -> Get("m12_csv");
  TH1F* sighist = (TH1F*)sigfile -> Get("m12_csv");
  TH1F* datasrhist = (TH1F*)datasrfile -> Get("pt_1_csv");
  
  cout << "Got all histograms." << endl;

  ///
  /// Scale factors and general checks before starting
  ///

  // 1M pb^{-1} (1 pb is the target, 1M events produced) = 1000 fb^{-1} in the signal samples
  const float scalefactor = lumi / 1000;
  cout << "Scale factor: " << scalefactor << endl;
  const float targetevents = datasrhist -> GetEntries();
  cout << "target events: " << targetevents << endl;
  const float presentevents = bghist -> GetEntries();
  cout << "present events: " << presentevents << endl;
  const float normalization = targetevents / presentevents;
  cout << "Normalization: " << normalization << endl;

  const int signalbins = sighist -> GetNbinsX();
  cout << "Bins in signal histogram: " << signalbins << endl;
  const int bgbins = bghist -> GetNbinsX();
  cout << "Bins in background histogram: " << bgbins << endl;
  const int databins = datahist -> GetNbinsX();
  cout << "Bins in data histogram: " << databins << endl;

  cout << "Got all numbers." << endl;

  if ( !( (signalbins == bgbins) && (signalbins == databins) ) ){
    cout << "Histograms do not have same binning. Please first take care of this!" << endl;
    return -1;
  }

  cout << "Did all checks." << endl;

  ///
  /// Cloning histograms into a common file and scaling them
  ///

  TH1F* QCD_Mbb = (TH1F*) ( (TH1F*) bgfile -> Get("m12_csv") -> Clone("QCD_Mbb") );
  QCD_Mbb -> Scale(normalization);
  TH1F* data_obs = (TH1F*) ( (TH1F*) bgfile -> Get("m12_csv") -> Clone("data_obs") );
  data_obs -> Scale(normalization);

  TFile* outputfile = new TFile( ("rootfiles/combine_"+masspoint+"_"+era+".root").c_str(),"RECREATE");
  TH1F* bbH_Mbb = (TH1F*) ( (TH1F*) sigfile -> Get("m12_csv") -> Clone("bbH_Mbb") );
  bbH_Mbb -> Scale(scalefactor);

  cout << "Created output file and cloned all histograms." << endl;

  bbH_Mbb  -> Write();
  QCD_Mbb  -> Write();
  data_obs -> Write();

  cout << "Wrote all histograms." << endl;

  bgfile -> Close();
  datafile -> Close();
  sigfile -> Close();
  datasrfile -> Close();
  outputfile -> Close();

  cout << "Closed all files." << endl;

  return 0;

}
