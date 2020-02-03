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
  /// Files
  ///
  TFile* file_1 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_pT120110_apartSameAsNov12-19_Jan23-20/rereco/rereco-CDEF-deep-CR-3j.root","READ");//MC
  TFile* file_2 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rereco/rereco-CDEF-deep-CR-3j.root","READ");//data
  
  ///
  /// histograms
  ///
  TH1F* hist_1 = (TH1F*)file_1 -> Get("m12_aac");
  TH1F* hist_2 = (TH1F*)file_2 -> Get("m12_aac");

  hist_1 -> Rebin(1);
  hist_2 -> Rebin(1);

  int binwidth_1 = hist_1 -> GetBinWidth(1);
  int binwidth_2 = hist_2 -> GetBinWidth(1);
  int rebin = binwidth_1/binwidth_2;
  hist_2 -> Rebin(rebin);

  cout << "rebinning done" << endl;

  TCanvas* can = style.MakeCanvas("can","CR 3b, pT 120/110 vs. 110/100",700,700);
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

  rp -> GetLowerRefYaxis() -> SetRangeUser(0.51,2.5);
  rp -> GetUpperRefYaxis() -> SetRangeUser(1,10000000);
  rp -> GetLowerRefYaxis() -> SetTitle("loose/tight");
  rp -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp -> GetLowerRefYaxis() -> SetTitleOffset(1.6);
  rp -> GetLowerRefXaxis() -> SetRangeUser(100,2000);
  rp -> GetUpperRefXaxis() -> SetRangeUser(100,2000);

  rp -> SetUpTopMargin(0.03);
  rp -> SetLowBottomMargin(0.4);
  rp -> SetRightMargin(0.05);
  rp -> SetLeftMargin(0.12);
  rp -> SetSeparationMargin(0.02);

  TLegend* leg = new TLegend(0.44,0.72,0.84,0.91);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_2,"m_{12}, bbnb, p_{T}^{(1,2)} > 110/100 GeV","L");
  leg -> AddEntry(hist_1,"m_{12}, bbnb, p_{T}^{(1,2)} > 120/110 GeV","L");
  leg -> SetTextSize(0.04);

  rp -> GetUpperPad() -> cd();

  leg -> Draw();

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/comp_bbnb_3b_pT120110vs110100_Jan30-20-1509_20GeVbinning.pdf");
}
