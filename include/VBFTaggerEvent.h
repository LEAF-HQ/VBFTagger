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

  void DeleteVectorsVBFTaggerEvent();
  void SetZeroVectorsVBFTaggerEvent();
  void SetNewVectors();
  void SetNewNonVectors();


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
  int PF_UE_neutral_size() const { return m_PF_UE_neutral_size;}

  int is_VBF() const { return m_is_VBF;}
  int eventCategory() const { return m_eventCategory;}
  int n_PF_jet1() const { return m_n_PF_jet1;}
  int n_PF_jet2() const { return m_n_PF_jet2;}
  int n_PF_VBF_charged() const { return m_n_PF_VBF_charged;}
  int n_PF_VBF_neutral() const { return m_n_PF_VBF_neutral;}
  int n_nonVBF_jets() const { return m_n_nonVBF_jets;}
  float HT_nonVBF_jets() const { return m_HT_nonVBF_jets;}
  float mjj() const { return m_mjj;}
  float Zeppenfeld() const { return m_Zeppenfeld;}
  float Zeppenfeld_charged() const { return m_Zeppenfeld_charged;}
  float Zeppenfeld_neutral() const { return m_Zeppenfeld_neutral;}
  float energy_density_ratio() const { return m_energy_density_ratio;}
  float energy_density_ratio_charged() const { return m_energy_density_ratio_charged;}
  float energy_density_ratio_neutral() const { return m_energy_density_ratio_neutral;}



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
  void set_PF_UE_neutral_size(int x) { m_PF_UE_neutral_size = x;}

  void set_is_VBF(int x) { m_is_VBF = x;}
  void set_eventCategory(int x) { m_eventCategory = x;}
  void set_n_PF_jet1(int x) { m_n_PF_jet1 = x;}
  void set_n_PF_jet2(int x) { m_n_PF_jet2 = x;}
  void set_n_PF_VBF_charged(int x) { m_n_PF_VBF_charged = x;}
  void set_n_PF_VBF_neutral(int x) { m_n_PF_VBF_neutral = x;}
  void set_n_nonVBF_jets(int x) { m_n_nonVBF_jets = x;}
  void set_HT_nonVBF_jets(float x) { m_HT_nonVBF_jets = x;}
  void set_mjj(float x) { m_mjj = x;}
  void set_Zeppenfeld(float x) { m_Zeppenfeld = x;}
  void set_Zeppenfeld_charged(float x) { m_Zeppenfeld_charged = x;}
  void set_Zeppenfeld_neutral(float x) { m_Zeppenfeld_neutral = x;}
  void set_energy_density_ratio(float x) { m_energy_density_ratio = x;}
  void set_energy_density_ratio_charged(float x) { m_energy_density_ratio_charged = x;}
  void set_energy_density_ratio_neutral(float x) { m_energy_density_ratio_neutral = x;}

  vector<GenParticle>* gen_higgs;
  vector<GenParticle>* gen_higgs_Z;
  vector<GenParticle>* gen_higgs_leptons;
  vector<GenParticle>* gen_higgs_decays;
  vector<GenParticle>* gen_non_higgs_decays;
  vector<GenJet>* VBF_genjets;

  vector<Muon>* H_muons;
  vector<Electron>* H_electrons;
  vector<FlavorParticle>* H_leptons;
  vector<TLorentzVector>* reco_Z_bosons;
  vector<TLorentzVector>* reco_H_bosons;
  vector<Jet>* VBF_jets;
  vector<Jet>* non_VBF_jets;

  vector<PFCandidate>* PF_Higgs;
  vector<PFCandidate>* PF_VBF;
  vector<PFCandidate>* PF_UE_charged;
  vector<PFCandidate>* PF_UE_neutral;

  vector<double>* VBFjet_pt;
  vector<double>* VBFjet_eta;
  vector<double>* VBFjet_phi;
  vector<double>* VBFjet_energy;
  vector<double>* VBFjet_score_qgl;
  vector<double>* VBFjet_n_constituents;
  vector<double>* nonVBFjet_pt;
  vector<double>* nonVBFjet_eta;
  vector<double>* nonVBFjet_phi;
  vector<double>* nonVBFjet_energy;
  vector<double>* nonVBFjet_score_qgl;
  vector<double>* nonVBFjet_n_constituents;

  vector<double>* PF_VBF1_pt;
  vector<double>* PF_VBF1_eta;
  vector<double>* PF_VBF1_phi;
  vector<double>* PF_VBF1_energy;
  vector<double>* PF_VBF1_pdgid;
  vector<double>* PF_VBF1_charge;
  vector<double>* PF_VBF1_puppiweight;

  vector<double>* PF_VBF2_pt;
  vector<double>* PF_VBF2_eta;
  vector<double>* PF_VBF2_phi;
  vector<double>* PF_VBF2_energy;
  vector<double>* PF_VBF2_pdgid;
  vector<double>* PF_VBF2_charge;
  vector<double>* PF_VBF2_puppiweight;

  vector<double>* PF_UE_charged_pt;
  vector<double>* PF_UE_charged_eta;
  vector<double>* PF_UE_charged_phi;
  vector<double>* PF_UE_charged_energy;
  vector<double>* PF_UE_charged_pdgid;
  vector<double>* PF_UE_charged_charge;
  vector<double>* PF_UE_charged_puppiweight;

  vector<double>* PF_UE_neutral_pt;
  vector<double>* PF_UE_neutral_eta;
  vector<double>* PF_UE_neutral_phi;
  vector<double>* PF_UE_neutral_energy;
  vector<double>* PF_UE_neutral_pdgid;
  vector<double>* PF_UE_neutral_charge;
  vector<double>* PF_UE_neutral_puppiweight;

  vector<double>* PF_UE_pt;
  vector<double>* PF_UE_eta;
  vector<double>* PF_UE_phi;
  vector<double>* PF_UE_energy;
  vector<double>* PF_UE_pdgid;
  vector<double>* PF_UE_charge;
  vector<double>* PF_UE_puppiweight;

  vector<double>* PF_VBF_pt;
  vector<double>* PF_VBF_eta;
  vector<double>* PF_VBF_phi;
  vector<double>* PF_VBF_energy;
  vector<double>* PF_VBF_pdgid;
  vector<double>* PF_VBF_charge;
  vector<double>* PF_VBF_puppiweight;

  vector<double>* PF_UE_VBF_pt;
  vector<double>* PF_UE_VBF_eta;
  vector<double>* PF_UE_VBF_phi;
  vector<double>* PF_UE_VBF_energy;
  vector<double>* PF_UE_VBF_pdgid;
  vector<double>* PF_UE_VBF_charge;
  vector<double>* PF_UE_VBF_puppiweight;

protected:
  int m_identifier_VBFgenparticle1;
  int m_identifier_VBFgenparticle2;
  Decay m_gen_higgs_decay;

  float m_H_chi2, m_Z1_chi2, m_Z2_chi2, m_HZZ_chi2;

  int m_PF_Higgs_size;
  int m_PF_VBF_size;
  int m_PF_UE_charged_size;
  int m_PF_UE_neutral_size;

  int m_is_VBF;
  int m_eventCategory;
  int m_n_PF_jet1;
  int m_n_PF_jet2;
  int m_n_PF_VBF_charged;
  int m_n_PF_VBF_neutral;
  int m_n_nonVBF_jets;
  float m_HT_nonVBF_jets;
  float m_mjj;
  float m_Zeppenfeld;
  float m_Zeppenfeld_charged;
  float m_Zeppenfeld_neutral;
  float m_energy_density_ratio;
  float m_energy_density_ratio_charged;
  float m_energy_density_ratio_neutral;

};
