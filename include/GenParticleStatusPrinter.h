#pragma once

#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/Selection.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"

#include <vector>
// #include <pair>

class GenParticleStatusPrinter: public AnalysisModule<RecoEvent>{
 public:
  explicit GenParticleStatusPrinter(const Config & cfg);
  virtual bool process(RecoEvent & event) override;

};
