#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

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

int ratioMCbg(string basis_, double ylow_, double yhigh_, bool logy_, int rebin_) {

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TFile* file_cr_3b = new TFile( (basis_ + "-CR-total-3j.root").c_str() ,"READ");
  TFile* file_sr_3b = new TFile( (basis_ + "-SR-total-3j.root").c_str() ,"READ");
  TFile* file_cr_4b = new TFile( (basis_ + "-CR-total-4j.root").c_str() ,"READ");
  TFile* file_sr_4b = new TFile( (basis_ + "-SR-total-4j.root").c_str() ,"READ");

  TFile* out_file = new TFile( (basis_ + "-MC-scaled-total.root").c_str(), "RECREATE");

  TCanvas* in_can_cr_3b = (TCanvas*)file_cr_3b -> Get("GesCan");
  TH1F* hist_cr_3b = (TH1F*)in_can_cr_3b->GetListOfPrimitives()->At(1)->Clone();
  TCanvas* in_can_sr_3b = (TCanvas*)file_sr_3b -> Get("GesCan");
  TH1F* hist_sr_3b = (TH1F*)in_can_sr_3b->GetListOfPrimitives()->At(1)->Clone();

  TH1F* out_cr_3b = (TH1F*)hist_cr_3b->Clone();
  out_cr_3b -> SetName("3b_cr_m12_aac");
  TH1F* out_sr_3b = (TH1F*)hist_sr_3b->Clone();
  out_sr_3b -> SetName("3b_sr_m12_aac");
  
  hist_sr_3b -> Divide(hist_cr_3b);
  hist_sr_3b -> GetYaxis() -> SetRangeUser(ylow_,yhigh_);
  hist_sr_3b -> Rebin(rebin_);//take care: rebinning should probably not be done here but by rebinning the original histograms in order to keep the result consistent
  hist_sr_3b -> GetYaxis() -> SetTitle("bbb/bbnb");

  TCanvas* out_can_3b = style.MakeCanvas("out_can_3b", "", 700,700);
  out_can_3b -> cd();
  if (logy_) out_can_3b -> SetLogy(1);
  hist_sr_3b -> Draw();

  TF1* fitfunction = new TF1("fitfunction","[0]*erf([2]*(x-[1]))",200,1200);
  fitfunction -> SetParameters(0.5,88,0.008);
  fitfunction -> SetLineColor(kRed);

  hist_sr_3b -> Fit(fitfunction,"R");
  TFitResultPtr r = hist_sr_3b->Fit(fitfunction,"RS");

  cout << "chi2/ndf = " << r->Chi2() << "/" << r->Ndf() << " = " << r->Chi2()/r->Ndf() << ", prob = " << r->Prob() << endl;

  out_can_3b -> Update();

  out_can_3b -> SaveAs("Outputdata/m12_ratio_CR-SR/test.pdf");
  out_can_3b -> SaveAs("Outputdata/m12_ratio_CR-SR/test.root");
  
  out_cr_3b -> Write();
  out_sr_3b -> Write();
  hist_sr_3b -> Write();

  return 0;
}
