#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>

#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TAttAxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>
#include "TMath.h"

#include "HbbStylesNew.cc"

using namespace std;

void CreateHistFromFormula_TF(bool log_=false, int seed_=1904){

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

  TF1* TOSR1 = new TF1("TOSR1","0.5*(erf(0.02*(x-229.047))+1)",200,500);//slope = 0.02, TO = 228.68
  TF1* newx_Bern = new TF1("newx_Bern","(x-200)/300",200,500);//normalize to interval [0,1]: xnew = (xin-xin_min)/(xin_max-xin_min)=(xin-200)/300
  TF1* s_Bern = new TF1("s_Bern","1-newx_Bern",200,500);
  TF1* f_B0SR1 = new TF1("f_B0SR1","2.31*1*pow(s_Bern,6)*pow(newx_Bern,0)",200,500);
  TF1* f_B1SR1 = new TF1("f_B1SR1","3.1e-7*6*pow(s_Bern,5)*pow(newx_Bern,1)",200,500);
  TF1* f_B2SR1 = new TF1("f_B2SR1","25*15*pow(s_Bern,4)*pow(newx_Bern,2)",200,500);
  TF1* f_B3SR1 = new TF1("f_B3SR1","0.779*20*pow(s_Bern,3)*pow(newx_Bern,3)",200,500);
  TF1* f_B4SR1 = new TF1("f_B4SR1","6.16*15*pow(s_Bern,2)*pow(newx_Bern,4)",200,500);
  TF1* f_B5SR1 = new TF1("f_B5SR1","2.16*6*pow(s_Bern,1)*pow(newx_Bern,5)",200,500);
  TF1* f_B6SR1 = new TF1("f_B6SR1","1.848*1*pow(s_Bern,0)*pow(newx_Bern,6)",200,500);

  TF1* funcSR1 = new TF1("funcSR1","(f_B0SR1+f_B1SR1+f_B2SR1+f_B3SR1+f_B4SR1+f_B5SR1+f_B6SR1)*TOSR1*588.845295",200,500);//last factor to scale to data (about 53k for 10 GeV bins, 26151 for 5 GeV bins, 5349 for 1 GeV)
  //maximum 20GeV binning data: 103872; max here w/o scale: 9.08388 --> (5 GeV bins) --> norm 2878.835916
  cout << "max bef scale: " << funcSR1->GetMaximum() << endl;
  funcSR1 -> SetNpx(1000000);
  funcSR1 -> SetLineColor(kRed);
  TF1* fuckroot = new TF1("fuckroot","funcSR1",180,2100);
  fuckroot -> SetTitle("");
  fuckroot -> SetLineColor(kWhite);
  fuckroot -> GetYaxis() -> SetRangeUser(0.01,30000);
  //fuckroot -> GetYaxis() -> SetRangeUser(0.1,1000000);
  fuckroot -> Draw();
  funcSR1 -> Draw("SAME");

  /*

    Definition Novosibirsk:
    Extended (SR2): par != 0 (par == 0 in SR 3/4)

    xsi = 2*sqrt(ln4) = 2.3548
    w0 = 2/xsi * asinh(tail*xsi/2)
    frac1 = (x-peak)*tail/width

    SN(x) = exp[ -0.5/(w0^2) * log^2{ 1 - frac1 - ( par*(x-peak)^2*tail/width )} - w0^2/2 ]

  */

  //par = 0.000232, peak = 270.117, tail = -0.8788, width = 51.8367
  //(TO): slope = 0.01, turnon = 281.955
  //--> w0 = -0.769
  TF1* TOSR2 = new TF1("TOSR2","0.5*(erf(0.01*(x-281.955))+1)",260,785);//slope = 0.01, TO = 260.07
  TF1* l2 = new TF1("l2","pow(log(1+0.017*(x-270.117)+3.933e-6*(pow((x-270.117),2))),2)",260,785);
  TF1* SNSR2 = new TF1("SNSR2","exp(-0.8455*l2-0.296)",260,785);
  TF1* funcSR20 = new TF1("funcSR20","TOSR2*SNSR2",260,785);
  double normsr2 = funcSR1->GetMaximum()/funcSR20->GetMaximum();
  TF1* funcSR2 = new TF1("funcSR2","[0]*TOSR2*SNSR2",260,785);//[0] to adjust max to same height
  funcSR2 -> SetParameter(0,normsr2);
  funcSR2 -> SetLineColor(kCyan);
  funcSR2 -> Draw("SAME");

  //peak (frozen) = 240, tail = -0.71, width = 57.801
  //--> w0 = 0.646
  TF1* l2SR3 = new TF1("l2SR3","pow(log(1+0.012*(x-240)),2)",390,1270);
  TF1* SNSR3 = new TF1("SNSR3","exp(-1.198*l2SR3-0.209)",390,1270);
  TF1* funcSR3 = new TF1("funcSR3","[0]*SNSR3",390,1270);//[0] to adjust same normalization
  double normsr3 = (funcSR2 -> Eval(587.5))/(SNSR3 -> Eval(587.5));
  funcSR3 -> SetParameter(0,normsr3);
  funcSR3 -> SetLineColor(kGreen);
  funcSR3 -> Draw("SAME");

  //peak (frozen) = 240, tail = -0.764, width = 51.046
  //--> w0 = -0.687
  TF1* l2SR4 = new TF1("l2SR4","pow(log(1+0.015*(x-240)),2)",500,2000);
  TF1* SNSR4 = new TF1("SNSR4","exp(-1.06*l2SR4-0.236)",500,2000);
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

  //  TCanvas* canCR = style.MakeCanvas("canCR","",700,700);

  TRandom3* rand = new TRandom3(seed_);//standard: 1904

  TH1F* CRHist = new TH1F("CRHist","",90,200,2000);
  style.InitHist(CRHist,"m_{12} [GeV]","Entries / 10 GeV",kBlue,0);
  TH1F* SRHist = new TH1F("SRHist","",90,200,2000);
  style.InitHist(SRHist,"m_{12} [GeV]","Entries / 10 GeV",kRed,0);

  TF1* transferfactor = new TF1("transferfactor","[0]*erf([2]*(x-[1]))*(1+[3]*x)",200,2000);
  transferfactor -> SetParameters(0.16,93,7.5e-3,-1.5e-4);
  int n_obs_SR_1 = 0;
  int n_obs_SiSR_1 = 0;
  
  for (int i = 0; i < 90; i++){
    int bin = i+1;
    float bincenter = 210 + i*20;
    float value = 0;
    float error = 0;
    float tfval = transferfactor->Eval(bincenter);
    float sigval = 0;
    float sigerr = 0;
    if (i < 9){
      value = funcSR1 -> Eval(bincenter);
    }
    else if (i < 19){
      value = funcSR2 -> Eval(bincenter);
    }
    else if (i < 34){
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
    //SRHist -> SetBinErrorOption((TH1::EBinErrorOpt) 1);
  }

  //  CRHist -> Draw("PE0");
  //SRHist -> Draw("PE0SAME");

  TGaxis::SetMaxDigits(4);

  //
  // Subrange Transfer Factors
  //

  TF1* transferfactor_SR1 = new TF1("transferfactor_SR1","[0]*erf([2]*(x-[1]))",200,500);
  transferfactor_SR1 -> SetParameters(0.145,152,0.016);
  TF1* transferfactor_SR2 = new TF1("transferfactor_SR2","0.1458",260,785);
  TF1* transferfactor_SR3 = new TF1("transferfactor_SR3","[0]*x+[1]",390,1270);
  transferfactor_SR3 -> SetParameters(-1.27e-5,0.15);
  TF1* transferfactor_SR4 = new TF1("transferfactor_SR4","[0]*x+[1]",500,2000);
  transferfactor_SR4 -> SetParameters(-2.65e-5,0.17);


  ///
  /// Properly binned SR1 hist (1 GeV)
  ///

  TCanvas* canCR_SR1 = style.MakeCanvas("canCR_SR1","SR1",700,700);

  TH1F* CRHist_SR1 = new TH1F("CRHist_SR1","",300,200,500);
  style.InitHist(CRHist_SR1,"m_{12} [GeV]","Entries / 5 GeV",kBlue,0);
  TH1F* SRHist_SR1 = new TH1F("SRHist_SR1","",300,200,500);
  style.InitHist(SRHist_SR1,"m_{12} [GeV]","Entries / 5 GeV",kRed,0);

  for (int i_SR1 = 0; i_SR1 < 300; i_SR1++){
    int bin_SR1 = i_SR1+1;
    float bincenter_SR1 = 200.5 + i_SR1*1;
    float value_SR1 = 0;
    float error_SR1 = 0;
    float tfval_SR1 = transferfactor_SR1->Eval(bincenter_SR1);
    float sigval_SR1 = 0;
    float sigerr_SR1 = 0;
    value_SR1 = funcSR1 -> Eval(bincenter_SR1);
    float actualvalue_SR1 = rand->Poisson(value_SR1);
    CRHist_SR1 -> SetBinContent(bin_SR1,actualvalue_SR1);
    //CRHist -> SetBinErrorOption((TH1::EBinErrorOpt) 1);
    error_SR1 = sqrt(value_SR1);
    CRHist_SR1 -> SetBinError(bin_SR1,error_SR1);
    sigval_SR1 = value_SR1*tfval_SR1;
    float acsigval_SR1 = rand->Poisson(sigval_SR1);
    SRHist_SR1 -> SetBinContent(bin_SR1,acsigval_SR1);
    sigerr_SR1 = sqrt(sigval_SR1);
    SRHist_SR1 -> SetBinError(bin_SR1,sigerr_SR1);
  }

  CRHist_SR1 -> GetYaxis() -> SetTitleOffset(1.2);
  CRHist_SR1 -> Draw("PE0");
  SRHist_SR1 -> Draw("PE0SAME");


  ///
  /// Properly binned SR2 hist (1 GeV)
  ///

  TCanvas* canCR_SR2 = style.MakeCanvas("canCR_SR2","SR2",700,700);

  TH1F* CRHist_SR2 = new TH1F("CRHist_SR2","",525,260,785);
  style.InitHist(CRHist_SR2,"m_{12} [GeV]","Entries / 5 GeV",kBlue,0);
  TH1F* SRHist_SR2 = new TH1F("SRHist_SR2","",525,260,785);
  style.InitHist(SRHist_SR2,"m_{12} [GeV]","Entries / 5 GeV",kRed,0);

  for (int i_SR2 = 0; i_SR2 < 525; i_SR2++){
    int bin_SR2 = i_SR2+1;
    float bincenter_SR2 = 260.5 + i_SR2*1;
    float value_SR2 = 0;
    float error_SR2 = 0;
    float tfval_SR2 = transferfactor_SR2->Eval(bincenter_SR2);
    float sigval_SR2 = 0;
    float sigerr_SR2 = 0;
    value_SR2 = funcSR2 -> Eval(bincenter_SR2);
    float actualvalue_SR2 = rand->Poisson(value_SR2);
    CRHist_SR2 -> SetBinContent(bin_SR2,actualvalue_SR2);
    //CRHist -> SetBinErrorOption((TH1::EBinErrorOpt) 1);
    error_SR2 = sqrt(value_SR2);
    CRHist_SR2 -> SetBinError(bin_SR2,error_SR2);
    sigval_SR2 = value_SR2*tfval_SR2;
    float acsigval_SR2 = rand->Poisson(sigval_SR2);
    SRHist_SR2 -> SetBinContent(bin_SR2,acsigval_SR2);
    sigerr_SR2 = sqrt(sigval_SR2);
    SRHist_SR2 -> SetBinError(bin_SR2,sigerr_SR2);
  }

  CRHist_SR2 ->GetYaxis() -> SetTitleOffset(1.1);
  CRHist_SR2 -> Draw("PE0");
  SRHist_SR2 -> Draw("PE0SAME");

  ///
  /// Properly binned SR3 hist (5 GeV)
  ///

  TCanvas* canCR_SR3 = style.MakeCanvas("canCR_SR3","SR3",700,700);

  TH1F* CRHist_SR3 = new TH1F("CRHist_SR3","",176,390,1270);
  style.InitHist(CRHist_SR3,"m_{12} [GeV]","Entries / 5 GeV",kBlue,0);
  TH1F* SRHist_SR3 = new TH1F("SRHist_SR3","",176,390,1270);
  style.InitHist(SRHist_SR3,"m_{12} [GeV]","Entries / 5 GeV",kRed,0);

  for (int i_SR3 = 0; i_SR3 < 176; i_SR3++){
    int bin_SR3 = i_SR3+1;
    float bincenter_SR3 = 392.5 + i_SR3*5;
    float value_SR3 = 0;
    float error_SR3 = 0;
    float tfval_SR3 = transferfactor_SR3->Eval(bincenter_SR3);
    float sigval_SR3 = 0;
    float sigerr_SR3 = 0;
    value_SR3 = funcSR3 -> Eval(bincenter_SR3);
    float actualvalue_SR3 = rand->Poisson(value_SR3);
    CRHist_SR3 -> SetBinContent(bin_SR3,actualvalue_SR3);
    //CRHist -> SetBinErrorOption((TH1::EBinErrorOpt) 1);
    error_SR3 = sqrt(value_SR3);
    CRHist_SR3 -> SetBinError(bin_SR3,error_SR3);
    sigval_SR3 = value_SR3*tfval_SR3;
    float acsigval_SR3 = rand->Poisson(sigval_SR3);
    SRHist_SR3 -> SetBinContent(bin_SR3,acsigval_SR3);
    sigerr_SR3 = sqrt(sigval_SR3);
    SRHist_SR3 -> SetBinError(bin_SR3,sigerr_SR3);
  }

  CRHist_SR3 -> GetYaxis() -> SetTitleOffset(1.1);
  CRHist_SR3 -> Draw("PE0");
  SRHist_SR3 -> Draw("PE0SAME");

  ///
  /// Properly binned SR4 hist (10 GeV)
  ///

  TCanvas* canCR_SR4 = style.MakeCanvas("canCR_SR4","SR4",700,700);

  TH1F* CRHist_SR4 = new TH1F("CRHist_SR4","",150,500,2000);
  style.InitHist(CRHist_SR4,"m_{12} [GeV]","Entries / 10 GeV",kBlue,0);
  TH1F* SRHist_SR4 = new TH1F("SRHist_SR4","",150,500,2000);
  style.InitHist(SRHist_SR4,"m_{12} [GeV]","Entries / 10 GeV",kRed,0);
  
  //CRHist_SR4 -> GetYaxis() -> SetMaxDigits(3);
  //SRHist_SR4 -> GetYaxis() -> SetMaxDigits(3);

  for (int i_SR4 = 0; i_SR4 < 150; i_SR4++){
    int bin_SR4 = i_SR4+1;
    float bincenter_SR4 = 505.0 + i_SR4*5;
    float value_SR4 = 0;
    float error_SR4 = 0;
    float tfval_SR4 = transferfactor_SR4->Eval(bincenter_SR4);
    float sigval_SR4 = 0;
    float sigerr_SR4 = 0;
    value_SR4 = funcSR4 -> Eval(bincenter_SR4);
    float actualvalue_SR4 = rand->Poisson(value_SR4);
    CRHist_SR4 -> SetBinContent(bin_SR4,actualvalue_SR4);
    //CRHist -> SetBinErrorOption((TH1::EBinErrorOpt) 1);
    error_SR4 = sqrt(value_SR4);
    CRHist_SR4 -> SetBinError(bin_SR4,error_SR4);
    sigval_SR4 = value_SR4*tfval_SR4;
    float acsigval_SR4 = rand->Poisson(sigval_SR4);
    SRHist_SR4 -> SetBinContent(bin_SR4,acsigval_SR4);
    sigerr_SR4 = sqrt(sigval_SR4);
    SRHist_SR4 -> SetBinError(bin_SR4,sigerr_SR4);
  }

  CRHist_SR4 ->GetYaxis() -> SetTitleOffset(1.1);
  CRHist_SR4 -> Draw("PE0");
  SRHist_SR4 -> Draw("PE0SAME");

  //
  // SR 1, including a signal
  //

  //TCanvas* c_withsig = style.MakeCanvas("c_withsig","",700,700);
  CRHist_SR1 -> GetYaxis() -> SetRangeUser(0.01,100000);
  //  CRHist_SR1 -> Draw("PE0");
  //SRHist_SR1 -> Draw("PE0SAME");

  TF1* sigfunc = new TF1("sigfunc","TMath::Gaus(x,400,10)",200,500);
  TH1F* SignalHist = new TH1F("SignalHist","",30,200,500);
  style.InitHist(SignalHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen+2,0);
  //SignalHist -> FillRandom("sigfunc",5000);
  //SignalHist -> Draw("PE0SAME");

  //
  // First: Change number of entries: 2k -> 5k -> 25k -> 100
  // Second: Kepp one of these numbers and change peak to 390 -> 375 and then width to 2 -> 17
  //

  TF1* sigfunc2 = new TF1("sigfunc2","TMath::Gaus(x,400,10)",200,500);
  TH1F* SignalHist2 = new TH1F("SignalHist2","",30,200,500);
  style.InitHist(SignalHist2,"m_{12} [GeV]","Entries / 10 GeV",kGreen+6,0);
  //SignalHist2 -> FillRandom("sigfunc2",500);
  //SignalHist2 -> Draw("PE0SAME");

  TH1F* SigSRHist = new TH1F("SigSRHist","",30,200,500);
  style.InitHist(SigSRHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen+4,0);
  SigSRHist -> Add(SignalHist2);
  SigSRHist -> Add(SRHist_SR1);
  //SigSRHist -> Draw("PE0SAME");

  /*for (unsigned int i = 0; i < SigSRHist->GetNbinsX(); i++){
    n_obs_SiSR_1 += SigSRHist->GetBinContent(i+1);
  }

  cout << "SiSR: " << n_obs_SiSR_1 << ", SR: " << n_obs_SR_1 << endl;
  */
  //
  // Transfer Factor
  //

  TH1F* TFHist = (TH1F*)SRHist->Clone(); TFHist->SetName("TFHist");
  style.InitHist(TFHist,"m_{12} [GeV]","Entries / 10 GeV",kGreen,0);
  TFHist -> Divide(CRHist);
  TFHist -> GetYaxis() -> SetRangeUser(0.01,0.3);

  //TCanvas* canTF = style.MakeCanvas("canTF","",700,700);
  //TFHist -> Draw("PE0");

  //
  // Saving
  //

  /*  TFile* outfile = new TFile(("Outputdata/TF_bias/Pseudos_evenFiner1GeVBins_" + seedstr + ".root").c_str(),"RECREATE");
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
  CRHist_SR2 -> Write();
  SRHist_SR2 -> Write();
  CRHist_SR2 -> Write();
  SRHist_SR3 -> Write();
  CRHist_SR4 -> Write();
  SRHist_SR4 -> Write();
  outfile -> Close();
  cout << ("Outputdata/TF_bias/Pseudos_evenFiner1GeVBins_" + seedstr + ".root").c_str() << " has been created" << endl;
  can -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_fineBinsForCombine1GeV_functions_" + seedstr + ".pdf").c_str());
  canCR_SR1 -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_fineBinsForCombine1GeV_histsSR1_" + seedstr + ".pdf").c_str());
  canCR_SR2 -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_fineBinsForCombine1GeV_histsSR2_" + seedstr + ".pdf").c_str());
  canCR_SR3 -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_fineBinsForCombine1GeV_histsSR3_" + seedstr + ".pdf").c_str());
  canCR_SR4 -> SaveAs(("Outputdata/TF_bias/subranges_modeled_4TF1s_fineBinsForCombine1GeV_histsSR4_" + seedstr + ".pdf").c_str());*/
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
