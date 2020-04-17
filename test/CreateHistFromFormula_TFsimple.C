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
#include "TMath.h"

#include "HbbStylesNew.cc"

using namespace std;

void CreateHistFromFormula_TFsimple(bool log_, int seed_){

  TH1::SetDefaultSumw2();

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  string seedstr = to_string(seed_);

  //
  // Modeling the functions
  //

  TCanvas* can = style.MakeCanvas("can","",700,700);

  TF1* funcSR1 = new TF1("funcSR1","146201*exp(-0.00536*x)",200,500);
  funcSR1 -> SetNpx(1000000);
  funcSR1 -> SetLineColor(kRed);
  funcSR1 -> Draw();

  TCanvas* canCR = style.MakeCanvas("canCR","",700,700);

  TRandom3* rand = new TRandom3(seed_);

  TH1F* CRHist = new TH1F("CRHist","",30,200,500);
  style.InitHist(CRHist,"m_{12} [GeV]","Entries / 10 GeV",kBlue,0);
  CRHist -> GetYaxis() -> SetRangeUser(0.1,75000);
  TH1F* SRHist = new TH1F("SRHist","",30,200,500);
  style.InitHist(SRHist,"m_{12} [GeV]","Entries / 10 GeV",kRed,0);
  TF1* transferfactor = new TF1("transferfactor","1/7",200,500);
  int n_obs_SR_1 = 0;
  int n_obs_SiSR_1 = 0;
  
  for (int i = 0; i < 30; i++){
    int bin = i+1;
    float bincenter = 205 + i*10;
    float value = 0;
    float error = 0;
    float sigval = 0;
    float sigerr = 0;
    value = funcSR1 -> Eval(bincenter);
    float actualvalue = rand->Poisson(value);
    CRHist -> SetBinContent(bin,actualvalue);
    error = sqrt(value);
    CRHist -> SetBinError(bin,error);
    sigval = value/7.;
    float acsigval = rand->Poisson(sigval);
    SRHist -> SetBinContent(bin,acsigval);
    sigerr = sqrt(sigval);
    SRHist -> SetBinError(bin,sigerr);
  }

  CRHist -> Draw("PE0");
  SRHist -> Draw("PE0SAME");

  //
  // SR 1, including a signal
  //

  TF1* sigfunc = new TF1("sigfunc","TMath::Gaus(x,400,5)",200,500);
  TH1F* SignalHist = new TH1F("SignalHist","",30,200,500);
  style.InitHist(SignalHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen+2,0);
  SignalHist -> FillRandom("sigfunc",2500);
  SignalHist -> Draw("PE0SAME");

  TH1F* SigSRHist = new TH1F("SigSRHist","",30,200,500);
  style.InitHist(SigSRHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen+4,0);
  SigSRHist -> Add(SignalHist);
  SigSRHist -> Add(SRHist);
  SigSRHist -> Draw("PE0SAME");

  for (unsigned int i = 0; i < SigSRHist->GetNbinsX(); i++){
    n_obs_SiSR_1 += SigSRHist->GetBinContent(i+1);
  }

  cout << "SiSR: " << n_obs_SiSR_1 << ", SR: " << n_obs_SR_1 << endl;

  TFile* outfile = new TFile(("Outputdata/TF_bias/Pseudos_10GeVBins_simpleExp_" + seedstr + ".root").c_str(),"RECREATE");
  funcSR1 -> Write();
  SRHist -> Write();
  CRHist -> Write();
  SignalHist -> Write();
  SigSRHist -> Write();
  outfile -> Close();
  cout << ("Outputdata/TF_bias/Pseudos_10GeVBins_simpleExp_" + seedstr + ".root").c_str() << " has been created" << endl;
  if (log_) {can -> SetLogy(); canCR -> SetLogy();
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_simpleExp_" + seedstr + "_log.pdf").c_str());
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_simpleExp_" + seedstr + "_log.root").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_simpleExp_" + seedstr + "_log.pdf").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_simpleExp_" + seedstr + "_log.root").c_str());
  }
  else{
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_simpleExp_" + seedstr + ".pdf").c_str());
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_simpleExp_" + seedstr + ".root").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_simpleExp_" + seedstr + ".pdf").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_simpleExp_" + seedstr + ".root").c_str());
  }
}
