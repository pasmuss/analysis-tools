#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>

#include "TLatex.h"
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

void DrawBiasPerFR(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  int pointsFR1 = 3;
  int pointsFR2 = 5;
  int pointsFR3 = 4;
  int pointsFR4 = 4;

  double biasFR1 = 30;
  double biasFR2 = 30;
  double biasFR3 = 10;
  double biasFR4 = 10;

  TCanvas* can_FR1 = style.MakeCanvas("can_FR1","",700,700);
  can_FR1 -> SetBottomMargin(0.12);
  can_FR1 -> SetLeftMargin(0.15);
  can_FR1 -> SetTopMargin(0.05);
  TLegend* leg_FR1_exterf = new TLegend(0.22,0.65,0.44,0.9);
  TLegend* leg_FR1_extlog = new TLegend(0.45,0.7,0.67,0.9);
  TLegend* leg_FR1_modlog = new TLegend(0.7,0.7,0.92,0.9);
  style.SetLegendStyle(leg_FR1_exterf);
  style.SetLegendStyle(leg_FR1_extlog);
  style.SetLegendStyle(leg_FR1_modlog);
  leg_FR1_exterf -> SetHeader("#it{Fit: ext. erf}");
  leg_FR1_extlog -> SetHeader("#it{Fit: ext. logistic}");
  leg_FR1_modlog -> SetHeader("#it{Fit: mod. logistic}");

  double massesFR1 [] = {300, 350, 400};
  
  double mu0exterfFR1[] = {-17, -24, 11};
  double mu1exterfFR1[] = {-18, -25, 12};
  double mu2exterfFR1[] = {-16, -25, 10};
  double mu3exterfFR1[] = {-17, -25, 12};
  TGraph* gr_mu0_exterf_FR1 = new TGraph(pointsFR1, massesFR1, mu0exterfFR1);
  TGraph* gr_mu1_exterf_FR1 = new TGraph(pointsFR1, massesFR1, mu1exterfFR1);
  TGraph* gr_mu2_exterf_FR1 = new TGraph(pointsFR1, massesFR1, mu2exterfFR1);
  TGraph* gr_mu3_exterf_FR1 = new TGraph(pointsFR1, massesFR1, mu3exterfFR1);
  gr_mu0_exterf_FR1 -> SetTitle("");
  gr_mu0_exterf_FR1 -> GetYaxis() -> SetRangeUser(-40,130);
  gr_mu0_exterf_FR1 -> GetYaxis() -> SetTitle("B [%]");
  gr_mu0_exterf_FR1 -> GetYaxis() -> SetTitleOffset(1.4);
  gr_mu0_exterf_FR1 -> GetXaxis() -> SetRangeUser(290,410);
  gr_mu0_exterf_FR1 -> GetXaxis() -> SetTitle("m_{A/H} [GeV]");
  gr_mu0_exterf_FR1 -> GetXaxis() -> SetTitleOffset(1.0);
  gr_mu0_exterf_FR1 -> SetLineColor(kRed);
  gr_mu1_exterf_FR1 -> SetLineColor(kBlue);
  gr_mu2_exterf_FR1 -> SetLineColor(kGreen);
  gr_mu3_exterf_FR1 -> SetLineColor(kBlack);
  gr_mu0_exterf_FR1 -> Draw("ALP");
  gr_mu1_exterf_FR1 -> Draw("LP");
  gr_mu2_exterf_FR1 -> Draw("LP");
  gr_mu3_exterf_FR1 -> Draw("LP");
  leg_FR1_exterf -> AddEntry(gr_mu0_exterf_FR1,"#mu=0","LP");
  leg_FR1_exterf -> AddEntry(gr_mu1_exterf_FR1,"#mu=1","LP");
  leg_FR1_exterf -> AddEntry(gr_mu2_exterf_FR1,"#mu=2","LP");
  leg_FR1_exterf -> AddEntry(gr_mu3_exterf_FR1,"#mu=3","LP");

  TLine* lineFR1pos = new TLine(290,biasFR1,410,biasFR1);
  TLine* lineFR1neg = new TLine(290,-biasFR1,410,-biasFR1);
  lineFR1pos -> SetLineColor(kRed);
  lineFR1neg -> SetLineColor(kRed);
  lineFR1pos -> SetLineStyle(3);
  lineFR1neg -> SetLineStyle(3);
  lineFR1pos -> Draw("SAME");
  lineFR1neg -> Draw("SAME");

  leg_FR1_exterf -> AddEntry(lineFR1pos,"Assigned B","L");
  leg_FR1_exterf -> Draw("SAME");
  
  double mu0extlogFR1[] = {15, -3, 2};
  double mu1extlogFR1[] = {15, -3, 3};  
  double mu2extlogFR1[] = {15, -3, 1};
  double mu3extlogFR1[] = {15, -4, 3};
  TGraph* gr_mu0_extlog_FR1 = new TGraph(pointsFR1, massesFR1, mu0extlogFR1);
  TGraph* gr_mu1_extlog_FR1 = new TGraph(pointsFR1, massesFR1, mu1extlogFR1);
  TGraph* gr_mu2_extlog_FR1 = new TGraph(pointsFR1, massesFR1, mu2extlogFR1);
  TGraph* gr_mu3_extlog_FR1 = new TGraph(pointsFR1, massesFR1, mu3extlogFR1);
  gr_mu0_extlog_FR1 -> SetLineColor(kMagenta);
  gr_mu1_extlog_FR1 -> SetLineColor(kCyan);
  gr_mu2_extlog_FR1 -> SetLineColor(kGreen+1);
  gr_mu3_extlog_FR1 -> SetLineColor(kGray);
  gr_mu0_extlog_FR1 -> SetMarkerStyle(21);
  gr_mu1_extlog_FR1 -> SetMarkerStyle(21);
  gr_mu2_extlog_FR1 -> SetMarkerStyle(21);
  gr_mu3_extlog_FR1 -> SetMarkerStyle(21);
  gr_mu0_extlog_FR1 -> Draw("LP");
  gr_mu1_extlog_FR1 -> Draw("LP");
  gr_mu2_extlog_FR1 -> Draw("LP");
  gr_mu3_extlog_FR1 -> Draw("LP");

  leg_FR1_extlog -> AddEntry(gr_mu0_extlog_FR1,"#mu=0","LP");
  leg_FR1_extlog -> AddEntry(gr_mu1_extlog_FR1,"#mu=1","LP");
  leg_FR1_extlog -> AddEntry(gr_mu2_extlog_FR1,"#mu=2","LP");
  leg_FR1_extlog -> AddEntry(gr_mu3_extlog_FR1,"#mu=3","LP");
  leg_FR1_extlog -> Draw("SAME");
  
  double mu0modlogFR1[] = {35, 28, -8};
  double mu1modlogFR1[] = {33, 27, -7};
  double mu2modlogFR1[] = {35, 28, -8};
  double mu3modlogFR1[] = {35, 26, -6};
  TGraph* gr_mu0_modlog_FR1 = new TGraph(pointsFR1, massesFR1, mu0modlogFR1);
  TGraph* gr_mu1_modlog_FR1 = new TGraph(pointsFR1, massesFR1, mu1modlogFR1);
  TGraph* gr_mu2_modlog_FR1 = new TGraph(pointsFR1, massesFR1, mu2modlogFR1);
  TGraph* gr_mu3_modlog_FR1 = new TGraph(pointsFR1, massesFR1, mu3modlogFR1);
  gr_mu0_modlog_FR1 -> SetLineColor(kViolet);
  gr_mu1_modlog_FR1 -> SetLineColor(kAzure-3);
  gr_mu2_modlog_FR1 -> SetLineColor(kGreen-7);
  gr_mu3_modlog_FR1 -> SetLineColor(kGray+2);
  gr_mu0_modlog_FR1 -> SetMarkerStyle(22);
  gr_mu1_modlog_FR1 -> SetMarkerStyle(22);
  gr_mu2_modlog_FR1 -> SetMarkerStyle(22);
  gr_mu3_modlog_FR1 -> SetMarkerStyle(22);
  gr_mu0_modlog_FR1 -> Draw("LP");
  gr_mu1_modlog_FR1 -> Draw("LP");
  gr_mu2_modlog_FR1 -> Draw("LP");
  gr_mu3_modlog_FR1 -> Draw("LP");

  leg_FR1_modlog -> AddEntry(gr_mu0_modlog_FR1,"#mu=0","LP");
  leg_FR1_modlog -> AddEntry(gr_mu1_modlog_FR1,"#mu=1","LP");
  leg_FR1_modlog -> AddEntry(gr_mu2_modlog_FR1,"#mu=2","LP");
  leg_FR1_modlog -> AddEntry(gr_mu3_modlog_FR1,"#mu=3","LP");
  leg_FR1_modlog -> Draw("SAME");

  float posXfr1 = can_FR1->GetLeftMargin() + 0.085;
  float posYfr1 = 1 - (can_FR1->GetTopMargin()) + 0.025;
  float canWfr1 = can_FR1->GetWw();

  TLatex* textfr1 = new TLatex();
  textfr1 -> SetNDC();
  textfr1 -> SetTextSize(0.045);
  textfr1 -> SetTextAlign(32);
  textfr1 -> SetTextFont(61);
  textfr1 -> DrawLatex(posXfr1,posYfr1,"CMS");

  UInt_t wfr1;
  UInt_t hfr1;
  textfr1 -> GetTextExtent(wfr1,hfr1,"CMS");
  textfr1 -> SetTextFont(51);
  textfr1 -> SetTextSize(0.04);
  textfr1 -> DrawLatex(posXfr1+(wfr1/canWfr1)*2,posYfr1," Simulation");

  UInt_t wfr1sim;
  UInt_t hfr1sim;
  textfr1 -> GetTextExtent(wfr1sim,hfr1sim,"CMS Simulation");
  textfr1 -> SetTextFont(41);
  textfr1 -> DrawLatex(posXfr1+(wfr1sim/canWfr1)*1.78,posYfr1,"Work in progress");

  TLatex* textfr1right = new TLatex();
  textfr1right -> SetNDC();
  textfr1right -> SetTextSize(0.03);
  textfr1right -> SetTextFont(41);
  textfr1right -> SetTextAlign(32);
  textfr1right -> DrawLatex(1-can_FR1->GetRightMargin(),posYfr1-0.005,"(13 TeV)");
  
  TCanvas* can_FR2 = style.MakeCanvas("can_FR2","",700,700);
  can_FR2 -> SetBottomMargin(0.12);
  can_FR2 -> SetLeftMargin(0.15);
  can_FR2 -> SetTopMargin(0.05);
  TLegend* leg_FR2_exterf = new TLegend(0.22,0.65,0.44,0.9);
  TLegend* leg_FR2_lin = new TLegend(0.45,0.7,0.67,0.9);
  style.SetLegendStyle(leg_FR2_exterf);
  style.SetLegendStyle(leg_FR2_lin);
  leg_FR2_exterf -> SetHeader("#it{Fit: ext. erf}");
  leg_FR2_lin -> SetHeader("#it{Fit: linear}");

  double massesFR2[] = {400, 450, 500, 600, 700};

  double mu0exterfFR2[] = {33, 8, 21, 30, 33};
  double mu1exterfFR2[] = {34, 8, 21, 29, 33};
  double mu2exterfFR2[] = {35, 8, 22, 29, 32};
  double mu3exterfFR2[] = {32, 7, 20, 30, 31};
  TGraph* gr_mu0_exterf_FR2 = new TGraph(pointsFR2, massesFR2, mu0exterfFR2);
  TGraph* gr_mu1_exterf_FR2 = new TGraph(pointsFR2, massesFR2, mu1exterfFR2);
  TGraph* gr_mu2_exterf_FR2 = new TGraph(pointsFR2, massesFR2, mu2exterfFR2);
  TGraph* gr_mu3_exterf_FR2 = new TGraph(pointsFR2, massesFR2, mu3exterfFR2);
  gr_mu0_exterf_FR2 -> SetTitle("");
  gr_mu0_exterf_FR2 -> GetYaxis() -> SetRangeUser(-40,130);
  gr_mu0_exterf_FR2 -> GetYaxis() -> SetTitle("B [%]");
  gr_mu0_exterf_FR2 -> GetYaxis() -> SetTitleOffset(1.4);
  gr_mu0_exterf_FR2 -> GetXaxis() -> SetRangeUser(390,710);
  gr_mu0_exterf_FR2 -> GetXaxis() -> SetTitle("m_{A/H} [GeV]");
  gr_mu0_exterf_FR2 -> GetXaxis() -> SetTitleOffset(1.0);
  gr_mu0_exterf_FR2 -> SetLineColor(kRed);
  gr_mu1_exterf_FR2 -> SetLineColor(kBlue);
  gr_mu2_exterf_FR2 -> SetLineColor(kGreen);
  gr_mu3_exterf_FR2 -> SetLineColor(kBlack);
  gr_mu0_exterf_FR2 -> Draw("ALP");
  gr_mu1_exterf_FR2 -> Draw("LP");
  gr_mu2_exterf_FR2 -> Draw("LP");
  gr_mu3_exterf_FR2 -> Draw("LP");
  leg_FR2_exterf -> AddEntry(gr_mu0_exterf_FR2,"#mu=0","LP");
  leg_FR2_exterf -> AddEntry(gr_mu1_exterf_FR2,"#mu=1","LP");
  leg_FR2_exterf -> AddEntry(gr_mu2_exterf_FR2,"#mu=2","LP");
  leg_FR2_exterf -> AddEntry(gr_mu3_exterf_FR2,"#mu=3","LP");

  TLine* lineFR2pos = new TLine(390,biasFR2,710,biasFR2);
  TLine* lineFR2neg = new TLine(390,-biasFR2,710,-biasFR2);
  lineFR2pos -> SetLineColor(kRed);
  lineFR2neg -> SetLineColor(kRed);
  lineFR2pos -> SetLineStyle(3);
  lineFR2neg -> SetLineStyle(3);
  lineFR2pos -> Draw("SAME");
  lineFR2neg -> Draw("SAME");

  leg_FR2_exterf -> AddEntry(lineFR2pos,"Assigned B","L");
  leg_FR2_exterf -> Draw("SAME");

  double mu0linFR2[] = {53, 16, 15, 8, 6};
  double mu1linFR2[] = {52, 16, 16, 8, 6};
  double mu2linFR2[] = {53, 15, 16, 7, 3};
  double mu3linFR2[] = {53, 17, 16, 7, 3};
  TGraph* gr_mu0_lin_FR2 = new TGraph(pointsFR2, massesFR2, mu0linFR2);
  TGraph* gr_mu1_lin_FR2 = new TGraph(pointsFR2, massesFR2, mu1linFR2);
  TGraph* gr_mu2_lin_FR2 = new TGraph(pointsFR2, massesFR2, mu2linFR2);
  TGraph* gr_mu3_lin_FR2 = new TGraph(pointsFR2, massesFR2, mu3linFR2);
  gr_mu0_lin_FR2 -> SetLineColor(kViolet);
  gr_mu1_lin_FR2 -> SetLineColor(kAzure-3);
  gr_mu2_lin_FR2 -> SetLineColor(kGreen-7);
  gr_mu3_lin_FR2 -> SetLineColor(kGray+2);
  gr_mu0_lin_FR2 -> SetMarkerStyle(22);
  gr_mu1_lin_FR2 -> SetMarkerStyle(22);
  gr_mu2_lin_FR2 -> SetMarkerStyle(22);
  gr_mu3_lin_FR2 -> SetMarkerStyle(22);
  gr_mu0_lin_FR2 -> Draw("LP");
  gr_mu1_lin_FR2 -> Draw("LP");
  gr_mu2_lin_FR2 -> Draw("LP");
  gr_mu3_lin_FR2 -> Draw("LP");

  leg_FR2_lin -> AddEntry(gr_mu0_lin_FR2,"#mu=0","LP");
  leg_FR2_lin -> AddEntry(gr_mu1_lin_FR2,"#mu=1","LP");
  leg_FR2_lin -> AddEntry(gr_mu2_lin_FR2,"#mu=2","LP");
  leg_FR2_lin -> AddEntry(gr_mu3_lin_FR2,"#mu=3","LP");
  leg_FR2_lin -> Draw("SAME");

  float posXfr2 = can_FR2->GetLeftMargin() + 0.085;
  float posYfr2 = 1 - (can_FR2->GetTopMargin()) + 0.025;
  float canWfr2 = can_FR2->GetWw();

  TLatex* textfr2 = new TLatex();
  textfr2 -> SetNDC();
  textfr2 -> SetTextSize(0.045);
  textfr2 -> SetTextAlign(32);
  textfr2 -> SetTextFont(61);
  textfr2 -> DrawLatex(posXfr2,posYfr2,"CMS");

  UInt_t wfr2;
  UInt_t hfr2;
  textfr2 -> GetTextExtent(wfr2,hfr2,"CMS");
  textfr2 -> SetTextFont(51);
  textfr2 -> SetTextSize(0.04);
  textfr2 -> DrawLatex(posXfr2+(wfr2/canWfr2)*2,posYfr2," Simulation");

  UInt_t wfr2sim;
  UInt_t hfr2sim;
  textfr2 -> GetTextExtent(wfr2sim,hfr2sim,"CMS Simulation");
  textfr2 -> SetTextFont(41);
  textfr2 -> DrawLatex(posXfr2+(wfr2sim/canWfr2)*1.78,posYfr2,"Work in progress");

  TLatex* textfr2right = new TLatex();
  textfr2right -> SetNDC();
  textfr2right -> SetTextSize(0.03);
  textfr2right -> SetTextFont(41);
  textfr2right -> SetTextAlign(32);
  textfr2right -> DrawLatex(1-can_FR2->GetRightMargin(),posYfr2-0.005,"(13 TeV)");

  TCanvas* can_FR3 = style.MakeCanvas("can_FR3","",700,700);
  can_FR3 -> SetBottomMargin(0.12);
  can_FR3 -> SetLeftMargin(0.15);
  can_FR3 -> SetTopMargin(0.05);
  TLegend* leg_FR3_exterf = new TLegend(0.22,0.65,0.44,0.9);
  style.SetLegendStyle(leg_FR3_exterf);
  leg_FR3_exterf -> SetHeader("#it{Fit: ext. erf}");

  double massesFR3[] = {700, 800, 900, 1000};

  double mu0exterfFR3[] = {10, 4, 3, -2};
  double mu1exterfFR3[] = {10, 6, 4, 0};
  double mu2exterfFR3[] = {8, 4, 4, -2};
  double mu3exterfFR3[] = {9, 5, 1, -4};
  TGraph* gr_mu0_exterf_FR3 = new TGraph(pointsFR3, massesFR3, mu0exterfFR3);
  TGraph* gr_mu1_exterf_FR3 = new TGraph(pointsFR3, massesFR3, mu1exterfFR3);
  TGraph* gr_mu2_exterf_FR3 = new TGraph(pointsFR3, massesFR3, mu2exterfFR3);
  TGraph* gr_mu3_exterf_FR3 = new TGraph(pointsFR3, massesFR3, mu3exterfFR3);

  gr_mu0_exterf_FR3 -> SetTitle("");
  gr_mu0_exterf_FR3 -> GetYaxis() -> SetRangeUser(-40,130);
  gr_mu0_exterf_FR3 -> GetYaxis() -> SetTitle("B [%]");
  gr_mu0_exterf_FR3 -> GetYaxis() -> SetTitleOffset(1.4);
  gr_mu0_exterf_FR3 -> GetXaxis() -> SetRangeUser(690,1010);
  gr_mu0_exterf_FR3 -> GetXaxis() -> SetTitle("m_{A/H} [GeV]");
  gr_mu0_exterf_FR3 -> GetXaxis() -> SetTitleOffset(1.0);
  gr_mu0_exterf_FR3 -> SetLineColor(kRed);
  gr_mu1_exterf_FR3 -> SetLineColor(kBlue);
  gr_mu2_exterf_FR3 -> SetLineColor(kGreen);
  gr_mu3_exterf_FR3 -> SetLineColor(kBlack);
  gr_mu0_exterf_FR3 -> Draw("ALP");
  gr_mu1_exterf_FR3 -> Draw("LP");
  gr_mu2_exterf_FR3 -> Draw("LP");
  gr_mu3_exterf_FR3 -> Draw("LP");
  leg_FR3_exterf -> AddEntry(gr_mu0_exterf_FR3,"#mu=0","LP");
  leg_FR3_exterf -> AddEntry(gr_mu1_exterf_FR3,"#mu=1","LP");
  leg_FR3_exterf -> AddEntry(gr_mu2_exterf_FR3,"#mu=2","LP");
  leg_FR3_exterf -> AddEntry(gr_mu3_exterf_FR3,"#mu=3","LP");

  TLine* lineFR3pos = new TLine(690,biasFR3,1010,biasFR3);
  TLine* lineFR3neg = new TLine(690,-biasFR3,1010,-biasFR3);
  lineFR3pos -> SetLineColor(kRed);
  lineFR3neg -> SetLineColor(kRed);
  lineFR3pos -> SetLineStyle(3);
  lineFR3neg -> SetLineStyle(3);
  lineFR3pos -> Draw("SAME");
  lineFR3neg -> Draw("SAME");

  leg_FR3_exterf -> AddEntry(lineFR3pos,"Assigned B","L");
  leg_FR3_exterf -> Draw("SAME");

  float posXfr3 = can_FR3->GetLeftMargin() + 0.085;
  float posYfr3 = 1 - (can_FR3->GetTopMargin()) + 0.025;
  float canWfr3 = can_FR3->GetWw();

  TLatex* textfr3 = new TLatex();
  textfr3 -> SetNDC();
  textfr3 -> SetTextSize(0.045);
  textfr3 -> SetTextAlign(32);
  textfr3 -> SetTextFont(61);
  textfr3 -> DrawLatex(posXfr3,posYfr3,"CMS");

  UInt_t wfr3;
  UInt_t hfr3;
  textfr3 -> GetTextExtent(wfr3,hfr3,"CMS");
  textfr3 -> SetTextFont(51);
  textfr3 -> SetTextSize(0.04);
  textfr3 -> DrawLatex(posXfr3+(wfr3/canWfr3)*2,posYfr3," Simulation");

  UInt_t wfr3sim;
  UInt_t hfr3sim;
  textfr3 -> GetTextExtent(wfr3sim,hfr3sim,"CMS Simulation");
  textfr3 -> SetTextFont(41);
  textfr3 -> DrawLatex(posXfr3+(wfr3sim/canWfr3)*1.78,posYfr3,"Work in progress");

  TLatex* textfr3right = new TLatex();
  textfr3right -> SetNDC();
  textfr3right -> SetTextSize(0.03);
  textfr3right -> SetTextFont(41);
  textfr3right -> SetTextAlign(32);
  textfr3right -> DrawLatex(1-can_FR3->GetRightMargin(),posYfr3-0.005,"(13 TeV)");

  TCanvas* can_FR4 = style.MakeCanvas("can_FR4","",700,700);
  can_FR4 -> SetBottomMargin(0.12);
  can_FR4 -> SetLeftMargin(0.15);
  can_FR4 -> SetTopMargin(0.05);
  TLegend* leg_FR4_exterf = new TLegend(0.22,0.65,0.44,0.9);
  style.SetLegendStyle(leg_FR4_exterf);
  leg_FR4_exterf -> SetHeader("#it{Fit: ext. erf}");

  double massesFR4[] = {1000, 1200, 1400, 1600};

  double mu0exterfFR4[] = {0, 5, 9, 7};
  double mu1exterfFR4[] = {1, 6, 8, 6};
  double mu2exterfFR4[] = {2, 7, 8, 6};
  double mu3exterfFR4[] = {2, 3, 2, 8};
  TGraph* gr_mu0_exterf_FR4 = new TGraph(pointsFR4, massesFR4, mu0exterfFR4);
  TGraph* gr_mu1_exterf_FR4 = new TGraph(pointsFR4, massesFR4, mu1exterfFR4);
  TGraph* gr_mu2_exterf_FR4 = new TGraph(pointsFR4, massesFR4, mu2exterfFR4);
  TGraph* gr_mu3_exterf_FR4 = new TGraph(pointsFR4, massesFR4, mu3exterfFR4);

  gr_mu0_exterf_FR4 -> SetTitle("");
  gr_mu0_exterf_FR4 -> GetYaxis() -> SetRangeUser(-40,130);
  gr_mu0_exterf_FR4 -> GetYaxis() -> SetTitle("B [%]");
  gr_mu0_exterf_FR4 -> GetYaxis() -> SetTitleOffset(1.4);
  gr_mu0_exterf_FR4 -> GetXaxis() -> SetRangeUser(990,1610);
  gr_mu0_exterf_FR4 -> GetXaxis() -> SetTitle("m_{A/H} [GeV]");
  gr_mu0_exterf_FR4 -> GetXaxis() -> SetTitleOffset(1.0);
  gr_mu0_exterf_FR4 -> SetLineColor(kRed);
  gr_mu1_exterf_FR4 -> SetLineColor(kBlue);
  gr_mu2_exterf_FR4 -> SetLineColor(kGreen);
  gr_mu3_exterf_FR4 -> SetLineColor(kBlack);
  gr_mu0_exterf_FR4 -> Draw("ALP");
  gr_mu1_exterf_FR4 -> Draw("LP");
  gr_mu2_exterf_FR4 -> Draw("LP");
  gr_mu3_exterf_FR4 -> Draw("LP");
  leg_FR4_exterf -> AddEntry(gr_mu0_exterf_FR4,"#mu=0","LP");
  leg_FR4_exterf -> AddEntry(gr_mu1_exterf_FR4,"#mu=1","LP");
  leg_FR4_exterf -> AddEntry(gr_mu2_exterf_FR4,"#mu=2","LP");
  leg_FR4_exterf -> AddEntry(gr_mu3_exterf_FR4,"#mu=3","LP");

  TLine* lineFR4pos = new TLine(990,biasFR4,1610,biasFR4);
  TLine* lineFR4neg = new TLine(990,-biasFR4,1610,-biasFR4);
  lineFR4pos -> SetLineColor(kRed);
  lineFR4neg -> SetLineColor(kRed);
  lineFR4pos -> SetLineStyle(3);
  lineFR4neg -> SetLineStyle(3);
  lineFR4pos -> Draw("SAME");
  lineFR4neg -> Draw("SAME");

  leg_FR4_exterf -> AddEntry(lineFR4pos,"Assigned B","L");
  leg_FR4_exterf -> Draw("SAME");

  float posXfr4 = can_FR4->GetLeftMargin() + 0.085;
  float posYfr4 = 1 - (can_FR4->GetTopMargin()) + 0.025;
  float canWfr4 = can_FR4->GetWw();

  TLatex* textfr4 = new TLatex();
  textfr4 -> SetNDC();
  textfr4 -> SetTextSize(0.045);
  textfr4 -> SetTextAlign(32);
  textfr4 -> SetTextFont(61);
  textfr4 -> DrawLatex(posXfr4,posYfr4,"CMS");

  UInt_t wfr4;
  UInt_t hfr4;
  textfr4 -> GetTextExtent(wfr4,hfr4,"CMS");
  textfr4 -> SetTextFont(51);
  textfr4 -> SetTextSize(0.04);
  textfr4 -> DrawLatex(posXfr4+(wfr4/canWfr4)*2,posYfr4," Simulation");

  UInt_t wfr4sim;
  UInt_t hfr4sim;
  textfr4 -> GetTextExtent(wfr4sim,hfr4sim,"CMS Simulation");
  textfr4 -> SetTextFont(41);
  textfr4 -> DrawLatex(posXfr4+(wfr4sim/canWfr4)*1.78,posYfr4,"Work in progress");

  TLatex* textfr4right = new TLatex();
  textfr4right -> SetNDC();
  textfr4right -> SetTextSize(0.03);
  textfr4right -> SetTextFont(41);
  textfr4right -> SetTextAlign(32);
  textfr4right -> DrawLatex(1-can_FR4->GetRightMargin(),posYfr4-0.005,"(13 TeV)");

  can_FR1 -> SaveAs("Outputdata/Bias_results_FR1_Feb08-21.pdf");
  can_FR1 -> SaveAs("Outputdata/Bias_results_FR1_Feb08-21.root");
  can_FR2 -> SaveAs("Outputdata/Bias_results_FR2_Feb08-21.pdf");
  can_FR2 -> SaveAs("Outputdata/Bias_results_FR2_Feb08-21.root");
  can_FR3 -> SaveAs("Outputdata/Bias_results_FR3_Feb08-21.pdf");
  can_FR3 -> SaveAs("Outputdata/Bias_results_FR3_Feb08-21.root");
  can_FR4 -> SaveAs("Outputdata/Bias_results_FR4_Feb08-21.pdf");
  can_FR4 -> SaveAs("Outputdata/Bias_results_FR4_Feb08-21.root");

}
