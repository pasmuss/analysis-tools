#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

void PlotMCsigMasses120_350_600_1200(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);

  //obviously only CR, SR needs to remain blinded!
  
  ///
  /// Files
  ///
  TFile* file_120 = new TFile("PlotsWithMuonInformation/MCHist/120-SR-deepcsv-mediumMuonlooseJet-MC-noJSON_SR.root","READ");
  TFile* file_350 = new TFile("PlotsWithMuonInformation/MCHist/350-SR-deepcsv-mediumMuonlooseJet-MC-noJSON_SR.root","READ");
  TFile* file_600 = new TFile("PlotsWithMuonInformation/MCHist/600-SR-deepcsv-mediumMuonlooseJet-MC-noJSON_SR.root","READ");
  TFile* file_1200 = new TFile("PlotsWithMuonInformation/MCHist/1200-SR-deepcsv-mediumMuonlooseJet-MC-noJSON_SR.root","READ");
  
  ///
  /// Mass histograms
  ///
  TH1F* hist_m_120 = (TH1F*)file_120 -> Get("m12_csv");
  TH1F* hist_m_350 = (TH1F*)file_350 -> Get("m12_csv");
  TH1F* hist_m_600 = (TH1F*)file_600 -> Get("m12_csv");
  TH1F* hist_m_1200 = (TH1F*)file_1200 -> Get("m12_csv");

  TCanvas* can = style.MakeCanvas("can","signal masses, after cuts, SR",700,700);
  can -> SetLeftMargin(0.17);
  
  style.InitHist(hist_m_120,"m_{12} / GeV","Entries / 20 GeV",kBlue,0);
  hist_m_120 -> GetYaxis() -> SetRangeUser(0.1,2500);
  hist_m_120 -> GetXaxis() -> SetRangeUser(0,2000);
  hist_m_120 -> GetXaxis() -> SetNdivisions(505);
  hist_m_120 -> GetYaxis() -> SetTitleOffset(1.5);
  hist_m_120 -> Draw();
  style.InitHist(hist_m_350,"m_{12} / GeV","Entries / 20 GeV",kRed,0);
  hist_m_350 -> Draw("SAME");
  style.InitHist(hist_m_600,"m_{12} / GeV","Entries / 20 GeV",kGreen,0);
  hist_m_600 -> Draw("SAME");
  style.InitHist(hist_m_1200,"m_{12} / GeV","Entries / 20 GeV",kOrange,0);
  hist_m_1200 -> Draw("SAME");

  TLegend* leg = new TLegend(0.5,0.6,0.9,0.9);
  style.SetLegendStyle(leg);
  leg -> AddEntry(hist_m_120,"120 GeV","L");
  leg -> AddEntry(hist_m_350,"350 GeV","L");
  leg -> AddEntry(hist_m_600,"600 GeV","L");
  leg -> AddEntry(hist_m_1200,"1200 GeV","L");
  leg -> Draw("SAME");
}
