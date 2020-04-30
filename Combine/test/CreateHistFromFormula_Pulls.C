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

void CreateHistFromFormula_Pulls(int number_){

  TH1::SetDefaultSumw2();

  //
  // Modeling the function
  //

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

  TF1* transferfactor = new TF1("transferfactor","[0]*erf([2]*(x-[1]))*(1+[3]*x)",200,2000);
  transferfactor -> SetParameters(0.16,93,7.5e-3,-1.5e-4);

  //
  // Defining the signal template
  //

  TF1* sigfunc = new TF1("sigfunc","TMath::Gaus(x,400,10)",200,500);
  TH1F* SignalHist = new TH1F("SignalHist","",30,200,500);
  SignalHist -> FillRandom("sigfunc",2000);//template, always same

  //
  // Creating pseudo histograms (Asimov)
  // In order to do consistency checks: Run n (e.g. 1000) toys with different random seeds
  // and compare the r value (combine) they yield with the expected one
  // --> plot pulls
  // Signal: always same (to have a fix point)
  // CR and SR histograms (pseudo-data_obs) to change
  // for now: only SR 1
  //
  
  vector<string> signalstrengths = {"0p0", "0p05", "0p1", "0p25", "0p5", "1p0", "5p0"};
  vector<int>    signalevents    = {   0 ,   100  ,  200 ,  500,    1000,  2000, 10000};//relative to 2k signal template events
  std::map<std::string, TH1F*> histograms;

  TFile* outfile = new TFile(("VariousSignalStrengths_CombineTest_" + to_string(number_) + "iterations.root").c_str(),"RECREATE");
  SignalHist -> Write();

  for(int sample = 0; sample < number_; sample++){
    
    int seed = (sample * 17) + 2412;
    TRandom3* rand = new TRandom3(seed);
    
    cout << "Generating Asimov for sample" << sample + 1 << ", seed " << seed << endl;

    histograms[Form("CR_Hist_%i",sample)] = new TH1F(Form("CR_Hist_%i",sample),"",180,200,2000);
    
    for (int strength = 0; strength < signalstrengths.size(); strength ++){
      histograms[Form("Sig_Hist_%i_%s",sample,signalstrengths[strength].c_str())] = new TH1F(Form("Sig_Hist_%i_%s",sample,signalstrengths[strength].c_str()),"",30,200,500);
      histograms[Form("SR_Hist_%i_%s",sample,signalstrengths[strength].c_str())] = new TH1F(Form("SR_Hist_%i_%s",sample,signalstrengths[strength].c_str()),"",180,200,2000);//will always include signal
      histograms[Form("Sig_Hist_%i_%s",sample,signalstrengths[strength].c_str())] -> FillRandom("sigfunc",signalevents[strength]);
    }
      
    for (int i = 0; i < 30; i++){
      int bin = i+1;
      float bincenter = 205 + i*10;
      float tfval = transferfactor->Eval(bincenter);
      float value = funcSR1->Eval(bincenter);
      float actualvalue = rand->Poisson(value);
      histograms[Form("CR_Hist_%i",sample)] -> SetBinContent(bin,actualvalue);
      float error = sqrt(actualvalue);
      histograms[Form("CR_Hist_%i",sample)] -> SetBinError(bin,error);
      for (int strength = 0; strength < signalstrengths.size(); strength ++){
	float sigval = (value*tfval) + histograms[Form("Sig_Hist_%i_%s",sample,signalstrengths[strength].c_str())]->GetBinContent(bin);
	float acsigval = rand->Poisson(sigval);
	float sigerr = sqrt(acsigval);
	histograms[Form("SR_Hist_%i_%s",sample,signalstrengths[strength].c_str())] -> SetBinContent(bin,acsigval);
	histograms[Form("SR_Hist_%i_%s",sample,signalstrengths[strength].c_str())] -> SetBinError(bin,sigerr);
      }
    }
    for (int strength = 0; strength < signalstrengths.size(); strength ++) histograms[Form("SR_Hist_%i_%s",sample,signalstrengths[strength].c_str())] -> Write();
    histograms[Form("CR_Hist_%i",sample)] -> Write();
  }

  outfile -> Close();
  cout << ("VariousSignalStrengths_CombineTest_" + to_string(number_) + "iterations.root").c_str() << " has been created" << endl;
}
