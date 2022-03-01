#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/GenParticlePrinter.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"


class GenEventMatch: public AnalysisModule<VBFTaggerEvent> {
public:
  explicit GenEventMatch(const Config& cfg);
  virtual ~GenEventMatch() = default;

  virtual bool process(VBFTaggerEvent & event) override;

  GenParticle FindParticle(VBFTaggerEvent& event, int );
  GenParticle FindParticle(VBFTaggerEvent&, ParticleID , GenParticle::StatusFlag status= GenParticle::isLastCopy);
  std::vector<GenParticle> FindMothers(VBFTaggerEvent&, GenParticle);
  std::vector<GenParticle> FindDaughters(VBFTaggerEvent&, GenParticle);

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
};
