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

  int eventCategory() const { return m_eventCategory;}
  float Zeppenfeld() const { return m_Zeppenfeld;}
  float Zeppenfeld_charged() const { return m_Zeppenfeld_charged;}
  float Zeppenfeld_neutral() const { return m_Zeppenfeld_neutral;}
  float energy_density_ratio() const { return m_energy_density_ratio;}
  float energy_density_ratio_charged() const { return m_energy_density_ratio_charged;}
  float energy_density_ratio_neutral() const { return m_energy_density_ratio_neutral;}
  int n_nonVBF_jets() const { return m_n_nonVBF_jets;}
  float HT_nonVBF_jets() const { return m_HT_nonVBF_jets;}
  int n_PF_jet1() const { return m_n_PF_jet1;}
  int n_PF_jet2() const { return m_n_PF_jet2;}

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

  void set_eventCategory(int x) { m_eventCategory = x;}
  void set_Zeppenfeld(float x) { m_Zeppenfeld = x;}
  void set_Zeppenfeld_charged(float x) { m_Zeppenfeld_charged = x;}
  void set_Zeppenfeld_neutral(float x) { m_Zeppenfeld_neutral = x;}
  void set_energy_density_ratio(float x) { m_energy_density_ratio = x;}
  void set_energy_density_ratio_charged(float x) { m_energy_density_ratio_charged = x;}
  void set_energy_density_ratio_neutral(float x) { m_energy_density_ratio_neutral = x;}
  void set_n_nonVBF_jets(int x) { m_n_nonVBF_jets = x;}
  void set_HT_nonVBF_jets(float x) { m_HT_nonVBF_jets = x;}
  void set_n_PF_jet1(int x) { m_n_PF_jet1 = x;}
  void set_n_PF_jet2(int x) { m_n_PF_jet2 = x;}

  vector<GenParticle>* gen_higgs;
  vector<GenParticle>* gen_higgs_Z;
  vector<GenParticle>* gen_higgs_leptons;
  vector<GenParticle>* gen_higgs_decays;
  vector<GenParticle>* gen_non_higgs_decays;

  vector<GenJet>* VBF_genjets;
  vector<Jet>* VBF_jets;
  vector<Jet>* non_VBF_jets;
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

  int m_eventCategory;
  float m_Zeppenfeld;
  float m_Zeppenfeld_charged;
  float m_Zeppenfeld_neutral;
  float m_energy_density_ratio;
  float m_energy_density_ratio_charged;
  float m_energy_density_ratio_neutral;
  int m_n_nonVBF_jets;
  float m_HT_nonVBF_jets;
  int m_n_PF_jet1;
  int m_n_PF_jet2;

};
