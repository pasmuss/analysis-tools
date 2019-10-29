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

void eff_pT_per_eta_forSF() {

  TFile* dataCin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017C.root","READ");
  TFile* dataDin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017D.root","READ");
  TFile* dataEin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017E.root","READ");
  TFile* dataFin = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017F.root","READ");

  TFile* dataCout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017C_eff_for_sf.root","RECREATE");
  TFile* dataDout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017D_eff_for_sf.root","RECREATE");
  TFile* dataEout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017E_eff_for_sf.root","RECREATE");
  TFile* dataFout = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/Configs_jetTriggerSF/rootfiles/2017F_eff_for_sf.root","RECREATE");

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

  dataCout -> cd();
  TH1F* eff_C_0to1 = (TH1F*)in_C_100_0to1->Clone();
  eff_C_0to1 -> Divide(in_C_60_0to1);
  eff_C_0to1 -> Write();
  TH1F* eff_C_1to14 = (TH1F*)in_C_100_1to14->Clone();
  eff_C_1to14 -> Divide(in_C_60_1to14);
  eff_C_1to14 -> Write();
  TH1F* eff_C_14to22 = (TH1F*)in_C_100_14to22->Clone();
  eff_C_14to22 -> Divide(in_C_60_14to22);
  eff_C_14to22 -> Write();

  dataDout -> cd();
  TH1F* eff_D_0to1 = (TH1F*)in_D_100_0to1->Clone();
  eff_D_0to1 -> Divide(in_D_60_0to1);
  eff_D_0to1 -> Write();
  TH1F* eff_D_1to14 = (TH1F*)in_D_100_1to14->Clone();
  eff_D_1to14 -> Divide(in_D_60_1to14);
  eff_D_1to14 -> Write();
  TH1F* eff_D_14to22 = (TH1F*)in_D_100_14to22->Clone();
  eff_D_14to22 -> Divide(in_D_60_14to22);
  eff_D_14to22 -> Write();

  dataEout -> cd();
  TH1F* eff_E_0to1 = (TH1F*)in_E_100_0to1->Clone();
  eff_E_0to1 -> Divide(in_E_60_0to1);
  eff_E_0to1 -> Write();
  TH1F* eff_E_1to14 = (TH1F*)in_E_100_1to14->Clone();
  eff_E_1to14 -> Divide(in_E_60_1to14);
  eff_E_1to14 -> Write();
  TH1F* eff_E_14to22 = (TH1F*)in_E_100_14to22->Clone();
  eff_E_14to22 -> Divide(in_E_60_14to22);
  eff_E_14to22 -> Write();

  dataFout -> cd();
  TH1F* eff_F_0to1 = (TH1F*)in_F_100_0to1->Clone();
  eff_F_0to1 -> Divide(in_F_60_0to1);
  eff_F_0to1 -> Write();
  TH1F* eff_F_1to14 = (TH1F*)in_F_100_1to14->Clone();
  eff_F_1to14 -> Divide(in_F_60_1to14);
  eff_F_1to14 -> Write();
  TH1F* eff_F_14to22 = (TH1F*)in_F_100_14to22->Clone();
  eff_F_14to22 -> Divide(in_F_60_14to22);
  eff_F_14to22 -> Write();

}
