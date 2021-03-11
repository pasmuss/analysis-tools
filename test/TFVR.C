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

int TFVR(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TFile* file_cr_3b = new TFile( "Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/central/rereco/rereco-CDEF-deep-CR-3j.root" ,"READ");
  TFile* file_vr_3b = new TFile( "Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/central/rereco/rereco-CDEF-deep-VR-3j.root" ,"READ");

  TFile* out_file = new TFile( "Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/central/rereco/MC-tfVR_FR2_eml.root", "RECREATE");

  //to become the final TF histograms: divide VR/CR
  TH1F* hist_cr_3b_FR1 = (TH1F*)file_cr_3b -> Get("m12_SR1_10GeV");
  TH1F* hist_vr_3b_FR1 = (TH1F*)file_vr_3b -> Get("m12_SR1_10GeV");
  TH1F* hist_cr_3b_FR2 = (TH1F*)file_cr_3b -> Get("m12_SR2_15GeV");
  TH1F* hist_vr_3b_FR2 = (TH1F*)file_vr_3b -> Get("m12_SR2_15GeV");
  TH1F* hist_cr_3b_FR3 = (TH1F*)file_cr_3b -> Get("m12_SR3_20GeV");
  TH1F* hist_vr_3b_FR3 = (TH1F*)file_vr_3b -> Get("m12_SR3_20GeV");
  TH1F* hist_cr_3b_FR4 = (TH1F*)file_cr_3b -> Get("m12_SR4_25GeV");
  TH1F* hist_vr_3b_FR4 = (TH1F*)file_vr_3b -> Get("m12_SR4_25GeV");

  if( (!(hist_cr_3b_FR1->GetBinWidth(1) == hist_vr_3b_FR1->GetBinWidth(1)) ||
       !(hist_cr_3b_FR2->GetBinWidth(1) == hist_vr_3b_FR2->GetBinWidth(1))) ||
      (!(hist_cr_3b_FR3->GetBinWidth(1) == hist_vr_3b_FR3->GetBinWidth(1)) ||
       !(hist_cr_3b_FR4->GetBinWidth(1) == hist_vr_3b_FR4->GetBinWidth(1))) ){
    cout << "Bin widths of histograms in at least one subrange does not match:" << endl;
    cout << 
      hist_cr_3b_FR1->GetBinWidth(1) << " " << hist_vr_3b_FR1->GetBinWidth(1) << " " <<
      hist_cr_3b_FR2->GetBinWidth(1) << " " << hist_vr_3b_FR2->GetBinWidth(1) << " " <<
      hist_cr_3b_FR3->GetBinWidth(1) << " " << hist_vr_3b_FR3->GetBinWidth(1) << " " << 
      hist_cr_3b_FR4->GetBinWidth(1) << " " << hist_vr_3b_FR4->GetBinWidth(1) << endl;
    return -1;
  }

  //only for storage: input histograms
  TH1F* out_cr_3b_FR1 = (TH1F*)hist_cr_3b_FR1->Clone(); out_cr_3b_FR1 -> SetName("out_cr_3b_FR1");
  TH1F* out_vr_3b_FR1 = (TH1F*)hist_vr_3b_FR1->Clone(); out_vr_3b_FR1 -> SetName("out_vr_3b_FR1");
  TH1F* out_cr_3b_FR2 = (TH1F*)hist_cr_3b_FR2->Clone(); out_cr_3b_FR2 -> SetName("out_cr_3b_FR2");
  TH1F* out_vr_3b_FR2 = (TH1F*)hist_vr_3b_FR2->Clone(); out_vr_3b_FR2 -> SetName("out_vr_3b_FR2");
  TH1F* out_cr_3b_FR3 = (TH1F*)hist_cr_3b_FR3->Clone(); out_cr_3b_FR3 -> SetName("out_cr_3b_FR3");
  TH1F* out_vr_3b_FR3 = (TH1F*)hist_vr_3b_FR3->Clone(); out_vr_3b_FR3 -> SetName("out_vr_3b_FR3");
  TH1F* out_cr_3b_FR4 = (TH1F*)hist_cr_3b_FR4->Clone(); out_cr_3b_FR4 -> SetName("out_cr_3b_FR4");
  TH1F* out_vr_3b_FR4 = (TH1F*)hist_vr_3b_FR4->Clone(); out_vr_3b_FR4 -> SetName("out_vr_3b_FR4");
  
  //calculate TF histograms
  hist_vr_3b_FR1 -> Divide(hist_cr_3b_FR1);
  hist_vr_3b_FR1 -> GetXaxis() -> SetRangeUser(200,500);
  hist_vr_3b_FR1 -> GetYaxis() -> SetRangeUser(0.14,0.24);
  hist_vr_3b_FR1 -> GetYaxis() -> SetTitle("bbsb/bbnb");
  hist_vr_3b_FR2 -> Divide(hist_cr_3b_FR2);
  hist_vr_3b_FR2 -> GetXaxis() -> SetRangeUser(260,785);
  hist_vr_3b_FR2 -> GetYaxis() -> SetRangeUser(0.14,0.24);
  hist_vr_3b_FR2 -> GetYaxis() -> SetTitle("bbsb/bbnb");
  hist_vr_3b_FR3 -> Divide(hist_cr_3b_FR3);
  hist_vr_3b_FR3 -> GetXaxis() -> SetRangeUser(390,1270);
  hist_vr_3b_FR3 -> GetYaxis() -> SetRangeUser(0.01,0.4);
  hist_vr_3b_FR3 -> GetYaxis() -> SetTitle("bbsb/bbnb");
  hist_vr_3b_FR4 -> Divide(hist_cr_3b_FR4);
  hist_vr_3b_FR4 -> GetXaxis() -> SetRangeUser(500,2000);
  hist_vr_3b_FR4 -> GetYaxis() -> SetRangeUser(0.01,0.5);
  hist_vr_3b_FR4 -> GetYaxis() -> SetTitle("bbsb/bbnb");
  /*
  //FR 1: canvas, fitfunction, fit
  TCanvas* out_can_3b_FR1 = style.MakeCanvas("out_can_3b_FR1", "", 700,700);
  out_can_3b_FR1 -> cd();
  hist_vr_3b_FR1 -> Draw();

  //TF1* fitfunction_FR1 = new TF1("fitfunction_FR1","[0]*x+[1]",200,500);//ax+b
  TF1* fitfunction_FR1 = new TF1("fitfunction_FR1","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",200,500);//extended modified logistic function
  //fitfunction_FR1 -> SetParameters(0.15,0.007965,250,0.5927,-0.00018);
  fitfunction_FR1 -> SetLineColor(kRed);
  fitfunction_FR1 -> SetParameter(0,0.15);
  fitfunction_FR1 -> FixParameter(1,0.05);//steepness
  fitfunction_FR1 -> FixParameter(2,235);//offset
  fitfunction_FR1 -> FixParameter(3,1.17);//alpha
  fitfunction_FR1 -> FixParameter(4,0.00004);//linslope
  hist_vr_3b_FR1 -> Fit(fitfunction_FR1,"R");

  TF1* fitfunction_FR1_350 = new TF1("fitfunction_FR1_350","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",200,500);//extended modified logistic function
  //fitfunction_FR1_350 -> SetParameters(0.15,0.007965,250,0.5927,-0.00018);
  fitfunction_FR1_350 -> SetLineColor(kMagenta);
  fitfunction_FR1_350 -> SetParameter(0,0.15);
  fitfunction_FR1_350 -> FixParameter(1,0.04);
  fitfunction_FR1_350 -> FixParameter(2,250);
  fitfunction_FR1_350 -> FixParameter(3,1.18);
  fitfunction_FR1_350 -> FixParameter(4,0.000001);
  hist_vr_3b_FR1 -> Fit(fitfunction_FR1_350,"R");

  TF1* fitfunction_FR1_400 = new TF1("fitfunction_FR1_400","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",200,500);//extended modified logistic function
  //fitfunction_FR1_400 -> SetParameters(0.15,0.007965,250,0.5927,-0.00018);
  fitfunction_FR1_400 -> SetLineColor(kViolet-5);
  fitfunction_FR1_400 -> SetParameter(0,0.15);
  fitfunction_FR1_400 -> FixParameter(1,0.02);
  fitfunction_FR1_400 -> FixParameter(2,250);
  fitfunction_FR1_400 -> FixParameter(3,1.23);
  fitfunction_FR1_400 -> FixParameter(4,0.000001);
  hist_vr_3b_FR1 -> Fit(fitfunction_FR1_400,"R");

  fitfunction_FR1 -> Draw("SAME");
  fitfunction_FR1_350 -> Draw("SAME");
  fitfunction_FR1_400 -> Draw("SAME");

  TLegend* legFR1 = new TLegend(0.2,0.7,0.95,0.9);
  style.SetLegendStyle(legFR1);
  legFR1 -> SetNColumns(2);
  legFR1 -> AddEntry(hist_vr_3b_FR1,"TF VR/CR FR 1","LP");
  legFR1 -> AddEntry(fitfunction_FR1_350,"350 GeV fit result","L");
  legFR1 -> AddEntry(fitfunction_FR1,"300 GeV fit result","L");
  legFR1 -> AddEntry(fitfunction_FR1_400,"400 GeV fit result","L");
  legFR1 -> Draw("SAME");
  
  //TFitResultPtr r_FR1 = hist_vr_3b_FR1->Fit(fitfunction_FR1,"RS");

  //int nbinsin_FR1 = 0;
  //int xlowin_FR1 = 0;
  //int xhighin_FR1 = 0;
  //nbinsin_FR1 = hist_vr_3b_FR1 -> GetNbinsX();
  //xlowin_FR1 = hist_vr_3b_FR1 -> GetBinLowEdge(1);
  //xhighin_FR1 = hist_vr_3b_FR1 -> GetBinLowEdge(nbinsin_FR1) + hist_vr_3b_FR1 -> GetBinWidth(nbinsin_FR1);
  //cout << "nbins, low, high: " << nbinsin_FR1 << " " << xlowin_FR1 << " " << xhighin_FR1 << endl;
  //TH1F* fiterrhist_FR1 = new TH1F("fitterrhist_FR1","Histogram with fit error band",nbinsin_FR1,xlowin_FR1,xhighin_FR1);
  //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(fiterrhist_FR1);
  //fiterrhist_FR1 -> SetStats(kFALSE);
  //fiterrhist_FR1 -> SetFillColor(2);
  //fiterrhist_FR1 -> SetLineColor(2);
  //fiterrhist_FR1 -> SetMarkerSize(0);
  //fiterrhist_FR1 -> Draw("e3 SAME");
  //cout << "chi2/ndf = " << r_FR1->Chi2() << "/" << r_FR1->Ndf() << " = " << r_FR1->Chi2()/r_FR1->Ndf() << ", prob = " << r_FR1->Prob() << endl;
  

  out_can_3b_FR1 -> Update();
  out_can_3b_FR1 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR1_Feb12-21_slTFasBef.pdf");
  out_can_3b_FR1 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR1_Feb12-21_slTFasBef.root");
  
*/

  /*TCanvas* rpFR1can = style.MakeCanvas("rpFR1can","",700,700);
  auto rp = new TRatioPlot(hist_vr_3b_FR1); 
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
  
  rpFR1can -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/ratio_TF_vs_FitResultCombine_FR1_Feb02-21.pdf");
  rpFR1can -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/ratio_TF_vs_FitResultCombine_FR1_Feb02-21.root");
  */

  /*
  //FR 2: canvas, fitfunction, fit
  TCanvas* out_can_3b_FR2 = style.MakeCanvas("out_can_3b_FR2", "", 700,700);
  out_can_3b_FR2 -> cd();
  hist_vr_3b_FR2 -> Draw();

  //TF1* fitfunction_FR2 = new TF1("fitfunction_FR2","[0]*x+[1]",260,785);//ax+b
  TF1* fitfunction_FR2 = new TF1("fitfunction_FR2","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",260,785);//extended modified logistic function
  fitfunction_FR2 -> SetLineColor(kRed);
  fitfunction_FR2 -> SetParameter(0,0.15);
  fitfunction_FR2 -> FixParameter(1,0.00044);//steepness
  fitfunction_FR2 -> FixParameter(2,250);//offset
  fitfunction_FR2 -> FixParameter(3,0.00);//alpha
  fitfunction_FR2 -> FixParameter(4,3.5e-4);//linslope
  hist_vr_3b_FR2 -> Fit(fitfunction_FR2,"R");

  TF1* fitfunction_FR2_450 = new TF1("fitfunction_FR2_450","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",260,785);//extended modified logistic function
  fitfunction_FR2_450 -> SetLineColor(kMagenta);
  fitfunction_FR2_450 -> SetParameter(0,0.15);
  fitfunction_FR2_450 -> FixParameter(1,0.00045);
  fitfunction_FR2_450 -> FixParameter(2,250);
  fitfunction_FR2_450 -> FixParameter(3,0.04);
  fitfunction_FR2_450 -> FixParameter(4,3.5e-4);
  hist_vr_3b_FR2 -> Fit(fitfunction_FR2_450,"R");

  TF1* fitfunction_FR2_500 = new TF1("fitfunction_FR2_500","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",260,785);//extended modified logistic function
  fitfunction_FR2_500 -> SetLineColor(kViolet-5);
  fitfunction_FR2_500 -> SetParameter(0,0.15);
  fitfunction_FR2_500 -> FixParameter(1,0.00037);
  fitfunction_FR2_500 -> FixParameter(2,250);
  fitfunction_FR2_500 -> FixParameter(3,0.01);
  fitfunction_FR2_500 -> FixParameter(4,3.5e-4);
  hist_vr_3b_FR2 -> Fit(fitfunction_FR2_500,"R");

  TF1* fitfunction_FR2_600 = new TF1("fitfunction_FR2_600","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",260,785);//extended modified logistic function
  fitfunction_FR2_600 -> SetLineColor(kCyan);
  fitfunction_FR2_600 -> SetParameter(0,0.15);
  fitfunction_FR2_600 -> FixParameter(1,0.00043);
  fitfunction_FR2_600 -> FixParameter(2,250);
  fitfunction_FR2_600 -> FixParameter(3,0.12);
  fitfunction_FR2_600 -> FixParameter(4,3.5e-4);
  hist_vr_3b_FR2 -> Fit(fitfunction_FR2_600,"R");

  TF1* fitfunction_FR2_700 = new TF1("fitfunction_FR2_700","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",260,785);//extended modified logistic function
  fitfunction_FR2_700 -> SetLineColor(kGreen);
  fitfunction_FR2_700 -> SetParameter(0,0.15);
  fitfunction_FR2_700 -> FixParameter(1,0.0117);
  fitfunction_FR2_700 -> FixParameter(2,250);
  fitfunction_FR2_700 -> FixParameter(3,0.90);
  fitfunction_FR2_700 -> FixParameter(4,3.5e-4);
  hist_vr_3b_FR2 -> Fit(fitfunction_FR2_700,"R");

  fitfunction_FR2 -> Draw("SAME");
  fitfunction_FR2_450 -> Draw("SAME");
  fitfunction_FR2_500 -> Draw("SAME");
  fitfunction_FR2_600 -> Draw("SAME");
  fitfunction_FR2_700 -> Draw("SAME");

  TLegend* legFR2 = new TLegend(0.2,0.7,0.95,0.9);
  style.SetLegendStyle(legFR2);
  legFR2 -> SetNColumns(2);
  legFR2 -> AddEntry(hist_vr_3b_FR2,"TF VR/CR FR 2","LP");
  legFR2 -> AddEntry(fitfunction_FR2_500,"500 GeV fit result","L");
  legFR2 -> AddEntry(fitfunction_FR2,"400 GeV fit result","L");
  legFR2 -> AddEntry(fitfunction_FR2_600,"600 GeV fit result","L");
  legFR2 -> AddEntry(fitfunction_FR2_450,"450 GeV fit result","L");
  legFR2 -> AddEntry(fitfunction_FR2_700,"700 GeV fit result","L");
  legFR2 -> Draw("SAME");
  */
  /*TFitResultPtr r_FR2 = hist_vr_3b_FR2->Fit(fitfunction_FR2,"RS");

  int nbinsin_FR2 = 0;
  int xlowin_FR2 = 0;
  int xhighin_FR2 = 0;
  nbinsin_FR2 = hist_vr_3b_FR2 -> GetNbinsX();
  xlowin_FR2 = hist_vr_3b_FR2 -> GetBinLowEdge(1);
  xhighin_FR2 = hist_vr_3b_FR2 -> GetBinLowEdge(nbinsin_FR2) + hist_vr_3b_FR2 -> GetBinWidth(nbinsin_FR2);
  cout << "nbins, low, high: " << nbinsin_FR2 << " " << xlowin_FR2 << " " << xhighin_FR2 << endl;
  TH1F* fiterrhist_FR2 = new TH1F("fitterrhist_FR2","Histogram with fit error band",nbinsin_FR2,xlowin_FR2,xhighin_FR2);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(fiterrhist_FR2);
  fiterrhist_FR2 -> SetStats(kFALSE);
  fiterrhist_FR2 -> SetFillColor(2);
  fiterrhist_FR2 -> SetLineColor(2);
  fiterrhist_FR2 -> SetMarkerSize(0);
  fiterrhist_FR2 -> Draw("e3 SAME");
  cout << "chi2/ndf = " << r_FR2->Chi2() << "/" << r_FR2->Ndf() << " = " << r_FR2->Chi2()/r_FR2->Ndf() << ", prob = " << r_FR2->Prob() << endl;*/
  
  /*
  out_can_3b_FR2 -> Update();
  out_can_3b_FR2 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR2_Feb12-21.pdf");
  out_can_3b_FR2 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR2_Feb12-21.root");
    
  //FR 3: canvas, fitfunction, fit
  TCanvas* out_can_3b_FR3 = style.MakeCanvas("out_can_3b_FR3", "", 700,700);
  out_can_3b_FR3 -> cd();
  hist_vr_3b_FR3 -> Draw();

  //TF1* fitfunction_FR3 = new TF1("fitfunction_FR3","[0]*erf([2]*(x-[1]))*(1+[3]*x)",390,1270);//ext erf
  TF1* fitfunction_FR3 = new TF1("fitfunction_FR3","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",390,1270);//ext mod logistic
  fitfunction_FR3 -> SetLineColor(kRed);
  fitfunction_FR3 -> SetParameter(0,0.15);
  fitfunction_FR3 -> FixParameter(1,0.0068);//steepness
  fitfunction_FR3 -> FixParameter(2,250);//offset
  fitfunction_FR3 -> FixParameter(3,1.53);//alpha
  fitfunction_FR3 -> FixParameter(4,-0.0002);//linslope
  hist_vr_3b_FR3 -> Fit(fitfunction_FR3,"R");

  TF1* fitfunction_FR3_800 = new TF1("fitfunction_FR3_800","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",390,1270);//ext mod logistic
  fitfunction_FR3_800 -> SetLineColor(kMagenta);
  fitfunction_FR3_800 -> SetParameter(0,0.15);
  fitfunction_FR3_800 -> FixParameter(1,0.0055);//steepness
  fitfunction_FR3_800 -> FixParameter(2,250);//offset
  fitfunction_FR3_800 -> FixParameter(3,1.53);//alpha
  fitfunction_FR3_800 -> FixParameter(4,-0.0002);//linslope
  hist_vr_3b_FR3 -> Fit(fitfunction_FR3_800,"R");

  TF1* fitfunction_FR3_900 = new TF1("fitfunction_FR3_900","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",390,1270);//ext mod logistic
  fitfunction_FR3_900 -> SetLineColor(kViolet-5);
  fitfunction_FR3_900 -> SetParameter(0,0.15);
  fitfunction_FR3_900 -> FixParameter(1,0.0040);//steepness
  fitfunction_FR3_900 -> FixParameter(2,250);//offset
  fitfunction_FR3_900 -> FixParameter(3,1.61);//alpha
  fitfunction_FR3_900 -> FixParameter(4,-0.0002);//linslope
  hist_vr_3b_FR3 -> Fit(fitfunction_FR3_900,"R");

  TF1* fitfunction_FR3_1000 = new TF1("fitfunction_FR3_1000","[0]*(1+[3]*TMath::Exp(-[1]*(x-[2])))/(1+TMath::Exp(-[1]*(x-[2])))*(1-[4]*x)",390,1270);//ext mod logistic
  fitfunction_FR3_1000 -> SetLineColor(kCyan);
  fitfunction_FR3_1000 -> SetParameter(0,0.15);
  fitfunction_FR3_1000 -> FixParameter(1,0.0100);//steepness
  fitfunction_FR3_1000 -> FixParameter(2,250);//offset
  fitfunction_FR3_1000 -> FixParameter(3,1.21);//alpha
  fitfunction_FR3_1000 -> FixParameter(4,0.00005);//linslope
  hist_vr_3b_FR3 -> Fit(fitfunction_FR3_1000,"R");

  fitfunction_FR3 -> Draw("SAME");
  fitfunction_FR3_800 -> Draw("SAME");
  fitfunction_FR3_900 -> Draw("SAME");
  fitfunction_FR3_1000 -> Draw("SAME");

  TLegend* legFR3 = new TLegend(0.2,0.7,0.95,0.9);
  style.SetLegendStyle(legFR3);
  legFR3 -> SetNColumns(2);
  legFR3 -> AddEntry(hist_vr_3b_FR3,"TF VR/CR FR 3","LP");
  legFR3 -> AddEntry(fitfunction_FR3_900,"900 GeV fit result","L");
  legFR3 -> AddEntry(fitfunction_FR3,"700 GeV fit result","L");
  legFR3 -> AddEntry(fitfunction_FR3_1000,"1000 GeV fit result","L");
  legFR3 -> AddEntry(fitfunction_FR3_800,"800 GeV fit result","L");
  legFR3 -> Draw("SAME");
  */

  //TFitResultPtr r_FR3 = hist_vr_3b_FR3->Fit(fitfunction_FR3,"RS");

  /*int nbinsin_FR3 = 0;
  int xlowin_FR3 = 0;
  int xhighin_FR3 = 0;
  nbinsin_FR3 = hist_vr_3b_FR3 -> GetNbinsX();
  xlowin_FR3 = hist_vr_3b_FR3 -> GetBinLowEdge(1);
  xhighin_FR3 = hist_vr_3b_FR3 -> GetBinLowEdge(nbinsin_FR3) + hist_vr_3b_FR3 -> GetBinWidth(nbinsin_FR3);
  cout << "nbins, low, high: " << nbinsin_FR3 << " " << xlowin_FR3 << " " << xhighin_FR3 << endl;
  TH1F* fiterrhist_FR3 = new TH1F("fitterrhist_FR3","Histogram with fit error band",nbinsin_FR3,xlowin_FR3,xhighin_FR3);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(fiterrhist_FR3);
  fiterrhist_FR3 -> SetStats(kFALSE);
  fiterrhist_FR3 -> SetFillColor(2);
  fiterrhist_FR3 -> SetLineColor(2);
  fiterrhist_FR3 -> SetMarkerSize(0);
  fiterrhist_FR3 -> Draw("e3 SAME");
  cout << "chi2/ndf = " << r_FR3->Chi2() << "/" << r_FR3->Ndf() << " = " << r_FR3->Chi2()/r_FR3->Ndf() << ", prob = " << r_FR3->Prob() << endl;*/
  
  /*
  out_can_3b_FR3 -> Update();
  out_can_3b_FR3 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR3_Feb12-21.pdf");
  out_can_3b_FR3 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR3_Feb12-21.root");
  */


  //FR 4: canvas, fitfunction, fit
  TCanvas* out_can_3b_FR4 = style.MakeCanvas("out_can_3b_FR4", "", 700,700);
  out_can_3b_FR4 -> cd();
  hist_vr_3b_FR4 -> Draw();

  TF1* fitfunction_FR4 = new TF1("fitfunction_FR4","[0]*erf([2]*(x-[1]))*(1+[3]*x)",500,2000);//ext erf
  //fitfunction_FR4 -> SetParameters(0.15,1e-3);
  fitfunction_FR4 -> SetLineColor(kRed);
  fitfunction_FR4 -> SetParameter(0,0.15);
  fitfunction_FR4 -> FixParameter(2,0.0019);//steepness
  fitfunction_FR4 -> FixParameter(1,-590);//offset
  fitfunction_FR4 -> FixParameter(3,0.00005);//linslope
  hist_vr_3b_FR4 -> Fit(fitfunction_FR4,"R");

  TF1* fitfunction_FR4_1200 = new TF1("fitfunction_FR4_1200","[0]*erf([2]*(x-[1]))*(1+[3]*x)",500,2000);//ext erf
  //fitfunction_FR4_1200 -> SetParameters(0.15,1e-3);
  fitfunction_FR4_1200 -> SetLineColor(kMagenta);
  fitfunction_FR4_1200 -> SetParameter(0,0.15);
  fitfunction_FR4_1200 -> FixParameter(2,0.0014);//steepness
  fitfunction_FR4_1200 -> FixParameter(1,-590);//offset
  fitfunction_FR4_1200 -> FixParameter(3,0.00009);//linslope
  hist_vr_3b_FR4 -> Fit(fitfunction_FR4_1200,"R");

  TF1* fitfunction_FR4_1400 = new TF1("fitfunction_FR4_1400","[0]*erf([2]*(x-[1]))*(1+[3]*x)",500,2000);//ext erf
  //fitfunction_FR4_1400 -> SetParameters(0.15,1e-3);
  fitfunction_FR4_1400 -> SetLineColor(kViolet-5);
  fitfunction_FR4_1400 -> SetParameter(0,0.15);
  fitfunction_FR4_1400 -> FixParameter(2,0.0013);//steepness
  fitfunction_FR4_1400 -> FixParameter(1,-590);//offset
  fitfunction_FR4_1400 -> FixParameter(3,0.00009);//linslope
  hist_vr_3b_FR4 -> Fit(fitfunction_FR4_1400,"R");

  TF1* fitfunction_FR4_1600 = new TF1("fitfunction_FR4_1600","[0]*erf([2]*(x-[1]))*(1+[3]*x)",500,2000);//ext erf
  //fitfunction_FR4_1600 -> SetParameters(0.15,1e-3);
  fitfunction_FR4_1600 -> SetLineColor(kCyan);
  fitfunction_FR4_1600 -> SetParameter(0,0.15);
  fitfunction_FR4_1600 -> FixParameter(2,0.012);//steepness
  fitfunction_FR4_1600 -> FixParameter(1,-590);//offset
  fitfunction_FR4_1600 -> FixParameter(3,0.00003);//linslope
  hist_vr_3b_FR4 -> Fit(fitfunction_FR4_1600,"R");

  fitfunction_FR4 -> Draw("SAME");
  fitfunction_FR4_1200 -> Draw("SAME");
  fitfunction_FR4_1400 -> Draw("SAME");
  fitfunction_FR4_1600 -> Draw("SAME");

  TLegend* legFR4 = new TLegend(0.2,0.7,0.95,0.9);
  style.SetLegendStyle(legFR4);
  legFR4 -> SetNColumns(2);
  legFR4 -> AddEntry(hist_vr_3b_FR4,"TF VR/CR FR 4","LP");
  legFR4 -> AddEntry(fitfunction_FR4_1400,"1400 GeV fit result","L");
  legFR4 -> AddEntry(fitfunction_FR4,"1000 GeV fit result","L");
  legFR4 -> AddEntry(fitfunction_FR4_1600,"1600 GeV fit result","L");
  legFR4 -> AddEntry(fitfunction_FR4_1200,"1200 GeV fit result","L");
  legFR4 -> Draw("SAME");

  /*TFitResultPtr r_FR4 = hist_vr_3b_FR4->Fit(fitfunction_FR4,"RS");

  int nbinsin_FR4 = 0;
  int xlowin_FR4 = 0;
  int xhighin_FR4 = 0;
  nbinsin_FR4 = hist_vr_3b_FR4 -> GetNbinsX();
  xlowin_FR4 = hist_vr_3b_FR4 -> GetBinLowEdge(1);
  xhighin_FR4 = hist_vr_3b_FR4 -> GetBinLowEdge(nbinsin_FR4) + hist_vr_3b_FR4 -> GetBinWidth(nbinsin_FR4);
  cout << "nbins, low, high: " << nbinsin_FR4 << " " << xlowin_FR4 << " " << xhighin_FR4 << endl;
  TH1F* fiterrhist_FR4 = new TH1F("fitterrhist_FR4","Histogram with fit error band",nbinsin_FR4,xlowin_FR4,xhighin_FR4);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(fiterrhist_FR4);
  fiterrhist_FR4 -> SetStats(kFALSE);
  fiterrhist_FR4 -> SetFillColor(2);
  fiterrhist_FR4 -> SetLineColor(2);
  fiterrhist_FR4 -> SetMarkerSize(0);
  fiterrhist_FR4 -> Draw("e3 SAME");
  cout << "chi2/ndf = " << r_FR4->Chi2() << "/" << r_FR4->Ndf() << " = " << r_FR4->Chi2()/r_FR4->Ndf() << ", prob = " << r_FR4->Prob() << endl;*/
  out_can_3b_FR4 -> Update();
  out_can_3b_FR4 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR4_Feb16-21.pdf");
  out_can_3b_FR4 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/TF_vs_FitResultsCombine_FR4_Feb16-21.root");
  
  
  //saving
  /*out_can_3b_FR1 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR1_eml_Oct29-20_dataMay11-20.pdf");
  out_can_3b_FR1 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR1_eml_Oct29-20_dataMay11-20.root");  
  hist_vr_3b_FR1 -> Write();
  out_cr_3b_FR1 -> Write();
  out_vr_3b_FR1 -> Write();*/
  /*out_can_3b_FR2 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR2_eml_Nov09-20_dataMay11-20.pdf");
  out_can_3b_FR2 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR2_eml_Nov09-20_dataMay11-20.root");  
  hist_vr_3b_FR2 -> Write();
  out_cr_3b_FR2 -> Write();
  out_vr_3b_FR2 -> Write();*/
  //out_can_3b_FR3 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR3_eml_Nov19-20_dataMay11-20.pdf");
  //out_can_3b_FR3 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR3_eml_Nov19-20_dataMay11-20.root");  
  //hist_vr_3b_FR3 -> Write();
  //out_cr_3b_FR3 -> Write();
  //out_vr_3b_FR3 -> Write();
  /*out_can_3b_FR4 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR4_exterf_Nov19-20_dataMay11-20.pdf");
  out_can_3b_FR4 -> SaveAs("Outputdata/m12_ratio_CR-VR_cuts/fit_TFVR_FR4_exterf_Nov19-20_dataMay11-20.root");  
  hist_vr_3b_FR4 -> Write();
  out_cr_3b_FR4 -> Write();
  out_vr_3b_FR4 -> Write();
  */
  return 0;
}

  //TF1* fitfunction = new TF1("fitfunction","[0]*erf([2]*(x-[1]))*(1+[3]*x)",200,2000);//erf times linear decrease at higher masses
  //TF1* fitfunction = new TF1("fitfunction","[0]*erf([2]*(x-[1]))",200,500);//simple erf
  //TF1* fitfunction = new TF1("fitfunction","[0]*x+[1]",500,2000);//ax+b
  //TF1* fitfunction = new TF1("fitfunction","[0]",260,785);//a
  //TF1* fitfunction = new TF1("fitfunction","[0]*x*x+[1]*x+[2]",200,500);//ax^2+bx+c
  //TF1* fitfunction = new TF1("fitfunction","[0]/(1+TMath::Exp(-[1]*(x-[2])))",200,500);//logistic function
