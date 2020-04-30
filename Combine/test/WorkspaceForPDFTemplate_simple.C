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

void WorkspaceForPDFTemplate_simple(){

  // As usual, load the combine library to get access to the RooParametricHist
  gSystem->Load("libHiggsAnalysisCombinedLimit.so");
  
  //Get input data
  TFile* fIn = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Outputdata/TF_bias/Pseudos_10GeVBins_simpleExp_2222.root","READ");

  // A search in a mbb tail, define mbb as our variable
  RooRealVar mbb("mbb","m_{12}",200,500);//SR 1
  RooArgList vars(mbb);

  TH1F* CRHist = (TH1F*)fIn->Get("CRHist");//data_obs CR
  RooDataHist RDHCR("RDHCR","CR",vars,CRHist); 

  TH1F* SRHist = (TH1F*)fIn->Get("SRHist");//data_obs SR
  RooDataHist RDHSR("RDHSR","SR",vars,SRHist);

  TH1F* SigSRHist = (TH1F*)fIn->Get("SigSRHist");//data_obs SR including Gaussian signal
  RooDataHist RDHSigSR("RDHSigSR","SR + Signal",vars,SigSRHist);

  TH1F* SignalHist = (TH1F*)fIn->Get("SignalHist");//signal
  RooDataHist RDHSig("RDHSig","Signal",vars,SignalHist);

  RooGenericPdf TF("TF","TF","1/7",vars);
  RooRealVar TF_norm("TF_norm","ratio of SR/CR",RDHSR.sumEntries()/RDHCR.sumEntries(),0.0,1.0);
  //TF_norm.setConstant();

  RooRealVar slope("slope","slope",0.005,0.0,0.05);
  RooArgList varsbg(mbb,slope);

  RooGenericPdf background("background","background","TMath::Exp(-slope*mbb)",varsbg);
  RooRealVar background_norm("background_norm","Number of background events",RDHCR.sumEntries(),0,100000);
  cout << "entries in data: " << RDHCR.sumEntries() << endl;
  background_norm.setConstant();

  //RooRealVar signal_norm("signal_norm","Signal normalization",RDHSR.sumEntries()/RDHCR.sumEntries(),0,100000);

  //Output file
  TFile *fOut = new TFile("ws_pseudodata_pdf_template.root","RECREATE");
  RooWorkspace wspace("wspace","wspace");
  wspace.import(RDHCR);
  wspace.import(RDHSR);
  wspace.import(RDHSigSR);
  wspace.import(RDHSig);
  wspace.import(background);
  wspace.import(background_norm);
  wspace.import(TF);
  wspace.import(TF_norm);
  wspace.factory("PROD::signal(background,TF)");
  //wspace.import(signal_norm);
  wspace.Write();
  cout << "File created: ws_pseudodata_pdf_template.root" << endl;
  fOut -> Close();
}
