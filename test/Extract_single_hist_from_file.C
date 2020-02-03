#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TAttAxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"
#include "tdrstyle.C"

using namespace std;

void Extract_single_hist_from_file(string var_, int rebin_, bool logy_, string xtitle_, string ytitle_, string legentry_, double xlow_, double xhigh_, double ylow_, double yhigh_){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);
  
  TFile* file_1 = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rereco/rereco-CDEF-deep-CR-3j.root","READ");//MC
  
  TH1F* hist_1 = (TH1F*)file_1 -> Get(var_.c_str());

  hist_1 -> Rebin(rebin_);

  TCanvas* can = style.MakeCanvas("can","",700,700);
  if(logy_) can -> SetLogy();
  style.InitHist(hist_1,xtitle_.c_str(),ytitle_.c_str(),kBlue,0);

  hist_1 -> Draw("E");

  hist_1 -> SetMarkerSize(1);

  hist_1 -> GetXaxis() -> SetNdivisions(505);
  hist_1 -> GetYaxis() -> SetTitleOffset(1.2);
  hist_1 -> GetXaxis() -> SetTitleOffset(1.0);
  hist_1 -> GetYaxis() -> SetRangeUser(ylow_,yhigh_);
  hist_1 -> GetXaxis() -> SetRangeUser(xlow_,xhigh_);

  TLegend* leg = new TLegend(0.44,0.72,0.84,0.91);
  style.SetLegendStyle(leg);
  leg -> AddEntry(hist_1,legentry_.c_str(),"L");
  leg -> SetTextSize(0.04);
  leg -> Draw();

  can -> Update();
  can -> SaveAs(("Outputdata/hist-" + var_ + "-2020_01_30_1415.pdf").c_str());
}
