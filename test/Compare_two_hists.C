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
  //TFile* file_1 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_2J1B_pTmax400300_Mar05-20/cuts/MCbg-QCD-eta_0_aac-2017CDEF.root","READ");
  //TFile* file_2 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_2J1B_pTmax400300_Mar05-20/weights/MCbg-QCD-eta_0_aac-2017CDEF.root","READ");

  TFile* file_1 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Outputdata/TF_bias/Pseudos1346.root","READ");//worst: 1% prob
  TFile* file_2 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Outputdata/TF_bias/Pseudos9816.root","READ");// best: 94% prob

  cout << "files read" << endl;
  
  ///
  /// histograms
  ///
  TH1F* hist_1 = (TH1F*)file_1 -> Get("TFHist");
  TH1F* hist_2 = (TH1F*)file_2 -> Get("TFHist");

  cout << "initialized histograms" << endl;

  hist_1 -> Rebin(1);
  hist_2 -> Rebin(1);

  double binwidth_1 = hist_1 -> GetBinWidth(1);
  cout << "Bin width 1: " << binwidth_1 << endl;
  double binwidth_2 = hist_2 -> GetBinWidth(1);
  cout << "Bin width 2: " << binwidth_2 << endl;
  int rebin = binwidth_1/binwidth_2;
  cout << "rebin " << rebin << endl;
  hist_2 -> Rebin(rebin);

  cout << "rebinning done" << endl;

  TCanvas* can = style.MakeCanvas("can","TF 3b vs. 4b",700,700);
  //can -> SetLogy();
  style.InitHist(hist_1,"m_{12} [GeV]",/*("Entries / " + to_string(binwidth_1) + "GeV").c_str()*/"",kBlue,0);
  style.InitHist(hist_2,"m_{12} [GeV]",/*("Entries / " + to_string(binwidth_1) + "GeV").c_str()*/"",kRed,0);
  //style.InitHist(hist_1,"#eta","Entries",kBlue,0);
  //style.InitHist(hist_2,"#eta","Entries",kRed,0);

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
  //rp -> GetUpperRefYaxis() -> SetRangeUser(1,1000000);
  rp -> GetUpperRefYaxis() -> SetRangeUser(0.01,0.3);
  rp -> GetLowerRefYaxis() -> SetTitle("best/worst");// file2/file1
  rp -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp -> GetLowerRefYaxis() -> SetTitleOffset(1.6);
  rp -> GetLowerRefXaxis() -> SetRangeUser(100,2000);
  rp -> GetUpperRefXaxis() -> SetRangeUser(100,2000);

  rp -> SetUpTopMargin(0.03);
  rp -> SetLowBottomMargin(0.4);
  rp -> SetRightMargin(0.05);
  rp -> SetLeftMargin(0.12);
  rp -> SetSeparationMargin(0.02);

  TLegend* leg = new TLegend(0.15,0.7,0.55,0.9);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_2,"m_{12} (TF), best (94% prob)","L");
  leg -> AddEntry(hist_1,"m_{12} (TF), worst (1% prob)","L");
  leg -> SetTextSize(0.04);

  rp -> GetUpperPad() -> cd();

  leg -> Draw();

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/TF_bias/comp_best-worst_m12_TF.pdf");
}
