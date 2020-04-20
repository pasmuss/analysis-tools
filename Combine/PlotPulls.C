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

  vector<string> strengths = {"0p0","0p05","0p1","0p25","0p5","1p0","5p0"};

  for (unsigned int s = 0; s < strengths.size(); s++){
    string strength = strengths[s];
    cout << strength << endl;

    //
    // Create Canvases and histograms for pulls
    //

    TCanvas* c_0p0 = style.MakeCanvas("c_0p0",strength.c_str(),700,700);
    TH1F* h_0p0 = new TH1F("h_0p0",strength.c_str(),100,-5,5);
    style.InitHist(h_0p0,"Pull","Counts",kBlue,0);

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
}
