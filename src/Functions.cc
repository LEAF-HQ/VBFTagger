#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/VBFTagger/include/Functions.h"

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

double Zeppenfeld1(const VBFTaggerEvent& event, GenParticle p) {
  auto j1 = event.genjets->at(0);
  auto j2 = event.genjets->at(1);
  double z = fabs(p.eta()-(j1.eta()+j2.eta()) /2);
  return z;
}

double Zeppenfeld2(const VBFTaggerEvent& event, GenParticle p) {
  auto j1 = event.genjets->at(0);
  auto j2 = event.genjets->at(1);
  double z = fabs(p.eta()-(j1.eta()+j2.eta()) /2)/deltaEta(j1, j2);
  return z;
}
