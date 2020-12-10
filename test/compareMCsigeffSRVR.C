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

void compareMCsigeffSRVR(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  vector<string> nlomasspoints = {"300","350","400","450","500","600","700","800","900","1000","1200","1400","1600"};

  int nlopoints = nlomasspoints.size();

  float nlofloats[nlopoints];

  float nloeffCR[nlopoints];
  float nloeffVR[nlopoints];
  float nloeffSR[nlopoints];

  map<string,TFile*> nlofilesCR;
  map<string,TH1F*> nlohistsCR;
  map<string,TFile*> nlofilesVR;
  map<string,TH1F*> nlohistsVR;
  map<string,TFile*> nlofilesSR;
  map<string,TH1F*> nlohistsSR;
    
  TCanvas* can = style.MakeCanvas("canSR3j", "SR and VR, 3 b tags", 700,700);

  for (unsigned int i = 0; i < nlomasspoints.size(); i++){
    nlofloats[i] = stof(nlomasspoints[i].c_str());

    nlofilesCR[nlomasspoints[i]] = new TFile( ("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/mcsig/mc-sig-"+nlomasspoints[i]+"-NLO-deep-CR-3j.root").c_str() ,"READ");
    nlofilesVR[nlomasspoints[i]] = new TFile( ("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/mcsig/mc-sig-"+nlomasspoints[i]+"-NLO-deep-VR-3j.root").c_str() ,"READ");
    nlofilesSR[nlomasspoints[i]] = new TFile( ("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_asympT_onlMC_triggersfMC_Nov12-19/rootfiles_May11-20_properSubranges_inclMC/mcsig/mc-sig-"+nlomasspoints[i]+"-NLO-deep-SR-3j.root").c_str() ,"READ");

    nlohistsCR[nlomasspoints[i]] = (TH1F*)nlofilesCR[nlomasspoints[i]]->Get("noofevents_w_nlo");
    float scalenloCR = nlohistsCR[nlomasspoints[i]]->GetBinContent(2);
    nlohistsCR[nlomasspoints[i]] -> Scale(1/scalenloCR);
    
    nlohistsVR[nlomasspoints[i]] = (TH1F*)nlofilesVR[nlomasspoints[i]]->Get("noofevents_w_nlo");
    float scalenloVR = nlohistsVR[nlomasspoints[i]]->GetBinContent(2);
    nlohistsVR[nlomasspoints[i]] -> Scale(1/scalenloVR);

    nlohistsSR[nlomasspoints[i]] = (TH1F*)nlofilesSR[nlomasspoints[i]]->Get("noofevents_w_nlo");
    float scalenloSR = nlohistsSR[nlomasspoints[i]]->GetBinContent(2);
    nlohistsSR[nlomasspoints[i]] -> Scale(1/scalenloSR);

    nloeffCR[i] = nlohistsCR[nlomasspoints[i]] -> GetBinContent(9);
    nloeffVR[i] = nlohistsVR[nlomasspoints[i]] -> GetBinContent(9);
    nloeffSR[i] = nlohistsSR[nlomasspoints[i]] -> GetBinContent(9);

    cout << "Entries of vectors for " << nlomasspoints[i] << " GeV mass point (NLO): " << nloeffVR[i] << " " << nloeffSR[i] << endl;
  }
  
  can -> cd();
  can -> SetLogy();

  TGraph* GnloeffVR = new TGraph(nlopoints,nlofloats,nloeffVR);
  GnloeffVR -> SetTitle();
  GnloeffVR -> GetXaxis() -> SetTitle("m_{A/H} [GeV]");
  GnloeffVR -> SetMinimum(0.0000001);
  GnloeffVR -> SetMaximum(1.);
  GnloeffVR -> GetYaxis() -> SetTitle("Efficiency");
  GnloeffVR -> GetYaxis() -> SetTitleOffset(1.28);
  GnloeffVR -> SetTitle();
  GnloeffVR -> SetLineColor(kBlue);
  GnloeffVR -> SetMarkerStyle(20);
  GnloeffVR -> SetLineStyle(1);
  GnloeffVR -> Draw("ACP");
  TGraph* GnloeffSR = new TGraph(nlopoints,nlofloats,nloeffSR);
  GnloeffSR -> SetLineColor(kRed);
  GnloeffSR -> SetMarkerStyle(20);
  GnloeffSR -> SetLineStyle(1);
  GnloeffSR -> Draw("CP");
  TGraph* GnloeffCR = new TGraph(nlopoints,nlofloats,nloeffCR);
  GnloeffCR -> SetLineColor(kGreen);
  GnloeffCR -> SetMarkerStyle(20);
  GnloeffCR -> SetLineStyle(1);
  GnloeffCR -> Draw("CP");

  TLegend* legSR = new TLegend(0.17,0.17,0.92,0.35);
  style.SetLegendStyle(legSR);
  legSR -> SetNColumns(3);
  legSR -> AddEntry(GnloeffCR,"CR (bbnbb)","LP");
  legSR -> AddEntry(GnloeffVR,"VR (bbsbb)","LP");
  legSR -> AddEntry(GnloeffSR,"SR (bbb)","LP");
  legSR -> Draw("SAME");
 
  can -> Update();

  can -> SaveAs("Outputdata/eff_MC-sig_CRVRSR_Nov27-20.pdf");
}
