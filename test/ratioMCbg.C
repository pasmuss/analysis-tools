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

int ratioMCbg(string basis_, double ylow_, double yhigh_, bool logy_=0, int rebin_=1) {

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TFile* file_cr_3b = new TFile( (basis_ + "CR-3j.root").c_str() ,"READ");
  TFile* file_sr_3b = new TFile( (basis_ + "SR-3j.root").c_str() ,"READ");
  //TFile* file_cr_4b = new TFile( (basis_ + "CR-4j.root").c_str() ,"READ");
  //TFile* file_sr_4b = new TFile( (basis_ + "SR-4j.root").c_str() ,"READ");

  TFile* out_file = new TFile( (basis_ + "MC-tf_FR3_eml.root").c_str(), "RECREATE");

  TH1F* hist_cr_3b = (TH1F*)file_cr_3b -> Get("hist_output_ges");
  TH1F* hist_sr_3b = (TH1F*)file_sr_3b -> Get("hist_output_ges");

  TH1F* out_cr_3b = (TH1F*)hist_cr_3b->Clone(); out_cr_3b -> SetName("out_cr_3b");
  TH1F* out_sr_3b = (TH1F*)hist_sr_3b->Clone(); out_sr_3b -> SetName("out_sr_3b");
  
  hist_sr_3b -> Divide(hist_cr_3b);
  hist_sr_3b -> Rebin(rebin_);
  double scale = 1/(double)rebin_;
  cout << "scale: " << scale << endl;
  hist_sr_3b -> Scale(scale);
  hist_sr_3b -> GetYaxis() -> SetRangeUser(ylow_,yhigh_);
  hist_sr_3b -> GetYaxis() -> SetTitle("bbb/bbnb");

  TCanvas* out_can_3b = style.MakeCanvas("out_can_3b", "", 700,700);
  out_can_3b -> cd();
  if (logy_) out_can_3b -> SetLogy(1);
  hist_sr_3b -> Draw();

  TF1* fitfunction = new TF1("fitfunction","[0]*erf([2]*(x-[1]))*(1+[3]*x)",260,785);//erf times linear decrease at higher masses
  //TF1* fitfunction = new TF1("fitfunction","[0]*erf([2]*(x-[1]))",200,500);//simple erf
  //TF1* fitfunction = new TF1("fitfunction","[0]*x+[1]",390,1270);//ax+b
  //TF1* fitfunction = new TF1("fitfunction","[0]",260,785);//a
  //TF1* fitfunction = new TF1("fitfunction","[0]*x*x+[1]*x+[2]",200,500);//ax^2+bx+c
  //TF1* fitfunction = new TF1("fitfunction","[0]/(1+TMath::Exp(-[1]*(x-[2])))",200,500);//logistic function
  //TF1* fitfunction = new TF1("fitfunction","[0]/(1+TMath::Exp(-[1]*(x-[2])))*(1+[3]*x)",200,500);//extended logistic function
  //TF1* fitfunction = new TF1("fitfunction","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))",200,500);//modified logistic function
  //TF1* fitfunction = new TF1("fitfunction","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",260,785);//extended modified logistic function
  fitfunction -> SetParameters(0.17,200,0.05,-2e-4);
  fitfunction -> SetParLimits(3,0.0,15.0);
  fitfunction -> SetLineColor(kRed);

  hist_sr_3b -> Fit(fitfunction,"R");
  TFitResultPtr r = hist_sr_3b->Fit(fitfunction,"RS");

  int nbinsin = 0;
  int xlowin = 0;
  int xhighin = 0;
  nbinsin = hist_sr_3b -> GetNbinsX();
  xlowin = hist_sr_3b -> GetBinLowEdge(1);
  xhighin = hist_sr_3b -> GetBinLowEdge(nbinsin) + hist_sr_3b -> GetBinWidth(nbinsin);
  cout << "nbins, low, high: " << nbinsin << " " << xlowin << " " << xhighin << endl;
  //TH1F* fiterrhist = new TH1F("fitterrhist","Histogram with fit error band",nbinsin,xlowin,xhighin);
  TH1F* fiterrhist = new TH1F("fitterrhist","Histogram with fit error band",176,390,1270);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(fiterrhist);
  fiterrhist -> SetStats(kFALSE);
  fiterrhist -> SetFillColor(2);
  fiterrhist -> SetLineColor(2);
  fiterrhist -> SetMarkerSize(0);
  fiterrhist -> Draw("e3 SAME");

  cout << "chi2/ndf = " << r->Chi2() << "/" << r->Ndf() << " = " << r->Chi2()/r->Ndf() << ", prob = " << r->Prob() << endl;

  hist_sr_3b -> GetXaxis() -> SetRangeUser(200,2000);
  out_can_3b -> Update();

  TCanvas* out_can_rp = style.MakeCanvas("out_can_rp", "", 700,700);
  out_can_rp -> cd();
  if (logy_) out_can_rp -> SetLogy(1);

  auto rp = new TRatioPlot(hist_sr_3b);
  rp -> SetUpTopMargin(0.03);
  rp -> SetLowBottomMargin(0.4);
  rp -> SetRightMargin(0.05);
  rp -> SetLeftMargin(0.12);
  rp -> SetSeparationMargin(0.02);
  rp -> Draw(); 
  rp -> GetLowerRefXaxis() -> SetTitleOffset(1.0);
  rp -> GetUpperRefYaxis() -> SetTitleOffset(1.05);
  rp -> GetLowerRefYaxis() -> SetRangeUser(-2,2);
  rp -> GetLowYaxis() -> SetNdivisions(505);
  rp -> GetConfidenceInterval1() -> SetFillColor(0);
  rp -> GetConfidenceInterval2() -> SetFillColor(0);

  out_can_rp -> SaveAs("Outputdata/m12_ratio_CR-SR_cuts/fitratio_TFSR_exterf_m12-260-785_Dec10-20_weights_nfsdataMay12-20.pdf");
  out_can_rp -> SaveAs("Outputdata/m12_ratio_CR-SR_cuts/fitratio_TFSR_exterf_m12-260-785_Dec10-20_weights_nfsdataMay12-20.root");
  
  out_can_3b -> SaveAs("Outputdata/m12_ratio_CR-SR_cuts/fit_TFSR_exterf_m12-260-785_Dec10-20_weights_nfsdataMay12-20.pdf");
  out_can_3b -> SaveAs("Outputdata/m12_ratio_CR-SR_cuts/fit_TFSR_exterf_m12-260-785_Dec10-20_weights_nfsdataMay12-20.root");
  
  hist_sr_3b -> Write();
  out_cr_3b -> Write();
  out_sr_3b -> Write();

  return 0;
}
