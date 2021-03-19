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
#include "RooPlot.h"
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

using namespace RooFit;
using namespace std;

void DrawCMSInfo(const char* energy, const char* status, const bool wip);
void setParameters(const vector<string> parameters, const RooFitResult* fitres, RooWorkspace* pdf_ws_in);
void plotData(const RooPlot* comp, const RooWorkspace* pdf_ws_in, const RooFitResult* fitres, const int nbins, const string subrange, const string binning);

void DrawFitsWithUncert(){

  TH1::SetDefaultSumw2();

  vector<string> parameters = {"bernstein_coefficient_00","bernstein_coefficient_01","bernstein_coefficient_02","bernstein_coefficient_03","bernstein_coefficient_04","bernstein_coefficient_05","bernstein_coefficient_06","offsetTF","slopelinTF","steepnessTF","alpha","slope_novoeff","turnon_novoeff","shapeBkg_QCD_SR_SR__norm"};

  vector<string> parameterssr2 = {"tail","width","peak","par0","offsetTF","slopelinTF","steepnessTF","alphaTF","slope_novoeff","turnon_novoeff","shapeBkg_QCD_SR_SR__norm"};

  vector<string> parameterssr3 = {"tail","width","peak","offsetTF","slopelinTF","steepnessTF","alphTF","shapeBkg_QCD_SR_SR__norm"};

  vector<string> parameterssr4 = {"tail","width","peak","offsetTF","slopelinTF","steepnessTF","shapeBkg_QCD_SR_SR__norm"};

  TFile* input_f = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR1_300_slstTFb03Larger/fitDiagnosticsHbb_SR1.root","READ");
  TFile* pdf_input_f = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR1_300_slstTFb03Larger/datacard_Analysis_toy_SR1_300GeV.root","READ");

  RooPlot* input_rp_s = (RooPlot*)input_f->Get("SR_mbb_fit_s");

  TFile* input_fsr2 = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR2_500_newoffTF/fitDiagnosticsHbb_SR2.root","READ");
  TFile* pdf_input_fsr2 = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR2_500_newoffTF/datacard_Analysis_toy_SR2_500GeV.root","READ");

  TFile* input_fsr3 = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR3_900_freezealpha0/fitDiagnosticsHbb_SR3.root","READ");
  TFile* pdf_input_fsr3 = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR3_900_freezealpha0/datacard_Analysis_toy_SR3_900GeV.root","READ");

  TFile* input_fsr4 = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR4_1400_oldTFset/fitDiagnosticsHbb_SR4.root","READ");
  TFile* pdf_input_fsr4 = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR4_1400_oldTFset/datacard_Analysis_toy_SR4_1400GeV.root","READ");

  RooWorkspace* pdf_ws_in = (RooWorkspace*)pdf_input_f->Get("w");
  RooFitResult* fitres = (RooFitResult*)input_f->Get("fit_s");
  RooFitResult* fitresbg = (RooFitResult*)input_f->Get("fit_b");

  RooWorkspace* pdf_ws_insr2 = (RooWorkspace*)pdf_input_fsr2->Get("w");
  RooFitResult* fitressr2 = (RooFitResult*)input_fsr2->Get("fit_s");
  RooFitResult* fitresbgsr2 = (RooFitResult*)input_fsr2->Get("fit_b");

  RooWorkspace* pdf_ws_insr3 = (RooWorkspace*)pdf_input_fsr3->Get("w");
  RooFitResult* fitressr3 = (RooFitResult*)input_fsr3->Get("fit_s");
  RooFitResult* fitresbgsr3 = (RooFitResult*)input_fsr3->Get("fit_b");

  RooWorkspace* pdf_ws_insr4 = (RooWorkspace*)pdf_input_fsr4->Get("w");
  RooFitResult* fitressr4 = (RooFitResult*)input_fsr4->Get("fit_s");
  RooFitResult* fitresbgsr4 = (RooFitResult*)input_fsr4->Get("fit_b");

  setParameters(parameters,fitres,pdf_ws_in);
  //setParameters(parameterssr2,fitresbgsr2,pdf_ws_insr2);
  //setParameters(parameterssr3,fitresbgsr3,pdf_ws_insr3);
  //setParameters(parameterssr4,fitresbgsr4,pdf_ws_insr4);

  plotData(input_rp_s,pdf_ws_in,fitres,54,"SR1","10");
  //plotData(input_rp_s,pdf_ws_insr2,fitressr2,55,"SR2","15");
  //plotData(input_rp_s,pdf_ws_insr3,fitressr3,54,"SR3","20");
  //plotData(input_rp_s,pdf_ws_insr4,fitressr4,86,"SR4","20");

}

void setParameters(const vector<string> parameters, const RooFitResult* fitresult, RooWorkspace* pdf_ws_in){
  for (int par = 0; par<parameters.size(); par++){
    RooRealVar* intermediate = (RooRealVar*)fitresult->floatParsInit().find(parameters[par].c_str());
    if (intermediate) cout << parameters[par] << " initial value: " << intermediate->getVal();
    RooRealVar* resulting = (RooRealVar*)fitresult->floatParsFinal().find(parameters[par].c_str());
    if (resulting){
      double resvalue = resulting->getVal();
      cout << " " << parameters[par] << " final value: " << resvalue << endl;
      double borderlow = pdf_ws_in -> var(parameters[par].c_str()) -> getMin();
      double borderhigh = pdf_ws_in -> var(parameters[par].c_str()) -> getMax();
      if (resvalue < borderlow) pdf_ws_in -> var(parameters[par].c_str()) -> setMin(resvalue);
      else if (resvalue > borderhigh) pdf_ws_in -> var(parameters[par].c_str()) -> setMax(resvalue);
      else cout << "Fit result inside original borders" << endl;
      pdf_ws_in -> var(parameters[par].c_str()) -> setVal(resvalue);
      cout << "New value: " << pdf_ws_in -> var(parameters[par].c_str()) -> getVal() << endl;
    }
  }  
}

void DrawCMSInfo(const char* energy, const char* status, const bool wip){
  TPaveText* CMS = new TPaveText(0.148,0.933,0.2,0.99,"NDC");
  CMS->SetBorderSize(0);
  CMS->SetFillStyle(0);
  CMS->SetTextAlign(11);
  CMS->SetTextSize (0.05);
  CMS->SetTextColor(1);
  CMS->SetTextFont (62);
  CMS->AddText("CMS");
  CMS->Draw();

  TPaveText* STATUS = new TPaveText(0.24,0.933,0.40,0.99,"NDC");
  STATUS->SetBorderSize(0);
  STATUS->SetFillStyle(0);
  STATUS->SetTextAlign(11);
  STATUS->SetTextSize (0.04);
  STATUS->SetTextColor(1);
  STATUS->SetTextFont (52);
  STATUS->AddText(status);
  //STATUS->Draw();

  if (wip){
    TPaveText* INPROGRESS = new TPaveText(0.23,0.933,0.5,0.99,"NDC");
    INPROGRESS->SetBorderSize(0);
    INPROGRESS->SetFillStyle(0);
    INPROGRESS->SetTextAlign(11);
    INPROGRESS->SetTextSize (0.035);
    INPROGRESS->SetTextColor(1);
    INPROGRESS->SetTextFont (42);
    INPROGRESS->AddText("Work in progress");
    INPROGRESS->Draw();
  }

  TPaveText* ENERGY = new TPaveText(0.844,0.933,0.875,0.99,"NDC");
  ENERGY->SetBorderSize(0);
  ENERGY->SetFillStyle(0);
  ENERGY->SetTextAlign(11);
  ENERGY->SetTextSize (0.035);
  ENERGY->SetTextColor(1);
  ENERGY->SetTextFont (42);
  ENERGY->AddText(energy);
  ENERGY->Draw();

  TPaveText* LUMINOSITY = new TPaveText(0.735,0.933,0.875,0.99,"NDC");
  LUMINOSITY->SetBorderSize(0);
  LUMINOSITY->SetFillStyle(0);
  LUMINOSITY->SetTextAlign(11);
  LUMINOSITY->SetTextSize (0.035);
  LUMINOSITY->SetTextColor(1);
  LUMINOSITY->SetTextFont (42);
  LUMINOSITY->AddText("36.0 fb^{-1}");
  LUMINOSITY->Draw();
}

void plotData(const RooPlot* comp, const RooWorkspace* pdf_ws_in, const RooFitResult* fitres, const int nbins, const string subrange, const string binning){
  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  bool logy = false;

  int xlow = 200; int xhigh = 500; int nbinsx = 30;
  if (subrange == "SR2") {xlow = 260; xhigh = 785; nbinsx = 35;}
  if (subrange == "SR3") {xlow = 390; xhigh = 1270; nbinsx = 44; logy = true;}
  if (subrange == "SR4") {xlow = 500; xhigh = 2000; nbinsx = 75; logy = true;}

  RooRealVar mbb("mbb","m_{12}",xlow,xhigh);
  RooPlot* plot = mbb.frame(Bins(nbinsx));

  double ydiv = 0.25;
  double largetitle = 0.045;
  double largelabel = 0.04;
  double titlesize = largetitle*((1-ydiv)/ydiv);
  double labelsize = largelabel*((1-ydiv)/ydiv);
  double ticksize = (comp -> GetXaxis() -> GetTickLength()) * ((1-ydiv)/ydiv);

  plot -> SetTitle("");
  plot -> GetYaxis() -> SetTitle(("Entries / " + binning + " GeV").c_str());
  plot -> GetYaxis() -> SetTitleOffset(1.5);
  plot -> GetYaxis() -> SetTitleSize(largetitle);
  plot -> GetYaxis() -> SetLabelSize(largelabel);
  plot -> GetYaxis() -> SetRangeUser(0.1,10000);
  plot -> GetXaxis() -> SetTitle("");
  plot -> GetXaxis() -> SetLabelOffset(999);
  plot -> GetXaxis() -> SetNdivisions(505);
  plot -> GetYaxis() -> SetNdivisions(505);

  RooAbsPdf* bg_pdf = pdf_ws_in->pdf("shapeBkg_QCD_SR_SR");
  bg_pdf->SetName("bg_pdf");
  TCanvas* can = style.MakeCanvas("can","",700,800);
  gStyle -> SetLineWidth(1);
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

  RooAbsData* data_obs = pdf_ws_in->data("data_obs");
  RooRealVar n_bkg("n_bkg","",pdf_ws_in->var("shapeBkg_QCD_SR_SR__norm")->getVal());
  bg_pdf -> plotOn(plot,
		   VisualizeError(*fitres,2,true),
		   FillColor(kOrange),
		   Normalization(n_bkg.getVal(), RooAbsReal::NumEvent),
		   Name("bg_pdf_2sigma") );
  bg_pdf -> plotOn(plot,
                   VisualizeError(*fitres,1,true),
                   FillColor(kGreen+1),
                   Normalization(n_bkg.getVal(), RooAbsReal::NumEvent),
                   Name("bg_pdf_1sigma") );
  bg_pdf -> plotOn(plot,
                   LineColor(kBlue),
                   Normalization(n_bkg.getVal(), RooAbsReal::NumEvent),
		   Name("bg_pdf") );
  data_obs->plotOn(plot,
		   Cut("CMS_channel==0"),
		   Name("data_obs_sr") );
  plot -> Draw();

  if (logy) {plot -> GetYaxis() -> SetRangeUser(0.1,10000); pad_top -> SetLogy();};

  TGraph* dummy1 = new TGraph();
  dummy1 -> SetFillColor(kGreen+1); dummy1 -> SetLineColor(kGreen+1);
  TGraph* dummy2 = new TGraph();
  dummy2 -> SetFillColor(kOrange); dummy2 -> SetLineColor(kOrange);
  TGraph* dummy = new TGraph();
  dummy -> SetMarkerStyle(20);
  TGraph* dummy3 = new TGraph();
  dummy3 -> SetLineWidth(3);
  dummy3 -> SetLineColor(kBlue);

  TLegend* legtop = new TLegend(0.7,0.7,0.9,0.9);
  style.SetLegendStyle(legtop);
  legtop -> AddEntry(dummy,"Data","PE");
  legtop -> AddEntry(dummy3,"Background","L");
  legtop -> AddEntry(dummy1,"#pm 1 #sigma","F");
  legtop -> AddEntry(dummy2,"#pm 2 #sigma","F");
  legtop -> Draw("SAME");

  DrawCMSInfo("(13 TeV)","Simulation",true);

  pad_bot->cd();  

  auto* h_rebinned = data_obs->createHistogram("h_data_obs_rebinned", mbb, RooFit::Binning( nbins , mbb.getMin(), mbb.getMax()) );
  TH1F* hdummy = new TH1F("hdummy", "", h_rebinned->GetNbinsX(), h_rebinned->GetXaxis()->GetXmin(), h_rebinned->GetXaxis()->GetXmax());

  TH1F* hbkg = new TH1F("hbkg", "", h_rebinned->GetNbinsX(), h_rebinned->GetXaxis()->GetXmin(), h_rebinned->GetXaxis()->GetXmax());
  hbkg->SetFillColor(kAzure+1);
  hbkg->SetLineColor(kAzure+1);
  hbkg->SetFillStyle(3001);

  TH1F* h1sigmaU = new TH1F("h1sigmaU", "", h_rebinned->GetNbinsX(), h_rebinned->GetXaxis()->GetXmin(), h_rebinned->GetXaxis()->GetXmax());
  h1sigmaU->SetFillColor(kGreen+1);
  h1sigmaU->SetLineColor(kGreen+1);
  h1sigmaU->SetFillStyle(1001);

  TH1F* h1sigmaD = new TH1F("h1sigmaD", "", h_rebinned->GetNbinsX(), h_rebinned->GetXaxis()->GetXmin(), h_rebinned->GetXaxis()->GetXmax());
  h1sigmaD->SetFillColor(kGreen+1);
  h1sigmaD->SetLineColor(kGreen+1);
  h1sigmaD->SetFillStyle(1001);

  TH1F* h2sigmaU = new TH1F("h2sigmaU", "", h_rebinned->GetNbinsX(), h_rebinned->GetXaxis()->GetXmin(), h_rebinned->GetXaxis()->GetXmax());
  h2sigmaU->SetFillColor(kOrange);
  h2sigmaU->SetLineColor(kOrange);
  h2sigmaU->SetFillStyle(1001);

  TH1F* h2sigmaD = new TH1F("h2sigmaD", "", h_rebinned->GetNbinsX(), h_rebinned->GetXaxis()->GetXmin(), h_rebinned->GetXaxis()->GetXmax());
  h2sigmaD->SetFillColor(kOrange);
  h2sigmaD->SetLineColor(kOrange);
  h2sigmaD->SetFillStyle(1001);

  cout << "bins mbb: " << mbb.numBins() << endl;

  RooPlot* pullframe = mbb.frame();

  auto *sigma2 = plot->getCurve("bg_pdf_2sigma");
  auto *sigma1 = plot->getCurve("bg_pdf_1sigma");
  auto *nominal = plot->getCurve("bg_pdf");

  TGraph up1Bound(nominal->GetN());
  TGraph lo1Bound(nominal->GetN());
  TGraph up2Bound(nominal->GetN());
  TGraph lo2Bound(nominal->GetN());
  double err1U,err1D,err2U,err2D;

  for( int j = 0; j < sigma2->GetN(); ++j ){
    if( j < nominal->GetN() ){
      up1Bound.SetPoint(j, sigma1->GetX()[j], sigma1->GetY()[j]);
      up2Bound.SetPoint(j, sigma2->GetX()[j], sigma2->GetY()[j]);
    }
    else{
      lo1Bound.SetPoint(j, sigma1->GetX()[j], sigma1->GetY()[j]);
      lo2Bound.SetPoint(j, sigma2->GetX()[j], sigma2->GetY()[j]);
    }
  }

  int k = 0;

  for( int j = 0; j < nominal->GetN(); ++j ){
    double x = nominal->GetX()[j];
    auto bin_i = h1sigmaU->FindBin( x );
    if(bin_i <= 0 || bin_i > h1sigmaU->GetNbinsX()) continue;
    ++k;

    auto n_i = nominal->Eval(x);
    auto n_1up_i = up1Bound.Eval(x);
    auto n_1down_i = lo1Bound.Eval(x);
    auto n_2up_i = up2Bound.Eval(x);
    auto n_2down_i = lo2Bound.Eval(x);

    //Fill band histograms
    err1U = (-n_i+n_1up_i)  ;
    err1D = (-n_i+n_1down_i);
    err2U = (-n_i+n_2up_i)  ;
    err2D = (-n_i+n_2down_i);

    err1U /= sqrt(n_i);
    err1D /= sqrt(n_i);
    err2U /= sqrt(n_i);
    err2D /= sqrt(n_i);

    h1sigmaU->SetBinContent( k, err1U);
    h1sigmaD->SetBinContent( k, err1D);
    h2sigmaU->SetBinContent( k, err2U);
    h2sigmaD->SetBinContent( k, err2D);
    cout << "bin number: " << k << endl;
  }

  pullframe->addTH1(h2sigmaU,"C");
  pullframe->addTH1(h2sigmaD,"C");
  pullframe->addTH1(h1sigmaU,"C");
  pullframe->addTH1(h1sigmaD,"C");

  //parameters sr 1
  if (subrange == "SR1"){
  vector<string> parameters = {"bernstein_coefficient_00","bernstein_coefficient_01","bernstein_coefficient_02","bernstein_coefficient_03","bernstein_coefficient_04","bernstein_coefficient_05","bernstein_coefficient_06","offsetTF","slopelinTF","steepnessTF","alpha","slope_novoeff","turnon_novoeff","shapeBkg_QCD_SR_SR__norm"};

  TFile* input_f = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR1_300_slstTFb03Larger/fitDiagnosticsHbb_SR1.root","READ");
  TFile* pdf_input_f = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_10_2_13/src/Combine/AnalysisLimits/SR_unblinded/SR1_300_slstTFb03Larger/datacard_Analysis_toy_SR1_300GeV.root","READ");

  RooWorkspace* pdf_ws_in = (RooWorkspace*)pdf_input_f->Get("w");
  RooFitResult* fitresbg = (RooFitResult*)input_f->Get("fit_b");

    for (int par = 0; par<parameters.size(); par++){
      RooRealVar* intermediate = (RooRealVar*)fitresbg->floatParsInit().find(parameters[par].c_str());
      if (intermediate) cout << parameters[par] << " initial value: " << intermediate->getVal();
      RooRealVar* resulting = (RooRealVar*)fitresbg->floatParsFinal().find(parameters[par].c_str());
      if (resulting){
	double resvalue = resulting->getVal();
	cout << " " << parameters[par] << " final value: " << resvalue << endl;
	double borderlow = pdf_ws_in -> var(parameters[par].c_str()) -> getMin();
	double borderhigh = pdf_ws_in -> var(parameters[par].c_str()) -> getMax();
	if (resvalue < borderlow) pdf_ws_in -> var(parameters[par].c_str()) -> setMin(resvalue);
	else if (resvalue > borderhigh) pdf_ws_in -> var(parameters[par].c_str()) -> setMax(resvalue);
	else cout << "Fit result inside original borders" << endl;
      pdf_ws_in -> var(parameters[par].c_str()) -> setVal(resvalue);
      cout << "New value: " << pdf_ws_in -> var(parameters[par].c_str()) -> getVal() << endl;
      }
    }
    pad_top -> cd();
    bg_pdf -> plotOn(plot,
		     LineColor(kBlue),
		     Normalization(n_bkg.getVal(), RooAbsReal::NumEvent),
		     Name("bg_pdf") );
    data_obs->plotOn(plot,
		     Cut("CMS_channel==0"),
		     Name("data_obs_sr") );
    plot -> Draw();
    
    legtop -> Draw("SAME");
    DrawCMSInfo("(13 TeV)","Simulation",true);

    pad_bot -> cd();
  }
  
  auto* hpull = plot->pullHist("data_obs_sr","bg_pdf");
  hpull -> GetYaxis() -> SetRangeUser(-5,5);

  pullframe -> Draw();
  hpull -> Draw("PSAME");
  pullframe -> SetTitle("");
  pullframe -> GetYaxis() -> SetTitle("#frac{Data - Bkg}{#sqrt{Bkg}}");
  pullframe -> GetXaxis() -> SetTitle("m_{12} [GeV]");
  pullframe -> GetXaxis() -> SetTitleOffset(1.05);
  pullframe -> GetYaxis() -> SetTitleOffset(0.4);
  pullframe -> GetYaxis() -> CenterTitle();
  pullframe -> GetYaxis() -> SetRangeUser(-3.999,3.999);
  pullframe -> GetYaxis() -> SetNdivisions(404);
  pullframe -> GetYaxis() -> SetTickLength(0.5*ticksize);
  pullframe -> GetXaxis() -> SetTickLength(ticksize);
  pullframe -> GetXaxis() -> SetTitleSize(titlesize);
  pullframe -> GetYaxis() -> SetTitleSize(titlesize);
  pullframe -> GetXaxis() -> SetLabelSize(labelsize);
  pullframe -> GetYaxis() -> SetLabelSize(labelsize);

  TLine* line = new TLine(xlow,0,xhigh,0);  
  line -> SetLineStyle(7);
  line -> Draw("SAME");

  can -> SaveAs(("Outputdata/Pulls_" + subrange + "_bonly_withUncert.pdf").c_str());
  can -> SaveAs(("Outputdata/Pulls_" + subrange + "_bonly_withUncert.root").c_str());
}
