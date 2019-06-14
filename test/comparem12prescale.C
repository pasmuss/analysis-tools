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

void comparem12prescale()
{

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  //setTDRStyle();

  float lumi = 36.0; // all 2017 C to F

  //CR
  TFile* f3j = new TFile("Configs_diffBTags_allmedium/rootfiles_4med_dfl_incl_prescale/rereco/rereco-CDEF-deep-CR-3j.root","READ");// 3 jets
  TFile* f4j = new TFile("Configs_diffBTags_allmedium/rootfiles_4med_dfl_incl_prescale/rereco/rereco-CDEF-deep-CR.root","READ");// 4 jets

  TH1F* hist_3j_0 = (TH1F*)f3j->Get("m12_sel_0");
  TH1F* hist_3j_1 = (TH1F*)f3j->Get("m12_sel_1");
  TH1F* hist_3j_2 = (TH1F*)f3j->Get("m12_sel_2");
  TH1F* hist_3j_3 = (TH1F*)f3j->Get("m12_sel_3");
  TH1F* hist_3j_4 = (TH1F*)f3j->Get("m12_sel_4");
  TH1F* hist_3j_5 = (TH1F*)f3j->Get("m12_sel_5");
  TH1F* hist_3j_6 = (TH1F*)f3j->Get("m12_sel_6");

  TH1F* hist_4j_0 = (TH1F*)f4j->Get("m12_sel_0");
  TH1F* hist_4j_1 = (TH1F*)f4j->Get("m12_sel_1");
  TH1F* hist_4j_2 = (TH1F*)f4j->Get("m12_sel_2");
  TH1F* hist_4j_3 = (TH1F*)f4j->Get("m12_sel_3");

  TCanvas* can3j = style.MakeCanvas("can3j","m12, 3 b category",700,700);
  can3j -> SetLogy();
  style.InitHist(hist_3j_0,"m_{12} [GeV]","Entires",kBlack,0);
  hist_3j_0 -> GetYaxis() -> SetRangeUser(0.1,100000);
  hist_3j_0 -> Draw();
  style.InitHist(hist_3j_1,"m_{12} [GeV]","Entires",kGreen,0);
  hist_3j_1 -> Draw("SAME");
  style.InitHist(hist_3j_2,"m_{12} [GeV]","Entires",kBlue,0);
  hist_3j_2 -> Draw("SAME");
  style.InitHist(hist_3j_3,"m_{12} [GeV]","Entires",kRed,0);
  hist_3j_3 -> Draw("SAME");
  style.InitHist(hist_3j_4,"m_{12} [GeV]","Entires",kCyan,0);
  hist_3j_4 -> Draw("SAME");
  style.InitHist(hist_3j_5,"m_{12} [GeV]","Entires",kMagenta,0);
  hist_3j_5 -> Draw("SAME");
  style.InitHist(hist_3j_6,"m_{12} [GeV]","Entires",kGray,0);
  hist_3j_6 -> Draw("SAME");

  TLegend* leg3j = new TLegend(0.58,0.7,0.87,0.89);
  style.SetLegendStyle(leg3j);
  leg3j -> AddEntry(hist_3j_0,"window 1","L");
  leg3j -> AddEntry(hist_3j_1,"window 2","L");
  leg3j -> AddEntry(hist_3j_2,"window 3","L");
  leg3j -> AddEntry(hist_3j_3,"window 4","L");
  leg3j -> AddEntry(hist_3j_4,"window 5","L");
  leg3j -> AddEntry(hist_3j_5,"window 6","L");
  leg3j -> AddEntry(hist_3j_6,"window 7","L");
  leg3j -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.12, 0.84);

  can3j -> Update();
  can3j -> SaveAs("Outputdata/Comparison_m12_windows-prescale_data_CR_3j.pdf");


  TCanvas* can4j = style.MakeCanvas("can4j","m12, 4 b category",700,700);
  can4j -> SetLogy();
  style.InitHist(hist_4j_0,"m_{12} [GeV]","Entires",kBlack,0);
  hist_4j_0 -> GetYaxis() -> SetRangeUser(0.1,100000);
  hist_4j_0 -> Draw();
  style.InitHist(hist_4j_1,"m_{12} [GeV]","Entires",kGreen,0);
  hist_4j_1 -> Draw("SAME");
  style.InitHist(hist_4j_2,"m_{12} [GeV]","Entires",kBlue,0);
  hist_4j_2 -> Draw("SAME");
  style.InitHist(hist_4j_3,"m_{12} [GeV]","Entires",kRed,0);
  hist_4j_3 -> Draw("SAME");

  TLegend* leg4j = new TLegend(0.58,0.7,0.87,0.89);
  style.SetLegendStyle(leg4j);
  leg4j -> AddEntry(hist_4j_0,"window 1","L");
  leg4j -> AddEntry(hist_4j_1,"window 2","L");
  leg4j -> AddEntry(hist_4j_2,"window 3","L");
  leg4j -> AddEntry(hist_4j_3,"window 4","L");
  leg4j -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.12, 0.84);

  can4j -> Update();
  can4j -> SaveAs("Outputdata/Comparison_m12_windows-prescale_data_CR_4j.pdf");

}
