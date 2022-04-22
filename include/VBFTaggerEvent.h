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
  Decay higgs_decay() const { return m_higgs_decay;}

  void set_identifier_VBFgenparticle1(int x) { m_identifier_VBFgenparticle1 = x;}
  void set_identifier_VBFgenparticle2(int x) { m_identifier_VBFgenparticle2 = x;}
  void set_identifier_VBFjet1(int x) { m_identifier_VBFjet1 = x;}
  void set_identifier_VBFjet2(int x) { m_identifier_VBFjet2 = x;}
  void set_higgs_decay(Decay x) { m_higgs_decay = x;}

  vector<GenJet>* VBF_genjets;
  
protected:
  int m_identifier_VBFgenparticle1;
  int m_identifier_VBFgenparticle2;
  int m_identifier_VBFjet1;
  int m_identifier_VBFjet2;
  Decay m_higgs_decay;

};
