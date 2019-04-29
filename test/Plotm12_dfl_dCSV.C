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


void Plotm12_dfl_dCSV(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);
  
  ///
  /// Files
  ///
  TFile* file_dcsv = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/CutOptimization/Configs_diffBTags_alltight/rootfiles/rereco/rereco-CDEF-deep-CR-3j.root","READ");
  TFile* file_dfl = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/CutOptimization/Configs_diffBTags_alltight_deepflavour/rootfiles/rereco/rereco-CDEF-deep-CR-3j.root","READ");
  
  ///
  /// Mass histograms
  ///
  TH1F* hist_m_dcsv = (TH1F*)file_dcsv -> Get("pt_1_csv");
  TH1F* hist_m_dfl = (TH1F*)file_dfl -> Get("pt_1_csv");


  TCanvas* can = style.MakeCanvas("can","masses, after cuts, CR",700,700);
  can -> SetLogy();
  style.InitHist(hist_m_dcsv,"p_{T}^{(2)} [GeV]","Entries / 10 GeV",kBlue,0);
  hist_m_dcsv -> GetYaxis() -> SetRangeUser(0.1,300000);
  hist_m_dcsv -> GetXaxis() -> SetRangeUser(0,3000);
  hist_m_dcsv -> GetXaxis() -> SetNdivisions(505);
  hist_m_dcsv -> GetYaxis() -> SetTitleOffset(1.3);
  hist_m_dcsv -> Draw();
  style.InitHist(hist_m_dfl,"p_{T}^{(2)} [GeV]","Entries / 10 GeV",kRed,0);
  hist_m_dfl -> Draw("SAME");

  TLegend* leg = new TLegend(0.41,0.63,0.86,0.89);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_m_dcsv,"p_{T}^{(2)}, deepCSV","L");
  leg -> AddEntry(hist_m_dfl,"p_{T}^{(2)}, deepflavour","L");
  leg -> Draw("SAME");

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/comp_dfl-dcsv_pt-2_data_CR_tight-wp_3j.pdf");
}
