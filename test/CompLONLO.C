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

int CompLONLO( string var_, string region_ , string xtitle_, float xlow_ ,float xhigh_ , float ylow_ ,float yhigh_ , /*float yRlow_ ,float yRhigh_, */float rebinning_)
{

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  //setTDRStyle();

  std::string var = var_;
  std::string region = region_;
  std::string xtitle = xtitle_;
  
  const float xlow  = xlow_;
  const float xhigh = xhigh_;
  const float ylow  = ylow_;
  const float yhigh = yhigh_;
  //const float yRlow  = yRlow_;
  //const float yRhigh = yRhigh_;
  const float rebinning = rebinning_;
  if ( (var_ == "m12_csv") || (var_ == "m12") || (var_ == "pt_0_csv") || (var_ == "pt_0") || (var_ == "pt_1_csv") || (var_ == "pt_1") || (var_ == "pt_2_csv") || (var_ == "pt_2") || (var_ == "pt_3_csv") || (var_ == "pt_3") ) int rebinning = rebinning;

  TFile * lo350 = new TFile( ("rootfiles/mcsig/mc-sig-350-deep-"+region+".root").c_str(),"READ");//LO 350
  TFile * nlo350 = new TFile( ("rootfiles/mcsig/mc-sig-350-NLO-deep-"+region+".root").c_str(),"READ");//NLO 350
  TFile * lo600 = new TFile( ("rootfiles/mcsig/mc-sig-600-deep-"+region+".root").c_str(),"READ");//LO 600
  TFile * nlo600 = new TFile( ("rootfiles/mcsig/mc-sig-600-NLO-deep-"+region+".root").c_str(),"READ");//NLO 600
  TFile * lo1200 = new TFile( ("rootfiles/mcsig/mc-sig-1200-deep-"+region+".root").c_str(),"READ");//LO 1200
  TFile * nlo1200 = new TFile( ("rootfiles/mcsig/mc-sig-1200-NLO-deep-"+region+".root").c_str(),"READ");//NLO 1200

  TH1F * hist_lo350 = (TH1F*)lo350->Get(var.c_str());
  TH1F * hist_nlo350 = (TH1F*)nlo350->Get(var.c_str());
  TH1F * hist_lo600 = (TH1F*)lo600->Get(var.c_str());
  TH1F * hist_nlo600 = (TH1F*)nlo600->Get(var.c_str());
  TH1F * hist_lo1200 = (TH1F*)lo1200->Get(var.c_str());
  TH1F * hist_nlo1200 = (TH1F*)nlo1200->Get(var.c_str());

  float startstep = hist_lo350->GetBinWidth(0);
  float binning = startstep * rebinning;
  if ( (var_ == "m12_csv") || (var_ == "m12") || (var_ == "pt_0_csv") || (var_ == "pt_0") || (var_ == "pt_1_csv") || (var_ == "pt_1") || (var_ == "pt_2_csv") || (var_ == "pt_2") || (var_ == "pt_3_csv") || (var_ == "pt_3") ){
    int startstep = hist_lo350->GetBinWidth(0);
    int binning = startstep * rebinning;
  }
  string binning_str = to_string(binning);
  string ytitle = ("Entries / " + binning_str).c_str();
  if ( (var_ == "m12_csv") || (var_ == "m12") || (var_ == "pt_0_csv") || (var_ == "pt_0") || (var_ == "pt_1_csv") || (var_ == "pt_1") || (var_ == "pt_2_csv") || (var_ == "pt_2") || (var_ == "pt_3_csv") || (var_ == "pt_3") ) string ytitle = ("Entries / " + binning_str + " GeV").c_str();

  std::vector<double> lines1 = {0, 0.5, 1.0, 1.5, 2.0};

  TCanvas* c1 = style.MakeCanvas("c1","",700,700);
  c1 -> SetLogy();
  
  style.InitHist(hist_lo350, xtitle.c_str(), ytitle.c_str(),kBlue,0);
  style.InitHist(hist_nlo350, xtitle.c_str(), ytitle.c_str(),kRed,0);
  style.InitHist(hist_lo600, xtitle.c_str(), ytitle.c_str(),kCyan,0);
  style.InitHist(hist_nlo600, xtitle.c_str(), ytitle.c_str(),kMagenta,0);
  style.InitHist(hist_lo1200, xtitle.c_str(), ytitle.c_str(),kGreen,0);
  style.InitHist(hist_nlo1200, xtitle.c_str(), ytitle.c_str(),kViolet-2,0);
  
  hist_lo350 -> Draw();
  hist_lo350 -> GetXaxis() -> SetRangeUser(xlow,xhigh);
  hist_lo350 -> GetYaxis() -> SetRangeUser(ylow,yhigh);
  hist_lo350 -> GetXaxis() -> SetNdivisions(505);  

  hist_nlo350 -> Draw("SAME");
  hist_lo600 -> Draw("SAME");
  hist_nlo600 -> Draw("SAME");
  hist_lo1200 -> Draw("SAME");
  hist_nlo1200 -> Draw("SAME");

  /*
  //Ratio plot 350
  auto rp350 = new TRatioPlot(hist_nlo350,hist_lo350);
  rp350 -> SetH1DrawOpt("E");
  rp350 -> SetH2DrawOpt("E");
  rp350 -> SetGridlines(lines1);
  rp350 -> Draw();
  
  rp350 -> GetLowerRefGraph() -> SetLineWidth(2);
  rp350 -> GetLowerRefGraph() -> SetLineColor(kBlue);
  rp350 -> GetLowerRefGraph() -> SetMarkerSize(1);
  
  rp350 -> SetRightMargin(0.05);
  rp350 -> SetUpTopMargin(0.08); // 0.03
  rp350 -> SetLeftMargin(0.13);
  rp350 -> SetSeparationMargin(0.07);
  rp350 -> SetLowBottomMargin(0.4); 
  rp350 -> SetLowTopMargin(0.0);
  
  rp350 -> GetLowerRefYaxis() -> SetTitle("NLO/LO");
  rp350 -> GetLowerRefYaxis() -> SetRangeUser(yRlow,yRhigh);
  rp350 -> GetUpperRefYaxis() -> SetRangeUser(ylow,yhigh);
  rp350 -> GetUpperRefXaxis() -> SetRangeUser(xlow,xhigh);

  //TGaxis::SetMaxDigits(3);
    
  rp350 -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp350 -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp350 -> GetUpperRefYaxis() -> SetTitleSize(0.035);
  rp350 -> GetUpperRefYaxis() -> SetTitleOffset(1.7);
  rp350 -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp350 -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp350 -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp350 -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp350 -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp350 -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp350 -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp350 -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp350 -> GetLowYaxis() -> SetNdivisions(505);
  rp350 -> GetUpperPad() -> cd();
  */
  //Ratio plot 600
  /*auto rp600 = new TRatioPlot(hist_nlo600,hist_lo600);
  rp600 -> SetH1DrawOpt("E");
  rp600 -> SetH2DrawOpt("E");
  //rp600 -> SetGridlines(lines1);
  rp600 -> Draw("SAME");
  
  rp600 -> GetLowerRefGraph() -> SetLineWidth(2);
  rp600 -> GetLowerRefGraph() -> SetLineColor(kCyan);
  rp600 -> GetLowerRefGraph() -> SetMarkerSize(1);*/
  
  /*rp600 -> SetRightMargin(0.05);
  rp600 -> SetUpTopMargin(0.08); // 0.03
  rp600 -> SetLeftMargin(0.13);
  rp600 -> SetSeparationMargin(0.07);
  rp600 -> SetLowBottomMargin(0.4); 
  rp600 -> SetLowTopMargin(0.0);
  
  rp600 -> GetLowerRefYaxis() -> SetTitle("NLO/LO");
  rp600 -> GetLowerRefYaxis() -> SetRangeUser(yRlow,yRhigh);
  rp600 -> GetUpperRefYaxis() -> SetRangeUser(ylow,yhigh);
  rp600 -> GetUpperRefXaxis() -> SetRangeUser(xlow,xhigh);*/

  //TGaxis::SetMaxDigits(3);
    
  /*rp600 -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp600 -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp600 -> GetUpperRefYaxis() -> SetTitleSize(0.035);
  rp600 -> GetUpperRefYaxis() -> SetTitleOffset(1.7);
  rp600 -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp600 -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp600 -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp600 -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp600 -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp600 -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp600 -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp600 -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp600 -> GetLowYaxis() -> SetNdivisions(505);
  rp600 -> GetUpperPad() -> cd();*/

  //Ratio plot 1200
  /*  auto rp1200 = new TRatioPlot(hist_nlo1200,hist_lo1200);
  rp1200 -> SetH1DrawOpt("E");
  rp1200 -> SetH2DrawOpt("E");
  //rp1200 -> SetGridlines(lines1);
  rp1200 -> Draw("SAME");
  
  rp1200 -> GetLowerRefGraph() -> SetLineWidth(2);
  rp1200 -> GetLowerRefGraph() -> SetLineColor(kGreen);
  rp1200 -> GetLowerRefGraph() -> SetMarkerSize(1);
  */
  /*rp1200 -> SetRightMargin(0.05);
  rp1200 -> SetUpTopMargin(0.08); // 0.03
  rp1200 -> SetLeftMargin(0.13);
  rp1200 -> SetSeparationMargin(0.07);
  rp1200 -> SetLowBottomMargin(0.4); 
  rp1200 -> SetLowTopMargin(0.0);
  
  rp1200 -> GetLowerRefYaxis() -> SetTitle("NLO/LO");
  rp1200 -> GetLowerRefYaxis() -> SetRangeUser(yRlow,yRhigh);
  rp1200 -> GetUpperRefYaxis() -> SetRangeUser(ylow,yhigh);
  rp1200 -> GetUpperRefXaxis() -> SetRangeUser(xlow,xhigh);*/

  //TGaxis::SetMaxDigits(3);
    
  /*rp1200 -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp1200 -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp1200 -> GetUpperRefYaxis() -> SetTitleSize(0.035);
  rp1200 -> GetUpperRefYaxis() -> SetTitleOffset(1.7);
  rp1200 -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp1200 -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp1200 -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp1200 -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp1200 -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp1200 -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp1200 -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp1200 -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp1200 -> GetLowYaxis() -> SetNdivisions(505);*/
  //rp1200 -> GetUpperPad() -> cd();
  
  TLegend* leg = new TLegend(0.406,0.575,0.706,0.876);
  style.SetLegendStyle(leg);
  leg -> AddEntry(hist_lo350,("LO 350 GeV, "+region).c_str(),"L");
  leg -> AddEntry(hist_nlo350,("NLO 350 GeV, "+region).c_str(),"L");
  leg -> AddEntry(hist_lo600,("LO 600 GeV, "+region).c_str(),"L");
  leg -> AddEntry(hist_nlo600,("NLO 600 GeV, "+region).c_str(),"L");
  leg -> AddEntry(hist_lo1200,("LO 1200 GeV, "+region).c_str(),"L");
  leg -> AddEntry(hist_nlo1200,("NLO 1200 GeV, "+region).c_str(),"L");

  leg -> Draw("SAME");
  
  //CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c1 -> Update();
  c1 -> SaveAs(("Outputdata_LO_NLO/Comp_"+ var_+ "-LO_NLO-" + region_ + ".pdf").c_str());

  return 0;
}
