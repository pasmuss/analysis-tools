void RPHforToyHists(){
  // As usual, load the combine library to get access to the RooParametricHist
  gSystem->Load("libHiggsAnalysisCombinedLimit.so");

  //Get input histograms
  TFile* fIn = new TFile("/afs/desy.de/user/a/asmusspa/Documents/CMSSW_9_2_15/src/Analysis/Tools/test/InputForCombineSigCRSR.root","READ");
  TH1F* SNhist = (TH1F*)fIn -> Get("SuperNovoHist");//CR
  TH1F* SRhist = (TH1F*)fIn -> Get("SignalRegionHist");//SR
  TH1F* Sighist = (TH1F*)fIn -> Get("SignalHist");//signal
  TH1F* SiSRhist = (TH1F*)fIn -> Get("SignalHistPlusSR");//SR plus signal

  // Output file and workspace
  TFile *fOut = new TFile("ws_linTF_smallerSig.root","RECREATE");
  RooWorkspace wspace("wspace","wspace");
  //RooWorkspace sigwspace("sigwspace","sigwspace");

  // A search in a m12 tail, define m12 as our variable
  RooRealVar m12("m12","m_{12}",200,2000);
  RooArgList vars(m12);

  // ---------------------------- CONTROL REGION -------------------------------------------------------------------//
  RooDataHist data_hist_CR("data_obs_CR","Data observed in the Control Region",vars,SNhist);
  wspace.import(data_hist_CR);

  // In the control region, our background process will be freely floating,
  // Create one parameter per bin representing the yield. (note of course we can have multiple processes like this)
  RooArgList bkg_CR_bins;

  for (int i = 1; i <= 30; i++) cout << i << " " << SNhist->GetBinContent(i) << endl;

  RooRealVar bin1("bkg_CR_bin1","Background CR bin 1",SNhist->GetBinContent(1),SNhist->GetBinContent(1)-sqrt(SNhist->GetBinContent(1)),SNhist->GetBinContent(1)+sqrt(SNhist->GetBinContent(1)));
  RooRealVar bin2("bkg_CR_bin2","Background CR bin 2",SNhist->GetBinContent(2),SNhist->GetBinContent(2)-sqrt(SNhist->GetBinContent(2)),SNhist->GetBinContent(2)+sqrt(SNhist->GetBinContent(2)));
  RooRealVar bin3("bkg_CR_bin3","Background CR bin 3",SNhist->GetBinContent(3),SNhist->GetBinContent(3)-sqrt(SNhist->GetBinContent(3)),SNhist->GetBinContent(3)+sqrt(SNhist->GetBinContent(3)));
  RooRealVar bin4("bkg_CR_bin4","Background CR bin 4",SNhist->GetBinContent(4),SNhist->GetBinContent(4)-sqrt(SNhist->GetBinContent(4)),SNhist->GetBinContent(4)+sqrt(SNhist->GetBinContent(4)));
  RooRealVar bin5("bkg_CR_bin5","Background CR bin 5",SNhist->GetBinContent(5),SNhist->GetBinContent(5)-sqrt(SNhist->GetBinContent(5)),SNhist->GetBinContent(5)+sqrt(SNhist->GetBinContent(5)));
  RooRealVar bin6("bkg_CR_bin6","Background CR bin 6",SNhist->GetBinContent(6)/*,SNhist->GetBinContent(6)-sqrt(SNhist->GetBinContent(6)),SNhist->GetBinContent(6)+sqrt(SNhist->GetBinContent(6))*/);
  RooRealVar bin7("bkg_CR_bin7","Background CR bin 7",SNhist->GetBinContent(7)/*,SNhist->GetBinContent(7)-sqrt(SNhist->GetBinContent(7)),SNhist->GetBinContent(7)+sqrt(SNhist->GetBinContent(7))*/);
  RooRealVar bin8("bkg_CR_bin8","Background CR bin 8",SNhist->GetBinContent(8)/*,SNhist->GetBinContent(8)-sqrt(SNhist->GetBinContent(8)),SNhist->GetBinContent(8)+sqrt(SNhist->GetBinContent(8))*/);
  RooRealVar bin9("bkg_CR_bin9","Background CR bin 9",SNhist->GetBinContent(9)/*,SNhist->GetBinContent(9)-sqrt(SNhist->GetBinContent(9)),SNhist->GetBinContent(9)+sqrt(SNhist->GetBinContent(9))*/);
  RooRealVar bin10("bkg_CR_bin10","Background CR bin 10",SNhist->GetBinContent(10)/*,SNhist->GetBinContent(10)-sqrt(SNhist->GetBinContent(10)),SNhist->GetBinContent(10)+sqrt(SNhist->GetBinContent(10))*/);
  RooRealVar bin11("bkg_CR_bin11","Background CR bin 11",SNhist->GetBinContent(11)/*,SNhist->GetBinContent(11)-sqrt(SNhist->GetBinContent(11)),SNhist->GetBinContent(11)+sqrt(SNhist->GetBinContent(11))*/);
  RooRealVar bin12("bkg_CR_bin12","Background CR bin 12",SNhist->GetBinContent(12)/*,SNhist->GetBinContent(12)-sqrt(SNhist->GetBinContent(12)),SNhist->GetBinContent(12)+sqrt(SNhist->GetBinContent(12))*/);
  RooRealVar bin13("bkg_CR_bin13","Background CR bin 13",SNhist->GetBinContent(13)/*,SNhist->GetBinContent(13)-sqrt(SNhist->GetBinContent(13)),SNhist->GetBinContent(13)+sqrt(SNhist->GetBinContent(13))*/);
  RooRealVar bin14("bkg_CR_bin14","Background CR bin 14",SNhist->GetBinContent(14)/*,SNhist->GetBinContent(14)-sqrt(SNhist->GetBinContent(14)),SNhist->GetBinContent(14)+sqrt(SNhist->GetBinContent(14))*/);
  RooRealVar bin15("bkg_CR_bin15","Background CR bin 15",SNhist->GetBinContent(15)/*,SNhist->GetBinContent(15)-sqrt(SNhist->GetBinContent(15)),SNhist->GetBinContent(15)+sqrt(SNhist->GetBinContent(15))*/);
  RooRealVar bin16("bkg_CR_bin16","Background CR bin 16",SNhist->GetBinContent(16)/*,SNhist->GetBinContent(16)-sqrt(SNhist->GetBinContent(16)),SNhist->GetBinContent(16)+sqrt(SNhist->GetBinContent(16))*/);
  RooRealVar bin17("bkg_CR_bin17","Background CR bin 17",SNhist->GetBinContent(17)/*,SNhist->GetBinContent(17)-sqrt(SNhist->GetBinContent(17)),SNhist->GetBinContent(17)+sqrt(SNhist->GetBinContent(17))*/);
  RooRealVar bin18("bkg_CR_bin18","Background CR bin 18",SNhist->GetBinContent(18)/*,SNhist->GetBinContent(18)-sqrt(SNhist->GetBinContent(18)),SNhist->GetBinContent(18)+sqrt(SNhist->GetBinContent(18))*/);
  RooRealVar bin19("bkg_CR_bin19","Background CR bin 19",SNhist->GetBinContent(19)/*,SNhist->GetBinContent(19)-sqrt(SNhist->GetBinContent(19)),SNhist->GetBinContent(19)+sqrt(SNhist->GetBinContent(19))*/);
  RooRealVar bin20("bkg_CR_bin20","Background CR bin 20",SNhist->GetBinContent(20)/*,SNhist->GetBinContent(20)-sqrt(SNhist->GetBinContent(20)),SNhist->GetBinContent(20)+sqrt(SNhist->GetBinContent(20))*/);
  RooRealVar bin21("bkg_CR_bin21","Background CR bin 21",SNhist->GetBinContent(21)/*,SNhist->GetBinContent(21)-sqrt(SNhist->GetBinContent(21)),SNhist->GetBinContent(21)+sqrt(SNhist->GetBinContent(21))*/);
  RooRealVar bin22("bkg_CR_bin22","Background CR bin 22",SNhist->GetBinContent(22)/*,SNhist->GetBinContent(22)-sqrt(SNhist->GetBinContent(22)),SNhist->GetBinContent(22)+sqrt(SNhist->GetBinContent(22))*/);
  RooRealVar bin23("bkg_CR_bin23","Background CR bin 23",SNhist->GetBinContent(23)/*,SNhist->GetBinContent(23)-sqrt(SNhist->GetBinContent(23)),SNhist->GetBinContent(23)+sqrt(SNhist->GetBinContent(23))*/);
  RooRealVar bin24("bkg_CR_bin24","Background CR bin 24",SNhist->GetBinContent(24)/*,SNhist->GetBinContent(24)-sqrt(SNhist->GetBinContent(24)),SNhist->GetBinContent(24)+sqrt(SNhist->GetBinContent(24))*/);
  RooRealVar bin25("bkg_CR_bin25","Background CR bin 25",SNhist->GetBinContent(25)/*,SNhist->GetBinContent(25)-sqrt(SNhist->GetBinContent(25)),SNhist->GetBinContent(25)+sqrt(SNhist->GetBinContent(25))*/);
  RooRealVar bin26("bkg_CR_bin26","Background CR bin 26",SNhist->GetBinContent(26)/*,SNhist->GetBinContent(26)-sqrt(SNhist->GetBinContent(26)),SNhist->GetBinContent(26)+sqrt(SNhist->GetBinContent(26))*/);
  RooRealVar bin27("bkg_CR_bin27","Background CR bin 27",SNhist->GetBinContent(27)/*,SNhist->GetBinContent(27)-sqrt(SNhist->GetBinContent(27)),SNhist->GetBinContent(27)+sqrt(SNhist->GetBinContent(27))*/);
  RooRealVar bin28("bkg_CR_bin28","Background CR bin 28",SNhist->GetBinContent(28)/*,SNhist->GetBinContent(28)-sqrt(SNhist->GetBinContent(28)),SNhist->GetBinContent(28)+sqrt(SNhist->GetBinContent(28))*/);
  RooRealVar bin29("bkg_CR_bin29","Background CR bin 29",SNhist->GetBinContent(29)/*,SNhist->GetBinContent(29)-sqrt(SNhist->GetBinContent(29)),SNhist->GetBinContent(29)+sqrt(SNhist->GetBinContent(29))*/);
  RooRealVar bin30("bkg_CR_bin30","Background CR bin 30",SNhist->GetBinContent(30)/*,SNhist->GetBinContent(30)-sqrt(SNhist->GetBinContent(30)),SNhist->GetBinContent(30)+sqrt(SNhist->GetBinContent(30))*/);
  
  bkg_CR_bins.add(bin1);
  bkg_CR_bins.add(bin2);
  bkg_CR_bins.add(bin3);
  bkg_CR_bins.add(bin4);
  bkg_CR_bins.add(bin5);
  bkg_CR_bins.add(bin6);
  bkg_CR_bins.add(bin7);
  bkg_CR_bins.add(bin8);
  bkg_CR_bins.add(bin9);
  bkg_CR_bins.add(bin10);
  bkg_CR_bins.add(bin11);
  bkg_CR_bins.add(bin12);
  bkg_CR_bins.add(bin13);
  bkg_CR_bins.add(bin14);
  bkg_CR_bins.add(bin15);
  bkg_CR_bins.add(bin16);
  bkg_CR_bins.add(bin17);
  bkg_CR_bins.add(bin18);
  bkg_CR_bins.add(bin19);
  bkg_CR_bins.add(bin20);
  bkg_CR_bins.add(bin21);
  bkg_CR_bins.add(bin22);
  bkg_CR_bins.add(bin23);
  bkg_CR_bins.add(bin24);
  bkg_CR_bins.add(bin25);
  bkg_CR_bins.add(bin26);
  bkg_CR_bins.add(bin27);
  bkg_CR_bins.add(bin28);
  bkg_CR_bins.add(bin29);
  bkg_CR_bins.add(bin30);

  // Create a RooParametericHist which contains those yields, last argument is just for the binning,
  // can use the data TH1 for that
  RooParametricHist p_CRbkg("bkg_CR", "Background PDF in control region",m12,bkg_CR_bins,*SNhist);
  // Always include a _norm term which should be the sum of the yields (thats how combine likes to play with pdfs)
  RooAddition p_CRbkg_norm("bkg_CR_norm","Total Number of events from background in control region",bkg_CR_bins);

  // Every signal region needs a signal
  RooDataHist signal_hist("signal","Signal only",vars,Sighist);
  wspace.import(signal_hist);

  // -------------------------------------------------------------------------------------------------------------//
  // ---------------------------- SIGNAL REGION ------------------------------------------------------------------//
  RooDataHist data_hist_SR("data_obs_SR","Data observed in signal region",vars,SRhist);
  wspace.import(data_hist_SR);

  // This time, the background process will be dependent on the yields of the background in the signal region.
  // The transfer factor TF must account for acceptance/efficiency etc differences in the signal to control
  // In this example lets assume the control region is populated by the same process decaying to clean daughters with 2xBR
  // compared to the signal region

  // NB You could have a different transfer factor for each bin represented by a completely different RooRealVar

  // We can imagine that the transfer factor could be associated with some uncertainty - lets say a 1% uncertainty due to efficiency and 2% due to acceptance.
  // We need to make these nuisance parameters ourselves and give them a nominal value of 0

  //RooRealVar efficiency("efficiency", "efficiency nuisance parameter",0);
  //RooRealVar acceptance("acceptance", "acceptance nuisance parameter",0);

  // We would need to make the transfer factor a function of those too. Here we've assumed Log-normal effects (i.e the same as putting lnN in the CR datacard)
  // but note that we could use any function which could be used to parameterise the effect - eg if the systematic is due to some alternate template, we could
  // use polynomials for example.

  // Finally, we need to make each bin of the background in the control region a function of the background in the signal and the transfer factor
  // N_CR = N_SR x TF

  //RooRealVar normvar("normvar", "prescale of SR wrt CR", 0.1, 0.0, 1.0);
  RooRealVar TFslope("TFslope", "slope of TF", 0.01/*, 0.0, 0.1*/);
  //RooRealVar TFoffset("TFoffset", "offset of TF", 1.0, 0.0, 10.0);
  
  RooFormulaVar TF_bin1("TF_bin1","Transfer factor bin 1","(@0*230.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin2("TF_bin2","Transfer factor bin 2","(@0*290.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin3("TF_bin3","Transfer factor bin 3","(@0*350.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin4("TF_bin4","Transfer factor bin 4","(@0*410.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin5("TF_bin5","Transfer factor bin 5","(@0*470.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin6("TF_bin6","Transfer factor bin 6","(@0*530.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin7("TF_bin7","Transfer factor bin 7","(@0*590.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin8("TF_bin8","Transfer factor bin 8","(@0*650.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin9("TF_bin9","Transfer factor bin 9","(@0*710.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin10("TF_bin10","Transfer factor bin 10","(@0*770.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin11("TF_bin11","Transfer factor bin 11","(@0*830.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin12("TF_bin12","Transfer factor bin 12","(@0*890.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin13("TF_bin13","Transfer factor bin 13","(@0*950.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin14("TF_bin14","Transfer factor bin 14","(@0*1010.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin15("TF_bin15","Transfer factor bin 15","(@0*1070.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin16("TF_bin16","Transfer factor bin 16","(@0*1130.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin17("TF_bin17","Transfer factor bin 17","(@0*1190.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin18("TF_bin18","Transfer factor bin 18","(@0*1250.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin19("TF_bin19","Transfer factor bin 19","(@0*1310.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin20("TF_bin20","Transfer factor bin 20","(@0*1370.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin21("TF_bin21","Transfer factor bin 21","(@0*1430.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin22("TF_bin22","Transfer factor bin 22","(@0*1490.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin23("TF_bin23","Transfer factor bin 23","(@0*1550.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin24("TF_bin24","Transfer factor bin 24","(@0*1610.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin25("TF_bin25","Transfer factor bin 25","(@0*1670.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin26("TF_bin26","Transfer factor bin 26","(@0*1730.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin27("TF_bin27","Transfer factor bin 27","(@0*1790.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin28("TF_bin28","Transfer factor bin 28","(@0*1850.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin29("TF_bin29","Transfer factor bin 29","(@0*1910.0)",RooArgList(TFslope));
  RooFormulaVar TF_bin30("TF_bin30","Transfer factor bin 30","(@0*1970.0)",RooArgList(TFslope));
  
  RooFormulaVar SRbin1("bkg_SR_bin1","Background yield in signal region, bin 1","(@0*@1)",RooArgList(TF_bin1,bin1));
  RooFormulaVar SRbin2("bkg_SR_bin2","Background yield in signal region, bin 2","(@0*@1)",RooArgList(TF_bin2,bin2));
  RooFormulaVar SRbin3("bkg_SR_bin3","Background yield in signal region, bin 3","(@0*@1)",RooArgList(TF_bin3,bin3));
  RooFormulaVar SRbin4("bkg_SR_bin4","Background yield in signal region, bin 4","(@0*@1)",RooArgList(TF_bin4,bin4));
  RooFormulaVar SRbin5("bkg_SR_bin5","Background yield in signal region, bin 5","(@0*@1)",RooArgList(TF_bin5,bin5));
  RooFormulaVar SRbin6("bkg_SR_bin6","Background yield in signal region, bin 6","(@0*@1)",RooArgList(TF_bin6,bin6));
  RooFormulaVar SRbin7("bkg_SR_bin7","Background yield in signal region, bin 7","(@0*@1)",RooArgList(TF_bin7,bin7));
  RooFormulaVar SRbin8("bkg_SR_bin8","Background yield in signal region, bin 8","(@0*@1)",RooArgList(TF_bin8,bin8));
  RooFormulaVar SRbin9("bkg_SR_bin9","Background yield in signal region, bin 9","(@0*@1)",RooArgList(TF_bin9,bin9));
  RooFormulaVar SRbin10("bkg_SR_bin10","Background yield in signal region, bin 10","(@0*@1)",RooArgList(TF_bin10,bin10));
  RooFormulaVar SRbin11("bkg_SR_bin11","Background yield in signal region, bin 11","(@0*@1)",RooArgList(TF_bin11,bin11));
  RooFormulaVar SRbin12("bkg_SR_bin12","Background yield in signal region, bin 12","(@0*@1)",RooArgList(TF_bin12,bin12));
  RooFormulaVar SRbin13("bkg_SR_bin13","Background yield in signal region, bin 13","(@0*@1)",RooArgList(TF_bin13,bin13));
  RooFormulaVar SRbin14("bkg_SR_bin14","Background yield in signal region, bin 14","(@0*@1)",RooArgList(TF_bin14,bin14));
  RooFormulaVar SRbin15("bkg_SR_bin15","Background yield in signal region, bin 15","(@0*@1)",RooArgList(TF_bin15,bin15));
  RooFormulaVar SRbin16("bkg_SR_bin16","Background yield in signal region, bin 16","(@0*@1)",RooArgList(TF_bin16,bin16));
  RooFormulaVar SRbin17("bkg_SR_bin17","Background yield in signal region, bin 17","(@0*@1)",RooArgList(TF_bin17,bin17));
  RooFormulaVar SRbin18("bkg_SR_bin18","Background yield in signal region, bin 18","(@0*@1)",RooArgList(TF_bin18,bin18));
  RooFormulaVar SRbin19("bkg_SR_bin19","Background yield in signal region, bin 19","(@0*@1)",RooArgList(TF_bin19,bin19));
  RooFormulaVar SRbin20("bkg_SR_bin20","Background yield in signal region, bin 20","(@0*@1)",RooArgList(TF_bin20,bin20));
  RooFormulaVar SRbin21("bkg_SR_bin21","Background yield in signal region, bin 21","(@0*@1)",RooArgList(TF_bin21,bin21));
  RooFormulaVar SRbin22("bkg_SR_bin22","Background yield in signal region, bin 22","(@0*@1)",RooArgList(TF_bin22,bin22));
  RooFormulaVar SRbin23("bkg_SR_bin23","Background yield in signal region, bin 23","(@0*@1)",RooArgList(TF_bin23,bin23));
  RooFormulaVar SRbin24("bkg_SR_bin24","Background yield in signal region, bin 24","(@0*@1)",RooArgList(TF_bin24,bin24));
  RooFormulaVar SRbin25("bkg_SR_bin25","Background yield in signal region, bin 25","(@0*@1)",RooArgList(TF_bin25,bin25));
  RooFormulaVar SRbin26("bkg_SR_bin26","Background yield in signal region, bin 26","(@0*@1)",RooArgList(TF_bin26,bin26));
  RooFormulaVar SRbin27("bkg_SR_bin27","Background yield in signal region, bin 27","(@0*@1)",RooArgList(TF_bin27,bin27));
  RooFormulaVar SRbin28("bkg_SR_bin28","Background yield in signal region, bin 28","(@0*@1)",RooArgList(TF_bin28,bin28));
  RooFormulaVar SRbin29("bkg_SR_bin29","Background yield in signal region, bin 29","(@0*@1)",RooArgList(TF_bin29,bin29));
  RooFormulaVar SRbin30("bkg_SR_bin30","Background yield in signal region, bin 30","(@0*@1)",RooArgList(TF_bin30,bin30));

  RooArgList bkg_SR_bins;
  bkg_SR_bins.add(SRbin1);
  bkg_SR_bins.add(SRbin2);
  bkg_SR_bins.add(SRbin3);
  bkg_SR_bins.add(SRbin4);
  bkg_SR_bins.add(SRbin5);
  bkg_SR_bins.add(SRbin6);
  bkg_SR_bins.add(SRbin7);
  bkg_SR_bins.add(SRbin8);
  bkg_SR_bins.add(SRbin9);
  bkg_SR_bins.add(SRbin10);
  bkg_SR_bins.add(SRbin11);
  bkg_SR_bins.add(SRbin12);
  bkg_SR_bins.add(SRbin13);
  bkg_SR_bins.add(SRbin14);
  bkg_SR_bins.add(SRbin15);
  bkg_SR_bins.add(SRbin16);
  bkg_SR_bins.add(SRbin17);
  bkg_SR_bins.add(SRbin18);
  bkg_SR_bins.add(SRbin19);
  bkg_SR_bins.add(SRbin20);
  bkg_SR_bins.add(SRbin21);
  bkg_SR_bins.add(SRbin22);
  bkg_SR_bins.add(SRbin23);
  bkg_SR_bins.add(SRbin24);
  bkg_SR_bins.add(SRbin25);
  bkg_SR_bins.add(SRbin26);
  bkg_SR_bins.add(SRbin27);
  bkg_SR_bins.add(SRbin28);
  bkg_SR_bins.add(SRbin29);
  bkg_SR_bins.add(SRbin30);

  RooParametricHist p_SRbkg("bkg_SR", "Background PDF in signal region",m12,bkg_SR_bins,*SRhist);
  RooAddition p_SRbkg_norm("bkg_SR_norm","Total Number of events from background in signal region",bkg_SR_bins);
  // -------------------------------------------------------------------------------------------------------------//

  // import the pdfs
  wspace.import(p_CRbkg);
  wspace.import(p_CRbkg_norm,RooFit::RecycleConflictNodes());
  wspace.import(p_SRbkg);
  wspace.import(p_SRbkg_norm,RooFit::RecycleConflictNodes());
  fOut->cd();
  wspace.Write();

  // Clean up
  fOut->Close();
  fOut->Delete();

}
