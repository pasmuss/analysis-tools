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

  bool ptaftercuts = false;
  bool etaaftercuts = true;
  bool kinbefcuts = false;
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
  
  if(ptaftercuts){
    TH1F* pt_cuts_C_crCSV_hist_1 = (TH1F*)FileCcrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_C_crCSV_hist_2 = (TH1F*)FileCcrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_C_crCSV_hist_3 = (TH1F*)FileCcrCSV->Get("pt_2_csv");
    TH1F* pt_cuts_D_crCSV_hist_1 = (TH1F*)FileDcrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_D_crCSV_hist_2 = (TH1F*)FileDcrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_D_crCSV_hist_3 = (TH1F*)FileDcrCSV->Get("pt_2_csv");
    TH1F* pt_cuts_E_crCSV_hist_1 = (TH1F*)FileEcrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_E_crCSV_hist_2 = (TH1F*)FileEcrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_E_crCSV_hist_3 = (TH1F*)FileEcrCSV->Get("pt_2_csv");
    TH1F* pt_cuts_F_crCSV_hist_1 = (TH1F*)FileFcrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_F_crCSV_hist_2 = (TH1F*)FileFcrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_F_crCSV_hist_3 = (TH1F*)FileFcrCSV->Get("pt_2_csv");

    TH1F* pt_cuts_C_srCSV_hist_1 = (TH1F*)FileCsrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_C_srCSV_hist_2 = (TH1F*)FileCsrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_C_srCSV_hist_3 = (TH1F*)FileCsrCSV->Get("pt_2_csv");
    TH1F* pt_cuts_D_srCSV_hist_1 = (TH1F*)FileDsrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_D_srCSV_hist_2 = (TH1F*)FileDsrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_D_srCSV_hist_3 = (TH1F*)FileDsrCSV->Get("pt_2_csv");
    TH1F* pt_cuts_E_srCSV_hist_1 = (TH1F*)FileEsrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_E_srCSV_hist_2 = (TH1F*)FileEsrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_E_srCSV_hist_3 = (TH1F*)FileEsrCSV->Get("pt_2_csv");
    TH1F* pt_cuts_F_srCSV_hist_1 = (TH1F*)FileFsrCSV->Get("pt_0_csv");
    TH1F* pt_cuts_F_srCSV_hist_2 = (TH1F*)FileFsrCSV->Get("pt_1_csv");
    TH1F* pt_cuts_F_srCSV_hist_3 = (TH1F*)FileFsrCSV->Get("pt_2_csv");

    TH1F* pt_cuts_C_crdeep_hist_1 = (TH1F*)FileCcrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_C_crdeep_hist_2 = (TH1F*)FileCcrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_C_crdeep_hist_3 = (TH1F*)FileCcrdeep->Get("pt_2_csv");
    TH1F* pt_cuts_D_crdeep_hist_1 = (TH1F*)FileDcrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_D_crdeep_hist_2 = (TH1F*)FileDcrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_D_crdeep_hist_3 = (TH1F*)FileDcrdeep->Get("pt_2_csv");
    TH1F* pt_cuts_E_crdeep_hist_1 = (TH1F*)FileEcrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_E_crdeep_hist_2 = (TH1F*)FileEcrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_E_crdeep_hist_3 = (TH1F*)FileEcrdeep->Get("pt_2_csv");
    TH1F* pt_cuts_F_crdeep_hist_1 = (TH1F*)FileFcrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_F_crdeep_hist_2 = (TH1F*)FileFcrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_F_crdeep_hist_3 = (TH1F*)FileFcrdeep->Get("pt_2_csv");

    TH1F* pt_cuts_C_srdeep_hist_1 = (TH1F*)FileCsrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_C_srdeep_hist_2 = (TH1F*)FileCsrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_C_srdeep_hist_3 = (TH1F*)FileCsrdeep->Get("pt_2_csv");
    TH1F* pt_cuts_D_srdeep_hist_1 = (TH1F*)FileDsrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_D_srdeep_hist_2 = (TH1F*)FileDsrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_D_srdeep_hist_3 = (TH1F*)FileDsrdeep->Get("pt_2_csv");
    TH1F* pt_cuts_E_srdeep_hist_1 = (TH1F*)FileEsrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_E_srdeep_hist_2 = (TH1F*)FileEsrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_E_srdeep_hist_3 = (TH1F*)FileEsrdeep->Get("pt_2_csv");
    TH1F* pt_cuts_F_srdeep_hist_1 = (TH1F*)FileFsrdeep->Get("pt_0_csv");
    TH1F* pt_cuts_F_srdeep_hist_2 = (TH1F*)FileFsrdeep->Get("pt_1_csv");
    TH1F* pt_cuts_F_srdeep_hist_3 = (TH1F*)FileFsrdeep->Get("pt_2_csv");

    TCanvas* pt_cuts_1_crCSV_can = style.MakeCanvas("pt_cuts_1_crCSV_can","pt 1st jet cuts (CR, CSV)",700,700);
    pt_cuts_1_crCSV_can -> SetLogy();
    style.InitHist(pt_cuts_C_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kBlack,0);
    pt_cuts_C_crCSV_hist_1->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_crCSV_hist_1->Draw();
    style.InitHist(pt_cuts_D_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kRed,0);
    pt_cuts_D_crCSV_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_E_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kBlue,0);
    pt_cuts_E_crCSV_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_F_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kGreen,0);
    pt_cuts_F_crCSV_hist_1->Draw("SAME");

    TLegend* legpt1acCRcsv = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt1acCRcsv);
    legpt1acCRcsv->SetNColumns(2);
    legpt1acCRcsv->AddEntry(pt_cuts_C_crCSV_hist_1,"era C","L");
    legpt1acCRcsv->AddEntry(pt_cuts_D_crCSV_hist_1,"era D","L");
    legpt1acCRcsv->AddEntry(pt_cuts_E_crCSV_hist_1,"era E","L");
    legpt1acCRcsv->AddEntry(pt_cuts_F_crCSV_hist_1,"era F","L");
    legpt1acCRcsv->Draw("SAME");
    
    TCanvas* pt_cuts_2_crCSV_can = style.MakeCanvas("pt_cuts_2_crCSV_can","pt 2nd jet cuts (CR, CSV)",700,700);
    pt_cuts_2_crCSV_can -> SetLogy();
    style.InitHist(pt_cuts_C_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kBlack,0);
    pt_cuts_C_crCSV_hist_2->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_crCSV_hist_2->Draw();
    style.InitHist(pt_cuts_D_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kRed,0);
    pt_cuts_D_crCSV_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_E_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kBlue,0);
    pt_cuts_E_crCSV_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_F_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kGreen,0);
    pt_cuts_F_crCSV_hist_2->Draw("SAME");

    TLegend* legpt2acCRcsv = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt2acCRcsv);
    legpt2acCRcsv->SetNColumns(2);
    legpt2acCRcsv->AddEntry(pt_cuts_C_crCSV_hist_2,"era C","L");
    legpt2acCRcsv->AddEntry(pt_cuts_D_crCSV_hist_2,"era D","L");
    legpt2acCRcsv->AddEntry(pt_cuts_E_crCSV_hist_2,"era E","L");
    legpt2acCRcsv->AddEntry(pt_cuts_F_crCSV_hist_2,"era F","L");
    legpt2acCRcsv->Draw("SAME");
    
    TCanvas* pt_cuts_3_crCSV_can = style.MakeCanvas("pt_cuts_3_crCSV_can","pt 3rd jet cuts (CR, CSV)",700,700);
    pt_cuts_3_crCSV_can -> SetLogy();
    style.InitHist(pt_cuts_C_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kBlack,0);
    pt_cuts_C_crCSV_hist_3->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_crCSV_hist_3->Draw();
    style.InitHist(pt_cuts_D_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kRed,0);
    pt_cuts_D_crCSV_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_E_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kBlue,0);
    pt_cuts_E_crCSV_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_F_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kGreen,0);
    pt_cuts_F_crCSV_hist_3->Draw("SAME");

    TLegend* legpt3acCRcsv = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt3acCRcsv);
    legpt3acCRcsv->SetNColumns(2);
    legpt3acCRcsv->AddEntry(pt_cuts_C_crCSV_hist_3,"era C","L");
    legpt3acCRcsv->AddEntry(pt_cuts_D_crCSV_hist_3,"era D","L");
    legpt3acCRcsv->AddEntry(pt_cuts_E_crCSV_hist_3,"era E","L");
    legpt3acCRcsv->AddEntry(pt_cuts_F_crCSV_hist_3,"era F","L");
    legpt3acCRcsv->Draw("SAME");

    TCanvas* pt_cuts_1_srCSV_can = style.MakeCanvas("pt_cuts_1_srCSV_can","pt 1st jet cuts (SR, CSV)",700,700);
    pt_cuts_1_srCSV_can -> SetLogy();
    style.InitHist(pt_cuts_C_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kBlack,0);
    pt_cuts_C_srCSV_hist_1->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_srCSV_hist_1->Draw();
    style.InitHist(pt_cuts_D_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kRed,0);
    pt_cuts_D_srCSV_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_E_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kBlue,0);
    pt_cuts_E_srCSV_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_F_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kGreen,0);
    pt_cuts_F_srCSV_hist_1->Draw("SAME");

    TLegend* legpt1acSRcsv = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt1acSRcsv);
    legpt1acSRcsv->SetNColumns(2);
    legpt1acSRcsv->AddEntry(pt_cuts_C_srCSV_hist_1,"era C","L");
    legpt1acSRcsv->AddEntry(pt_cuts_D_srCSV_hist_1,"era D","L");
    legpt1acSRcsv->AddEntry(pt_cuts_E_srCSV_hist_1,"era E","L");
    legpt1acSRcsv->AddEntry(pt_cuts_F_srCSV_hist_1,"era F","L");
    legpt1acSRcsv->Draw("SAME");
    
    TCanvas* pt_cuts_2_srCSV_can = style.MakeCanvas("pt_cuts_2_srCSV_can","pt 2nd jet cuts (SR, CSV)",700,700);
    pt_cuts_2_srCSV_can -> SetLogy();
    style.InitHist(pt_cuts_C_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kBlack,0);
    pt_cuts_C_srCSV_hist_2->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_srCSV_hist_2->Draw();
    style.InitHist(pt_cuts_D_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kRed,0);
    pt_cuts_D_srCSV_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_E_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kBlue,0);
    pt_cuts_E_srCSV_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_F_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kGreen,0);
    pt_cuts_F_srCSV_hist_2->Draw("SAME");

    TLegend* legpt2acSRcsv = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt2acSRcsv);
    legpt2acSRcsv->SetNColumns(2);
    legpt2acSRcsv->AddEntry(pt_cuts_C_srCSV_hist_2,"era C","L");
    legpt2acSRcsv->AddEntry(pt_cuts_D_srCSV_hist_2,"era D","L");
    legpt2acSRcsv->AddEntry(pt_cuts_E_srCSV_hist_2,"era E","L");
    legpt2acSRcsv->AddEntry(pt_cuts_F_srCSV_hist_2,"era F","L");
    legpt2acSRcsv->Draw("SAME");
    
    TCanvas* pt_cuts_3_srCSV_can = style.MakeCanvas("pt_cuts_3_srCSV_can","pt 3rd jet cuts (SR, CSV)",700,700);
    pt_cuts_3_srCSV_can -> SetLogy();
    style.InitHist(pt_cuts_C_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kBlack,0);
    pt_cuts_C_srCSV_hist_3->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_srCSV_hist_3->Draw();
    style.InitHist(pt_cuts_D_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kRed,0);
    pt_cuts_D_srCSV_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_E_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kBlue,0);
    pt_cuts_E_srCSV_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_F_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kGreen,0);
    pt_cuts_F_srCSV_hist_3->Draw("SAME");

    TLegend* legpt3acSRcsv = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt3acSRcsv);
    legpt3acSRcsv->SetNColumns(2);
    legpt3acSRcsv->AddEntry(pt_cuts_C_srCSV_hist_3,"era C","L");
    legpt3acSRcsv->AddEntry(pt_cuts_D_srCSV_hist_3,"era D","L");
    legpt3acSRcsv->AddEntry(pt_cuts_E_srCSV_hist_3,"era E","L");
    legpt3acSRcsv->AddEntry(pt_cuts_F_srCSV_hist_3,"era F","L");
    legpt3acSRcsv->Draw("SAME");
    
    TCanvas* pt_cuts_1_crdeep_can = style.MakeCanvas("pt_cuts_1_crdeep_can","pt 1st jet cuts (CR, deep)",700,700);
    pt_cuts_1_crdeep_can -> SetLogy();
    style.InitHist(pt_cuts_C_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kBlack,0);
    pt_cuts_C_crdeep_hist_1->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_crdeep_hist_1->Draw();
    style.InitHist(pt_cuts_D_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kRed,0);
    pt_cuts_D_crdeep_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_E_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kBlue,0);
    pt_cuts_E_crdeep_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_F_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kGreen,0);
    pt_cuts_F_crdeep_hist_1->Draw("SAME");

    TLegend* legpt1acCRdeep = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt1acCRdeep);
    legpt1acCRdeep->SetNColumns(2);
    legpt1acCRdeep->AddEntry(pt_cuts_C_crdeep_hist_1,"era C","L");
    legpt1acCRdeep->AddEntry(pt_cuts_D_crdeep_hist_1,"era D","L");
    legpt1acCRdeep->AddEntry(pt_cuts_E_crdeep_hist_1,"era E","L");
    legpt1acCRdeep->AddEntry(pt_cuts_F_crdeep_hist_1,"era F","L");
    legpt1acCRdeep->Draw("SAME");
    
    TCanvas* pt_cuts_2_crdeep_can = style.MakeCanvas("pt_cuts_2_crdeep_can","pt 2nd jet cuts (CR, deep)",700,700);
    pt_cuts_2_crdeep_can -> SetLogy();
    style.InitHist(pt_cuts_C_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kBlack,0);
    pt_cuts_C_crdeep_hist_2->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_crdeep_hist_2->Draw();
    style.InitHist(pt_cuts_D_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kRed,0);
    pt_cuts_D_crdeep_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_E_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kBlue,0);
    pt_cuts_E_crdeep_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_F_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kGreen,0);
    pt_cuts_F_crdeep_hist_2->Draw("SAME");

    TLegend* legpt2acCRdeep = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt2acCRdeep);
    legpt2acCRdeep->SetNColumns(2);
    legpt2acCRdeep->AddEntry(pt_cuts_C_crdeep_hist_2,"era C","L");
    legpt2acCRdeep->AddEntry(pt_cuts_D_crdeep_hist_2,"era D","L");
    legpt2acCRdeep->AddEntry(pt_cuts_E_crdeep_hist_2,"era E","L");
    legpt2acCRdeep->AddEntry(pt_cuts_F_crdeep_hist_2,"era F","L");
    legpt2acCRdeep->Draw("SAME");
    
    TCanvas* pt_cuts_3_crdeep_can = style.MakeCanvas("pt_cuts_3_crdeep_can","pt 3rd jet cuts (CR, deep)",700,700);
    pt_cuts_3_crdeep_can -> SetLogy();
    style.InitHist(pt_cuts_C_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kBlack,0);
    pt_cuts_C_crdeep_hist_3->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_crdeep_hist_3->Draw();
    style.InitHist(pt_cuts_D_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kRed,0);
    pt_cuts_D_crdeep_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_E_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kBlue,0);
    pt_cuts_E_crdeep_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_F_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kGreen,0);
    pt_cuts_F_crdeep_hist_3->Draw("SAME");

    TLegend* legpt3acCRdeep = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt3acCRdeep);
    legpt3acCRdeep->SetNColumns(2);
    legpt3acCRdeep->AddEntry(pt_cuts_C_crdeep_hist_3,"era C","L");
    legpt3acCRdeep->AddEntry(pt_cuts_D_crdeep_hist_3,"era D","L");
    legpt3acCRdeep->AddEntry(pt_cuts_E_crdeep_hist_3,"era E","L");
    legpt3acCRdeep->AddEntry(pt_cuts_F_crdeep_hist_3,"era F","L");
    legpt3acCRdeep->Draw("SAME");

    TCanvas* pt_cuts_1_srdeep_can = style.MakeCanvas("pt_cuts_1_srdeep_can","pt 1st jet cuts (SR, deep)",700,700);
    pt_cuts_1_srdeep_can -> SetLogy();
    style.InitHist(pt_cuts_C_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kBlack,0);
    pt_cuts_C_srdeep_hist_1->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_srdeep_hist_1->Draw();
    style.InitHist(pt_cuts_D_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kRed,0);
    pt_cuts_D_srdeep_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_E_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kBlue,0);
    pt_cuts_E_srdeep_hist_1->Draw("SAME");
    style.InitHist(pt_cuts_F_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kGreen,0);
    pt_cuts_F_srdeep_hist_1->Draw("SAME");

    TLegend* legpt1acSRdeep = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt1acSRdeep);
    legpt1acSRdeep->SetNColumns(2);
    legpt1acSRdeep->AddEntry(pt_cuts_C_srdeep_hist_1,"era C","L");
    legpt1acSRdeep->AddEntry(pt_cuts_D_srdeep_hist_1,"era D","L");
    legpt1acSRdeep->AddEntry(pt_cuts_E_srdeep_hist_1,"era E","L");
    legpt1acSRdeep->AddEntry(pt_cuts_F_srdeep_hist_1,"era F","L");
    legpt1acSRdeep->Draw("SAME");
    
    TCanvas* pt_cuts_2_srdeep_can = style.MakeCanvas("pt_cuts_2_srdeep_can","pt 2nd jet cuts (SR, deep)",700,700);
    pt_cuts_2_srdeep_can -> SetLogy();
    style.InitHist(pt_cuts_C_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kBlack,0);
    pt_cuts_C_srdeep_hist_2->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_srdeep_hist_2->Draw();
    style.InitHist(pt_cuts_D_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kRed,0);
    pt_cuts_D_srdeep_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_E_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kBlue,0);
    pt_cuts_E_srdeep_hist_2->Draw("SAME");
    style.InitHist(pt_cuts_F_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kGreen,0);
    pt_cuts_F_srdeep_hist_2->Draw("SAME");

    TLegend* legpt2acSRdeep = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt2acSRdeep);
    legpt2acSRdeep->SetNColumns(2);
    legpt2acSRdeep->AddEntry(pt_cuts_C_srdeep_hist_2,"era C","L");
    legpt2acSRdeep->AddEntry(pt_cuts_D_srdeep_hist_2,"era D","L");
    legpt2acSRdeep->AddEntry(pt_cuts_E_srdeep_hist_2,"era E","L");
    legpt2acSRdeep->AddEntry(pt_cuts_F_srdeep_hist_2,"era F","L");
    legpt2acSRdeep->Draw("SAME");

    TCanvas* pt_cuts_3_srdeep_can = style.MakeCanvas("pt_cuts_3_srdeep_can","pt 3rd jet cuts (SR, deep)",700,700);
    pt_cuts_3_srdeep_can -> SetLogy();
    style.InitHist(pt_cuts_C_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kBlack,0);
    pt_cuts_C_srdeep_hist_3->GetYaxis()->SetRangeUser(0.1,100000);
    pt_cuts_C_srdeep_hist_3->Draw();
    style.InitHist(pt_cuts_D_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kRed,0);
    pt_cuts_D_srdeep_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_E_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kBlue,0);
    pt_cuts_E_srdeep_hist_3->Draw("SAME");
    style.InitHist(pt_cuts_F_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kGreen,0);
    pt_cuts_F_srdeep_hist_3->Draw("SAME");

    TLegend* legpt3acSRdeep = new TLegend(0.5,0.65,0.95,0.9);
    style.SetLegendStyle(legpt3acSRdeep);
    legpt3acSRdeep->SetNColumns(2);
    legpt3acSRdeep->AddEntry(pt_cuts_C_srdeep_hist_3,"era C","L");
    legpt3acSRdeep->AddEntry(pt_cuts_D_srdeep_hist_3,"era D","L");
    legpt3acSRdeep->AddEntry(pt_cuts_E_srdeep_hist_3,"era E","L");
    legpt3acSRdeep->AddEntry(pt_cuts_F_srdeep_hist_3,"era F","L");
    legpt3acSRdeep->Draw("SAME");
  }

  if (etaaftercuts){
    TH1F* eta_cuts_C_crCSV_hist_1 = (TH1F*)FileCcrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_C_crCSV_hist_2 = (TH1F*)FileCcrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_C_crCSV_hist_3 = (TH1F*)FileCcrCSV->Get("eta_2_csv");
    TH1F* eta_cuts_D_crCSV_hist_1 = (TH1F*)FileDcrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_D_crCSV_hist_2 = (TH1F*)FileDcrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_D_crCSV_hist_3 = (TH1F*)FileDcrCSV->Get("eta_2_csv");
    TH1F* eta_cuts_E_crCSV_hist_1 = (TH1F*)FileEcrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_E_crCSV_hist_2 = (TH1F*)FileEcrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_E_crCSV_hist_3 = (TH1F*)FileEcrCSV->Get("eta_2_csv");
    TH1F* eta_cuts_F_crCSV_hist_1 = (TH1F*)FileFcrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_F_crCSV_hist_2 = (TH1F*)FileFcrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_F_crCSV_hist_3 = (TH1F*)FileFcrCSV->Get("eta_2_csv");

    TH1F* eta_cuts_C_srCSV_hist_1 = (TH1F*)FileCsrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_C_srCSV_hist_2 = (TH1F*)FileCsrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_C_srCSV_hist_3 = (TH1F*)FileCsrCSV->Get("eta_2_csv");
    TH1F* eta_cuts_D_srCSV_hist_1 = (TH1F*)FileDsrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_D_srCSV_hist_2 = (TH1F*)FileDsrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_D_srCSV_hist_3 = (TH1F*)FileDsrCSV->Get("eta_2_csv");
    TH1F* eta_cuts_E_srCSV_hist_1 = (TH1F*)FileEsrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_E_srCSV_hist_2 = (TH1F*)FileEsrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_E_srCSV_hist_3 = (TH1F*)FileEsrCSV->Get("eta_2_csv");
    TH1F* eta_cuts_F_srCSV_hist_1 = (TH1F*)FileFsrCSV->Get("eta_0_csv");
    TH1F* eta_cuts_F_srCSV_hist_2 = (TH1F*)FileFsrCSV->Get("eta_1_csv");
    TH1F* eta_cuts_F_srCSV_hist_3 = (TH1F*)FileFsrCSV->Get("eta_2_csv");

    TH1F* eta_cuts_C_crdeep_hist_1 = (TH1F*)FileCcrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_C_crdeep_hist_2 = (TH1F*)FileCcrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_C_crdeep_hist_3 = (TH1F*)FileCcrdeep->Get("eta_2_csv");
    TH1F* eta_cuts_D_crdeep_hist_1 = (TH1F*)FileDcrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_D_crdeep_hist_2 = (TH1F*)FileDcrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_D_crdeep_hist_3 = (TH1F*)FileDcrdeep->Get("eta_2_csv");
    TH1F* eta_cuts_E_crdeep_hist_1 = (TH1F*)FileEcrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_E_crdeep_hist_2 = (TH1F*)FileEcrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_E_crdeep_hist_3 = (TH1F*)FileEcrdeep->Get("eta_2_csv");
    TH1F* eta_cuts_F_crdeep_hist_1 = (TH1F*)FileFcrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_F_crdeep_hist_2 = (TH1F*)FileFcrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_F_crdeep_hist_3 = (TH1F*)FileFcrdeep->Get("eta_2_csv");

    TH1F* eta_cuts_C_srdeep_hist_1 = (TH1F*)FileCsrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_C_srdeep_hist_2 = (TH1F*)FileCsrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_C_srdeep_hist_3 = (TH1F*)FileCsrdeep->Get("eta_2_csv");
    TH1F* eta_cuts_D_srdeep_hist_1 = (TH1F*)FileDsrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_D_srdeep_hist_2 = (TH1F*)FileDsrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_D_srdeep_hist_3 = (TH1F*)FileDsrdeep->Get("eta_2_csv");
    TH1F* eta_cuts_E_srdeep_hist_1 = (TH1F*)FileEsrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_E_srdeep_hist_2 = (TH1F*)FileEsrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_E_srdeep_hist_3 = (TH1F*)FileEsrdeep->Get("eta_2_csv");
    TH1F* eta_cuts_F_srdeep_hist_1 = (TH1F*)FileFsrdeep->Get("eta_0_csv");
    TH1F* eta_cuts_F_srdeep_hist_2 = (TH1F*)FileFsrdeep->Get("eta_1_csv");
    TH1F* eta_cuts_F_srdeep_hist_3 = (TH1F*)FileFsrdeep->Get("eta_2_csv");

    TCanvas* eta_cuts_1_crCSV_can = style.MakeCanvas("eta_cuts_1_crCSV_can","eta 1st jet cuts (CR, CSV)",700,700);
    eta_cuts_1_crCSV_can -> SetLogy();
    style.InitHist(eta_cuts_C_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kBlack,0);
    eta_cuts_C_crCSV_hist_1->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_crCSV_hist_1->Draw();
    style.InitHist(eta_cuts_D_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kRed,0);
    eta_cuts_D_crCSV_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_E_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kBlue,0);
    eta_cuts_E_crCSV_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_F_crCSV_hist_1,"p_{T}, after cuts, CR, CSV, first jet","Entries",kGreen,0);
    eta_cuts_F_crCSV_hist_1->Draw("SAME");

    TLegend* legeta1acCRcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta1acCRcsv);
    legeta1acCRcsv->SetNColumns(2);
    legeta1acCRcsv->AddEntry(eta_cuts_C_crCSV_hist_1,"era C","L");
    legeta1acCRcsv->AddEntry(eta_cuts_D_crCSV_hist_1,"era D","L");
    legeta1acCRcsv->AddEntry(eta_cuts_E_crCSV_hist_1,"era E","L");
    legeta1acCRcsv->AddEntry(eta_cuts_F_crCSV_hist_1,"era F","L");
    legeta1acCRcsv->Draw("SAME");
    
    TCanvas* eta_cuts_2_crCSV_can = style.MakeCanvas("eta_cuts_2_crCSV_can","eta 2nd jet cuts (CR, CSV)",700,700);
    eta_cuts_2_crCSV_can -> SetLogy();
    style.InitHist(eta_cuts_C_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kBlack,0);
    eta_cuts_C_crCSV_hist_2->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_crCSV_hist_2->Draw();
    style.InitHist(eta_cuts_D_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kRed,0);
    eta_cuts_D_crCSV_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_E_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kBlue,0);
    eta_cuts_E_crCSV_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_F_crCSV_hist_2,"p_{T}, after cuts, CR, CSV, second jet","Entries",kGreen,0);
    eta_cuts_F_crCSV_hist_2->Draw("SAME");

    TLegend* legeta2acCRcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta2acCRcsv);
    legeta2acCRcsv->SetNColumns(2);
    legeta2acCRcsv->AddEntry(eta_cuts_C_crCSV_hist_2,"era C","L");
    legeta2acCRcsv->AddEntry(eta_cuts_D_crCSV_hist_2,"era D","L");
    legeta2acCRcsv->AddEntry(eta_cuts_E_crCSV_hist_2,"era E","L");
    legeta2acCRcsv->AddEntry(eta_cuts_F_crCSV_hist_2,"era F","L");
    legeta2acCRcsv->Draw("SAME");
    
    TCanvas* eta_cuts_3_crCSV_can = style.MakeCanvas("eta_cuts_3_crCSV_can","eta 3rd jet cuts (CR, CSV)",700,700);
    eta_cuts_3_crCSV_can -> SetLogy();
    style.InitHist(eta_cuts_C_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kBlack,0);
    eta_cuts_C_crCSV_hist_3->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_crCSV_hist_3->Draw();
    style.InitHist(eta_cuts_D_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kRed,0);
    eta_cuts_D_crCSV_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_E_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kBlue,0);
    eta_cuts_E_crCSV_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_F_crCSV_hist_3,"p_{T}, after cuts, CR, CSV, third jet","Entries",kGreen,0);
    eta_cuts_F_crCSV_hist_3->Draw("SAME");

    TLegend* legeta3acCRcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta3acCRcsv);
    legeta3acCRcsv->SetNColumns(2);
    legeta3acCRcsv->AddEntry(eta_cuts_C_crCSV_hist_3,"era C","L");
    legeta3acCRcsv->AddEntry(eta_cuts_D_crCSV_hist_3,"era D","L");
    legeta3acCRcsv->AddEntry(eta_cuts_E_crCSV_hist_3,"era E","L");
    legeta3acCRcsv->AddEntry(eta_cuts_F_crCSV_hist_3,"era F","L");
    legeta3acCRcsv->Draw("SAME");

    TCanvas* eta_cuts_1_srCSV_can = style.MakeCanvas("eta_cuts_1_srCSV_can","eta 1st jet cuts (SR, CSV)",700,700);
    eta_cuts_1_srCSV_can -> SetLogy();
    style.InitHist(eta_cuts_C_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kBlack,0);
    eta_cuts_C_srCSV_hist_1->GetYaxis()->SetRangeUser(0.1,100000);
    eta_cuts_C_srCSV_hist_1->Draw();
    style.InitHist(eta_cuts_D_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kRed,0);
    eta_cuts_D_srCSV_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_E_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kBlue,0);
    eta_cuts_E_srCSV_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_F_srCSV_hist_1,"p_{T}, after cuts, SR, CSV, first jet","Entries",kGreen,0);
    eta_cuts_F_srCSV_hist_1->Draw("SAME");

    TLegend* legeta1acSRcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta1acSRcsv);
    legeta1acSRcsv->SetNColumns(2);
    legeta1acSRcsv->AddEntry(eta_cuts_C_srCSV_hist_1,"era C","L");
    legeta1acSRcsv->AddEntry(eta_cuts_D_srCSV_hist_1,"era D","L");
    legeta1acSRcsv->AddEntry(eta_cuts_E_srCSV_hist_1,"era E","L");
    legeta1acSRcsv->AddEntry(eta_cuts_F_srCSV_hist_1,"era F","L");
    legeta1acSRcsv->Draw("SAME");
    
    TCanvas* eta_cuts_2_srCSV_can = style.MakeCanvas("eta_cuts_2_srCSV_can","eta 2nd jet cuts (SR, CSV)",700,700);
    eta_cuts_2_srCSV_can -> SetLogy();
    style.InitHist(eta_cuts_C_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kBlack,0);
    eta_cuts_C_srCSV_hist_2->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_srCSV_hist_2->Draw();
    style.InitHist(eta_cuts_D_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kRed,0);
    eta_cuts_D_srCSV_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_E_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kBlue,0);
    eta_cuts_E_srCSV_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_F_srCSV_hist_2,"p_{T}, after cuts, SR, CSV, second jet","Entries",kGreen,0);
    eta_cuts_F_srCSV_hist_2->Draw("SAME");

    TLegend* legeta2acSRcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta2acSRcsv);
    legeta2acSRcsv->SetNColumns(2);
    legeta2acSRcsv->AddEntry(eta_cuts_C_srCSV_hist_2,"era C","L");
    legeta2acSRcsv->AddEntry(eta_cuts_D_srCSV_hist_2,"era D","L");
    legeta2acSRcsv->AddEntry(eta_cuts_E_srCSV_hist_2,"era E","L");
    legeta2acSRcsv->AddEntry(eta_cuts_F_srCSV_hist_2,"era F","L");
    legeta2acSRcsv->Draw("SAME");
    
    TCanvas* eta_cuts_3_srCSV_can = style.MakeCanvas("eta_cuts_3_srCSV_can","eta 3rd jet cuts (SR, CSV)",700,700);
    eta_cuts_3_srCSV_can -> SetLogy();
    style.InitHist(eta_cuts_C_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kBlack,0);
    eta_cuts_C_srCSV_hist_3->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_srCSV_hist_3->Draw();
    style.InitHist(eta_cuts_D_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kRed,0);
    eta_cuts_D_srCSV_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_E_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kBlue,0);
    eta_cuts_E_srCSV_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_F_srCSV_hist_3,"p_{T}, after cuts, SR, CSV, third jet","Entries",kGreen,0);
    eta_cuts_F_srCSV_hist_3->Draw("SAME");

    TLegend* legeta3acSRcsv = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta3acSRcsv);
    legeta3acSRcsv->SetNColumns(2);
    legeta3acSRcsv->AddEntry(eta_cuts_C_srCSV_hist_3,"era C","L");
    legeta3acSRcsv->AddEntry(eta_cuts_D_srCSV_hist_3,"era D","L");
    legeta3acSRcsv->AddEntry(eta_cuts_E_srCSV_hist_3,"era E","L");
    legeta3acSRcsv->AddEntry(eta_cuts_F_srCSV_hist_3,"era F","L");
    legeta3acSRcsv->Draw("SAME");
    
    TCanvas* eta_cuts_1_crdeep_can = style.MakeCanvas("eta_cuts_1_crdeep_can","eta 1st jet cuts (CR, deep)",700,700);
    eta_cuts_1_crdeep_can -> SetLogy();
    style.InitHist(eta_cuts_C_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kBlack,0);
    eta_cuts_C_crdeep_hist_1->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_crdeep_hist_1->Draw();
    style.InitHist(eta_cuts_D_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kRed,0);
    eta_cuts_D_crdeep_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_E_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kBlue,0);
    eta_cuts_E_crdeep_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_F_crdeep_hist_1,"p_{T}, after cuts, CR, deep CSV, first jet","Entries",kGreen,0);
    eta_cuts_F_crdeep_hist_1->Draw("SAME");

    TLegend* legeta1acCRdeep = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta1acCRdeep);
    legeta1acCRdeep->SetNColumns(2);
    legeta1acCRdeep->AddEntry(eta_cuts_C_crdeep_hist_1,"era C","L");
    legeta1acCRdeep->AddEntry(eta_cuts_D_crdeep_hist_1,"era D","L");
    legeta1acCRdeep->AddEntry(eta_cuts_E_crdeep_hist_1,"era E","L");
    legeta1acCRdeep->AddEntry(eta_cuts_F_crdeep_hist_1,"era F","L");
    legeta1acCRdeep->Draw("SAME");
    
    TCanvas* eta_cuts_2_crdeep_can = style.MakeCanvas("eta_cuts_2_crdeep_can","eta 2nd jet cuts (CR, deep)",700,700);
    eta_cuts_2_crdeep_can -> SetLogy();
    style.InitHist(eta_cuts_C_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kBlack,0);
    eta_cuts_C_crdeep_hist_2->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_crdeep_hist_2->Draw();
    style.InitHist(eta_cuts_D_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kRed,0);
    eta_cuts_D_crdeep_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_E_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kBlue,0);
    eta_cuts_E_crdeep_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_F_crdeep_hist_2,"p_{T}, after cuts, CR, deep CSV, second jet","Entries",kGreen,0);
    eta_cuts_F_crdeep_hist_2->Draw("SAME");

    TLegend* legeta2acCRdeep = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta2acCRdeep);
    legeta2acCRdeep->SetNColumns(2);
    legeta2acCRdeep->AddEntry(eta_cuts_C_crdeep_hist_2,"era C","L");
    legeta2acCRdeep->AddEntry(eta_cuts_D_crdeep_hist_2,"era D","L");
    legeta2acCRdeep->AddEntry(eta_cuts_E_crdeep_hist_2,"era E","L");
    legeta2acCRdeep->AddEntry(eta_cuts_F_crdeep_hist_2,"era F","L");
    legeta2acCRdeep->Draw("SAME");
    
    TCanvas* eta_cuts_3_crdeep_can = style.MakeCanvas("eta_cuts_3_crdeep_can","eta 3rd jet cuts (CR, deep)",700,700);
    eta_cuts_3_crdeep_can -> SetLogy();
    style.InitHist(eta_cuts_C_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kBlack,0);
    eta_cuts_C_crdeep_hist_3->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_crdeep_hist_3->Draw();
    style.InitHist(eta_cuts_D_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kRed,0);
    eta_cuts_D_crdeep_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_E_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kBlue,0);
    eta_cuts_E_crdeep_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_F_crdeep_hist_3,"p_{T}, after cuts, CR, deep CSV, third jet","Entries",kGreen,0);
    eta_cuts_F_crdeep_hist_3->Draw("SAME");

    TLegend* legeta3acCRdeep = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta3acCRdeep);
    legeta3acCRdeep->SetNColumns(2);
    legeta3acCRdeep->AddEntry(eta_cuts_C_crdeep_hist_3,"era C","L");
    legeta3acCRdeep->AddEntry(eta_cuts_D_crdeep_hist_3,"era D","L");
    legeta3acCRdeep->AddEntry(eta_cuts_E_crdeep_hist_3,"era E","L");
    legeta3acCRdeep->AddEntry(eta_cuts_F_crdeep_hist_3,"era F","L");
    legeta3acCRdeep->Draw("SAME");

    TCanvas* eta_cuts_1_srdeep_can = style.MakeCanvas("eta_cuts_1_srdeep_can","eta 1st jet cuts (SR, deep)",700,700);
    eta_cuts_1_srdeep_can -> SetLogy();
    style.InitHist(eta_cuts_C_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kBlack,0);
    eta_cuts_C_srdeep_hist_1->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_srdeep_hist_1->Draw();
    style.InitHist(eta_cuts_D_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kRed,0);
    eta_cuts_D_srdeep_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_E_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kBlue,0);
    eta_cuts_E_srdeep_hist_1->Draw("SAME");
    style.InitHist(eta_cuts_F_srdeep_hist_1,"p_{T}, after cuts, SR, deep CSV, first jet","Entries",kGreen,0);
    eta_cuts_F_srdeep_hist_1->Draw("SAME");

    TLegend* legeta1acSRdeep = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta1acSRdeep);
    legeta1acSRdeep->SetNColumns(2);
    legeta1acSRdeep->AddEntry(eta_cuts_C_srdeep_hist_1,"era C","L");
    legeta1acSRdeep->AddEntry(eta_cuts_D_srdeep_hist_1,"era D","L");
    legeta1acSRdeep->AddEntry(eta_cuts_E_srdeep_hist_1,"era E","L");
    legeta1acSRdeep->AddEntry(eta_cuts_F_srdeep_hist_1,"era F","L");
    legeta1acSRdeep->Draw("SAME");
    
    TCanvas* eta_cuts_2_srdeep_can = style.MakeCanvas("eta_cuts_2_srdeep_can","eta 2nd jet cuts (SR, deep)",700,700);
    eta_cuts_2_srdeep_can -> SetLogy();
    style.InitHist(eta_cuts_C_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kBlack,0);
    eta_cuts_C_srdeep_hist_2->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_srdeep_hist_2->Draw();
    style.InitHist(eta_cuts_D_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kRed,0);
    eta_cuts_D_srdeep_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_E_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kBlue,0);
    eta_cuts_E_srdeep_hist_2->Draw("SAME");
    style.InitHist(eta_cuts_F_srdeep_hist_2,"p_{T}, after cuts, SR, deep CSV, second jet","Entries",kGreen,0);
    eta_cuts_F_srdeep_hist_2->Draw("SAME");

    TLegend* legeta2acSRdeep = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta2acSRdeep);
    legeta2acSRdeep->SetNColumns(2);
    legeta2acSRdeep->AddEntry(eta_cuts_C_srdeep_hist_2,"era C","L");
    legeta2acSRdeep->AddEntry(eta_cuts_D_srdeep_hist_2,"era D","L");
    legeta2acSRdeep->AddEntry(eta_cuts_E_srdeep_hist_2,"era E","L");
    legeta2acSRdeep->AddEntry(eta_cuts_F_srdeep_hist_2,"era F","L");
    legeta2acSRdeep->Draw("SAME");

    TCanvas* eta_cuts_3_srdeep_can = style.MakeCanvas("eta_cuts_3_srdeep_can","eta 3rd jet cuts (SR, deep)",700,700);
    eta_cuts_3_srdeep_can -> SetLogy();
    style.InitHist(eta_cuts_C_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kBlack,0);
    eta_cuts_C_srdeep_hist_3->GetYaxis()->SetRangeUser(10,100000);
    eta_cuts_C_srdeep_hist_3->Draw();
    style.InitHist(eta_cuts_D_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kRed,0);
    eta_cuts_D_srdeep_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_E_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kBlue,0);
    eta_cuts_E_srdeep_hist_3->Draw("SAME");
    style.InitHist(eta_cuts_F_srdeep_hist_3,"p_{T}, after cuts, SR, deep CSV, third jet","Entries",kGreen,0);
    eta_cuts_F_srdeep_hist_3->Draw("SAME");

    TLegend* legeta3acSRdeep = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta3acSRdeep);
    legeta3acSRdeep->SetNColumns(2);
    legeta3acSRdeep->AddEntry(eta_cuts_C_srdeep_hist_3,"era C","L");
    legeta3acSRdeep->AddEntry(eta_cuts_D_srdeep_hist_3,"era D","L");
    legeta3acSRdeep->AddEntry(eta_cuts_E_srdeep_hist_3,"era E","L");
    legeta3acSRdeep->AddEntry(eta_cuts_F_srdeep_hist_3,"era F","L");
    legeta3acSRdeep->Draw("SAME");
  }

  if(kinbefcuts){
    TH1F* pt_befcuts_C_hist_1 = (TH1F*)FileCcrCSV->Get("pt_0");
    TH1F* pt_befcuts_C_hist_2 = (TH1F*)FileCcrCSV->Get("pt_1");
    TH1F* pt_befcuts_C_hist_3 = (TH1F*)FileCcrCSV->Get("pt_2");
    TH1F* eta_befcuts_C_hist_1 = (TH1F*)FileCcrCSV->Get("eta_0");
    TH1F* eta_befcuts_C_hist_2 = (TH1F*)FileCcrCSV->Get("eta_1");
    TH1F* eta_befcuts_C_hist_3 = (TH1F*)FileCcrCSV->Get("eta_2");

    TH1F* pt_befcuts_D_hist_1 = (TH1F*)FileDcrCSV->Get("pt_0");
    TH1F* pt_befcuts_D_hist_2 = (TH1F*)FileDcrCSV->Get("pt_1");
    TH1F* pt_befcuts_D_hist_3 = (TH1F*)FileDcrCSV->Get("pt_2");
    TH1F* eta_befcuts_D_hist_1 = (TH1F*)FileDcrCSV->Get("eta_0");
    TH1F* eta_befcuts_D_hist_2 = (TH1F*)FileDcrCSV->Get("eta_1");
    TH1F* eta_befcuts_D_hist_3 = (TH1F*)FileDcrCSV->Get("eta_2");

    TH1F* pt_befcuts_E_hist_1 = (TH1F*)FileEcrCSV->Get("pt_0");
    TH1F* pt_befcuts_E_hist_2 = (TH1F*)FileEcrCSV->Get("pt_1");
    TH1F* pt_befcuts_E_hist_3 = (TH1F*)FileEcrCSV->Get("pt_2");
    TH1F* eta_befcuts_E_hist_1 = (TH1F*)FileEcrCSV->Get("eta_0");
    TH1F* eta_befcuts_E_hist_2 = (TH1F*)FileEcrCSV->Get("eta_1");
    TH1F* eta_befcuts_E_hist_3 = (TH1F*)FileEcrCSV->Get("eta_2");

    TH1F* pt_befcuts_F_hist_1 = (TH1F*)FileFcrCSV->Get("pt_0");
    TH1F* pt_befcuts_F_hist_2 = (TH1F*)FileFcrCSV->Get("pt_1");
    TH1F* pt_befcuts_F_hist_3 = (TH1F*)FileFcrCSV->Get("pt_2");
    TH1F* eta_befcuts_F_hist_1 = (TH1F*)FileFcrCSV->Get("eta_0");
    TH1F* eta_befcuts_F_hist_2 = (TH1F*)FileFcrCSV->Get("eta_1");
    TH1F* eta_befcuts_F_hist_3 = (TH1F*)FileFcrCSV->Get("eta_2");

    TCanvas* pt_befcuts_1_can = style.MakeCanvas("pt_befcuts_1_can","pt 1st jet before cuts",700,700);
    pt_befcuts_1_can -> SetLogy();
    style.InitHist(pt_befcuts_C_hist_1,"p_{T}, before cuts, first jet","Entries",kBlack,0);
    pt_befcuts_C_hist_1->GetYaxis()->SetRangeUser(0.1,1000000);
    pt_befcuts_C_hist_1->Draw();
    style.InitHist(pt_befcuts_D_hist_1,"p_{T}, before cuts, first jet","Entries",kRed,0);
    pt_befcuts_D_hist_1->Draw("SAME");
    style.InitHist(pt_befcuts_E_hist_1,"p_{T}, before cuts, first jet","Entries",kBlue,0);
    pt_befcuts_E_hist_1->Draw("SAME");
    style.InitHist(pt_befcuts_F_hist_1,"p_{T}, before cuts, first jet","Entries",kGreen,0);
    pt_befcuts_F_hist_1->Draw("SAME");

    TLegend* legpt1bc = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legpt1bc);
    legpt1bc->SetNColumns(2);
    legpt1bc->AddEntry(pt_befcuts_C_hist_1,"era C","L");
    legpt1bc->AddEntry(pt_befcuts_D_hist_1,"era D","L");
    legpt1bc->AddEntry(pt_befcuts_E_hist_1,"era E","L");
    legpt1bc->AddEntry(pt_befcuts_F_hist_1,"era F","L");
    legpt1bc->Draw("SAME");

    TCanvas* pt_befcuts_2_can = style.MakeCanvas("pt_befcuts_2_can","pt 2nd jet before cuts",700,700);
    pt_befcuts_2_can -> SetLogy();
    pt_befcuts_C_hist_2->GetYaxis()->SetRangeUser(0.1,1000000);
    style.InitHist(pt_befcuts_C_hist_2,"p_{T}, before cuts, second jet","Entries",kBlack,0);
    pt_befcuts_C_hist_2->Draw();
    style.InitHist(pt_befcuts_D_hist_2,"p_{T}, before cuts, second jet","Entries",kRed,0);
    pt_befcuts_D_hist_2->Draw("SAME");
    style.InitHist(pt_befcuts_E_hist_2,"p_{T}, before cuts, second jet","Entries",kBlue,0);
    pt_befcuts_E_hist_2->Draw("SAME");
    style.InitHist(pt_befcuts_F_hist_2,"p_{T}, before cuts, second jet","Entries",kGreen,0);
    pt_befcuts_F_hist_2->Draw("SAME");

    TLegend* legpt2bc = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legpt2bc);
    legpt2bc->SetNColumns(2);
    legpt2bc->AddEntry(pt_befcuts_C_hist_2,"era C","L");
    legpt2bc->AddEntry(pt_befcuts_D_hist_2,"era D","L");
    legpt2bc->AddEntry(pt_befcuts_E_hist_2,"era E","L");
    legpt2bc->AddEntry(pt_befcuts_F_hist_2,"era F","L");
    legpt2bc->Draw("SAME");

    TCanvas* pt_befcuts_3_can = style.MakeCanvas("pt_befcuts_3_can","pt 3rd jet before cuts",700,700);
    pt_befcuts_3_can -> SetLogy();
    style.InitHist(pt_befcuts_C_hist_3,"p_{T}, before cuts, third jet","Entries",kBlack,0);
    pt_befcuts_C_hist_3->GetYaxis()->SetRangeUser(0.1,1000000);
    pt_befcuts_C_hist_3->Draw();
    style.InitHist(pt_befcuts_D_hist_3,"p_{T}, before cuts, third jet","Entries",kRed,0);
    pt_befcuts_D_hist_3->Draw("SAME");
    style.InitHist(pt_befcuts_E_hist_3,"p_{T}, before cuts, third jet","Entries",kBlue,0);
    pt_befcuts_E_hist_3->Draw("SAME");
    style.InitHist(pt_befcuts_F_hist_3,"p_{T}, before cuts, third jet","Entries",kGreen,0);
    pt_befcuts_F_hist_3->Draw("SAME");

    TLegend* legpt3bc = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legpt3bc);
    legpt3bc->SetNColumns(2);
    legpt3bc->AddEntry(pt_befcuts_C_hist_3,"era C","L");
    legpt3bc->AddEntry(pt_befcuts_D_hist_3,"era D","L");
    legpt3bc->AddEntry(pt_befcuts_E_hist_3,"era E","L");
    legpt3bc->AddEntry(pt_befcuts_F_hist_3,"era F","L");
    legpt3bc->Draw("SAME");

    TCanvas* eta_befcuts_1_can = style.MakeCanvas("eta_befcuts_1_can","eta 1st jet before cuts",700,700);
    eta_befcuts_1_can -> SetLogy();
    style.InitHist(eta_befcuts_C_hist_1,"#eta, before cuts, first jet","Entries",kBlack,0);
    eta_befcuts_C_hist_1->GetYaxis()->SetRangeUser(1000,100000);
    eta_befcuts_C_hist_1->Draw();
    style.InitHist(eta_befcuts_D_hist_1,"#eta, before cuts, first jet","Entries",kRed,0);
    eta_befcuts_D_hist_1->Draw("SAME");
    style.InitHist(eta_befcuts_E_hist_1,"#eta, before cuts, first jet","Entries",kBlue,0);
    eta_befcuts_E_hist_1->Draw("SAME");
    style.InitHist(eta_befcuts_F_hist_1,"#eta, before cuts, first jet","Entries",kGreen,0);
    eta_befcuts_F_hist_1->Draw("SAME");

    TLegend* legeta1bc = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta1bc);
    legeta1bc->SetNColumns(2);
    legeta1bc->AddEntry(eta_befcuts_C_hist_1,"era C","L");
    legeta1bc->AddEntry(eta_befcuts_D_hist_1,"era D","L");
    legeta1bc->AddEntry(eta_befcuts_E_hist_1,"era E","L");
    legeta1bc->AddEntry(eta_befcuts_F_hist_1,"era F","L");
    legeta1bc->Draw("SAME");

    TCanvas* eta_befcuts_2_can = style.MakeCanvas("eta_befcuts_2_can","eta 2nd jet before cuts",700,700);
    eta_befcuts_2_can -> SetLogy();
    style.InitHist(eta_befcuts_C_hist_2,"#eta, before cuts, second jet","Entries",kBlack,0);
    eta_befcuts_C_hist_2->GetYaxis()->SetRangeUser(1000,100000);
    eta_befcuts_C_hist_2->Draw();
    style.InitHist(eta_befcuts_D_hist_2,"#eta, before cuts, second jet","Entries",kRed,0);
    eta_befcuts_D_hist_2->Draw("SAME");
    style.InitHist(eta_befcuts_E_hist_2,"#eta, before cuts, second jet","Entries",kBlue,0);
    eta_befcuts_E_hist_2->Draw("SAME");
    style.InitHist(eta_befcuts_F_hist_2,"#eta, before cuts, second jet","Entries",kGreen,0);
    eta_befcuts_F_hist_2->Draw("SAME");

    TLegend* legeta2bc = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta2bc);
    legeta2bc->SetNColumns(2);
    legeta2bc->AddEntry(eta_befcuts_C_hist_2,"era C","L");
    legeta2bc->AddEntry(eta_befcuts_D_hist_2,"era D","L");
    legeta2bc->AddEntry(eta_befcuts_E_hist_2,"era E","L");
    legeta2bc->AddEntry(eta_befcuts_F_hist_2,"era F","L");
    legeta2bc->Draw("SAME");

    TCanvas* eta_befcuts_3_can = style.MakeCanvas("eta_befcuts_3_can","eta 3rd jet before cuts",700,700);
    eta_befcuts_3_can -> SetLogy();
    style.InitHist(eta_befcuts_C_hist_3,"#eta, before cuts, third jet","Entries",kBlack,0);
    eta_befcuts_C_hist_3->GetYaxis()->SetRangeUser(1000,100000);
    eta_befcuts_C_hist_3->Draw();
    style.InitHist(eta_befcuts_D_hist_3,"#eta, before cuts, third jet","Entries",kRed,0);
    eta_befcuts_D_hist_3->Draw("SAME");
    style.InitHist(eta_befcuts_E_hist_3,"#eta, before cuts, third jet","Entries",kBlue,0);
    eta_befcuts_E_hist_3->Draw("SAME");
    style.InitHist(eta_befcuts_F_hist_3,"#eta, before cuts, third jet","Entries",kGreen,0);
    eta_befcuts_F_hist_3->Draw("SAME");

    TLegend* legeta3bc = new TLegend(0.35,0.65,0.8,0.9);
    style.SetLegendStyle(legeta3bc);
    legeta3bc->SetNColumns(2);
    legeta3bc->AddEntry(eta_befcuts_C_hist_3,"era C","L");
    legeta3bc->AddEntry(eta_befcuts_D_hist_3,"era D","L");
    legeta3bc->AddEntry(eta_befcuts_E_hist_3,"era E","L");
    legeta3bc->AddEntry(eta_befcuts_F_hist_3,"era F","L");
    legeta3bc->Draw("SAME");
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
