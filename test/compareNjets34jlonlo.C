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

void compareNjets34jlonlo(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  vector<string> masspoints = {"350","600","1200"};

  for (unsigned int i=0; i<masspoints.size(); i++){//before cuts
    TFile* f3jlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[i]+"-deep-SR-3j.root").c_str(),"READ");
    TFile* f3jnlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[i]+"-NLO-deep-SR-3j.root").c_str(),"READ");
    TFile* f4jlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[i]+"-deep-SR.root").c_str(),"READ");
    TFile* f4jnlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[i]+"-NLO-deep-SR.root").c_str(),"READ");

    TH1F* h3jlo = (TH1F*)f3jlo->Get("n_ptmin20");
    TH1F* h3jnlo = (TH1F*)f3jnlo->Get("n_ptmin20");
    TH1F* h4jlo = (TH1F*)f4jlo->Get("n_ptmin20");
    TH1F* h4jnlo = (TH1F*)f4jnlo->Get("n_ptmin20");

    TCanvas* can = style.MakeCanvas("can","can",700,700);
    can -> SetLogy();

    //TGaxis::SetMaxDigits(3);

    h3jlo -> SetLineColor(kRed);
    h3jlo -> SetLineWidth(2);
    h3jlo -> GetXaxis() -> SetTitle("Number of jets with p_{T} > 20 GeV");
    h3jlo -> GetXaxis() -> SetTitleOffset(1.1);
    h3jlo -> GetXaxis() -> SetRangeUser(0,20);
    h3jlo -> GetYaxis() -> SetTitle("Number of events");
    h3jlo -> GetYaxis() -> SetTitleOffset(1.1);
    h3jlo -> GetYaxis() -> SetRangeUser(1,1000000);
    h3jlo -> Draw();
    h3jnlo -> SetLineColor(kMagenta);
    h3jnlo -> SetLineWidth(2);
    h3jnlo -> Draw("SAME");
    h4jlo -> SetLineColor(kBlue);
    h4jlo -> SetLineWidth(2);
    h4jlo -> Draw("SAME");
    h4jnlo -> SetLineColor(kCyan);
    h4jnlo -> SetLineWidth(2);
    h4jnlo -> Draw("SAME");

    TLegend* leg = new TLegend(0.71,0.7,0.91,0.87);
    style.SetLegendStyle(leg);
    leg -> AddEntry(h3jlo,"3 jets, LO","L");
    leg -> AddEntry(h3jnlo,"3 jets, NLO","L");
    leg -> AddEntry(h4jlo,"4 jets, LO","L");
    leg -> AddEntry(h4jnlo,"4 jets, NLO","L");
    leg -> Draw("SAME");

    can->SaveAs(("Outputdata_LO_NLO/njets-bc-lo-nlo"+masspoints[i]+".pdf").c_str());

    float norm3jlo = h3jlo -> Integral();
    float norm3jnlo = h3jnlo -> Integral();
    float norm4jlo = h4jlo -> Integral();
    float norm4jnlo = h4jnlo -> Integral();

    h3jlo -> Scale(1/norm3jlo);
    h3jnlo -> Scale(1/norm3jnlo);
    h4jlo -> Scale(1/norm4jlo);
    h4jnlo -> Scale(1/norm4jnlo);

    can -> Update();

    can->SaveAs(("Outputdata_LO_NLO/njets-bc-lo-nlo"+masspoints[i]+"_norm.pdf").c_str());
  }


  for (unsigned int j=0; j<masspoints.size(); j++){//after cuts
    TFile* f3jlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[j]+"-deep-SR-3j.root").c_str(),"READ");
    TFile* f3jnlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[j]+"-NLO-deep-SR-3j.root").c_str(),"READ");
    TFile* f4jlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[j]+"-deep-SR.root").c_str(),"READ");
    TFile* f4jnlo = new TFile(("rootfiles/mcsig/mc-sig-"+masspoints[j]+"-NLO-deep-SR.root").c_str(),"READ");

    TH1F* h3jlo = (TH1F*)f3jlo->Get("n_ptmin20_csv");
    TH1F* h3jnlo = (TH1F*)f3jnlo->Get("n_ptmin20_csv");
    TH1F* h4jlo = (TH1F*)f4jlo->Get("n_ptmin20_csv");
    TH1F* h4jnlo = (TH1F*)f4jnlo->Get("n_ptmin20_csv");

    TCanvas* can = style.MakeCanvas("can","can",700,700);
    can -> SetLogy();
    //TGaxis::SetMaxDigits(3);

    h3jlo -> SetLineColor(kRed);
    h3jlo -> SetLineWidth(2);
    h3jlo -> GetXaxis() -> SetTitle("Number of jets with p_{T} > 20 GeV (after cuts)");
    h3jlo -> GetXaxis() -> SetTitleOffset(1.1);
    h3jlo -> GetXaxis() -> SetRangeUser(0,20);
    h3jlo -> GetYaxis() -> SetTitle("Number of events");
    h3jlo -> GetYaxis() -> SetTitleOffset(1.1);
    h3jlo -> GetYaxis() -> SetRangeUser(1,1000000);
    h3jlo -> Draw();
    h3jnlo -> SetLineColor(kMagenta);
    h3jnlo -> SetLineWidth(2);
    h3jnlo -> Draw("SAME");
    h4jlo -> SetLineColor(kBlue);
    h4jlo -> SetLineWidth(2);
    h4jlo -> Draw("SAME");
    h4jnlo -> SetLineColor(kCyan);
    h4jnlo -> SetLineWidth(2);
    h4jnlo -> Draw("SAME");

    TLegend* leg = new TLegend(0.71,0.7,0.91,0.87);
    style.SetLegendStyle(leg);
    leg -> AddEntry(h3jlo,"3 jets, LO","L");
    leg -> AddEntry(h3jnlo,"3 jets, NLO","L");
    leg -> AddEntry(h4jlo,"4 jets, LO","L");
    leg -> AddEntry(h4jnlo,"4 jets, NLO","L");
    leg -> Draw("SAME");

    can->SaveAs(("Outputdata_LO_NLO/njets-bc-lo-nlo"+masspoints[j]+"_csv.pdf").c_str());

    float norm3jlo = h3jlo -> Integral();
    float norm3jnlo = h3jnlo -> Integral();
    float norm4jlo = h4jlo -> Integral();
    float norm4jnlo = h4jnlo -> Integral();
    
    h3jlo -> Scale(1/norm3jlo);
    h3jnlo -> Scale(1/norm3jnlo);
    h4jlo -> Scale(1/norm4jlo);
    h4jnlo -> Scale(1/norm4jnlo);

    can -> Update();

    can->SaveAs(("Outputdata_LO_NLO/njets-bc-lo-nlo"+masspoints[j]+"_csv_norm.pdf").c_str());
  }  

}
