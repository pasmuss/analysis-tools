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

int CompLONLO( string var_, string region_, string mass_, string xtitle_, float xlow_, float xhigh_, float ylow_, float yhigh_, float yRlow_, float yRhigh_, int rebinning_)
{
  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  string var = var_;
  string region = region_;
  string xtitle = xtitle_;
  string mass = mass_;
  
  const float xlow  = xlow_;
  const float xhigh = xhigh_;
  const float ylow  = ylow_;
  const float yhigh = yhigh_;
  const float yRlow  = yRlow_;
  const float yRhigh = yRhigh_;
  const int rebinning = rebinning_;
  if ( (var == "m12_csv") || (var == "m12") || (var == "pt_0_csv") || (var == "pt_0") || (var == "pt_1_csv") || (var == "pt_1") || (var == "pt_2_csv") || (var == "pt_2") || (var == "pt_3_csv") || (var == "pt_3") ) int rebinning = rebinning;

  TFile * file_lo = new TFile( ("rootfiles/mcsig/mc-sig-"+mass+ "-deep-"+region+".root").c_str(),"READ");
  TFile * file_nlo = new TFile( ("rootfiles/mcsig/mc-sig-"+mass+"-NLO-deep-"+region+".root").c_str(),"READ");

  TH1F * hist_lo = (TH1F*)file_lo->Get(var.c_str());
  TH1F * hist_nlo = (TH1F*)file_nlo->Get(var.c_str());

  float startstep = hist_lo->GetBinWidth(0);
  float binning = startstep * rebinning;
  hist_lo -> Rebin(rebinning);
  hist_nlo -> Rebin(rebinning);
  string binning_str = to_string(binning);
  string ytitle = ("Entries / " + binning_str).c_str();

  if ( (var == "m12_csv") || (var == "m12") || (var == "pt_0_csv") || (var == "pt_0") || (var == "pt_1_csv") || (var == "pt_1") || (var == "pt_2_csv") || (var == "pt_2") || (var == "pt_3_csv") || (var == "pt_3") ){
    int ibinning = (int)binning;
    string ibinning_str = to_string(ibinning);
    ytitle = ("Entries / " + ibinning_str + " GeV").c_str();
  }

  std::vector<double> lines1 = {0, 0.5, 1.0, 1.5, 2.0};

  float normlo = hist_lo->Integral();
  float normnlo = hist_nlo->Integral();
 
  hist_lo -> Scale(1/normlo);
  hist_nlo -> Scale(1/normnlo);

  TCanvas* c1 = style.MakeCanvas("c1","",700,700);
  c1 -> SetLogy();
  
  style.InitHist(hist_lo, xtitle.c_str(), ytitle.c_str(),kBlue,0);
  style.InitHist(hist_nlo, xtitle.c_str(), ytitle.c_str(),kRed,0);
  
  //Ratio plot
  auto rp = new TRatioPlot(hist_nlo,hist_lo);
  rp -> SetH1DrawOpt("E");
  rp -> SetH2DrawOpt("E");
  rp -> SetGridlines(lines1);
  rp -> Draw();
  
  rp -> GetLowerRefGraph() -> SetLineWidth(2);
  rp -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp -> SetRightMargin(0.05);
  rp -> SetUpTopMargin(0.08); // 0.03                                                                                                                                                                       
  rp -> SetLeftMargin(0.13);
  rp -> SetSeparationMargin(0.07);
  rp -> SetLowBottomMargin(0.45);
  rp -> SetLowTopMargin(0.0);

  rp -> GetLowerRefYaxis() -> SetTitle( "NLO/LO" );
  rp -> GetLowerRefYaxis() -> SetRangeUser(yRlow,yRhigh);
  rp -> GetUpperRefYaxis() -> SetRangeUser(ylow,yhigh);
  rp -> GetUpperRefXaxis() -> SetRangeUser(xlow,xhigh);

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
 
  TLegend* leg = new TLegend(0.56,0.65,0.86,0.83);
  style.SetLegendStyle(leg);
  leg -> AddEntry(hist_lo,("LO "+mass+" GeV, "+region).c_str(),"L");
  leg -> AddEntry(hist_nlo,("NLO "+mass+" GeV, "+region).c_str(),"L");
  leg -> SetTextSize(0.05);
  leg -> Draw("SAME");
  
  //CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c1 -> Update();
  c1 -> SaveAs(("Outputdata_LO_NLO/Comp_" + var + "-LO_NLO-" + region + "_" + mass + ".pdf").c_str());

  return 0;
}
