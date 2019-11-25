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

  TF1* errf_data_1 = new TF1("errf_data_1","0.999*erf(0.039*(x-98.6))",100,500);
  errf_data_1 -> SetLineColor(kRed);
  TF1* errf_data_2 = new TF1("errf_data_2","0.998*erf(0.036*(x-99.03))",100,500);
  errf_data_2 -> SetLineColor(kRed);
  TF1* errf_data_3 = new TF1("errf_data_3","0.999*erf(0.037*(x-101.0))",100,500);
  errf_data_3 -> SetLineColor(kRed);

  TF1* errf_MC_1 = new TF1("errf_MC_1","0.998*erf(0.040*(x-93.59))",100,500);
  errf_MC_1 -> SetLineColor(kBlue);
  TF1* errf_MC_2 = new TF1("errf_MC_2","0.998*erf(0.037*(x-93.35))",100,500);
  errf_MC_2 -> SetLineColor(kBlue);
  TF1* errf_MC_3 = new TF1("errf_MC_3","0.998*erf(0.041*(x-96.22))",100,500);
  errf_MC_3 -> SetLineColor(kBlue);

  TCanvas* can_effs_1 = style.MakeCanvas("can_effs_1","",700,700);
  errf_data_1 -> SetTitle(";p_{T} [GeV];#epsilon");
  errf_data_1 -> Draw();
  errf_MC_1 -> Draw("SAME");
  TLegend* leg_effs_1 = new TLegend(0.37,0.65,0.71,0.75);
  style.SetLegendStyle(leg_effs_1);
  leg_effs_1 -> AddEntry(errf_data_1,"Fit to 2017 data, 0.0 < |#eta| < 1.0","L");
  leg_effs_1 -> AddEntry(errf_MC_1,"Fit to QCD MC, 0.0 < |#eta| < 1.0","L");
  leg_effs_1 -> Draw("SAME");
  can_effs_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff_eta0to1_dataMC.pdf");
  can_effs_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff_eta0to1_dataMC.root");

  TCanvas* can_sf_1 = style.MakeCanvas("can_sf_1","",700,700);
  TF1* sf_1 = new TF1("sf_1", "errf_data_1/errf_MC_1", 100, 500);
  sf_1 -> SetTitle(";p_{T} [GeV];scale factor");
  sf_1 -> GetYaxis() -> SetTitleOffset(1.2);
  sf_1 -> Draw();
  TLegend* leg_sf_1 = new TLegend(0.37,0.65,0.71,0.75);
  style.SetLegendStyle(leg_sf_1);
  leg_sf_1 -> AddEntry(sf_1,"Scale Factor, 0.0 < |#eta| < 1.0","L");
  leg_sf_1 -> Draw("SAME");
  can_sf_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf_eta0to1.pdf");
  can_sf_1 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf_eta0to1.root");

  TCanvas* can_effs_2 = style.MakeCanvas("can_effs_2","",700,700);
  errf_data_2 -> SetTitle(";p_{T} [GeV];#epsilon");
  errf_data_2 -> Draw();
  errf_MC_2 -> Draw("SAME");
  TLegend* leg_effs_2 = new TLegend(0.37,0.65,0.71,0.75);
  style.SetLegendStyle(leg_effs_2);
  leg_effs_2 -> AddEntry(errf_data_2,"Fit to 2017 data, 1.0 < |#eta| < 1.4","L");
  leg_effs_2 -> AddEntry(errf_MC_2,"Fit to QCD MC, 1.0 < |#eta| < 1.4","L");
  leg_effs_2 -> Draw("SAME");
  can_effs_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff_eta1to14_dataMC.pdf");
  can_effs_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff_eta1to14_dataMC.root");

  TCanvas* can_sf_2 = style.MakeCanvas("can_sf_2","",700,700);
  TF1* sf_2 = new TF1("sf_2", "errf_data_2/errf_MC_2", 100, 500);
  sf_2 -> SetTitle(";p_{T} [GeV];scale factor");
  sf_2 -> GetYaxis() -> SetTitleOffset(1.2);
  sf_2 -> Draw();
  TLegend* leg_sf_2 = new TLegend(0.37,0.65,0.71,0.75);
  style.SetLegendStyle(leg_sf_2);
  leg_sf_2 -> AddEntry(sf_2,"Scale Factor, 1.0 < |#eta| < 1.4","L");
  leg_sf_2 -> Draw("SAME");
  can_sf_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf_eta1to14.pdf");
  can_sf_2 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf_eta1to14.root");

  TCanvas* can_effs_3 = style.MakeCanvas("can_effs_3","",700,700);
  errf_data_3 -> SetTitle(";p_{T} [GeV];#epsilon");
  errf_data_3 -> Draw();
  errf_MC_3 -> Draw("SAME");
  TLegend* leg_effs_3 = new TLegend(0.37,0.65,0.71,0.75);
  style.SetLegendStyle(leg_effs_3);
  leg_effs_3 -> AddEntry(errf_data_3,"Fit to 2017 data, 1.4 < |#eta| < 2.2","L");
  leg_effs_3 -> AddEntry(errf_MC_3,"Fit to QCD MC, 1.4 < |#eta| < 2.2","L");
  leg_effs_3 -> Draw("SAME");
  can_effs_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff_eta14to22_dataMC.pdf");
  can_effs_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/eff_eta14to22_dataMC.root");

  TCanvas* can_sf_3 = style.MakeCanvas("can_sf_3","",700,700);
  TF1* sf_3 = new TF1("sf_3", "errf_data_3/errf_MC_3", 100, 500);
  sf_3 -> SetTitle(";p_{T} [GeV];scale factor");
  sf_3 -> GetYaxis() -> SetTitleOffset(1.2);
  sf_3 -> Draw();
  TLegend* leg_sf_3 = new TLegend(0.37,0.65,0.71,0.75);
  style.SetLegendStyle(leg_sf_3);
  leg_sf_3 -> AddEntry(sf_3,"Scale Factor, 1.4 < |#eta| < 2.2","L");
  leg_sf_3 -> Draw("SAME");
  can_sf_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf_eta14to22.pdf");
  can_sf_3 -> SaveAs("Outputdata/TriggerSF/Nov07-19_inclDR_fineBins/sf_eta14to22.root");

}
