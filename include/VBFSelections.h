#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"

#include <vector>

class GenParticleSelection: public Selection<VBFTaggerEvent>{
public:
  explicit GenParticleSelection(const Config & cfg, ParticleID pdgid_, int nmin_=0, int nmax_=-1);
  virtual bool passes(VBFTaggerEvent & event) override;

private:
  ParticleID pdgid;
  int nmin, nmax;
};


class NoGenTauSelection: public Selection<VBFTaggerEvent> {
public:
  explicit NoGenTauSelection(const Config & cfg);
  virtual bool passes(VBFTaggerEvent & event) override;

private:
  unique_ptr<GenParticleSelection> genparticleselection;

};


class GenLeptonPhaseSpaceSelection: public Selection<VBFTaggerEvent> {
public:
  explicit GenLeptonPhaseSpaceSelection(const Config & cfg);
  virtual bool passes(VBFTaggerEvent & event) override;
};


class VBFJetDefinition: public AnalysisModule<VBFTaggerEvent> {
public:
  explicit VBFJetDefinition(const Config& cfg, const float& min_jet_pt_);
  virtual ~VBFJetDefinition() = default;
  virtual bool process(VBFTaggerEvent & event) override;

private:
  float min_jet_pt;
};


class Higgs4LeptonsFinder: public AnalysisModule<VBFTaggerEvent> {
public:
  explicit Higgs4LeptonsFinder(const Config& cfg);
  virtual ~Higgs4LeptonsFinder() = default;
  virtual bool process(VBFTaggerEvent & event) override;
};
