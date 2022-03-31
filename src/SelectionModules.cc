#include "LEAF/VBFTagger/include/SelectionModules.h"
#include "LEAF/Analyzer/include/useful_functions.h"

using namespace std;

GenJetIDLeptonRemoval::GenJetIDLeptonRemoval(const double & dr_): m_dr(dr_) {}
bool GenJetIDLeptonRemoval::process(GenEvent & event){

  // throw away jets, that are closer than mindR to any visible lepton
  vector<GenJet> cleaned_jets;
  for(size_t i=0; i<event.genjets->size(); i++){
    GenJet gj = event.genjets->at(i);
    bool keep = true;
    for(size_t j=0; j<event.genparticles_all->size(); j++){
      GenParticle gt = event.genparticles_all->at(j);
      if (gt.pdgid()<11 || gt.pdgid()>18) continue;
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
