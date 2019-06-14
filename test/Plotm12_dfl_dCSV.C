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
  TFile* file_dcsv = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_prescale_4jnn/rereco/rereco-CDEF-deep-CR.root","READ");
  TFile* file_dfl = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_4jnn_m12above200/rereco/rereco-CDEF-deep-CR.root","READ");
  
  ///
  /// Mass histograms
  ///
  TH1F* hist_m_dcsv = (TH1F*)file_dcsv -> Get("m12_csv");
  TH1F* hist_m_dfl = (TH1F*)file_dfl -> Get("m12_csv");


  TCanvas* can = style.MakeCanvas("can","masses, after cuts, CR",700,700);
  //can -> SetLogy();
  style.InitHist(hist_m_dcsv,"m_{12} [GeV]","Entries / 20 GeV",kBlue,0);
  hist_m_dcsv -> GetYaxis() -> SetRangeUser(0.1,15000);
  hist_m_dcsv -> GetXaxis() -> SetRangeUser(0,3000);
  hist_m_dcsv -> GetXaxis() -> SetNdivisions(505);
  hist_m_dcsv -> GetYaxis() -> SetTitleOffset(1.6);
  hist_m_dcsv -> SetMarkerSize(1.1);
  hist_m_dcsv -> Draw();
  style.InitHist(hist_m_dfl,"m_{12} [GeV]","Entries / 20 GeV",kRed,0);
  hist_m_dfl -> Draw("SAME");

  TLegend* leg = new TLegend(0.41,0.63,0.86,0.89);
  style.SetLegendStyle(leg);
  //leg -> SetBorderSize(1);
  leg -> AddEntry(hist_m_dcsv,"m_{12}, bbnbnb","L");
  leg -> AddEntry(hist_m_dfl,"m_{12} > 200 GeV, bbnbnb","L");
  leg -> Draw("SAME");

  // CMSPrelim( "Simulation" , "Work in progress", 0.18, 0.77);

  can -> Update();
  can -> SaveAs("Outputdata/comp_dfl_bbnbnb_WithAndWithoutM12Above200GeV_4j.pdf");
}
