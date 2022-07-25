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
  Decay gen_higgs_decay() const { return m_gen_higgs_decay;}
  float H_chi2() const { return m_H_chi2;}
  float Z1_chi2() const { return m_Z1_chi2;}
  float Z2_chi2() const { return m_Z2_chi2;}
  float HZZ_chi2() const { return m_HZZ_chi2;}
  int PF_Higgs_size() const { return m_PF_Higgs_size;}
  int PF_VBF_size() const { return m_PF_VBF_size;}
  int PF_UE_charged_size() const { return m_PF_UE_charged_size;}
  int PF_UE_neutrals_size() const { return m_PF_UE_neutrals_size;}

  void set_identifier_VBFgenparticle1(int x) { m_identifier_VBFgenparticle1 = x;}
  void set_identifier_VBFgenparticle2(int x) { m_identifier_VBFgenparticle2 = x;}
  void set_gen_higgs_decay(Decay x) { m_gen_higgs_decay = x;}
  void set_H_chi2(float x) { m_H_chi2 = x;}
  void set_Z1_chi2(float x) { m_Z1_chi2 = x;}
  void set_Z2_chi2(float x) { m_Z2_chi2 = x;}
  void set_HZZ_chi2(float x) { m_HZZ_chi2 = x;}
  void set_PF_Higgs_size(int x) { m_PF_Higgs_size = x;}
  void set_PF_VBF_size(int x) { m_PF_VBF_size = x;}
  void set_PF_UE_charged_size(int x) { m_PF_UE_charged_size = x;}
  void set_PF_UE_neutrals_size(int x) { m_PF_UE_neutrals_size = x;}

  vector<GenParticle>* gen_higgs;
  vector<GenParticle>* gen_higgs_Z;
  vector<GenParticle>* gen_higgs_leptons;
  vector<GenParticle>* gen_higgs_decays;
  vector<GenParticle>* gen_non_higgs_decays;

  vector<GenJet>* VBF_genjets;
  vector<Jet>* VBF_jets;
  vector<Muon>* H_muons;
  vector<Electron>* H_electrons;
  vector<FlavorParticle>* H_leptons;
  vector<TLorentzVector>* reco_Z_bosons;
  vector<TLorentzVector>* reco_H_bosons;
  vector<PFCandidate>* PF_Higgs;
  vector<PFCandidate>* PF_VBF;
  vector<PFCandidate>* PF_UE_charged;
  vector<PFCandidate>* PF_UE_neutrals;

protected:
  int m_identifier_VBFgenparticle1;
  int m_identifier_VBFgenparticle2;
  Decay m_gen_higgs_decay;
  float m_H_chi2, m_Z1_chi2, m_Z2_chi2, m_HZZ_chi2;
  int m_PF_Higgs_size;
  int m_PF_VBF_size;
  int m_PF_UE_charged_size;
  int m_PF_UE_neutrals_size;

};
