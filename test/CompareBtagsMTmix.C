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

int CompareBtagsMTmix( string var_, float xlow_, float xhigh_, float ylow_, float yhigh_, int rebinning_ )
{
  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  string vartitle = var_;
  if (var_ == "m12_csv" || var_ == "m12") vartitle = "m_{12} [GeV]";
  else if (var_ == "pt_0_csv" || var_ == "pt_0") vartitle = "p_{T}, 1^{st} jet [GeV]";
  else if (var_ == "pt_1_csv" || var_ == "pt_1") vartitle = "p_{T}, 2^{nd} jet [GeV]";
  else if (var_ == "pt_2_csv" || var_ == "pt_2") vartitle = "p_{T}, 3^{rd} jet [GeV]";
  else if (var_ == "pt_3_csv" || var_ == "pt_3") vartitle = "p_{T}, 4^{th} jet [GeV]";
  else if (var_ == "btag_0_csv" || var_ == "btag_0") vartitle = "CSV b tag, 1^{st} jet";
  else if (var_ == "btag_1_csv" || var_ == "btag_1") vartitle = "CSV b tag, 2^{nd} jet";
  else if (var_ == "btag_2_csv" || var_ == "btag_2") vartitle = "CSV b tag, 3^{rd} jet";
  else if (var_ == "btag_3_csv" || var_ == "btag_3") vartitle = "CSV b tag, 4^{th} jet";
  else if (var_ == "deepcsvbtag_0_csv" || var_ == "deepcsvbtag_0") vartitle = "CSV b tag, 1^{st} jet";
  else if (var_ == "deepcsvbtag_1_csv" || var_ == "deepcsvbtag_1") vartitle = "CSV b tag, 2^{nd} jet";
  else if (var_ == "deepcsvbtag_2_csv" || var_ == "deepcsvbtag_2") vartitle = "CSV b tag, 3^{rd} jet";
  else if (var_ == "deepcsvbtag_3_csv" || var_ == "deepcsvbtag_3") vartitle = "CSV b tag, 4^{th} jet";
  else if (var_ == "eta_0_csv" || var_ == "eta_0") vartitle = "#eta, 1^{st} jet";
  else if (var_ == "eta_1_csv" || var_ == "eta_1") vartitle = "#eta, 2^{nd} jet";
  else if (var_ == "eta_2_csv" || var_ == "eta_2") vartitle = "#eta, 3^{rd} jet";
  else if (var_ == "eta_3_csv" || var_ == "eta_3") vartitle = "#eta, 4^{th} jet";
  string var = var_;

  TFile* file4m3j = new TFile("Configs_diffBTags_allmedium/rootfiles_4med_WithMuVeto/rereco/rereco-CDEF-deep-CR-3j.root","READ");
  TFile* file4t3j = new TFile("Configs_diffBTags_alltight/rootfiles_4tig_WithMuVeto/rereco/rereco-CDEF-deep-CR-3j.root","READ");
  TFile* file2t2m3j = new TFile("Configs_diffBTags/rootfiles_2tig2med_WithMuVeto/rereco/rereco-CDEF-deep-CR-3j.root","READ");

  TFile* file4m = new TFile("Configs_diffBTags_allmedium/rootfiles_4med_WithMuVeto/rereco/rereco-CDEF-deep-CR.root","READ");
  TFile* file4t = new TFile("Configs_diffBTags_alltight/rootfiles_4tig_WithMuVeto/rereco/rereco-CDEF-deep-CR.root","READ");
  TFile* file2t2m = new TFile("Configs_diffBTags/rootfiles_2tig2med_WithMuVeto/rereco/rereco-CDEF-deep-CR.root","READ");

  TH1F* hist_4m3j = (TH1F*)file4m3j->Get(var.c_str());
  TH1F* hist_4t3j = (TH1F*)file4t3j->Get(var.c_str());
  TH1F* hist_2t2m3j = (TH1F*)file2t2m3j->Get(var.c_str());

  TH1F* hist_4m = (TH1F*)file4m->Get(var.c_str());
  TH1F* hist_4t = (TH1F*)file4t->Get(var.c_str());
  TH1F* hist_2t2m = (TH1F*)file2t2m->Get(var.c_str());

  style.InitHist(hist_4m3j, vartitle.c_str(), "Entries / 0.04",kGreen,0);
  hist_4m3j -> Rebin(rebinning_);
  style.InitHist(hist_4t3j, vartitle.c_str(), "Entries / 0.04",kBlue,0);
  hist_4t3j -> Rebin(rebinning_);
  style.InitHist(hist_2t2m3j, vartitle.c_str(), "Entries / 0.04",kRed,0);
  hist_2t2m3j -> Rebin(rebinning_);

  style.InitHist(hist_4m, vartitle.c_str(), "Entries / 0.04",kGreen,0);
  hist_4m -> Rebin(rebinning_);
  style.InitHist(hist_4t, vartitle.c_str(), "Entries / 0.04",kBlue,0);
  hist_4t -> Rebin(rebinning_);
  style.InitHist(hist_2t2m, vartitle.c_str(), "Entries / 0.04",kRed,0);
  hist_2t2m -> Rebin(rebinning_);

  TCanvas* can3j = style.MakeCanvas("can3j","3j",700,700);
  can3j -> cd();
  can3j -> SetLogy();
  hist_4m3j -> GetXaxis() -> SetRangeUser(xlow_,xhigh_);
  hist_4m3j -> GetYaxis() -> SetRangeUser(ylow_,yhigh_);
  hist_4m3j -> Draw();
  hist_4t3j -> Draw("SAME");
  hist_2t2m3j -> Draw("SAME");

  TLegend* leg3j = new TLegend(0.36,0.70,0.66,0.87);
  style.SetLegendStyle(leg3j);
  leg3j -> AddEntry(hist_4m3j,"3 medium b tags","L");
  leg3j -> AddEntry(hist_4t3j,"3 tight b tags","L");
  leg3j -> AddEntry(hist_2t2m3j,"2 tight b tags, 1 medium","L");
  leg3j -> SetTextSize(0.05);
  leg3j -> Draw("SAME");

  can3j -> Update();
  can3j -> SaveAs(("Outputdata_LO_NLO/Comp_" + var + "_btagCombinations_CR_data_3j.pdf").c_str());

  TCanvas* can4j = style.MakeCanvas("can4j","4j",700,700);
  can4j -> cd();
  can4j -> SetLogy();
  hist_4m -> Draw();
  hist_4m -> GetXaxis() -> SetRangeUser(xlow_,xhigh_);
  hist_4m -> GetYaxis() -> SetRangeUser(ylow_,yhigh_);
  hist_4t -> Draw("SAME");
  hist_2t2m -> Draw("SAME");

  TLegend* leg4j = new TLegend(0.36,0.70,0.66,0.87);
  style.SetLegendStyle(leg4j);
  leg4j -> AddEntry(hist_4m,"4 medium b tags","L");
  leg4j -> AddEntry(hist_4t,"4 tight b tags","L");
  leg4j -> AddEntry(hist_2t2m,"2 tight b tags, 2 medium","L");
  leg4j -> SetTextSize(0.05);
  leg4j -> Draw("SAME");

  can4j -> Update();
  can4j -> SaveAs(("Outputdata_LO_NLO/Comp_" + var + "_btagCombinations_CR_data_4j.pdf").c_str());
  
  return 0;
}
