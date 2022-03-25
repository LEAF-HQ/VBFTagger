#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "LEAF/Analyzer/include/RecoEvent.h"

using namespace std;

// Container class for all quantities
class VBFTaggerEvent : public RecoEvent{

public:
  // Constructors, destructor
  VBFTaggerEvent();
  ~VBFTaggerEvent();

  void clear();

  void reset();

  int identifier_VBFjet1() const { return identifier_VBF1;}
  int identifier_VBFjet2() const { return identifier_VBF2;}

  void set_identifier_VBFjet1(int x) { identifier_VBF1 = x;}
  void set_identifier_VBFjet2(int x) { identifier_VBF2 = x;}

  int identifier_VBF1;
  int identifier_VBF2;

};
