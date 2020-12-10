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

int scaleMCbg(string var_, int rebin_ , string region_, string era_, double xlow_, double xhigh_, double ylow_, double yhigh_, bool logy_, bool threejets_, bool jetht_) {

  cout << " " << endl;
  cout << "Input to be provided:" << endl;
  cout << "(str)variable ('pt_n', 'eta_n', 'phi_n', 'HT' or 'm12' with n=(0,1,2,3) and '_aac' for quantity after all cuts) [set to " << var_ <<"]," << endl;
  cout << "(int)rebinning factor [" << rebin_ << "]," << endl;
  cout << "(str)region ('CR'/'SR') [" << region_ << "]," << endl;
  cout << "(str)era ('C'/'D'/'E'/'F'/'CDE'/'CDEF') [" << era_ << "]," << endl;
  cout << "(double)x-axis-beginning ["<< xlow_ << "]," << endl;
  cout << "(double)x-axis-end [" << xhigh_ << "]," << endl;
  cout << "(double)y-axis-beginning [" << ylow_ << "]," << endl;
  cout << "(double)y-axis-end [" << yhigh_ << "]," << endl;
  cout << "(bool)logy? [" << logy_ << "]," << endl;
  cout << "(bool)3jets? [" << threejets_ << "]" << endl;

  string xtitleEnr, xtitleGeF, xtitleGes, ytitle = "Did you forget me?";
  double binning = 0.0;

  string assigndir = "rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/";
  string directory = ("Configs_diffBTags_allmedium/" + assigndir).c_str();

  string outfilename = (directory + "mcbg/MCbg-QCD-" + var_ + "-2017" + era_ + "-" + region_ + "-3j" + ".root").c_str();
  if (!threejets_) outfilename = (directory + "mcbg/MCbg-QCD-" + var_ + "-2017" + era_ + "-" + region_ + "-4j" + ".root").c_str();

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
  else if ( var == "m12" || (var == "m12_csv" || var == "m12_aac") ){
    cout << "m12 selected" << endl;
    binning = rebin_*20.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( (var == "m12_SR1" || var == "m12_SR2") || (var == "m12_SR3" || var == "m12_SR4")){
    cout << "m12 selected" << endl;
    binning = rebin_*20.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( var == "m12_SR1_1GeV" || var == "m12_SR2_1GeV" ){
    cout << "m12 selected" << endl;
    binning = rebin_*1.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( var == "m12_SR1_10GeV" ){
    cout << "m12 selected" << endl;
    binning = rebin_*10.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( var == "m12_SR2_15GeV" ){
    cout << "m12 selected" << endl;
    binning = rebin_*15.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( var == "m12_SR3_5GeV" ){
    cout << "m12 selected" << endl;
    binning = rebin_*5.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( var == "m12_SR3_20GeV" ){
    cout << "m12 selected" << endl;
    binning = rebin_*20.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( var == "m12_SR4_10GeV" ){
    cout << "m12 selected" << endl;
    binning = rebin_*10.0;
    xtitleEnr = "m_{12} [GeV], bEnriched";
    xtitleGeF = "m_{12} [GeV], bGenFilter";
    xtitleGes = "m_{12} [GeV]";
    ytitle = ("Events/" + to_string(binning) + " GeV").c_str();
  }
  else if ( var == "m12_SR4_25GeV" ){
    cout << "m12 selected" << endl;
    binning = rebin_*25.0;
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
  else if ((var_ == "phi_0" || var_ == "phi_0_csv") || var_ == "phi_0_bef_cuts"){
    cout << "phi_0 selected" << endl;
    binning = rebin_*0.1;
    cout << "binning: " << binning << endl;
    xtitleEnr = "#phi, 1^{st} jet, bEnriched";
    xtitleGeF = "#phi, 1^{st} jet, bGenFilter";
    xtitleGes = "#phi, 1^{st} jet";
    ytitle = ("Events/" + to_string(binning)).c_str();
  }
  else if ((var_ == "phi_1" || var_ == "phi_1_csv") || var_ == "phi_1_bef_cuts"){
    cout << "phi_1 selected" << endl;
    binning = rebin_*0.1;
    xtitleEnr = "#phi, 2^{nd} jet, bEnriched";
    xtitleGeF = "#phi, 2^{nd} jet, bGenFilter";
    xtitleGes = "#phi, 2^{nd} jet";
    ytitle = ("Events/" + to_string(binning)).c_str();
  }
  else if ((var_ == "phi_2" || var_ == "phi_2_csv") || var_ == "phi_2_bef_cuts"){
    cout << "phi_2 selected" << endl;
    binning = rebin_*0.1;
    xtitleEnr = "#phi, 3^{rd} jet, bEnriched";
    xtitleGeF = "#phi, 3^{rd} jet, bGenFilter";
    xtitleGes = "#phi, 3^{rd} jet";
    ytitle = ("Events/" + to_string(binning)).c_str();
  }
  else if ((var_ == "phi_3" || var_ == "phi_3_csv") || var_ == "phi_3_bef_cuts"){
    cout << "phi_3 selected" << endl;
    binning = rebin_*0.1;
    xtitleEnr = "#phi, 4^{th} jet, bEnriched";
    xtitleGeF = "#phi, 4^{th} jet, bGenFilter";
    xtitleGes = "#phi, 4^{th} jet";
    ytitle = ("Events/" + to_string(binning)).c_str();
  }
  else{
    cout << "No known variable selected. Please select 'pt_n', 'eta_n', 'HT' or 'm12' with n=(0,1,2,3). For the quantities after cuts, please add '_aac' to the string. For the subrange histograms, the options 'm12_SR1_1GeV', 'm12_SR2_1GeV', 'm12_SR3_5GeV', 'm12_SR4_10GeV' are available." << endl; 
    return -1;
  }
  cout << "Variable check successful. Bin width: " << binning << endl;
  cout << "titles: " << xtitleEnr << " " << xtitleGeF << " " << xtitleGes << " " << ytitle << endl;

  cout << " " << endl;
  cout << "Checking region consistency..." << endl;
  string reg = region_;
  if (! ((reg == "CR" || reg == "SR") || reg == "VR")){
    cout << "Please select either 'CR', 'VR' or 'SR' as region!" << endl; 
    return -1;
  }
  cout << "Region check successful." << endl;

  string varname;
  if ( var_ == "pt_0" || var_ == "pt_0_aac") varname = "p_{T}, 1^{st} jet";
  else if ( var_ == "pt_1" || var_ == "pt_1_aac") varname = "p_{T}, 2^{nd} jet";
  else if ( var_ == "pt_2" || var_ == "pt_2_aac") varname = "p_{T}, 3^{rd} jet";
  else if ( var_ == "eta_0" || var_ == "eta_0_aac") varname = "#eta, 1^{st} jet";
  else if ( var_ == "eta_1" || var_ == "eta_1_aac") varname = "#eta, 2^{nd} jet";
  else if ( var_ == "eta_2" || var_ == "eta_2_aac") varname = "#eta, 3^{rd} jet";
  else if ( var_ == "phi_0" || var_ == "phi_0_csv") varname = "#phi, 1^{st} jet";
  else if ( var_ == "phi_1" || var_ == "phi_1_csv") varname = "#phi, 2^{nd} jet";
  else if ( var_ == "phi_2" || var_ == "phi_2_csv") varname = "#phi, 3^{rd} jet";
  else if ( (var_ == "HT" || var_ == "HT_aac") || var_ == "HT_bef_cuts") varname = "H_{T}";
  else if ( var_ == "m12" || var_ == "m12_aac") varname = "m_{12}";
  else varname = var_;

  cout << "Set varname: " << varname << endl;

  vector<string> pthatbins = {"200to300","300to500","500to700","700to1000","1000to1500", "1500to2000", "2000toInf"};
  vector<double> sfvaluesEnr = {291.08  ,  168.74  ,   26.64  ,   11.70   ,    6.26    ,     2.19    ,    0.08    };
  vector<double> sfvaluesGeF = {467.62  ,  182.85  ,   14.57  ,   14.36   ,    3.94    ,     2.19    ,    0.49    };//for bGenFilter
  if (era_ == "C"){
    sfvaluesEnr = {77.424, 44.884, 7.087, 3.185, 1.666, 0.582, 0.020};
    sfvaluesGeF = {124.384, 48.635, 3.874, 3.819, 1.049, 0.581, 0.130};
  }
  else if (era_ == "D"){
    sfvaluesEnr = {34.134, 19.788, 3.125, 1.404, 0.735, 0.257, 0.009};
    sfvaluesGeF = {54.838, 21.442, 1.708, 1.684, 0.463, 0.256, 0.057};
  }
  else if (era_ == "E"){
    sfvaluesEnr = {70.733, 41.005, 6.475, 2.910, 1.522, 0.532, 0.019};
    sfvaluesGeF = {113.635, 44.432, 3.539, 3.489, 0.959, 0.531, 0.119};
  }
  else if (era_ == "F"){
    sfvaluesEnr = {108.786, 63.065, 9.958, 4.475, 2.341, 0.818, 0.029};
    sfvaluesGeF = {174.769, 68.336, 5.444, 5.366, 1.474, 0.817, 0.183};
  }
  else if (era_ == "CDE"){
    sfvaluesEnr = {182.291, 105.677, 16.687, 7.499, 3.923, 1.370, 0.048};
    sfvaluesGeF = {292.856, 114.510, 9.122, 8.992, 2.470, 1.369, 0.307};
  }
  if (jetht_) sfvaluesGeF = {0.03192073, 0.00647697, 0.00064592, 0.00016072, 0.00007939, 0.00001032, 0.00000412};

  cout << "Selected scale factors." << endl;
  
  vector<int> colors = {kRed,kBlue,kGreen,kMagenta,kCyan,kBlack,kViolet};
  //  map<string, string> colormap;

  map<string, double> scalefactorsEnr;
  map<string, TFile*> filesEnr;
  map<string, TH1F*> histogramsEnr;

  map<string, double> scalefactorsGeF;
  map<string, TFile*> filesGeF;
  map<string, TH1F*> histogramsGeF;

  for (unsigned int i = 0; i < pthatbins.size(); i++){
    if (!jetht_) scalefactorsEnr[pthatbins[i]] = sfvaluesEnr[i];
    scalefactorsGeF[pthatbins[i]] = sfvaluesGeF[i];
    //    colormap[pthatbins[i]] = colors[i];
    if (!jetht_) filesEnr[pthatbins[i]] = new TFile( (directory + "mcbg/mc-bg-HT-" + pthatbins[i] + "-bEnriched-" + region_ + ".root").c_str(),"READ");
    filesGeF[pthatbins[i]] = new TFile( (directory + "mcbg/mc-bg-HT-" + pthatbins[i] + "-bGenFilter-" + region_ + ".root").c_str(),"READ");
    if (threejets_){
      if (!jetht_) filesEnr[pthatbins[i]] = new TFile( (directory + "mcbg/mc-bg-HT-" + pthatbins[i] + "-bEnriched-" + region_ + "-3j.root").c_str(),"READ");
      filesGeF[pthatbins[i]] = new TFile( (directory + "mcbg/mc-bg-HT-" + pthatbins[i] + "-bGenFilter-" + region_ + "-3j.root").c_str(),"READ");
    }

    cout << "Selected input files." << endl;

    if (!jetht_){
      cout << "QCD samples" << endl;
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
    }
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

  cout << "Extracted histogram from file" << endl;

  double nbinsx = histogramsGeF[pthatbins[0]] -> GetNbinsX();
  double xreflow = histogramsGeF[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( 1 );
  double xrefhigh = histogramsGeF[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( histogramsGeF[pthatbins[0]] -> GetNbinsX()+1 );

  TCanvas* EnrCan = style.MakeCanvas("EnrCan", "", 700,700);
  TCanvas* GeFCan = style.MakeCanvas("GeFCan", "", 700,700);
  TCanvas* GesCan = style.MakeCanvas("GesCan", "", 700,700);
  TCanvas* EnrSingleCan = style.MakeCanvas("EnrSingleCan", "", 700,700);
  TCanvas* GeFSingleCan = style.MakeCanvas("GeFSingleCan", "", 700,700);
  if (logy_){
    if (!jetht_) EnrCan -> SetLogy();
    if (!jetht_) EnrSingleCan -> SetLogy();
    GeFCan -> SetLogy();
    GeFSingleCan -> SetLogy();
    GesCan -> SetLogy();
  }
  TH1F* hist_output_enr = new TH1F("hist_output_enr", "", nbinsx, xreflow, xrefhigh);
  TH1F* hist_output_gef = new TH1F("hist_output_gef", "", nbinsx, xreflow, xrefhigh);
  TH1F* hist_output_ges = new TH1F("hist_output_ges", "", nbinsx, xreflow, xrefhigh);
  if (!jetht_) style.InitHist(hist_output_enr,xtitleEnr.c_str(),ytitle.c_str(),kBlue,0);
  style.InitHist(hist_output_gef,xtitleGeF.c_str(),ytitle.c_str(),kRed,0);
  style.InitHist(hist_output_ges,xtitleGeF.c_str(),ytitle.c_str(),kGreen,0);
  if (!jetht_) hist_output_enr -> SetMarkerSize(1);
  hist_output_gef -> SetMarkerSize(1);
  hist_output_ges -> SetMarkerSize(1);

  cout << "Filled histograms" << endl;

  if (!jetht_) {
    for (auto const &hist1 : histogramsEnr){
      hist_output_enr -> Add(histogramsEnr[hist1.first]/* , scalefactorsEnr[hist1.first]*/);
    }
  }

  for (auto const &hist2 : histogramsGeF){
    hist_output_gef -> Add(histogramsGeF[hist2.first]/* , scalefactorsGeF[hist2.first]*/);
  }

  if (!jetht_) {
    //hist_output_enr -> Rebin(rebin_);
    hist_output_enr -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
    hist_output_enr -> GetXaxis() -> SetTitle(xtitleEnr.c_str());
    hist_output_enr -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
    hist_output_enr -> GetYaxis() -> SetTitle(ytitle.c_str());
    hist_output_enr -> GetYaxis() -> SetTitleOffset(1.2);
    hist_output_enr -> GetYaxis() -> SetNdivisions(505);
  }  
  
  TLegend* legEnr = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legEnr);
  if (!jetht_) legEnr -> AddEntry(hist_output_enr,varname.c_str(),"LP");
  
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
  if (!jetht_) hist_output_ges -> Add(hist_output_enr);
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

  if (!jetht_){
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
  }
  
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
    
  /*  if (threejets_){
    EnrCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-3j.pdf").c_str() );
    EnrCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-3j.root").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-3j-single_hists.pdf").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-3j-single_hists.root").c_str() );
    GeFCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-3j.pdf").c_str() );
    GeFCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-3j.root").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-3j-single_hists.pdf").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-3j-single_hists.root").c_str() );
    GesCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-total-3j.pdf").c_str() );
    GesCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-total-3j.root").c_str() );
  }
  else{
    EnrCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-4j.pdf").c_str() );
    EnrCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-4j.root").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-4j-single_hists.pdf").c_str() );
    EnrSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bEnriched-4j-single_hists.root").c_str() );
    GeFCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-4j.pdf").c_str() );
    GeFCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-4j.root").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-4j-single_hists.pdf").c_str() );
    GeFSingleCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-bGenFilter-4j-single_hists.root").c_str() );
    GesCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-total-4j.pdf").c_str() );
    GesCan -> SaveAs( ("Outputdata/" + assigndir + "mc-bg-inclProperSubrangeHists-" + var_ + "-2017" + era_ + "-" + region_ + "-total-4j.root").c_str() );
    }*/
  return 0;
}
