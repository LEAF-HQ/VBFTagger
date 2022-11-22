#pragma once

#include <iostream>
#include <sys/stat.h>

#include <TH1F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "LEAF/Analyzer/include/BaseHists.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/GenLevelConstants.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"

#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/Utils.h"

using namespace std;

class VBFGenJetsHists : public BaseHists{

public:
  // Constructors, destructor
  VBFGenJetsHists(TString dir_, TString selection_="");
  VBFGenJetsHists(const VBFGenJetsHists &) = default;
  VBFGenJetsHists & operator = (const VBFGenJetsHists &) = default;
  ~VBFGenJetsHists() = default;

  // Main functions
  void fill(const VBFTaggerEvent & event);

private:
  TString selection;

};
