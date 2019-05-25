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

int scaleMCbg(string var_, int rebin_ , string region_, double xlow_, double xhigh_, double ylow_, double yhigh_, bool logy_, bool threejets_) {

  cout << " " << endl;
  cout << "Input to be provided:" << endl;
  cout << "(str)variable ('pt_n', 'eta_n' or 'm12' with n=(0,1,2,3))," << endl;
  cout << "(int)rebinning factor," << endl;
  cout << "(str)region ('CR'/'SR')," << endl;
  cout << "(double)x-axis-beginning," << endl;
  cout << "(double)x-axis-end," << endl;
  cout << "(double)y-axis-beginning," << endl;
  cout << "(double)y-axis-end," << endl;
  cout << "(bool)logy?," << endl;
  cout << "(bool)3jets?" << endl;

  string xtitleEnr, xtitleGeF, xtitleGes, ytitle = "Did you forget me?";
  long binning = 0.0;

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  cout << " " << endl;
  cout << "Checking variable consistency..." << endl;
  string var = var_;
  if (var == "pt_0" || var == "pt_0_csv"){
    cout << "pT of first jet selected" << endl;
    binning = rebin_*10.0;
    xtitleEnr = "p_{T}, 1^{st} jet [GeV], bEnriched";
    xtitleGeF = "p_{T}, 1^{st} jet [GeV], bGenFilter";
    xtitleGes = "p_{T}, 1^{st} jet [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV [a.u.]").c_str();
  }
  else if (var == "pt_1" || var == "pt_1_csv"){
    cout << "pT of second jet selected"<< endl;
    binning = rebin_*10.0;
    xtitleEnr = "p_{T}, 2^{nd} jet [GeV], bEnriched";
    xtitleGeF = "p_{T}, 2^{nd} jet [GeV], bGenFilter";
    xtitleGes = "p_{T}, 2^{nd} jet [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV [a.u.]").c_str();
  }
  else if (var == "pt_2" || var == "pt_2_csv"){
    cout << "pT of third jet selected"<< endl;
    binning = rebin_*10.0;
    xtitleEnr = "p_{T}, 3^{rd} jet [GeV], bEnriched";
    xtitleGeF = "p_{T}, 3^{rd} jet [GeV], bGenFilter";
    xtitleGes = "p_{T}, 3^{rd} jet [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV [a.u.]").c_str();
  }
  else if (var == "pt_3" || var == "pt_3_csv"){
    cout << "pT of fourth jet selected"<< endl;
    binning = rebin_*10.0;
    xtitleEnr = "p_{T}, 4^{th} jet [GeV], bEnriched";
    xtitleGeF = "p_{T}, 4^{th} jet [GeV], bGenFilter";
    xtitleGes = "p_{T}, 4^{th} jet [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV [a.u.]").c_str();
  }
  else if (var == "eta_0" || var == "eta_0_csv"){
    cout << "eta of first jet selected" << endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 1^{st} jet, bEnriched";
    xtitleGeF = "#eta, 1^{st} jet, bGenFilter";
    xtitleGes = "#eta, 1^{st} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if (var == "eta_1" || var == "eta_1_csv"){
    cout << "eta of second jet selected"<< endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 2^{nd} jet, bEnriched";
    xtitleGeF = "#eta, 2^{nd} jet, bGenFilter";
    xtitleGes = "#eta, 2^{nd} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if (var == "eta_2" || var == "eta_2_csv"){
    cout << "eta of third jet selected"<< endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 3^{rd} jet, bEnriched";
    xtitleGeF = "#eta, 3^{rd} jet, bGenFilter";
    xtitleGes = "#eta, 3^{rd} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if (var == "eta_3" || var == "eta_3_csv"){
    cout << "eta of fourth jet selected"<< endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 4^{th} jet, bEnriched";
    xtitleGeF = "#eta, 4^{th} jet, bGenFilter";
    xtitleGes = "#eta, 4^{th} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if (var == "m12" || var == "m12_csv"){
    cout << "m12 selected" << endl;
    binning = rebin_*20.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV [a.u.]").c_str();
  }
  else{
    cout << "No known variable selected. Please select 'pt_n', 'eta_n' or 'm12' with n=(0,1,2,3). For the quantities after cuts, please add '_csv' to the string." << endl; 
    return -1;
  }
  cout << "Variable check successful. Bin width: " << binning << endl;

  cout << " " << endl;
  cout << "Checking region consistency..." << endl;
  string reg = region_;
  if (! (reg == "CR" || reg == "SR")){
    cout << "Please select either 'CR' or 'SR' as region!" << endl; 
    return -1;
  }
  cout << "Region check successful." << endl;

  string varname;
  if ( var_ == "pt_0" || var_ == "pt_0_csv") varname = "p_{T}, 1^{st} jet";
  else if ( var_ == "pt_1" || var_ == "pt_1_csv") varname = "p_{T}, 2^{nd} jet";
  else if ( var_ == "pt_2" || var_ == "pt_2_csv") varname = "p_{T}, 3^{rd} jet";
  else if ( var_ == "eta_0" || var_ == "eta_0_csv") varname = "#eta, 1^{st} jet";
  else if ( var_ == "eta_1" || var_ == "eta_1_csv") varname = "#eta, 2^{nd} jet";
  else if ( var_ == "eta_2" || var_ == "eta_2_csv") varname = "#eta, 3^{rd} jet";
  else if ( var_ == "phi_0" || var_ == "phi_0_csv") varname = "#phi, 1^{st} jet";
  else if ( var_ == "phi_1" || var_ == "phi_1_csv") varname = "#phi, 2^{nd} jet";
  else if ( var_ == "phi_2" || var_ == "phi_2_csv") varname = "#phi, 3^{rd} jet";
  else if ( var_ == "m12" || var_ == "m12_csv") varname = "m_{12}";
  else varname = var_;

  vector<string> pthatbins = {"200to300","300to500","500to700","700to1000","1000to1500", "1500to2000", "2000toInf"};
  vector<double> sfvaluesEnr = {291.08  ,  168.74  ,   26.64  ,   11.70   ,    6.26    ,     2.19    ,    0.08    };
  vector<double> sfvaluesGeF = {645.81  ,  245.44  ,   19.57  ,   19.40   ,    5.41    ,     3.27    ,    0.75    };//for bGenFilter

  map<string, double> scalefactorsEnr;
  map<string, TFile*> filesEnr;
  map<string, TH1F*> histogramsEnr;

  map<string, double> scalefactorsGeF;
  map<string, TFile*> filesGeF;
  map<string, TH1F*> histogramsGeF;

  for (unsigned int i = 0; i < pthatbins.size(); i++){
    scalefactorsEnr[pthatbins[i]] = sfvaluesEnr[i];
    scalefactorsGeF[pthatbins[i]] = sfvaluesGeF[i];
    filesEnr[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_dfl_new-QCD-MC_pTcorrectionsToBeginning/mcbg/mc-bg-HT-" + pthatbins[i] + "-bEnriched-" + region_ + ".root").c_str(),"READ");
    filesGeF[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_dfl_new-QCD-MC_pTcorrectionsToBeginning/mcbg/mc-bg-HT-" + pthatbins[i] + "-bGenFilter-" + region_ + ".root").c_str(),"READ");
    if (threejets_){
      filesEnr[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_dfl_new-QCD-MC_pTcorrectionsToBeginning/mcbg/mc-bg-HT-" + pthatbins[i] + "-bEnriched-" + region_ + "-3j.root").c_str(),"READ");
      filesGeF[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_dfl_new-QCD-MC_pTcorrectionsToBeginning/mcbg/mc-bg-HT-" + pthatbins[i] + "-bGenFilter-" + region_ + "-3j.root").c_str(),"READ");
    }
    histogramsEnr[pthatbins[i]] = (TH1F*)filesEnr[pthatbins[i]] -> Get(var_.c_str());
    histogramsGeF[pthatbins[i]] = (TH1F*)filesGeF[pthatbins[i]] -> Get(var_.c_str());
  }

  double nbinsx = histogramsEnr[pthatbins[0]] -> GetNbinsX();
  double xreflow = histogramsEnr[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( 1 );
  double xrefhigh = histogramsEnr[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( histogramsEnr[pthatbins[0]] -> GetNbinsX()+1 );

  TCanvas* EnrCan = style.MakeCanvas("EnrCan", "", 700,700);
  TCanvas* GeFCan = style.MakeCanvas("GeFCan", "", 700,700);
  TCanvas* GesCan = style.MakeCanvas("GesCan", "", 700,700);
  if (logy_){
    EnrCan -> SetLogy();
    GeFCan -> SetLogy();
    GesCan -> SetLogy();
  }
  TH1F* hist_output_enr = new TH1F("hist_output_enr", "", nbinsx, xreflow, xrefhigh);
  TH1F* hist_output_gef = new TH1F("hist_output_gef", "", nbinsx, xreflow, xrefhigh);
  TH1F* hist_output_ges = new TH1F("hist_output_ges", "", nbinsx, xreflow, xrefhigh);
  style.InitHist(hist_output_enr,xtitleEnr.c_str(),ytitle.c_str(),kBlue,0);
  style.InitHist(hist_output_gef,xtitleGeF.c_str(),ytitle.c_str(),kRed,0);
  style.InitHist(hist_output_ges,xtitleGeF.c_str(),ytitle.c_str(),kGreen,0);
  hist_output_enr -> SetMarkerSize(1);
  hist_output_gef -> SetMarkerSize(1);
  hist_output_ges -> SetMarkerSize(1);

  for (auto const &hist1 : histogramsEnr){
    hist_output_enr -> Add(histogramsEnr[hist1.first] , scalefactorsEnr[hist1.first]);
  }

  for (auto const &hist2 : histogramsGeF){
    hist_output_gef -> Add(histogramsGeF[hist2.first] , scalefactorsGeF[hist2.first]);
  }

  hist_output_enr -> Rebin(rebin_);
  hist_output_enr -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output_enr -> GetXaxis() -> SetTitle(xtitleEnr.c_str());
  hist_output_enr -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output_enr -> GetYaxis() -> SetTitle(ytitle.c_str());
  hist_output_enr -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output_enr -> GetYaxis() -> SetNdivisions(505);

  TLegend* legEnr = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legEnr);
  legEnr -> AddEntry(hist_output_enr,varname.c_str(),"LP");

  hist_output_gef -> Rebin(rebin_);
  hist_output_gef -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output_gef -> GetXaxis() -> SetTitle(xtitleGeF.c_str());
  hist_output_gef -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output_gef -> GetYaxis() -> SetTitle(ytitle.c_str());
  hist_output_gef -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output_gef -> GetYaxis() -> SetNdivisions(505);

  TLegend* legGef = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legGef);
  legGef -> AddEntry(hist_output_gef,varname.c_str(),"LP");

  hist_output_ges -> Rebin(rebin_);
  hist_output_ges -> Add(hist_output_enr);
  hist_output_ges -> Add(hist_output_gef);
  hist_output_ges -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output_ges -> GetXaxis() -> SetTitle(xtitleGes.c_str());
  hist_output_ges -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output_ges -> GetYaxis() -> SetTitle(ytitle.c_str());
  hist_output_ges -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output_ges -> GetYaxis() -> SetNdivisions(505);

  TLegend* legGes = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legGes);
  legGes -> AddEntry(hist_output_ges,varname.c_str(),"LP");

  EnrCan -> cd();
  hist_output_enr -> Draw();
  legEnr -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.18, 0.76);
  EnrCan -> Update();

  GeFCan -> cd();
  hist_output_gef -> Draw();
  legGef -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.18, 0.76);
  GeFCan -> Update();

  GesCan -> cd();
  hist_output_ges -> Draw();
  legGes -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.18, 0.76);
  GesCan -> Update();

  if (threejets_){
    EnrCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bEnriched-3j.pdf").c_str() );
    EnrCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bEnriched-3j.root").c_str() );
    GeFCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bGenFilter-3j.pdf").c_str() );
    GeFCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bGenFilter-3j.root").c_str() );
    GesCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-total-3j.pdf").c_str() );
    GesCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-total-3j.root").c_str() );
  }
  else{
    EnrCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bEnriched-4j.pdf").c_str() );
    EnrCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bEnriched-4j.root").c_str() );
    GeFCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bGenFilter-4j.pdf").c_str() );
    GeFCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-bGenFilter-4j.root").c_str() );
    GesCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-total-4j.pdf").c_str() );
    GesCan -> SaveAs( ("Outputdata/mc-bg-" + var_ + "-" + region_ + "-total-4j.root").c_str() );
  }
  return 0;
}
