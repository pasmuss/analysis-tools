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

void CreateHistFromFormula_TF(bool log_, int seed_){

  TH1::SetDefaultSumw2();

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  string seedstr = to_string(seed_);

  //
  // Modeling the functions
  //

  TCanvas* can = style.MakeCanvas("can","",700,700);
  //can -> SetLogy();

  TF1* TOSR1 = new TF1("TOSR1","0.5*(erf(0.02*(x-228.68))+1)",200,500);//slope = 0.02, TO = 228.68
  TF1* newx_Bern = new TF1("newx_Bern","(x-200)/300",200,500);//normalize to interval [0,1]: xnew = (xin-xin_min)/(xin_max-xin_min)=(xin-200)/300
  TF1* s_Bern = new TF1("s_Bern","1-newx_Bern",200,500);
  TF1* f_B0SR1 = new TF1("f_B0SR1","2.07*1*pow(s_Bern,6)*pow(newx_Bern,0)",200,500);
  TF1* f_B1SR1 = new TF1("f_B1SR1","0.0045*6*pow(s_Bern,5)*pow(newx_Bern,1)",200,500);
  TF1* f_B2SR1 = new TF1("f_B2SR1","24.08*15*pow(s_Bern,4)*pow(newx_Bern,2)",200,500);
  TF1* f_B3SR1 = new TF1("f_B3SR1","0.13*20*pow(s_Bern,3)*pow(newx_Bern,3)",200,500);
  TF1* f_B4SR1 = new TF1("f_B4SR1","6.21*15*pow(s_Bern,2)*pow(newx_Bern,4)",200,500);
  TF1* f_B5SR1 = new TF1("f_B5SR1","1.92*6*pow(s_Bern,1)*pow(newx_Bern,5)",200,500);
  TF1* f_B6SR1 = new TF1("f_B6SR1","1.76*1*pow(s_Bern,0)*pow(newx_Bern,6)",200,500);

  TF1* funcSR1 = new TF1("funcSR1","(f_B0SR1+f_B1SR1+f_B2SR1+f_B3SR1+f_B4SR1+f_B5SR1+f_B6SR1)*TOSR1*6028",200,500);//last factor to scale to data (about 52k)
  //maximum 20GeV binning data: 103872; max here w/o scale: 8.615; norm  = 12057
  funcSR1 -> SetNpx(1000000);
  funcSR1 -> SetLineColor(kRed);
  TF1* fuckroot = new TF1("fuckroot","funcSR1",180,2100);
  fuckroot -> SetTitle("");
  fuckroot -> SetLineColor(kWhite);
  fuckroot -> GetYaxis() -> SetRangeUser(0.01,60000);
  //fuckroot -> GetYaxis() -> SetRangeUser(0.1,1000000);
  fuckroot -> Draw();
  funcSR1 -> Draw("SAME");

  TF1* TOSR2 = new TF1("TOSR2","0.5*(erf(0.01*(x-260.07))+1)",260,785);//slope = 0.01, TO = 260.07
  TF1* l2 = new TF1("l2","pow(log(1+0.01*(x-281.74)-2.08e-6*(pow((x-281.74),2))),2)",260,785);
  TF1* SNSR2 = new TF1("SNSR2","exp(-1.47*l2-0.17)",260,785);
  TF1* funcSR20 = new TF1("funcSR20","TOSR2*SNSR2",260,785);
  double normsr2 = funcSR1->GetMaximum()/funcSR20->GetMaximum();
  TF1* funcSR2 = new TF1("funcSR2","[0]*TOSR2*SNSR2",260,785);//[0] to adjust max to same height
  funcSR2 -> SetParameter(0,normsr2);
  funcSR2 -> SetLineColor(kCyan);
  funcSR2 -> Draw("SAME");

  TF1* l2SR3 = new TF1("l2SR3","pow(log(1+0.012*(x-239.477)),2)",390,1270);
  TF1* SNSR3 = new TF1("SNSR3","exp(-1.2*l2SR3-0.209)",390,1270);
  TF1* funcSR3 = new TF1("funcSR3","[0]*SNSR3",390,1270);//[0] to adjust same normalization
  double normsr3 = (funcSR2 -> Eval(587.5))/(SNSR3 -> Eval(587.5));
  funcSR3 -> SetParameter(0,normsr3);
  funcSR3 -> SetLineColor(kGreen);
  funcSR3 -> Draw("SAME");

  TF1* l2SR4 = new TF1("l2SR4","pow(log(1+0.013*(x-394.241)),2)",500,2000);
  TF1* SNSR4 = new TF1("SNSR4","exp(-1.0*l2SR4-0.2499)",500,2000);
  TF1* funcSR4 = new TF1("funcSR4","[0]*SNSR4",500,2000);//[0] to adjust same normalization
  double normsr4 = (funcSR3 -> Eval(885))/(SNSR4 -> Eval(885));
  funcSR4 -> SetParameter(0,normsr4);
  funcSR4 -> SetLineColor(kBlue);  
  funcSR4 -> Draw("SAME");

  TLegend* leg = new TLegend(0.44,0.70,0.84,0.90);
  style.SetLegendStyle(leg);
  leg -> AddEntry(funcSR1,"Bernstein7*TO (SR 1)","L");
  leg -> AddEntry(funcSR2,"Ext. Novosibirsk*TO (SR 2)","L");
  leg -> AddEntry(funcSR3,"Novosibirsk (SR 3)","L");
  leg -> AddEntry(funcSR4,"Novosibirsk (SR 4)","L");
  leg -> Draw("SAME");

  //
  // Creating pseudo histograms (Asimov)
  // (a) CR: Based on TF1 above
  // (b) SR: Based on TF1 above times TF fit from MC
  // (c) TF: New division of SR/CR
  // Ranges for histograms (switching to next SR and center of overlap):
  // (1) 200 - 380 // 9 bins
  // (2) 380 - 580 // 10 bins
  // (3) 580 - 880 // 15 bins
  // (4) 880 - 2000 // 56 bins
  //

  TCanvas* canCR = style.MakeCanvas("canCR","",700,700);

  TRandom3* rand = new TRandom3(seed_);//standard: 1904

  TH1F* CRHist = new TH1F("CRHist","",180,200,2000);
  style.InitHist(CRHist,"m_{12} [GeV]","Entries / 10 GeV",kBlue,0);
  TH1F* SRHist = new TH1F("SRHist","",180,200,2000);
  style.InitHist(SRHist,"m_{12} [GeV]","Entries / 10 GeV",kRed,0);

  TH1F* CRHist_SR1 = new TH1F("CRHist_SR1","",180,200,2000);
  style.InitHist(CRHist_SR1,"m_{12} [GeV]","Entries / 10 GeV",kBlue,0);
  TH1F* SRHist_SR1 = new TH1F("SRHist_SR1","",180,200,2000);
  style.InitHist(SRHist_SR1,"m_{12} [GeV]","Entries / 10 GeV",kRed,0);

  TF1* transferfactor = new TF1("transferfactor","[0]*erf([2]*(x-[1]))*(1+[3]*x)",200,2000);
  transferfactor -> SetParameters(0.16,93,7.5e-3,-1.5e-4);
  int n_obs_SR_1 = 0;
  int n_obs_SiSR_1 = 0;
  
  for (int i = 0; i < 180; i++){
    int bin = i+1;
    float bincenter = 205 + i*10;
    float value = 0;
    float error = 0;
    float tfval = transferfactor->Eval(bincenter);
    float sigval = 0;
    float sigerr = 0;
    if (i < 18){
      value = funcSR1 -> Eval(bincenter);
    }
    else if (i < 38){
      value = funcSR2 -> Eval(bincenter);
    }
    else if (i < 68){
      value = funcSR3 -> Eval(bincenter);
    }
    else{
      value = funcSR4 -> Eval(bincenter);
    }
    float actualvalue = rand->Poisson(value);
    CRHist -> SetBinContent(bin,actualvalue);
    //CRHist -> SetBinErrorOption((TH1::EBinErrorOpt) 1);
    error = sqrt(value);
    CRHist -> SetBinError(bin,error);
    sigval = value*tfval;
    float acsigval = rand->Poisson(sigval);
    SRHist -> SetBinContent(bin,acsigval);
    sigerr = sqrt(sigval);
    SRHist -> SetBinError(bin,sigerr);
    if (i < 30){
      CRHist_SR1 -> SetBinContent(bin,actualvalue);
      CRHist_SR1 -> SetBinError(bin,error);
      SRHist_SR1 -> SetBinContent(bin,acsigval);
      SRHist_SR1 -> SetBinError(bin,sigerr); 
      n_obs_SR_1 += acsigval;
      }
    //SRHist -> SetBinErrorOption((TH1::EBinErrorOpt) 1);
  }

  CRHist -> Draw("PE0");
  SRHist -> Draw("PE0SAME");

  //
  // SR 1, including a signal
  //

  TCanvas* c_withsig = style.MakeCanvas("c_withsig","",700,700);
  CRHist_SR1 -> GetYaxis() -> SetRangeUser(0.01,100000);
  CRHist_SR1 -> Draw("PE0");
  SRHist_SR1 -> Draw("PE0SAME");

  TF1* sigfunc = new TF1("sigfunc","TMath::Gaus(x,400,10)",200,500);
  TH1F* SignalHist = new TH1F("SignalHist","",30,200,500);
  style.InitHist(SignalHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen+2,0);
  SignalHist -> FillRandom("sigfunc",5000);
  SignalHist -> Draw("PE0SAME");

  //
  // First: Change number of entries: 2k -> 5k -> 25k -> 100
  // Second: Kepp one of these numbers and change peak to 390 -> 375 and then width to 2 -> 17
  //

  TF1* sigfunc2 = new TF1("sigfunc2","TMath::Gaus(x,400,10)",200,500);
  TH1F* SignalHist2 = new TH1F("SignalHist2","",30,200,500);
  style.InitHist(SignalHist2,"m_{12} [GeV]","Entries / 10 GeV",kGreen+6,0);
  SignalHist2 -> FillRandom("sigfunc2",500);
  SignalHist2 -> Draw("PE0SAME");

  TH1F* SigSRHist = new TH1F("SigSRHist","",30,200,500);
  style.InitHist(SigSRHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen+4,0);
  SigSRHist -> Add(SignalHist2);
  SigSRHist -> Add(SRHist_SR1);
  SigSRHist -> Draw("PE0SAME");

  for (unsigned int i = 0; i < SigSRHist->GetNbinsX(); i++){
    n_obs_SiSR_1 += SigSRHist->GetBinContent(i+1);
  }

  cout << "SiSR: " << n_obs_SiSR_1 << ", SR: " << n_obs_SR_1 << endl;

  //
  // Transfer Factor
  //

  TH1F* TFHist = (TH1F*)SRHist->Clone(); TFHist->SetName("TFHist");
  style.InitHist(TFHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen,0);
  TFHist -> Divide(CRHist);
  TFHist -> GetYaxis() -> SetRangeUser(0.01,0.3);

  TCanvas* canTF = style.MakeCanvas("canTF","",700,700);
  TFHist -> Draw("PE0");

  //
  // Saving
  //

  TFile* outfile = new TFile(("Outputdata/TF_bias/Pseudos_10GeVBins_Sig500EvtsMu400Sig10" + seedstr + ".root").c_str(),"RECREATE");
  funcSR1 -> Write();
  funcSR2 -> Write();
  funcSR3 -> Write();
  funcSR4 -> Write();
  SRHist -> Write();
  CRHist -> Write();
  TFHist -> Write();
  SignalHist -> Write();
  SigSRHist -> Write();
  CRHist_SR1 -> Write();
  SRHist_SR1 -> Write();
  outfile -> Close();
  cout << ("Outputdata/TF_bias/Pseudos_10GeVBins_Sig500EvtsMu400Sig10" + seedstr + ".root").c_str() << " has been created" << endl;
  /*if (log_) {can -> SetLogy(); canTF -> SetLogy(); canCR -> SetLogy(); c_withsig -> SetLogy();
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_Sig5kEvts" + seedstr + "_log.pdf").c_str());
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_Sig5kEvts" + seedstr + "_log.root").c_str());
    canTF -> SaveAs(("Outputdata/TF_bias/PseudoTFFromTF1_10GeVBins_Sig5kEvts" + seedstr + "_log.pdf").c_str());
    canTF -> SaveAs(("Outputdata/TF_bias/PseudoTFFromTF1_10GeVBins_Sig5kEvts" + seedstr + "_log.root").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_Sig5kEvts" + seedstr + "_log.pdf").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_Sig5kEvts" + seedstr + "_log.root").c_str());
    c_withsig -> SaveAs(("Outputdata/TF_bias/PseudoSignal_10GeVBins_Sig5kEvts" + seedstr + "_log.pdf").c_str()); 
  }
  else{
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_Sig5kEvts" + seedstr + ".pdf").c_str());
    can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_10GeVBins_Sig5kEvts" + seedstr + ".root").c_str());
    canTF -> SaveAs(("Outputdata/TF_bias/PseudoTFFromTF1_10GeVBins_Sig5kEvts" + seedstr + ".pdf").c_str());
    canTF -> SaveAs(("Outputdata/TF_bias/PseudoTFFromTF1_10GeVBins_Sig5kEvts" + seedstr + ".root").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_Sig5kEvts" + seedstr + ".pdf").c_str());
    canCR -> SaveAs(("Outputdata/TF_bias/PseudoCRSRFromTF1_10GeVBins_Sig5kEvts" + seedstr + ".root").c_str());
    c_withsig -> SaveAs(("Outputdata/TF_bias/PseudoSignal_10GeVBins_Sig5kEvts" + seedstr + ".pdf").c_str());
    }*/
}
