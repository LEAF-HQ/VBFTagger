#include "LEAF/VBFTagger/include/GenEventMatch.h"

using namespace std;

GenEventMatch::GenEventMatch(const Config& cfg){

  gp_printer.reset(new GenParticlePrinter(cfg));

}



GenParticle GenEventMatch::FindParticle(VBFTaggerEvent& event, int identifier) {
  for(const auto & p : *event.genparticles_all) {
    if (p.identifier() == identifier) return p;
  }
  return GenParticle();
}

GenParticle GenEventMatch::FindParticle(VBFTaggerEvent& event, ParticleID pdgID, GenParticle::StatusFlag status) {
  for(const auto & p : *event.genparticles_all){
    if (!p.get_statusflag(GenParticle::isHardProcess) && !p.get_statusflag(GenParticle::fromHardProcessBeforeFSR)) continue;
    if (p.pdgid() == pdgID && p.get_statusflag(status)) return p;
  }
  return GenParticle();
}

std::vector<GenParticle> GenEventMatch::FindMothers(VBFTaggerEvent& event, GenParticle particle) {
  std::vector<GenParticle> mothers;
  int mother_id = particle.mother_identifier();
  if (mother_id<0) return mothers;
  for(const auto & p : *event.genparticles_all){
    if (p.identifier() == particle.identifier()) continue;
    if (!p.get_statusflag(GenParticle::isHardProcess) && !p.get_statusflag(GenParticle::fromHardProcessBeforeFSR)) continue;
    if (p.identifier() == mother_id || p.mother_identifier() == mother_id) mothers.push_back(p);
  }
  return mothers;
}

std::vector<GenParticle> GenEventMatch::FindDaughters(VBFTaggerEvent& event, GenParticle particle) {
  std::vector<GenParticle> daughters;
  for(const auto & p : *event.genparticles_all){
    if (p.mother_identifier()==particle.identifier()) daughters.push_back(p);
  }
  return daughters;
}


bool GenEventMatch::process(VBFTaggerEvent& event) {
  if(event.is_data) return true;

  std::vector<GenParticle> H_mothers = FindMothers(event, FindParticle(event, ParticleID::H, GenParticle::isFirstCopy));
  std::vector<GenParticle> H_daughters = FindDaughters(event, FindParticle(event, ParticleID::H, GenParticle::isLastCopy));

  std::vector<string> H_mothers_names;
  for (const auto &m: H_mothers) {
    H_mothers_names.push_back(pdgId2str(m.pdgid()));
    cout << pdgId2str(m.pdgid()) << " " << m.pt() << " " << m.eta() << " " << m.phi() << endl;
  }


  std::vector<string> H_daughters_names;
  std::vector<string> H_daughters_dauthers;
  for (const auto &d: H_daughters) {
    H_daughters_names.push_back(pdgId2str(d.pdgid()));
    for (const auto &dd: FindDaughters(event, d)) {
      H_daughters_dauthers.push_back(pdgId2str(dd.pdgid()));
    }
  }



  // cout << cyan << H_mothers_names << " --> Higgs --> " << H_daughters_names << " --> " << H_daughters_dauthers << reset << endl;

 bool check = true;
 bool check_pt = false;

  for(const auto & gj : *event.genjets){
    vector<GenParticle> particles_in_jet = ParticlesInJet(gj, H_mothers);
    vector<string> particles_in_jet_names;
    vector<double> particles_in_jet_etas;
    vector<double> particles_in_jet_DR;
    for (const auto &p: particles_in_jet) {
      particles_in_jet_names.push_back(pdgId2str(p.pdgid()));
      particles_in_jet_etas.push_back(p.eta());
      particles_in_jet_DR.push_back(deltaR(p, gj));
      check = false;
    }
    if (gj.pt()>10) check_pt = true;
    //cout << gj.pt() << " " << gj.eta() << " " << gj.phi() << " " << particles_in_jet.size() << " " << particles_in_jet_names << " " << particles_in_jet_etas << " " << particles_in_jet_DR << endl;
  }

  cout << "+++ End Event +++" << endl;

  if (check && check_pt){
    throw std::runtime_error("stop");

  }



  // for(const auto & gp : event->genparticles_all){
  //   cout << "  --> New particle" << endl;
  //
  //   FindParticle(int& ID)
  //

  return true;
}
