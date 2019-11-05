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

int scaleMCbg_forSF(string var_, string era_, double xlow_, double xhigh_, string xtitle_, double ylow_, double yhigh_, string ytitle_, bool logy_) {

  cout << " " << endl;
  cout << "Input to be provided:" << endl;
  cout << "(str)variable [set to " << var_ << "]," << endl;
  cout << "(str)era [" << era_ << "]," << endl;
  cout << "(double)x-axis-beginning ["<< xlow_ << "]," << endl;
  cout << "(double)x-axis-end [" << xhigh_ << "]," << endl;
  cout << "(str) title of x axis [" << xtitle_ << "]," << endl; 
  cout << "(double)y-axis-beginning [" << ylow_ << "]," << endl;
  cout << "(double)y-axis-end [" << yhigh_ << "]," << endl;
  cout << "(str) title of y axis [" << ytitle_ << "]," << endl;
  cout << "(bool)logy? [" << logy_ << "]" << endl;

  string xtitle, xtitleGeF, xtitleGes, ytitle = "Did you forget me?";

  string outfilename = ("QCDMC-" + var_ + "_" + era_ + "_for-sf.root").c_str();
  cout << "output root file: " << outfilename << endl;

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  vector<string> pthatbins = {"200to300","300to500","500to700","700to1000","1000to1500", "1500to2000", "2000toInf"};
  vector<double> sfvalues  = {0.00666882, 0.00135316, 0.00013494, 0.00003358, 0.00001659, 0.00000216, 0.00000086};
  if (era_ == "D") sfvalues = {0.01067539, 0.00216612, 0.00021602, 0.00005375, 0.00002655, 0.00000345, 0.00000138};
  else if (era_ == "E") sfvalues = {0.00759139, 0.00154035, 0.00015361, 0.00003822, 0.00001888, 0.00000245, 0.00000098};
  else if (era_ == "F") sfvalues = {0.00698513, 0.00141734, 0.00014135, 0.00003517, 0.00001737, 0.00000226, 0.00000090};
  else if (era_ == "2017") sfvalues = {0.03192073, 0.00647697, 0.00064592, 0.00016072, 0.00007939, 0.00001032, 0.00000412};
  else cout << "Era C selected" << endl;
  
  vector<int> colors = {kRed,kBlue,kGreen,kMagenta,kCyan,kBlack,kViolet};

  map<string, double> scalefactors;
  map<string, TFile*> files;
  map<string, TH1F*> histograms;

  for (unsigned int i = 0; i < pthatbins.size(); i++){
    scalefactors[pthatbins[i]] = sfvalues[i];
    files[pthatbins[i]] = new TFile( ("Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/QCDMC_" + pthatbins[i] + ".root").c_str(),"READ");
    cout << ("Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/QCDMC_" + pthatbins[i] + ".root").c_str();
    histograms[pthatbins[i]] = (TH1F*)files[pthatbins[i]] -> Get(var_.c_str());
    style.InitHist(histograms[pthatbins[i]],xtitle_.c_str(),ytitle_.c_str(),colors[i],0);
    cout << "initialized." << endl;
    histograms[pthatbins[i]] -> SetMarkerSize(1.0);
    histograms[pthatbins[i]] -> Scale(scalefactors[pthatbins[i]]);
    histograms[pthatbins[i]] -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
    histograms[pthatbins[i]] -> GetXaxis() -> SetTitle(xtitle_.c_str());
    histograms[pthatbins[i]] -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
    histograms[pthatbins[i]] -> GetYaxis() -> SetTitle(ytitle_.c_str());
    histograms[pthatbins[i]] -> GetYaxis() -> SetTitleOffset(1.2);
    histograms[pthatbins[i]] -> GetYaxis() -> SetNdivisions(505);
    histograms[pthatbins[i]] -> GetXaxis() -> SetNdivisions(505);
    cout << "Done." << endl;
  }

  double nbinsx = histograms[pthatbins[0]] -> GetNbinsX();
  double xreflow = histograms[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( 1 );
  double xrefhigh = histograms[pthatbins[0]] -> GetXaxis() -> GetBinLowEdge( histograms[pthatbins[0]] -> GetNbinsX()+1 );

  TCanvas* Can = style.MakeCanvas("Can", "", 700,700);
  TCanvas* SingleCan = style.MakeCanvas("SingleCan", "", 700,700);
  if (logy_){
    Can -> SetLogy();
    SingleCan -> SetLogy();
  }
  TH1F* hist_output_enr = new TH1F("hist_output_enr", "", nbinsx, xreflow, xrefhigh);
  style.InitHist(hist_output_enr,xtitle_.c_str(),ytitle_.c_str(),kBlue,0);
  hist_output_enr -> SetMarkerSize(1);

  for (auto const &hist1 : histograms){
    hist_output_enr -> Add(histograms[hist1.first]/* , scalefactors[hist1.first]*/);
  }

  hist_output_enr -> GetXaxis() -> SetRangeUser(xlow_, xhigh_);
  hist_output_enr -> GetXaxis() -> SetTitle(xtitle_.c_str());
  hist_output_enr -> GetYaxis() -> SetRangeUser(ylow_, yhigh_);
  hist_output_enr -> GetYaxis() -> SetTitle(ytitle_.c_str());
  hist_output_enr -> GetYaxis() -> SetTitleOffset(1.2);
  hist_output_enr -> GetYaxis() -> SetNdivisions(505);

  string varname = "p_{T}^{(1)}";
  if (var_ == "pt_0_PFJet60xOffl_eta0to1") varname = "p_{T}^{(1)}, 0.0 < |#eta| < 1.0, PFJet60 x offl.";
  else if (var_ == "pt_0_PFJet60xOffl_eta1to1p4") varname = "p_{T}^{(1)}, 1.0 < |#eta| < 1.4, PFJet60 x offl.";
  else if (var_ == "pt_0_PFJet60xOffl_eta1p4to2p2") varname = "p_{T}^{(1)}, 1.4 < |#eta| < 2.2, PFJet60 x offl.";
  else if (var_ == "pt_0_PFJet100xOffl_eta0to1") varname = "p_{T}^{(1)}, 0.0 < |#eta| < 1.0, PFJet100 x offl.";
  else if (var_ == "pt_0_PFJet100xOffl_eta1to1p4") varname = "p_{T}^{(1)}, 1.0 < |#eta| < 1.4, PFJet100 x offl.";
  else if (var_ == "pt_0_PFJet100xOffl_eta1p4to2p2") varname = "p_{T}^{(1)}, 1.4 < |#eta| < 2.2, PFJet100 x offl.";
  
  
  TLegend* leg = new TLegend(0.39,0.68,0.79,0.98);
  style.SetLegendStyle(leg);
  leg -> AddEntry(hist_output_enr,varname.c_str(),"LP");

  TLegend* legSi = new TLegend(0.58,0.6,0.98,0.9);
  style.SetLegendStyle(legSi);

  cout << "Number of entries after adding and scaling all bins: " << hist_output_enr->Integral() << endl;

  Can -> cd();
  hist_output_enr -> Draw();
  leg -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.123, 0.84);
  Can -> Update();

  SingleCan -> cd();
  for (unsigned int i = 0; i < pthatbins.size(); i++){
    legSi -> AddEntry(histograms[pthatbins[i]],(pthatbins[i]).c_str(),"LP");
    if (i == 0){
      histograms[pthatbins[i]] -> Draw();
    }
    else{
      histograms[pthatbins[i]] -> Draw("SAME");
    }
  }
  legSi -> Draw("SAME");
  CMSPrelim( "Simulation (13 TeV)" , "Work in progress", 0.123, 0.84);
  SingleCan -> Update();

  TFile* out_file = new TFile( (outfilename).c_str() , "RECREATE" );
  hist_output_enr -> Write();

  Can -> SaveAs( ("Outputdata/TriggerSF/MC-" + var_ + "-2017" + era_ + ".pdf").c_str() );
  Can -> SaveAs( ("Outputdata/TriggerSF/MC-" + var_ + "-2017" + era_ + ".root").c_str() );
  SingleCan -> SaveAs( ("Outputdata/TriggerSF/MC-" + var_ + "-2017" + era_ + "single_hists.pdf").c_str() );
  SingleCan -> SaveAs( ("Outputdata/TriggerSF/MC-" + var_ + "-2017" + era_ + "single_hists.root").c_str() );
  
  return 0;
}
