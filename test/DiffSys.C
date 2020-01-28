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

int DiffSys( )
{
  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);
  setTDRStyle();

  TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms

  std::string var = "m12_aac";
  std::string varunit = "GeV";
  std::string xtitle = "m_{A/H} [GeV]" ;
  std::string ytitle = "Events [a.u.]" ;

  std::string nospace = "";

  bool corrBefKin = false;
  std::vector<string> systs = {"JER","JES","PU","SFbtag","onlSFbtag", "jet_trigeff"};
  std::vector<string> systs_name = {"Jet Energy Resolution","Jet Energy Scale","Pile-up","Offline b-tag eff.","Online b-tag eff.", "Jet trigger eff."};

  std::vector<string> mps = {"400","900","1200"};
  
  float xlow  = 100;
  float xhigh = 3000;
  float ylow  = 0;
  const float yhigh = 600;
  float yRlow  = 0.5;
  float yRhigh = 1.5;

  float lumi = 36.0; // all 2017 C to F  

  for ( auto & mp : mps )
    {
      int n =0; //sys counter
      for ( auto & sys : systs )
	{
	  string nuis = systs_name[n];

	  TFile * f = new TFile( ("Configs_diffBTags_allmedium/Syst_Variations/MergedFiles/mc-sig-"+mp+"-NLO-deep-SR-3j.root").c_str(),"READ");

	  cout << ("Configs_diffBTags_allmedium/Syst_Variations/MergedFiles/mc-sig-"+mp+"-NLO-deep-SR-3j.root").c_str() << endl;

	  TH1F * hist_central = hist_central = (TH1F*)f->Get(var.c_str());
	  TH1F * hist_up      = (TH1F*)f->Get((var+"_"+sys+"_up").c_str());
	  TH1F * hist_down    = (TH1F*)f->Get((var+"_"+sys+"_down").c_str());
	  cout << var.c_str() << endl;

	  int sr1_low = hist_central->FindBin(200);
	  int sr1_high = hist_central->FindBin(3000);

	  double central_int = hist_central->Integral(sr1_low, sr1_high);
	  double up_int      = hist_up     ->Integral(sr1_low, sr1_high);
	  double down_int    = hist_down   ->Integral(sr1_low, sr1_high);

	  hist_down->Rebin(2); hist_central->Rebin(2); hist_up->Rebin(2);
	  if ( mp =="130" ) {hist_down->Rebin(2); hist_central->Rebin(2); hist_up->Rebin(2);}

	  hist_central -> GetXaxis() -> SetRangeUser(xlow,xhigh);
	  hist_central -> GetXaxis() -> SetTitle(( xtitle ).c_str());
	  hist_central -> GetYaxis() -> SetTitle(( ytitle ).c_str());

	  hist_central -> GetYaxis() -> SetRangeUser(0,hist_down->GetMaximum()*1.65);
	  hist_central -> GetXaxis() ->SetLabelSize(0);
	  hist_central -> GetYaxis() ->SetLabelSize(0.05);
	  hist_central -> GetYaxis() ->SetTitleSize(0.07);
	  hist_central -> GetYaxis() ->SetTitleOffset(1.0);

	  TCanvas* c1 = style.MakeCanvas("c1","",700,700);

	  TPad* pad1;
	  pad1 = new TPad("pad1","",0,0.4,1,1);
	  pad1->Range(-69.62637,-87.99509,871.2674,2467.689);
	  pad1->SetFillColor(0);
	  pad1->SetBorderMode(0);
	  pad1->SetBorderSize(2);
	  pad1->SetTickx(1);
	  pad1->SetTicky(1);
	  pad1->SetLeftMargin(0.1590258);
	  pad1->SetRightMargin(0.05014327);
	  pad1->SetTopMargin(0.0499002);
	  pad1->SetBottomMargin(0.03443114);
	  pad1->SetFrameFillStyle(0);
	  pad1->SetFrameBorderMode(0);
	  pad1->SetFrameFillStyle(0);
	  pad1->SetFrameBorderMode(0);
	  pad1->Draw();
	  pad1->cd();

	  hist_down->SetLineColor(2); hist_up->SetLineColor(4); hist_central->SetLineColor(1);
	  hist_central->SetFillColor(kRed-10);
	  hist_down->SetMarkerColor(2); hist_up->SetMarkerColor(4);
	  hist_down->SetMarkerStyle(20); hist_up->SetMarkerStyle(20); hist_central->SetMarkerStyle(20);

	  hist_central->Draw("HIST "); hist_up->Draw("same"); hist_down->Draw("same");

	  if ( sys== "SFbtag" ) sys="SFb";

	  string mass = "m_{A/H} = "+ mp + "GeV";

	  TLegend *leg = new TLegend(0.6074499,0.4236527,0.9297994,0.8877246,NULL,"brNDC");
    
	  leg -> SetHeader( ( "#it{#splitline{"+mass+"}{"+nuis+"}} " ).c_str(), "");
	  leg -> AddEntry(hist_central,"Central","f");
	  leg -> AddEntry(hist_down,( "-2"+nospace+"#sigma variation ").c_str() ,"lp");
	  leg -> AddEntry(hist_up,  ( "+2"+nospace+"#sigma variation ").c_str() ,"lp");
	  leg -> Draw("SAME");
   
	  c1->cd();
   
	  TPad *pad2 = new TPad("pad2","",0,0.0,1,0.4);
	  pad2->SetTopMargin(0.1);
	  pad2->SetBottomMargin(0.33);
	  pad2->SetLeftMargin(pad1->GetLeftMargin());
	  pad2->SetRightMargin(pad1->GetRightMargin());
	  pad2->Draw();
	  pad2->cd();

	  TH1F *ratio_up = (TH1F*)   hist_up->Clone();
	  TH1F *ratio_down = (TH1F*) hist_down->Clone();

	  ratio_up->Divide(hist_central);
	  ratio_down->Divide(hist_central);
  
	  ratio_up -> GetYaxis() -> SetRangeUser(yRlow,yRhigh);
	  ratio_up -> GetXaxis() -> SetTitle(( xtitle ).c_str());
	  ratio_up -> GetYaxis()->SetLabelSize(0.07);
	  ratio_up -> GetXaxis()->SetLabelSize(0.07);
	  ratio_up -> GetXaxis() -> SetTitleOffset(1.);
	  ratio_up -> GetYaxis() -> SetTitleOffset(0.6);
	  ratio_up -> GetYaxis() -> SetTitle("#frac{Down(Up)}{Central}");
	  ratio_up -> GetXaxis() -> SetTitle("M_{12} [GeV]");
	  ratio_up  -> GetXaxis() ->SetTitleSize(0.12);
	  ratio_up  -> GetYaxis() ->SetTitleSize(0.10);

	  ratio_up -> GetXaxis() -> SetRangeUser(xlow,xhigh);
	  ratio_down -> GetXaxis() -> SetRangeUser(xlow,xhigh);
  
	  ratio_up->Draw("HIST PE ");
	  ratio_down->Draw("HIST PE same");

	  //  CMSPrelim( Form("%.1f fb^{-1} (13 TeV)", lumi ) , 0.15, 0.78)

	  cout << mp << "\t " << sys << " \t" << 1+((((up_int/central_int + central_int/down_int)*0.5)-1)*0.5)  << endl;

	  if ( sys == "onlSFbtag") sys = "onlSFb";
	  if ( sys == "onlSFb") sys = "onlSFbtag";

	  c1 -> SaveAs(("Outputdata/SystVar/Compsys_"+ sys +"_"+mp+ "_"+var+".png").c_str());
	  c1 -> SaveAs(("Outputdata/SystVar/Compsys_"+ sys +"_"+mp+ "_"+var+".root").c_str());
	  c1 -> SaveAs(("Outputdata/SystVar/Compsys_"+ sys +"_"+mp+ "_"+var+".pdf").c_str());
	  ++n;	
	}
    }
  return 0;
}

