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

int EraDiffRatio( string era1_, string era2_, string reco_, string var_, string region_ , string xtitle_, float xlow_ ,float xhigh_ , float ylow_ ,float yhigh_ , float yRlow_ ,float yRhigh_  )
{

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  //setTDRStyle();

  std::string reco = reco_;
  std::string var = var_;
  std::string region = region_;
  std::string xtitle = xtitle_;
  
  const float xlow  = xlow_;
  const float xhigh = xhigh_;
  const float ylow  = ylow_;
  const float yhigh = yhigh_;
  const float yRlow  = yRlow_;
  const float yRhigh = yRhigh_;

  float lumi = 36.0; // all 2017 C to F

  if ( (era1_ == "C" && era2_ == "D") || (era1_ == "D" && era2_ == "C") ) lumi = 13.8;
  if ( (era1_ == "C" && era2_ == "E") || (era1_ == "E" && era2_ == "C") ) lumi = 18.4;
  if ( (era1_ == "C" && era2_ == "F") || (era1_ == "F" && era2_ == "C") ) lumi = 23.1;
  if ( (era1_ == "D" && era2_ == "E") || (era1_ == "E" && era2_ == "D") ) lumi = 13.1;
  if ( (era1_ == "D" && era2_ == "F") || (era1_ == "F" && era2_ == "D") ) lumi = 17.7;
  if ( (era1_ == "E" && era2_ == "F") || (era1_ == "F" && era2_ == "E") ) lumi = 22.4;
 

  TFile * f1 = new TFile( ("rootfiles/"+reco+"/"+reco+"-"+era1_+"-deep-"+region+".root").c_str(),"READ");//era 1
  TFile * f2 = new TFile( ("rootfiles/"+reco+"/"+reco+"-"+era2_+"-deep-"+region+".root").c_str(),"READ");//era 2

  TH1F * hist_era1 = (TH1F*)f1->Get(var.c_str());
  TH1F * hist_era2 = (TH1F*)f2->Get(var.c_str());

  std::vector<double> lines1 = {0.5, 1.0, 1.5, 2.0};
  std::vector<double> linespt = {0.5, 1.0, 1.5, 2.0, 2.5};
  //std::vector<double> linesF = {1.0, 2.0, 3.0, 4.0};

  TCanvas* c1 = style.MakeCanvas("c1","",700,700);

  if ( (var_ == "m12_csv") || (var_ == "m12") )
    {
      c1 -> SetLogy();
      style.InitHist(hist_era1, xtitle.c_str(),"Entries / 60 GeV ",kBlue,0);
      hist_era1 -> Rebin(3);
      style.InitHist(hist_era2, xtitle.c_str(),"Entries / 60 GeV ",kRed,0);
      hist_era2 -> Rebin(3);
    }
  else if ( (var_ == "pt_0_csv") || (var_ == "pt_0") || (var_ == "pt_1_csv") || (var_ == "pt_1") )
    {
      c1 -> SetLogy();
      style.InitHist(hist_era1, xtitle.c_str(),"Entries / 50 GeV ",kBlue,0);
      hist_era1 -> Rebin(5);
      style.InitHist(hist_era2, xtitle.c_str(),"Entries / 50 GeV ",kRed,0);
      hist_era2 -> Rebin(5);
    }
  else
    {
      style.InitHist(hist_era1, xtitle.c_str(),"Entries / 10 GeV ",kBlue,0);
      style.InitHist(hist_era2, xtitle.c_str(),"Entries / 10 GeV ",kRed,0);
    }

  //Ratio plot
  auto rp = new TRatioPlot(hist_era2,hist_era1);
  rp -> SetH1DrawOpt("E");
  rp -> SetH2DrawOpt("E");
  if ( (var_ == "pt_0_csv") || (var_ == "pt_0") || (var_ == "pt_1_csv") || (var_ == "pt_1") )
    rp -> SetGridlines(linespt);
  else rp -> SetGridlines(lines1);
  rp -> Draw();
  
  rp -> GetLowerRefGraph() -> SetLineWidth(2);
  rp -> GetLowerRefGraph() -> SetMarkerSize(1);
  
  rp -> SetRightMargin(0.05);
  rp -> SetUpTopMargin(0.08); // 0.03
  rp -> SetLeftMargin(0.13);
  rp -> SetSeparationMargin(0.07);
  rp -> SetLowBottomMargin(0.4); 
  rp -> SetLowTopMargin(0.0);
  
  rp -> GetLowerRefYaxis() -> SetTitle( (era2_+" / "+era1_).c_str() );
  rp -> GetLowerRefYaxis() -> SetRangeUser(yRlow,yRhigh);
  rp -> GetUpperRefYaxis() -> SetRangeUser(ylow,yhigh);
  rp -> GetUpperRefXaxis() -> SetRangeUser(xlow,xhigh);

  //TGaxis::SetMaxDigits(3);
    
  rp -> GetLowerRefYaxis() -> SetTitleSize(0.035);
  rp -> GetLowerRefYaxis() -> SetTitleOffset(1.7);
  rp -> GetUpperRefYaxis() -> SetTitleSize(0.035);
  rp -> GetUpperRefYaxis() -> SetTitleOffset(1.7);
  rp -> GetLowerRefXaxis() -> SetTitleSize(0.05);
  rp -> GetLowerRefXaxis() -> SetTitleOffset(1.15);
  rp -> GetLowerRefXaxis() -> SetLabelSize(0.035);
  rp -> GetLowerRefXaxis() -> SetLabelOffset(0.02);
  rp -> GetLowerRefYaxis() -> SetLabelSize(0.035);
  rp -> GetLowerRefYaxis() -> SetLabelOffset(0.02);
  rp -> GetUpperRefYaxis() -> SetLabelSize(0.035);
  rp -> GetUpperRefYaxis() -> SetLabelOffset(0.02);

  rp -> GetLowYaxis() -> SetNdivisions(505);
  rp -> GetUpperPad() -> cd();
  
  TLegend* leg = new TLegend(0.65,0.6,0.95,0.9);
  style.SetLegendStyle(leg);
  if ( (var_ == "pt_0_csv") || (var_ == "pt_0") ) {
    leg -> AddEntry(hist_era1,("p_{T}, 1^{st} jet, Era "+era1_).c_str(),"L");
    leg -> AddEntry(hist_era2,("p_{T}, 1^{st} jet, Era "+era2_).c_str(),"L");
  }
  else if ( (var_ == "pt_1_csv") || (var_ == "pt_1") ) {
    leg -> AddEntry(hist_era1,("p_{T}, 2^{nd} jet, Era "+era1_).c_str(),"L");
    leg -> AddEntry(hist_era2,("p_{T}, 2^{nd} jet, Era "+era2_).c_str(),"L");
  }
  else if ( (var_ == "m12_csv") || (var_ == "m12") ) {
    leg -> AddEntry(hist_era1,("m_{12}, Era "+era1_).c_str(),"L");
    leg -> AddEntry(hist_era2,("m_{12}, Era "+era2_).c_str(),"L");
  }
  else{
  leg -> AddEntry(hist_era1,(var_+", Era "+era1_).c_str(),"L");
  leg -> AddEntry(hist_era2,(var_+", Era "+era2_).c_str(),"L");
  }
  leg -> Draw("SAME");
  
  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , "Work in progress", 0.15, 0.75);

  c1 -> Update();
  c1 -> SaveAs(("Outputdata/Comp_"+ var_+ "-" + era1_ + "-vs-" + era2_ + "-" + reco_ + "-" + region_ + ".pdf").c_str());

  //pad1 -> SetLogy();
  //c1 -> SaveAs(("PLOTS/CompReco"+ era_ + "Log.png").c_str());

  return 0;
}
