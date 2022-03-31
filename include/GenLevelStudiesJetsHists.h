#pragma once

#include <TString.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/Analyzer/include/BaseHists.h"
#include "LEAF/Analyzer/include/CleaningModules.h"

using namespace std;

// class GenJetIDLeptonRemoval {
// public:
//   explicit GenJetIDLeptonRemoval(double dr);
//   bool operator()(const GenJet&, const RecoEvent&) const;
// private:
//   double m_dr;
// };


class GenLevelStudiesJetsHists : public BaseHists{

public:
  // Constructors, destructor
  GenLevelStudiesJetsHists(TString dir_);
  GenLevelStudiesJetsHists(const GenLevelStudiesJetsHists &) = default;
  GenLevelStudiesJetsHists & operator = (const GenLevelStudiesJetsHists &) = default;
  ~GenLevelStudiesJetsHists() = default;

  // Main functions
  void fill(const RecoEvent & event);

  // unique_ptr<GenJetCleaner> cleaner_genjet;

};
