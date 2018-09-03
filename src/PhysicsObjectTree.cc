/**\class PhysicsObjectTree PhysicsObjectTree.cc Analysis/Tools/src/PhysicsObjectTree.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roberval Walsh Bastos Rangel
//         Created:  Mon, 20 Oct 2014 14:24:08 GMT
//
//

// system include files
#include <iostream>
//
// user include files
#include "Analysis/Tools/interface/PhysicsObjectTree.h"


//
// class declaration
//

using namespace analysis;
using namespace analysis::tools;

//
// constructors and destructor
//
template <class Object>
      PhysicsObjectTree<Object>::PhysicsObjectTree() : PhysicsObjectTreeBase<Object>()     {}
template <class Object>
      PhysicsObjectTree<Object>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<Object>(tree, name) {}
template <class Object>
      PhysicsObjectTree<Object>::~PhysicsObjectTree()                                                   {}

// member function
template <class Object> Collection<Object>  PhysicsObjectTree<Object>::collection()
{
   // DUMMY
   Collection<Object> obj;
   return obj;
}

// Candidate
// Constructors and destructor
PhysicsObjectTree<Candidate>::PhysicsObjectTree() : PhysicsObjectTreeBase<Candidate>()
{
}
PhysicsObjectTree<Candidate>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<Candidate>(tree, name)
{
}
PhysicsObjectTree<Candidate>::~PhysicsObjectTree() {}

// Member functions
Collection<Candidate>  PhysicsObjectTree<Candidate>::collection()
{
   std::vector<Candidate> candidates;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      Candidate cand(pt_[i], eta_[i], phi_[i], e_[i], q_[i]);
      candidates.push_back(cand);
   }
   Collection<Candidate> CandidateCollection(candidates, name_);
   return CandidateCollection;

}


// JETS
// Constructors and destructor
PhysicsObjectTree<Jet>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<Jet>(tree, name)
{
   isSimpleJet_ = false;
//   tree_  -> SetBranchAddress( "btag_csvivf", btag_    );
   int algos = 0;
   for ( auto & branch : branches_ )
   {
      std::size_t found = branch.find("btag_");
      if (found!=std::string::npos)
      {
         mbtag_[branch] = btags_[algos];
         ++algos;
         tree_  -> SetBranchAddress( branch.c_str(), mbtag_[branch]);
      }
   }
//    std::vector<std::string>::iterator it;
//    it = std::find(branches_.begin(),branches_.end(),"btag_");
//    if ( it != branches_.end() )
//       std::cout << *it << std::endl;
   
   if ( mbtag_.size() > 0 )
   {
      tree_  -> SetBranchAddress( "flavour"        , flavour_ );
      tree_  -> SetBranchAddress( "hadronFlavour"  , hadrflavour_ );
      tree_  -> SetBranchAddress( "partonFlavour"  , partflavour_ );
      tree_  -> SetBranchAddress( "physicsFlavour" , physflavour_ );
      tree_  -> SetBranchAddress( "id_nHadFrac", nHadFrac_);
      tree_  -> SetBranchAddress( "id_nEmFrac" , nEmFrac_ );
      tree_  -> SetBranchAddress( "id_nMult"   , nMult_   );
      tree_  -> SetBranchAddress( "id_cHadFrac", cHadFrac_);
      tree_  -> SetBranchAddress( "id_cEmFrac" , cEmFrac_ );
      tree_  -> SetBranchAddress( "id_cMult"   , cMult_   );
      tree_  -> SetBranchAddress( "id_muonFrac", muFrac_  );
      tree_  -> SetBranchAddress( "jecUncert"  , jecUnc_);
      tree_  -> SetBranchAddress( "jerSF", jerSF_);
      tree_  -> SetBranchAddress( "jerSFDown", jerSFDown_);
      tree_  -> SetBranchAddress( "jerSFUp", jerSFUp_);
      tree_  -> SetBranchAddress( "jerResolution", jerResolution_);
      std::vector<std::string>::iterator it;
      it = std::find(branches_.begin(),branches_.end(),"qgLikelihood")            ;  if ( it != branches_.end() ) tree_  -> SetBranchAddress( (*it).c_str() , qgLikelihood_ );
      it = std::find(branches_.begin(),branches_.end(),"puJetIdFullDiscriminant") ;  if ( it != branches_.end() ) tree_  -> SetBranchAddress( (*it).c_str() , puJetIdFullDisc_ );
      it = std::find(branches_.begin(),branches_.end(),"puJetIdFullId")           ;  if ( it != branches_.end() ) tree_  -> SetBranchAddress( (*it).c_str() , puJetIdFullId_ );
   }
   else
   {
      isSimpleJet_ = true;
   }
//   std::cout << "oioi" << std::endl;
//   std::vector<std::string>::iterator it;
//   it = std::find(branches_.begin(),branches_.end(),"jecUncert");  if ( it != branches_.end() ) tree_  -> SetBranchAddress( (*it).c_str(), jecUnc_);

}
PhysicsObjectTree<Jet>::~PhysicsObjectTree() {}

// Member functions
Collection<Jet>  PhysicsObjectTree<Jet>::collection()
{
   std::vector<Jet> jets;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      Jet jet(pt_[i], eta_[i], phi_[i], e_[i]);
      jet.btag(btag_[i]);
      for ( auto & b : mbtag_ )
         jet.btag(b.first,b.second[i]);
      jet.flavour(flavour_[i]);
      jet.flavour("Hadron",hadrflavour_[i]);
      jet.flavour("Parton",partflavour_[i]);
      jet.flavour("Physics",physflavour_[i]);
      jet.jecUncert(jecUnc_[i]);
      jet.id(nHadFrac_[i],
             nEmFrac_[i] ,
             nMult_[i]   ,
             cHadFrac_[i],
             cEmFrac_[i] ,
             cMult_[i]   ,
             muFrac_[i]  );
      jet.JerResolution(jerResolution_[i]);
      jet.JerSf(jerSF_[i]);
      jet.JerSfUp(jerSFUp_[i]);
      jet.JerSfDown(jerSFDown_[i]);
      jet.qgLikelihood(qgLikelihood_[i]);
      jet.pileupJetIdFullDiscriminant(puJetIdFullDisc_[i]);
      jet.pileupJetIdFullId(puJetIdFullId_[i]);
      jets.push_back(jet);
   }
   Collection<Jet> jetCollection(jets, name_);
   return jetCollection;

}

// GENPARTICLE
// Constructors and destructor
PhysicsObjectTree<GenParticle>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<GenParticle>(tree, name)
{
   tree_  -> SetBranchAddress( "pdg"   , pdgid_  );
   tree_  -> SetBranchAddress( "status", status_ );
   tree_  -> SetBranchAddress( "higgs_dau", higgs_dau_ );
}
PhysicsObjectTree<GenParticle>::~PhysicsObjectTree() {}

// Member functions
Collection<GenParticle>  PhysicsObjectTree<GenParticle>::collection()
{
   std::vector<GenParticle> particles;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      GenParticle p(pt_[i], eta_[i], phi_[i], e_[i], q_[i]);
      p.pdgId(pdgid_[i]);
      p.status(status_[i]);
      p.higgsDaughter(higgs_dau_[i]);
      particles.push_back(p);
   }
   Collection<GenParticle> genPartCollection(particles, name_);
   return genPartCollection;

}

// MET
// Constructors and destructor
PhysicsObjectTree<MET>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<MET>(tree, name)
{
   tree_  -> SetBranchAddress( "sigxx" , sigxx_ );
   tree_  -> SetBranchAddress( "sigxy" , sigxy_ );
   tree_  -> SetBranchAddress( "sigyx" , sigyx_ );
   tree_  -> SetBranchAddress( "sigyy" , sigyy_ );
   // Exists in MC; check if available and set
   // Maybe it's better to use analysis::isMC() for this perpouse?
   std::vector<std::string>::iterator it;
   it = std::find(branches_.begin(),branches_.end(),"gen_px");  if ( it != branches_.end() ) tree_  -> SetBranchAddress( (*it).c_str(), gen_px_);
   it = std::find(branches_.begin(),branches_.end(),"gen_py");  if ( it != branches_.end() ) tree_  -> SetBranchAddress( (*it).c_str(), gen_py_);
   it = std::find(branches_.begin(),branches_.end(),"gen_pz");  if ( it != branches_.end() ) tree_  -> SetBranchAddress( (*it).c_str(), gen_pz_);
}
PhysicsObjectTree<MET>::~PhysicsObjectTree() {}

// Member function
Collection<MET>  PhysicsObjectTree<MET>::collection()
{
   std::vector<MET> mets;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      MET met(px_[i], py_[i], pz_[i]);
      met.significanceMatrix(sigxx_[i],sigxy_[i],sigyx_[i],sigyy_[i]);
      met.genP(gen_px_[i],gen_py_[i],gen_pz_[i]);
      mets.push_back(met);
   }
   Collection<MET> metCollection(mets, name_);
   return metCollection;

}

// MUON
// Constructors and destructor
PhysicsObjectTree<Muon>::PhysicsObjectTree() : PhysicsObjectTreeBase<Muon>()
{
}
PhysicsObjectTree<Muon>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<Muon>(tree, name)
{
  tree_  -> SetBranchAddress ("isPFMuon"      , isPFMuon_     ) ;      
  tree_  -> SetBranchAddress ("isGlobalMuon"  , isGlobalMuon_ ) ;  
  tree_  -> SetBranchAddress ("isTrackerMuon" , isTrackerMuon_) ; 
  tree_  -> SetBranchAddress ("isLooseMuon"   , isLooseMuon_  ) ;   
  tree_  -> SetBranchAddress ("isMediumMuon"  , isMediumMuon_ ) ;  
  tree_  -> SetBranchAddress ("isTightMuon"   , isTightMuon_ ) ;  

  tree_  -> SetBranchAddress ("validFraction" ,validFraction_ ) ;
  tree_  -> SetBranchAddress ("segmentCompatibility" , segmentCompatibility_) ;
  tree_  -> SetBranchAddress ("trkKink" , trkKink_) ;      
  tree_  -> SetBranchAddress ("chi2LocalPos" ,chi2LocalPos_) ;

  tree_  -> SetBranchAddress ("normChi2" , normChi2_) ;
}
PhysicsObjectTree<Muon>::~PhysicsObjectTree()
{
}
// Member functions
Collection<Muon>  PhysicsObjectTree<Muon>::collection()
{
   std::vector<Muon> muons;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      Muon muon(pt_[i], eta_[i], phi_[i], e_[i], q_[i]);
      muon.isPFMuon(isPFMuon_[i]) ;      
      muon.isGlobalMuon(isGlobalMuon_[i]) ;  
      muon.isTrackerMuon(isTrackerMuon_[i]) ; 
      muon.isLooseMuon(isLooseMuon_[i]) ;   
      muon.isMediumMuon(isMediumMuon_[i]) ;  
      muon.isTightMuon(isTightMuon_[i]) ;

      muon.validFraction(validFraction_[i]) ;
      muon.segmentCompatibility(segmentCompatibility_[i]) ;
      muon.trkKink(trkKink_[i]) ;      
      muon.chi2LocalPos(chi2LocalPos_[i]) ; 
      
      muon.normChi2(normChi2_[i]) ;
      muons.push_back(muon);
   }
   Collection<Muon> muonCollection(muons, name_);
   return muonCollection;
}

// JETTAG
// Constructors and destructor
PhysicsObjectTree<JetTag>::PhysicsObjectTree() : PhysicsObjectTreeBase<JetTag>()
{
}
PhysicsObjectTree<JetTag>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<JetTag>(tree, name)
{
   tree_  -> SetBranchAddress( "btag", btag_    );
}
PhysicsObjectTree<JetTag>::~PhysicsObjectTree()
{
}
// Member functions
Collection<JetTag>  PhysicsObjectTree<JetTag>::collection()
{
   std::vector<JetTag> jetstags;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      JetTag jettag(pt_[i], eta_[i], phi_[i], e_[i]);
      jettag.btag(btag_[i]);
      jetstags.push_back(jettag);
   }
   Collection<JetTag> jettagCollection(jetstags, name_);
   return jettagCollection;
}


// GenJet
// Constructors and destructor
PhysicsObjectTree<GenJet>::PhysicsObjectTree() : PhysicsObjectTreeBase<GenJet>()
{
}
PhysicsObjectTree<GenJet>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<GenJet>(tree, name)
{
}
PhysicsObjectTree<GenJet>::~PhysicsObjectTree()
{
}
// Member functions
Collection<GenJet>  PhysicsObjectTree<GenJet>::collection()
{
   std::vector<GenJet> genjets;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      GenJet genjet(pt_[i], eta_[i], phi_[i], e_[i], q_[i]);
      genjets.push_back(genjet);
   }
   Collection<GenJet> genjetCollection(genjets, name_);
   return genjetCollection;
}



// VERTEX
// Constructors and destructor
PhysicsObjectTree<Vertex>::PhysicsObjectTree()              : PhysicsObjectTreeBase<Vertex>()     {}
PhysicsObjectTree<Vertex>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<Vertex>(tree, name) {}
PhysicsObjectTree<Vertex>::~PhysicsObjectTree()                                                   {}

// Member functions
Collection<Vertex>  PhysicsObjectTree<Vertex>::collection()
{
   std::vector<Vertex> vertices;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      Vertex vertex(x_[i], y_[i], z_[i]);
      vertex.chi2(chi2_[i]);
      vertex.ndof(ndof_[i]);
      vertex.rho(rho_[i]);
      vertex.fake(fake_[i]);

      vertices.push_back(vertex);
   }
   Collection<Vertex> vertexCollection(vertices, name_ );
   return vertexCollection;
}

// TriggerObjects
// Constructors and destructor
PhysicsObjectTree<TriggerObject>::PhysicsObjectTree() : PhysicsObjectTreeBase<TriggerObject>()
{
}
PhysicsObjectTree<TriggerObject>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<TriggerObject>(tree, name)
{
  tree_  -> SetBranchAddress ("type"      , type_     ) ;
}
PhysicsObjectTree<TriggerObject>::~PhysicsObjectTree() {}

// Member functions
Collection<TriggerObject>  PhysicsObjectTree<TriggerObject>::collection()
{
   std::vector<TriggerObject> triggers;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      TriggerObject trig(pt_[i], eta_[i], phi_[i], e_[i]);
      trig.type(type_[i]);
      triggers.push_back(trig);
   }
   Collection<TriggerObject> TriggerObjectCollection(triggers, name_);
   return TriggerObjectCollection;

}

// L1TMuon
// Constructors and destructor
PhysicsObjectTree<L1TMuon>::PhysicsObjectTree() : PhysicsObjectTreeBase<L1TMuon>()
{
}
PhysicsObjectTree<L1TMuon>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<L1TMuon>(tree, name)
{
  tree_  -> SetBranchAddress ("hwQual"   , hwQual_   ) ;      
  tree_  -> SetBranchAddress ("etaAtVtx" , etaAtVtx_ ) ;  
  tree_  -> SetBranchAddress ("phiAtVtx" , phiAtVtx_ ) ; 
}
PhysicsObjectTree<L1TMuon>::~PhysicsObjectTree()
{
}
// Member functions
Collection<L1TMuon>  PhysicsObjectTree<L1TMuon>::collection()
{
   std::vector<L1TMuon> muons;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      L1TMuon muon(pt_[i], eta_[i], phi_[i], e_[i], q_[i]);
      muon.hwQual  (hwQual_  [i]) ;      
      muon.etaAtVtx(etaAtVtx_[i]) ;  
      muon.phiAtVtx(phiAtVtx_[i]) ; 
      muons.push_back(muon);
   }
   Collection<L1TMuon> muonCollection(muons, name_);
   return muonCollection;
}

// L1TJet
// Constructors and destructor
PhysicsObjectTree<L1TJet>::PhysicsObjectTree() : PhysicsObjectTreeBase<L1TJet>()
{
}
PhysicsObjectTree<L1TJet>::PhysicsObjectTree(TChain * tree, const std::string & name) : PhysicsObjectTreeBase<L1TJet>(tree, name)
{
}
PhysicsObjectTree<L1TJet>::~PhysicsObjectTree()
{
}
// Member functions
Collection<L1TJet>  PhysicsObjectTree<L1TJet>::collection()
{
   std::vector<L1TJet> jets;
   for ( int i = 0 ; i < n_ ; ++i )
   {
      L1TJet jet(pt_[i], eta_[i], phi_[i], e_[i], 0);
      jets.push_back(jet);
   }
   Collection<L1TJet> jetCollection(jets, name_);
   return jetCollection;
}



// ======================================
// Templates declarations
template class PhysicsObjectTree<Candidate>;
template class PhysicsObjectTree<Jet>;
template class PhysicsObjectTree<MET>;
template class PhysicsObjectTree<Muon>;
template class PhysicsObjectTree<Vertex>;
template class PhysicsObjectTree<TriggerObject>;
template class PhysicsObjectTree<GenParticle>;
template class PhysicsObjectTree<GenJet>;
template class PhysicsObjectTree<L1TMuon>;
template class PhysicsObjectTree<L1TJet>;
