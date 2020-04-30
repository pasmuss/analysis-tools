#include "TH1.h"
#include "TGaxis.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>

#include "HbbStylesNew.cc"
#include "tdrstyle.C"

using namespace std;

void PlotPulls(){

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);

  /*  vector<string> strengths = {"0p0","0p05","0p1","0p25","0p5","1p0","5p0"};

  for (unsigned int s = 0; s < strengths.size(); s++){
    string strength = strengths[s];
    cout << strength << endl;

    //
    // Create Canvases and histograms for pulls
    //

    TCanvas* c_0p0 = style.MakeCanvas("c_0p0",strength.c_str(),700,700);
    TH1F* h_0p0 = new TH1F("h_0p0",strength.c_str(),100,-5,5);
    style.InitHist(h_0p0,"","Counts",kRed,0);

    //
    // Read input lists with pulls and fill/draw histogram
    //

    ifstream f_in_0p0;
    f_in_0p0.open(("pulls_"+strength+".txt").c_str());
    while (1){
      float tmp= -999.999;
      f_in_0p0 >> tmp;
      if (!f_in_0p0.good()) break;
      h_0p0 -> Fill(tmp);
    }

    h_0p0->Draw();

    //
    // Fit hist with Gaussian
    //

    h_0p0->Fit("gaus");

    //
    // Saving
    //

    c_0p0 -> SaveAs(("Plots/Pulls/Pulls_"+strength+".pdf").c_str());
    c_0p0 -> SaveAs(("Plots/Pulls/Pulls_"+strength+".root").c_str());

  }
*/
  TCanvas* c_all = style.MakeCanvas("c_all","all",700,700);
  TH1F* h_all = new TH1F("h_all","",141,-1.025,6.025);
  style.InitHist(h_all,"r_{exp}","r_{extr}",kRed,0);
  h_all -> SetBinContent(21,0.008); h_all -> SetBinError(21,0.074);
  h_all -> SetBinContent(22,0.057); h_all -> SetBinError(22,0.074);
  h_all -> SetBinContent(23,0.108); h_all -> SetBinError(23,0.073);
  h_all -> SetBinContent(26,0.257); h_all -> SetBinError(26,0.073);
  h_all -> SetBinContent(31,0.507); h_all -> SetBinError(31,0.074);
  h_all -> SetBinContent(41,1.013); h_all -> SetBinError(41,0.078);
  h_all -> SetBinContent(121,5.004); h_all -> SetBinError(121,0.094);
  h_all -> SetMarkerSize(1);
  h_all -> Draw();

  h_all -> Fit("pol1");

  c_all -> SaveAs("Plots/Pulls/r_extr.pdf");
  c_all -> SaveAs("Plots/Pulls/r_extr.root");
}
