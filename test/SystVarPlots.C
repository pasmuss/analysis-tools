#include "tdrstyle.C"
#include "HbbStylesNew.cc"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

#include "TH1.h"
#include "TH2.h"
#include "TLatex.h"
#include "TGaxis.h"
#include "TStyle.h"

using namespace std;

void SystVarPlots(){

  TH1::SetDefaultSumw2();

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  //vector<string> subranges = {"SR1","SR2","SR3","SR4"};
  vector<string> subranges = {"SR2"};
  vector<string> masses;
  //vector<string> variations = {"up","down"};
  vector<string> variations = {"plus3","minus3"};
  //vector<string> uncertainties = {"JER","JES"};
  vector<string> uncertainties = {"JES"};

  string maindir = "Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rootfiles_Nov19-20_inclSystVariations/";
  string histname = "";
  string entries = "";
  int rebin = 1;

  //loop over subranges
  for (unsigned int sr = 0; sr < subranges.size(); sr++){
    string subrange = subranges[sr];
    if (subrange == "SR1"){
      masses = {"300","350","400"};
      histname = "m12_SR1_1GeV";
      entries = "10";
      rebin = 10;
    }
    else if (subrange == "SR2"){
      //masses = {"400","450","500","600","700"};
      masses = {"500"};
      histname = "m12_SR2_1GeV";
      entries = "15";
      rebin = 15;
    }
    else if (subrange == "SR3"){
      masses = {"700","800","900","1000"};
      histname = "m12_SR3_5GeV";
      entries = "20";
      rebin = 4;
    }
    else{
      masses = {"1000","1200","1400","1600"};
      //masses = {"1000"};
      histname = "m12_SR4_10GeV";
      entries = "20";
      rebin = 2;
    }
  //loop over masses
    for (unsigned int masspoint = 0; masspoint < masses.size(); masspoint++){
      string mass = masses[masspoint];
      double xlow = 0.7, xhigh = 0.9, ylow = 0.6, yhigh = 0.8;
      if (subrange == "SR1" && mass == "400"){
        xlow = 0.2; xhigh = 0.4;
      }
      if (subrange == "SR2" && (mass == "600" || mass == "700")){
	xlow = 0.2; xhigh = 0.4;
      }
      if (subrange == "SR3" && (mass == "900" || mass == "1000")){
	xlow = 0.2; xhigh = 0.4;
      }
      if (subrange == "SR4" && (mass == "1400" || mass == "1600")){
	xlow = 0.2; xhigh = 0.4;
      }
            
      //loop over uncertainties
      for (unsigned int uncert = 0; uncert < uncertainties.size(); uncert++){
	string uncertainty = uncertainties[uncert];

	cout << (maindir + "central/mcsig/mc-sig-" + mass + "-NLO-deep-SR-3j.root/" + histname).c_str() << endl;

	string description = "Jet Energy Resolution";
	if (uncertainty == "JES") description = "Jet Energy Scale";

	TCanvas* can = style.MakeCanvas("can","",700,800);
	gStyle -> SetLineWidth(1);
	double ydiv = 0.25;
	TPad* pad_bot = new TPad("pad_bot","",0.0,0.0,1.0,ydiv);
	pad_bot -> SetLeftMargin(0.15);
	pad_bot -> SetBottomMargin(0.3);
	pad_bot -> Draw();
	TPad* pad_top = new TPad("pad_top","",0.0,ydiv,1.0,1.0);
	pad_top -> Draw();
	pad_top -> cd();
	pad_top -> SetRightMargin(0.05);
	pad_top -> SetLeftMargin(0.15);
	pad_top -> SetBottomMargin(0.02);
	TFile* f_central = new TFile( (maindir + "central/mcsig/mc-sig-" + mass + "-NLO-deep-SR-3j.root").c_str() ,"READ");
	TH1F* h_central = (TH1F*)f_central->Get(histname.c_str());
	style.InitHist(h_central,"m_{12} [GeV]",("Entries / " + entries + " GeV").c_str(),kBlack,0);
	h_central -> Rebin(rebin);
	h_central -> SetLineWidth(1);
	h_central -> SetFillColor(kRed-10);
	h_central -> SetFillStyle(1001);
	int histmax = h_central -> GetMaximum();
	h_central -> GetYaxis() -> SetRangeUser(0,histmax*1.1);
	h_central -> Draw("hist");
	double largetitle = 0.045;
	double largelabel = 0.04;
	h_central -> GetYaxis() -> SetTitleOffset(1.7);
	h_central -> GetYaxis() -> SetTitleSize(largetitle);
	h_central -> GetXaxis() -> SetTitle();
	h_central -> GetXaxis() -> SetLabelSize(0);
	TLegend* leg = new TLegend(xlow,ylow,xhigh,yhigh);
	style.SetLegendStyle(leg);
	leg -> AddEntry(h_central, "central", "F");
	TPaveText* pave = new TPaveText(xlow,yhigh,xhigh,yhigh+0.1,"ndc");
	pave -> AddText(("m_{A/H} = " + mass + " GeV").c_str());
	pave -> AddText(description.c_str());
	pave -> SetTextFont(12);
	pave -> SetFillColor(0);
	pave -> SetTextSize(leg->GetTextSize());
	pave -> SetTextAlign(12);
	
	//loop over variations
	for (unsigned int var = 0; var < variations.size(); var++){
	  pad_top -> cd();
	  string variation = variations[var];
	  int color;
	  if (variation == "up" || variation == "plus3") color = kBlue;
	  else color = kRed;
	  cout << (maindir + uncertainty + variation + "/mcsig/mc-sig-" + mass + "-NLO-deep-SR-3j.root/" + histname).c_str() << endl;
	  TFile* f_var = new TFile( (maindir + uncertainty + variation + "/mcsig/mc-sig-" + mass + "-NLO-deep-SR-3j.root").c_str() ,"READ");
	  TH1F* h_var = (TH1F*)f_var->Get(histname.c_str());
	  style.InitHist(h_var,"m_{12} [GeV]",("Entries / " + entries + " GeV").c_str(),color,0);
	  h_var -> Rebin(rebin);
	  h_var -> SetMarkerSize(1);
	  h_var -> SetLineColor(kBlack);
	  h_var -> SetLineWidth(1);
	  h_var -> Draw("same");
	  leg -> AddEntry(h_var,(uncertainty + " " + variation).c_str(),"LP");
	  TH1F* var_copy = (TH1F*)h_var -> Clone("cen_copy");
	  var_copy -> Divide(h_central);
	  pad_bot -> cd();
	  double titlesize = largetitle*((1-ydiv)/ydiv);
	  double labelsize = largelabel*((1-ydiv)/ydiv);
	  double ticksize = (h_central -> GetXaxis() -> GetTickLength()) * ((1-ydiv)/ydiv);
	  var_copy -> SetMarkerColor(color);
	  var_copy -> SetMarkerSize(1);
	  var_copy -> GetYaxis() -> SetRangeUser(0.5,1.5);
	  var_copy -> GetYaxis() -> SetNdivisions(5);
	  var_copy -> GetYaxis() -> SetLabelSize(labelsize);
	  var_copy -> GetYaxis() -> SetTitle("#frac{Down(Up)}{Central}");
	  var_copy -> GetYaxis() -> SetTickSize(0.5*ticksize);
	  var_copy -> GetYaxis() -> CenterTitle();
	  var_copy -> GetYaxis() -> SetTitleSize(titlesize);
	  var_copy -> GetYaxis() -> SetTitleOffset(0.5);
	  var_copy -> GetXaxis() -> SetLabelSize(labelsize);
	  var_copy -> GetXaxis() -> SetTitle("m_{12} [GeV]");
	  var_copy -> GetXaxis() -> SetTitleSize(titlesize);
	  var_copy -> GetXaxis() -> SetTitleOffset(1.1);
	  var_copy -> GetXaxis() -> SetTickSize(ticksize);
	  if (var == 0) var_copy -> Draw();
	  else var_copy -> Draw("SAME");
	  pad_bot -> Update();
	  TLine* gridline = new TLine(pad_bot->GetUxmin(), 1.0, pad_bot->GetUxmax(), 1.0);
	  gridline -> SetLineStyle(7);
	  gridline -> Draw("SAME");
	}//variations

	pad_top -> cd();
	pave -> Draw("SAME");
	leg -> Draw("SAME");
	can -> Update();
	can -> SaveAs(("OutputSystVar/Variation_" + uncertainty + "_" + mass + "_" + subrange + "_3sigma_Jan06-21.root").c_str());
	can -> SaveAs(("OutputSystVar/Variation_" + uncertainty + "_" + mass + "_" + subrange + "_3sigma_Jan06-21.pdf").c_str());

      }//uncertainties
    }//masses
  }//subranges
}
