#include "LEAF/VBFTagger/include/SelectionModules.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/VBFTagger/include/Functions.h"

using namespace std;

GenJetIDLeptonRemoval::GenJetIDLeptonRemoval(const double & dr_): m_dr(dr_) {}
bool GenJetIDLeptonRemoval::process(GenEvent & event){

  // throw away jets, that are closer than mindR to any visible lepton
  vector<GenJet> cleaned_jets;
  for(size_t i=0; i<event.genjets->size(); i++){
    GenJet gj = event.genjets->at(i);
    bool keep = true;
    for(size_t j=0; j<event.genparticles_stable->size(); j++){
      GenParticle gt = event.genparticles_stable->at(j);
      if (fabs(gt.pdgid())<11 || fabs(gt.pdgid())>18) continue;
      if(deltaR(gj, gt) < m_dr){
        keep = false;
        break;
      }
    }
    if(keep) cleaned_jets.emplace_back(gj);
  }
  swap(cleaned_jets, *event.genjets);
  return true;
}

GenParticleCleaner::GenParticleCleaner(const GenID<GenParticle> & id_): id(id_) {}
bool GenParticleCleaner::process(GenEvent & event){
  clean_collection(event.genparticles_stable, event, id);
  return true;
}

GenLJCleaner::GenLJCleaner(const double & dr_): m_dr(dr_) {}
bool GenLJCleaner::process(GenEvent & event){
//
  // throw away particles that are closer than mindR to the two leading jets
  if (event.genjets->size()<2) {return false;}
  vector<GenParticle> cleaner;
  GenJet j1 = event.genjets->at(0);
  GenJet j2 = event.genjets->at(1);
  for (const GenParticle& p: *event.genparticles_stable) {
    if(std::min(deltaR(p,j1), deltaR(p,j2)) > m_dr) {
      cleaner.emplace_back(p);
    }
  }
  swap(cleaner, *event.genparticles_stable);
  return true;
}

// GenJetInvMassTreshold::GenJetInvMassTreshold(const double & tresh_): tresh(tresh_) {}
// bool GenJetInvMassTreshold::process(GenEvent & event) {
//   vector<GenJet> jets_new;
//   vector<GenParticle> particles_new;
//   GenJet j1, j2;
//   TLorentzVector v;
//   if (event.genjets->size()>1) {
//     j1 = event.genjets->at(0);
//     j2 = event.genejts->at(1);
//     v = j1.p4() + j2.p4();
//     if (v.M()>tresh) {}
//   }
// }
