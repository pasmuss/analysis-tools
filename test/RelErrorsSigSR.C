#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>

#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include <iostream>
#include "TMath.h"

#include "HbbStylesNew.cc"

using namespace std;

int RelErrorsSigSR(){

  TH1::SetDefaultSumw2();

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TCanvas* can = style.MakeCanvas("can","",700,700);

  TFile* ToySRfile = new TFile("Outputdata/TF_bias/Pseudos_evenFiner1GeVBins_1904.root","READ");//SR3: 5 GeV binning
  TFile* SignalFile_1000 = new TFile("/nfs/dust/cms/user/asmusspa/private/rootfiles_analysis_3jsel_evenFinerBinsForCombine_SR1and2_Aug04-20/mcsig/mc-sig-1000-NLO-deep-SR-3j.root","READ");
  TFile* OutFile = new TFile("Outputdata/RelErrSigToSR.root","RECREATE");

  TH1F* ToySR3hist = (TH1F*)ToySRfile->Get("SRHist_SR3");
  TH1F* SignalHist_1000_SR3 = (TH1F*)SignalFile_1000->Get("m12_SR3_5GeV");

  int nbinsSR3hist = ToySR3hist->GetNbinsX();
  int nbinssighist1000SR3 = SignalHist_1000_SR3->GetNbinsX();

  int binwidth = ToySR3hist->GetBinWidth(10);
  int lowerbound = ToySR3hist->GetBinLowEdge(1);
  int upperbound = ToySR3hist->GetBinLowEdge(nbinsSR3hist) + binwidth;

  double sf_1000_SR3 = 1/74.27;

  SignalHist_1000_SR3 -> Scale(sf_1000_SR3);

  if (nbinsSR3hist!=nbinssighist1000SR3){
    cout << "Number of bins does not agree between histograms. Something is wrong. Aborting." << endl;
    cout << "Number of bins in signal hist: " << nbinssighist1000SR3 << endl;
    cout << "Number of bins in SR hist: " << nbinsSR3hist << endl;
      return -1;
  }

  cout << lowerbound << " " << binwidth << " " << upperbound << endl;
  cout << "Number of bins: " << nbinsSR3hist << ", bin width = " << binwidth << endl;

  TH1F* outhist_1000_SR3 = new TH1F("outhist_1000_SR3","",nbinsSR3hist,lowerbound,upperbound);

  for (int bin = 1; bin <= nbinsSR3hist; bin++){
    float errorsig = SignalHist_1000_SR3->GetBinError(bin);
    float errorSR  = ToySR3hist->GetBinError(bin);
    float relation = errorsig/errorSR;
    //cout << "Error relation for bin " << bin << ": " << relation << endl;
    outhist_1000_SR3 -> SetBinContent(bin,relation);
    //cout << "Content in output hist: " << outhist_1000_SR3->GetBinContent(bin) << endl;
    if (bin%10==0){
      cout << "Bin " << bin << ", centered at " << ToySR3hist->GetBinCenter(bin) << ", errors SR / sig: " << errorSR << " " << errorsig << endl;
    }
  }

  outhist_1000_SR3->Draw();
  outhist_1000_SR3->Write();

  return 0;

}
