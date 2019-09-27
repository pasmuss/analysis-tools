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
  cout << "(str)variable ('pt_n', 'eta_n', 'HT' or 'm12' with n=(0,1,2,3) and '_aac' for quantity after all cuts) [set to " << var_ <<"]," << endl;
  cout << "(int)rebinning factor [" << rebin_ << "]," << endl;
  cout << "(str)region ('CR'/'SR') [" << region_ << "]," << endl;
  cout << "(double)x-axis-beginning ["<< xlow_ << "]," << endl;
  cout << "(double)x-axis-end [" << xhigh_ << "]," << endl;
  cout << "(double)y-axis-beginning [" << ylow_ << "]," << endl;
  cout << "(double)y-axis-end [" << yhigh_ << "]," << endl;
  cout << "(bool)logy? [" << logy_ << "]," << endl;
  cout << "(bool)3jets? [" << threejets_ << "]" << endl;

  string xtitleEnr, xtitleGeF, xtitleGes, ytitle = "Did you forget me?";
  long binning = 0.0;

  string outfilename = ("MCbg-QCD-" + var_ + "-" + region_ + "-3j" + ".root").c_str();
  if (!threejets_) outfilename = ("MCbg-QCD-" + var_ + "-" + region_ + "-4j" + ".root").c_str();

  cout << "output root file: " << outfilename << endl;

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  cout << " " << endl;
  cout << "Checking variable consistency..." << endl;
  string var = var_;
  if (var == "pt_0" || (var == "pt_0_csv" || var == "pt_0_aac")){
    cout << "pT of first jet selected" << endl;
    binning = rebin_*10.0;
    xtitleEnr = "p_{T}, 1^{st} jet [GeV], bEnriched";
    xtitleGeF = "p_{T}, 1^{st} jet [GeV], bGenFilter";
    xtitleGes = "p_{T}, 1^{st} jet [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV [a.u.]").c_str();
  }
  else if (var == "pt_1" || (var == "pt_1_csv" || var == "pt_1_aac")){
    cout << "pT of second jet selected"<< endl;
    binning = rebin_*10.0;
    xtitleEnr = "p_{T}, 2^{nd} jet [GeV], bEnriched";
    xtitleGeF = "p_{T}, 2^{nd} jet [GeV], bGenFilter";
    xtitleGes = "p_{T}, 2^{nd} jet [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV [a.u.]").c_str();
  }
  else if (var == "pt_2" || (var == "pt_2_csv" || var == "pt_2_aac")){
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
  else if (var == "eta_0" || (var == "eta_0_csv" || var == "eta_0_aac")){
    cout << "eta of first jet selected" << endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 1^{st} jet, bEnriched";
    xtitleGeF = "#eta, 1^{st} jet, bGenFilter";
    xtitleGes = "#eta, 1^{st} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if (var == "eta_1" || (var == "eta_1_csv" || var == "eta_1_aac")){
    cout << "eta of second jet selected"<< endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 2^{nd} jet, bEnriched";
    xtitleGeF = "#eta, 2^{nd} jet, bGenFilter";
    xtitleGes = "#eta, 2^{nd} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if (var == "eta_2" || (var == "eta_2_csv" || var == "eta_2_aac")){
    cout << "eta of third jet selected"<< endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 3^{rd} jet, bEnriched";
    xtitleGeF = "#eta, 3^{rd} jet, bGenFilter";
    xtitleGes = "#eta, 3^{rd} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if (var == "eta_3" || (var == "eta_3_csv" || var == "eta_3_aac")){
    cout << "eta of fourth jet selected"<< endl;
    binning = rebin_*0.01;
    xtitleEnr = "#eta, 4^{th} jet, bEnriched";
    xtitleGeF = "#eta, 4^{th} jet, bGenFilter";
    xtitleGes = "#eta, 4^{th} jet";
    ytitle = ("Events/" + to_string(binning) + " [a.u.]").c_str();
  }
  else if ( var == "m12" || (var == "m12_csv" || var == "m12_aac")){
    cout << "m12 selected" << endl;
    binning = rebin_*20.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ((var_ == "HT" || var_ == "HT_aac") || var_ == "HT_bef_cuts"){
    cout << "HT selected" << endl;
    binning = rebin_*10.0;
    xtitleEnr = "H_{T} [GeV], bEnriched";
    xtitleGeF = "H_{T} [GeV], bGenFilter";
    xtitleGes = "H_{T} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else{
    cout << "No known variable selected. Please select 'pt_n', 'eta_n', 'HT' or 'm12' with n=(0,1,2,3). For the quantities after cuts, please add '_aac' to the string." << endl; 
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
  else if ( (var_ == "HT" || var_ == "HT_aac") || var_ == "HT_bef_cuts") varname = "H_{T}";
  else if ( var_ == "m12" || var_ == "m12_csv") varname = "m_{12}";
  else varname = var_;

  vector<string> pthatbins = {"200to300","300to500","500to700","700to1000","1000to1500", "1500to2000", "2000toInf"};
  vector<double> sfvaluesEnr = {291.08  ,  168.74  ,   26.64  ,   11.70   ,    6.26    ,     2.19    ,    0.08    };
  vector<double> sfvaluesGeF = {467.62  ,  182.85  ,   14.57  ,   14.36   ,    3.94    ,     2.19    ,    0.49    };//for bGenFilter
  
  vector<int> colors = {kRed,kBlue,kGreen,kMagenta,kCyan,kBlack,kViolet};
  //  map<string, string> colormap;

  map<string, double> scalefactorsEnr;
  map<string, TFile*> filesEnr;
  map<string, TH1F*> histogramsEnr;

  map<string, double> scalefactorsGeF;
  map<string, TFile*> filesGeF;
  map<string, TH1F*> histogramsGeF;

  for (unsigned int i = 0; i < pthatbins.size(); i++){
    scalefactorsEnr[pthatbins[i]] = sfvaluesEnr[i];
    scalefactorsGeF[pthatbins[i]] = sfvaluesGeF[i];
    //    colormap[pthatbins[i]] = colors[i];
    filesEnr[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_pT110-100_Sep02-19/mcbg/mc-bg-HT-" + pthatbins[i] + "-bEnriched-" + region_ + ".root").c_str(),"READ");
    filesGeF[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_pT110-100_Sep02-19/mcbg/mc-bg-HT-" + pthatbins[i] + "-bGenFilter-" + region_ + ".root").c_str(),"READ");
    if (threejets_){
      filesEnr[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_pT110-100_Sep02-19/mcbg/mc-bg-HT-" + pthatbins[i] + "-bEnriched-" + region_ + "-3j.root").c_str(),"READ");
      filesGeF[pthatbins[i]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_pT110-100_Sep02-19/mcbg/mc-bg-HT-" + pthatbins[i] + "-bGenFilter-" + region_ + "-3j.root").c_str(),"READ");
    }
    histogramsEnr[pthatbins[i]] = (TH1F*)filesEnr[pthatbins[i]] -> Get(var_.c_str());
    style.InitHist(histogramsEnr[pthatbins[i]],xtitleEnr.c_str(),ytitle.c_str(),colors[i],0);
    histogramsEnr[pthatbins[i]] -> SetMarkerSize(1.0);
    histogramsEnr[pthatbins[i]] -> Scale(scalefactorsEnr[pthatbins[i]]);
    histogramsEnr[pthatbins[i]] -> Rebin(rebin_);
    histogramsEnr[pthatbins[i]] -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
    histogramsEnr[pthatbins[i]] -> GetXaxis() -> SetTitle(xtitleEnr.c_str());
    histogramsEnr[pthatbins[i]] -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
    histogramsEnr[pthatbins[i]] -> GetYaxis() -> SetTitle(ytitle.c_str());
    histogramsEnr[pthatbins[i]] -> GetYaxis() -> SetTitleOffset(1.2);
    histogramsEnr[pthatbins[i]] -> GetYaxis() -> SetNdivisions(505);
    histogramsEnr[pthatbins[i]] -> GetXaxis() -> SetNdivisions(505);
    histogramsGeF[pthatbins[i]] = (TH1F*)filesGeF[pthatbins[i]] -> Get(var_.c_str());
    style.InitHist(histogramsGeF[pthatbins[i]],xtitleGeF.c_str(),ytitle.c_str(),colors[i],0);
    histogramsGeF[pthatbins[i]] -> SetMarkerSize(1.0);
    histogramsGeF[pthatbins[i]] -> Scale(scalefactorsGeF[pthatbins[i]]);
    histogramsGeF[pthatbins[i]] -> Rebin(rebin_);
    histogramsGeF[pthatbins[i]] -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
    histogramsGeF[pthatbins[i]] -> GetXaxis() -> SetTitle(xtitleGeF.c_str());
    histogramsGeF[pthatbins[i]] -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
    histogramsGeF[pthatbins[i]] -> GetYaxis() -> SetTitle(ytitle.c_str());
    histogramsGeF[pthatbins[i]] -> GetYaxis() -> SetTitleOffset(1.2);
    histogramsGeF[pthatbins[i]] -> GetYaxis() -> SetNdivisions(505);
    histogramsGeF[pthatbins[i]] -> GetXaxis() -> SetNdivisions(505);
  }

  double nbinsx = histogramsEnr[pthatbins[0]] -> GetNbinsX();
  double xreflow = histogramsEnr[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( 1 );
  double xrefhigh = histogramsEnr[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( histogramsEnr[pthatbins[0]] -> GetNbinsX()+1 );

  TCanvas* EnrCan = style.MakeCanvas("EnrCan", "", 700,700);
  TCanvas* GeFCan = style.MakeCanvas("GeFCan", "", 700,700);
  TCanvas* GesCan = style.MakeCanvas("GesCan", "", 700,700);
  TCanvas* EnrSingleCan = style.MakeCanvas("EnrSingleCan", "", 700,700);
  TCanvas* GeFSingleCan = style.MakeCanvas("GeFSingleCan", "", 700,700);
  if (logy_){
    EnrCan -> SetLogy();
    EnrSingleCan -> SetLogy();
    GeFCan -> SetLogy();
    GeFSingleCan -> SetLogy();
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
    hist_output_enr -> Add(histogramsEnr[hist1.first]/* , scalefactorsEnr[hist1.first]*/);
  }

  for (auto const &hist2 : histogramsGeF){
    hist_output_gef -> Add(histogramsGeF[hist2.first]/* , scalefactorsGeF[hist2.first]*/);
  }

  //hist_output_enr -> Rebin(rebin_);
  hist_output_enr -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output_enr -> GetXaxis() -> SetTitle(xtitleEnr.c_str());
  hist_output_enr -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output_enr -> GetYaxis() -> SetTitle(ytitle.c_str());
  hist_output_enr -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output_enr -> GetYaxis() -> SetNdivisions(505);

  TLegend* legEnr = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legEnr);
  legEnr -> AddEntry(hist_output_enr,varname.c_str(),"LP");

  TLegend* legEnrSi = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legEnrSi);

  //hist_output_gef -> Rebin(rebin_);
  hist_output_gef -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output_gef -> GetXaxis() -> SetTitle(xtitleGeF.c_str());
  hist_output_gef -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output_gef -> GetYaxis() -> SetTitle(ytitle.c_str());
  hist_output_gef -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output_gef -> GetYaxis() -> SetNdivisions(505);

  TLegend* legGef = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legGef);
  legGef -> AddEntry(hist_output_gef,varname.c_str(),"LP");

  TLegend* legGefSi = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legGefSi);

  //hist_output_ges -> Rebin(rebin_);
  hist_output_ges -> Add(hist_output_enr);
  hist_output_ges -> Add(hist_output_gef);
  hist_output_ges -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output_ges -> GetXaxis() -> SetTitle(xtitleGes.c_str());
  hist_output_ges -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output_ges -> GetYaxis() -> SetTitle(ytitle.c_str());
  hist_output_ges -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output_ges -> GetYaxis() -> SetNdivisions(505);

  cout << "Number of entries after adding and scaling all bins: " << hist_output_ges->Integral() << endl;

  TLegend* legGes = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legGes);
  legGes -> AddEntry(hist_output_ges,varname.c_str(),"LP");

  EnrCan -> cd();
  hist_output_enr -> Draw();
  legEnr -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.123, 0.84);
  EnrCan -> Update();

  EnrSingleCan -> cd();
  for (unsigned int i = 0; i < pthatbins.size(); i++){
    legEnrSi -> AddEntry(histogramsEnr[pthatbins[i]],(pthatbins[i]).c_str(),"LP");
    if (i == 0){
      histogramsEnr[pthatbins[i]] -> Draw();
    }
    else{
      histogramsEnr[pthatbins[i]] -> Draw("SAME");
    }
  }
  legEnrSi -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.123, 0.84);
  EnrSingleCan -> Update();

  GeFCan -> cd();
  hist_output_gef -> Draw();
  legGef -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.123, 0.84);
  GeFCan -> Update();

  GeFSingleCan -> cd();
  for (unsigned int i = 0; i < pthatbins.size(); i++){
    legGefSi ->AddEntry(histogramsGeF[pthatbins[i]],(pthatbins[i]).c_str(),"LP");
    if (i == 0){
      histogramsGeF[pthatbins[i]] -> Draw();
    }
    else{
      histogramsGeF[pthatbins[i]] -> Draw("SAME");
    }
  }
  legGefSi -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.123, 0.84);
  GeFSingleCan -> Update();


  GesCan -> cd();
  hist_output_ges -> Draw();

  TFile* out_file = new TFile( (outfilename).c_str() , "RECREATE" );
  hist_output_ges -> Write();

  legGes -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.123, 0.84);
  GesCan -> Update();
  /*  
  if (threejets_){
    EnrCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-3j.pdf").c_str() );
    EnrCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-3j.root").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-3j-single_hists.pdf").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-3j-single_hists.root").c_str() );
    GeFCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-3j.pdf").c_str() );
    GeFCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-3j.root").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-3j-single_hists.pdf").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-3j-single_hists.root").c_str() );
    GesCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-total-3j.pdf").c_str() );
    GesCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-total-3j.root").c_str() );
  }
  else{
    EnrCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-4j.pdf").c_str() );
    EnrCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-4j.root").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-4j-single_hists.pdf").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bEnriched-4j-single_hists.root").c_str() );
    GeFCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-4j.pdf").c_str() );
    GeFCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-4j.root").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-4j-single_hists.pdf").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-bGenFilter-4j-single_hists.root").c_str() );
    GesCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-total-4j.pdf").c_str() );
    GesCan -> SaveAs( ("Outputdata/m12_ratio_CR-SR/mc-bg-inclOnlBtagSF-" + var_ + "-" + region_ + "-total-4j.root").c_str() );
    }*/
  return 0;
}
