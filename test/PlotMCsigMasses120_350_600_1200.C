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
  TFile* file_350w = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/central/mcsig/mc-sig-350-NLO-deep-SR-3j.root","READ");
  TFile* file_600w = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/central/mcsig/mc-sig-600-NLO-deep-SR-3j.root","READ");
  TFile* file_1200w = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/central/mcsig/mc-sig-1200-NLO-deep-SR-3j.root","READ");

  //  TFile* file_350wo = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_comp-no-asym-pT-no-onl-MC-sf_Sep24-19/mcsig/mc-sig-350-NLO-deep-SR-3j.root","READ");
  //TFile* file_600wo = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_comp-no-asym-pT-no-onl-MC-sf_Sep24-19/mcsig/mc-sig-600-NLO-deep-SR-3j.root","READ");
  //TFile* file_1200wo = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_comp-no-asym-pT-no-onl-MC-sf_Sep24-19/mcsig/mc-sig-1200-NLO-deep-SR-3j.root","READ");
  
  ///
  /// Mass histograms
  ///
  TH1F* hist_m_350w = (TH1F*)file_350w -> Get("m12_aac");
  TH1F* hist_m_600w = (TH1F*)file_600w -> Get("m12_aac");
  TH1F* hist_m_1200w = (TH1F*)file_1200w -> Get("m12_aac");

  //TH1F* hist_m_350wo = (TH1F*)file_350wo -> Get("m12_aac");
  //TH1F* hist_m_600wo = (TH1F*)file_600wo -> Get("m12_aac");
  //TH1F* hist_m_1200wo = (TH1F*)file_1200wo -> Get("m12_aac");

  TCanvas* can = style.MakeCanvas("can","signal masses, after cuts, SR",700,700);
  can -> SetLeftMargin(0.17);
  
  style.InitHist(hist_m_350w,"m_{12} [GeV]","Entries / 20 GeV",kBlue,0);
  hist_m_350w -> GetYaxis() -> SetRangeUser(0.1,5000);
  hist_m_350w -> GetXaxis() -> SetRangeUser(0,1500);
  can -> SetLogy(0);
  hist_m_350w -> GetXaxis() -> SetNdivisions(505);
  hist_m_350w -> GetYaxis() -> SetTitleOffset(1.5);
  hist_m_350w -> Draw("HIST");
  //style.InitHist(hist_m_350wo,"m_{12} [GeV]","Entries / 20 GeV",kBlue,0);
  //hist_m_350wo -> SetLineStyle(7);
  //hist_m_350wo -> Draw("HIST SAME");
  style.InitHist(hist_m_600w,"m_{12} [GeV]","Entries / 20 GeV",kGreen,0);
  hist_m_600w -> Draw("HIST SAME");
  //style.InitHist(hist_m_600wo,"m_{12} [GeV]","Entries / 20 GeV",kGreen,0);
  //hist_m_600wo -> SetLineStyle(7);
  //hist_m_600wo -> Draw("HIST SAME");
  style.InitHist(hist_m_1200w,"m_{12} [GeV]","Entries / 20 GeV",kRed,0);
  hist_m_1200w -> Draw("HIST SAME");
  //style.InitHist(hist_m_1200wo,"m_{12} [GeV]","Entries / 20 GeV",kRed,0);
  //hist_m_1200wo -> SetLineStyle(7);
  //hist_m_1200wo -> Draw("HIST SAME");

  TLegend* leg = new TLegend(0.65,0.75,0.9,0.9);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_m_350w,"m_{A/H} = 350 GeV","L");
  //leg -> AddEntry(hist_m_350wo,"m_{A/H} = 350 GeV, without both","L");
  leg -> AddEntry(hist_m_600w,"m_{A/H} = 600 GeV","L");
  //leg -> AddEntry(hist_m_600wo,"m_{A/H} = 600 GeV, without both","L");
  leg -> AddEntry(hist_m_1200w,"m_{A/H} = 1200 GeV","L");
  //leg -> AddEntry(hist_m_1200wo,"m_{A/H} = 1200 GeV, without both","L");
  leg -> Draw("SAME");

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/sig_masses_350_600_1200_finalSelection_Feb05-21.pdf");
  can -> SaveAs("Outputdata/sig_masses_350_600_1200_finalSelection_Feb05-21.root");
}
