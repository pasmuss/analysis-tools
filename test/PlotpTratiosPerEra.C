#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

void PlotpTratiosPerEra(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);
  
  ///
  /// Files
  ///
  TFile* file_C_prompt = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/PromptRes/Prompt-C-deep-CR.root","READ");
  TFile* file_D_prompt = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/PromptRes/Prompt-D-deep-CR.root","READ");
  TFile* file_E_prompt = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/PromptRes/Prompt-E-deep-CR.root","READ");
  TFile* file_F_prompt = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/PromptRes/Prompt-F-deep-CR.root","READ");
  TFile* file_C_rereco = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/ReRecoRes/ReRecoC1-C-deep-CR.root","READ");
  TFile* file_D_rereco = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/ReRecoRes/ReRecoC1-D-deep-CR.root","READ");
  TFile* file_E_rereco = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/ReRecoRes/ReRecoC1-E-deep-CR.root","READ");
  TFile* file_F_rereco = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/ReRecoRes/ReRecoC1-F-deep-CR.root","READ");
  TFile* file_Ec2_rereco = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/ReRecoRes/ReRecoC2-E-deep-CR.root","READ");
  TFile* file_Fc2_rereco = new TFile("Results_Apr_26_Prompt_ReReco_MCsig_MCbg/ReRecoRes/ReRecoC2-F-deep-CR.root","READ");
  
  ///
  /// pT histograms (1st jet)
  ///
  TH1F* hist_pt1_C_prompt = (TH1F*)file_C_prompt -> Get("pt_0_csv");
  TH1F* hist_pt1_D_prompt = (TH1F*)file_D_prompt -> Get("pt_0_csv");
  TH1F* hist_pt1_E_prompt = (TH1F*)file_E_prompt -> Get("pt_0_csv");
  TH1F* hist_pt1_F_prompt = (TH1F*)file_F_prompt -> Get("pt_0_csv");
  TH1F* hist_pt1_C_rereco = (TH1F*)file_C_rereco -> Get("pt_0_csv");
  TH1F* hist_pt1_D_rereco = (TH1F*)file_D_rereco -> Get("pt_0_csv");
  TH1F* hist_pt1_E_rereco = (TH1F*)file_E_rereco -> Get("pt_0_csv");
  TH1F* hist_pt1_F_rereco = (TH1F*)file_F_rereco -> Get("pt_0_csv");
  TH1F* hist_pt1_Ec2_rereco = (TH1F*)file_Ec2_rereco -> Get("pt_0_csv");
  TH1F* hist_pt1_Fc2_rereco = (TH1F*)file_Fc2_rereco -> Get("pt_0_csv");

  ///
  /// pT histograms (2nd jet)
  ///
  TH1F* hist_pt2_C_prompt = (TH1F*)file_C_prompt -> Get("pt_1_csv");
  TH1F* hist_pt2_D_prompt = (TH1F*)file_D_prompt -> Get("pt_1_csv");
  TH1F* hist_pt2_E_prompt = (TH1F*)file_E_prompt -> Get("pt_1_csv");
  TH1F* hist_pt2_F_prompt = (TH1F*)file_F_prompt -> Get("pt_1_csv");
  TH1F* hist_pt2_C_rereco = (TH1F*)file_C_rereco -> Get("pt_1_csv");
  TH1F* hist_pt2_D_rereco = (TH1F*)file_D_rereco -> Get("pt_1_csv");
  TH1F* hist_pt2_E_rereco = (TH1F*)file_E_rereco -> Get("pt_1_csv");
  TH1F* hist_pt2_F_rereco = (TH1F*)file_F_rereco -> Get("pt_1_csv");
  TH1F* hist_pt2_Ec2_rereco = (TH1F*)file_Ec2_rereco -> Get("pt_1_csv");
  TH1F* hist_pt2_Fc2_rereco = (TH1F*)file_Fc2_rereco -> Get("pt_1_csv");

  std::vector<double> lines1 = {1.0, 1.5, 2.0};
  std::vector<double> linesF = {1.0, 2.0, 3.0, 4.0};

  ///
  /// Era C, jet 1
  ///
  TCanvas* can_C1 = style.MakeCanvas("can_C1","era C: pT prompt vs. rereco, 1st jet",700,700);
  can_C1 -> SetLogy();
  style.InitHist(hist_pt1_C_prompt,"p_{T} / GeV","Entries / 50 GeV",kRed,0);
  hist_pt1_C_prompt -> Rebin(5);
  style.InitHist(hist_pt1_C_rereco,"p_{T} / GeV","Entries / 50 GeV",kBlue,0);
  hist_pt1_C_rereco -> Rebin(5);

  auto rp_C1 = new TRatioPlot(hist_pt1_C_rereco,hist_pt1_C_prompt);
  rp_C1 -> SetH1DrawOpt("E");
  rp_C1 -> SetH2DrawOpt("E");
  rp_C1 -> SetGridlines(lines1);
  rp_C1 -> Draw();

  rp_C1 -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_C1 -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_C1 -> SetRightMargin(0.05);
  rp_C1 -> SetUpTopMargin(0.03);
  rp_C1 -> SetLeftMargin(0.13);
  rp_C1 -> SetSeparationMargin(0.07);
  rp_C1 -> SetLowBottomMargin(0.4);
  rp_C1 -> SetLowTopMargin(0.0);

  rp_C1 -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_C1 -> GetLowerRefYaxis() -> SetRangeUser(0.5,2.5);
  rp_C1 -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);
  rp_C1 -> GetUpperRefXaxis() -> SetRangeUser(0,1500);

  rp_C1 -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_C1 -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_C1 -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_C1 -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_C1 -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_C1 -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_C1 -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_C1 -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_C1 -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_C1 -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_C1 -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_C1 -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_C1 -> GetLowYaxis() -> SetNdivisions(505);

  rp_C1 -> GetUpperPad() -> cd();

  TLegend* leg_C1 = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_C1);
  leg_C1 -> AddEntry(hist_pt1_C_prompt,"era C, prompt","L");
  leg_C1 -> AddEntry(hist_pt1_C_rereco,"era C, rereco","L");
  leg_C1 -> Draw("SAME");

  can_C1 -> Update();

  ///
  /// Era C, jet 2
  ///
  TCanvas* can_C2 = style.MakeCanvas("can_C2","era C: pT prompt vs. rereco, 2nd jet",700,700);
  can_C2 -> SetLogy();
  style.InitHist(hist_pt2_C_prompt,"p_{T} / GeV","Entries / 50 GeV",kRed,0);
  hist_pt2_C_prompt -> Rebin(5);
  style.InitHist(hist_pt2_C_rereco,"p_{T} / GeV","Entries / 50 GeV",kBlue,0);
  hist_pt2_C_rereco -> Rebin(5);

  auto rp_C2 = new TRatioPlot(hist_pt2_C_rereco,hist_pt2_C_prompt);
  rp_C2 -> SetH1DrawOpt("E");
  rp_C2 -> SetH2DrawOpt("E");
  rp_C2 -> SetGridlines(lines1);
  rp_C2 -> Draw();

  rp_C2 -> GetLowerRefGraph() -> SetLineWidth(2);
  rp_C2 -> GetLowerRefGraph() -> SetMarkerSize(1);

  rp_C2 -> SetRightMargin(0.05);
  rp_C2 -> SetUpTopMargin(0.03);
  rp_C2 -> SetLeftMargin(0.13);
  rp_C2 -> SetSeparationMargin(0.07);
  rp_C2 -> SetLowBottomMargin(0.4);
  rp_C2 -> SetLowTopMargin(0.0);

  rp_C2 -> GetLowerRefYaxis() -> SetTitle("rereco / prompt");
  rp_C2 -> GetLowerRefYaxis() -> SetRangeUser(0.5,2.5);
  rp_C2 -> GetUpperRefYaxis() -> SetRangeUser(0.1,500000);
  rp_C2 -> GetUpperRefXaxis() -> SetRangeUser(0,1500);

  rp_C2 -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp_C2 -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp_C2 -> GetUpperRefYaxis() -> SetTitleSize(0.05);
  rp_C2 -> GetUpperRefYaxis() -> SetTitleOffset(1.3);
  rp_C2 -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp_C2 -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp_C2 -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp_C2 -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp_C2 -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp_C2 -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp_C2 -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp_C2 -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp_C2 -> GetLowYaxis() -> SetNdivisions(505);

  rp_C2 -> GetUpperPad() -> cd();

  TLegend* leg_C2 = new TLegend(0.58,0.63,0.98,0.93);
  style.SetLegendStyle(leg_C2);
  leg_C2 -> AddEntry(hist_pt2_C_prompt,"era C, prompt","L");
  leg_C2 -> AddEntry(hist_pt2_C_rereco,"era C, rereco","L");
  leg_C2 -> Draw("SAME");

  can_C2 -> Update();
  
}
