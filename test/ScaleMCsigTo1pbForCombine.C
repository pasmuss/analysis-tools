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
#include "TMath.h"

#include "HbbStylesNew.cc"

using namespace std;

void ScaleMCsigTo1pbForCombine(string dir_){

  TH1::SetDefaultSumw2();

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  

}
