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

void compareDataCRsr34j_cutflow(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TCanvas* canrel = style.MakeCanvas("canrel", "Efficiency", 700,700);
  TCanvas* canabs = style.MakeCanvas("canabs", "Number of Events", 700,700);

  int cutflowsteps = 8;

  TFile* file3jsr = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_incl_prescale/rereco/rereco-CDEF-deep-SR-3j.root","READ");
  TFile* file3jcr = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_incl_prescale/rereco/rereco-CDEF-deep-CR-3j.root","READ");
  TFile* file4jsr = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_incl_prescale/rereco/rereco-CDEF-deep-SR.root","READ");
  TFile* file4jcr = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dfl_incl_prescale/rereco/rereco-CDEF-deep-CR.root","READ");

  TH1F* hist3jsrRel = (TH1F*)file3jsr->Get("cutflow");
  TH1F* hist3jcrRel = (TH1F*)file3jcr->Get("cutflow");
  TH1F* hist4jsrRel = (TH1F*)file4jsr->Get("cutflow");
  TH1F* hist4jcrRel = (TH1F*)file4jcr->Get("cutflow");

  TH1F* hist3jsrAbs = (TH1F*)file3jsr->Get("noofevents_h");
  TH1F* hist3jcrAbs = (TH1F*)file3jcr->Get("noofevents_h");
  TH1F* hist4jsrAbs = (TH1F*)file4jsr->Get("noofevents_h");
  TH1F* hist4jcrAbs = (TH1F*)file4jcr->Get("noofevents_h");

  float scalefactor = hist3jsrRel->GetBinContent(1);

  hist3jsrRel -> Scale(1/scalefactor);
  hist3jcrRel -> Scale(1/scalefactor);
  hist4jsrRel -> Scale(1/scalefactor);
  hist4jcrRel -> Scale(1/scalefactor);

  //Absolute number must not be scaled - only relative should be normalized to one!

  float val3jsrRel[cutflowsteps];
  float val3jcrRel[cutflowsteps];
  float val4jsrRel[cutflowsteps];
  float val4jcrRel[cutflowsteps];

  float val3jsrAbs[cutflowsteps];
  float val3jcrAbs[cutflowsteps];
  float val4jsrAbs[cutflowsteps];
  float val4jcrAbs[cutflowsteps];

  float cfsteps[cutflowsteps];

  for (unsigned int i; i < cutflowsteps; i++){
    val3jsrRel[i] = hist3jsrRel->GetBinContent(i+1);
    val3jcrRel[i] = hist3jcrRel->GetBinContent(i+1);
    val4jsrRel[i] = hist4jsrRel->GetBinContent(i+1);
    val4jcrRel[i] = hist4jcrRel->GetBinContent(i+1);

    cfsteps[i] = i;

    val3jsrAbs[i] = hist3jsrAbs->GetBinContent(i+2);
    val3jcrAbs[i] = hist3jcrAbs->GetBinContent(i+2);
    val4jsrAbs[i] = hist4jsrAbs->GetBinContent(i+2);
    val4jcrAbs[i] = hist4jcrAbs->GetBinContent(i+2);
  }

  canrel -> cd();
  canrel -> SetLogy();
  TGraph* gr3jsrRel = new TGraph(cutflowsteps,cfsteps,val3jsrRel);
  gr3jsrRel -> SetTitle();
  gr3jsrRel -> GetXaxis() -> SetTitle("Cuts");
  gr3jsrRel -> GetYaxis() -> SetTitle("Efficiency");
  gr3jsrRel -> GetYaxis() -> SetTitleOffset(1.2);
  gr3jsrRel -> SetMinimum(0.00001);
  gr3jsrRel -> SetMarkerStyle(20);
  gr3jsrRel -> SetLineColor(kRed);
  gr3jsrRel -> Draw("ALP");
  TGraph* gr3jcrRel = new TGraph(cutflowsteps,cfsteps,val3jcrRel);
  gr3jcrRel -> SetMarkerStyle(26);
  gr3jcrRel -> SetLineColor(kRed);
  gr3jcrRel -> Draw("LP");
  TGraph* gr4jsrRel = new TGraph(cutflowsteps,cfsteps,val4jsrRel);
  gr4jsrRel -> SetMarkerStyle(20);
  gr4jsrRel -> SetLineColor(kBlue);
  gr4jsrRel -> Draw("LP");
  TGraph* gr4jcrRel = new TGraph(cutflowsteps,cfsteps,val4jcrRel);
  gr4jcrRel -> SetMarkerStyle(26);
  gr4jcrRel -> SetLineColor(kBlue);
  gr4jcrRel -> Draw("LP");

  TLegend* legRel = new TLegend(0.2,0.3,0.7,0.7);
  style.SetLegendStyle(legRel);
  legRel -> AddEntry(gr4jsrRel,"4 jets (bbnbb), SR","LP");
  legRel -> AddEntry(gr4jcrRel,"4 jets (bbnbb), CR","LP");
  legRel -> AddEntry(gr3jsrRel,"3 jets (bbnbb), SR","LP");
  legRel -> AddEntry(gr3jcrRel,"3 jets (bbnbb), CR","LP");
  legRel -> Draw("SAME");

  canrel -> Update();
  canrel -> SaveAs("Outputdata/comp_bbnbb_dfl_data_cr_sr_3-4-j_efficiency.pdf");

  canabs -> cd();
  canabs -> SetLogy();
  //TGaxis::SetMaxDigits(3);

  TGraph* gr3jsrAbs = new TGraph(cutflowsteps,cfsteps,val3jsrAbs);
  gr3jsrAbs -> SetTitle();
  gr3jsrAbs -> GetXaxis() -> SetTitle("Cuts");
  gr3jsrAbs -> GetYaxis() -> SetTitle("Events");
  gr3jsrAbs -> GetYaxis() -> SetTitleOffset(1.15);
  gr3jsrAbs -> SetMinimum(100);
  gr3jsrAbs -> SetMarkerStyle(20);
  gr3jsrAbs -> SetLineColor(kRed);
  gr3jsrAbs -> Draw("ALP");
  TGraph* gr3jcrAbs = new TGraph(cutflowsteps,cfsteps,val3jcrAbs);
  gr3jcrAbs -> SetMarkerStyle(26);
  gr3jcrAbs -> SetLineColor(kRed);
  gr3jcrAbs -> Draw("LP");
  TGraph* gr4jsrAbs = new TGraph(cutflowsteps,cfsteps,val4jsrAbs);
  gr4jsrAbs -> SetMarkerStyle(20);
  gr4jsrAbs -> SetLineColor(kBlue);
  gr4jsrAbs -> Draw("LP");
  TGraph* gr4jcrAbs = new TGraph(cutflowsteps,cfsteps,val4jcrAbs);
  gr4jcrAbs -> SetMarkerStyle(26);
  gr4jcrAbs -> SetLineColor(kBlue);
  gr4jcrAbs -> Draw("LP");

  TLegend* legAbs = new TLegend(0.2,0.3,0.7,0.7);
  style.SetLegendStyle(legAbs);
  legAbs -> AddEntry(gr4jsrAbs,"4 jets (bbnbb), SR","LP");
  legAbs -> AddEntry(gr4jcrAbs,"4 jets (bbnbb), CR","LP");
  legAbs -> AddEntry(gr3jsrAbs,"3 jets (bbnbb), SR","LP");
  legAbs -> AddEntry(gr3jcrAbs,"3 jets (bbnbb), CR","LP");
  legAbs -> Draw("SAME");

  canabs -> Update();
  canabs -> SaveAs("Outputdata/comp_bbnbb_dfl_data_cr_sr_3-4-j_NoOfEvents.pdf");
}
