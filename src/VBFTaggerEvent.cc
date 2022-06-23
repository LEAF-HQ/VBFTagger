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
  gen_higgs = new vector<GenParticle>;
  gen_higgs_Z = new vector<GenParticle>;
  gen_higgs_leptons = new vector<GenParticle>;
  gen_higgs_decays = new vector<GenParticle>;
  gen_non_higgs_decays = new vector<GenParticle>;
  VBF_genjets = new vector<GenJet>;
  H_muons = new vector<Muon>;
  H_electrons = new vector<Electron>;
  H_leptons = new vector<FlavorParticle>;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_identifier_VBFjet1 = -1;
  m_identifier_VBFjet2 = -1;
  m_gen_higgs_decay = Decay::nodecay;
}

VBFTaggerEvent::~VBFTaggerEvent(){
  delete gen_higgs;
  delete gen_higgs_Z;
  delete gen_higgs_leptons;
  delete gen_higgs_decays;
  delete gen_non_higgs_decays;
  delete VBF_genjets;
  delete H_muons;
  delete H_electrons;
  delete H_leptons;
}

void VBFTaggerEvent::clear(){
  RecoEvent::clear();
  delete gen_higgs;
  delete gen_higgs_Z;
  delete gen_higgs_leptons;
  delete gen_higgs_decays;
  delete gen_non_higgs_decays;
  delete VBF_genjets;
  delete H_muons;
  delete H_electrons;
  delete H_leptons;
  gen_higgs = 0;
  gen_higgs_Z = 0;
  gen_higgs_leptons = 0;
  gen_higgs_decays = 0;
  gen_non_higgs_decays = 0;
  VBF_genjets = 0;
  H_muons = 0;
  H_electrons = 0;
  H_leptons = 0;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_identifier_VBFjet1 = -1;
  m_identifier_VBFjet2 = -1;
  m_gen_higgs_decay = Decay::nodecay;
}

void VBFTaggerEvent::reset(){
  RecoEvent::reset();
  delete gen_higgs;
  delete gen_higgs_Z;
  delete gen_higgs_leptons;
  delete gen_higgs_decays;
  delete gen_non_higgs_decays;
  delete VBF_genjets;
  delete H_muons;
  delete H_electrons;
  delete H_leptons;
  gen_higgs = new vector<GenParticle>;
  gen_higgs_Z = new vector<GenParticle>;
  gen_higgs_leptons = new vector<GenParticle>;
  gen_higgs_decays = new vector<GenParticle>;
  gen_non_higgs_decays = new vector<GenParticle>;
  VBF_genjets = new vector<GenJet>;
  H_muons = new vector<Muon>;
  H_electrons = new vector<Electron>;
  H_leptons = new vector<FlavorParticle>;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_identifier_VBFjet1 = -1;
  m_identifier_VBFjet2 = -1;
  m_gen_higgs_decay = Decay::nodecay;
}
