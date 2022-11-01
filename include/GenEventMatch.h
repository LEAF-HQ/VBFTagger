#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/GenParticlePrinter.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/GenParticleStatusPrinter.h"


class GenEventMatch: public AnalysisModule<VBFTaggerEvent> {
public:
  explicit GenEventMatch(const Config& cfg);
  virtual ~GenEventMatch() = default;

  virtual bool process(VBFTaggerEvent & event) override;

  GenParticle FindParticle(VBFTaggerEvent& event, int );
  GenParticle FindParticle(VBFTaggerEvent&, ParticleID , GenParticle::StatusFlag status= GenParticle::StatusFlag::isLastCopy);
  GenParticle FindMother(VBFTaggerEvent&, int);
  std::vector<GenParticle> FindMothers(VBFTaggerEvent&, GenParticle);
  std::vector<GenParticle> FindDaughters(VBFTaggerEvent&, GenParticle, bool check_PhaseSpace);

  bool isHiggsDecay(VBFTaggerEvent&, const GenParticle&);
  void ClearGenParticles(VBFTaggerEvent&);

  void DoMotherMatching(VBFTaggerEvent&);
  void DoDecayMatching(VBFTaggerEvent&);



protected:
  bool skipMatching;
  bool skipMotherMatching;
  unique_ptr<GenParticlePrinter> gp_printer;
  unique_ptr<GenParticlePrinter> gp_printer_stable;
  unique_ptr<GenParticleStatusPrinter> gp_status_printer;
};
