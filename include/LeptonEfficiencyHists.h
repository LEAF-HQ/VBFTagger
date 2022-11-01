#pragma once

#include "LEAF/Analyzer/include/BaseHists.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/GenLevelConstants.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"

#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/Utils.h"

using namespace std;

class LeptonEfficiencyHists : public BaseHists{

public:
  // Constructors, destructor
  LeptonEfficiencyHists(TString dir_);
  LeptonEfficiencyHists(const LeptonEfficiencyHists &) = default;
  LeptonEfficiencyHists & operator = (const LeptonEfficiencyHists &) = default;
  ~LeptonEfficiencyHists() = default;

  // Main functions
  void fill(const VBFTaggerEvent & event);

};
