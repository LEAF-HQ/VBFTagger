#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/Analyzer/include/constants.h"
#include <TH1D.h>
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
#include <iostream>
#include <sys/stat.h>

using namespace std;

VBFTaggerEvent::VBFTaggerEvent(){
  identifier_VBF1 = -1;
  identifier_VBF2 = -1;
}

VBFTaggerEvent::~VBFTaggerEvent(){
}

void VBFTaggerEvent::clear(){
  RecoEvent::clear();
  identifier_VBF1 = -1;
  identifier_VBF2 = -1;
}

void VBFTaggerEvent::reset(){
  RecoEvent::reset();
  identifier_VBF1 = -1;
  identifier_VBF2 = -1;
}
