#include <sstream>

using namespace std;

void PrepareHistograms()
{  

   bool NLO = true;
   std::string selection("nominal");//files created by macro must have this ending (see below) //also for data CR from macro!
   std::string observable("m12_csv");
     
   int nmassps = 16;
   if( !NLO ) nmassps = 3;
   int mass[nmassps];
   if ( NLO )
     {
       mass[0] = 200;
       mass[1] = 250;
       mass[2] = 350;
       mass[3] = 400;
       mass[4] = 450;
       mass[5] = 500;
       mass[6] = 600;
       mass[7] = 700;
       mass[8] = 800;
       mass[9] = 900;
       mass[10] = 1000;
       mass[11] = 1200;
       mass[12] = 1400;
       mass[13] = 1600;
       mass[14] = 1800;
       mass[15] = 2000;
     }

   else {
     mass[0] = 350;
     mass[1] = 600;
     mass[2] = 1200;
   }
  
   //Bkg  file
   TFile * fb = new TFile(Form("data_bbnb/histograms_2017all_%s.root",selection.c_str()),"READ"); //change according to desired input //this is the data CR file from the macro!!
   
   //bkg hists
   TH1F * QCD_Mbb  = (TH1F*) ((TH1F*) fb->Get((observable).c_str()))->Clone("QCD_Mbb");
   TH1F * data_obs = (TH1F*) ((TH1F*) fb->Get((observable).c_str()))->Clone("data_obs");

   TFile * fs[nmassps]; // signal (input, directly from macro)
   TFile * fc[nmassps]; // output
 
   float lumi_data = 36020.; // pb-1
   float sf; //lumi sf
   float lumi_gen;

   cout << "Loaded files" << endl;
   
   for ( int i = 0 ; i < nmassps ; ++i )
   {
     cout << "Analyzing mass point " << mass[i] << " GeV." << endl;

     //Input signal
     if (NLO) fs[i] = new TFile(Form("mssmhbb/NLO/histograms_m%i_%s.root",mass[i],selection.c_str()),"READ");//input (from macro, NLO)
     else  fs[i] = new TFile(Form("mssmhbb/LO/histograms_m%i_%s.root",mass[i],selection.c_str()),"READ");//input (from macro, LO)

     //Output file
     if (NLO) fc[i] = new TFile(Form("inputfiles/histograms_%s_m%i.root",selection.c_str(),mass[i]),"RECREATE");//creates files
     else fc[i] = new TFile(Form("inputfiles/histograms_%s_LO_m%i.root",selection.c_str(),mass[i]),"RECREATE");//for combine tool
     TH1F * bbH_Mbb  = (TH1F*) ((TH1F*) fs[i]->Get(observable.c_str()))->Clone("bbH_Mbb");
     TH1F * nentries = (TH1F*) ((TH1F*) fs[i]->Get("nentries"))->Clone("nentries");

     //     float sf = 1.0/xs[to_string(mass[i])]; // inv scaling to get MEASURED x-section
     lumi_gen = nentries->GetBinContent(2)-nentries->GetBinContent(1); //effectively produced number of events (those with positive weight - those with negative weight)
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

     std::cout << mass[i] << " inverse significance = " << 1/significance << " +/- " << errsignificance/(significance*significance) << endl;        

     //Write and close file
     bbH_Mbb  -> Write();
     QCD_Mbb  -> Write();
     data_obs -> Write();

     fc[i]-> Close();
     fs[i]-> Close();
   }
   fb-> Close();
}

