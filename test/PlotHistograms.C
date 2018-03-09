#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"

void PlotHistograms(){

  bool plotpt = false;
  bool ploteta = false;
  bool plotmass = false;
  bool plotDRj12mu = true;
  bool plotptall = false;
  bool plotetaall = false;
  bool plotmassall = false;
  bool plotDRj12muall = false;

  TFile* FileC = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/PlotsWithMuonInformation/histogramsC-mediumMuon-deepcsv_SR.root","READ");
  TFile* FileD = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/PlotsWithMuonInformation/histogramsD-mediumMuon-deepcsv_SR.root","READ");
  TFile* FileE = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/PlotsWithMuonInformation/histogramsE-mediumMuon-deepcsv_SR.root","READ");
  TFile* FileF = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/PlotsWithMuonInformation/histogramsF-mediumMuon-deepcsv_SR.root","READ");
  
  //no directory needed: all histograms are stored directly

  ///
  //pt//
  ///

  if(plotpt){
    TH1F* pt0C = (TH1F*)FileC->Get("pt_0"); pt0C->SetMarkerColor(2); pt0C->SetMarkerStyle(20);
    TH1F* pt0D = (TH1F*)FileD->Get("pt_0"); pt0D->SetMarkerColor(3); pt0D->SetMarkerStyle(20);
    TH1F* pt0E = (TH1F*)FileE->Get("pt_0"); pt0E->SetMarkerColor(4); pt0E->SetMarkerStyle(20);
    TH1F* pt0F = (TH1F*)FileF->Get("pt_0"); pt0F->SetMarkerColor(6); pt0F->SetMarkerStyle(20);
    TH1F* pt1C = (TH1F*)FileC->Get("pt_1"); pt1C->SetMarkerColor(2); pt1C->SetMarkerStyle(21);
    TH1F* pt1D = (TH1F*)FileD->Get("pt_1"); pt1D->SetMarkerColor(3); pt1D->SetMarkerStyle(21);
    TH1F* pt1E = (TH1F*)FileE->Get("pt_1"); pt1E->SetMarkerColor(4); pt1E->SetMarkerStyle(21);
    TH1F* pt1F = (TH1F*)FileF->Get("pt_1"); pt1F->SetMarkerColor(6); pt1F->SetMarkerStyle(21);
    TH1F* pt2C = (TH1F*)FileC->Get("pt_2"); pt2C->SetMarkerColor(2); pt2C->SetMarkerStyle(22);
    TH1F* pt2D = (TH1F*)FileD->Get("pt_2"); pt2D->SetMarkerColor(3); pt2D->SetMarkerStyle(22);
    TH1F* pt2E = (TH1F*)FileE->Get("pt_2"); pt2E->SetMarkerColor(4); pt2E->SetMarkerStyle(22);
    TH1F* pt2F = (TH1F*)FileF->Get("pt_2"); pt2F->SetMarkerColor(6); pt2F->SetMarkerStyle(22);

    TH1F* ptcsv0C = (TH1F*)FileC->Get("pt_0_csv"); ptcsv0C->SetMarkerColor(2); ptcsv0C->SetMarkerStyle(20);
    TH1F* ptcsv0D = (TH1F*)FileD->Get("pt_0_csv"); ptcsv0D->SetMarkerColor(3); ptcsv0D->SetMarkerStyle(20);
    TH1F* ptcsv0E = (TH1F*)FileE->Get("pt_0_csv"); ptcsv0E->SetMarkerColor(4); ptcsv0E->SetMarkerStyle(20);
    TH1F* ptcsv0F = (TH1F*)FileF->Get("pt_0_csv"); ptcsv0F->SetMarkerColor(6); ptcsv0F->SetMarkerStyle(20);
    TH1F* ptcsv1C = (TH1F*)FileC->Get("pt_1_csv"); ptcsv1C->SetMarkerColor(2); ptcsv1C->SetMarkerStyle(21);
    TH1F* ptcsv1D = (TH1F*)FileD->Get("pt_1_csv"); ptcsv1D->SetMarkerColor(3); ptcsv1D->SetMarkerStyle(21);
    TH1F* ptcsv1E = (TH1F*)FileE->Get("pt_1_csv"); ptcsv1E->SetMarkerColor(4); ptcsv1E->SetMarkerStyle(21);
    TH1F* ptcsv1F = (TH1F*)FileF->Get("pt_1_csv"); ptcsv1F->SetMarkerColor(6); ptcsv1F->SetMarkerStyle(21);
    TH1F* ptcsv2C = (TH1F*)FileC->Get("pt_2_csv"); ptcsv2C->SetMarkerColor(2); ptcsv2C->SetMarkerStyle(22);
    TH1F* ptcsv2D = (TH1F*)FileD->Get("pt_2_csv"); ptcsv2D->SetMarkerColor(3); ptcsv2D->SetMarkerStyle(22);
    TH1F* ptcsv2E = (TH1F*)FileE->Get("pt_2_csv"); ptcsv2E->SetMarkerColor(4); ptcsv2E->SetMarkerStyle(22);
    TH1F* ptcsv2F = (TH1F*)FileF->Get("pt_2_csv"); ptcsv2F->SetMarkerColor(6); ptcsv2F->SetMarkerStyle(22);

    TCanvas* ptall = new TCanvas("ptall","ptall",1000,1000);
    gStyle->SetOptStat(0);
    pt0C->GetYaxis()->SetRangeUser(0,120000);
    pt0C->Draw(); pt0D->Draw("SAME"); pt0E->Draw("SAME"); pt0F->Draw("SAME");
    pt1C->Draw("SAME"); pt1D->Draw("SAME"); pt1E->Draw("SAME"); pt1F->Draw("SAME");
    pt2C->Draw("SAME"); pt2D->Draw("SAME"); pt2E->Draw("SAME"); pt2F->Draw("SAME");
    TLegend* legptall = new TLegend(0.3,0.59,0.88,0.89);
    legptall -> SetBorderSize(0);
    legptall -> SetNColumns(3);
    legptall -> AddEntry(pt0C,"p_{T} of first jet, era C","p");
    legptall -> AddEntry(pt1C,"p_{T} of second jet, era C","p");
    legptall -> AddEntry(pt2C,"p_{T} of third jet, era C","p");
    legptall -> AddEntry(pt0D,"p_{T} of first jet, era D","p");
    legptall -> AddEntry(pt1D,"p_{T} of second jet, era D","p");
    legptall -> AddEntry(pt2D,"p_{T} of third jet, era D","p");
    legptall -> AddEntry(pt0E,"p_{T} of first jet, era E","p");
    legptall -> AddEntry(pt1E,"p_{T} of second jet, era E","p");
    legptall -> AddEntry(pt2E,"p_{T} of third jet, era E","p");
    legptall -> AddEntry(pt0F,"p_{T} of first jet, era F","p");
    legptall -> AddEntry(pt1F,"p_{T} of second jet, era F","p");
    legptall -> AddEntry(pt2F,"p_{T} of third jet, era F","p");
    legptall -> Draw();

    TCanvas* ptcsvall = new TCanvas("ptcsvall","ptcsvall",1000,1000);
    gStyle->SetOptStat(0);
    ptcsv0C->GetYaxis()->SetRangeUser(0,60000);
    ptcsv0C->Draw(); ptcsv0D->Draw("SAME"); ptcsv0E->Draw("SAME"); ptcsv0F->Draw("SAME");
    ptcsv1C->Draw("SAME"); ptcsv1D->Draw("SAME"); ptcsv1E->Draw("SAME"); ptcsv1F->Draw("SAME");
    ptcsv2C->Draw("SAME"); ptcsv2D->Draw("SAME"); ptcsv2E->Draw("SAME"); ptcsv2F->Draw("SAME");
    TLegend* legptcsvall = new TLegend(0.35,0.59,0.88,0.89);//CR
    legptcsvall -> SetBorderSize(0);
    legptcsvall -> SetNColumns(3);
    legptcsvall -> AddEntry(ptcsv0C,"p_{T} of first jet, era C, after cuts","p");
    legptcsvall -> AddEntry(ptcsv1C,"p_{T} of second jet, era C, after cuts","p");
    legptcsvall -> AddEntry(ptcsv2C,"p_{T} of third jet, era C, after cuts","p");
    legptcsvall -> AddEntry(ptcsv0D,"p_{T} of first jet, era D, after cuts","p");
    legptcsvall -> AddEntry(ptcsv1D,"p_{T} of second jet, era D, after cuts","p");
    legptcsvall -> AddEntry(ptcsv2D,"p_{T} of third jet, era D, after cuts","p");
    legptcsvall -> AddEntry(ptcsv0E,"p_{T} of first jet, era E, after cuts","p");
    legptcsvall -> AddEntry(ptcsv1E,"p_{T} of second jet, era E, after cuts","p");
    legptcsvall -> AddEntry(ptcsv2E,"p_{T} of third jet, era E, after cuts","p");
    legptcsvall -> AddEntry(ptcsv0F,"p_{T} of first jet, era F, after cuts","p");
    legptcsvall -> AddEntry(ptcsv1F,"p_{T} of second jet, era F, after cuts","p");
    legptcsvall -> AddEntry(ptcsv2F,"p_{T} of third jet, era F, after cuts","p");
    legptcsvall -> Draw();
  
    if(plotptall){
      TCanvas* ptC = new TCanvas("ptC","ptC",1000,1000);
      gStyle->SetOptStat(0);
      pt0C->GetYaxis()->SetRangeUser(0,60000);
      pt0C->Draw(); pt1C->Draw("SAME"); pt2C->Draw("SAME");
      TLegend* legptC = new TLegend(0.32,0.82,0.9,0.9);
      legptC -> SetNColumns(3);
      legptC -> AddEntry(pt0C,"p_{T} of first jet, era C","p");
      legptC -> AddEntry(pt1C,"p_{T} of second jet, era C","p");
      legptC -> AddEntry(pt2C,"p_{T} of third jet, era C","p");
      legptC -> Draw();

      TCanvas* ptcsvC = new TCanvas("ptcsvC","ptcsvC",1000,1000);
      gStyle->SetOptStat(0);
      ptcsv0C->GetYaxis()->SetRangeUser(0,60000);
      ptcsv0C->Draw(); ptcsv1C->Draw("SAME"); ptcsv2C->Draw("SAME");
      TLegend* legptcsvC = new TLegend(0.32,0.82,0.9,0.9);
      legptcsvC -> SetNColumns(3);
      legptcsvC -> AddEntry(ptcsv0C,"p_{T} of first jet, era C, after cuts","p");
      legptcsvC -> AddEntry(ptcsv1C,"p_{T} of second jet, era C, after cuts","p");
      legptcsvC -> AddEntry(ptcsv2C,"p_{T} of third jet, era C, after cuts","p");
      legptcsvC -> Draw();

      TCanvas* ptD = new TCanvas("ptD","ptD",1000,1000);
      gStyle->SetOptStat(0);
      pt0D->GetYaxis()->SetRangeUser(0,60000);
      pt0D->Draw(); pt1D->Draw("SAME"); pt2D->Draw("SAME");
      TLegend* legptD = new TLegend(0.32,0.82,0.9,0.9);
      legptD -> SetNColumns(3);
      legptD -> AddEntry(pt0D,"p_{T} of first jet, era D","p");
      legptD -> AddEntry(pt1D,"p_{T} of second jet, era D","p");
      legptD -> AddEntry(pt2D,"p_{T} of third jet, era D","p");
      legptD -> Draw();

      TCanvas* ptcsvD = new TCanvas("ptcsvD","ptcsvD",1000,1000);
      gStyle->SetOptStat(0);
      ptcsv0D->GetYaxis()->SetRangeUser(0,60000);
      ptcsv0D->Draw(); ptcsv1D->Draw("SAME"); ptcsv2D->Draw("SAME");
      TLegend* legptcsvD = new TLegend(0.32,0.82,0.9,0.9);
      legptcsvD -> SetNColumns(3);
      legptcsvD -> AddEntry(ptcsv0D,"p_{T} of first jet, era D, after cuts","p");
      legptcsvD -> AddEntry(ptcsv1D,"p_{T} of second jet, era D, after cuts","p");
      legptcsvD -> AddEntry(ptcsv2D,"p_{T} of third jet, era D, after cuts","p");
      legptcsvD -> Draw();

      TCanvas* ptE = new TCanvas("ptE","ptE",1000,1000);
      gStyle->SetOptStat(0);
      pt0E->GetYaxis()->SetRangeUser(0,60000);
      pt0E->Draw(); pt1E->Draw("SAME"); pt2E->Draw("SAME");
      TLegend* legptE = new TLegend(0.32,0.82,0.9,0.9);
      legptE -> SetNColumns(3);
      legptE -> AddEntry(pt0E,"p_{T} of first jet, era E","p");
      legptE -> AddEntry(pt1E,"p_{T} of second jet, era E","p");
      legptE -> AddEntry(pt2E,"p_{T} of third jet, era E","p");
      legptE -> Draw();

      TCanvas* ptcsvE = new TCanvas("ptcsvE","ptcsvE",1000,1000);
      gStyle->SetOptStat(0);
      ptcsv0E->GetYaxis()->SetRangeUser(0,60000);
      ptcsv0E->Draw(); ptcsv1E->Draw("SAME"); ptcsv2E->Draw("SAME");
      TLegend* legptcsvE = new TLegend(0.32,0.82,0.9,0.9);
      legptcsvE -> SetNColumns(3);
      legptcsvE -> AddEntry(ptcsv0E,"p_{T} of first jet, era E, after cuts","p");
      legptcsvE -> AddEntry(ptcsv1E,"p_{T} of second jet, era E, after cuts","p");
      legptcsvE -> AddEntry(ptcsv2E,"p_{T} of third jet, era E, after cuts","p");
      legptcsvE -> Draw();

      TCanvas* ptF = new TCanvas("ptF","ptF",1000,1000);
      gStyle->SetOptStat(0);
      pt0F->GetYaxis()->SetRangeUser(0,60000);
      pt0F->Draw(); pt1F->Draw("SAME"); pt2F->Draw("SAME");
      TLegend* legptF = new TLegend(0.32,0.82,0.9,0.9);
      legptF -> SetNColumns(3);
      legptF -> AddEntry(pt0F,"p_{T} of first jet, era F","p");
      legptF -> AddEntry(pt1F,"p_{T} of second jet, era F","p");
      legptF -> AddEntry(pt2F,"p_{T} of third jet, era F","p");
      legptF -> Draw();

      TCanvas* ptcsvF = new TCanvas("ptcsvF","ptcsvF",1000,1000);
      gStyle->SetOptStat(0);
      ptcsv0F->GetYaxis()->SetRangeUser(0,60000);
      ptcsv0F->Draw(); ptcsv1F->Draw("SAME"); ptcsv2F->Draw("SAME");
      TLegend* legptcsvF = new TLegend(0.32,0.82,0.9,0.9);
      legptcsvF -> SetNColumns(3);
      legptcsvF -> AddEntry(ptcsv0F,"p_{T} of first jet, era F, after cuts","p");
      legptcsvF -> AddEntry(ptcsv1F,"p_{T} of second jet, era F, after cuts","p");
      legptcsvF -> AddEntry(ptcsv2F,"p_{T} of third jet, era F, after cuts","p");
      legptcsvF -> Draw();
    }
  }

  ///
  //ETA//
  ///

  if(ploteta){
    TH1F* eta0C = (TH1F*)FileC->Get("eta_0"); eta0C->SetMarkerColor(2); eta0C->SetMarkerStyle(20);
    TH1F* eta0D = (TH1F*)FileD->Get("eta_0"); eta0D->SetMarkerColor(3); eta0D->SetMarkerStyle(20);
    TH1F* eta0E = (TH1F*)FileE->Get("eta_0"); eta0E->SetMarkerColor(4); eta0E->SetMarkerStyle(20);
    TH1F* eta0F = (TH1F*)FileF->Get("eta_0"); eta0F->SetMarkerColor(6); eta0F->SetMarkerStyle(20);
    TH1F* eta1C = (TH1F*)FileC->Get("eta_1"); eta1C->SetMarkerColor(2); eta1C->SetMarkerStyle(21);
    TH1F* eta1D = (TH1F*)FileD->Get("eta_1"); eta1D->SetMarkerColor(3); eta1D->SetMarkerStyle(21);
    TH1F* eta1E = (TH1F*)FileE->Get("eta_1"); eta1E->SetMarkerColor(4); eta1E->SetMarkerStyle(21);
    TH1F* eta1F = (TH1F*)FileF->Get("eta_1"); eta1F->SetMarkerColor(6); eta1F->SetMarkerStyle(21);
    TH1F* eta2C = (TH1F*)FileC->Get("eta_2"); eta2C->SetMarkerColor(2); eta2C->SetMarkerStyle(22);
    TH1F* eta2D = (TH1F*)FileD->Get("eta_2"); eta2D->SetMarkerColor(3); eta2D->SetMarkerStyle(22);
    TH1F* eta2E = (TH1F*)FileE->Get("eta_2"); eta2E->SetMarkerColor(4); eta2E->SetMarkerStyle(22);
    TH1F* eta2F = (TH1F*)FileF->Get("eta_2"); eta2F->SetMarkerColor(6); eta2F->SetMarkerStyle(22);

    TH1F* etacsv0C = (TH1F*)FileC->Get("eta_0_csv"); etacsv0C->SetMarkerColor(2); etacsv0C->SetMarkerStyle(20);
    TH1F* etacsv0D = (TH1F*)FileD->Get("eta_0_csv"); etacsv0D->SetMarkerColor(3); etacsv0D->SetMarkerStyle(20);
    TH1F* etacsv0E = (TH1F*)FileE->Get("eta_0_csv"); etacsv0E->SetMarkerColor(4); etacsv0E->SetMarkerStyle(20);
    TH1F* etacsv0F = (TH1F*)FileF->Get("eta_0_csv"); etacsv0F->SetMarkerColor(6); etacsv0F->SetMarkerStyle(20);
    TH1F* etacsv1C = (TH1F*)FileC->Get("eta_1_csv"); etacsv1C->SetMarkerColor(2); etacsv1C->SetMarkerStyle(21);
    TH1F* etacsv1D = (TH1F*)FileD->Get("eta_1_csv"); etacsv1D->SetMarkerColor(3); etacsv1D->SetMarkerStyle(21);
    TH1F* etacsv1E = (TH1F*)FileE->Get("eta_1_csv"); etacsv1E->SetMarkerColor(4); etacsv1E->SetMarkerStyle(21);
    TH1F* etacsv1F = (TH1F*)FileF->Get("eta_1_csv"); etacsv1F->SetMarkerColor(6); etacsv1F->SetMarkerStyle(21);
    TH1F* etacsv2C = (TH1F*)FileC->Get("eta_2_csv"); etacsv2C->SetMarkerColor(2); etacsv2C->SetMarkerStyle(22);
    TH1F* etacsv2D = (TH1F*)FileD->Get("eta_2_csv"); etacsv2D->SetMarkerColor(3); etacsv2D->SetMarkerStyle(22);
    TH1F* etacsv2E = (TH1F*)FileE->Get("eta_2_csv"); etacsv2E->SetMarkerColor(4); etacsv2E->SetMarkerStyle(22);
    TH1F* etacsv2F = (TH1F*)FileF->Get("eta_2_csv"); etacsv2F->SetMarkerColor(6); etacsv2F->SetMarkerStyle(22);
  
    TCanvas* etaall = new TCanvas("etaall","etaall",1000,1000);
    gStyle->SetOptStat(0);
    eta0C->GetYaxis()->SetRangeUser(0,50000);
    eta0C->Draw(); eta0D->Draw("SAME"); eta0E->Draw("SAME"); eta0F->Draw("SAME");
    eta1C->Draw("SAME"); eta1D->Draw("SAME"); eta1E->Draw("SAME"); eta1F->Draw("SAME");
    eta2C->Draw("SAME"); eta2D->Draw("SAME"); eta2E->Draw("SAME"); eta2F->Draw("SAME");
    TLegend* legetaall = new TLegend(0.12,0.59,0.89,0.89);
    legetaall -> SetBorderSize(0);
    legetaall -> SetNColumns(3);
    legetaall -> AddEntry(eta0C,"#eta of first jet, era C","p");
    legetaall -> AddEntry(eta1C,"#eta of second jet, era C","p");
    legetaall -> AddEntry(eta2C,"#eta of third jet, era C","p");
    legetaall -> AddEntry(eta0D,"#eta of first jet, era D","p");
    legetaall -> AddEntry(eta1D,"#eta of second jet, era D","p");
    legetaall -> AddEntry(eta2D,"#eta of third jet, era D","p");
    legetaall -> AddEntry(eta0E,"#eta of first jet, era E","p");
    legetaall -> AddEntry(eta1E,"#eta of second jet, era E","p");
    legetaall -> AddEntry(eta2E,"#eta of third jet, era E","p");
    legetaall -> AddEntry(eta0F,"#eta of first jet, era F","p");
    legetaall -> AddEntry(eta1F,"#eta of second jet, era F","p");
    legetaall -> AddEntry(eta2F,"#eta of third jet, era F","p");
    legetaall -> Draw();

    TCanvas* etacsvall = new TCanvas("etacsvall","etacsvall",1000,1000);
    gStyle->SetOptStat(0);
    etacsv0C->GetYaxis()->SetRangeUser(0,20000);
    etacsv0C->Draw(); etacsv0D->Draw("SAME"); etacsv0E->Draw("SAME"); etacsv0F->Draw("SAME");
    etacsv1C->Draw("SAME"); etacsv1D->Draw("SAME"); etacsv1E->Draw("SAME"); etacsv1F->Draw("SAME");
    etacsv2C->Draw("SAME"); etacsv2D->Draw("SAME"); etacsv2E->Draw("SAME"); etacsv2F->Draw("SAME");
    TLegend* legetacsvall = new TLegend(0.12,0.59,0.89,0.89);
    legetacsvall -> SetBorderSize(0);
    legetacsvall -> SetNColumns(3);
    legetacsvall -> AddEntry(etacsv0C,"#eta of first jet, era C, after cuts","p");
    legetacsvall -> AddEntry(etacsv1C,"#eta of second jet, era C, after cuts","p");
    legetacsvall -> AddEntry(etacsv2C,"#eta of third jet, era C, after cuts","p");
    legetacsvall -> AddEntry(etacsv0D,"#eta of first jet, era D, after cuts","p");
    legetacsvall -> AddEntry(etacsv1D,"#eta of second jet, era D, after cuts","p");
    legetacsvall -> AddEntry(etacsv2D,"#eta of third jet, era D, after cuts","p");
    legetacsvall -> AddEntry(etacsv0E,"#eta of first jet, era E, after cuts","p");
    legetacsvall -> AddEntry(etacsv1E,"#eta of second jet, era E, after cuts","p");
    legetacsvall -> AddEntry(etacsv2E,"#eta of third jet, era E, after cuts","p");
    legetacsvall -> AddEntry(etacsv0F,"#eta of first jet, era F, after cuts","p");
    legetacsvall -> AddEntry(etacsv1F,"#eta of second jet, era F, after cuts","p");
    legetacsvall -> AddEntry(etacsv2F,"#eta of third jet, era F, after cuts","p");
    legetacsvall -> Draw();

    if(plotetaall){
      TCanvas* etaC = new TCanvas("etaC","etaC",1000,1000);
      gStyle->SetOptStat(0);
      eta0C->GetYaxis()->SetRangeUser(0,60000);
      eta0C->Draw(); eta1C->Draw("SAME"); eta2C->Draw("SAME");
      TLegend* legetaC = new TLegend(0.32,0.82,0.9,0.9);
      legetaC -> SetNColumns(3);
      legetaC -> AddEntry(eta0C,"#eta of first jet, era C","p");
      legetaC -> AddEntry(eta1C,"#eta of second jet, era C","p");
      legetaC -> AddEntry(eta2C,"#eta of third jet, era C","p");
      legetaC -> Draw();

      TCanvas* etacsvC = new TCanvas("etacsvC","etacsvC",1000,1000);
      gStyle->SetOptStat(0);
      etacsv0C->GetYaxis()->SetRangeUser(0,60000);
      etacsv0C->Draw(); etacsv1C->Draw("SAME"); etacsv2C->Draw("SAME");
      TLegend* legetacsvC = new TLegend(0.32,0.82,0.9,0.9);
      legetacsvC -> SetNColumns(3);
      legetacsvC -> AddEntry(etacsv0C,"#eta of first jet, era C, after cuts","p");
      legetacsvC -> AddEntry(etacsv1C,"#eta of second jet, era C, after cuts","p");
      legetacsvC -> AddEntry(etacsv2C,"#eta of third jet, era C, after cuts","p");
      legetacsvC -> Draw();

      TCanvas* etaD = new TCanvas("etaD","etaD",1000,1000);
      gStyle->SetOptStat(0);
      eta0D->GetYaxis()->SetRangeUser(0,60000);
      eta0D->Draw(); eta1D->Draw("SAME"); eta2D->Draw("SAME");
      TLegend* legetaD = new TLegend(0.32,0.82,0.9,0.9);
      legetaD -> SetNColumns(3);
      legetaD -> AddEntry(eta0D,"#eta of first jet, era D","p");
      legetaD -> AddEntry(eta1D,"#eta of second jet, era D","p");
      legetaD -> AddEntry(eta2D,"#eta of third jet, era D","p");
      legetaD -> Draw();

      TCanvas* etacsvD = new TCanvas("etacsvD","etacsvD",1000,1000);
      gStyle->SetOptStat(0);
      etacsv0D->GetYaxis()->SetRangeUser(0,60000);
      etacsv0D->Draw(); etacsv1D->Draw("SAME"); etacsv2D->Draw("SAME");
      TLegend* legetacsvD = new TLegend(0.32,0.82,0.9,0.9);
      legetacsvD -> SetNColumns(3);
      legetacsvD -> AddEntry(etacsv0D,"#eta of first jet, era D, after cuts","p");
      legetacsvD -> AddEntry(etacsv1D,"#eta of second jet, era D, after cuts","p");
      legetacsvD -> AddEntry(etacsv2D,"#eta of third jet, era D, after cuts","p");
      legetacsvD -> Draw();

      TCanvas* etaE = new TCanvas("etaE","etaE",1000,1000);
      gStyle->SetOptStat(0);
      eta0E->GetYaxis()->SetRangeUser(0,60000);
      eta0E->Draw(); eta1E->Draw("SAME"); eta2E->Draw("SAME");
      TLegend* legetaE = new TLegend(0.32,0.82,0.9,0.9);
      legetaE -> SetNColumns(3);
      legetaE -> AddEntry(eta0E,"#eta of first jet, era E","p");
      legetaE -> AddEntry(eta1E,"#eta of second jet, era E","p");
      legetaE -> AddEntry(eta2E,"#eta of third jet, era E","p");
      legetaE -> Draw();

      TCanvas* etacsvE = new TCanvas("etacsvE","etacsvE",1000,1000);
      gStyle->SetOptStat(0);
      etacsv0E->GetYaxis()->SetRangeUser(0,60000);
      etacsv0E->Draw(); etacsv1E->Draw("SAME"); etacsv2E->Draw("SAME");
      TLegend* legetacsvE = new TLegend(0.32,0.82,0.9,0.9);
      legetacsvE -> SetNColumns(3);
      legetacsvE -> AddEntry(etacsv0E,"#eta of first jet, era E, after cuts","p");
      legetacsvE -> AddEntry(etacsv1E,"#eta of second jet, era E, after cuts","p");
      legetacsvE -> AddEntry(etacsv2E,"#eta of third jet, era E, after cuts","p");
      legetacsvE -> Draw();

      TCanvas* etaF = new TCanvas("etaF","etaF",1000,1000);
      gStyle->SetOptStat(0);
      eta0F->GetYaxis()->SetRangeUser(0,60000);
      eta0F->Draw(); eta1F->Draw("SAME"); eta2F->Draw("SAME");
      TLegend* legetaF = new TLegend(0.32,0.82,0.9,0.9);
      legetaF -> SetNColumns(3);
      legetaF -> AddEntry(eta0F,"#eta of first jet, era F","p");
      legetaF -> AddEntry(eta1F,"#eta of second jet, era F","p");
      legetaF -> AddEntry(eta2F,"#eta of third jet, era F","p");
      legetaF -> Draw();

      TCanvas* etacsvF = new TCanvas("etacsvF","etacsvF",1000,1000);
      gStyle->SetOptStat(0);
      etacsv0F->GetYaxis()->SetRangeUser(0,60000);
      etacsv0F->Draw(); etacsv1F->Draw("SAME"); etacsv2F->Draw("SAME");
      TLegend* legetacsvF = new TLegend(0.32,0.82,0.9,0.9);
      legetacsvF -> SetNColumns(3);
      legetacsvF -> AddEntry(etacsv0F,"#eta of first jet, era F, after cuts","p");
      legetacsvF -> AddEntry(etacsv1F,"#eta of second jet, era F, after cuts","p");
      legetacsvF -> AddEntry(etacsv2F,"#eta of third jet, era F, after cuts","p");
      legetacsvF -> Draw();
    }
  }

  ///
  //MASS//
  ///

  if(plotmass){
    TH1F* mj12C = (TH1F*)FileC->Get("m12"); mj12C->SetMarkerColor(2); mj12C->SetMarkerStyle(20);
    TH1F* mj12D = (TH1F*)FileD->Get("m12"); mj12D->SetMarkerColor(3); mj12D->SetMarkerStyle(20);
    TH1F* mj12E = (TH1F*)FileE->Get("m12"); mj12E->SetMarkerColor(4); mj12E->SetMarkerStyle(20);
    TH1F* mj12F = (TH1F*)FileF->Get("m12"); mj12F->SetMarkerColor(6); mj12F->SetMarkerStyle(20);  
  
    TH1F* mj12Ccsv = (TH1F*)FileC->Get("m12_csv"); mj12Ccsv->SetMarkerColor(2); mj12Ccsv->SetMarkerStyle(21);
    TH1F* mj12Dcsv = (TH1F*)FileD->Get("m12_csv"); mj12Dcsv->SetMarkerColor(3); mj12Dcsv->SetMarkerStyle(21);
    TH1F* mj12Ecsv = (TH1F*)FileE->Get("m12_csv"); mj12Ecsv->SetMarkerColor(4); mj12Ecsv->SetMarkerStyle(21);
    TH1F* mj12Fcsv = (TH1F*)FileF->Get("m12_csv"); mj12Fcsv->SetMarkerColor(6); mj12Fcsv->SetMarkerStyle(21);

    TCanvas* canmj12all = new TCanvas("mj12all","mj12all",1000,1000);
    gStyle->SetOptStat(0);
    mj12C->GetYaxis()->SetRangeUser(0,80000);
    mj12C->Draw(); mj12D->Draw("SAME"); mj12E->Draw("SAME"); mj12F->Draw("SAME");
    mj12Ccsv->Draw("SAME"); mj12Dcsv->Draw("SAME"); mj12Ecsv->Draw("SAME"); mj12Fcsv->Draw("SAME");
    TLegend* legmj12all = new TLegend(0.4,0.59,0.89,0.89);
    legmj12all -> SetBorderSize(0);
    legmj12all -> SetNColumns(2);
    legmj12all -> AddEntry(mj12C,"m of leading 2 jets before cuts, era C","p");
    legmj12all -> AddEntry(mj12Ccsv,"m of leading 2 jets after cuts, era C","p");
    legmj12all -> AddEntry(mj12D,"m of leading 2 jets before cuts, era D","p");
    legmj12all -> AddEntry(mj12Dcsv,"m of leading 2 jets after cuts, era D","p");
    legmj12all -> AddEntry(mj12E,"m of leading 2 jets before cuts, era E","p");
    legmj12all -> AddEntry(mj12Ecsv,"m of leading 2 jets after cuts, era E","p");
    legmj12all -> AddEntry(mj12F,"m of leading 2 jets before cuts, era F","p");
    legmj12all -> AddEntry(mj12Fcsv,"m of leading 2 jets after cuts, era F","p");
    legmj12all -> Draw();

    if(plotmassall){
      TCanvas* canmj12C = new TCanvas("mj12C","mj12C",1000,1000);
      gStyle->SetOptStat(0);
      mj12C->GetYaxis()->SetRangeUser(0.01,80000);
      mj12C->Draw(); mj12Ccsv->Draw("SAME");
      TLegend* legmj12C = new TLegend(0.32,0.82,0.9,0.9);
      legmj12C -> SetNColumns(2);
      legmj12C -> AddEntry(mj12C,"m of leading 2 jets before cuts, era C","p");
      legmj12C -> AddEntry(mj12Ccsv,"m of leading 2 jets after cuts, era C","p");
      legmj12C -> Draw();

      TCanvas* canmj12D = new TCanvas("mj12D","mj12D",1000,1000);
      gStyle->SetOptStat(0);
      mj12D->GetYaxis()->SetRangeUser(0.01,80000);
      mj12D->Draw(); mj12Dcsv->Draw("SAME");
      TLegend* legmj12D = new TLegend(0.32,0.82,0.9,0.9);
      legmj12D -> SetNColumns(2);
      legmj12D -> AddEntry(mj12D,"m of leading 2 jets before cuts, era D","p");
      legmj12D -> AddEntry(mj12Dcsv,"m of leading 2 jets after cuts, era D","p");
      legmj12D -> Draw();
  
      TCanvas* canmj12E = new TCanvas("mj12E","mj12E",1000,1000);
      gStyle->SetOptStat(0);
      mj12E->GetYaxis()->SetRangeUser(0.01,80000);
      mj12E->Draw(); mj12Ecsv->Draw("SAME");
      TLegend* legmj12E = new TLegend(0.32,0.82,0.9,0.9);
      legmj12E -> SetNColumns(2);
      legmj12E -> AddEntry(mj12E,"m of leading 2 jets before cuts, era E","p");
      legmj12E -> AddEntry(mj12Ecsv,"m of leading 2 jets after cuts, era E","p");
      legmj12E -> Draw();

      TCanvas* canmj12F = new TCanvas("mj12F","mj12F",1000,1000);
      gStyle->SetOptStat(0);
      mj12F->GetYaxis()->SetRangeUser(0.01,80000);
      mj12F->Draw(); mj12Fcsv->Draw("SAME");
      TLegend* legmj12F = new TLegend(0.32,0.82,0.9,0.9);
      legmj12F -> SetNColumns(2);
      legmj12F -> AddEntry(mj12F,"m of leading 2 jets before cuts, era F","p");
      legmj12F -> AddEntry(mj12Fcsv,"m of leading 2 jets after cuts, era F","p");
      legmj12F -> Draw();
    }
  }

  if(plotDRj12mu){//dr is only available after cuts (before it is not interesting)
    TH1F* DRj12muC = (TH1F*)FileC->Get("dR_muj"); DRj12muC->SetMarkerColor(2); DRj12muC->SetMarkerStyle(20);
    TH1F* DRj12muD = (TH1F*)FileD->Get("dR_muj"); DRj12muD->SetMarkerColor(3); DRj12muD->SetMarkerStyle(20);
    TH1F* DRj12muE = (TH1F*)FileE->Get("dR_muj"); DRj12muE->SetMarkerColor(4); DRj12muE->SetMarkerStyle(20);
    TH1F* DRj12muF = (TH1F*)FileF->Get("dR_muj"); DRj12muF->SetMarkerColor(6); DRj12muF->SetMarkerStyle(20);  

    TCanvas* canDRj12muall = new TCanvas("DRj12muall","DRj12muall",1000,1000);
    gStyle->SetOptStat(0);
    DRj12muC->GetYaxis()->SetRangeUser(0,10000);
    DRj12muC->Draw(); DRj12muD->Draw("SAME"); DRj12muE->Draw("SAME"); DRj12muF->Draw("SAME");
    TLegend* legDRj12muall = new TLegend(0.12,0.65,0.89,0.89);
    legDRj12muall -> SetBorderSize(0);
    legDRj12muall -> SetNColumns(2);
    legDRj12muall -> AddEntry(DRj12muC,"#Delta R of leading 2 jets and a #mu after cuts, era C","p");
    legDRj12muall -> AddEntry(DRj12muD,"#Delta R of leading 2 jets and a #mu after cuts, era D","p");
    legDRj12muall -> AddEntry(DRj12muE,"#Delta R of leading 2 jets and a #mu after cuts, era E","p");
    legDRj12muall -> AddEntry(DRj12muF,"#Delta R of leading 2 jets and a #mu after cuts, era F","p");
    legDRj12muall -> Draw();

    if(plotDRj12muall){
      TCanvas* canDRj12muC = new TCanvas("DRj12muC","DRj12muC",1000,1000);
      gStyle->SetOptStat(0);
      DRj12muC->GetYaxis()->SetRangeUser(0.01,80000);
      DRj12muC->Draw();
      TLegend* legDRj12muC = new TLegend(0.32,0.82,0.9,0.9);
      legDRj12muC -> SetNColumns(2);
      legDRj12muC -> AddEntry(DRj12muC,"#Delta R of leading 2 jets and a #mu before cuts, era C","p");
      legDRj12muC -> Draw();

      TCanvas* canDRj12muD = new TCanvas("DRj12muD","DRj12muD",1000,1000);
      gStyle->SetOptStat(0);
      DRj12muD->GetYaxis()->SetRangeUser(0.01,80000);
      DRj12muD->Draw();
      TLegend* legDRj12muD = new TLegend(0.32,0.82,0.9,0.9);
      legDRj12muD -> SetNColumns(2);
      legDRj12muD -> AddEntry(DRj12muD,"#Delta R of leading 2 jets and a #mu before cuts, era D","p");
      legDRj12muD -> Draw();
  
      TCanvas* canDRj12muE = new TCanvas("DRj12muE","DRj12muE",1000,1000);
      gStyle->SetOptStat(0);
      DRj12muE->GetYaxis()->SetRangeUser(0.01,80000);
      DRj12muE->Draw();
      TLegend* legDRj12muE = new TLegend(0.32,0.82,0.9,0.9);
      legDRj12muE -> SetNColumns(2);
      legDRj12muE -> AddEntry(DRj12muE,"#Delta R of leading 2 jets and a #mu before cuts, era E","p");
      legDRj12muE -> Draw();

      TCanvas* canDRj12muF = new TCanvas("DRj12muF","DRj12muF",1000,1000);
      gStyle->SetOptStat(0);
      DRj12muF->GetYaxis()->SetRangeUser(0.01,80000);
      DRj12muF->Draw();
      TLegend* legDRj12muF = new TLegend(0.32,0.82,0.9,0.9);
      legDRj12muF -> SetNColumns(2);
      legDRj12muF -> AddEntry(DRj12muF,"#Delta R of leading 2 jets and a #mu before cuts, era F","p");
      legDRj12muF -> Draw();
    }
  }
}
