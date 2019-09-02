//#include "tdrstyle.C"
#include <iostream>
#include <cstring>
#include <string>

#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "Fit/Fitter.h"
#include "TStyle.h"
#include <iostream>

#include "HbbStylesNew.cc"

using namespace std;

void DrawBtagSFandUncerts(){

  //////////////////////////
  ///      medium        ///
  //////////////////////////

  TF1* mediumbcent = new TF1("mediumbcent","0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x)))",20,1000);//b, central (same for c)

  TF1* mediumbup1 = new TF1("mediumbup1","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.076275914907455444",20,30);//b, +1 sigma
  TF1* mediumbup2 = new TF1("mediumbup2","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.026398291811347008",30,50);
  TF1* mediumbup3 = new TF1("mediumbup3","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.02534114383161068",50,70);
  TF1* mediumbup4 = new TF1("mediumbup4","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.02437339723110199",70,100);
  TF1* mediumbup5 = new TF1("mediumbup5","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.026176376268267632",100,140);
  TF1* mediumbup6 = new TF1("mediumbup6","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.02870459109544754",140,200);
  TF1* mediumbup7 = new TF1("mediumbup7","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.037160992622375488",200,300);
  TF1* mediumbup8 = new TF1("mediumbup8","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.036622315645217896",300,600);
  TF1* mediumbup9 = new TF1("mediumbup9","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.04215230792760849",600,1000);
  TF1* mediumbdown1 = new TF1("mediumbdown1","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.076275914907455444",20,30);//b, -1 sigma
  TF1* mediumbdown2 = new TF1("mediumbdown2","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.026398291811347008",30,50);
  TF1* mediumbdown3 = new TF1("mediumbdown3","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.02534114383161068",50,70);
  TF1* mediumbdown4 = new TF1("mediumbdown4","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.02437339723110199",70,100);
  TF1* mediumbdown5 = new TF1("mediumbdown5","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.026176376268267632",100,140);
  TF1* mediumbdown6 = new TF1("mediumbdown6","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.02870459109544754",140,200);
  TF1* mediumbdown7 = new TF1("mediumbdown7","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.037160992622375488",200,300);
  TF1* mediumbdown8 = new TF1("mediumbdown8","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.036622315645217896",300,600);
  TF1* mediumbdown9 = new TF1("mediumbdown9","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.04215230792760849",600,1000);

  TF1* mediumcup1 = new TF1("mediumcup1","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.22882774472236633",20,30);//c, +1 sigma
  TF1* mediumcup2 = new TF1("mediumcup2","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.079194873571395874",30,50);
  TF1* mediumcup3 = new TF1("mediumcup3","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.07602342963218689",50,70);
  TF1* mediumcup4 = new TF1("mediumcup4","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.073120191693305969",70,100);
  TF1* mediumcup5 = new TF1("mediumcup5","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.078529126942157745",100,140);
  TF1* mediumcup6 = new TF1("mediumcup6","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.086113773286342621",140,200);
  TF1* mediumcup7 = new TF1("mediumcup7","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.11148297786712646",200,300);
  TF1* mediumcup8 = new TF1("mediumcup8","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.10986694693565369",300,600);
  TF1* mediumcup9 = new TF1("mediumcup9","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))+0.12645691633224487",600,1000);
  TF1* mediumcdown1 = new TF1("mediumcdown1","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.22882774472236633",20,30);//c, -1 sigma
  TF1* mediumcdown2 = new TF1("mediumcdown2","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.079194873571395874",30,50);
  TF1* mediumcdown3 = new TF1("mediumcdown3","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.07602342963218689",50,70);
  TF1* mediumcdown4 = new TF1("mediumcdown4","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.073120191693305969",70,100);
  TF1* mediumcdown5 = new TF1("mediumcdown5","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.078529126942157745",100,140);
  TF1* mediumcdown6 = new TF1("mediumcdown6","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.086113773286342621",140,200);
  TF1* mediumcdown7 = new TF1("mediumcdown7","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.11148297786712646",200,300);
  TF1* mediumcdown8 = new TF1("mediumcdown8","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.10986694693565369",300,600);
  TF1* mediumcdown9 = new TF1("mediumcdown9","(0.991757*((1.+(0.0209615*x))/(1.+(0.0234962*x))))-0.12645691633224487",600,1000);

  HbbStylesNew style;
  style.SetStyle();
  gStyle->SetOptStat(0);

  TCanvas* canmediumbc = style.MakeCanvas("canmediumbc", "b/c, medium", 700,700);

  mediumbcent -> Draw("FC");

  mediumcup1 -> Draw("FCSAME");
  mediumcup2 -> Draw("FCSAME");
  mediumcup3 -> Draw("FCSAME");
  mediumcup4 -> Draw("FCSAME");
  mediumcup5 -> Draw("FCSAME");
  mediumcup6 -> Draw("FCSAME");
  mediumcup7 -> Draw("FCSAME");
  mediumcup8 -> Draw("FCSAME");
  mediumcup9 -> Draw("FCSAME");

  mediumbup1 -> Draw("FCSAME");
  mediumbup2 -> Draw("FCSAME");
  mediumbup3 -> Draw("FCSAME");
  mediumbup4 -> Draw("FCSAME");
  mediumbup5 -> Draw("FCSAME");
  mediumbup6 -> Draw("FCSAME");
  mediumbup7 -> Draw("FCSAME");
  mediumbup8 -> Draw("FCSAME");
  mediumbup9 -> Draw("FCSAME");

  mediumbcent -> Draw("FCSAME");

  mediumbdown1 -> Draw("FCSAME");
  mediumbdown2 -> Draw("FCSAME");
  mediumbdown3 -> Draw("FCSAME");
  mediumbdown4 -> Draw("FCSAME");
  mediumbdown5 -> Draw("FCSAME");
  mediumbdown6 -> Draw("FCSAME");
  mediumbdown7 -> Draw("FCSAME");
  mediumbdown8 -> Draw("FCSAME");
  mediumbdown9 -> Draw("FCSAME");

  mediumcdown1 -> Draw("FCSAME");
  mediumcdown2 -> Draw("FCSAME");
  mediumcdown3 -> Draw("FCSAME");
  mediumcdown4 -> Draw("FCSAME");
  mediumcdown5 -> Draw("FCSAME");
  mediumcdown6 -> Draw("FCSAME");
  mediumcdown7 -> Draw("FCSAME");
  mediumcdown8 -> Draw("FCSAME");
  mediumcdown9 -> Draw("FCSAME");

  mediumbcent -> SetMaximum(1.2);
  mediumbcent -> SetMinimum(0.7);
  mediumbcent -> SetTitle(";jet p_{T} [GeV]; scale factor (bc)");

  mediumbcent -> GetYaxis() -> SetTitleOffset(1.4);

  canmediumbc -> SetLeftMargin(0.16);

  mediumbcent -> SetLineColor(kBlack);

  mediumbup1 -> SetLineColor(kBlack);
  mediumbup2 -> SetLineColor(kBlack);
  mediumbup3 -> SetLineColor(kBlack);
  mediumbup4 -> SetLineColor(kBlack);
  mediumbup5 -> SetLineColor(kBlack);
  mediumbup6 -> SetLineColor(kBlack);
  mediumbup7 -> SetLineColor(kBlack);
  mediumbup8 -> SetLineColor(kBlack);
  mediumbup9 -> SetLineColor(kBlack);
  mediumbdown1 -> SetLineColor(kBlack);
  mediumbdown2 -> SetLineColor(kBlack);
  mediumbdown3 -> SetLineColor(kBlack);
  mediumbdown4 -> SetLineColor(kBlack);
  mediumbdown5 -> SetLineColor(kBlack);
  mediumbdown6 -> SetLineColor(kBlack);
  mediumbdown7 -> SetLineColor(kBlack);
  mediumbdown8 -> SetLineColor(kBlack);
  mediumbdown9 -> SetLineColor(kBlack);
  mediumcup1 -> SetLineColor(kBlack);
  mediumcup2 -> SetLineColor(kBlack);
  mediumcup3 -> SetLineColor(kBlack);
  mediumcup4 -> SetLineColor(kBlack);
  mediumcup5 -> SetLineColor(kBlack);
  mediumcup6 -> SetLineColor(kBlack);
  mediumcup7 -> SetLineColor(kBlack);
  mediumcup8 -> SetLineColor(kBlack);
  mediumcup9 -> SetLineColor(kBlack);
  mediumcdown1 -> SetLineColor(kBlack);
  mediumcdown2 -> SetLineColor(kBlack);
  mediumcdown3 -> SetLineColor(kBlack);
  mediumcdown4 -> SetLineColor(kBlack);
  mediumcdown5 -> SetLineColor(kBlack);
  mediumcdown6 -> SetLineColor(kBlack);
  mediumcdown7 -> SetLineColor(kBlack);
  mediumcdown8 -> SetLineColor(kBlack);
  mediumcdown9 -> SetLineColor(kBlack);

  mediumbup1 -> SetFillStyle(1001);
  mediumbup2 -> SetFillStyle(1001);
  mediumbup3 -> SetFillStyle(1001);
  mediumbup4 -> SetFillStyle(1001);
  mediumbup5 -> SetFillStyle(1001);
  mediumbup6 -> SetFillStyle(1001);
  mediumbup7 -> SetFillStyle(1001);
  mediumbup8 -> SetFillStyle(1001);
  mediumbup9 -> SetFillStyle(1001);

  mediumbup1 -> SetFillColor(5);
  mediumbup2 -> SetFillColor(5);
  mediumbup3 -> SetFillColor(5);
  mediumbup4 -> SetFillColor(5);
  mediumbup5 -> SetFillColor(5);
  mediumbup6 -> SetFillColor(5);
  mediumbup7 -> SetFillColor(5);
  mediumbup8 -> SetFillColor(5);
  mediumbup9 -> SetFillColor(5);
  
  mediumcup1 -> SetFillStyle(1001);
  mediumcup2 -> SetFillStyle(1001);
  mediumcup3 -> SetFillStyle(1001);
  mediumcup4 -> SetFillStyle(1001);
  mediumcup5 -> SetFillStyle(1001);
  mediumcup6 -> SetFillStyle(1001);
  mediumcup7 -> SetFillStyle(1001);
  mediumcup8 -> SetFillStyle(1001);
  mediumcup9 -> SetFillStyle(1001);

  mediumcup1 -> SetFillColor(7);
  mediumcup2 -> SetFillColor(7);
  mediumcup3 -> SetFillColor(7);
  mediumcup4 -> SetFillColor(7);
  mediumcup5 -> SetFillColor(7);
  mediumcup6 -> SetFillColor(7);
  mediumcup7 -> SetFillColor(7);
  mediumcup8 -> SetFillColor(7);
  mediumcup9 -> SetFillColor(7);

  mediumbdown1 -> SetFillStyle(1001);
  mediumbdown2 -> SetFillStyle(1001);
  mediumbdown3 -> SetFillStyle(1001);
  mediumbdown4 -> SetFillStyle(1001);
  mediumbdown5 -> SetFillStyle(1001);
  mediumbdown6 -> SetFillStyle(1001);
  mediumbdown7 -> SetFillStyle(1001);
  mediumbdown8 -> SetFillStyle(1001);
  mediumbdown9 -> SetFillStyle(1001);

  mediumbdown1 -> SetFillColor(7);
  mediumbdown2 -> SetFillColor(7);
  mediumbdown3 -> SetFillColor(7);
  mediumbdown4 -> SetFillColor(7);
  mediumbdown5 -> SetFillColor(7);
  mediumbdown6 -> SetFillColor(7);
  mediumbdown7 -> SetFillColor(7);
  mediumbdown8 -> SetFillColor(7);
  mediumbdown9 -> SetFillColor(7);

  mediumcdown1 -> SetFillStyle(1001);
  mediumcdown2 -> SetFillStyle(1001);
  mediumcdown3 -> SetFillStyle(1001);
  mediumcdown4 -> SetFillStyle(1001);
  mediumcdown5 -> SetFillStyle(1001);
  mediumcdown6 -> SetFillStyle(1001);
  mediumcdown7 -> SetFillStyle(1001);
  mediumcdown8 -> SetFillStyle(1001);
  mediumcdown9 -> SetFillStyle(1001);

  mediumcdown1 -> SetFillColor(10);
  mediumcdown2 -> SetFillColor(10);
  mediumcdown3 -> SetFillColor(10);
  mediumcdown4 -> SetFillColor(10);
  mediumcdown5 -> SetFillColor(10);
  mediumcdown6 -> SetFillColor(10);
  mediumcdown7 -> SetFillColor(10);
  mediumcdown8 -> SetFillColor(10);
  mediumcdown9 -> SetFillColor(10);

  mediumbcent -> SetFillStyle(1001);
  mediumbcent -> SetFillColor(5);
  
  mediumbup1 -> SetLineStyle(7);
  mediumbup2 -> SetLineStyle(7);
  mediumbup3 -> SetLineStyle(7);
  mediumbup4 -> SetLineStyle(7);
  mediumbup5 -> SetLineStyle(7);
  mediumbup6 -> SetLineStyle(7);
  mediumbup7 -> SetLineStyle(7);
  mediumbup8 -> SetLineStyle(7);
  mediumbup9 -> SetLineStyle(7);
  mediumbdown1 -> SetLineStyle(7);
  mediumbdown2 -> SetLineStyle(7);
  mediumbdown3 -> SetLineStyle(7);
  mediumbdown4 -> SetLineStyle(7);
  mediumbdown5 -> SetLineStyle(7);
  mediumbdown6 -> SetLineStyle(7);
  mediumbdown7 -> SetLineStyle(7);
  mediumbdown8 -> SetLineStyle(7);
  mediumbdown9 -> SetLineStyle(7);

  mediumcup1 -> SetLineStyle(4);
  mediumcup2 -> SetLineStyle(4);
  mediumcup3 -> SetLineStyle(4);
  mediumcup4 -> SetLineStyle(4);
  mediumcup5 -> SetLineStyle(4);
  mediumcup6 -> SetLineStyle(4);
  mediumcup7 -> SetLineStyle(4);
  mediumcup8 -> SetLineStyle(4);
  mediumcup9 -> SetLineStyle(4);
  mediumcdown1 -> SetLineStyle(4);
  mediumcdown2 -> SetLineStyle(4);
  mediumcdown3 -> SetLineStyle(4);
  mediumcdown4 -> SetLineStyle(4);
  mediumcdown5 -> SetLineStyle(4);
  mediumcdown6 -> SetLineStyle(4);
  mediumcdown7 -> SetLineStyle(4);
  mediumcdown8 -> SetLineStyle(4);
  mediumcdown9 -> SetLineStyle(4);

  TLegend* legmedbc = new TLegend(0.58,0.72,0.98,0.89);
  style.SetLegendStyle(legmedbc);
  legmedbc -> SetHeader("medium wp, deepJet");
  legmedbc -> AddEntry(mediumbcent,"b tag sf (bc)","L");
  legmedbc -> AddEntry(mediumcup1,"uncertainty c","F");
  legmedbc -> AddEntry(mediumbup1,"uncertainty b","F");

  legmedbc -> Draw("SAME");

  canmediumbc -> SaveAs("Outputdata/dfl-btag-sf-medium-bc-updown.pdf");
  
  TF1* mediumlcent = new TF1("mediumlcent","1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x",20,1000);//light/udsg, central
  TF1* mediumlup = new TF1("mediumlup","(1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x)*(1+(0.100661+0.000294578*x+-3.2739e-07*x*x))",20,1000);//light/udsg, +1 sigma
  TF1* mediumldown = new TF1("mediumldown","(1.40779+-0.00094558*x+8.74982e-07*x*x+-4.67814/x)*(1-(0.100661+0.000294578*x+-3.2739e-07*x*x))",20,1000);//light/udsg, -1 sigma

  TCanvas* canmediumudsg = style.MakeCanvas("canmediumudsg", "udsg, medium", 700,700);

  mediumlup -> Draw("FC");
  mediumlcent -> Draw("FCSAME");
  mediumldown -> Draw("FCSAME");

  mediumlup -> SetTitle(";jet p_{T} [GeV]; scale factor (udsg)");
  
  mediumlup -> SetMinimum(0.9);
  mediumlup -> SetMaximum(1.5);

  mediumlup -> SetLineStyle(7);
  mediumlup -> SetFillColor(5);
  mediumlup -> SetFillStyle(1001);

  mediumlcent -> SetFillColor(5);
  mediumlcent -> SetFillStyle(1001);

  mediumldown -> SetLineStyle(7);
  mediumldown -> SetFillColor(10);
  mediumldown -> SetFillStyle(1001);

  mediumlup -> GetYaxis() -> SetTitleOffset(1.1);

  TLegend* legmedudsg = new TLegend(0.44,0.74,0.8,0.91);
  style.SetLegendStyle(legmedudsg);
  legmedudsg -> SetHeader("medium wp, deepJet");
  legmedudsg -> AddEntry(mediumlcent,"b tag sf (udsg)","L");
  legmedudsg -> AddEntry(mediumlup,"uncertainty","F");

  legmedudsg -> Draw("SAME");
  
  canmediumudsg -> SaveAs("Outputdata/dfl-btag-sf-medium-udsg-updown.pdf");

  //////////////////////////
  ///       tight        ///
  //////////////////////////

  TF1* tightbcent = new TF1("tightbcent","0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x)))",20,1000);//b, central (same for c)

  TF1* tightbup1 = new TF1("tightbup1","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.083331704139709473",20,30);//b, +1 sigma
  TF1* tightbup2 = new TF1("tightbup2","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.034065559506416321",30,50);
  TF1* tightbup3 = new TF1("tightbup3","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.031077833846211433",50,70);
  TF1* tightbup4 = new TF1("tightbup4","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.027616133913397789",70,100);
  TF1* tightbup5 = new TF1("tightbup5","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.031399231404066086",100,140);
  TF1* tightbup6 = new TF1("tightbup6","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.034734658896923065",140,200);
  TF1* tightbup7 = new TF1("tightbup7","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.044301345944404602",200,300);
  TF1* tightbup8 = new TF1("tightbup8","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.050837442278862",300,600);
  TF1* tightbup9 = new TF1("tightbup9","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.040907666087150574",600,1000);
  TF1* tightbdown1 = new TF1("tightbdown1","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.083331704139709473",20,30);//b, -1 sigma
  TF1* tightbdown2 = new TF1("tightbdown2","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.034065559506416321",30,50);
  TF1* tightbdown3 = new TF1("tightbdown3","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.031077833846211433",50,70);
  TF1* tightbdown4 = new TF1("tightbdown4","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.027616133913397789",70,100);
  TF1* tightbdown5 = new TF1("tightbdown5","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.031399231404066086",100,140);
  TF1* tightbdown6 = new TF1("tightbdown6","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.034734658896923065",140,200);
  TF1* tightbdown7 = new TF1("tightbdown7","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.044301345944404602",200,300);
  TF1* tightbdown8 = new TF1("tightbdown8","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.050837442278862",300,600);
  TF1* tightbdown9 = new TF1("tightbdown9","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.040907666087150574",600,1000);

  TF1* tightcup1 = new TF1("tightcup1","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.29166096448898315",20,30);//c, +1 sigma
  TF1* tightcup2 = new TF1("tightcup2","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.11922945827245712",30,50);
  TF1* tightcup3 = new TF1("tightcup3","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.10877241939306259",50,70);
  TF1* tightcup4 = new TF1("tightcup4","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.096656471490859985",70,100);
  TF1* tightcup5 = new TF1("tightcup5","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.10989730805158615",100,140);
  TF1* tightcup6 = new TF1("tightcup6","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.12157130241394043",140,200);
  TF1* tightcup7 = new TF1("tightcup7","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.1550547182559967",200,300);
  TF1* tightcup8 = new TF1("tightcup8","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.1779310405254364",300,600);
  TF1* tightcup9 = new TF1("tightcup9","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))+0.14317682385444641",600,1000);
  TF1* tightcdown1 = new TF1("tightcdown1","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.29166096448898315",20,30);//c, -1 sigma
  TF1* tightcdown2 = new TF1("tightcdown2","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.11922945827245712",30,50);
  TF1* tightcdown3 = new TF1("tightcdown3","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.10877241939306259",50,70);
  TF1* tightcdown4 = new TF1("tightcdown4","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.096656471490859985",70,100);
  TF1* tightcdown5 = new TF1("tightcdown5","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.10989730805158615",100,140);
  TF1* tightcdown6 = new TF1("tightcdown6","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.12157130241394043",140,200);
  TF1* tightcdown7 = new TF1("tightcdown7","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.1550547182559967",200,300);
  TF1* tightcdown8 = new TF1("tightcdown8","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.1779310405254364",300,600);
  TF1* tightcdown9 = new TF1("tightcdown9","(0.908648*((1.+(0.00516407*x))/(1.+(0.00564675*x))))-0.14317682385444641",600,1000);
  
  TCanvas* cantightbc = style.MakeCanvas("cantightbc", "b/c, tight", 700,700);

  tightbcent -> Draw("FC");

  tightcup1 -> Draw("FCSAME");
  tightcup2 -> Draw("FCSAME");
  tightcup3 -> Draw("FCSAME");
  tightcup4 -> Draw("FCSAME");
  tightcup5 -> Draw("FCSAME");
  tightcup6 -> Draw("FCSAME");
  tightcup7 -> Draw("FCSAME");
  tightcup8 -> Draw("FCSAME");
  tightcup9 -> Draw("FCSAME");

  tightbup1 -> Draw("FCSAME");
  tightbup2 -> Draw("FCSAME");
  tightbup3 -> Draw("FCSAME");
  tightbup4 -> Draw("FCSAME");
  tightbup5 -> Draw("FCSAME");
  tightbup6 -> Draw("FCSAME");
  tightbup7 -> Draw("FCSAME");
  tightbup8 -> Draw("FCSAME");
  tightbup9 -> Draw("FCSAME");

  tightbcent -> Draw("FCSAME");

  tightbdown1 -> Draw("FCSAME");
  tightbdown2 -> Draw("FCSAME");
  tightbdown3 -> Draw("FCSAME");
  tightbdown4 -> Draw("FCSAME");
  tightbdown5 -> Draw("FCSAME");
  tightbdown6 -> Draw("FCSAME");
  tightbdown7 -> Draw("FCSAME");
  tightbdown8 -> Draw("FCSAME");
  tightbdown9 -> Draw("FCSAME");

  tightcdown1 -> Draw("FCSAME");
  tightcdown2 -> Draw("FCSAME");
  tightcdown3 -> Draw("FCSAME");
  tightcdown4 -> Draw("FCSAME");
  tightcdown5 -> Draw("FCSAME");
  tightcdown6 -> Draw("FCSAME");
  tightcdown7 -> Draw("FCSAME");
  tightcdown8 -> Draw("FCSAME");
  tightcdown9 -> Draw("FCSAME");

  tightbcent -> SetMaximum(1.2);
  tightbcent -> SetMinimum(0.6);
  tightbcent -> SetTitle(";jet p_{T} [GeV]; scale factor (bc)");
  tightbcent -> GetYaxis() -> SetTitleOffset(1.1);

  tightbcent -> SetLineColor(kBlack);

  tightbup1 -> SetLineColor(kBlack);
  tightbup2 -> SetLineColor(kBlack);
  tightbup3 -> SetLineColor(kBlack);
  tightbup4 -> SetLineColor(kBlack);
  tightbup5 -> SetLineColor(kBlack);
  tightbup6 -> SetLineColor(kBlack);
  tightbup7 -> SetLineColor(kBlack);
  tightbup8 -> SetLineColor(kBlack);
  tightbup9 -> SetLineColor(kBlack);
  tightbdown1 -> SetLineColor(kBlack);
  tightbdown2 -> SetLineColor(kBlack);
  tightbdown3 -> SetLineColor(kBlack);
  tightbdown4 -> SetLineColor(kBlack);
  tightbdown5 -> SetLineColor(kBlack);
  tightbdown6 -> SetLineColor(kBlack);
  tightbdown7 -> SetLineColor(kBlack);
  tightbdown8 -> SetLineColor(kBlack);
  tightbdown9 -> SetLineColor(kBlack);
  tightcup1 -> SetLineColor(kBlack);
  tightcup2 -> SetLineColor(kBlack);
  tightcup3 -> SetLineColor(kBlack);
  tightcup4 -> SetLineColor(kBlack);
  tightcup5 -> SetLineColor(kBlack);
  tightcup6 -> SetLineColor(kBlack);
  tightcup7 -> SetLineColor(kBlack);
  tightcup8 -> SetLineColor(kBlack);
  tightcup9 -> SetLineColor(kBlack);
  tightcdown1 -> SetLineColor(kBlack);
  tightcdown2 -> SetLineColor(kBlack);
  tightcdown3 -> SetLineColor(kBlack);
  tightcdown4 -> SetLineColor(kBlack);
  tightcdown5 -> SetLineColor(kBlack);
  tightcdown6 -> SetLineColor(kBlack);
  tightcdown7 -> SetLineColor(kBlack);
  tightcdown8 -> SetLineColor(kBlack);
  tightcdown9 -> SetLineColor(kBlack);

  tightbup1 -> SetFillStyle(1001);
  tightbup2 -> SetFillStyle(1001);
  tightbup3 -> SetFillStyle(1001);
  tightbup4 -> SetFillStyle(1001);
  tightbup5 -> SetFillStyle(1001);
  tightbup6 -> SetFillStyle(1001);
  tightbup7 -> SetFillStyle(1001);
  tightbup8 -> SetFillStyle(1001);
  tightbup9 -> SetFillStyle(1001);

  tightbup1 -> SetFillColor(5);
  tightbup2 -> SetFillColor(5);
  tightbup3 -> SetFillColor(5);
  tightbup4 -> SetFillColor(5);
  tightbup5 -> SetFillColor(5);
  tightbup6 -> SetFillColor(5);
  tightbup7 -> SetFillColor(5);
  tightbup8 -> SetFillColor(5);
  tightbup9 -> SetFillColor(5);
  
  tightcup1 -> SetFillStyle(1001);
  tightcup2 -> SetFillStyle(1001);
  tightcup3 -> SetFillStyle(1001);
  tightcup4 -> SetFillStyle(1001);
  tightcup5 -> SetFillStyle(1001);
  tightcup6 -> SetFillStyle(1001);
  tightcup7 -> SetFillStyle(1001);
  tightcup8 -> SetFillStyle(1001);
  tightcup9 -> SetFillStyle(1001);

  tightcup1 -> SetFillColor(7);
  tightcup2 -> SetFillColor(7);
  tightcup3 -> SetFillColor(7);
  tightcup4 -> SetFillColor(7);
  tightcup5 -> SetFillColor(7);
  tightcup6 -> SetFillColor(7);
  tightcup7 -> SetFillColor(7);
  tightcup8 -> SetFillColor(7);
  tightcup9 -> SetFillColor(7);

  tightbdown1 -> SetFillStyle(1001);
  tightbdown2 -> SetFillStyle(1001);
  tightbdown3 -> SetFillStyle(1001);
  tightbdown4 -> SetFillStyle(1001);
  tightbdown5 -> SetFillStyle(1001);
  tightbdown6 -> SetFillStyle(1001);
  tightbdown7 -> SetFillStyle(1001);
  tightbdown8 -> SetFillStyle(1001);
  tightbdown9 -> SetFillStyle(1001);

  tightbdown1 -> SetFillColor(7);
  tightbdown2 -> SetFillColor(7);
  tightbdown3 -> SetFillColor(7);
  tightbdown4 -> SetFillColor(7);
  tightbdown5 -> SetFillColor(7);
  tightbdown6 -> SetFillColor(7);
  tightbdown7 -> SetFillColor(7);
  tightbdown8 -> SetFillColor(7);
  tightbdown9 -> SetFillColor(7);

  tightcdown1 -> SetFillStyle(1001);
  tightcdown2 -> SetFillStyle(1001);
  tightcdown3 -> SetFillStyle(1001);
  tightcdown4 -> SetFillStyle(1001);
  tightcdown5 -> SetFillStyle(1001);
  tightcdown6 -> SetFillStyle(1001);
  tightcdown7 -> SetFillStyle(1001);
  tightcdown8 -> SetFillStyle(1001);
  tightcdown9 -> SetFillStyle(1001);

  tightcdown1 -> SetFillColor(10);
  tightcdown2 -> SetFillColor(10);
  tightcdown3 -> SetFillColor(10);
  tightcdown4 -> SetFillColor(10);
  tightcdown5 -> SetFillColor(10);
  tightcdown6 -> SetFillColor(10);
  tightcdown7 -> SetFillColor(10);
  tightcdown8 -> SetFillColor(10);
  tightcdown9 -> SetFillColor(10);

  tightbcent -> SetFillStyle(1001);
  tightbcent -> SetFillColor(5);
  
  tightbup1 -> SetLineStyle(7);
  tightbup2 -> SetLineStyle(7);
  tightbup3 -> SetLineStyle(7);
  tightbup4 -> SetLineStyle(7);
  tightbup5 -> SetLineStyle(7);
  tightbup6 -> SetLineStyle(7);
  tightbup7 -> SetLineStyle(7);
  tightbup8 -> SetLineStyle(7);
  tightbup9 -> SetLineStyle(7);
  tightbdown1 -> SetLineStyle(7);
  tightbdown2 -> SetLineStyle(7);
  tightbdown3 -> SetLineStyle(7);
  tightbdown4 -> SetLineStyle(7);
  tightbdown5 -> SetLineStyle(7);
  tightbdown6 -> SetLineStyle(7);
  tightbdown7 -> SetLineStyle(7);
  tightbdown8 -> SetLineStyle(7);
  tightbdown9 -> SetLineStyle(7);

  tightcup1 -> SetLineStyle(4);
  tightcup2 -> SetLineStyle(4);
  tightcup3 -> SetLineStyle(4);
  tightcup4 -> SetLineStyle(4);
  tightcup5 -> SetLineStyle(4);
  tightcup6 -> SetLineStyle(4);
  tightcup7 -> SetLineStyle(4);
  tightcup8 -> SetLineStyle(4);
  tightcup9 -> SetLineStyle(4);
  tightcdown1 -> SetLineStyle(4);
  tightcdown2 -> SetLineStyle(4);
  tightcdown3 -> SetLineStyle(4);
  tightcdown4 -> SetLineStyle(4);
  tightcdown5 -> SetLineStyle(4);
  tightcdown6 -> SetLineStyle(4);
  tightcdown7 -> SetLineStyle(4);
  tightcdown8 -> SetLineStyle(4);
  tightcdown9 -> SetLineStyle(4);

  TLegend* legtightbc = new TLegend(0.58,0.72,0.98,0.89);
  style.SetLegendStyle(legtightbc);
  legtightbc -> SetHeader("tight wp, deepJet");
  legtightbc -> AddEntry(tightbcent,"b tag sf (bc)","L");
  legtightbc -> AddEntry(tightcup1,"uncertainty c","F");
  legtightbc -> AddEntry(tightbup1,"uncertainty b","F");

  legtightbc -> Draw("SAME");


  cantightbc -> SaveAs("Outputdata/dfl-btag-sf-tight-bc-updown.pdf");

  TF1* tightlcent = new TF1("tightlcent","0.952956+0.000569069*x+-1.88872e-06*x*x+1.25729e-09*x*x*x",20,1000);//light/udsg, central
  TF1* tightlup = new TF1("tightlup","(0.952956+0.000569069*x+-1.88872e-06*x*x+1.25729e-09*x*x*x)*(1+(0.232956+0.000143975*x+-1.66524e-07*x*x))",20,1000);//light/udsg, +1 sigma
  TF1* tightldown = new TF1("tightldown","(0.952956+0.000569069*x+-1.88872e-06*x*x+1.25729e-09*x*x*x)*(1-(0.232956+0.000143975*x+-1.66524e-07*x*x))",20,1000);//light/udsg, -1 sigma

  TCanvas* cantightudsg = style.MakeCanvas("cantightudsg", "udsg, tight", 700,700);

  tightlup -> Draw("FC");
  tightlcent -> Draw("FCSAME");
  tightldown -> Draw("FCSAME");

  tightlup -> GetYaxis() -> SetTitleOffset(1.2);
  
  tightlup -> SetMinimum(0.5);
  tightlup -> SetMaximum(1.5);

  tightlup -> SetTitle(";jet p_{T} [GeV]; scale factor (udsg)");

  tightlup -> SetLineStyle(7);
  tightlup -> SetFillColor(5);
  tightlup -> SetFillStyle(1001);

  tightlcent -> SetFillColor(5);
  tightlcent -> SetFillStyle(1001);

  tightldown -> SetLineStyle(7);
  tightldown -> SetFillColor(10);
  tightldown -> SetFillStyle(1001);

  TLegend* legtightudsg = new TLegend(0.44,0.74,0.8,0.91);
  style.SetLegendStyle(legtightudsg);
  legtightudsg -> SetHeader("tight wp, deepJet");
  legtightudsg -> AddEntry(tightlcent,"b tag sf (udsg)","L");
  legtightudsg -> AddEntry(tightlup,"uncertainty","F");

  legtightudsg -> Draw("SAME");

  
  cantightudsg -> SaveAs("Outputdata/dfl-btag-sf-tight-udsg-updown.pdf");

}
