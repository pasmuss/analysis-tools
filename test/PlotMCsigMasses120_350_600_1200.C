#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"
#include "tdrstyle.C"


void PlotMCsigMasses120_350_600_1200(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);
  
  ///
  /// Files
  ///
  TFile* file_350w = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_incl_PUweights_Jul12-19/mcsig/mc-sig-350-NLO-deep-SR-3j.root","READ");
  TFile* file_600w = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_incl_PUweights_Jul12-19/mcsig/mc-sig-600-NLO-deep-SR-3j.root","READ");
  TFile* file_1200w = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_incl_PUweights_Jul12-19/mcsig/mc-sig-1200-NLO-deep-SR-3j.root","READ");

  TFile* file_350wo = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_noFSR_Aug09-19/mcsig/mc-sig-350-NLO-deep-SR-3j.root","READ");
  TFile* file_600wo = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_noFSR_Aug09-19/mcsig/mc-sig-600-NLO-deep-SR-3j.root","READ");
  TFile* file_1200wo = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_noFSR_Aug09-19/mcsig/mc-sig-1200-NLO-deep-SR-3j.root","READ");
  
  ///
  /// Mass histograms
  ///
  TH1F* hist_m_350w = (TH1F*)file_350w -> Get("m12_aac");
  TH1F* hist_m_600w = (TH1F*)file_600w -> Get("m12_aac");
  TH1F* hist_m_1200w = (TH1F*)file_1200w -> Get("m12_aac");

  TH1F* hist_m_350wo = (TH1F*)file_350wo -> Get("m12_aac");
  TH1F* hist_m_600wo = (TH1F*)file_600wo -> Get("m12_aac");
  TH1F* hist_m_1200wo = (TH1F*)file_1200wo -> Get("m12_aac");

  TCanvas* can = style.MakeCanvas("can","signal masses, after cuts, SR",700,700);
  can -> SetLeftMargin(0.17);
  
  style.InitHist(hist_m_350w,"m_{12} [GeV]","Entries / 20 GeV",kBlue,0);
  hist_m_350w -> GetYaxis() -> SetRangeUser(0.1,10000);
  hist_m_350w -> GetXaxis() -> SetRangeUser(0,1500);
  hist_m_350w -> GetXaxis() -> SetNdivisions(505);
  hist_m_350w -> GetYaxis() -> SetTitleOffset(1.5);
  hist_m_350w -> Draw("HIST");
  style.InitHist(hist_m_350wo,"m_{12} [GeV]","Entries / 20 GeV",kBlue,0);
  hist_m_350wo -> SetLineStyle(7);
  hist_m_350wo -> Draw("HIST SAME");
  style.InitHist(hist_m_600w,"m_{12} [GeV]","Entries / 20 GeV",kGreen,0);
  hist_m_600w -> Draw("HIST SAME");
  style.InitHist(hist_m_600wo,"m_{12} [GeV]","Entries / 20 GeV",kGreen,0);
  hist_m_600wo -> SetLineStyle(7);
  hist_m_600wo -> Draw("HIST SAME");
  style.InitHist(hist_m_1200w,"m_{12} [GeV]","Entries / 20 GeV",kRed,0);
  hist_m_1200w -> Draw("HIST SAME");
  style.InitHist(hist_m_1200wo,"m_{12} [GeV]","Entries / 20 GeV",kRed,0);
  hist_m_1200wo -> SetLineStyle(7);
  hist_m_1200wo -> Draw("HIST SAME");

  TLegend* leg = new TLegend(0.41,0.63,0.86,0.89);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_m_350w,"m_{A/H} = 350 GeV, all corrections","L");
  leg -> AddEntry(hist_m_350wo,"m_{A/H} = 350 GeV, no FSR","L");
  leg -> AddEntry(hist_m_600w,"m_{A/H} = 600 GeV, all corrections","L");
  leg -> AddEntry(hist_m_600wo,"m_{A/H} = 600 GeV, no FSR","L");
  leg -> AddEntry(hist_m_1200w,"m_{A/H} = 1200 GeV, all corrections","L");
  leg -> AddEntry(hist_m_1200wo,"m_{A/H} = 1200 GeV, no FSR","L");
  leg -> Draw("SAME");

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/sig_masses_comp_w-wo-FSR-3j.pdf");
}
