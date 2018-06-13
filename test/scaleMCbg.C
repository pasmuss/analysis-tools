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

void scaleMCbg(string var_, string region_, string xtitle_, double xlow_, double xhigh_, string ytitle_, double ylow_, double yhigh_, bool logy_) {

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  string varname;
  if ( var_ == "pt_0" || var_ == "pt_0_csv") varname = "p_{T}, 1^{st} jet";
  else if ( var_ == "pt_1" || var_ == "pt_1_csv") varname = "p_{T}, 2^{nd} jet";
  else if ( var_ == "pt_2" || var_ == "pt_2_csv") varname = "p_{T}, 3^{rd} jet";
  else if ( var_ == "eta_0" || var_ == "eta_0_csv") varname = "#eta, 1^{st} jet";
  else if ( var_ == "eta_1" || var_ == "eta_1_csv") varname = "#eta, 2^{nd} jet";
  else if ( var_ == "eta_2" || var_ == "eta_2_csv") varname = "#eta, 3^{rd} jet";
  else if ( var_ == "phi_0" || var_ == "phi_0_csv") varname = "#phi, 1^{st} jet";
  else if ( var_ == "phi_1" || var_ == "phi_1_csv") varname = "#phi, 2^{nd} jet";
  else if ( var_ == "phi_2" || var_ == "phi_2_csv") varname = "#phi, 3^{rd} jet";
  else if ( var_ == "m12" || var_ == "m12_csv") varname = "m_{12}";
  else varname = var_;

  vector<string> pthatbins = {"30-50","50-80","80-120","120-170","170-300", "300-470", "470-600", "600-800", "800-1000", "1000-1400", "1400-1800", "1800-2400", "2400-3200"};
  vector<double> sfvalues = {257272, 35990.2, 3454.43, 631.133, 143.022, 5.26458, 0.88170, 0.10142, 0.03117, 0.01733, 0.00535, 0.00142, 0.00013};

  map<string, double> scalefactors;
  map<string, TFile*> files;
  map<string, TH1F*> histograms;

  for (unsigned int i = 0; i < pthatbins.size(); i++){
    scalefactors[pthatbins[i]] = sfvalues[i];
    files[pthatbins[i]] = new TFile( ("rootfiles/mcbg/mc-bg-" + pthatbins[i] + "-deep-" + region_ + ".root").c_str(),"READ");
    histograms[pthatbins[i]] = (TH1F*)files[pthatbins[i]] -> Get(var_.c_str());
  }

  double nbinsx = histograms[pthatbins[0]] -> GetNbinsX();
  double xreflow = histograms[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( 1 );
  double xrefhigh = histograms[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( histograms[pthatbins[0]] -> GetNbinsX()+1 );

  TCanvas* c1 = style.MakeCanvas("c1", "", 700,700);
  if (logy_) c1 -> SetLogy();
  TH1F* hist_output = new TH1F("hist_output", "", nbinsx, xreflow, xrefhigh);
  style.InitHist(hist_output,xtitle_.c_str(),ytitle_.c_str(),kBlue,0);
  hist_output -> SetMarkerSize(1);

  for (auto const &hist : histograms){
    hist_output -> Add(histograms[hist.first] , scalefactors[hist.first]);
  }

  if ( var_ == "pt_0" || var_ == "pt_0_csv" || var_ == "pt_1" || var_ == "pt_1_csv" || var_ == "pt_2" || var_ == "pt_2_csv" ) hist_output -> Rebin(5);
  if ( var_ == "m12" || var_ == "m12_csv" ) hist_output -> Rebin(3);

  hist_output -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output -> GetXaxis() -> SetTitle(xtitle_.c_str());
  hist_output -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output -> GetYaxis() -> SetTitle(ytitle_.c_str());
  hist_output -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output -> GetYaxis() -> SetNdivisions(505);
  TGaxis::SetMaxDigits(3);

  hist_output -> Draw();//perhaps also create histograms for each single bin to check performance of adding

  TLegend* leg = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(leg);
  leg -> AddEntry(hist_output,varname.c_str(),"LP");
  leg -> Draw("SAME");

  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.17, 0.76);

  c1 -> Update();
  c1 -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + ".pdf").c_str() );

}
