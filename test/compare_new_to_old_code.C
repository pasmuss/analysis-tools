#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

void compare_new_to_old_code(){
  HbbStylesNew style;
  style.SetStyle();

  //Definition of files (three or four jets required, respectively, all CR)
  TFile* threeold = new TFile("Configs_diffBTags_allmedium/rootfiles_4med_incl_PUweights_Jul12-19/rereco/rereco-CDEF-deep-CR.root","READ");
  TFile* threenew = new TFile("Configs_diffBTags_allmedium/rootfiles_4med_pT110-100_Sep02-19/rereco/rereco-CDEF-deep-CR.root","READ");
  //TFile* fourold = new TFile("Archive_NAF/ResultsJul13-mediumwp-4jets/rootfiles/rereco/rereco-CDEF-deep-CR.root","READ");
  //TFile* fournew = new TFile("StandardConfig_4jets_bmedium_nbloose_pT1001004040_deta1p5_dRij1/rootfiles/rereco/rereco-CDEF-deep-CR.root","READ");

  //Histograms: pt1, pt2, m12 (all after cuts)
  /*TH1F* pt1_threeold = (TH1F*)threeold->Get("pt_0_csv");
  TH1F* pt1_threenew = (TH1F*)threenew->Get("pt_0_csv");
  TH1F* pt1_fourold = (TH1F*)fourold->Get("pt_0_csv");
  TH1F* pt1_fournew = (TH1F*)fournew->Get("pt_0_csv");

  TH1F* pt2_threeold = (TH1F*)threeold->Get("pt_1_csv");
  TH1F* pt2_threenew = (TH1F*)threenew->Get("pt_1_csv");
  TH1F* pt2_fourold = (TH1F*)fourold->Get("pt_1_csv");
  TH1F* pt2_fournew = (TH1F*)fournew->Get("pt_1_csv");
  */
  TH1F* m12_threeold = (TH1F*)threeold->Get("m12_aac");
  TH1F* m12_threenew = (TH1F*)threenew->Get("m12_aac");
  //TH1F* m12_fourold = (TH1F*)fourold->Get("m12_csv");
  //TH1F* m12_fournew = (TH1F*)fournew->Get("m12_csv");
  /*
  //pt1
  TCanvas* pt1threecan = style.MakeCanvas("pt1threecan","pt1threecan",700,700);
  pt1threecan -> SetLogy();
  style.InitHist(pt1_threeold,"p_{T}, 1^{st} jet","Entries",kBlack,0);
  pt1_threeold->Draw();
  style.InitHist(pt1_threenew,"p_{T}, 1^{st} jet","Entries",kRed,0);
  pt1_threenew->Draw("SAME");
    
  TLegend* pt1threeleg = new TLegend(0.35,0.65,0.8,0.9);
  style.SetLegendStyle(pt1threeleg);
  pt1threeleg->AddEntry(pt1_threeold,"old code (3 jet category)","L");
  pt1threeleg->AddEntry(pt1_threenew,"new code (3 jet category)","L");
  pt1threeleg->Draw("SAME");

  pt1_threeold -> GetXaxis() -> SetNdivisions(505);
  pt1threecan -> Update();
  pt1threecan -> SaveAs("comp_old_new_code_pt1_3jetcat.pdf");

  TCanvas* pt1fourcan = style.MakeCanvas("pt1fourcan","pt1fourcan",700,700);
  pt1fourcan -> SetLogy();
  style.InitHist(pt1_fourold,"p_{T}, 1^{st} jet","Entries",kBlack,0);
  pt1_fourold->Draw();
  style.InitHist(pt1_fournew,"p_{T}, 1^{st} jet","Entries",kRed,0);
  pt1_fournew->Draw("SAME");
    
  TLegend* pt1fourleg = new TLegend(0.35,0.65,0.8,0.9);
  style.SetLegendStyle(pt1fourleg);
  pt1fourleg->AddEntry(pt1_fourold,"old code (4 jet category)","L");
  pt1fourleg->AddEntry(pt1_fournew,"new code (4 jet category)","L");
  pt1fourleg->Draw("SAME");

  pt1_fourold -> GetXaxis() -> SetNdivisions(505);
  pt1fourcan -> Update();
  pt1fourcan -> SaveAs("comp_old_new_code_pt1_4jetcat.pdf");

  //pt2
  TCanvas* pt2threecan = style.MakeCanvas("pt2threecan","pt2threecan",700,700);
  pt2threecan -> SetLogy();
  style.InitHist(pt2_threeold,"p_{T}, 2^{nd} jet","Entries",kBlack,0);
  pt2_threeold->Draw();
  style.InitHist(pt2_threenew,"p_{T}, 2^{nd} jet","Entries",kRed,0);
  pt2_threenew->Draw("SAME");
    
  TLegend* pt2threeleg = new TLegend(0.35,0.65,0.8,0.9);
  style.SetLegendStyle(pt2threeleg);
  pt2threeleg->AddEntry(pt2_threeold,"old code (3 jet category)","L");
  pt2threeleg->AddEntry(pt2_threenew,"new code (3 jet category)","L");
  pt2threeleg->Draw("SAME");

  pt2_threeold -> GetXaxis() -> SetNdivisions(505);
  pt2threecan -> Update();
  pt2threecan -> SaveAs("comp_old_new_code_pt2_3jetcat.pdf");

  TCanvas* pt2fourcan = style.MakeCanvas("pt2fourcan","pt2fourcan",700,700);
  pt2fourcan -> SetLogy();
  style.InitHist(pt2_fourold,"p_{T}, 2^{nd} jet","Entries",kBlack,0);
  pt2_fourold->Draw();
  style.InitHist(pt2_fournew,"p_{T}, 2^{nd} jet","Entries",kRed,0);
  pt2_fournew->Draw("SAME");
    
  TLegend* pt2fourleg = new TLegend(0.35,0.65,0.8,0.9);
  style.SetLegendStyle(pt2fourleg);
  pt2fourleg->AddEntry(pt2_fourold,"old code (4 jet category)","L");
  pt2fourleg->AddEntry(pt2_fournew,"new code (4 jet category)","L");
  pt2fourleg->Draw("SAME");

  pt2_fourold -> GetXaxis() -> SetNdivisions(505);
  pt2fourcan -> Update();
  pt2fourcan -> SaveAs("comp_old_new_code_pt2_4jetcat.pdf");
*/
  //m12
  TCanvas* m12threecan = style.MakeCanvas("m12threecan","m12threecan",700,700);
  m12threecan -> SetLogy();
  style.InitHist(m12_threeold,"m_{12} [GeV]","Entries / 20 GeV",kBlack,0);
  m12_threeold -> GetXaxis() -> SetRangeUser(0,2000);
  m12_threeold -> SetNdivisions(505);
  m12_threeold->Draw();
  style.InitHist(m12_threenew,"m_{12} [GeV]","Entries / 20 GeV",kRed,0);
  m12_threenew->Draw("SAME");
    
  TLegend* m12threeleg = new TLegend(0.54,0.65,0.98,0.9);
  style.SetLegendStyle(m12threeleg);
  m12threeleg->AddEntry(m12_threeold,"p_{T}^{(1,2)} > 100/100","L");
  m12threeleg->AddEntry(m12_threenew,"p_{T}^{(1,2)} > 110/100","L");
  m12threeleg->Draw("SAME");

  m12threecan -> Update();
  m12threecan -> SaveAs("comp_old_new_code_m12_3jetcat_pt-110-100.pdf");
  /*
  TCanvas* m12fourcan = style.MakeCanvas("m12fourcan","m12fourcan",700,700);
  m12fourcan -> SetLogy();
  style.InitHist(m12_fourold,"m_{12}","Entries",kBlack,0);
  m12_fourold->Draw();
  style.InitHist(m12_fournew,"m_{12}","Entries",kRed,0);
  m12_fournew->Draw("SAME");
    
  TLegend* m12fourleg = new TLegend(0.35,0.65,0.8,0.9);
  style.SetLegendStyle(m12fourleg);
  m12fourleg->AddEntry(m12_fourold,"old code (4 jet category)","L");
  m12fourleg->AddEntry(m12_fournew,"new code (4 jet category)","L");
  m12fourleg->Draw("SAME");

  m12fourcan -> Update();
  m12fourcan -> SaveAs("comp_old_new_code_m12_4jetcat.pdf");
  */
}
