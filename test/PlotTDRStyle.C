#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

void PlotTDRStyle (){
  HbbStylesNew style;
  style.SetStyle();

  bool drawpt = true;
  bool drawbtag = false;

  TFile* FileCcrCSV = new TFile("PlotsWithMuonInformation/C-CR-csv-mediumJetMuon_CR.root","READ");
  TFile* FileDcrCSV = new TFile("PlotsWithMuonInformation/D-CR-csv-mediumJetMuon_CR.root","READ");
  TFile* FileEcrCSV = new TFile("PlotsWithMuonInformation/E-CR-csv-mediumJetMuon_CR.root","READ");
  TFile* FileFcrCSV = new TFile("PlotsWithMuonInformation/F-CR-csv-mediumJetMuon_CR.root","READ");
  TFile* FileCsrCSV = new TFile("PlotsWithMuonInformation/C-SR-csv-mediumJetMuon_SR.root","READ");
  TFile* FileDsrCSV = new TFile("PlotsWithMuonInformation/D-SR-csv-mediumJetMuon_SR.root","READ");
  TFile* FileEsrCSV = new TFile("PlotsWithMuonInformation/E-SR-csv-mediumJetMuon_SR.root","READ");
  TFile* FileFsrCSV = new TFile("PlotsWithMuonInformation/F-SR-csv-mediumJetMuon_SR.root","READ");
  TFile* FileCcrdeep = new TFile("PlotsWithMuonInformation/C-CR-deepcsv-mediumJetMuon_CR.root","READ");
  TFile* FileDcrdeep = new TFile("PlotsWithMuonInformation/D-CR-deepcsv-mediumJetMuon_CR.root","READ");
  TFile* FileEcrdeep = new TFile("PlotsWithMuonInformation/E-CR-deepcsv-mediumJetMuon_CR.root","READ");
  TFile* FileFcrdeep = new TFile("PlotsWithMuonInformation/F-CR-deepcsv-mediumJetMuon_CR.root","READ");
  TFile* FileCsrdeep = new TFile("PlotsWithMuonInformation/C-SR-deepcsv-mediumJetMuon_SR.root","READ");
  TFile* FileDsrdeep = new TFile("PlotsWithMuonInformation/D-SR-deepcsv-mediumJetMuon_SR.root","READ");
  TFile* FileEsrdeep = new TFile("PlotsWithMuonInformation/E-SR-deepcsv-mediumJetMuon_SR.root","READ");
  TFile* FileFsrdeep = new TFile("PlotsWithMuonInformation/F-SR-deepcsv-mediumJetMuon_SR.root","READ");
  
  if(drawpt){
    
  }

  if (drawbtag){
    TH1F* btag_csv_C_hist_1 = (TH1F*)FileCcrCSV->Get("btag_0");
    TH1F* btag_csv_C_hist_2 = (TH1F*)FileCcrCSV->Get("btag_1");
    TH1F* btag_csv_C_hist_3 = (TH1F*)FileCcrCSV->Get("btag_2");
    TH1F* btag_deep_C_hist_1 = (TH1F*)FileCcrdeep->Get("deepcsvbtag_0");
    TH1F* btag_deep_C_hist_2 = (TH1F*)FileCcrdeep->Get("deepcsvbtag_1");
    TH1F* btag_deep_C_hist_3 = (TH1F*)FileCcrdeep->Get("deepcsvbtag_2");

    TH1F* btag_csv_D_hist_1 = (TH1F*)FileDcrCSV->Get("btag_0");
    TH1F* btag_csv_D_hist_2 = (TH1F*)FileDcrCSV->Get("btag_1");
    TH1F* btag_csv_D_hist_3 = (TH1F*)FileDcrCSV->Get("btag_2");
    TH1F* btag_deep_D_hist_1 = (TH1F*)FileDcrdeep->Get("deepcsvbtag_0");
    TH1F* btag_deep_D_hist_2 = (TH1F*)FileDcrdeep->Get("deepcsvbtag_1");
    TH1F* btag_deep_D_hist_3 = (TH1F*)FileDcrdeep->Get("deepcsvbtag_2");

    TH1F* btag_csv_E_hist_1 = (TH1F*)FileEcrCSV->Get("btag_0");
    TH1F* btag_csv_E_hist_2 = (TH1F*)FileEcrCSV->Get("btag_1");
    TH1F* btag_csv_E_hist_3 = (TH1F*)FileEcrCSV->Get("btag_2");
    TH1F* btag_deep_E_hist_1 = (TH1F*)FileEcrdeep->Get("deepcsvbtag_0");
    TH1F* btag_deep_E_hist_2 = (TH1F*)FileEcrdeep->Get("deepcsvbtag_1");
    TH1F* btag_deep_E_hist_3 = (TH1F*)FileEcrdeep->Get("deepcsvbtag_2");

    TH1F* btag_csv_F_hist_1 = (TH1F*)FileFcrCSV->Get("btag_0");
    TH1F* btag_csv_F_hist_2 = (TH1F*)FileFcrCSV->Get("btag_1");
    TH1F* btag_csv_F_hist_3 = (TH1F*)FileFcrCSV->Get("btag_2");
    TH1F* btag_deep_F_hist_1 = (TH1F*)FileFcrdeep->Get("deepcsvbtag_0");
    TH1F* btag_deep_F_hist_2 = (TH1F*)FileFcrdeep->Get("deepcsvbtag_1");
    TH1F* btag_deep_F_hist_3 = (TH1F*)FileFcrdeep->Get("deepcsvbtag_2");

    TCanvas* btagcsv1_can = style.MakeCanvas("btagcsv1_can","btagcsv1",700,700);
    btagcsv1_can -> SetLogy();
    style.InitHist(btag_csv_C_hist_1,"b tag, CSV, first jet","Entries",kBlack,0);
    btag_csv_C_hist_1->Draw();
    style.InitHist(btag_csv_D_hist_1,"b tag, CSV, first jet","Entries",kRed,0);
    btag_csv_D_hist_1->Draw("SAME"); 
    style.InitHist(btag_csv_E_hist_1,"b tag, CSV, first jet","Entries",kBlue,0);
    btag_csv_E_hist_1->Draw("SAME");
    style.InitHist(btag_csv_F_hist_1,"b tag, CSV, first jet","Entries",kGreen,0);
    btag_csv_F_hist_1->Draw("SAME");

    TLegend* leg1csv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(leg1csv);
    leg1csv->SetNColumns(2);
    leg1csv->AddEntry(btag_csv_C_hist_1,"era C","L");
    leg1csv->AddEntry(btag_csv_D_hist_1,"era D","L");
    leg1csv->AddEntry(btag_csv_E_hist_1,"era E","L");
    leg1csv->AddEntry(btag_csv_F_hist_1,"era F","L");
    leg1csv->Draw("SAME");

    TCanvas* btagcsv2_can = style.MakeCanvas("btagcsv2_can","btagcsv2",700,700);
    btagcsv2_can -> SetLogy();
    style.InitHist(btag_csv_C_hist_2,"b tag, CSV, second jet","Entries",kBlack,0);
    btag_csv_C_hist_2->Draw();
    style.InitHist(btag_csv_D_hist_2,"b tag, CSV, second jet","Entries",kRed,0);
    btag_csv_D_hist_2->Draw("SAME");
    style.InitHist(btag_csv_E_hist_2,"b tag, CSV, second jet","Entries",kBlue,0);
    btag_csv_E_hist_2->Draw("SAME");
    style.InitHist(btag_csv_F_hist_2,"b tag, CSV, second jet","Entries",kGreen,0);
    btag_csv_F_hist_2->Draw("SAME");

    TLegend* leg2csv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(leg2csv);
    leg2csv->SetNColumns(2);
    leg2csv->AddEntry(btag_csv_C_hist_2,"era C","L");
    leg2csv->AddEntry(btag_csv_D_hist_2,"era D","L");
    leg2csv->AddEntry(btag_csv_E_hist_2,"era E","L");
    leg2csv->AddEntry(btag_csv_F_hist_2,"era F","L");
    leg2csv->Draw("SAME");

    TCanvas* btagcsv3_can = style.MakeCanvas("btagcsv3_can","btagcsv3",700,700);
    btagcsv3_can ->SetLogy();
    style.InitHist(btag_csv_C_hist_3,"b tag, CSV, third jet","Entries",kBlack,0);
    btag_csv_C_hist_3->Draw();
    style.InitHist(btag_csv_D_hist_3,"b tag, CSV, third jet","Entries",kRed,0);
    btag_csv_D_hist_3->Draw("SAME");
    style.InitHist(btag_csv_E_hist_3,"b tag, CSV, third jet","Entries",kBlue,0);
    btag_csv_E_hist_3->Draw("SAME");
    style.InitHist(btag_csv_F_hist_3,"b tag, CSV, third jet","Entries",kGreen,0);
    btag_csv_F_hist_3->Draw("SAME");

    TLegend* leg3csv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(leg3csv);
    leg3csv->SetNColumns(2);
    leg3csv->AddEntry(btag_csv_C_hist_3,"era C","L");
    leg3csv->AddEntry(btag_csv_D_hist_3,"era D","L");
    leg3csv->AddEntry(btag_csv_E_hist_3,"era E","L");
    leg3csv->AddEntry(btag_csv_F_hist_3,"era F","L");
    leg3csv->Draw("SAME");


    TCanvas* btagdeepcsv1_can = style.MakeCanvas("btagdeepcsv1_can","btagdeepcsv1",700,700);
    btagdeepcsv1_can -> SetLogy();
    style.InitHist(btag_deep_C_hist_1,"b tag, deep CSV, first jet","Entries",kBlack,0);
    btag_deep_C_hist_1->Draw();
    style.InitHist(btag_deep_D_hist_1,"b tag, deep CSV, first jet","Entries",kRed,0);
    btag_deep_D_hist_1->Draw("SAME");
    style.InitHist(btag_deep_E_hist_1,"b tag, deep CSV, first jet","Entries",kBlue,0);
    btag_deep_E_hist_1->Draw("SAME");
    style.InitHist(btag_deep_F_hist_1,"b tag, deep CSV, first jet","Entries",kGreen,0);
    btag_deep_F_hist_1->Draw("SAME");

    TLegend* leg1deepcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(leg1deepcsv);
    leg1deepcsv->SetNColumns(2);
    leg1deepcsv->AddEntry(btag_deep_C_hist_1,"era C","L");
    leg1deepcsv->AddEntry(btag_deep_D_hist_1,"era D","L");
    leg1deepcsv->AddEntry(btag_deep_E_hist_1,"era E","L");
    leg1deepcsv->AddEntry(btag_deep_F_hist_1,"era F","L");
    leg1deepcsv->Draw("SAME");

    TCanvas* btagdeepcsv2_can = style.MakeCanvas("btagdeepcsv2_can","btagdeepcsv2",700,700);
    btagdeepcsv2_can -> SetLogy();
    style.InitHist(btag_deep_C_hist_2,"b tag, deep CSV, second jet","Entries",kBlack,0);
    btag_deep_C_hist_2->Draw();
    style.InitHist(btag_deep_D_hist_2,"b tag, deep CSV, second jet","Entries",kRed,0);
    btag_deep_D_hist_2->Draw("SAME");
    style.InitHist(btag_deep_E_hist_2,"b tag, deep CSV, second jet","Entries",kBlue,0);
    btag_deep_E_hist_2->Draw("SAME");
    style.InitHist(btag_deep_F_hist_2,"b tag, deep CSV, second jet","Entries",kGreen,0);
    btag_deep_F_hist_2->Draw("SAME");

    TLegend* leg2deepcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(leg2deepcsv);
    leg2deepcsv->SetNColumns(2);
    leg2deepcsv->AddEntry(btag_deep_C_hist_2,"era C","L");
    leg2deepcsv->AddEntry(btag_deep_D_hist_2,"era D","L");
    leg2deepcsv->AddEntry(btag_deep_E_hist_2,"era E","L");
    leg2deepcsv->AddEntry(btag_deep_F_hist_2,"era F","L");
    leg2deepcsv->Draw("SAME");

    TCanvas* btagdeepcsv3_can = style.MakeCanvas("btagdeepcsv3_can","btagdeepcsv3",700,700);
    btagdeepcsv3_can -> SetLogy();
    style.InitHist(btag_deep_C_hist_3,"b tag, deep CSV, third jet","Entries",kBlack,0);
    btag_deep_C_hist_3->Draw();
    style.InitHist(btag_deep_D_hist_3,"b tag, deep CSV, third jet","Entries",kRed,0);
    btag_deep_D_hist_3->Draw("SAME");
    style.InitHist(btag_deep_E_hist_3,"b tag, deep CSV, third jet","Entries",kBlue,0);
    btag_deep_E_hist_3->Draw("SAME");
    style.InitHist(btag_deep_F_hist_3,"b tag, deep CSV, third jet","Entries",kGreen,0);
    btag_deep_F_hist_3->Draw("SAME");

    TLegend* leg3deepcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(leg3deepcsv);
    leg3deepcsv->SetNColumns(2);
    leg3deepcsv->AddEntry(btag_deep_C_hist_3,"era C","L");
    leg3deepcsv->AddEntry(btag_deep_D_hist_3,"era D","L");
    leg3deepcsv->AddEntry(btag_deep_E_hist_3,"era E","L");
    leg3deepcsv->AddEntry(btag_deep_F_hist_3,"era F","L");
    leg3deepcsv->Draw("SAME");
  }
}
