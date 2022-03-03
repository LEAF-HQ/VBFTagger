#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/GenParticlePrinter.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/GenParticleStatusPrinter.h"


class GenEventMatch: public AnalysisModule<RecoEvent> {
public:
  explicit GenEventMatch(const Config& cfg);
  virtual ~GenEventMatch() = default;

  virtual bool process(RecoEvent & event) override;

  GenParticle FindParticle(RecoEvent& event, int );
  GenParticle FindParticle(RecoEvent&, ParticleID , GenParticle::StatusFlag status= GenParticle::isLastCopy);
  std::vector<GenParticle> FindMothers(RecoEvent&, GenParticle);
  std::vector<GenParticle> FindDaughters(RecoEvent&, GenParticle);

  template<typename T>
  std::vector<T> ParticlesInJet(const Particle  & jet, const std::vector<T> & particles, double deltarmin=0.6){
    std::vector<T> results;
    for(const auto & pi : particles){
      double dr = deltaR(pi, jet);
      if(dr < deltarmin && &pi != &jet) {
        deltarmin = dr;
        results.push_back(pi);
      }
    }
    return results;
  }

protected:

  unique_ptr<GenParticlePrinter> gp_printer;
  unique_ptr<GenParticleStatusPrinter> gp_status_printer;
};

template<class T>
ostream& operator<<(ostream& os, const std::vector<T>& vec)
{
 for (const auto& x: vec) {
    os << x << " ";
  }
  return os;
}
