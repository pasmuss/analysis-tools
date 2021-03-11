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
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"

#include "RooWorkspace.h"
#include "RooHist.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooFormulaVar.h"
#include "RooEffProd.h"
#include "RooGenericPdf.h"
#include "RooProdPdf.h"

void DrawSRimpacts(){

  TH1::SetDefaultSumw2();

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TFile* input_f = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR1_300_slstTFb03Larger/fitDiagnosticsHbb_SR1.root","READ");
  RooPlot* input_rp_s = (RooPlot*)input_f->Get("SR_mbb_fit_s");
  RooPlot* input_rpcr_s = (RooPlot*)input_f->Get("CR_mbb_fit_s");
  RooPlot* emptyrp = input_rp_s->emptyClone("emptyrp");
  RooPlot* emptyrpcr = input_rpcr_s->emptyClone("emptyrpcr");
  RooPlot* input_rp_prefit = (RooPlot*)input_f->Get("SR_mbb_prefit");

  //bg fit result (shapeBkg)
  RooCurve* shapeBonly = input_rp_s -> getCurve("pdf_binSR_Norm[mbb]_Comp[shapeBkg*]");
  RooCurve* shapeBonlyCR = input_rpcr_s -> getCurve("pdf_binCR_Norm[mbb]_Comp[shapeBkg*]");
  //s+b result
  RooCurve* shapeSpB = input_rp_s -> getCurve("pdf_binSR_Norm[mbb]");
  RooCurve* shapeSpBCR = input_rpcr_s -> getCurve("pdf_binCR_Norm[mbb]");
  //data hist
  RooHist* datahist = input_rp_s -> getHist("h_SR");
  RooHist* datahistCR = input_rpcr_s -> getHist("h_CR");
  //sig prefit
  RooCurve* sig_prefit = input_rp_prefit -> getCurve("pdf_binSR_Norm[mbb]_Comp[shapeSig*]");
  sig_prefit -> SetLineColor(kGreen);
  for (int i=0; i<sig_prefit->GetN(); i++) sig_prefit->GetY()[i] *= 10;
  //sig result
  RooCurve* sig_result = input_rp_s -> getCurve("pdf_binSR_Norm[mbb]_Comp[shapeSig*]");
  for (int i=0; i<sig_result->GetN(); i++) sig_result->GetY()[i] *= 10;

  //Frames
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
  pad_top -> cd();

  double largetitle = 0.045;
  double largelabel = 0.04;
  double titlesize = largetitle*((1-ydiv)/ydiv);
  double labelsize = largelabel*((1-ydiv)/ydiv);
  double ticksize = (input_rp_s -> GetXaxis() -> GetTickLength()) * ((1-ydiv)/ydiv);
  
  emptyrp -> SetTitle("");
  emptyrp -> GetYaxis() -> SetTitle("Entries / 10 GeV");
  emptyrp -> GetYaxis() -> SetTitleOffset(1.5);
  emptyrp -> GetYaxis() -> SetRangeUser(0,10000);
  emptyrp -> GetXaxis() -> SetTitle("");
  emptyrp -> GetXaxis() -> SetLabelOffset(999);
  emptyrp -> GetXaxis() -> SetNdivisions(505);
  emptyrp -> GetYaxis() -> SetNdivisions(505);
  emptyrp -> Draw();
  shapeBonly -> Draw("SAME");
  shapeSpB -> Draw("SAME");
  datahist -> SetMarkerSize(1);
  datahist -> Draw("pSAME");
  sig_result -> Draw("SAME");
  sig_prefit -> Draw("SAME");

  TLegend* leg = new TLegend(0.65,0.6,0.9,0.9);
  style.SetLegendStyle(leg);
  leg -> AddEntry(shapeBonly,"B only fit result","L");
  leg -> AddEntry(shapeSpB,"S+B fit result","L");
  leg -> AddEntry(datahist, "Data", "PL");
  leg -> AddEntry(sig_prefit, "Signal template * 10","L");
  leg -> AddEntry(sig_result,"Fitted signal * 10","L");
  leg -> Draw("SAME");

  //make pull hist
  //RooHist* pullHist = input_rp_s->pullHist("h_SR","pdf_binSR_Norm[mbb]_Comp[shapeBkg*]");
  RooHist* pullHist = datahist -> makePullHist(*shapeBonly);
  pullHist -> SetMarkerSize(1);

  pad_bot -> cd();
  pullHist -> GetYaxis() -> SetRangeUser(-4.999,5);
  pullHist -> GetYaxis() -> SetNdivisions(505);
  pullHist -> GetYaxis() -> SetTickLength(0.5*ticksize);
  pullHist -> GetXaxis() -> SetTickLength(ticksize);
  pullHist -> GetXaxis() -> SetRangeUser(202,498);
  pullHist -> GetXaxis() -> SetTitle("m_{12} [GeV]");
  pullHist -> GetYaxis() -> SetTitle("Pulls (B only)");
  pullHist -> GetXaxis() -> SetTitleSize(titlesize);
  pullHist -> GetYaxis() -> SetTitleSize(titlesize);
  pullHist -> GetXaxis() -> SetTitleOffset(0.95);
  pullHist -> GetYaxis() -> SetTitleOffset(0.4);
  pullHist -> GetYaxis() -> CenterTitle();
  pullHist -> GetXaxis() -> SetLabelSize(labelsize);
  pullHist -> GetYaxis() -> SetLabelSize(labelsize);
  pullHist -> SetTitle("");
  pullHist -> Draw("ap");

  //pullHist->Print("v");

  TLatex* t200 = new TLatex();
  t200 -> SetTextSize(labelsize);
  t200 -> DrawLatexNDC(0.123,0.2,"200");
  TLatex* t500 = new TLatex();
  t500 -> SetTextSize(labelsize);
  t500 -> DrawLatexNDC(0.925,0.2,"500");
  pad_bot -> Update();

  can -> Update();  
  can -> SaveAs("Outputdata/Pulls/FR1_300_SR_Bonly_Mar04-21.pdf");
  can -> SaveAs("Outputdata/Pulls/FR1_300_SR_Bonly_Mar04-21.root");

  //Frames
  TCanvas* canSB = style.MakeCanvas("canSB","",700,800);
  gStyle -> SetLineWidth(1);
  TPad* pad_botSB = new TPad("pad_botSB","",0.0,0.0,1.0,ydiv);
  pad_botSB -> SetLeftMargin(0.15);
  pad_botSB -> SetBottomMargin(0.3);
  pad_botSB -> Draw();
  TPad* pad_topSB = new TPad("pad_topSB","",0.0,ydiv,1.0,1.0);
  pad_topSB -> Draw();
  pad_topSB -> cd();
  pad_topSB -> SetRightMargin(0.05);
  pad_topSB -> SetLeftMargin(0.15);
  pad_topSB -> SetBottomMargin(0.02);
  pad_topSB -> cd();

  emptyrp -> Draw();
  shapeBonly -> Draw("SAME");
  shapeSpB -> Draw("SAME");
  datahist -> SetMarkerSize(1);
  datahist -> Draw("pSAME");
  sig_result -> Draw("SAME");
  sig_prefit -> Draw("SAME");

  TLegend* legSB = new TLegend(0.65,0.6,0.9,0.9);
  style.SetLegendStyle(legSB);
  legSB -> AddEntry(shapeBonly,"B only fit result","L");
  legSB -> AddEntry(shapeSpB,"S+B fit result","L");
  legSB -> AddEntry(datahist, "Data", "PL");
  legSB -> AddEntry(sig_prefit, "Signal template * 10","L");
  legSB -> AddEntry(sig_result,"Fitted signal * 10","L");
  legSB -> Draw("SAME");

  RooHist* pullHistSB = datahist -> makePullHist(*shapeSpB);
  pullHistSB -> SetMarkerSize(1);

  pad_botSB -> cd();
  pullHistSB -> GetYaxis() -> SetRangeUser(-4.999,5);
  pullHistSB -> GetYaxis() -> SetNdivisions(505);
  pullHistSB -> GetYaxis() -> SetTickLength(0.5*ticksize);
  pullHistSB -> GetXaxis() -> SetTickLength(ticksize);
  pullHistSB -> GetXaxis() -> SetRangeUser(202,498);
  pullHistSB -> GetXaxis() -> SetTitle("m_{12} [GeV]");
  pullHistSB -> GetYaxis() -> SetTitle("Pulls (S+B)");
  pullHistSB -> GetXaxis() -> SetTitleSize(titlesize);
  pullHistSB -> GetYaxis() -> SetTitleSize(titlesize);
  pullHistSB -> GetXaxis() -> SetTitleOffset(0.95);
  pullHistSB -> GetYaxis() -> SetTitleOffset(0.4);
  pullHistSB -> GetYaxis() -> CenterTitle();
  pullHistSB -> GetXaxis() -> SetLabelSize(labelsize);
  pullHistSB -> GetYaxis() -> SetLabelSize(labelsize);
  pullHistSB -> SetTitle("");
  pullHistSB -> Draw("ap");
  
  TLatex* t200SB = new TLatex();
  t200SB -> SetTextSize(labelsize);
  t200SB -> DrawLatexNDC(0.123,0.2,"200");
  TLatex* t500SB = new TLatex();
  t500SB -> SetTextSize(labelsize);
  t500SB -> DrawLatexNDC(0.925,0.2,"500");
  pad_botSB -> Update();

  canSB -> Update();  
  canSB -> SaveAs("Outputdata/Pulls/FR1_300_SR_SB_Mar04-21.pdf");
  canSB -> SaveAs("Outputdata/Pulls/FR1_300_SR_SB_Mar04-21.root");


  ///////////////////////////////////////
  ///////////////////////////////////////
  ///////////////////////////////////////

  //Frames
  TCanvas* canCR = style.MakeCanvas("canCR","",700,800);
  gStyle -> SetLineWidth(1);
  TPad* pad_botCR = new TPad("pad_botCR","",0.0,0.0,1.0,ydiv);
  pad_botCR -> SetLeftMargin(0.15);
  pad_botCR -> SetBottomMargin(0.3);
  pad_botCR -> Draw();
  TPad* pad_topCR = new TPad("pad_topCR","",0.0,ydiv,1.0,1.0);
  pad_topCR -> Draw();
  pad_topCR -> cd();
  pad_topCR -> SetRightMargin(0.05);
  pad_topCR -> SetLeftMargin(0.15);
  pad_topCR -> SetBottomMargin(0.02);
  pad_topCR -> cd();
  
  emptyrpcr -> SetTitle("");
  emptyrpcr -> GetYaxis() -> SetTitle("Entries / 10 GeV");
  emptyrpcr -> GetYaxis() -> SetTitleOffset(1.5);
  emptyrpcr -> GetYaxis() -> SetRangeUser(0,60000);
  emptyrpcr -> GetXaxis() -> SetTitle("");
  emptyrpcr -> GetXaxis() -> SetLabelOffset(999);
  emptyrpcr -> GetXaxis() -> SetNdivisions(505);
  emptyrpcr -> GetYaxis() -> SetNdivisions(505);
  emptyrpcr -> Draw();
  shapeBonlyCR -> Draw("SAME");
  shapeSpBCR -> Draw("SAME");
  datahistCR -> SetMarkerSize(1);
  datahistCR -> Draw("pSAME");

  TLegend* legCR = new TLegend(0.7,0.6,0.9,0.9);
  style.SetLegendStyle(legCR);
  legCR -> AddEntry(shapeBonlyCR,"B only fit result","L");
  legCR -> AddEntry(shapeSpBCR,"S+B fit result","L");
  legCR -> AddEntry(datahistCR, "Data", "PL");
  legCR -> Draw("SAME");

  //make pull hist
  //RooHist* pullHist = input_rp_s->pullHist("h_SR","pdf_binSR_Norm[mbb]_Comp[shapeBkg*]");
  RooHist* pullHistCR = datahistCR -> makePullHist(*shapeBonlyCR);
  pullHistCR -> SetMarkerSize(1);

  pad_botCR -> cd();
  pullHistCR -> GetYaxis() -> SetRangeUser(-4.999,5);
  pullHistCR -> GetYaxis() -> SetNdivisions(505);
  pullHistCR -> GetYaxis() -> SetTickLength(0.5*ticksize);
  pullHistCR -> GetXaxis() -> SetTickLength(ticksize);
  pullHistCR -> GetXaxis() -> SetRangeUser(202,498);
  pullHistCR -> GetXaxis() -> SetTitle("m_{12} [GeV]");
  pullHistCR -> GetYaxis() -> SetTitle("Pulls (B only)");
  pullHistCR -> GetXaxis() -> SetTitleSize(titlesize);
  pullHistCR -> GetYaxis() -> SetTitleSize(titlesize);
  pullHistCR -> GetXaxis() -> SetTitleOffset(0.95);
  pullHistCR -> GetYaxis() -> SetTitleOffset(0.4);
  pullHistCR -> GetYaxis() -> CenterTitle();
  pullHistCR -> GetXaxis() -> SetLabelSize(labelsize);
  pullHistCR -> GetYaxis() -> SetLabelSize(labelsize);
  pullHistCR -> SetTitle("");
  pullHistCR -> Draw("ap");

  //pullHist->Print("v");

  TLatex* t200cr = new TLatex();
  t200cr -> SetTextSize(labelsize);
  t200cr -> DrawLatexNDC(0.123,0.2,"200");
  TLatex* t500cr = new TLatex();
  t500cr -> SetTextSize(labelsize);
  t500cr -> DrawLatexNDC(0.925,0.2,"500");
  pad_botCR -> Update();

  canCR -> Update();  
  canCR -> SaveAs("Outputdata/Pulls/FR1_300_SR_Bonlycr_Mar04-21.pdf");
  canCR -> SaveAs("Outputdata/Pulls/FR1_300_SR_Bonlycr_Mar04-21.root");

  //Frames
  TCanvas* canCRSB = style.MakeCanvas("canCRSB","",700,800);
  gStyle -> SetLineWidth(1);
  TPad* pad_botCRSB = new TPad("pad_botCRSB","",0.0,0.0,1.0,ydiv);
  pad_botCRSB -> SetLeftMargin(0.15);
  pad_botCRSB -> SetBottomMargin(0.3);
  pad_botCRSB -> Draw();
  TPad* pad_topCRSB = new TPad("pad_topCRSB","",0.0,ydiv,1.0,1.0);
  pad_topCRSB -> Draw();
  pad_topCRSB -> cd();
  pad_topCRSB -> SetRightMargin(0.05);
  pad_topCRSB -> SetLeftMargin(0.15);
  pad_topCRSB -> SetBottomMargin(0.02);
  pad_topCRSB -> cd();

  emptyrpcr -> Draw();
  shapeBonlyCR -> Draw("SAME");
  shapeSpBCR -> Draw("SAME");
  datahistCR -> SetMarkerSize(1);
  datahistCR -> Draw("pSAME");

  TLegend* legSBCR = new TLegend(0.7,0.6,0.9,0.9);
  style.SetLegendStyle(legSBCR);
  legSBCR -> AddEntry(shapeBonlyCR,"B only fit result","L");
  legSBCR -> AddEntry(shapeSpBCR,"S+B fit result","L");
  legSBCR -> AddEntry(datahistCR, "Data", "PL");
  legSBCR -> Draw("SAME");

  RooHist* pullHistSBCR = datahistCR -> makePullHist(*shapeSpBCR);
  pullHistSBCR -> SetMarkerSize(1);

  pad_botCRSB -> cd();
  pullHistSBCR -> GetYaxis() -> SetRangeUser(-4.999,5);
  pullHistSBCR -> GetYaxis() -> SetNdivisions(505);
  pullHistSBCR -> GetYaxis() -> SetTickLength(0.5*ticksize);
  pullHistSBCR -> GetXaxis() -> SetTickLength(ticksize);
  pullHistSBCR -> GetXaxis() -> SetRangeUser(202,498);
  pullHistSBCR -> GetXaxis() -> SetTitle("m_{12} [GeV]");
  pullHistSBCR -> GetYaxis() -> SetTitle("Pulls (S+B)");
  pullHistSBCR -> GetXaxis() -> SetTitleSize(titlesize);
  pullHistSBCR -> GetYaxis() -> SetTitleSize(titlesize);
  pullHistSBCR -> GetXaxis() -> SetTitleOffset(0.95);
  pullHistSBCR -> GetYaxis() -> SetTitleOffset(0.4);
  pullHistSBCR -> GetYaxis() -> CenterTitle();
  pullHistSBCR -> GetXaxis() -> SetLabelSize(labelsize);
  pullHistSBCR -> GetYaxis() -> SetLabelSize(labelsize);
  pullHistSBCR -> SetTitle("");
  pullHistSBCR -> Draw("ap");
  
  TLatex* t200SBcr = new TLatex();
  t200SBcr -> SetTextSize(labelsize);
  t200SBcr -> DrawLatexNDC(0.123,0.2,"200");
  TLatex* t500SBcr = new TLatex();
  t500SBcr -> SetTextSize(labelsize);
  t500SBcr -> DrawLatexNDC(0.925,0.2,"500");
  pad_botCRSB -> Update();

  canCRSB -> Update();  
  canCRSB -> SaveAs("Outputdata/Pulls/FR1_300_SR_SBcr_Mar04-21.pdf");
  canCRSB -> SaveAs("Outputdata/Pulls/FR1_300_SR_SBcr_Mar04-21.root");


}
