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
  VBF_jets = new vector<Jet>;
  non_VBF_jets = new vector<Jet>;
  H_muons = new vector<Muon>;
  H_electrons = new vector<Electron>;
  H_leptons = new vector<FlavorParticle>;
  reco_Z_bosons = new vector<TLorentzVector>;
  reco_H_bosons = new vector<TLorentzVector>;
  m_H_chi2 = -1;
  m_Z1_chi2 = -1;
  m_Z2_chi2 = -1;
  m_HZZ_chi2 = -1;
  PF_Higgs = new vector<PFCandidate>;
  PF_VBF = new vector<PFCandidate>;
  PF_UE_charged = new vector<PFCandidate>;
  PF_UE_neutrals = new vector<PFCandidate>;
  m_PF_Higgs_size = -1;
  m_PF_VBF_size = -1;
  m_PF_UE_charged_size = -1;
  m_PF_UE_neutrals_size = -1;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_gen_higgs_decay = Decay::nodecay;
  m_eventCategory = -1;
  m_Zeppenfeld = -1;
  m_Zeppenfeld_charged = -1;
  m_Zeppenfeld_neutral = -1;
  m_energy_density_ratio = -1;
  m_energy_density_ratio_charged = -1;
  m_energy_density_ratio_neutral = -1;
  m_n_nonVBF_jets = -1;
  m_HT_nonVBF_jets = -1;
  m_n_PF_jet1 = -1;
  m_n_PF_jet2 = -1;

  m_is_VBF = -1;
  PF_pt = new vector<double>;
  PF_eta = new vector<double>;
  PF_phi = new vector<double>;
  PF_energy = new vector<double>;
  PF_pdgid = new vector<double>;
  PF_charge = new vector<double>;
  PF_puppiweight = new vector<double>;
  VBFjet_pt = new vector<double>;
  VBFjet_eta = new vector<double>;
  VBFjet_phi = new vector<double>;
  VBFjet_energy = new vector<double>;
  VBFjet_score_qgl = new vector<double>;
  VBFjet_n_constituents = new vector<double>;
  nonVBFjet_pt = new vector<double>;
  nonVBFjet_eta = new vector<double>;
  nonVBFjet_phi = new vector<double>;
  nonVBFjet_energy = new vector<double>;
  nonVBFjet_score_qgl = new vector<double>;
  nonVBFjet_n_constituents = new vector<double>;
}

VBFTaggerEvent::~VBFTaggerEvent(){
  delete gen_higgs;
  delete gen_higgs_Z;
  delete gen_higgs_leptons;
  delete gen_higgs_decays;
  delete gen_non_higgs_decays;
  delete VBF_genjets;
  delete VBF_jets;
  delete non_VBF_jets;
  delete H_muons;
  delete H_electrons;
  delete H_leptons;
  delete reco_Z_bosons;
  delete reco_H_bosons;
  delete PF_Higgs;
  delete PF_VBF;
  delete PF_UE_charged;
  delete PF_UE_neutrals;

  delete PF_pt;
  delete PF_eta;
  delete PF_phi;
  delete PF_energy;
  delete PF_pdgid;
  delete PF_charge;
  delete PF_puppiweight;
  delete VBFjet_pt;
  delete VBFjet_eta;
  delete VBFjet_phi;
  delete VBFjet_energy;
  delete VBFjet_score_qgl;
  delete VBFjet_n_constituents;
  delete nonVBFjet_pt;
  delete nonVBFjet_eta;
  delete nonVBFjet_phi;
  delete nonVBFjet_energy;
  delete nonVBFjet_score_qgl;
  delete nonVBFjet_n_constituents;
}

void VBFTaggerEvent::clear(){
  RecoEvent::clear();
  delete gen_higgs;
  delete gen_higgs_Z;
  delete gen_higgs_leptons;
  delete gen_higgs_decays;
  delete gen_non_higgs_decays;
  delete VBF_genjets;
  delete VBF_jets;
  delete non_VBF_jets;
  delete H_muons;
  delete H_electrons;
  delete H_leptons;
  delete reco_Z_bosons;
  delete reco_H_bosons;
  delete PF_Higgs;
  delete PF_VBF;
  delete PF_UE_charged;
  delete PF_UE_neutrals;
  delete PF_pt;
  delete PF_eta;
  delete PF_phi;
  delete PF_energy;
  delete PF_pdgid;
  delete PF_charge;
  delete PF_puppiweight;
  delete VBFjet_pt;
  delete VBFjet_eta;
  delete VBFjet_phi;
  delete VBFjet_energy;
  delete VBFjet_score_qgl;
  delete VBFjet_n_constituents;
  delete nonVBFjet_pt;
  delete nonVBFjet_eta;
  delete nonVBFjet_phi;
  delete nonVBFjet_energy;
  delete nonVBFjet_score_qgl;
  delete nonVBFjet_n_constituents;
  gen_higgs = 0;
  gen_higgs_Z = 0;
  gen_higgs_leptons = 0;
  gen_higgs_decays = 0;
  gen_non_higgs_decays = 0;
  VBF_genjets = 0;
  VBF_jets = 0;
  non_VBF_jets = 0;
  H_muons = 0;
  H_electrons = 0;
  H_leptons = 0;
  reco_Z_bosons = 0;
  reco_H_bosons = 0;
  m_H_chi2 = -1;
  m_Z1_chi2 = -1;
  m_Z2_chi2 = -1;
  m_HZZ_chi2 = -1;
  PF_Higgs = 0;
  PF_VBF = 0;
  PF_UE_charged = 0;
  PF_UE_neutrals = 0;
  m_PF_Higgs_size = -1;
  m_PF_VBF_size = -1;
  m_PF_UE_charged_size = -1;
  m_PF_UE_neutrals_size = -1;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_gen_higgs_decay = Decay::nodecay;
  m_eventCategory = -1;
  m_Zeppenfeld = -1;
  m_Zeppenfeld_charged = -1;
  m_Zeppenfeld_neutral = -1;
  m_energy_density_ratio = -1;
  m_energy_density_ratio_charged = -1;
  m_energy_density_ratio_neutral = -1;
  m_n_nonVBF_jets = -1;
  m_HT_nonVBF_jets = -1;
  m_n_PF_jet1 = -1;
  m_n_PF_jet2 = -1;

  m_is_VBF = -1;
  PF_pt = new vector<double>;
  PF_eta = new vector<double>;
  PF_phi = new vector<double>;
  PF_energy = new vector<double>;
  PF_pdgid = new vector<double>;
  PF_charge = new vector<double>;
  PF_puppiweight = new vector<double>;
  VBFjet_pt = new vector<double>;
  VBFjet_eta = new vector<double>;
  VBFjet_phi = new vector<double>;
  VBFjet_energy = new vector<double>;
  VBFjet_score_qgl = new vector<double>;
  VBFjet_n_constituents = new vector<double>;
  nonVBFjet_pt = new vector<double>;
  nonVBFjet_eta = new vector<double>;
  nonVBFjet_phi = new vector<double>;
  nonVBFjet_energy = new vector<double>;
  nonVBFjet_score_qgl = new vector<double>;
  nonVBFjet_n_constituents = new vector<double>;
}

void VBFTaggerEvent::reset(){
  RecoEvent::reset();
  delete gen_higgs;
  delete gen_higgs_Z;
  delete gen_higgs_leptons;
  delete gen_higgs_decays;
  delete gen_non_higgs_decays;
  delete VBF_genjets;
  delete VBF_jets;
  delete non_VBF_jets;
  delete H_muons;
  delete H_electrons;
  delete H_leptons;
  delete reco_Z_bosons;
  delete reco_H_bosons;
  delete PF_Higgs;
  delete PF_VBF;
  delete PF_UE_charged;
  delete PF_UE_neutrals;
  delete PF_pt;
  delete PF_eta;
  delete PF_phi;
  delete PF_energy;
  delete PF_pdgid;
  delete PF_charge;
  delete PF_puppiweight;
  delete VBFjet_pt;
  delete VBFjet_eta;
  delete VBFjet_phi;
  delete VBFjet_energy;
  delete VBFjet_score_qgl;
  delete VBFjet_n_constituents;
  delete nonVBFjet_pt;
  delete nonVBFjet_eta;
  delete nonVBFjet_phi;
  delete nonVBFjet_energy;
  delete nonVBFjet_score_qgl;
  delete nonVBFjet_n_constituents;
  gen_higgs = new vector<GenParticle>;
  gen_higgs_Z = new vector<GenParticle>;
  gen_higgs_leptons = new vector<GenParticle>;
  gen_higgs_decays = new vector<GenParticle>;
  gen_non_higgs_decays = new vector<GenParticle>;
  VBF_genjets = new vector<GenJet>;
  VBF_jets = new vector<Jet>;
  non_VBF_jets = new vector<Jet>;
  H_muons = new vector<Muon>;
  H_electrons = new vector<Electron>;
  H_leptons = new vector<FlavorParticle>;
  reco_Z_bosons = new vector<TLorentzVector>;
  reco_H_bosons = new vector<TLorentzVector>;
  m_H_chi2 = -1;
  m_Z1_chi2 = -1;
  m_Z2_chi2 = -1;
  m_HZZ_chi2 = -1;
  PF_Higgs = new vector<PFCandidate>;
  PF_VBF = new vector<PFCandidate>;
  PF_UE_charged = new vector<PFCandidate>;
  PF_UE_neutrals = new vector<PFCandidate>;
  m_PF_Higgs_size = -1;
  m_PF_VBF_size = -1;
  m_PF_UE_charged_size = -1;
  m_PF_UE_neutrals_size = -1;
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_gen_higgs_decay = Decay::nodecay;
  m_eventCategory = -1;
  m_Zeppenfeld = -1;
  m_Zeppenfeld_charged = -1;
  m_Zeppenfeld_neutral = -1;
  m_energy_density_ratio = -1;
  m_energy_density_ratio_charged = -1;
  m_energy_density_ratio_neutral = -1;
  m_n_nonVBF_jets = -1;
  m_HT_nonVBF_jets = -1;
  m_n_PF_jet1 = -1;
  m_n_PF_jet2 = -1;

  m_is_VBF = -1;

  PF_pt = new vector<double>;
  PF_eta = new vector<double>;
  PF_phi = new vector<double>;
  PF_energy = new vector<double>;
  PF_pdgid = new vector<double>;
  PF_charge = new vector<double>;
  PF_puppiweight = new vector<double>;
  VBFjet_pt = new vector<double>;
  VBFjet_eta = new vector<double>;
  VBFjet_phi = new vector<double>;
  VBFjet_energy = new vector<double>;
  VBFjet_score_qgl = new vector<double>;
  VBFjet_n_constituents = new vector<double>;
  nonVBFjet_pt = new vector<double>;
  nonVBFjet_eta = new vector<double>;
  nonVBFjet_phi = new vector<double>;
  nonVBFjet_energy = new vector<double>;
  nonVBFjet_score_qgl = new vector<double>;
  nonVBFjet_n_constituents = new vector<double>;
}
