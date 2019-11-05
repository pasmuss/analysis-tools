#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TEfficiency.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

using namespace std;

void eff_pT_sf_MC_data() {

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);

  TFile* datain = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017C.root","READ");
  TFile* dataDin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017D.root","READ");
  TFile* dataEin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017E.root","READ");
  TFile* dataFin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017F.root","READ");

  TFile* dataout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017C_eff_for_sf.root","RECREATE");
  TFile* dataDout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017D_eff_for_sf.root","RECREATE");
  TFile* dataEout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017E_eff_for_sf.root","RECREATE");
  TFile* dataFout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_Nov04-19/2017F_eff_for_sf.root","RECREATE");

  TH1F* in_C_60_0to1 = (TH1F*) dataCin -> Get("pt_0_PFJet60xOffl_eta0to1");
  TH1F* in_C_60_1to14 = (TH1F*) dataCin -> Get("pt_0_PFJet60xOffl_eta1to1p4");
  TH1F* in_C_60_14to22 = (TH1F*) dataCin -> Get("pt_0_PFJet60xOffl_eta1p4to2p2");
  TH1F* in_C_100_0to1 = (TH1F*) dataCin -> Get("pt_0_PFJet100xOffl_eta0to1");
  TH1F* in_C_100_1to14 = (TH1F*) dataCin -> Get("pt_0_PFJet100xOffl_eta1to1p4");
  TH1F* in_C_100_14to22 = (TH1F*) dataCin -> Get("pt_0_PFJet100xOffl_eta1p4to2p2");

  TH1F* in_D_60_0to1 = (TH1F*) dataDin -> Get("pt_0_PFJet60xOffl_eta0to1");
  TH1F* in_D_60_1to14 = (TH1F*) dataDin -> Get("pt_0_PFJet60xOffl_eta1to1p4");
  TH1F* in_D_60_14to22 = (TH1F*) dataDin -> Get("pt_0_PFJet60xOffl_eta1p4to2p2");
  TH1F* in_D_100_0to1 = (TH1F*) dataDin -> Get("pt_0_PFJet100xOffl_eta0to1");
  TH1F* in_D_100_1to14 = (TH1F*) dataDin -> Get("pt_0_PFJet100xOffl_eta1to1p4");
  TH1F* in_D_100_14to22 = (TH1F*) dataDin -> Get("pt_0_PFJet100xOffl_eta1p4to2p2");

  TH1F* in_E_60_0to1 = (TH1F*) dataEin -> Get("pt_0_PFJet60xOffl_eta0to1");
  TH1F* in_E_60_1to14 = (TH1F*) dataEin -> Get("pt_0_PFJet60xOffl_eta1to1p4");
  TH1F* in_E_60_14to22 = (TH1F*) dataEin -> Get("pt_0_PFJet60xOffl_eta1p4to2p2");
  TH1F* in_E_100_0to1 = (TH1F*) dataEin -> Get("pt_0_PFJet100xOffl_eta0to1");
  TH1F* in_E_100_1to14 = (TH1F*) dataEin -> Get("pt_0_PFJet100xOffl_eta1to1p4");
  TH1F* in_E_100_14to22 = (TH1F*) dataEin -> Get("pt_0_PFJet100xOffl_eta1p4to2p2");

  TH1F* in_F_60_0to1 = (TH1F*) dataFin -> Get("pt_0_PFJet60xOffl_eta0to1");
  TH1F* in_F_60_1to14 = (TH1F*) dataFin -> Get("pt_0_PFJet60xOffl_eta1to1p4");
  TH1F* in_F_60_14to22 = (TH1F*) dataFin -> Get("pt_0_PFJet60xOffl_eta1p4to2p2");
  TH1F* in_F_100_0to1 = (TH1F*) dataFin -> Get("pt_0_PFJet100xOffl_eta0to1");
  TH1F* in_F_100_1to14 = (TH1F*) dataFin -> Get("pt_0_PFJet100xOffl_eta1to1p4");
  TH1F* in_F_100_14to22 = (TH1F*) dataFin -> Get("pt_0_PFJet100xOffl_eta1p4to2p2");

  ///
  /// C
  ///

  TF1* errfC1 = new TF1("errfC1","[0]*erf([2]*(x-[1]))",100,500);
  errfC1 -> SetParameters(1.0,100.0,0.05);
  errfC1 -> SetLineColor(kRed);

  dataCout -> cd();
  TCanvas* canC1 = style.MakeCanvas("canC1","",700,700);
  TEfficiency* EffC_0to1 = 0;
  if(TEfficiency::CheckConsistency(*in_C_100_0to1, *in_C_60_0to1)){//h_pass, h_total
    cout << "Fitting era C, eta 0 to 1" << endl;
    EffC_0to1 = new TEfficiency(*in_C_100_0to1, *in_C_60_0to1);
    EffC_0to1 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffC_0to1 -> Fit(errfC1,"RV");
    EffC_0to1 -> Draw();    
    EffC_0to1 -> Write();
    TLegend* legC1 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legC1);
    legC1 -> AddEntry(EffC_0to1, "Efficiency 2017C, 0 < |#eta| < 1", "LP");
    legC1 -> AddEntry(errfC1, "Fit (Error Function)", "L");
    legC1 -> Draw("SAME");

    double chi2C1 = errfC1 -> GetChisquare();
    double ndfC1 = errfC1 -> GetNDF();
    double chi2ndfC1 = chi2C1 / ndfC1;
    cout << "chi2/ndf, 2017C, 0 < |#eta| < 1: " << chi2ndfC1 << endl;
  }
  canC1 -> SaveAs("Outputdata/TriggerSF/eff-2017C-eta0to1.pdf");
  canC1 -> SaveAs("Outputdata/TriggerSF/eff-2017C-eta0to1.root");

  TF1* errfC2 = new TF1("errfC2","[0]*erf([2]*(x-[1]))",100,500);
  errfC2 -> SetParameters(1.0,100.0,0.05);
  errfC2 -> SetLineColor(kRed);

  TCanvas* canC2 = style.MakeCanvas("canC2","",700,700);
  TEfficiency* EffC_1to14 = 0;
  if(TEfficiency::CheckConsistency(*in_C_100_1to14, *in_C_60_1to14)){//h_pass, h_total
    cout << "Fitting era C, eta 1 to 1.4" << endl;
    EffC_1to14 = new TEfficiency(*in_C_100_1to14, *in_C_60_1to14);
    EffC_1to14 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffC_1to14 -> Fit(errfC2,"RV");
    EffC_1to14 -> Draw();    
    EffC_1to14 -> Write();
    TLegend* legC2 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legC2);
    legC2 -> AddEntry(EffC_1to14, "Efficiency 2017C, 1 < |#eta| < 1.4", "LP");
    legC2 -> AddEntry(errfC2, "Fit (Error Function)", "L");
    legC2 -> Draw("SAME");

    double chi2C2 = errfC2 -> GetChisquare();
    double ndfC2 = errfC2 -> GetNDF();
    double chi2ndfC2 = chi2C2 / ndfC2;
    cout << "chi2/ndf, 2017C, 1 < |#eta| < 1.4: " << chi2ndfC2 << endl;

  }
  canC2 -> SaveAs("Outputdata/TriggerSF/eff-2017C-eta1to14.pdf");
  canC2 -> SaveAs("Outputdata/TriggerSF/eff-2017C-eta1to14.root");

  TF1* errfC3 = new TF1("errfC3","[0]*erf([2]*(x-[1]))",100,500);
  errfC3 -> SetParameters(1.0,100.0,0.05);
  errfC3 -> SetLineColor(kRed);

  TCanvas* canC3 = style.MakeCanvas("canC3","",700,700);
  TEfficiency* EffC_14to22 = 0;
  if(TEfficiency::CheckConsistency(*in_C_100_14to22, *in_C_60_14to22)){//h_pass, h_total
    cout << "Fitting era C, eta 1.4 to 2.2" << endl;
    EffC_14to22 = new TEfficiency(*in_C_100_14to22, *in_C_60_14to22);
    EffC_14to22 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffC_14to22 -> Fit(errfC3,"RV");
    EffC_14to22 -> Draw();    
    EffC_14to22 -> Write();
    TLegend* legC3 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legC3);
    legC3 -> AddEntry(EffC_14to22, "Efficiency 2017C, 1.4 < |#eta| < 2.2", "LP");
    legC3 -> AddEntry(errfC3, "Fit (Error Function)", "L");
    legC3 -> Draw("SAME");

    double chi2C3 = errfC3 -> GetChisquare();
    double ndfC3 = errfC3 -> GetNDF();
    double chi2ndfC3 = chi2C3 / ndfC3;
    cout << "chi2/ndf, 2017C, 1.4 < |#eta| < 2.2: " << chi2ndfC3 << endl;

  }
  canC3 -> SaveAs("Outputdata/TriggerSF/eff-2017C-eta14to22.pdf");
  canC3 -> SaveAs("Outputdata/TriggerSF/eff-2017C-eta14to22.root");

  ///
  /// D
  ///

  TF1* errfD1 = new TF1("errfD1","[0]*erf([2]*(x-[1]))",100,500);
  errfD1 -> SetParameters(1.0,100.0,0.05);
  errfD1 -> SetLineColor(kRed);

  dataDout -> cd();
  TCanvas* canD1 = style.MakeCanvas("canD1","",700,700);
  TEfficiency* EffD_0to1 = 0;
  if(TEfficiency::CheckConsistency(*in_D_100_0to1, *in_D_60_0to1)){//h_pass, h_total
    cout << "Fitting era D, eta 0 to 1" << endl;
    EffD_0to1 = new TEfficiency(*in_D_100_0to1, *in_D_60_0to1);
    EffD_0to1 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffD_0to1 -> Fit(errfD1,"RV");
    EffD_0to1 -> Draw();    
    EffD_0to1 -> Write();
    TLegend* legD1 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legD1);
    legD1 -> AddEntry(EffD_0to1, "Efficiency 2017D, 0 < |#eta| < 1", "LP");
    legD1 -> AddEntry(errfD1, "Fit (Error Function)", "L");
    legD1 -> Draw("SAME");

    double chi2D1 = errfD1 -> GetChisquare();
    double ndfD1 = errfD1 -> GetNDF();
    double chi2ndfD1 = chi2D1 / ndfD1;
    cout << "chi2/ndf, 2017D, 0 < |#eta| < 1: " << chi2ndfD1 << endl;

  }
  canD1 -> SaveAs("Outputdata/TriggerSF/eff-2017D-eta0to1.pdf");
  canD1 -> SaveAs("Outputdata/TriggerSF/eff-2017D-eta0to1.root");


  TF1* errfD2 = new TF1("errfD2","[0]*erf([2]*(x-[1]))",100,500);
  errfD2 -> SetParameters(1.0,100.0,0.05);
  errfD2 -> SetLineColor(kRed);

  TCanvas* canD2 = style.MakeCanvas("canD2","",700,700);
  TEfficiency* EffD_1to14 = 0;
  if(TEfficiency::CheckConsistency(*in_D_100_1to14, *in_D_60_1to14)){//h_pass, h_total
    cout << "Fitting era D, eta 1 to 1.4" << endl;
    EffD_1to14 = new TEfficiency(*in_D_100_1to14, *in_D_60_1to14);
    EffD_1to14 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffD_1to14 -> Fit(errfD2,"RV");
    EffD_1to14 -> Draw();    
    EffD_1to14 -> Write();
    TLegend* legD2 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legD2);
    legD2 -> AddEntry(EffD_1to14, "Efficiency 2017D, 1 < |#eta| < 1.4", "LP");
    legD2 -> AddEntry(errfD2, "Fit (Error Function)", "L");
    legD2 -> Draw("SAME");

    double chi2D2 = errfD2 -> GetChisquare();
    double ndfD2 = errfD2 -> GetNDF();
    double chi2ndfD2 = chi2D2 / ndfD2;
    cout << "chi2/ndf, 2017D, 1 < |#eta| < 1.4: " << chi2ndfD2 << endl;

  }
  canD2 -> SaveAs("Outputdata/TriggerSF/eff-2017D-eta1to14.pdf");
  canD2 -> SaveAs("Outputdata/TriggerSF/eff-2017D-eta1to14.root");

  TF1* errfD3 = new TF1("errfD3","[0]*erf([2]*(x-[1]))",100,500);
  errfD3 -> SetParameters(1.0,100.0,0.05);
  errfD3 -> SetLineColor(kRed);

  TCanvas* canD3 = style.MakeCanvas("canD3","",700,700);
  TEfficiency* EffD_14to22 = 0;
  if(TEfficiency::CheckConsistency(*in_D_100_14to22, *in_D_60_14to22)){//h_pass, h_total
    cout << "Fitting era D, eta 1.4 to 2.2" << endl;
    EffD_14to22 = new TEfficiency(*in_D_100_14to22, *in_D_60_14to22);
    EffD_14to22 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffD_14to22 -> Fit(errfD3,"RV");
    EffD_14to22 -> Draw();    
    EffD_14to22 -> Write();
    TLegend* legD3 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legD3);
    legD3 -> AddEntry(EffD_14to22, "Efficiency 2017D, 1.4 < |#eta| < 2.2", "LP");
    legD3 -> AddEntry(errfD3, "Fit (Error Function)", "L");
    legD3 -> Draw("SAME");

    double chi2D3 = errfD3 -> GetChisquare();
    double ndfD3 = errfD3 -> GetNDF();
    double chi2ndfD3 = chi2D3 / ndfD3;
    cout << "chi2/ndf, 2017D, 1.4 < |#eta| < 2.2: " << chi2ndfD3 << endl;

  }
  canD3 -> SaveAs("Outputdata/TriggerSF/eff-2017D-eta14to22.pdf");
  canD3 -> SaveAs("Outputdata/TriggerSF/eff-2017D-eta14to22.root");

  ///
  /// E
  ///

  TF1* errfE1 = new TF1("errfE1","[0]*erf([2]*(x-[1]))",100,500);
  errfE1 -> SetParameters(1.0,100.0,0.05);
  errfE1 -> SetLineColor(kRed);

  dataEout -> cd();
  TCanvas* canE1 = style.MakeCanvas("canE1","",700,700);
  TEfficiency* EffE_0to1 = 0;
  if(TEfficiency::CheckConsistency(*in_E_100_0to1, *in_E_60_0to1)){//h_pass, h_total
    cout << "Fitting era E, eta 0 to 1" << endl;
    EffE_0to1 = new TEfficiency(*in_E_100_0to1, *in_E_60_0to1);
    EffE_0to1 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffE_0to1 -> Fit(errfE1,"RV");
    EffE_0to1 -> Draw();    
    EffE_0to1 -> Write();
    TLegend* legE1 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legE1);
    legE1 -> AddEntry(EffE_0to1, "Efficiency 2017E, 0 < |#eta| < 1", "LP");
    legE1 -> AddEntry(errfE1, "Fit (Error Function)", "L");
    legE1 -> Draw("SAME");

    double chi2E1 = errfE1 -> GetChisquare();
    double ndfE1 = errfE1 -> GetNDF();
    double chi2ndfE1 = chi2E1 / ndfE1;
    cout << "chi2/ndf, 2017E, 0 < |#eta| < 1: " << chi2ndfE1 << endl;

  }
  canE1 -> SaveAs("Outputdata/TriggerSF/eff-2017E-eta0to1.pdf");
  canE1 -> SaveAs("Outputdata/TriggerSF/eff-2017E-eta0to1.root");


  TF1* errfE2 = new TF1("errfE2","[0]*erf([2]*(x-[1]))",100,500);
  errfE2 -> SetParameters(1.0,100.0,0.05);
  errfE2 -> SetLineColor(kRed);

  TCanvas* canE2 = style.MakeCanvas("canE2","",700,700);
  TEfficiency* EffE_1to14 = 0;
  if(TEfficiency::CheckConsistency(*in_E_100_1to14, *in_E_60_1to14)){//h_pass, h_total
    cout << "Fitting era E, eta 1 to 1.4" << endl;
    EffE_1to14 = new TEfficiency(*in_E_100_1to14, *in_E_60_1to14);
    EffE_1to14 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffE_1to14 -> Fit(errfE2,"RV");
    EffE_1to14 -> Draw();    
    EffE_1to14 -> Write();
    TLegend* legE2 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legE2);
    legE2 -> AddEntry(EffE_1to14, "Efficiency 2017E, 1 < |#eta| < 1.4", "LP");
    legE2 -> AddEntry(errfE2, "Fit (Error Function)", "L");
    legE2 -> Draw("SAME");

    double chi2E2 = errfE2 -> GetChisquare();
    double ndfE2 = errfE2 -> GetNDF();
    double chi2ndfE2 = chi2E2 / ndfE2;
    cout << "chi2/ndf, 2017E, 1 < |#eta| < 1.4: " << chi2ndfE2 << endl;

  }
  canE2 -> SaveAs("Outputdata/TriggerSF/eff-2017E-eta1to14.pdf");
  canE2 -> SaveAs("Outputdata/TriggerSF/eff-2017E-eta1to14.root");

  TF1* errfE3 = new TF1("errfE3","[0]*erf([2]*(x-[1]))",100,500);
  errfE3 -> SetParameters(1.0,100.0,0.01);
  errfE3 -> SetLineColor(kRed);

  TCanvas* canE3 = style.MakeCanvas("canE3","",700,700);
  TEfficiency* EffE_14to22 = 0;
  if(TEfficiency::CheckConsistency(*in_E_100_14to22, *in_E_60_14to22)){//h_pass, h_total
    cout << "Fitting era E, eta 1.4 to 2.2" << endl;
    EffE_14to22 = new TEfficiency(*in_E_100_14to22, *in_E_60_14to22);
    EffE_14to22 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffE_14to22 -> Fit(errfE3,"RV");
    EffE_14to22 -> Draw();    
    EffE_14to22 -> Write();
    TLegend* legE3 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legE3);
    legE3 -> AddEntry(EffE_14to22, "Efficiency 2017E, 1.4 < |#eta| < 2.2", "LP");
    legE3 -> AddEntry(errfE3, "Fit (Error Function)", "L");
    legE3 -> Draw("SAME");

    double chi2E3 = errfE3 -> GetChisquare();
    double ndfE3 = errfE3 -> GetNDF();
    double chi2ndfE3 = chi2E3 / ndfE3;
    cout << "chi2/ndf, 2017E, 1.4 < |#eta| < 2.2: " << chi2ndfE3 << endl;

  }
  canE3 -> SaveAs("Outputdata/TriggerSF/eff-2017E-eta14to22.pdf");
  canE3 -> SaveAs("Outputdata/TriggerSF/eff-2017E-eta14to22.root");

  ///
  /// F
  ///

  TF1* errfF1 = new TF1("errfF1","[0]*erf([2]*(x-[1]))",100,500);
  errfF1 -> SetParameters(1.0,100.0,0.01);
  errfF1 -> SetLineColor(kRed);

  dataFout -> cd();
  TCanvas* canF1 = style.MakeCanvas("canF1","",700,700);
  TEfficiency* EffF_0to1 = 0;
  if(TEfficiency::CheckConsistency(*in_F_100_0to1, *in_F_60_0to1)){//h_pass, h_total
    cout << "Fitting era F, eta 0 to 1" << endl;
    EffF_0to1 = new TEfficiency(*in_F_100_0to1, *in_F_60_0to1);
    EffF_0to1 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffF_0to1 -> Fit(errfF1,"RV");
    EffF_0to1 -> Draw();    
    EffF_0to1 -> Write();
    TLegend* legF1 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legF1);
    legF1 -> AddEntry(EffF_0to1, "Efficiency 2017F, 0 < |#eta| < 1", "LP");
    legF1 -> AddEntry(errfF1, "Fit (Error Function)", "L");
    legF1 -> Draw("SAME");

    double chi2F1 = errfF1 -> GetChisquare();
    double ndfF1 = errfF1 -> GetNDF();
    double chi2ndfF1 = chi2F1 / ndfF1;
    cout << "chi2/ndf, 2017F, 0 < |#eta| < 1: " << chi2ndfF1 << endl;

  }
  canF1 -> SaveAs("Outputdata/TriggerSF/eff-2017F-eta0to1.pdf");
  canF1 -> SaveAs("Outputdata/TriggerSF/eff-2017F-eta0to1.root");


  TF1* errfF2 = new TF1("errfF2","[0]*erf([2]*(x-[1]))",100,500);
  errfF2 -> SetParameters(1.0,100.0,0.05);
  errfF2 -> SetLineColor(kRed);

  TCanvas* canF2 = style.MakeCanvas("canF2","",700,700);
  TEfficiency* EffF_1to14 = 0;
  if(TEfficiency::CheckConsistency(*in_F_100_1to14, *in_F_60_1to14)){//h_pass, h_total
    cout << "Fitting era F, eta 1 to 1.4" << endl;
    EffF_1to14 = new TEfficiency(*in_F_100_1to14, *in_F_60_1to14);
    EffF_1to14 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffF_1to14 -> Fit(errfF2,"RV");
    EffF_1to14 -> Draw();    
    EffF_1to14 -> Write();
    TLegend* legF2 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legF2);
    legF2 -> AddEntry(EffF_1to14, "Efficiency 2017F, 1 < |#eta| < 1.4", "LP");
    legF2 -> AddEntry(errfF2, "Fit (Error Function)", "L");
    legF2 -> Draw("SAME");

    double chi2F2 = errfF2 -> GetChisquare();
    double ndfF2 = errfF2 -> GetNDF();
    double chi2ndfF2 = chi2F2 / ndfF2;
    cout << "chi2/ndf, 2017F, 1 < |#eta| < 1.4: " << chi2ndfF2 << endl;

  }
  canF2 -> SaveAs("Outputdata/TriggerSF/eff-2017F-eta1to14.pdf");
  canF2 -> SaveAs("Outputdata/TriggerSF/eff-2017F-eta1to14.root");

  TF1* errfF3 = new TF1("errfF3","[0]*erf([2]*(x-[1]))",100,500);
  errfF3 -> SetParameters(1.0,100.0,0.1);
  errfF3 -> SetLineColor(kRed);

  TCanvas* canF3 = style.MakeCanvas("canF3","",700,700);
  TEfficiency* EffF_14to22 = 0;
  if(TEfficiency::CheckConsistency(*in_F_100_14to22, *in_F_60_14to22)){//h_pass, h_total
    cout << "Fitting era F, eta 1.4 to 2.2" << endl;
    EffF_14to22 = new TEfficiency(*in_F_100_14to22, *in_F_60_14to22);
    EffF_14to22 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffF_14to22 -> Fit(errfF3,"RV");
    EffF_14to22 -> Draw();    
    EffF_14to22 -> Write();
    TLegend* legF3 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legF3);
    legF3 -> AddEntry(EffF_14to22, "Efficiency 2017F, 1.4 < |#eta| < 2.2", "LP");
    legF3 -> AddEntry(errfF3, "Fit (Error Function)", "L");
    legF3 -> Draw("SAME");

    double chi2F3 = errfF3 -> GetChisquare();
    double ndfF3 = errfF3 -> GetNDF();
    double chi2ndfF3 = chi2F3 / ndfF3;
    cout << "chi2/ndf, 2017F, 1.4 < |#eta| < 2.2: " << chi2ndfF3 << endl;
  }
  canF3 -> SaveAs("Outputdata/TriggerSF/eff-2017F-eta14to22.pdf");
  canF3 -> SaveAs("Outputdata/TriggerSF/eff-2017F-eta14to22.root");

}
