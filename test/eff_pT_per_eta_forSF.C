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

void eff_pT_per_eta_forSF() {

  HbbStylesNew style;
  style.SetStyle();

  gStyle->SetOptStat(0);

  TFile* dataCin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017C.root","READ");
  TFile* dataDin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017D.root","READ");
  TFile* dataEin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017E.root","READ");
  TFile* dataFin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017F.root","READ");
  TFile* data2017in = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017.root","READ");
  TFile* MC0to1_60in = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/MC-pt_0_PFJet60xOffl_eta0to1-20172017.root","READ");
  TFile* MC0to1_100in = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/MC-pt_0_PFJet100xOffl_eta0to1-20172017.root","READ");
  TFile* MC1to1p4_60in = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/MC-pt_0_PFJet60xOffl_eta1to1p4-20172017.root","READ");
  TFile* MC1to1p4_100in = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/MC-pt_0_PFJet100xOffl_eta1to1p4-20172017.root","READ");
  TFile* MC1p4to2p2_60in = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/MC-pt_0_PFJet60xOffl_eta1p4to2p2-20172017.root","READ");
  TFile* MC1p4to2p2_100in = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/MC-pt_0_PFJet100xOffl_eta1p4to2p2-20172017.root","READ");

  TFile* dataCout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017C_eff_for_sf.root","RECREATE");
  TFile* dataDout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017D_eff_for_sf.root","RECREATE");
  TFile* dataEout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017E_eff_for_sf.root","RECREATE");
  TFile* dataFout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017F_eff_for_sf.root","RECREATE");
  TFile* data2017out = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/2017_eff_for_sf.root","RECREATE");
  TFile* MCout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/TwoJets_StartingAt100GeV_inclDRcut_fineBinsBeg_Nov07-19/MC_eff_for_sf.root","RECREATE");

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

  TH1F* in_2017_60_0to1 = (TH1F*) data2017in -> Get("pt_0_PFJet60xOffl_eta0to1");
  TH1F* in_2017_60_1to14 = (TH1F*) data2017in -> Get("pt_0_PFJet60xOffl_eta1to1p4");
  TH1F* in_2017_60_14to22 = (TH1F*) data2017in -> Get("pt_0_PFJet60xOffl_eta1p4to2p2");
  TH1F* in_2017_100_0to1 = (TH1F*) data2017in -> Get("pt_0_PFJet100xOffl_eta0to1");
  TH1F* in_2017_100_1to14 = (TH1F*) data2017in -> Get("pt_0_PFJet100xOffl_eta1to1p4");
  TH1F* in_2017_100_14to22 = (TH1F*) data2017in -> Get("pt_0_PFJet100xOffl_eta1p4to2p2");

  TCanvas* in60_0to1 = (TCanvas*) MC0to1_60in -> Get("Can");
  TH1F* in_MC_60_0to1 = (TH1F*)in60_0to1->GetListOfPrimitives()->At(1)->Clone();
  TCanvas* in60_1to14 = (TCanvas*) MC1to1p4_60in -> Get("Can");
  TH1F* in_MC_60_1to14 = (TH1F*)in60_1to14->GetListOfPrimitives()->At(1)->Clone();
  TCanvas* in60_14to22 = (TCanvas*) MC1p4to2p2_60in -> Get("Can");
  TH1F* in_MC_60_14to22 = (TH1F*)in60_14to22->GetListOfPrimitives()->At(1)->Clone();
  TCanvas* in100_0to1 = (TCanvas*) MC0to1_100in -> Get("Can");
  TH1F* in_MC_100_0to1 = (TH1F*)in100_0to1->GetListOfPrimitives()->At(1)->Clone();
  TCanvas* in100_1to14 = (TCanvas*) MC1to1p4_100in -> Get("Can");
  TH1F* in_MC_100_1to14 = (TH1F*)in100_1to14->GetListOfPrimitives()->At(1)->Clone();
  TCanvas* in100_14to22 = (TCanvas*) MC1p4to2p2_100in -> Get("Can");
  TH1F* in_MC_100_14to22 = (TH1F*)in100_14to22->GetListOfPrimitives()->At(1)->Clone();

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
  canC1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017C-eta0to1.pdf");
  canC1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017C-eta0to1.root");

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
  canC2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017C-eta1to14.pdf");
  canC2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017C-eta1to14.root");

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
  canC3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017C-eta14to22.pdf");
  canC3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017C-eta14to22.root");

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
  canD1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017D-eta0to1.pdf");
  canD1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017D-eta0to1.root");


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
  canD2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017D-eta1to14.pdf");
  canD2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017D-eta1to14.root");

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
  canD3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017D-eta14to22.pdf");
  canD3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017D-eta14to22.root");

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
  canE1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017E-eta0to1.pdf");
  canE1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017E-eta0to1.root");


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
  canE2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017E-eta1to14.pdf");
  canE2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017E-eta1to14.root");

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
  canE3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017E-eta14to22.pdf");
  canE3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017E-eta14to22.root");

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
  canF1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017F-eta0to1.pdf");
  canF1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017F-eta0to1.root");


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
  canF2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017F-eta1to14.pdf");
  canF2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017F-eta1to14.root");

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
  canF3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017F-eta14to22.pdf");
  canF3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017F-eta14to22.root");

  ///
  /// 2017 total
  ///

  TF1* errf2017_1 = new TF1("errf2017_1","[0]*erf([2]*(x-[1]))",100,500);
  errf2017_1 -> SetParameters(1.0,100.0,0.1);
  errf2017_1 -> SetLineColor(kRed);

  TCanvas* can2017_1 = style.MakeCanvas("can2017_1","",700,700);
  TEfficiency* Eff2017_0to1 = 0;
  if(TEfficiency::CheckConsistency(*in_2017_100_0to1, *in_2017_60_0to1)){//h_pass, h_total
    cout << "Fitting 2017, eta 0.0 to 1.0" << endl;
    Eff2017_0to1 = new TEfficiency(*in_2017_100_0to1, *in_2017_60_0to1);
    Eff2017_0to1 -> SetTitle(";p_{T} [GeV];#epsilon");
    Eff2017_0to1 -> Fit(errf2017_1,"RV");
    Eff2017_0to1 -> Draw();    
    Eff2017_0to1 -> Write();
    TLegend* leg2017_1 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(leg2017_1);
    leg2017_1 -> AddEntry(Eff2017_0to1, "Efficiency 2017, 0.0 < |#eta| < 1.0", "LP");
    leg2017_1 -> AddEntry(errf2017_1, "Fit (Error Function)", "L");
    leg2017_1 -> Draw("SAME");

    double chi22017_1 = errf2017_1 -> GetChisquare();
    double ndf2017_1 = errf2017_1 -> GetNDF();
    double chi2ndf2017_1 = chi22017_1 / ndf2017_1;
    cout << "chi2/ndf, 2017, 0.0 < |#eta| < 1.0: " << chi2ndf2017_1 << endl;
  }
  can2017_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017-eta0to1.pdf");
  can2017_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017-eta0to1.root");


  TF1* errf2017_2 = new TF1("errf2017_2","[0]*erf([2]*(x-[1]))",100,500);
  errf2017_2 -> SetParameters(1.0,100.0,0.1);
  errf2017_2 -> SetLineColor(kRed);

  TCanvas* can2017_2 = style.MakeCanvas("can2017_2","",700,700);
  TEfficiency* Eff2017_1to14 = 0;
  if(TEfficiency::CheckConsistency(*in_2017_100_1to14, *in_2017_60_1to14)){//h_pass, h_total
    cout << "Fitting 2017, eta 0.0 to 1.0" << endl;
    Eff2017_1to14 = new TEfficiency(*in_2017_100_1to14, *in_2017_60_1to14);
    Eff2017_1to14 -> SetTitle(";p_{T} [GeV];#epsilon");
    Eff2017_1to14 -> Fit(errf2017_2,"RV");
    Eff2017_1to14 -> Draw();    
    Eff2017_1to14 -> Write();
    TLegend* leg2017_2 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(leg2017_2);
    leg2017_2 -> AddEntry(Eff2017_1to14, "Efficiency 2017, 1.0 < |#eta| < 1.4", "LP");
    leg2017_2 -> AddEntry(errf2017_2, "Fit (Error Function)", "L");
    leg2017_2 -> Draw("SAME");

    double chi22017_2 = errf2017_2 -> GetChisquare();
    double ndf2017_2 = errf2017_2 -> GetNDF();
    double chi2ndf2017_2 = chi22017_2 / ndf2017_2;
    cout << "chi2/ndf, 2017, 1.0 < |#eta| < 1.4: " << chi2ndf2017_2 << endl;
  }
  can2017_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017-eta1to14.pdf");
  can2017_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017-eta1to14.root");


  TF1* errf2017_3 = new TF1("errf2017_3","[0]*erf([2]*(x-[1]))",100,500);
  errf2017_3 -> SetParameters(1.0,100.0,0.1);
  errf2017_3 -> SetLineColor(kRed);

  TCanvas* can2017_3 = style.MakeCanvas("can2017_3","",700,700);
  TEfficiency* Eff2017_14to22 = 0;
  if(TEfficiency::CheckConsistency(*in_2017_100_14to22, *in_2017_60_14to22)){//h_pass, h_total
    cout << "Fitting 2017, eta 1.4 to 2.2" << endl;
    Eff2017_14to22 = new TEfficiency(*in_2017_100_14to22, *in_2017_60_14to22);
    Eff2017_14to22 -> SetTitle(";p_{T} [GeV];#epsilon");
    Eff2017_14to22 -> Fit(errf2017_3,"RV");
    Eff2017_14to22 -> Draw();    
    Eff2017_14to22 -> Write();
    TLegend* leg2017_3 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(leg2017_3);
    leg2017_3 -> AddEntry(Eff2017_14to22, "Efficiency 2017, 1.4 < |#eta| < 2.2", "LP");
    leg2017_3 -> AddEntry(errf2017_3, "Fit (Error Function)", "L");
    leg2017_3 -> Draw("SAME");

    double chi22017_3 = errf2017_3 -> GetChisquare();
    double ndf2017_3 = errf2017_3 -> GetNDF();
    double chi2ndf2017_3 = chi22017_3 / ndf2017_3;
    cout << "chi2/ndf, 2017, 1.4 < |#eta| < 2.2: " << chi2ndf2017_3 << endl;
  }
  can2017_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017-eta14to22.pdf");
  can2017_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-2017-eta14to22.root");

  ///
  /// MC
  ///

  TF1* errfMC_1 = new TF1("errfMC_1","[0]*erf([2]*(x-[1]))",100,500);
  errfMC_1 -> SetParameters(1.0,100.0,0.1);
  errfMC_1 -> SetLineColor(kRed);

  TCanvas* canMC_1 = style.MakeCanvas("canMC_1","",700,700);
  TEfficiency* EffMC_0to1 = 0;
  if(TEfficiency::CheckConsistency(*in_MC_100_0to1, *in_MC_60_0to1)){//h_pass, h_total
    cout << "Fitting MC, eta 0.0 to 1.0" << endl;
    EffMC_0to1 = new TEfficiency(*in_MC_100_0to1, *in_MC_60_0to1);
    EffMC_0to1 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffMC_0to1 -> Fit(errfMC_1,"RV");
    EffMC_0to1 -> Draw();    
    EffMC_0to1 -> Write();
    TLegend* legMC_1 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legMC_1);
    legMC_1 -> AddEntry(EffMC_0to1, "Efficiency MC, 0.0 < |#eta| < 1.0", "LP");
    legMC_1 -> AddEntry(errfMC_1, "Fit (Error Function)", "L");
    legMC_1 -> Draw("SAME");

    double chi2MC_1 = errfMC_1 -> GetChisquare();
    double ndfMC_1 = errfMC_1 -> GetNDF();
    double chi2ndfMC_1 = chi2MC_1 / ndfMC_1;
    cout << "chi2/ndf, MC, 0.0 < |#eta| < 1.0: " << chi2ndfMC_1 << endl;
  }
  canMC_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-MC-eta0to1.pdf");
  canMC_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-MC-eta0to1.root");


  TF1* errfMC_2 = new TF1("errfMC_2","[0]*erf([2]*(x-[1]))",100,500);
  errfMC_2 -> SetParameters(1.0,100.0,0.1);
  errfMC_2 -> SetLineColor(kRed);

  TCanvas* canMC_2 = style.MakeCanvas("canMC_2","",700,700);
  TEfficiency* EffMC_1to14 = 0;
  if(TEfficiency::CheckConsistency(*in_MC_100_1to14, *in_MC_60_1to14)){//h_pass, h_total
    cout << "Fitting MC, eta 0.0 to 1.0" << endl;
    EffMC_1to14 = new TEfficiency(*in_MC_100_1to14, *in_MC_60_1to14);
    EffMC_1to14 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffMC_1to14 -> Fit(errfMC_2,"RV");
    EffMC_1to14 -> Draw();    
    EffMC_1to14 -> Write();
    TLegend* legMC_2 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legMC_2);
    legMC_2 -> AddEntry(EffMC_1to14, "Efficiency MC, 1.0 < |#eta| < 1.4", "LP");
    legMC_2 -> AddEntry(errfMC_2, "Fit (Error Function)", "L");
    legMC_2 -> Draw("SAME");

    double chi2MC_2 = errfMC_2 -> GetChisquare();
    double ndfMC_2 = errfMC_2 -> GetNDF();
    double chi2ndfMC_2 = chi2MC_2 / ndfMC_2;
    cout << "chi2/ndf, MC, 1.0 < |#eta| < 1.4: " << chi2ndfMC_2 << endl;
  }
  canMC_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-MC-eta1to14.pdf");
  canMC_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-MC-eta1to14.root");


  TF1* errfMC_3 = new TF1("errfMC_3","[0]*erf([2]*(x-[1]))",100,500);
  errfMC_3 -> SetParameters(1.0,100.0,0.1);
  errfMC_3 -> SetLineColor(kRed);

  TCanvas* canMC_3 = style.MakeCanvas("canMC_3","",700,700);
  TEfficiency* EffMC_14to22 = 0;
  if(TEfficiency::CheckConsistency(*in_MC_100_14to22, *in_MC_60_14to22)){//h_pass, h_total
    cout << "Fitting MC, eta 1.4 to 2.2" << endl;
    EffMC_14to22 = new TEfficiency(*in_MC_100_14to22, *in_MC_60_14to22);
    EffMC_14to22 -> SetTitle(";p_{T} [GeV];#epsilon");
    EffMC_14to22 -> Fit(errfMC_3,"RV");
    EffMC_14to22 -> Draw();    
    EffMC_14to22 -> Write();
    TLegend* legMC_3 = new TLegend(0.37,0.65,0.71,0.75);
    style.SetLegendStyle(legMC_3);
    legMC_3 -> AddEntry(EffMC_14to22, "Efficiency MC, 1.4 < |#eta| < 2.2", "LP");
    legMC_3 -> AddEntry(errfMC_3, "Fit (Error Function)", "L");
    legMC_3 -> Draw("SAME");

    double chi2MC_3 = errfMC_3 -> GetChisquare();
    double ndfMC_3 = errfMC_3 -> GetNDF();
    double chi2ndfMC_3 = chi2MC_3 / ndfMC_3;
    cout << "chi2/ndf, MC, 1.4 < |#eta| < 2.2: " << chi2ndfMC_3 << endl;
  }
  canMC_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-MC-eta14to22.pdf");
  canMC_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff-MC-eta14to22.root");
  

  ///
  /// Other way: Go for ratio first (efficiencies), then TEff to calculate sf
  ///

  TH1F* MC_eff_0to1 = (TH1F*)in_MC_100_0to1->Clone();
  MC_eff_0to1 -> Divide(in_MC_60_0to1);
  TH1F* MC_eff_1to14 = (TH1F*)in_MC_100_1to14->Clone();
  MC_eff_1to14 -> Divide(in_MC_60_1to14);
  TH1F* MC_eff_14to22 = (TH1F*)in_MC_100_14to22->Clone();
  MC_eff_14to22 -> Divide(in_MC_60_14to22);
  
  TH1F* data_eff_0to1 = (TH1F*)in_2017_100_0to1->Clone();
  data_eff_0to1 -> Divide(in_2017_60_0to1);
  data_eff_0to1 -> Divide(MC_eff_0to1);
  TH1F* data_eff_1to14 = (TH1F*)in_2017_100_1to14->Clone();
  data_eff_1to14 -> Divide(in_2017_60_1to14);
  data_eff_1to14 -> Divide(MC_eff_1to14);
  TH1F* data_eff_14to22 = (TH1F*)in_2017_100_14to22->Clone();
  data_eff_14to22 -> Divide(in_2017_60_14to22);
  data_eff_14to22 -> Divide(MC_eff_14to22);

  //TF1* errfsf_1 = new TF1("errfsf_1","([0]*erf([2]*(x-[1])))/([3]*erf([5]*(x-[4])))",100,500);
  //errfsf_1 -> SetParameters(1.0,100.0,0.04,1.0,100.0,0.04);
  TF1* errfsf_1 = new TF1("errfsf_1","[0]*erf([2]*(x-[1]))",100,500);
  errfsf_1 -> SetParameters(1.0,100.0,0.04);
  errfsf_1 -> SetLineColor(kRed);

  //TF1* errfsf_2 = new TF1("errfsf_2","([0]*erf([2]*(x-[1])))/([3]*erf([5]*(x-[4])))",100,500);
  //errfsf_2 -> SetParameters(1.0,100.0,0.04,1.0,100.0,0.04);
  errfsf_2 = new TF1("errfsf_2","[0]*erf([2]*(x-[1]))",100,500);
  errfsf_2 -> SetParameters(1.0,100.0,0.04);
  errfsf_2 -> SetLineColor(kRed);

  //TF1* errfsf_3 = new TF1("errfsf_3","([0]*erf([2]*(x-[1])))/([3]*erf([5]*(x-[4])))",100,500);
  //errfsf_3 -> SetParameters(1.0,100.0,0.04,1.0,100.0,0.04);
  TF1* errfsf_3 = new TF1("errfsf_3","[0]*erf([2]*(x-[1]))",100,500);
  errfsf_3 -> SetParameters(1.0,100.0,0.04);
  errfsf_3 -> SetLineColor(kRed);

  TCanvas* cansf_1 = style.MakeCanvas("cansf_1","",700,700);
  cout << "sf 0.0 to 1.0" << endl;
  data_eff_0to1 -> SetTitle(";p_{T} [GeV];scale factor");
  data_eff_0to1 -> Fit(errfsf_1,"RV");
  data_eff_0to1 -> Draw();
  data_eff_0to1 -> Write();
  TLegend* legsf_1 = new TLegend(0.37,0.45,0.71,0.55);
  style.SetLegendStyle(legsf_1);
  legsf_1 -> AddEntry(data_eff_0to1, "scale factor, 0.0 < |#eta| < 1.0", "LP");
  legsf_1 -> AddEntry(errfsf_1, "Fit (Error Function)", "L");
  legsf_1 -> Draw("SAME");
  double chi2sf_1 = errfsf_1 -> GetChisquare();
  double ndfsf_1 = errfsf_1 -> GetNDF();
  double chi2ndfsf_1 = chi2sf_1 / ndfsf_1;
  cout << "chi2/ndf, MC, 0.0 < |#eta| < 1.0: " << chi2ndfsf_1 << endl;
  cansf_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf-eta0to1.pdf");
  cansf_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf-eta0to1.root");

  TCanvas* cansf_2 = style.MakeCanvas("cansf_2","",700,700);
  cout << "sf 1.0 to 1.4" << endl;
  data_eff_1to14 -> SetTitle(";p_{T} [GeV];scale factor");
  data_eff_1to14 -> Fit(errfsf_2,"RV");
  data_eff_1to14 -> Draw();
  data_eff_1to14 -> Write();
  TLegend* legsf_2 = new TLegend(0.37,0.45,0.71,0.55);
  style.SetLegendStyle(legsf_2);
  legsf_2 -> AddEntry(data_eff_1to14, "scale factor, 1.0 < |#eta| < 1.4", "LP");
  legsf_2 -> AddEntry(errfsf_2, "Fit (Error Function)", "L");
  legsf_2 -> Draw("SAME");
  double chi2sf_2 = errfsf_2 -> GetChisquare();
  double ndfsf_2 = errfsf_2 -> GetNDF();
  double chi2ndfsf_2 = chi2sf_2 / ndfsf_2;
  cout << "chi2/ndf, MC, 1.0 < |#eta| < 1.4: " << chi2ndfsf_2 << endl;
  cansf_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf-eta1to14.pdf");
  cansf_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf-eta1to14.root");

  TCanvas* cansf_3 = style.MakeCanvas("cansf_3","",700,700);
  cout << "sf 1.4 to 2.2" << endl;
  data_eff_14to22 -> SetTitle(";p_{T} [GeV];scale factor");
  data_eff_14to22 -> Fit(errfsf_3,"RV");
  data_eff_14to22 -> Draw();
  data_eff_14to22 -> Write();
  TLegend* legsf_3 = new TLegend(0.37,0.45,0.71,0.55);
  style.SetLegendStyle(legsf_3);
  legsf_3 -> AddEntry(data_eff_14to22, "scale factor, 1.4 < |#eta| < 2.2", "LP");
  legsf_3 -> AddEntry(errfsf_3, "Fit (Error Function)", "L");
  legsf_3 -> Draw("SAME");
  double chi2sf_3 = errfsf_3 -> GetChisquare();
  double ndfsf_3 = errfsf_3 -> GetNDF();
  double chi2ndfsf_3 = chi2sf_3 / ndfsf_3;
  cout << "chi2/ndf, MC, 1.4 < |#eta| < 2.2: " << chi2ndfsf_3 << endl;
  cansf_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf-eta14to22.pdf");
  cansf_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf-eta14to22.root");
}
