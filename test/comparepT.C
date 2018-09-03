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

void comparepT()
{

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  //setTDRStyle();

  float lumi = 36.0; // all 2017 C to F

  //CR
  TFile* f1 = new TFile("Archive_NAF/ResultsJul13-mediumwp-3jets/rootfiles/rereco/rereco-CDEF-deep-CR.root","READ");// 3 jets
  TFile* f2 = new TFile("Archive_NAF/ResultsJul13-mediumwp-4jets/rootfiles/rereco/rereco-CDEF-deep-CR.root","READ");// 4 jets, pt(1,2): 100 GeV
  TFile* f3 = new TFile("ResultsJul17_4jets-mediumWP-125GeVpTjet1and2/rootfiles/rereco/rereco-CDEF-deep-CR.root","READ");// 4 jets, pt(1,2): 125 GeV
  TFile* f4 = new TFile("ResultsJul17_4jets-mediumWP-150GeVpTjet1and2/rootfiles/rereco/rereco-CDEF-deep-CR.root","READ");// 4 jets, pt(1,2): 140 GeV
/*
  //SR
  TFile* f1 = new TFile("Archive_NAF/ResultsJul13-mediumwp-3jets/rootfiles/rereco/rereco-CDEF-deep-SR.root","READ");// 3 jets
  TFile* f2 = new TFile("Archive_NAF/ResultsJul13-mediumwp-4jets/rootfiles/rereco/rereco-CDEF-deep-SR.root","READ");// 4 jets, pt(1,2): 100 GeV
  TFile* f3 = new TFile("ResultsJul17_4jets-mediumWP-125GeVpTjet1and2/rootfiles/rereco/rereco-CDEF-deep-SR.root","READ");// 4 jets, pt(1,2): 125 GeV
  TFile* f4 = new TFile("ResultsJul17_4jets-mediumWP-150GeVpTjet1and2/rootfiles/rereco/rereco-CDEF-deep-SR.root","READ");// 4 jets, pt(1,2): 140 GeV
*/
  TH1F* hist_pt3_3_100_bc = (TH1F*)f1->Get("pt_2");
  TH1F* hist_pt3_4_100_bc = (TH1F*)f2->Get("pt_2");
  TH1F* hist_pt3_4_125_bc = (TH1F*)f3->Get("pt_2");
  TH1F* hist_pt3_4_150_bc = (TH1F*)f4->Get("pt_2");

  TH1F* hist_pt3_3_100_ac = (TH1F*)f1->Get("pt_2_csv");
  TH1F* hist_pt3_4_100_ac = (TH1F*)f2->Get("pt_2_csv");
  TH1F* hist_pt3_4_125_ac = (TH1F*)f3->Get("pt_2_csv");
  TH1F* hist_pt3_4_150_ac = (TH1F*)f4->Get("pt_2_csv");

  TH1F* hist_pt4_4_100_bc = (TH1F*)f2->Get("pt_3");
  TH1F* hist_pt4_4_125_bc = (TH1F*)f3->Get("pt_3");
  TH1F* hist_pt4_4_150_bc = (TH1F*)f4->Get("pt_3");

  TH1F* hist_pt4_4_100_ac = (TH1F*)f2->Get("pt_3_csv");
  TH1F* hist_pt4_4_125_ac = (TH1F*)f3->Get("pt_3_csv");
  TH1F* hist_pt4_4_150_ac = (TH1F*)f4->Get("pt_3_csv");

  TCanvas* c1 = style.MakeCanvas("c1","pt3-bc",700,700);
  c1 -> SetLogy();
  style.InitHist(hist_pt3_3_100_bc,"p_{T} bef. cuts, 3^{rd} jet [GeV]","Entires",kBlack,0);
  hist_pt3_3_100_bc -> GetXaxis() -> SetRangeUser(0,500);
  hist_pt3_3_100_bc -> GetYaxis() -> SetRangeUser(1,10000000);
  hist_pt3_3_100_bc -> Draw();
  style.InitHist(hist_pt3_4_100_bc,"p_{T} bef. cuts, 3^{rd} jet [GeV]","Entires",kBlue,0);
  hist_pt3_4_100_bc -> Draw("SAME");
  style.InitHist(hist_pt3_4_125_bc,"p_{T} bef. cuts, 3^{rd} jet [GeV]","Entires",kRed,0);
  hist_pt3_4_125_bc -> Draw("SAME");
  style.InitHist(hist_pt3_4_150_bc,"p_{T} bef. cuts, 3^{rd} jet [GeV]","Entires",kGreen,0);
  hist_pt3_4_150_bc -> Draw("SAME");
  
  TLegend* leg1 = new TLegend(0.58,0.7,0.87,0.89);
  style.SetLegendStyle(leg1);
  leg1 -> AddEntry(hist_pt3_3_100_bc,"3 jets, p_{T}_{1,2} #geq 100 GeV","L");
  leg1 -> AddEntry(hist_pt3_4_100_bc,"4 jets, p_{T}_{1,2} #geq 100 GeV","L");
  leg1 -> AddEntry(hist_pt3_4_125_bc,"4 jets, p_{T}_{1,2} #geq 125 GeV","L");
  leg1 -> AddEntry(hist_pt3_4_150_bc,"4 jets, p_{T}_{1,2} #geq 150 GeV","L");
  leg1 -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c1 -> Update();
  c1 -> SaveAs("Comparison_pT3-bc_3-4jets_100-125-150GeV.pdf");

  TCanvas* c2 = style.MakeCanvas("c2","pt3-ac",700,700);
  c2 -> SetLogy();
  style.InitHist(hist_pt3_3_100_ac,"p_{T} after cuts, 3^{rd} jet [GeV]","Entires",kBlack,0);
  hist_pt3_3_100_ac -> GetXaxis() -> SetRangeUser(0,500);
  hist_pt3_3_100_ac -> GetYaxis() -> SetRangeUser(1,10000000);
  hist_pt3_3_100_ac -> Draw();
  style.InitHist(hist_pt3_4_100_ac,"p_{T} after cuts, 3^{rd} jet [GeV]","Entires",kBlue,0);
  hist_pt3_4_100_ac -> Draw("SAME");
  style.InitHist(hist_pt3_4_125_ac,"p_{T} after cuts, 3^{rd} jet [GeV]","Entires",kRed,0);
  hist_pt3_4_125_ac -> Draw("SAME");
  style.InitHist(hist_pt3_4_150_ac,"p_{T} after cuts, 3^{rd} jet [GeV]","Entires",kGreen,0);
  hist_pt3_4_150_ac -> Draw("SAME");
  
  TLegend* leg2 = new TLegend(0.58,0.7,0.87,0.89);
  style.SetLegendStyle(leg2);
  leg2 -> AddEntry(hist_pt3_3_100_ac,"3 jets, p_{T}_{1,2} #geq 100 GeV","L");
  leg2 -> AddEntry(hist_pt3_4_100_ac,"4 jets, p_{T}_{1,2} #geq 100 GeV","L");
  leg2 -> AddEntry(hist_pt3_4_125_ac,"4 jets, p_{T}_{1,2} #geq 125 GeV","L");
  leg2 -> AddEntry(hist_pt3_4_150_ac,"4 jets, p_{T}_{1,2} #geq 150 GeV","L");
  leg2 -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c2 -> Update();
  c2 -> SaveAs("Comparison_pT3-ac_3-4jets_100-125-150GeV.pdf");

  TCanvas* c3 = style.MakeCanvas("c3","pt4-ac",700,700);
  c3 -> SetLogy();
  style.InitHist(hist_pt4_4_100_ac,"p_{T} after cuts, 4^{th} jet [GeV]","Entires",kBlue,0);  
  hist_pt4_4_100_ac -> GetXaxis() -> SetRangeUser(0,500);
  hist_pt4_4_100_ac -> GetYaxis() -> SetRangeUser(1,10000000);
  hist_pt4_4_100_ac -> Draw();
  style.InitHist(hist_pt4_4_125_ac,"p_{T} after cuts, 4^{th} jet [GeV]","Entires",kRed,0);
  hist_pt4_4_125_ac -> Draw("SAME");
  style.InitHist(hist_pt4_4_150_ac,"p_{T} after cuts, 4^{th} jet [GeV]","Entires",kGreen,0);
  hist_pt4_4_150_ac -> Draw("SAME");
  
  TLegend* leg3 = new TLegend(0.58,0.75,0.87,0.89);
  style.SetLegendStyle(leg3);
  leg3 -> AddEntry(hist_pt4_4_100_ac,"4 jets, p_{T}_{1,2} #geq 100 GeV","L");
  leg3 -> AddEntry(hist_pt4_4_125_ac,"4 jets, p_{T}_{1,2} #geq 125 GeV","L");
  leg3 -> AddEntry(hist_pt4_4_150_ac,"4 jets, p_{T}_{1,2} #geq 150 GeV","L");
  leg3 -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c3 -> Update();
  c3 -> SaveAs("Comparison_pT4-ac_3-4jets_100-125-150GeV.pdf");

  TCanvas* c4 = style.MakeCanvas("c4","pt4-bc",700,700);
  c4 -> SetLogy();
  style.InitHist(hist_pt4_4_100_bc,"p_{T} bef. cuts, 4^{th} jet [GeV]","Entires",kBlue,0);  
  hist_pt4_4_100_bc -> GetXaxis() -> SetRangeUser(0,500);
  hist_pt4_4_100_bc -> GetYaxis() -> SetRangeUser(1,10000000);
  hist_pt4_4_100_bc -> Draw();
  style.InitHist(hist_pt4_4_125_bc,"p_{T} bef. cuts, 4^{th} jet [GeV]","Entires",kRed,0);
  hist_pt4_4_125_bc -> Draw("SAME");
  style.InitHist(hist_pt4_4_150_bc,"p_{T} bef. cuts, 4^{th} jet [GeV]","Entires",kGreen,0);
  hist_pt4_4_150_bc -> Draw("SAME");
  
  TLegend* leg4 = new TLegend(0.58,0.75,0.87,0.89);
  style.SetLegendStyle(leg4);
  leg4 -> AddEntry(hist_pt4_4_100_bc,"4 jets, p_{T}_{1,2} #geq 100 GeV","L");
  leg4 -> AddEntry(hist_pt4_4_125_bc,"4 jets, p_{T}_{1,2} #geq 125 GeV","L");
  leg4 -> AddEntry(hist_pt4_4_150_bc,"4 jets, p_{T}_{1,2} #geq 150 GeV","L");
  leg4 -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c4 -> Update();
  c4 -> SaveAs("Comparison_pT4-bc_3-4jets_100-125-150GeV.pdf");

}
