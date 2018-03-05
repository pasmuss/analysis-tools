#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"

void GetHistFromFile(){
  TFile* FileC = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/histogramsC_CR.root","READ");
  TFile* FileD = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/histogramsD_CR.root","READ");
  TFile* FileE = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/histogramsE_CR.root","READ");
  TFile* FileF = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/histogramsF_CR.root","READ");
  //no directory needed: all histograms are stored directly

  TCanvas* pt = new TCanvas("pt","pt",1000,1000);
  TCanvas* eta = new TCanvas("eta","eta",1000,1000);

  //todo: get histograms before and after cuts/matching (csv/nothing) and draw them with different marker styles, one color for each era of C-F
  
  
}
