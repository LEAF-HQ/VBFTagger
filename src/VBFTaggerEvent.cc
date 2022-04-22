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
  VBF_genjets = new vector<GenJet>;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_identifier_VBFjet1 = -1;
  m_identifier_VBFjet2 = -1;
  m_higgs_decay = Decay::nodecay;
}

VBFTaggerEvent::~VBFTaggerEvent(){
  delete VBF_genjets;
}

void VBFTaggerEvent::clear(){
  RecoEvent::clear();
  delete VBF_genjets;
  VBF_genjets = 0;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_identifier_VBFjet1 = -1;
  m_identifier_VBFjet2 = -1;
  m_higgs_decay = Decay::nodecay;
}

void VBFTaggerEvent::reset(){
  RecoEvent::reset();
  delete VBF_genjets;
  VBF_genjets = new vector<GenJet>;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_identifier_VBFjet1 = -1;
  m_identifier_VBFjet2 = -1;
  m_higgs_decay = Decay::nodecay;
}
