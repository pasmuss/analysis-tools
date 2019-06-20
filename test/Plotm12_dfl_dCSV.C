#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TAttAxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"
#include "tdrstyle.C"


void Plotm12_dfl_dCSV(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);
  
  ///
  /// Files
  ///
  TFile* file_dcsv = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_incl_prescale/rereco/rereco-CDEF-deep-CR.root","READ");
  TFile* file_dfl = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_prescale_4jnn/rereco/rereco-CDEF-deep-CR.root","READ");
  
  ///
  /// Mass histograms
  ///
  TH1F* hist_m_dcsv = (TH1F*)file_dcsv -> Get("m12_csv");
  TH1F* hist_m_dfl = (TH1F*)file_dfl -> Get("m12_csv");


  TCanvas* can = style.MakeCanvas("can","masses, after cuts, CR",700,700);
  can -> SetLogy();
  style.InitHist(hist_m_dcsv,"m_{12} [GeV]","Entries / 20 GeV",kBlue,0);
  //hist_m_dcsv -> GetYaxis() -> SetRangeUser(0.1,20000);
  //hist_m_dcsv -> GetXaxis() -> SetRangeUser(200,3000);
  //hist_m_dcsv -> GetXaxis() -> SetNdivisions(505);
  //hist_m_dcsv -> GetYaxis() -> SetTitleOffset(1.2);
  //  hist_m_dcsv -> SetMarkerSize(1.1);
  //hist_m_dcsv -> Draw();
  style.InitHist(hist_m_dfl,"m_{12} [GeV]","Entries / 20 GeV",kRed,0);
  //hist_m_dfl -> Draw("SAME");

  std::vector<double> lines = {5.0,10.0,15.0};

  auto rp = new TRatioPlot(hist_m_dfl,hist_m_dcsv);
  rp -> SetH1DrawOpt("E");
  rp -> SetH2DrawOpt("E");
  rp -> SetGridlines(lines);
  rp -> Draw();

  rp -> GetLowerRefGraph() -> SetMarkerSize(1);
  rp -> GetLowerRefGraph() -> SetLineWidth(1);

  rp -> GetXaxis() -> SetNdivisions(505);
  rp -> GetLowYaxis() -> SetNdivisions(505);
  rp -> GetUpperRefYaxis() -> SetTitleOffset(1.05);
  rp -> GetLowerRefXaxis() -> SetTitleOffset(1.0);

  rp -> GetLowerRefYaxis() -> SetRangeUser(0.01,15.0);
  rp -> GetLowerRefYaxis() -> SetTitle("#splitline{bbnbnb/}{bbnbb}");
  rp -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp -> GetLowerRefYaxis() -> SetTitleOffset(1.6);
  rp -> GetLowerRefXaxis() -> SetRangeUser(200,3000);
  rp -> GetUpperRefXaxis() -> SetRangeUser(200,3000);
  
  rp -> SetUpTopMargin(0.01);
  rp -> SetLowBottomMargin(0.4);
  rp -> SetRightMargin(0.05);
  rp -> SetLeftMargin(0.12);
  rp -> SetSeparationMargin(0.02);

  TLegend* leg = new TLegend(0.6,0.63,0.9,0.89);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_m_dfl,"m_{12} bbnbnb","L");
  leg -> AddEntry(hist_m_dcsv,"m_{12} bbnbb","L");

  rp -> GetUpperPad() -> cd();

  leg -> Draw();

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/comp_m12_csv_dfl_bbnbb_bbnbnb_4j.pdf");
}
