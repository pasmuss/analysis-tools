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

void compareLOnlo34j_cutflow(){

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  vector<string> nlomasspoints = {"200","250","350","400","450","500","600","700","800","900","1000","1200","1400","1600"/*,"1800","2000"*/};
  //vector<string> lomasspoints  = {            "350",                  "600",                         "1200"};

  int nlopoints = nlomasspoints.size();
  //int lopoints = lomasspoints.size();

  float nlofloats[nlopoints];
  //float lofloats[lopoints];

  //float nloeffCRbc[nlopoints];
  //float nloeffCRac[nlopoints];
  float nloeffSRbc[nlopoints];
  float nloeffSRac[nlopoints];

  //float nloeffCRbc3j[nlopoints];
  //float nloeffCRac3j[nlopoints];
  float nloeffSRbc3j[nlopoints];
  float nloeffSRac3j[nlopoints];

  //float loeffCRbc[lopoints];
  //float loeffCRac[lopoints];
  //float loeffSRbc[lopoints];
  //float loeffSRac[lopoints];

  //float loeffCRbc3j[lopoints];
  //float loeffCRac3j[lopoints];
  //float loeffSRbc3j[lopoints];
  //float loeffSRac3j[lopoints];

  //map<string,TFile*> nlofilesCR3j;
  //map<string,TFile*> lofilesCR3j;
  map<string,TFile*> nlofilesSR3j;
  //map<string,TFile*> lofilesSR3j;

  //map<string,TH1F*> nlohistsCR3j;
  map<string,TH1F*> nlohistsSR3j;
  //map<string,TH1F*> lohistsCR3j;
  //map<string,TH1F*> lohistsSR3j;
  
  //map<string,TFile*> nlofilesCR;
  //map<string,TFile*> lofilesCR;
  map<string,TFile*> nlofilesSR;
  //map<string,TFile*> lofilesSR;

  //map<string,TH1F*> nlohistsCR;
  map<string,TH1F*> nlohistsSR;
  //map<string,TH1F*> lohistsCR;
  //map<string,TH1F*> lohistsSR;
    
  TCanvas* canSR = style.MakeCanvas("canSR", "SR, 4 b jets", 700,700);
  TCanvas* canSR3j = style.MakeCanvas("canSR3j", "SR, 3 b tags", 700,700);
  //TCanvas* canCR = style.MakeCanvas("canCR", "CR", 700,700);

  for (unsigned int i = 0; i < nlomasspoints.size(); i++){
    nlofloats[i] = stof(nlomasspoints[i].c_str());

    //nlofilesCR[nlomasspoints[i]] = new TFile( ("rootfiles_4med_WithMuVeto/mcsig/mc-sig-"+nlomasspoints[i]+"-NLO-deep-CR.root").c_str() ,"READ");
    nlofilesSR[nlomasspoints[i]] = new TFile( ("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dcsv_new-noofevtsweighted/mcsig/mc-sig-"+nlomasspoints[i]+"-NLO-deep-SR.root").c_str() ,"READ");

    //nlofilesCR3j[nlomasspoints[i]] = new TFile( ("rootfiles_4med_WithMuVeto/mcsig/mc-sig-"+nlomasspoints[i]+"-NLO-deep-CR-3j.root").c_str() ,"READ");
    nlofilesSR3j[nlomasspoints[i]] = new TFile( ("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_diffBTags_allmedium/rootfiles_4med_dcsv_new-noofevtsweighted/mcsig/mc-sig-"+nlomasspoints[i]+"-NLO-deep-SR-3j.root").c_str() ,"READ");
    
    //[nlomasspoints[i]] = (TH1F*)nlofilesCR[nlomasspoints[i]]->Get("cutflow");
    //float scalenloCR = nlohistsCR[nlomasspoints[i]]->GetBinContent(1);
    //nlohistsCR[nlomasspoints[i]] -> Scale(1/scalenloCR);
    nlohistsSR[nlomasspoints[i]] = (TH1F*)nlofilesSR[nlomasspoints[i]]->Get("noofevents_w_nlo");
    float scalenloSR = nlohistsSR[nlomasspoints[i]]->GetBinContent(2);
    nlohistsSR[nlomasspoints[i]] -> Scale(1/scalenloSR);

    //nlohistsCR3j[nlomasspoints[i]] = (TH1F*)nlofilesCR3j[nlomasspoints[i]]->Get("cutflow");
    //float scalenloCR3j = nlohistsCR3j[nlomasspoints[i]]->GetBinContent(1);
    //nlohistsCR3j[nlomasspoints[i]] -> Scale(1/scalenloCR3j);
    nlohistsSR3j[nlomasspoints[i]] = (TH1F*)nlofilesSR3j[nlomasspoints[i]]->Get("noofevents_w_nlo");
    float scalenloSR3j = nlohistsSR3j[nlomasspoints[i]]->GetBinContent(2);
    nlohistsSR3j[nlomasspoints[i]] -> Scale(1/scalenloSR3j);

    //nloeffCRbc[i] = nlohistsCR[nlomasspoints[i]]->GetBinContent(5);
    //nloeffCRac[i] = nlohistsCR[nlomasspoints[i]]->GetBinContent(7);

    nloeffSRbc[i] = nlohistsSR[nlomasspoints[i]] -> GetBinContent(6);
    nloeffSRac[i] = nlohistsSR[nlomasspoints[i]] -> GetBinContent(9);

    //nloeffCRbc3j[i] = nlohistsCR3j[nlomasspoints[i]] -> GetBinContent(5);
    //nloeffCRac3j[i] = nlohistsCR3j[nlomasspoints[i]] -> GetBinContent(7);

    nloeffSRbc3j[i] = nlohistsSR3j[nlomasspoints[i]] -> GetBinContent(6);
    nloeffSRac3j[i] = nlohistsSR3j[nlomasspoints[i]] -> GetBinContent(9);

    cout << "Entries of vectors for " << nlomasspoints[i] << " GeV mass point (NLO): " << nloeffSRbc[i] << " " << nloeffSRac[i] << " " << nloeffSRbc3j[i] << " " << nloeffSRac3j[i] << endl;
  }
  
  /*for (unsigned int j = 0; j < lomasspoints.size(); j++){
    lofloats[j] = stof(lomasspoints[j].c_str());

    //lofilesCR[lomasspoints[j]] = new TFile( ("rootfiles_4med_WithMuVeto/mcsig/mc-sig-"+lomasspoints[j]+"-deep-CR.root").c_str() ,"READ");
    lofilesSR[lomasspoints[j]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_allcorrections_nentries_v2/mcsig/mc-sig-"+lomasspoints[j]+"-deep-SR.root").c_str() ,"READ");
   
    //lofilesCR3j[lomasspoints[j]] = new TFile( ("rootfiles_4med_WithMuVeto/mcsig/mc-sig-"+lomasspoints[j]+"-deep-CR-3j.root").c_str() ,"READ");
    lofilesSR3j[lomasspoints[j]] = new TFile( ("Configs_diffBTags_allmedium/rootfiles_4med_allcorrections_nentries_v2/mcsig/mc-sig-"+lomasspoints[j]+"-deep-SR-3j.root").c_str() ,"READ");

    //lohistsCR[lomasspoints[j]] = (TH1F*)lofilesCR[lomasspoints[j]]->Get("cutflow");
    //float scaleloCR = lohistsCR[lomasspoints[j]]->GetBinContent(1);
    //lohistsCR[lomasspoints[j]] -> Scale(1/scaleloCR);
    lohistsSR[lomasspoints[j]] = (TH1F*)lofilesSR[lomasspoints[j]]->Get("cutflow");
    float scaleloSR = lohistsSR[lomasspoints[j]]->GetBinContent(1);
    lohistsSR[lomasspoints[j]] -> Scale(1/scaleloSR);

    //lohistsCR3j[lomasspoints[j]] = (TH1F*)lofilesCR3j[lomasspoints[j]]->Get("cutflow");
    //float scaleloCR3j = lohistsCR3j[lomasspoints[j]]->GetBinContent(1);
    //lohistsCR3j[lomasspoints[j]] -> Scale(1/scaleloCR3j);
    lohistsSR3j[lomasspoints[j]] = (TH1F*)lofilesSR3j[lomasspoints[j]]->Get("cutflow");
    float scaleloSR3j = lohistsSR3j[lomasspoints[j]]->GetBinContent(1);
    lohistsSR3j[lomasspoints[j]] -> Scale(1/scaleloSR3j);

    //loeffCRbc[j] = lohistsCR[lomasspoints[j]] -> GetBinContent(5);
    //loeffCRac[j] = lohistsCR[lomasspoints[j]] -> GetBinContent(7);

    loeffSRbc[j] = lohistsSR[lomasspoints[j]] -> GetBinContent(5);
    loeffSRac[j] = lohistsSR[lomasspoints[j]] -> GetBinContent(7);

    //loeffCRbc3j[j] = lohistsCR3j[lomasspoints[j]] -> GetBinContent(5);
    //loeffCRac3j[j] = lohistsCR3j[lomasspoints[j]] -> GetBinContent(7);

    loeffSRbc3j[j] = lohistsSR3j[lomasspoints[j]] -> GetBinContent(5);
    loeffSRac3j[j] = lohistsSR3j[lomasspoints[j]] -> GetBinContent(7);    

    cout << "Entries of vectors for " << lomasspoints[j] << " GeV mass point (LO): " << loeffSRbc[j] << " " << loeffSRac[j] << " " << loeffSRbc3j[j] << " " << loeffSRac3j[j] << endl;
  }*/
  /*
  canCR -> cd();
  canCR -> SetLogy();
  TGraph* GnloeffCRbc = new TGraph(nlopoints,nlofloats,nloeffCRbc);
  GnloeffCRbc -> SetTitle();
  GnloeffCRbc -> GetXaxis() -> SetTitle("Mass [GeV]");
  GnloeffCRbc -> SetMinimum(0.00001);
  GnloeffCRbc -> SetMaximum(1.);
  GnloeffCRbc -> GetYaxis() -> SetTitle("Efficiency");
  GnloeffCRbc -> GetYaxis() -> SetTitleOffset(1.28);
  GnloeffCRbc -> SetLineColor(kBlue);
  GnloeffCRbc -> SetMarkerStyle(20);
  GnloeffCRbc -> SetLineStyle(1);
  GnloeffCRbc -> Draw("ACP");
  TGraph* GnloeffCRac = new TGraph(nlopoints,nlofloats,nloeffCRac);
  GnloeffCRac -> SetLineColor(kRed);
  GnloeffCRac -> SetMarkerStyle(20);
  GnloeffCRac -> SetLineStyle(1);
  GnloeffCRac -> Draw("CP");

  TGraph* GnloeffCRbc3j = new TGraph(nlopoints,nlofloats,nloeffCRbc3j);
  GnloeffCRbc3j -> SetLineColor(kBlue);
  GnloeffCRbc3j -> SetMarkerStyle(20);
  GnloeffCRbc3j -> SetLineStyle(10);
  GnloeffCRbc3j -> Draw("CP");
  TGraph* GnloeffCRac3j = new TGraph(nlopoints,nlofloats,nloeffCRac3j);
  GnloeffCRac3j -> SetLineColor(kRed);
  GnloeffCRac3j -> SetMarkerStyle(20);
  GnloeffCRac3j -> SetLineStyle(10);
  GnloeffCRac3j -> Draw("CP");
  
  TGraph* GloeffCRbc = new TGraph(lopoints,lofloats,loeffCRbc);
  GloeffCRbc -> SetLineColor(kBlue);
  GloeffCRbc -> SetMarkerStyle(26);
  GloeffCRbc -> SetLineStyle(1);
  GloeffCRbc -> Draw("CP");
  TGraph* GloeffCRac = new TGraph(lopoints,lofloats,loeffCRac);
  GloeffCRac -> SetLineColor(kRed);
  GloeffCRac -> SetMarkerStyle(26);
  GloeffCRac -> SetLineStyle(1);
  GloeffCRac -> Draw("CP");
  
  TGraph* GloeffCRbc3j = new TGraph(lopoints,lofloats,loeffCRbc3j);
  GloeffCRbc3j -> SetLineColor(kBlue);
  GloeffCRbc3j ->SetMarkerStyle(26);
  GloeffCRbc3j -> SetLineStyle(10);
  GloeffCRbc3j -> Draw("CP");
  TGraph* GloeffCRac3j = new TGraph(lopoints,lofloats,loeffCRac3j);
  GloeffCRac3j -> SetLineColor(kRed);
  GloeffCRac3j -> SetMarkerStyle(26);
  GloeffCRac3j -> SetLineStyle(10);
  GloeffCRac3j -> Draw("CP");

  TLegend* legCR = new TLegend(0.271,0.165,0.923,0.349);
  style.SetLegendStyle(legCR);
  legCR -> SetNColumns(2);
  legCR -> AddEntry(GnloeffCRbc,"NLO, 4 b tags, kin. cuts","LP");
  legCR -> AddEntry(GnloeffCRac,"NLO, 4 b tags, all cuts","LP");
  legCR -> AddEntry(GloeffCRbc,"LO, 4 b tags, kin. cuts","LP");
  legCR -> AddEntry(GloeffCRac,"LO, 4 b tags, all cuts","LP");
  legCR -> AddEntry(GnloeffCRbc3j,"NLO, 3 b tags, kin. cuts","LP");
  legCR -> AddEntry(GnloeffCRac3j,"NLO, 3 b tags, all cuts","LP");
  legCR -> AddEntry(GloeffCRbc3j,"LO, 3 b tags, kin. cuts","LP");
  legCR -> AddEntry(GloeffCRac3j,"LO, 3 b tags, all cuts","LP");
  legCR -> Draw("SAME");
 
  canCR -> Update();
  */

  canSR -> cd();
  canSR -> SetLogy();

  TGraph* GnloeffSRbc = new TGraph(nlopoints,nlofloats,nloeffSRbc);
  GnloeffSRbc -> SetTitle();
  GnloeffSRbc -> GetXaxis() -> SetTitle("m_{A/H} [GeV]");
  GnloeffSRbc -> SetMinimum(0.0000001);
  GnloeffSRbc -> SetMaximum(1.);
  GnloeffSRbc -> GetYaxis() -> SetTitle("Efficiency");
  GnloeffSRbc -> GetYaxis() -> SetTitleOffset(1.28);
  GnloeffSRbc -> SetTitle();
  GnloeffSRbc -> SetLineColor(kBlue);
  GnloeffSRbc -> SetMarkerStyle(20);
  GnloeffSRbc -> SetLineStyle(1);
  GnloeffSRbc -> Draw("ACP");
  TGraph* GnloeffSRac = new TGraph(nlopoints,nlofloats,nloeffSRac);
  GnloeffSRac -> SetLineColor(kRed);
  GnloeffSRac -> SetMarkerStyle(20);
  GnloeffSRac -> SetLineStyle(1);
  GnloeffSRac -> Draw("CP");

  /*TGraph* GloeffSRbc = new TGraph(lopoints,lofloats,loeffSRbc);
  GloeffSRbc -> SetLineColor(kBlue);
  GloeffSRbc -> SetMarkerStyle(26);
  GloeffSRbc -> SetLineStyle(7);
  GloeffSRbc -> Draw("CP");
  TGraph* GloeffSRac = new TGraph(lopoints,lofloats,loeffSRac);
  GloeffSRac -> SetLineColor(kRed);
  GloeffSRac -> SetMarkerStyle(26);
  GloeffSRac -> SetLineStyle(7);
  GloeffSRac -> Draw("CP");*/

  TLegend* legSR = new TLegend(0.17,0.17,0.92,0.35);
  style.SetLegendStyle(legSR);
  legSR -> SetNColumns(2);
  legSR -> AddEntry(GnloeffSRbc,"NLO, 4 b tags, kin. cuts","LP");
  legSR -> AddEntry(GnloeffSRac,"NLO, 4 b tags, all cuts","LP");
  //legSR -> AddEntry(GloeffSRbc,"LO, 4 b tags, kin. cuts","LP");
  //legSR -> AddEntry(GloeffSRac,"LO, 4 b tags, all cuts","LP");
  legSR -> Draw("SAME");
 
  canSR -> Update();

  canSR -> SaveAs("Outputdata/btag-algo-comp_dcsv_mmm-m_SR_cut-eff_MC_NLO_incl_neg_weights_from_start-4j.pdf");

  canSR3j -> cd();
  canSR3j -> SetLogy();

  TGraph* GnloeffSRbc3j = new TGraph(nlopoints,nlofloats,nloeffSRbc3j);
  GnloeffSRbc3j -> SetTitle();
  GnloeffSRbc3j -> GetXaxis() -> SetTitle("m_{A/H} [GeV]");
  GnloeffSRbc3j -> SetMinimum(0.0000001);
  GnloeffSRbc3j -> SetMaximum(1.);
  GnloeffSRbc3j -> GetYaxis() -> SetTitle("Efficiency");
  GnloeffSRbc3j -> GetYaxis() -> SetTitleOffset(1.28);
  GnloeffSRbc3j -> SetTitle();
  GnloeffSRbc3j -> SetLineColor(kBlue);
  GnloeffSRbc3j -> SetMarkerStyle(20);
  GnloeffSRbc3j -> SetLineStyle(1);
  GnloeffSRbc3j -> Draw("ACP");
  TGraph* GnloeffSRac3j = new TGraph(nlopoints,nlofloats,nloeffSRac3j);
  GnloeffSRac3j -> SetLineColor(kRed);
  GnloeffSRac3j -> SetMarkerStyle(20);
  GnloeffSRac3j -> SetLineStyle(1);
  GnloeffSRac3j -> Draw("CP");

  /*TGraph* GloeffSRbc3j = new TGraph(lopoints,lofloats,loeffSRbc3j);
  GloeffSRbc3j -> SetLineColor(kBlue);
  GloeffSRbc3j -> SetMarkerStyle(26);
  GloeffSRbc3j -> SetLineStyle(7);
  GloeffSRbc3j -> Draw("CP");
  TGraph* GloeffSRac3j = new TGraph(lopoints,lofloats,loeffSRac3j);
  GloeffSRac3j -> SetLineColor(kRed);
  GloeffSRac3j -> SetMarkerStyle(26);
  GloeffSRac3j -> SetLineStyle(7);
  GloeffSRac3j -> Draw("CP");*/

  TLegend* legSR3j = new TLegend(0.17,0.17,0.92,0.35);
  style.SetLegendStyle(legSR3j);
  legSR3j -> SetNColumns(2);
  legSR3j -> AddEntry(GnloeffSRbc3j,"NLO, 3 b tags, kin. cuts","LP");
  legSR3j -> AddEntry(GnloeffSRac3j,"NLO, 3 b tags, all cuts","LP");
  //legSR3j -> AddEntry(GloeffSRbc3j,"LO, 3 b tags, kin. cuts","LP");
  //legSR3j -> AddEntry(GloeffSRac3j,"LO, 3 b tags, all cuts","LP");
  legSR3j -> Draw("SAME");
 
  canSR3j -> Update();
 
  canSR3j -> SaveAs("Outputdata/btag-algo-comp_dcsv_mmm-m_SR_cut-eff_MC_NLO_incl_neg_weights_from_start-3j.pdf");

}
