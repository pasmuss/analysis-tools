#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

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

void FitsPseudoTF() {

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TCanvas* can = style.MakeCanvas("can","",700,700);

  TFile* f_in = new TFile("Outputdata/TF_bias/Pseudos1904.root","READ");
  TH1F* tf_in = (TH1F*)f_in->Get("TFHist");

  TF1* fitfunction1a = new TF1("fitfunction1a","[0]*erf([2]*(x-[1]))",200,500);//simple erf
  TF1* fitfunction1b = new TF1("fitfunction1b","[0]*erf([2]*(x-[1]))*(1+[3]*x)",200,500);//erf times linear decrease at higher masses

  TF1* fitfunction2 = new TF1("fitfunction2","[0]*erf([2]*(x-[1]))*(1+[3]*x)",200,2000);//erf times linear decrease at higher masses
  TF1* fitfunction20 = new TF1("fitfunction20","[0]*erf((7.5e-3)*(x-93))*(1-(1.5e-4)*x)",200,2000);//ext erf with gen parameters
  TF1* fitfunction2a = new TF1("fitfunction2a","[0]*erf([2]*(x-[1]))",260,785);//simple erf
  TF1* fitfunction2b = new TF1("fitfunction2b","[0]*x+[1]",260,785);//ax+b
  TF1* fitfunction2c = new TF1("fitfunction2c","[0]*x*x+[1]*x+[2]",260,785);//ax^2+bx+c
  
  TF1* fitfunction3 = new TF1("fitfunction3","[0]*x+[1]",390,1270);//ax+b
  TF1* fitfunction4 = new TF1("fitfunction4","[0]*x+[1]",500,2000);//ax+b

  fitfunction1a -> SetParameters(0.16,93,7.5e-3);
  fitfunction1b -> SetParameters(0.16,93,7.5e-3,-1.5e-4);

  fitfunction2 -> SetParameters(0.16,93,7.5e-3,-1.5e-4);
  fitfunction20 -> SetParameter(0,0.16);

  fitfunction2 -> SetLineColor(kRed-3);
  fitfunction20 -> SetLineColor(kRed-3);
  fitfunction2a -> SetLineColor(kRed);
  fitfunction2b -> SetLineColor(kMagenta);
  fitfunction2c -> SetLineColor(kOrange);

  fitfunction3 -> SetLineColor(kCyan);
  fitfunction4 -> SetLineColor(kBlue);

  //tf_in -> Fit(fitfunction1a,"R");
  //TFitResultPtr r1a = tf_in->Fit(fitfunction1a,"RS");
  //cout << "chi2/ndf = " << r1a->Chi2() << "/" << r1a->Ndf() << " = " << r1a->Chi2()/r1a->Ndf() << ", prob = " << r1a->Prob() << endl;

  tf_in -> Fit(fitfunction1b,"R");
  TFitResultPtr r1b = tf_in->Fit(fitfunction1b,"RS");
  cout << "chi2/ndf = " << r1b->Chi2() << "/" << r1b->Ndf() << " = " << r1b->Chi2()/r1b->Ndf() << ", prob = " << r1b->Prob() << endl;

  //tf_in -> Fit(fitfunction2,"R");
  //TFitResultPtr r2 = tf_in->Fit(fitfunction2,"RS");
  //cout << "chi2/ndf = " << r2->Chi2() << "/" << r2->Ndf() << " = " << r2->Chi2()/r2->Ndf() << ", prob = " << r2->Prob() << endl;

  //tf_in -> Fit(fitfunction20,"R");
  //TFitResultPtr r20 = tf_in->Fit(fitfunction20,"RS");
  //cout << "chi2/ndf = " << r20->Chi2() << "/" << r20->Ndf() << " = " << r20->Chi2()/r20->Ndf() << ", prob = " << r20->Prob() << endl;

  //tf_in -> Fit(fitfunction2a,"R");
  //TFitResultPtr r2a = tf_in->Fit(fitfunction2a,"RS");
  //cout << "chi2/ndf = " << r2a->Chi2() << "/" << r2a->Ndf() << " = " << r2a->Chi2()/r2a->Ndf() << ", prob = " << r2a->Prob() << endl;

  //tf_in -> Fit(fitfunction2b,"R");
  //TFitResultPtr r2b = tf_in->Fit(fitfunction2b,"RS");
  //cout << "chi2/ndf = " << r2b->Chi2() << "/" << r2b->Ndf() << " = " << r2b->Chi2()/r2b->Ndf() << ", prob = " << r2b->Prob() << endl;

  //tf_in -> Fit(fitfunction2c,"R");
  //TFitResultPtr r2c = tf_in->Fit(fitfunction2c,"RS");
  //cout << "chi2/ndf = " << r2c->Chi2() << "/" << r2c->Ndf() << " = " << r2c->Chi2()/r2c->Ndf() << ", prob = " << r2c->Prob() << endl;

  //tf_in -> Fit(fitfunction3,"R");
  //TFitResultPtr r3 = tf_in->Fit(fitfunction3,"RS");
  //cout << "chi2/ndf = " << r3->Chi2() << "/" << r3->Ndf() << " = " << r3->Chi2()/r3->Ndf() << ", prob = " << r3->Prob() << endl;

  //tf_in -> Fit(fitfunction4,"R");
  //TFitResultPtr r4 = tf_in->Fit(fitfunction4,"RS");
  //cout << "chi2/ndf = " << r4->Chi2() << "/" << r4->Ndf() << " = " << r4->Chi2()/r4->Ndf() << ", prob = " << r4->Prob() << endl;

  can -> SaveAs("Outputdata/TF_bias/TF-SR1_exterf_1904.pdf");

}
