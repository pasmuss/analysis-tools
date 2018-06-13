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


void PlotMCsigKinematics_350_600_1200(){

  bool pt = false;
  bool eta = false;
  bool phi = true;

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);
  
  ///
  /// Files
  ///
  TFile* file_350 = new TFile("rootfiles/mcsig/mc-sig-350-deep-SR.root","READ");
  TFile* file_600 = new TFile("rootfiles/mcsig/mc-sig-600-deep-SR.root","READ");
  TFile* file_1200 = new TFile("rootfiles/mcsig/mc-sig-1200-deep-SR.root","READ");

  if (pt)
    {
      ///
      /// pT histograms
      ///
      TH1F* hist_pt1_350 = (TH1F*)file_350 -> Get("pt_0_csv");
      TH1F* hist_pt1_600 = (TH1F*)file_600 -> Get("pt_0_csv");
      TH1F* hist_pt1_1200 = (TH1F*)file_1200 -> Get("pt_0_csv");
      TH1F* hist_pt2_350 = (TH1F*)file_350 -> Get("pt_1_csv");
      TH1F* hist_pt2_600 = (TH1F*)file_600 -> Get("pt_1_csv");
      TH1F* hist_pt2_1200 = (TH1F*)file_1200 -> Get("pt_1_csv");
      TH1F* hist_pt3_350 = (TH1F*)file_350 -> Get("pt_2_csv");
      TH1F* hist_pt3_600 = (TH1F*)file_600 -> Get("pt_2_csv");
      TH1F* hist_pt3_1200 = (TH1F*)file_1200 -> Get("pt_2_csv");

      TCanvas* can_pt1 = style.MakeCanvas("can_pt1","signal pT, first jet, after cuts, SR",700,700);
      can_pt1 -> SetLeftMargin(0.17); 
      style.InitHist(hist_pt1_350,"p_{T}, 1^{st} jet [GeV]","Entries / 10 GeV",kBlue,0);
      hist_pt1_350 -> GetYaxis() -> SetRangeUser(0.1,3000);
      hist_pt1_350 -> GetXaxis() -> SetRangeUser(0,1000);
      hist_pt1_350 -> GetXaxis() -> SetNdivisions(505);
      hist_pt1_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_pt1_350 -> Draw();
      style.InitHist(hist_pt1_600,"p_{T}, 1^{st} jet [GeV]","Entries / 10 GeV",kGreen,0);
      hist_pt1_600 -> Draw("SAME");
      style.InitHist(hist_pt1_1200,"p_{T}, 1^{st} jet [GeV]","Entries / 10 GeV",kRed,0);
      hist_pt1_1200 -> Draw("SAME");
      TLegend* leg_pt1 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_pt1);
      leg_pt1 -> AddEntry(hist_pt1_350,"m_{A/H} = 350 GeV","L");
      leg_pt1 -> AddEntry(hist_pt1_600,"m_{A/H} = 600 GeV","L");
      leg_pt1 -> AddEntry(hist_pt1_1200,"m_{A/H} = 1200 GeV","L");
      leg_pt1 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_pt1 -> Update();
      can_pt1 -> SaveAs("Outputdata/MC-sig-sr-ac-pt1-350-600-1200.pdf");

      TCanvas* can_pt2 = style.MakeCanvas("can_pt2","signal pT, second jet, after cuts, SR",700,700);
      can_pt2 -> SetLeftMargin(0.17); 
      style.InitHist(hist_pt2_350,"p_{T}, 2^{nd} jet [GeV]","Entries / 10 GeV",kBlue,0);
      hist_pt2_350 -> GetYaxis() -> SetRangeUser(0.1,3000);
      hist_pt2_350 -> GetXaxis() -> SetRangeUser(0,1000);
      hist_pt2_350 -> GetXaxis() -> SetNdivisions(505);
      hist_pt2_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_pt2_350 -> Draw();
      style.InitHist(hist_pt2_600,"p_{T}, 2^{nd} jet [GeV]","Entries / 10 GeV",kGreen,0);
      hist_pt2_600 -> Draw("SAME");
      style.InitHist(hist_pt2_1200,"p_{T}, 2^{nd} jet [GeV]","Entries / 10 GeV",kRed,0);
      hist_pt2_1200 -> Draw("SAME");
      TLegend* leg_pt2 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_pt2);
      leg_pt2 -> AddEntry(hist_pt2_350,"m_{A/H} = 350 GeV","L");
      leg_pt2 -> AddEntry(hist_pt2_600,"m_{A/H} = 600 GeV","L");
      leg_pt2 -> AddEntry(hist_pt2_1200,"m_{A/H} = 1200 GeV","L");
      leg_pt2 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_pt2 -> Update();
      can_pt2 -> SaveAs("Outputdata/MC-sig-sr-ac-pt2-350-600-1200.pdf");

      TCanvas* can_pt3 = style.MakeCanvas("can_pt3","signal pT, third jet, after cuts, SR",700,700);
      can_pt3 -> SetLeftMargin(0.17); 
      style.InitHist(hist_pt3_350,"p_{T}, 3^{rd} jet [GeV]","Entries / 10 GeV",kBlue,0);
      hist_pt3_350 -> GetYaxis() -> SetRangeUser(0.1,3000);
      hist_pt3_350 -> GetXaxis() -> SetRangeUser(0,1000);
      hist_pt3_350 -> GetXaxis() -> SetNdivisions(505);
      hist_pt3_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_pt3_350 -> Draw();
      style.InitHist(hist_pt3_600,"p_{T}, 3^{rd} jet [GeV]","Entries / 10 GeV",kGreen,0);
      hist_pt3_600 -> Draw("SAME");
      style.InitHist(hist_pt3_1200,"p_{T}, 3^{rd} jet [GeV]","Entries / 10 GeV",kRed,0);
      hist_pt3_1200 -> Draw("SAME");
      TLegend* leg_pt3 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_pt3);
      leg_pt3 -> AddEntry(hist_pt3_350,"m_{A/H} = 350 GeV","L");
      leg_pt3 -> AddEntry(hist_pt3_600,"m_{A/H} = 600 GeV","L");
      leg_pt3 -> AddEntry(hist_pt3_1200,"m_{A/H} = 1200 GeV","L");
      leg_pt3 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_pt3 -> Update();
      can_pt3 -> SaveAs("Outputdata/MC-sig-sr-ac-pt3-350-600-1200.pdf");
    }

  ///
  /// eta histograms
  ///

  if (eta)
    {
      TH1F* hist_eta1_350 = (TH1F*)file_350 -> Get("eta_0_csv");
      TH1F* hist_eta1_600 = (TH1F*)file_600 -> Get("eta_0_csv");
      TH1F* hist_eta1_1200 = (TH1F*)file_1200 -> Get("eta_0_csv");
      TH1F* hist_eta2_350 = (TH1F*)file_350 -> Get("eta_1_csv");
      TH1F* hist_eta2_600 = (TH1F*)file_600 -> Get("eta_1_csv");
      TH1F* hist_eta2_1200 = (TH1F*)file_1200 -> Get("eta_1_csv");
      TH1F* hist_eta3_350 = (TH1F*)file_350 -> Get("eta_2_csv");
      TH1F* hist_eta3_600 = (TH1F*)file_600 -> Get("eta_2_csv");
      TH1F* hist_eta3_1200 = (TH1F*)file_1200 -> Get("eta_2_csv");

      TCanvas* can_eta1 = style.MakeCanvas("can_eta1","signal eta, first jet, after cuts, SR",700,700);
      can_eta1 -> SetLeftMargin(0.17); 
      style.InitHist(hist_eta1_350,"#eta, 1^{st} jet","Entries / 0.1",kBlue,0);
      hist_eta1_350 -> GetYaxis() -> SetRangeUser(0.1,1500);
      hist_eta1_350 -> GetXaxis() -> SetRangeUser(-2.5,2.5);
      hist_eta1_350 -> GetXaxis() -> SetNdivisions(505);
      hist_eta1_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_eta1_350 -> Draw();
      style.InitHist(hist_eta1_600,"#eta, 1^{st} jet","Entries / 0.1",kGreen,0);
      hist_eta1_600 -> Draw("SAME");
      style.InitHist(hist_eta1_1200,"#eta, 1^{st} jet","Entries / 0.1",kRed,0);
      hist_eta1_1200 -> Draw("SAME");
      TLegend* leg_eta1 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_eta1);
      leg_eta1 -> AddEntry(hist_eta1_350,"m_{A/H} = 350 GeV","L");
      leg_eta1 -> AddEntry(hist_eta1_600,"m_{A/H} = 600 GeV","L");
      leg_eta1 -> AddEntry(hist_eta1_1200,"m_{A/H} = 1200 GeV","L");
      leg_eta1 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_eta1 -> Update();
      can_eta1 -> SaveAs("Outputdata/MC-sig-sr-ac-eta1-350-600-1200.pdf");

      TCanvas* can_eta2 = style.MakeCanvas("can_eta2","signal eta, second jet, after cuts, SR",700,700);
      can_eta2 -> SetLeftMargin(0.17); 
      style.InitHist(hist_eta2_350,"#eta, 2^{nd} jet","Entries / 0.1",kBlue,0);
      hist_eta2_350 -> GetYaxis() -> SetRangeUser(0.1,1500);
      hist_eta2_350 -> GetXaxis() -> SetRangeUser(-2.5,2.5);
      hist_eta2_350 -> GetXaxis() -> SetNdivisions(505);
      hist_eta2_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_eta2_350 -> Draw();
      style.InitHist(hist_eta2_600,"#eta, 2^{nd} jet","Entries / 0.1",kGreen,0);
      hist_eta2_600 -> Draw("SAME");
      style.InitHist(hist_eta2_1200,"#eta, 2^{nd} jet","Entries / 0.1",kRed,0);
      hist_eta2_1200 -> Draw("SAME");
      TLegend* leg_eta2 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_eta2);
      leg_eta2 -> AddEntry(hist_eta2_350,"m_{A/H} = 350 GeV","L");
      leg_eta2 -> AddEntry(hist_eta2_600,"m_{A/H} = 600 GeV","L");
      leg_eta2 -> AddEntry(hist_eta2_1200,"m_{A/H} = 1200 GeV","L");
      leg_eta2 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_eta2 -> Update();
      can_eta2 -> SaveAs("Outputdata/MC-sig-sr-ac-eta2-350-600-1200.pdf");

      TCanvas* can_eta3 = style.MakeCanvas("can_eta3","signal eta, third jet, after cuts, SR",700,700);
      can_eta3 -> SetLeftMargin(0.17); 
      style.InitHist(hist_eta3_350,"#eta, 3^{rd} jet","Entries / 0.1",kBlue,0);
      hist_eta3_350 -> GetYaxis() -> SetRangeUser(0.1,1500);
      hist_eta3_350 -> GetXaxis() -> SetRangeUser(-2.5,2.5);
      hist_eta3_350 -> GetXaxis() -> SetNdivisions(505);
      hist_eta3_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_eta3_350 -> Draw();
      style.InitHist(hist_eta3_600,"#eta, 3^{rd} jet","Entries / 0.1",kGreen,0);
      hist_eta3_600 -> Draw("SAME");
      style.InitHist(hist_eta3_1200,"#eta, 3^{rd} jet","Entries / 0.1",kRed,0);
      hist_eta3_1200 -> Draw("SAME");
      TLegend* leg_eta3 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_eta3);
      leg_eta3 -> AddEntry(hist_eta3_350,"m_{A/H} = 350 GeV","L");
      leg_eta3 -> AddEntry(hist_eta3_600,"m_{A/H} = 600 GeV","L");
      leg_eta3 -> AddEntry(hist_eta3_1200,"m_{A/H} = 1200 GeV","L");
      leg_eta3 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_eta3 -> Update();
      can_eta3 -> SaveAs("Outputdata/MC-sig-sr-ac-eta3-350-600-1200.pdf");
    }

  ///
  /// phi histograms
  ///

  if (phi)
    {
      TH1F* hist_phi1_350 = (TH1F*)file_350 -> Get("phi_0_csv");
      TH1F* hist_phi1_600 = (TH1F*)file_600 -> Get("phi_0_csv");
      TH1F* hist_phi1_1200 = (TH1F*)file_1200 -> Get("phi_0_csv");
      TH1F* hist_phi2_350 = (TH1F*)file_350 -> Get("phi_1_csv");
      TH1F* hist_phi2_600 = (TH1F*)file_600 -> Get("phi_1_csv");
      TH1F* hist_phi2_1200 = (TH1F*)file_1200 -> Get("phi_1_csv");
      TH1F* hist_phi3_350 = (TH1F*)file_350 -> Get("phi_2_csv");
      TH1F* hist_phi3_600 = (TH1F*)file_600 -> Get("phi_2_csv");
      TH1F* hist_phi3_1200 = (TH1F*)file_1200 -> Get("phi_2_csv");

      TCanvas* can_phi1 = style.MakeCanvas("can_phi1","signal phi, first jet, after cuts, SR",700,700);
      can_phi1 -> SetLeftMargin(0.17); 
      style.InitHist(hist_phi1_350,"#phi, 1^{st} jet","Entries / 0.08",kBlue,0);
      hist_phi1_350 -> GetYaxis() -> SetRangeUser(0.1,500);
      hist_phi1_350 -> GetXaxis() -> SetRangeUser(-3.5,3.5);
      hist_phi1_350 -> GetXaxis() -> SetNdivisions(505);
      hist_phi1_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_phi1_350 -> Draw();
      style.InitHist(hist_phi1_600,"#phi, 1^{st} jet","Entries / 0.08",kGreen,0);
      hist_phi1_600 -> Draw("SAME");
      style.InitHist(hist_phi1_1200,"#phi, 1^{st} jet","Entries / 0.08",kRed,0);
      hist_phi1_1200 -> Draw("SAME");
      TLegend* leg_phi1 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_phi1);
      leg_phi1 -> AddEntry(hist_phi1_350,"m_{A/H} = 350 GeV","L");
      leg_phi1 -> AddEntry(hist_phi1_600,"m_{A/H} = 600 GeV","L");
      leg_phi1 -> AddEntry(hist_phi1_1200,"m_{A/H} = 1200 GeV","L");
      leg_phi1 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_phi1 -> Update();
      can_phi1 -> SaveAs("Outputdata/MC-sig-sr-ac-phi1-350-600-1200.pdf");

      TCanvas* can_phi2 = style.MakeCanvas("can_phi2","signal phi, second jet, after cuts, SR",700,700);
      can_phi2 -> SetLeftMargin(0.17); 
      style.InitHist(hist_phi2_350,"#phi, 2^{nd} jet","Entries / 0.08",kBlue,0);
      hist_phi2_350 -> GetYaxis() -> SetRangeUser(0.1,500);
      hist_phi2_350 -> GetXaxis() -> SetRangeUser(-3.5,3.5);
      hist_phi2_350 -> GetXaxis() -> SetNdivisions(505);
      hist_phi2_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_phi2_350 -> Draw();
      style.InitHist(hist_phi2_600,"#phi, 2^{nd} jet","Entries / 0.08",kGreen,0);
      hist_phi2_600 -> Draw("SAME");
      style.InitHist(hist_phi2_1200,"#phi, 2^{nd} jet","Entries / 0.08",kRed,0);
      hist_phi2_1200 -> Draw("SAME");
      TLegend* leg_phi2 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_phi2);
      leg_phi2 -> AddEntry(hist_phi2_350,"m_{A/H} = 350 GeV","L");
      leg_phi2 -> AddEntry(hist_phi2_600,"m_{A/H} = 600 GeV","L");
      leg_phi2 -> AddEntry(hist_phi2_1200,"m_{A/H} = 1200 GeV","L");
      leg_phi2 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_phi2 -> Update();
      can_phi2 -> SaveAs("Outputdata/MC-sig-sr-ac-phi2-350-600-1200.pdf");

      TCanvas* can_phi3 = style.MakeCanvas("can_phi3","signal phi, third jet, after cuts, SR",700,700);
      can_phi3 -> SetLeftMargin(0.17); 
      style.InitHist(hist_phi3_350,"#phi, 3^{rd} jet","Entries / 0.08",kBlue,0);
      hist_phi3_350 -> GetYaxis() -> SetRangeUser(0.1,500);
      hist_phi3_350 -> GetXaxis() -> SetRangeUser(-3.5,3.5);
      hist_phi3_350 -> GetXaxis() -> SetNdivisions(505);
      hist_phi3_350 -> GetYaxis() -> SetTitleOffset(1.5);
      hist_phi3_350 -> Draw();
      style.InitHist(hist_phi3_600,"#phi, 3^{rd} jet","Entries / 0.08",kGreen,0);
      hist_phi3_600 -> Draw("SAME");
      style.InitHist(hist_phi3_1200,"#phi, 3^{rd} jet","Entries / 0.08",kRed,0);
      hist_phi3_1200 -> Draw("SAME");
      TLegend* leg_phi3 = new TLegend(0.5,0.68,0.8,0.88);
      style.SetLegendStyle(leg_phi3);
      leg_phi3 -> AddEntry(hist_phi3_350,"m_{A/H} = 350 GeV","L");
      leg_phi3 -> AddEntry(hist_phi3_600,"m_{A/H} = 600 GeV","L");
      leg_phi3 -> AddEntry(hist_phi3_1200,"m_{A/H} = 1200 GeV","L");
      leg_phi3 -> Draw("SAME");
      CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.19, 0.76);
      can_phi3 -> Update();
      can_phi3 -> SaveAs("Outputdata/MC-sig-sr-ac-phi3-350-600-1200.pdf");
    }

}
