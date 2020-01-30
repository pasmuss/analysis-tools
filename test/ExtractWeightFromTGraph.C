#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>

#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

using namespace std;

void ExtractWeightFromTGraph(){

  TFile* btagweightfile = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/data/btag_eff_deepflavour_medium_pt_eta_flavour.root","READ");

  double pt = 178.7;
  double eta = 1.3;
  string flavor = "b";

  string etarange = "0.0-0.5";
  if (eta >= 0.5 && eta < 1.0) etarange = "0.5-1.0";
  else if (eta >= 1.0 && eta < 1.4) etarange = "1.0-1.4";
  else if (eta >= 1.4 && eta < 2.2) etarange = "1.4-2.2";

  string graphname = ("btag_eff_deepflavour_medium_" + flavor + "_pt_eta_" + etarange).c_str();
  cout << "pt: " << pt << ", eta: " << eta << endl;
  cout << graphname << endl;

  TGraphAsymmErrors* evalgraph = (TGraphAsymmErrors*)btagweightfile -> Get(graphname.c_str());
  cout << "weight with eval: " << evalgraph->Eval(pt);

  int dimension = evalgraph -> GetMaxSize();
  cout << dimension << endl;
  for (int i = 0; i < dimension; i++){
    double bincenter = (evalgraph -> GetX())[i];
    //cout << "bin " << i << ", center: " << bincenter << endl;
    double lowerror = evalgraph -> GetErrorXlow(i);
    double higherror = evalgraph -> GetErrorXhigh(i);
    double lowedge = bincenter - lowerror;
    double highedge = bincenter + higherror;
    if (pt >= lowedge && pt <= highedge){
      double weight = (evalgraph -> GetY())[i];
      cout << "bin " << i << " reaching from " << lowedge << " to " << highedge << endl;
      cout << "weight from bin: " << weight << endl;
      break;
    }
  }
}
