#include <sstream>

using namespace std;

void PrepareHistograms()
{  

   bool NLO = true;
   std::string selection("nominal");
   std::string observable("m12_mujsel");
   //          std::string observable("m12_mujsel_j4veto30");
     
   int nmassps = 12;
   if( !NLO ) nmassps = 3;
   int mass[nmassps];
   if ( NLO )
     {
       mass[0] = 120;
       mass[1] = 130;
       mass[2] = 140;
       mass[3] = 160;
       mass[4] = 180;
       mass[5] = 200;
       mass[6] = 250;
       mass[7] = 350;
       mass[8] = 400;
       mass[9] = 450;
       mass[10] = 500;
       mass[11] = 600;
       /*       mass[12] = 700;
       mass[13] = 800;
       mass[14] = 900;
       mass[15] = 1000; */
     }

   else {     
     mass[0] = 120;                                                                                                                                                     
     mass[1] = 350;                                                                                                                                                     
     mass[2] = 600;
   } 
  
   /*
   std::map<std::string,float> xs; //map of mass string and sf float 
   xs["100"] =  365.04 * 0.889297        +   5.21588 * 0.829672      ;
   xs["120"] =  207.345 * 0.886169       +   41.7379 * 0.88271       ;
   xs["160"] =  79.5406 * 0.88124        +   75.3253 * 0.879037      ;
   xs["200"] =  36.1034 * 0.857523       +   35.4616 * 0.869342      ;
   xs["250"] =  15.8387 * 0.811031       +   15.6594 * 0.85409       ;
   xs["300"] =  7.7196 * 0.705892        +   7.65395 * 0.809695      ;
   xs["350"] =  4.14873 * 0.564904       +   4.13288 * 0.708487      ;
   xs["400"] =  2.36367 * 0.515287       +   2.36207 * 0.624898      ;
   xs["500"] =  0.887828 * 0.435839      +   0.889008 * 0.415354     ;
   xs["600"] =  0.380582 * 0.350134      +   0.381322 * 0.346045     ;
   xs["700"] =  0.180691 * 0.311139      +   0.181021 * 0.309895     ;
   xs["900"] =  0.0497564 * 0.27335      +   0.0497311 * 0.272931    ;
   xs["1100"] =  0.0164384 * 0.254142    +   0.0164648 * 0.253845    ;
   xs["1300"] =  0.00616693 * 0.242023   +   0.00617024 * 0.241754   ;
   */

   //Bkg  file  
   TFile * fb = new TFile(Form("data_bbnb/histograms_2017all_%s.root",selection.c_str()),"OLD"); //chg
   
   /*
   TH1F * QCD_Mbb  = (TH1F*) ((TH1F*) fb->Get(observable.c_str()))->Clone("QCD_Mbb");
   TH1F * data_obs = (TH1F*) ((TH1F*) fb->Get(observable.c_str()))->Clone("data_obs");
   */

   TH1F * QCD_Mbb  = (TH1F*) ((TH1F*) fb->Get((observable+"_0").c_str()))->Clone("QCD_Mbb");
   TH1F * data_obs = (TH1F*) ((TH1F*) fb->Get((observable+"_0").c_str()))->Clone("data_obs");


   TFile * fs[nmassps]; // signal 
   TFile * fc[nmassps]; // output
 
   float lumi_data = 35600.; // pb-1
   float sf ; //lumi sf
   float lumi_gen ;

   cout << "Loaded files" << endl;
   //   freopen(Form("NOMINAL/table_%s.txt",selection.c_str()),"w",stdout);
   
   for ( int i = 0 ; i < nmassps ; ++i )
   {
     cout << "aaa" << endl;
     //Input signal
     if (NLO) fs[i] = new TFile(Form("mssmhbb/NLO/histograms_m%i_%s.root",mass[i],selection.c_str()),"OLD");          
     else  fs[i] = new TFile(Form("mssmhbb/LO/histograms_m%i_%s.root",mass[i],selection.c_str()),"OLD");

     //Output file
     if (NLO) fc[i] = new TFile(Form("inputfiles/histograms_%s_m%i.root",selection.c_str(),mass[i]),"RECREATE");
     else fc[i] = new TFile(Form("inputfiles/histograms_%s_LO_m%i.root",selection.c_str(),mass[i]),"RECREATE");
     TH1F * bbH_Mbb  = (TH1F*) ((TH1F*) fs[i]->Get(observable.c_str()))->Clone("bbH_Mbb");
     TH1F * nentries = (TH1F*) ((TH1F*) fs[i]->Get("nentries"))->Clone("nentries");

     //     float sf = 1.0/xs[to_string(mass[i])]; // inv scaling to get MEASURED x-section 
     lumi_gen = nentries->GetBinContent(2)-nentries->GetBinContent(1);
     sf = lumi_data/lumi_gen;  
     bbH_Mbb  -> Scale(sf);
     cout << "lumi_gen = "<< lumi_gen << " sf = " <<  sf << endl;
 
     // Printout table sig, bkg, sqrt(bkg), sig /sqrt(bkg)  
     int center = bbH_Mbb->GetMaximumBin(); //maximum bin
     int upper  = bbH_Mbb->GetMaximumBin()*1.2;
     int lower  = bbH_Mbb->GetMaximumBin()*0.8;

     float mass_center = bbH_Mbb->GetXaxis()->GetBinCenter(center);
     float mass_upper  = bbH_Mbb->GetXaxis()->GetBinCenter(upper);
     float mass_lower  = bbH_Mbb->GetXaxis()->GetBinCenter(lower);

     double errsig = 0.;
     double errbkg = 0.;

     double nsig = bbH_Mbb->IntegralAndError(lower,upper,errsig);
     double nbkg = QCD_Mbb->IntegralAndError(lower,upper,errbkg);

     double significance = nsig/sqrt(nbkg);
     double errsignificance = significance * sqrt( errsig*errsig/(nsig*nsig) + 0.25*errbkg*errbkg/(nbkg*nbkg) );

     //     float nbkg = QCD_Mbb->Integral()
     //     cout << "---------------------------------------------" << endl;
     //cout << "bin for masspoint " << mass[i] << " mass range integral [" << mass_lower <<  " ; " << mass_upper <<  "] with centre " << mass_center <<endl; 
     //cout << "#signal = " << nsig << " +/- " << errsig <<  ";  #bkg = "<< nbkg<< " +/- " << errbkg <<  ";  sign = "<< significance << " +/- " << errsignificance <<  endl << "limit = " << 1/significance << " +/- " << errsignificance/(significance*significance) << endl;
   
     std::cout << mass[i] << " inv. sign = " << 1/significance << " +/- " << errsignificance/(significance*significance) << endl;        

     //Write and close file
     bbH_Mbb  -> Write();
     QCD_Mbb  -> Write();
     data_obs -> Write();

     fc[i]-> Close();
     fs[i]-> Close();
 
      
   }
   fb-> Close();
 

}

