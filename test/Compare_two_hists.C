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


void Compare_two_hists(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);
  
  ///
  /// Files (ratio is taken file2/file1 in the end)
  ///
  TFile* file_1 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_btagcuts_notrigger-onlyofflbtagsf_Feb13-20/mcbg/MCbg-QCD-m12_aac-2017CDEF-CR-3j.root","READ");
  TFile* file_2 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_btagweights_notriggernosf_Feb13-20/mcbg/MCbg-QCD-m12_aac-2017CDEF-CR-3j.root","READ");
  
  ///
  /// histograms
  ///
  TH1F* hist_1 = (TH1F*)file_1 -> Get("hist_output_ges");
  TH1F* hist_2 = (TH1F*)file_2 -> Get("hist_output_ges");

  hist_1 -> Rebin(1);
  hist_2 -> Rebin(1);

  int binwidth_1 = hist_1 -> GetBinWidth(1);
  int binwidth_2 = hist_2 -> GetBinWidth(1);
  int rebin = binwidth_1/binwidth_2;
  hist_2 -> Rebin(rebin);

  cout << "rebinning done" << endl;

  TCanvas* can = style.MakeCanvas("can","CR 3b vs. 4b",700,700);
  can -> SetLogy();
  style.InitHist(hist_1,"m_{12} [GeV]",("Entries / " + to_string(binwidth_1) + "GeV").c_str(),kBlue,0);
  style.InitHist(hist_2,"m_{12} [GeV]",("Entries / " + to_string(binwidth_1) + "GeV").c_str(),kRed,0);

  std::vector<double> lines = {0.5,1.0,1.5,2.0};

  auto rp = new TRatioPlot(hist_2,hist_1);
  rp -> SetH1DrawOpt("E");
  rp -> SetH2DrawOpt("E");
  rp -> SetGridlines(lines);

  rp -> Draw();

  cout << "rp done" << endl;

  rp -> GetLowerRefGraph() -> SetMarkerSize(1);
  rp -> GetLowerRefGraph() -> SetLineWidth(1);

  rp -> GetXaxis() -> SetNdivisions(505);
  rp -> GetLowYaxis() -> SetNdivisions(505);
  rp -> GetUpperRefYaxis() -> SetTitleOffset(1.05);
  rp -> GetLowerRefXaxis() -> SetTitleOffset(1.0);

  rp -> GetLowerRefYaxis() -> SetRangeUser(0.01,1.99);
  rp -> GetUpperRefYaxis() -> SetRangeUser(1,1000000);
  rp -> GetLowerRefYaxis() -> SetTitle("weights/cuts");// file2/file1
  rp -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp -> GetLowerRefYaxis() -> SetTitleOffset(1.6);
  rp -> GetLowerRefXaxis() -> SetRangeUser(100,2000);
  rp -> GetUpperRefXaxis() -> SetRangeUser(100,2000);

  rp -> SetUpTopMargin(0.03);
  rp -> SetLowBottomMargin(0.4);
  rp -> SetRightMargin(0.05);
  rp -> SetLeftMargin(0.12);
  rp -> SetSeparationMargin(0.02);

  TLegend* leg = new TLegend(0.58,0.72,0.98,0.91);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_2,"m_{12}, weights","L");
  leg -> AddEntry(hist_1,"m_{12}, cuts","L");
  leg -> SetTextSize(0.04);

  rp -> GetUpperPad() -> cd();

  leg -> Draw();

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/CutsVsWeights_Feb13-20/comp_cuts-weights-m12_aac_nosf_notrigger_fullHT_3bCR_20200213-1730.pdf");
}
