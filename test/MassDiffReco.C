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

int MassDiffReco( string era_, string var_, string region_ , string xtitle_, float xlow_ ,float xhigh_ , float ylow_ ,float yhigh_ , float yRlow_ ,float yRhigh_  )
{

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  //setTDRStyle();
  
  std::string era = era_;
  std::string var = var_;
  std::string region = region_;
  std::string xtitle = xtitle_;
  
  const float xlow  = xlow_;
  const float xhigh = xhigh_;
  const float ylow  = ylow_;
  const float yhigh = yhigh_;
  const float yRlow  = yRlow_;
  const float yRhigh = yRhigh_;

  float lumi = 36.0; // all 2017 C to F

  if ( era_ == "C"   ) lumi = 9.58;
  if ( era_ == "D"   ) lumi = 4.22;
  if ( era_ == "E"   ) lumi = 8.85;
  if ( era_ == "F"   ) lumi = 13.5;
  if ( era_ == "CD"  ) lumi = 13.8;
  if ( era_ == "CDE" ) lumi = 22.6;
 

  TFile * f1 = new TFile( ("rootfiles/prompt/prompt-"+era_+"-deep-"+region+".root").c_str(),"READ");//prompt
  TFile * f2 = new TFile( ("rootfiles/rereco/rereco-"+era_+"-deep-"+region+".root").c_str(),"READ");//rereco

  TH1F * hist_prompt = (TH1F*)f1->Get(var.c_str());
  TH1F * hist_rereco = (TH1F*)f2->Get(var.c_str());

  std::vector<double> lines1 = {0.5, 1.0, 1.5, 2.0, 2.5};
  std::vector<double> linespt = {0.5, 1.0, 1.5, 2.0, 2.5};
  //std::vector<double> linesF = {1.0, 2.0, 3.0, 4.0};

  TCanvas* c1 = style.MakeCanvas("c1","",700,700);
  if ( (var_ == "m12_csv") || (var_ == "m12") )
    {
      c1 -> SetLogy();
      style.InitHist(hist_prompt, xtitle.c_str(),"Entries / 60 GeV ",kBlue,0);
      hist_prompt -> Rebin(3);
      style.InitHist(hist_rereco, xtitle.c_str(),"Entries / 60 GeV ",kRed,0);
      hist_rereco -> Rebin(3);
    }
  else if ( (var_ == "pt_0_csv") || (var_ == "pt_0") || (var_ == "pt_1_csv") || (var_ == "pt_1") )
    {
      c1 -> SetLogy();
      style.InitHist(hist_prompt, xtitle.c_str(),"Entries / 50 GeV ",kBlue,0);
      hist_prompt -> Rebin(5);
      style.InitHist(hist_rereco, xtitle.c_str(),"Entries / 50 GeV ",kRed,0);
      hist_rereco -> Rebin(5);
    }
    else if ( (var_ == "deepcsvbtag_0_csv") || (var_ == "deepcsvbtag_0") || (var_ == "deepcsvbtag_1_csv") || (var_ == "deepcsvbtag_1") )
    {
      c1 -> SetLogy();
      style.InitHist(hist_prompt, xtitle.c_str(),"Entries / 0.01 ",kBlue,0);
      hist_prompt -> Rebin(5);
      style.InitHist(hist_rereco, xtitle.c_str(),"Entries / 0.01 ",kRed,0);
      hist_rereco -> Rebin(5);
    }
    else if ( (var_ == "eta_0") || (var_ == "eta_1") || (var_ == "eta_0_csv") || (var_ == "eta_1_csv") ){
      c1 -> SetLogy();
      style.InitHist(hist_prompt, xtitle.c_str(),"Entries / 0.1 ",kBlue,0);
      style.InitHist(hist_rereco, xtitle.c_str(),"Entries / 0.1 ",kRed,0);
    }
    else if ( (var_ == "phi_0") || (var_ == "phi_1") || (var_ == "phi_0_csv") || (var_ == "phi_1_csv") ){
      style.InitHist(hist_prompt, xtitle.c_str(),"Entries / 0.08 ",kBlue,0);
      style.InitHist(hist_rereco, xtitle.c_str(),"Entries / 0.08 ",kRed,0);
      //TGaxis::SetMaxDigits(3);
    }
  else
    {
      style.InitHist(hist_prompt, xtitle.c_str(),"Entries / 20 GeV ",kBlue,0);
      style.InitHist(hist_rereco, xtitle.c_str(),"Entries / 20 GeV ",kRed,0);
    }

  //Ratio plot
  auto rp = new TRatioPlot(hist_rereco,hist_prompt);
  rp -> SetH1DrawOpt("E");
  rp -> SetH2DrawOpt("E");
  if ( (var_ == "pt_0_csv") || (var_ == "pt_0") || (var_ == "pt_1_csv") || (var_ == "pt_1") )
    rp -> SetGridlines(linespt);
  else rp -> SetGridlines(lines1);
  rp -> Draw();
  
  rp -> GetLowerRefGraph() -> SetLineWidth(2);
  rp -> GetLowerRefGraph() -> SetMarkerSize(1);
  
  rp -> SetRightMargin(0.05);
  rp -> SetUpTopMargin(0.08); // 0.03
  rp -> SetLeftMargin(0.13);
  rp -> SetSeparationMargin(0.07);
  rp -> SetLowBottomMargin(0.4); 
  rp -> SetLowTopMargin(0.0);
  
  rp -> GetLowerRefYaxis() -> SetTitle("ReReco / Prompt");
  rp -> GetLowerRefYaxis() -> SetRangeUser(yRlow,yRhigh);
  rp -> GetUpperRefYaxis() -> SetRangeUser(ylow,yhigh);
  rp -> GetUpperRefXaxis() -> SetRangeUser(xlow,xhigh);

  //TGaxis::SetMaxDigits(3);
    
  rp -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp -> GetUpperRefYaxis() -> SetTitleSize(0.035);
  rp -> GetUpperRefYaxis() -> SetTitleOffset(1.7);
  rp -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp -> GetLowYaxis() -> SetNdivisions(505);
  rp -> GetUpperPad() -> cd();
  
  TLegend* leg = new TLegend(0.37,0.6,0.78,0.9);
  style.SetLegendStyle(leg);
  if (era_ == "CDEF"){
    leg -> AddEntry(hist_prompt,"2017 Prompt","L");
    leg -> AddEntry(hist_rereco,"2017 ReReco","L");
  }
  else if (era_ == "CDE"){
    leg -> AddEntry(hist_prompt,"Eras C to E, Prompt","L");
    leg -> AddEntry(hist_rereco,"Eras C to E, ReReco","L");
  }
  else{
    leg -> AddEntry(hist_prompt,("Era "+era+ ", Prompt").c_str(),"L");
    leg -> AddEntry(hist_rereco,("Era "+era+ ", ReReco").c_str(),"L");
  }
  leg -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c1 -> Update();
  c1 -> SaveAs(("Outputdata/CompReco_"+ var_+ "-" + era_ + "-" + region +".pdf").c_str());

  //pad1 -> SetLogy();
  //c1 -> SaveAs(("PLOTS/CompReco"+ era_ + "Log.png").c_str());

  return 0;
}
