#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

void PlotMassRatiosPerEra(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);

  //obviously only CR, SR needs to remain blinded!
  
  ///
  /// Files
  ///
  TFile* file_C_prompt = new TFile("PlotsWithMuonInformation/PromptHist/C-CR-deep-prompt.root","READ");
  TFile* file_D_prompt = new TFile("PlotsWithMuonInformation/PromptHist/D-CR-deep-prompt.root","READ");
  TFile* file_E_prompt = new TFile("PlotsWithMuonInformation/PromptHist/E-CR-deep-prompt.root","READ");
  TFile* file_F_prompt = new TFile("PlotsWithMuonInformation/PromptHist/F-CR-deep-prompt.root","READ");
  TFile* file_C_rereco = new TFile("PlotsWithMuonInformation/ReRecoc1Hist/C-CR-deep-rerecoc1.root","READ");
  TFile* file_D_rereco = new TFile("PlotsWithMuonInformation/ReRecoc1Hist/D-CR-deep-rerecoc1.root","READ");
  TFile* file_E_rereco = new TFile("PlotsWithMuonInformation/ReRecoc1Hist/E-CR-deep-rerecoc1.root","READ");
  TFile* file_F_rereco = new TFile("PlotsWithMuonInformation/ReRecoc1Hist/F-CR-deep-rerecoc1.root","READ");
  TFile* file_Ec2_rereco = new TFile("PlotsWithMuonInformation/ReRecoc2Hist/E-CR-deep-rerecoc2.root","READ");
  TFile* file_Fc2_rereco = new TFile("PlotsWithMuonInformation/ReRecoc2Hist/F-CR-deep-rerecoc2.root","READ");
  
  ///
  /// Mass histograms
  ///
  TH1F* hist_m_C_prompt = (TH1F*)file_C_prompt -> Get("m12_csv");
  TH1F* hist_m_D_prompt = (TH1F*)file_D_prompt -> Get("m12_csv");
  TH1F* hist_m_E_prompt = (TH1F*)file_E_prompt -> Get("m12_csv");
  TH1F* hist_m_F_prompt = (TH1F*)file_F_prompt -> Get("m12_csv");
  TH1F* hist_m_C_rereco = (TH1F*)file_C_rereco -> Get("m12_csv");
  TH1F* hist_m_D_rereco = (TH1F*)file_D_rereco -> Get("m12_csv");
  TH1F* hist_m_E_rereco = (TH1F*)file_E_rereco -> Get("m12_csv");
  TH1F* hist_m_F_rereco = (TH1F*)file_F_rereco -> Get("m12_csv");
  TH1F* hist_m_Ec2_rereco = (TH1F*)file_Ec2_rereco -> Get("m12_csv");
  TH1F* hist_m_Fc2_rereco = (TH1F*)file_Fc2_rereco -> Get("m12_csv");

  std::vector<double> lines1 = {1.0, 1.5, 2.0};
  std::vector<double> linesF = {1.0, 2.0, 3.0, 4.0};

  ///
  /// Era C
  ///
  TCanvas* can_C = style.MakeCanvas("can_C","era C: m prompt vs. rereco",700,700);
  can_C -> SetLogy();
  style.InitHist(hist_m_C_prompt,"m_{12} / GeV","Entries / 60 GeV",kRed,0);
  hist_m_C_prompt -> Rebin(3);
  style.InitHist(hist_m_C_rereco,"m_{12} / GeV","Entries / 60 GeV",kBlue,0);
  hist_m_C_rereco -> Rebin(3);

  auto rp_C = new TRatioPlot(hist_m_C_rereco,hist_m_C_prompt);
  rp_C -> SetH1DrawOpt("E");
  rp_C -> SetH2DrawOpt("E");
  rp_C -> SetGridlines(lines1);
  rp_C -> Draw();

  rp_C -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_C -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_C -> SetRightMargin(0.05);
  rp_C -> SetUpTopMargin(0.03);
  rp_C -> SetLeftMargin(0.13);
  rp_C -> SetSeparationMargin(0.07);
  rp_C -> SetLowBottomMargin(0.4);
  rp_C -> SetLowTopMargin(0.0);

  rp_C -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_C -> GetLowerRefYaxis() -> SetRangeUser(0.5,2.5);
  rp_C -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);

  rp_C -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_C -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_C -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_C -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_C -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_C -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_C -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_C -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_C -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_C -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_C -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_C -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_C -> GetLowYaxis() -> SetNdivisions(505);

  rp_C -> GetUpperPad() -> cd();

  TLegend* leg_C = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_C);
  leg_C -> AddEntry(hist_m_C_prompt,"era C, prompt","L");
  leg_C -> AddEntry(hist_m_C_rereco,"era C, rereco","L");
  leg_C -> Draw("SAME");

  can_C -> Update();
  
  ///
  /// Era D
  ///

  TCanvas* can_D = style.MakeCanvas("can_D","era D: m prompt vs. rereco",700,700);
  can_D -> SetLogy();
  style.InitHist(hist_m_D_prompt,"m_{12} / GeV","Entries / 60 GeV",kRed,0);
  hist_m_D_prompt -> Rebin(3);
  style.InitHist(hist_m_D_rereco,"m_{12} / GeV","Entries / 60 GeV",kBlue,0);
  hist_m_D_rereco -> Rebin(3);

  auto rp_D = new TRatioPlot(hist_m_D_rereco,hist_m_D_prompt);
  rp_D -> SetH1DrawOpt("E");
  rp_D -> SetH2DrawOpt("E");
  rp_D -> SetGridlines(lines1);
  rp_D -> Draw();

  rp_D -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_D -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_D -> SetRightMargin(0.05);
  rp_D -> SetUpTopMargin(0.03);
  rp_D -> SetLeftMargin(0.13);
  rp_D -> SetSeparationMargin(0.07);
  rp_D -> SetLowBottomMargin(0.4);
  rp_D -> SetLowTopMargin(0.0);

  rp_D -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_D -> GetLowerRefYaxis() -> SetRangeUser(0.5,2.5);
  rp_D -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);

  rp_D -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_D -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_D -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_D -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_D -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_D -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_D -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_D -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_D -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_D -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_D -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_D -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_D -> GetLowYaxis() -> SetNdivisions(505);

  rp_D -> GetUpperPad() -> cd();

  TLegend* leg_D = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_D);
  leg_D -> AddEntry(hist_m_D_prompt,"era D, prompt","L");
  leg_D -> AddEntry(hist_m_D_rereco,"era D, rereco","L");
  leg_D -> Draw("SAME");

  can_D -> Update();

  ///
  /// Era E
  ///

  TCanvas* can_E = style.MakeCanvas("can_E","era E: m prompt vs. rereco",700,700);
  can_E -> SetLogy();
  style.InitHist(hist_m_E_prompt,"m_{12} / GeV","Entries / 60 GeV",kRed,0);
  hist_m_E_prompt -> Rebin(3);
  style.InitHist(hist_m_E_rereco,"m_{12} / GeV","Entries / 60 GeV",kBlue,0);
  hist_m_E_rereco -> Rebin(3);

  auto rp_E = new TRatioPlot(hist_m_E_rereco,hist_m_E_prompt);
  rp_E -> SetH1DrawOpt("E");
  rp_E -> SetH2DrawOpt("E");
  rp_E -> SetGridlines(lines1);
  rp_E -> Draw();

  rp_E -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_E -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_E -> SetRightMargin(0.05);
  rp_E -> SetUpTopMargin(0.03);
  rp_E -> SetLeftMargin(0.13);
  rp_E -> SetSeparationMargin(0.07);
  rp_E -> SetLowBottomMargin(0.4);
  rp_E -> SetLowTopMargin(0.0);

  rp_E -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_E -> GetLowerRefYaxis() -> SetRangeUser(0.5,2.5);
  rp_E -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);

  rp_E -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_E -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_E -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_E -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_E -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_E -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_E -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_E -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_E -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_E -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_E -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_E -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_E -> GetLowYaxis() -> SetNdivisions(505);

  rp_E -> GetUpperPad() -> cd();

  TLegend* leg_E = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_E);
  leg_E -> AddEntry(hist_m_E_prompt,"era E, prompt","L");
  leg_E -> AddEntry(hist_m_E_rereco,"era E, rereco","L");
  leg_E -> Draw("SAME");

  can_E -> Update();
  
  ///
  /// Era F
  ///

  TCanvas* can_F = style.MakeCanvas("can_F","era F: m prompt vs. rereco",700,700);
  can_F -> SetLogy();
  style.InitHist(hist_m_F_prompt,"m_{12} / GeV","Entries / 60 GeV",kRed,0);
  hist_m_F_prompt -> Rebin(3);
  style.InitHist(hist_m_F_rereco,"m_{12} / GeV","Entries / 60 GeV",kBlue,0);
  hist_m_F_rereco -> Rebin(3);

  auto rp_F = new TRatioPlot(hist_m_F_rereco,hist_m_F_prompt);
  rp_F -> SetH1DrawOpt("E");
  rp_F -> SetH2DrawOpt("E");
  rp_F -> SetGridlines(linesF);
  rp_F -> Draw();

  rp_F -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_F -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_F -> SetRightMargin(0.05);
  rp_F -> SetUpTopMargin(0.03);
  rp_F -> SetLeftMargin(0.13);
  rp_F -> SetSeparationMargin(0.07);
  rp_F -> SetLowBottomMargin(0.4);
  rp_F -> SetLowTopMargin(0.0);

  rp_F -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_F -> GetLowerRefYaxis() -> SetRangeUser(0.5,5.0);
  rp_F -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);

  rp_F -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_F -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_F -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_F -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_F -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_F -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_F -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_F -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_F -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_F -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_F -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_F -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_F -> GetLowYaxis() -> SetNdivisions(505);

  rp_F -> GetUpperPad() -> cd();

  TLegend* leg_F = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_F);
  leg_F -> AddEntry(hist_m_F_prompt,"era F, prompt","L");
  leg_F -> AddEntry(hist_m_F_rereco,"era F, rereco","L");
  leg_F -> Draw("SAME");

  can_F -> Update();

  ///
  /// Era E / case 2
  ///

  TCanvas* can_Ec2 = style.MakeCanvas("can_Ec2","era E, case 2: m prompt vs. rereco",700,700);
  can_Ec2 -> SetLogy();
  style.InitHist(hist_m_E_prompt,"m_{12} / GeV","Entries / 60 GeV",kRed,0);
  style.InitHist(hist_m_Ec2_rereco,"m_{12} / GeV","Entries / 60 GeV",kBlue,0);
  hist_m_Ec2_rereco -> Rebin(3);

  auto rp_Ec2 = new TRatioPlot(hist_m_Ec2_rereco,hist_m_E_prompt);
  rp_Ec2 -> SetH1DrawOpt("E");
  rp_Ec2 -> SetH2DrawOpt("E");
  rp_Ec2 -> SetGridlines(lines1);
  rp_Ec2 -> Draw();

  rp_Ec2 -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_Ec2 -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_Ec2 -> SetRightMargin(0.05);
  rp_Ec2 -> SetUpTopMargin(0.03);
  rp_Ec2 -> SetLeftMargin(0.13);
  rp_Ec2 -> SetSeparationMargin(0.07);
  rp_Ec2 -> SetLowBottomMargin(0.4);
  rp_Ec2 -> SetLowTopMargin(0.0);

  rp_Ec2 -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_Ec2 -> GetLowerRefYaxis() -> SetRangeUser(0.5,2.5);
  rp_Ec2 -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);

  rp_Ec2 -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_Ec2 -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_Ec2 -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_Ec2 -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_Ec2 -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_Ec2 -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_Ec2 -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_Ec2 -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_Ec2 -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_Ec2 -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_Ec2 -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_Ec2 -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_Ec2 -> GetLowYaxis() -> SetNdivisions(505);

  rp_Ec2 -> GetUpperPad() -> cd();

  TLegend* leg_Ec2 = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_Ec2);
  leg_Ec2 -> AddEntry(hist_m_E_prompt,"era E, prompt","L");
  leg_Ec2 -> AddEntry(hist_m_Ec2_rereco,"era E (c2), rereco","L");
  leg_Ec2 -> Draw("SAME");

  can_Ec2 -> Update();

  ///
  /// Era F / case 2
  ///
  
  TCanvas* can_Fc2 = style.MakeCanvas("can_Fc2","era F, case 2: m prompt vs. rereco",700,700);
  can_Fc2 -> SetLogy();
  style.InitHist(hist_m_F_prompt,"m_{12} / GeV","Entries / 60 GeV",kRed,0);
  style.InitHist(hist_m_Fc2_rereco,"m_{12} / GeV","Entries / 60 GeV",kBlue,0);
  hist_m_Fc2_rereco -> Rebin(3);

  auto rp_Fc2 = new TRatioPlot(hist_m_Fc2_rereco,hist_m_F_prompt);
  rp_Fc2 -> SetH1DrawOpt("E");
  rp_Fc2 -> SetH2DrawOpt("E");
  rp_Fc2 -> SetGridlines(linesF);
  rp_Fc2 -> Draw();

  rp_Fc2 -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_Fc2 -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_Fc2 -> SetRightMargin(0.05);
  rp_Fc2 -> SetUpTopMargin(0.03);
  rp_Fc2 -> SetLeftMargin(0.13);
  rp_Fc2 -> SetSeparationMargin(0.07);
  rp_Fc2 -> SetLowBottomMargin(0.4);
  rp_Fc2 -> SetLowTopMargin(0.0);

  rp_Fc2 -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_Fc2 -> GetLowerRefYaxis() -> SetRangeUser(0.5,5.0);
  rp_Fc2 -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);

  rp_Fc2 -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_Fc2 -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_Fc2 -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_Fc2 -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_Fc2 -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_Fc2 -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_Fc2 -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_Fc2 -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_Fc2 -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_Fc2 -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_Fc2 -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_Fc2 -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_Fc2 -> GetLowYaxis() -> SetNdivisions(505);

  rp_Fc2 -> GetUpperPad() -> cd();

  TLegend* leg_Fc2 = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_Fc2);
  leg_Fc2 -> AddEntry(hist_m_F_prompt,"era F, prompt","L");
  leg_Fc2 -> AddEntry(hist_m_Fc2_rereco,"era F (c2), rereco","L");
  leg_Fc2 -> Draw("SAME");

  can_Fc2 -> Update();
  
}
