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

  TFile* file3jsr = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rereco/rereco-CDEF-deep-SR-3j.root","READ");
  TFile* file3jvr = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rereco/rereco-CDEF-deep-VR-3j.root","READ");
  TFile* file3jcr = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/rereco/rereco-CDEF-deep-CR-3j.root","READ");

  TH1F* hist3jsrRel = (TH1F*)file3jsr->Get("cutflow");
  TH1F* hist3jcrRel = (TH1F*)file3jcr->Get("cutflow");
  TH1F* hist3jvrRel = (TH1F*)file3jvr->Get("cutflow");

  TH1F* hist3jsrAbs = (TH1F*)file3jsr->Get("noofevents_h");
  TH1F* hist3jcrAbs = (TH1F*)file3jcr->Get("noofevents_h");
  TH1F* hist3jvrAbs = (TH1F*)file3jvr->Get("noofevents_h");

  float scalefactor = hist3jsrRel->GetBinContent(1);

  hist3jsrRel -> Scale(1/scalefactor);
  hist3jcrRel -> Scale(1/scalefactor);
  hist3jvrRel -> Scale(1/scalefactor);

  //Absolute number must not be scaled - only relative should be normalized to one!

  float val3jsrRel[cutflowsteps];
  float val3jcrRel[cutflowsteps];
  float val3jvrRel[cutflowsteps];

  float val3jsrAbs[cutflowsteps];
  float val3jcrAbs[cutflowsteps];
  float val3jvrAbs[cutflowsteps];

  float cfsteps[cutflowsteps];

  for (unsigned int i; i < cutflowsteps; i++){
    val3jsrRel[i] = hist3jsrRel->GetBinContent(i+1);
    val3jcrRel[i] = hist3jcrRel->GetBinContent(i+1);
    val3jvrRel[i] = hist3jvrRel->GetBinContent(i+1);

    cfsteps[i] = i;

    val3jsrAbs[i] = hist3jsrAbs->GetBinContent(i+2);
    val3jcrAbs[i] = hist3jcrAbs->GetBinContent(i+2);
    val3jvrAbs[i] = hist3jvrAbs->GetBinContent(i+2);
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
  TGraph* gr3jvrRel = new TGraph(cutflowsteps,cfsteps,val3jvrRel);
  gr3jvrRel -> SetMarkerStyle(31);
  gr3jvrRel -> SetLineColor(kRed);
  gr3jvrRel -> Draw("LP");

  TLegend* legRel = new TLegend(0.2,0.3,0.7,0.7);
  style.SetLegendStyle(legRel);
  legRel -> AddEntry(gr3jsrRel,"SR (bbb)","LP");
  legRel -> AddEntry(gr3jvrRel,"VR (bbsb)","LP");
  legRel -> AddEntry(gr3jcrRel,"CR (bbnb)","LP");
  legRel -> Draw("SAME");

  canrel -> Update();
  canrel -> SaveAs("Outputdata/comp_CRVRSR_efficiency_Nov24-20.pdf");

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
  TGraph* gr3jvrAbs = new TGraph(cutflowsteps,cfsteps,val3jvrAbs);
  gr3jvrAbs -> SetMarkerStyle(31);
  gr3jvrAbs -> SetLineColor(kRed);
  gr3jvrAbs -> Draw("LP");

  TLegend* legAbs = new TLegend(0.2,0.3,0.7,0.7);
  style.SetLegendStyle(legAbs);
  legAbs -> AddEntry(gr3jsrAbs,"SR (bbb)","LP");
  legAbs -> AddEntry(gr3jvrAbs,"VR (bbsb)","LP");
  legAbs -> AddEntry(gr3jcrAbs,"CR (bbnb)","LP");
  legAbs -> Draw("SAME");

  canabs -> Update();
  canabs -> SaveAs("Outputdata/comp_CRVRSR_NoOfEvents_Nov24-20.pdf");
}
