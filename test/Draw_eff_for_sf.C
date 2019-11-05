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

void Draw_eff_for_sf(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);
  
  TFile* inC = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/SecondAtt_OneJet_OnlineObjectsCut_Oct30-10/rootfiles/2017C_eff_for_sf.root","READ");

  TH1F* in0to1C = (TH1F*) inC -> Get("pt_0_PFJet100xOffl_eta0to1");
  TH1F* in1to14C = (TH1F*) inC -> Get("pt_0_PFJet100xOffl_eta1to1p4");
  TH1F* in14to22C = (TH1F*) inC -> Get("pt_0_PFJet100xOffl_eta1p4to2p2");

  TCanvas* canC = style.MakeCanvas("canC", "", 700, 700);
  style.InitHist(in0to1C,"p_{T} [GeV]", "Efficiency", kBlue, 0);
  style.InitHist(in1to14C,"p_{T} [GeV]", "Efficiency", kGreen, 0);
  style.InitHist(in14to22C,"p_{T} [GeV]", "Efficiency", kRed, 0);

  in0to1C -> GetXaxis() -> SetRangeUser(80,200);

  TLegend* legC = new TLegend(0.6,0.3,0.8,0.5);
  style.SetLegendStyle(legC);
  legC -> AddEntry(in0to1C, "0.0 < |#eta| < 1.0", "LP");
  legC -> AddEntry(in1to14C, "1.0 < |#eta| < 1.4", "LP");
  legC -> AddEntry(in14to22C, "1.4 < |#eta| < 2.2", "LP");

  TPaveText* dataC = new TPaveText(0.67,0.42,0.77,0.63,"ndc");
  dataC -> AddText("2017C");
  dataC -> SetFillStyle(0);
  dataC -> SetTextFont(62);
  dataC -> SetBorderSize(0);

  in0to1C -> Draw();
  in1to14C -> Draw("SAME");
  in14to22C -> Draw("SAME");
  legC -> Draw("SAME");
  dataC -> Draw("SAME");

  canC -> SaveAs("Outputdata/TriggerSF/data_2017C_efficiencies-per-eta.pdf");
  canC -> SaveAs("Outputdata/TriggerSF/data_2017C_efficiencies-per-eta.root");
  
}
