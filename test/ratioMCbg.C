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

  TFile* file_cr_3b = new TFile( (basis_ + "CR-3j.root").c_str() ,"READ");
  TFile* file_sr_3b = new TFile( (basis_ + "SR-3j.root").c_str() ,"READ");
  //TFile* file_cr_4b = new TFile( (basis_ + "CR-4j.root").c_str() ,"READ");
  //TFile* file_sr_4b = new TFile( (basis_ + "SR-4j.root").c_str() ,"READ");

  TFile* out_file = new TFile( (basis_ + "-MC-tf.root").c_str(), "RECREATE");

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

  TF1* fitfunction = new TF1("fitfunction","[0]*erf([2]*(x-[1]))*(1+[3]*x)",200,500);//erf times linear decrease at higher masses
  //TF1* fitfunction = new TF1("fitfunction","[0]*erf([2]*(x-[1]))",80,500);//simple erf
  //TF1* fitfunction = new TF1("fitfunction","[0]*x+[1]",200,500);//ax+b
  //TF1* fitfunction = new TF1("fitfunction","[0]*x*x+[1]*x+[2]",200,500);//ax^2+bx+c
  fitfunction -> SetParameters(0.2,100,0);
  fitfunction -> SetLineColor(kRed);

  hist_sr_3b -> Fit(fitfunction,"R");
  TFitResultPtr r = hist_sr_3b->Fit(fitfunction,"RS");

  cout << "chi2/ndf = " << r->Chi2() << "/" << r->Ndf() << " = " << r->Chi2()/r->Ndf() << ", prob = " << r->Prob() << endl;

  hist_sr_3b -> GetXaxis() -> SetRangeUser(100,2000);

  out_can_3b -> Update();

  out_can_3b -> SaveAs("Outputdata/m12_ratio_CR-SR_weights/exterf_SR1_200to500_May12-20_weights.pdf");
  out_can_3b -> SaveAs("Outputdata/m12_ratio_CR-SR_weights/exterf_SR1_200to500_May12-20_weights.root");
  
  hist_sr_3b -> Write();
  out_cr_3b -> Write();
  out_sr_3b -> Write();

  return 0;
}
