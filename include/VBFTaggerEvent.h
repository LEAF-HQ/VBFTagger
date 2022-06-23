#pragma once

#include <TString.h>
#include <TH1F.h>
#include <map>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/GenLevelConstants.h"

using namespace std;

// Container class for all quantities
class VBFTaggerEvent : public RecoEvent{

public:
  // Constructors, destructor
  VBFTaggerEvent();
  ~VBFTaggerEvent();

  void clear();

  void reset();

  int identifier_VBFgenparticle1() const { return m_identifier_VBFgenparticle1;}
  int identifier_VBFgenparticle2() const { return m_identifier_VBFgenparticle2;}
  int identifier_VBFjet1() const { return m_identifier_VBFjet1;}
  int identifier_VBFjet2() const { return m_identifier_VBFjet2;}
  Decay gen_higgs_decay() const { return m_gen_higgs_decay;}

  void set_identifier_VBFgenparticle1(int x) { m_identifier_VBFgenparticle1 = x;}
  void set_identifier_VBFgenparticle2(int x) { m_identifier_VBFgenparticle2 = x;}
  void set_identifier_VBFjet1(int x) { m_identifier_VBFjet1 = x;}
  void set_identifier_VBFjet2(int x) { m_identifier_VBFjet2 = x;}
  void set_gen_higgs_decay(Decay x) { m_gen_higgs_decay = x;}


  vector<GenParticle>* gen_higgs;
  vector<GenParticle>* gen_higgs_Z;
  vector<GenParticle>* gen_higgs_leptons;
  vector<GenParticle>* gen_higgs_decays;
  vector<GenParticle>* gen_non_higgs_decays;

  vector<GenJet>* VBF_genjets;
  vector<Muon>* H_muons;
  vector<Electron>* H_electrons;
  vector<FlavorParticle>* H_leptons;

protected:
  int m_identifier_VBFgenparticle1;
  int m_identifier_VBFgenparticle2;
  int m_identifier_VBFjet1;
  int m_identifier_VBFjet2;
  Decay m_gen_higgs_decay;

};
