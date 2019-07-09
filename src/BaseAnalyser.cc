/**\class BaseAnalyser BaseAnalyser.cc Analysis/Tools/src/BaseAnalyser.cc

 Description: A base class for analyser

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roberval Walsh
//         Created:  6 Sep 2018
//
//

// system include files
#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
// 
// user include files
#include "Analysis/Tools/interface/BaseAnalyser.h"

//
// class declaration
//

using namespace analysis;
using namespace analysis::tools;

//
// constructors and destructor
//
BaseAnalyser::BaseAnalyser()
{
}


BaseAnalyser::BaseAnalyser(int argc, char * argv[])
{
   exe_ = std::string(argv[0]);
   
   // some inits
   scale_    = -1.;
   weight_   = 1.;
   xsection_ = -1.;
   genpartsanalysis_ = false;
   
   // the heavy stuff
   config_   = std::make_shared<Config>(argc,argv);
   analysis_ = std::make_shared<Analysis>(config_->ntuplesList(),config_->eventInfo());
   
   seed_ = analysis_ ->seed(config_->seedFile());
   
   // Workflow
   h1_["cutflow"] = std::make_shared<TH1F>("workflow",Form("Workflow #%d",config_->workflow()), 100,0,100);
      if ( std::string(h1_["cutflow"] -> GetXaxis()-> GetBinLabel(1)) == "" ) 
         h1_["cutflow"] -> GetXaxis()-> SetBinLabel(1,"Total events read");
      
   
   isMC_ = config_->isMC();
   isData_ = !isMC_;
   
   // Some MC-only stuff
   if ( isMC_ )
   {
      // Cross sections
      if ( analysis_ -> crossSections(config_->crossSectionTree()) == 0 )
         xsection_ = analysis_->crossSection(config_->crossSectionType());
      // Pileup weights
      if ( config_->pileupWeights() != "" )
         puweights_ = analysis_->pileupWeights(config_->pileupWeights());
      // gen part analysis
      genpartsanalysis_  = ( analysis_->addTree<GenParticle> ("GenParticles",config_->genParticlesCollection()) != nullptr );
      // cutflow init for MC
      if ( std::string(h1_["cutflow"] -> GetXaxis()-> GetBinLabel(2)) == "" ) 
         h1_["cutflow"] -> GetXaxis()-> SetBinLabel(2,"Generated weighted events");
      
   }
   
   // JSON for data   
   if( isData_ && config_->json_ != "" ) analysis_->processJsonFile(config_->json_);
   
   // output file
   if ( config_->outputRoot_ != "" )
   {
      hout_= std::make_shared<TFile>(config_->outputRoot_.c_str(),"recreate");
      hout_ -> cd();
   }
   
}

BaseAnalyser::~BaseAnalyser()
{
   std::cout << std::endl;
   // get last bin
   int lastbin = 0;
   for ( int i = 1; i <= h1_["cutflow"] ->GetNbinsX(); ++i )
   {
      std::string label = std::string(h1_["cutflow"]->GetXaxis()->GetBinLabel(i));
      if ( label == "" )
      {
         lastbin = i-1;
         break;
      }
   }
   float fevts =  h1_["cutflow"] -> GetBinContent(lastbin);
   // overall scale
   float scale = 1.; 
   bool doscale = false;
   if ( scale_ > 0. )  // superseeds the scale from config
   {
      doscale = true;
      scale = scale_;
   }
   else
   {
      // scale from config
      if ( config_ -> scale() > 0. )
      {
         doscale = true;
         scale = config_ -> scale();
      }
   }
   if ( doscale )
   {
      if ( std::string(h1_["cutflow"] -> GetXaxis()-> GetBinLabel(lastbin+1)) == "" )
      {
         h1_["cutflow"] -> GetXaxis()-> SetBinLabel(lastbin+1,Form("Number of events after scaling to %10.5f",scale));
      }
      h1_["cutflow"] -> Fill(lastbin,fevts*scale);
   }
    
//    // scale to luminosity
//    if ( config_->isMC() && config_ -> luminosity() > 0. && config_ -> scale() < 0. )
//    {
//       float nwevts = h1_["cutflow"] -> GetBinContent(2);
//       float genlumi = nwevts/xsection_;
//       scale = config_->luminosity()/genlumi;
//       if ( std::string(h1_["cutflow"] -> GetXaxis()-> GetBinLabel(lastbin+1)) == "" )
//       {
//          h1_["cutflow"] -> GetXaxis()-> SetBinLabel(lastbin+1,Form("Number of events after scaling to luminosity = %8.3f/pb",config_->luminosity()));
//       }
//       h1_["cutflow"] -> Fill(lastbin,fevts*scale);
//    }
   
   
   for ( auto h : h1_ )
   {
      if ( h.first == "cutflow" || h.first == "pileup" || h.first == "pileup_w" ) continue;
      if ( doscale ) h.second -> Scale(scale);
   }
   workflow();
   if ( hout_ )
   {
      std::cout << std::endl;
      std::cout << "output root file: " << config_->outputRoot_ << std::endl;
      hout_ -> cd();
      hout_->Write();
//      hout_->Close();
   }   
   
//   std::string cutflow = "Cutflow " + config_->outputRoot_;
//   std::system(cutflow.c_str());
   
   std::cout << exe_ << " finished!" << std::endl;
   printf("%s\n", std::string(100,'_').c_str());
   std::cout << std::endl;
}


//
// member functions
//
// ------------ method called for each event  ------------

bool BaseAnalyser::event(const int & i) { return true; }
void BaseAnalyser::histograms(const std::string & s, const int & i) { }

std::shared_ptr<Analysis> BaseAnalyser::analysis()
{
   return analysis_;
}

std::shared_ptr<Config> BaseAnalyser::config()
{
   return config_;
}

int BaseAnalyser::nEvents()
{
   int maxevt = config_->nEventsMax();
   if ( maxevt < 0 ) maxevt = analysis_->size();
   return maxevt;
}

std::shared_ptr<TH1F> BaseAnalyser::histogram(const std::string & hname)
{
   if ( h1_.find(hname) == h1_.end() ) 
   {
      std::cout << "-e- BaseAnalyser::H1F(const string & hname) -> no histogram with hname = " << hname << std::endl;
      return nullptr;
   }
   
   return h1_[hname];
}

std::map<std::string, std::shared_ptr<TH1F> > BaseAnalyser::histograms()
{
   return h1_;
}


void BaseAnalyser::workflow()
{
   printf("+%s+\n", std::string(150,'-').c_str());
   printf("| %-88s |    %10s |   %16s |   %16s |\n",h1_["cutflow"] -> GetTitle(),"n events","ratio wrt first","ratio wrt previous");
   printf("+%s+\n", std::string(150,'-').c_str());
   int firstbin = 2;
   for ( int i = 1; i <= h1_["cutflow"] ->GetNbinsX(); ++i )
   {
      std::string label = std::string(h1_["cutflow"]->GetXaxis()->GetBinLabel(i));
      if ( label == "" ) continue;
//      if ( firstbin < 0 ) firstbin = i;
      float n = h1_["cutflow"]->GetBinContent(i);
      float rn1 = h1_["cutflow"]->GetBinContent(i)/h1_["cutflow"]->GetBinContent(firstbin);
      float rni = 0;
      if ( i == 1 )
      {
         printf("| %-88s |    %10.1f |   %16s |  %19s |\n",label.c_str(),n,"-","-");
      }
      else if ( i == 2 )
      {
         printf("| %2d - %-83s |    %10.1f |   %16.4f |  %19s |\n",i-1,label.c_str(),n,rn1,"-");
      }
      else
      {
         rni = h1_["cutflow"]-> GetBinContent(i)/h1_["cutflow"]->GetBinContent(i-1);
         printf("| %2d - %-83s |    %10.1f |   %16.4f |     %16.4f |\n",i-1,label.c_str(),n,rn1,rni);
      }
      
   }
   printf("+%s+\n", std::string(150,'-').c_str());
   
}

int  BaseAnalyser::seed()
{
   return seed_;
}

int  BaseAnalyser::seed(const std::string & f)
{
   seed_ = analysis_ ->seed(f);
   return seed_;
}

void BaseAnalyser::seed(const int & seed)
{
   seed_ = seed;
}

void  BaseAnalyser::weight(const float & w)
{
   weight_ = w;
}

float  BaseAnalyser::weight()
{
   return weight_;
}

std::shared_ptr<TFile> BaseAnalyser::output()
{
   return hout_;
}

bool  BaseAnalyser::genParticlesAnalysis() const
{
   return genpartsanalysis_;
}

float BaseAnalyser::crossSection() const
{
   return xsection_;
}

std::shared_ptr<PileupWeight>  BaseAnalyser::pileupWeights() const
{
   return puweights_;
}

float BaseAnalyser::pileupWeight(const float & truepu, const int & var) const
{
   if ( ! puweights_ ) return 1.;   
   return puweights_->weight(truepu,var);
}

float BaseAnalyser::trueInteractions() const
{
   if ( ! config_->isMC() ) return -1;
    
   return float(analysis_->nTruePileup());
}

void BaseAnalyser::actionApplyPileupWeight(const int & var)
{
   if ( ! puweights_ ) return;
   if ( ! config_->isMC() ) return;
   
   ++cutflow_;
   if ( std::string(h1_["cutflow"] -> GetXaxis()-> GetBinLabel(cutflow_+1)) == "" ) 
      h1_["cutflow"] -> GetXaxis()-> SetBinLabel(cutflow_+1,"*** Apply pileup weight");
   
   weight_ *= this->pileupWeight(analysis_->nTruePileup(),var);
   
   h1_["cutflow"] -> Fill(cutflow_,weight_);
}

void BaseAnalyser::pileupHistogram()
{
   this->output()->cd();
   if ( config_->min() > 0 && config_->max() > 0 )
   {
      h1_["pileup"] = std::make_shared<TH1F>("pileup" , "pileup" , config_->n() , config_->min() , config_->max() );
      h1_["pileup_w"] = std::make_shared<TH1F>("pileup_w" , "weighted pileup" , config_->n() , config_->min() , config_->max() );
   }
   else
   {
      h1_["pileup"] = std::make_shared<TH1F>("pileup" , "pileup" , 100 , 0 , 100 );
      h1_["pileup_w"] = std::make_shared<TH1F>("pileup_w" , "weighted pileup" , 100 , 0 , 100 );
   }
   
}
void BaseAnalyser::fillPileupHistogram()
{
   ++cutflow_;
   if ( std::string(h1_["cutflow"] -> GetXaxis()-> GetBinLabel(cutflow_+1)) == "" ) 
      h1_["cutflow"] -> GetXaxis()-> SetBinLabel(cutflow_+1,"*** Fill true pileup histrogram");
   
   h1_["cutflow"] -> Fill(cutflow_,weight_);
   
   h1_["pileup"] -> Fill(analysis_->nTruePileup());
   h1_["pileup_w"] -> Fill(analysis_->nTruePileup(),this->pileupWeight(analysis_->nTruePileup(),0));
}

int BaseAnalyser::cutflow()
{
   return cutflow_;
}

void BaseAnalyser::cutflow(const int & c)
{
   cutflow_ = c;
}

void BaseAnalyser::scale(const float & scale)
{
   scale_ = scale;
}
