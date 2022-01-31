#pragma once

#include <TString.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/Analyzer/include/BaseHists.h"

using namespace std;

class GenLevelStudiesHists : public BaseHists{

public:
  // Constructors, destructor
  GenLevelStudiesHists(TString dir_);
  GenLevelStudiesHists(const GenLevelStudiesHists &) = default;
  GenLevelStudiesHists & operator = (const GenLevelStudiesHists &) = default;
  ~GenLevelStudiesHists() = default;

  // Main functions
  void fill(const RecoEvent & event);

};
