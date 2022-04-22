#include "LEAF/VBFTagger/include/VBFSelections.h"

using namespace std;


GenParticleSelection::GenParticleSelection(const Config & cfg, ParticleID pdgid_, int nmin_, int nmax_) : pdgid(pdgid_), nmin(nmin_), nmax(nmax_){}

bool GenParticleSelection::passes(VBFTaggerEvent & event){
  int count = 0;
  for(const auto & p : *event.genparticles_pruned) {
    if (abs(p.pdgid()) == (int)pdgid) count++;
  }
  return(count >= nmin && (count <= nmax || nmax == -1));
  return true;
}


NoGenTauSelection::NoGenTauSelection(const Config & cfg) {
  genparticleselection.reset(new GenParticleSelection(cfg, ParticleID::tau, 0, 0));
}

bool NoGenTauSelection::passes(VBFTaggerEvent & event){

  if (event.higgs_decay() == Decay::ZZtautautautau) return false;
  if (event.higgs_decay() == Decay::ZZeetautau) return false;
  if (event.higgs_decay() == Decay::ZZmumutautau) return false;
  if (event.higgs_decay() == Decay::ZZtautauvv) return false;

  if(!genparticleselection->passes(event)) return false;

  return true;
}


VBFJetDefinition::VBFJetDefinition(const Config& cfg, const float& min_jet_pt_): min_jet_pt(min_jet_pt_) {
}


bool VBFJetDefinition::process(VBFTaggerEvent& event) {

  bool isSet = false;
  for(const Jet& jet1: *event.jets_ak4chs){
    if (jet1.pt()<min_jet_pt) continue;
    for(const Jet& jet2: *event.jets_ak4chs){
      if (jet2.identifier() == jet1.identifier()) continue;
      if (jet2.pt()<min_jet_pt) continue;
      TLorentzVector jj = jet1.p4() + jet2.p4();
      if (jet2.eta()*jet1.eta()>0) continue;
      if (fabs(jet2.eta()-jet1.eta())<1.4) continue;
      if (jj.M()<200) continue;
      event.set_identifier_VBFjet1(jet1.identifier());
      event.set_identifier_VBFjet2(jet2.identifier());
      isSet=true;
      break;
    }
    if (isSet==true) break;
  }

  if (!isSet) return false;
  return true;

}
