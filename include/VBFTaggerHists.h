#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TROOT.h>
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/Analyzer/include/BaseHists.h"

using namespace std;

class VBFTaggerHists : public BaseHists{

public:
  // Constructors, destructor
  VBFTaggerHists(TString dir_);
  VBFTaggerHists(const VBFTaggerHists &) = default;
  VBFTaggerHists & operator = (const VBFTaggerHists &) = default;
  ~VBFTaggerHists() = default;

  // Main functions
  void fill(const VBFTaggerEvent & event);


protected:

  shared_ptr<TH1D> hmetpt, hmetphi, hsumweights;

};
