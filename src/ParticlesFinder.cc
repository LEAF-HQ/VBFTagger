#include "LEAF/VBFTagger/include/ParticlesFinder.h"

using namespace std;

GenParticle ParticleFinder(const VBFTaggerEvent& event, int identifier) {
  for(const auto & p : *event.genparticles_pruned) {
    if (p.identifier() == identifier) return p;
  }
  return GenParticle();
}

GenParticle ParticleFinder(const VBFTaggerEvent& event, ParticleID pdgID, GenParticle::StatusFlag status) {
  for(const auto & p : *event.genparticles_pruned){
    if (!p.isHardProcess() && !p.fromHardProcessBeforeFSR()) continue;
    if (p.pdgid() == (int)pdgID && p.get_statusflag(status)) return p;
  }
  return GenParticle();
}

std::vector<GenParticle> DaughtersFinder(const VBFTaggerEvent& event, GenParticle particle) {
  std::vector<GenParticle> daughters;
  for(const auto & p : *event.genparticles_pruned){
    if (p.mother_identifier()==particle.identifier()) daughters.push_back(p);
  }
  return daughters;
}
