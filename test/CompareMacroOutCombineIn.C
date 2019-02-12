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

void CompareMacroOutCombineIn(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TFile* sigout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_allcorrections_nentries_v2/mcsig/mc-sig-350-NLO-deep-SR-3j.root","READ");
  TFile* sigin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_8_1_0/AnalysisWorkflow/inputfiles/350_4M_allcor-3j.root","READ");
  TFile* bgout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_allcorrections_nentries_v2/rereco/rereco-CDEF-deep-CR-3j.root","READ");

  TH1F* sigmacro = (TH1F*)sigout->Get("m12_csv");
  style.InitHist(sigmacro,"Mass [GeV]","Entries",kBlue,0);
  sigmacro -> GetXaxis() -> SetRangeUser(0,1000);
  sigmacro -> GetXaxis() -> SetNdivisions(505);
  sigmacro -> GetYaxis() -> SetTitleOffset(1.3);
  TH1F* sigtool  = (TH1F*)sigin->Get("bbH_Mbb");
  style.InitHist(sigtool,"Mass [GeV]","Entries",kRed,0);
  TH1F* bgmacro = (TH1F*)bgout->Get("m12_csv");
  style.InitHist(bgmacro,"Mass [GeV]","Entries",kBlue,0);
  bgmacro -> SetMarkerStyle(25);
  bgmacro -> SetMarkerSize(1);
  bgmacro -> GetXaxis() -> SetRangeUser(0,1000);
  bgmacro -> GetXaxis() -> SetNdivisions(505);
  bgmacro -> GetYaxis() -> SetTitleOffset(1.3);
  TH1F* bgtool = (TH1F*)sigin->Get("data_obs");
  style.InitHist(bgtool,"Mass [GeV]","Entries",kRed,0);
  //bgtool -> SetMarkerStyle(26);

  TCanvas* compsig = style.MakeCanvas("compsig","",700,700);
  sigmacro->Draw();
  sigtool->Draw("SAME");

  TLegend* legsig = new TLegend(0.6,0.7,0.8,0.9);
  style.SetLegendStyle(legsig);
  legsig -> AddEntry(sigmacro,"Output of analysis","L");
  legsig -> AddEntry(sigtool,"Input to combine tool","L");
  legsig -> Draw();

  compsig -> Update();
  compsig -> SaveAs("Outputdata/comp_macro_out_combine_in_mc_sig-4medium_350GeV_NLO_3j.pdf");

  TCanvas* compbg = style.MakeCanvas("compbg","",700,700);
  bgmacro -> Draw();
  bgtool -> Draw("SAME");

  TLegend* legbg = new TLegend(0.6,0.7,0.8,0.9);
  style.SetLegendStyle(legbg);
  legbg -> AddEntry(bgmacro,"Output of analysis","L");
  legbg -> AddEntry(bgtool,"Input to combine tool","L");
  legbg -> Draw("SAME");
  
  compbg -> Update();
  compbg -> SaveAs("Outputdata/comp_macro_out_combine_in_bg-4medium_350GeV_NLO_3j.pdf");
}
