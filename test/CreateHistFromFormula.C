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

void CreateHistFromFormula(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TCanvas* can = style.MakeCanvas("can","",700,700);
  can -> SetLogy();

  //float bins[76] = {200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,720,740,760,780,800,820,840,860,880,900,920,940,960,980,1000,1020,1040,1060,1080,1100,1120,1140,1160,1180,1200,1220,1240,1260,1280,1300,1320,1340,1360,1380,1400,1420,1440,1460,1480,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000};
  
  TF1* SNTO = new TF1("SNTO","exp(-1.2276*pow(log(1+(0.7*(x-240))/50),2)-0.2037)*erf(0.015*(x-200)+1)",200,2000);
  SNTO -> SetNpx(1000000);
  //SNTO -> Draw();

  //TH1F* SuperNovoIntermHist = new TH1F("SuperNovoIntermHist","",140,200,3000);
  //SuperNovoIntermHist -> FillRandom("SNTO",1000000);

  TH1F* SuperNovoHist = new TH1F("SuperNovoHist","",30,200,2000);
  style.InitHist(SuperNovoHist,"m_{12} [GeV]","a.u.",kRed,0);
  SuperNovoHist -> FillRandom("SNTO",10000000);
  SuperNovoHist -> GetYaxis() -> SetRangeUser(0.1,1e8);
  //for (int i = 0; i < 10; i++) SuperNovoHist -> SetBinContent(i,0);
  //SuperNovoHist -> Add(SuperNovoIntermHist);
  //SuperNovoHist -> GetXaxis() -> SetRangeUser(160,2000);
  SuperNovoHist -> Draw("E0");

  //TF1* transfer = new TF1("transfer","0.5*erf(0.008*(x-88))",200,2000);
  TF1* transfer = new TF1("transfer","3.2*x",200,2000);
  TF1* signalregionbg = new TF1("signalregionbg","SNTO*transfer");
  signalregionbg -> SetNpx(1000000);

  TH1F* SignalRegionHist = new TH1F("SignalRegionHist","",30,200,2000);
  style.InitHist(SignalRegionHist,"m_{12} [GeV]","a.u.",kBlue,0);
  for (unsigned int bin = 1; bin < 31; bin++){
    cout << "bin " << bin;
    float CRcont = SuperNovoHist -> GetBinContent(bin);
    cout << " content: " << CRcont;
    float bincenter = SuperNovoHist -> GetBinCenter(bin);
    cout << " , center: " << bincenter;
    float SRcont = CRcont * 0.0003 * bincenter;
    cout << " --> SR content: " << SRcont << endl;
    SignalRegionHist -> SetBinContent(bin,SRcont);
  }
  //SignalRegionHist -> FillRandom("SNTO",1000000);
  //SignalRegionHist -> FillRandom("signalregionbg",1000000);
  SignalRegionHist -> Draw("E0SAME");

  //float sigbins[25] = {1100,1120,1140,1160,1180,1200,1220,1240,1260,1280,1300,1320,1340,1360,1380,1400,1420,1440,1460,1480,1500,1550,1600,1650,1700};

  TF1* sigfunc = new TF1("sigfunc","TMath::Gaus(x,1400,100)",1100,1700);
  TH1F* SignalHist = new TH1F("SignalHist","",30,200,2000);
  style.InitHist(SignalHist,"m_{12} [GeV]","a.u.",kGreen+1,0);
  SignalHist -> FillRandom("sigfunc",100000);
  SignalHist -> Draw("E0SAME");

  TH1F* SignalHistPlusSR = new TH1F("SignalHistPlusSR","",30,200,2000);
  style.InitHist(SignalHistPlusSR,"m_{12} [GeV]","a.u.",kCyan);
  SignalHistPlusSR -> Add(SignalRegionHist);
  SignalHistPlusSR -> Add(SignalHist);
  SignalHistPlusSR -> Draw("E0SAME");

  /*  for (int i = 1; i < 31; i++){
    cout << "SN, bin " << i << ": " << SuperNovoHist->GetBinContent(i) << " entries" << endl;
    cout << "SR, bin " << i << ": " << SignalRegionHist->GetBinContent(i) << " entries" <<endl;
    cout << "SRsig, bin " << i << ": " << SignalHistPlusSR->GetBinContent(i) << " entries" <<endl;
  }
  */
  TLegend* leg = new TLegend(0.44,0.70,0.84,0.90);
  style.SetLegendStyle(leg);
  leg -> AddEntry(SuperNovoHist,"SuperNovosibirsk, 'CR'","P");
  leg -> AddEntry(SignalRegionHist,"SN * transfer, 'SR, no sig'","P");
  leg -> AddEntry(SignalHist,"Gaussian signal","P");
  leg -> AddEntry(SignalHistPlusSR,"SR + signal","P");
  leg -> Draw("SAME");

  TFile* outfile = new TFile("InputForCombineSigCRSR.root","RECREATE");
  SuperNovoHist -> Write();
  SignalRegionHist -> Write();
  SignalHist -> Write();
  SignalHistPlusSR -> Write();
  outfile -> Close();

  can -> SaveAs("Outputdata/CombineDummy/sig-bg-sr_newappr-60GeV_smallerSig_070120_1145.pdf");
  can -> SaveAs("Outputdata/CombineDummy/sig-bg-sr_newappr-60GeV_smallerSig_070120_1145.root");

}
