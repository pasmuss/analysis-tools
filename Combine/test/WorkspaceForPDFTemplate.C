#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

#include "TH1.h"
#include "TStyle.h"
#include "TMath.h"
#include <iostream>

#include "RooWorkspace.h"

#include "HbbStylesNew.cc"

using namespace std;

void WorkspaceForPDFTemplate(){

  // As usual, load the combine library to get access to the RooParametricHist
  gSystem->Load("libHiggsAnalysisCombinedLimit.so");
  
  //Get input data
  TFile* fIn = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Outputdata/TF_bias/Pseudos_10GeVBins_Sig500EvtsMu400Sig102222.root","READ");

  // A search in a mbb tail, define mbb as our variable
  RooRealVar mbb("mbb","m_{12}",200,500);//SR 1
  RooArgList vars(mbb);

  TH1F* CRHist_SR1 = (TH1F*)fIn->Get("CRHist_SR1");//data_obs CR
  CRHist_SR1 -> SetName("CRHist_SR1");
  RooDataHist RDHCR("RDHCR","CR",vars,CRHist_SR1);

  TH1F* SRHist_SR1 = (TH1F*)fIn->Get("SRHist_SR1");//data_obs SR
  RooDataHist RDHSR("RDHSR","SR",vars,SRHist_SR1);

  TH1F* SigSRHist = (TH1F*)fIn->Get("SigSRHist");//data_obs SR including Gaussian signal
  SigSRHist -> SetName("SigSRHist");
  RooDataHist RDHSigSR("RDHSigSR","SR + Signal",vars,SigSRHist);

  TH1F* SignalHist = (TH1F*)fIn->Get("SignalHist");//signal
  RooDataHist RDHSig("RDHSig","Signal",vars,SignalHist);

  //RooRealVar normTF("normTF","normalization of TF",0.16,0,1);
  RooRealVar offsetTF("offsetTF","offset of TF in x direction",93,90,100);
  RooRealVar steepnessTF("steepnessTF","Steepness of rise in TF",7.5e-3,5e-3,1e-2);
  RooRealVar slopelinTF("slopelinTF","Slope of linear part of TF",-1.5e-4,-3e-4,-1e-5);
  RooArgList varsTF(mbb,offsetTF,steepnessTF,slopelinTF);
  RooGenericPdf TF("TF","TF","TMath::Erf(steepnessTF*(mbb-offsetTF))*(1+slopelinTF*mbb)",varsTF);
  //RooRealVar TF_norm("TF_norm","ratio of SR/CR",RDHSR.sumEntries()/RDHCR.sumEntries(),0.0,1.0);
  //TF_norm.setConstant();

  TFile* f_bgfit = new TFile("/nfs/dust/cms/user/asmusspa/private/CMSSW_9_2_15/src/Analysis/Models/results/BG-CR-3j_SR1/BernsteinEffProd7-1/200to500/workspace/FitContainer_workspace.root","READ");
  RooWorkspace* w_bgfit = (RooWorkspace*)f_bgfit->Get("workspace");
  RooAbsPdf* p_bgfit = w_bgfit -> pdf("background");
  p_bgfit -> SetName("background");
  //RooAbsData* data = w_bgfit->data("data_obs");
  RooRealVar bg_norm("background_norm","Number of background events",RDHCR.sumEntries(),0,1000000);
  cout << "entries in data: " << RDHCR.sumEntries() << endl;
  bg_norm.setConstant();

  RooRealVar signal_norm("signal_norm","Signal normalization",RDHSigSR.sumEntries(),0,1000000);

  std::cout << "Saving" << std::endl;

  //Output file
  TFile *fOut = new TFile("ws_pseudodata_pdf_template_500evtsSig.root","RECREATE");
  RooWorkspace wspace("wspace","wspace");
  wspace.import(RDHCR);
  wspace.import(RDHSR);
  wspace.import(RDHSigSR);
  wspace.import(RDHSig);
  wspace.import(*p_bgfit);
  wspace.import(bg_norm);
  wspace.import(TF);
  //wspace.import(TF_norm);
  wspace.factory("PROD::signal(background,TF)");
  wspace.import(signal_norm);
  wspace.Write();
  cout << "File created: ws_pseudodata_pdf_template_500evtsSig.root" << endl;
  fOut -> Close();
}
