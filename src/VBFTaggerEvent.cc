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

void VBFTaggerEvent::SetNewVectors(){
  gen_higgs = new vector<GenParticle>;
  gen_higgs_Z = new vector<GenParticle>;
  gen_higgs_leptons = new vector<GenParticle>;
  gen_higgs_decays = new vector<GenParticle>;
  gen_non_higgs_decays = new vector<GenParticle>;
  VBF_genjets = new vector<GenJet>;

  H_muons = new vector<Muon>;
  H_electrons = new vector<Electron>;
  H_leptons = new vector<FlavorParticle>;
  reco_Z_bosons = new vector<TLorentzVector>;
  reco_H_bosons = new vector<TLorentzVector>;
  VBF_jets = new vector<Jet>;
  non_VBF_jets = new vector<Jet>;

  PF_Higgs = new vector<PFCandidate>;
  PF_VBF = new vector<PFCandidate>;
  PF_UE_charged = new vector<PFCandidate>;
  PF_UE_neutral = new vector<PFCandidate>;

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

  PF_VBF1_pt = new vector<double>;
  PF_VBF1_eta = new vector<double>;
  PF_VBF1_phi = new vector<double>;
  PF_VBF1_energy = new vector<double>;
  PF_VBF1_pdgid = new vector<double>;
  PF_VBF1_charge = new vector<double>;
  PF_VBF1_puppiweight = new vector<double>;

  PF_VBF2_pt = new vector<double>;
  PF_VBF2_eta = new vector<double>;
  PF_VBF2_phi = new vector<double>;
  PF_VBF2_energy = new vector<double>;
  PF_VBF2_pdgid = new vector<double>;
  PF_VBF2_charge = new vector<double>;
  PF_VBF2_puppiweight = new vector<double>;

  PF_UE_charged_pt = new vector<double>;
  PF_UE_charged_eta = new vector<double>;
  PF_UE_charged_phi = new vector<double>;
  PF_UE_charged_energy = new vector<double>;
  PF_UE_charged_pdgid = new vector<double>;
  PF_UE_charged_charge = new vector<double>;
  PF_UE_charged_puppiweight = new vector<double>;

  PF_UE_neutral_pt = new vector<double>;
  PF_UE_neutral_eta = new vector<double>;
  PF_UE_neutral_phi = new vector<double>;
  PF_UE_neutral_energy = new vector<double>;
  PF_UE_neutral_pdgid = new vector<double>;
  PF_UE_neutral_charge = new vector<double>;
  PF_UE_neutral_puppiweight = new vector<double>;

  PF_UE_pt = new vector<double>;
  PF_UE_eta = new vector<double>;
  PF_UE_phi = new vector<double>;
  PF_UE_energy = new vector<double>;
  PF_UE_pdgid = new vector<double>;
  PF_UE_charge = new vector<double>;
  PF_UE_puppiweight = new vector<double>;

  PF_VBF_pt = new vector<double>;
  PF_VBF_eta = new vector<double>;
  PF_VBF_phi = new vector<double>;
  PF_VBF_energy = new vector<double>;
  PF_VBF_pdgid = new vector<double>;
  PF_VBF_charge = new vector<double>;
  PF_VBF_puppiweight = new vector<double>;

  PF_UE_VBF_pt = new vector<double>;
  PF_UE_VBF_eta = new vector<double>;
  PF_UE_VBF_phi = new vector<double>;
  PF_UE_VBF_energy = new vector<double>;
  PF_UE_VBF_pdgid = new vector<double>;
  PF_UE_VBF_charge = new vector<double>;
  PF_UE_VBF_puppiweight = new vector<double>;

  PF_UE_VBF_sorted_pt = new vector<double>;
  PF_UE_VBF_sorted_eta = new vector<double>;
  PF_UE_VBF_sorted_phi = new vector<double>;
  PF_UE_VBF_sorted_energy = new vector<double>;
  PF_UE_VBF_sorted_pdgid = new vector<double>;
  PF_UE_VBF_sorted_charge = new vector<double>;
  PF_UE_VBF_sorted_puppiweight = new vector<double>;

}


void VBFTaggerEvent::SetNewNonVectors(){
  m_identifier_VBFgenparticle1 = -1;
  m_identifier_VBFgenparticle2 = -1;
  m_gen_higgs_decay = Decay::nodecay;

  m_H_chi2 = -1;
  m_Z1_chi2 = -1;
  m_Z2_chi2 = -1;
  m_HZZ_chi2 = -1;

  m_PF_Higgs_size = -1;
  m_PF_VBF_size = -1;
  m_PF_UE_charged_size = -1;
  m_PF_UE_neutral_size = -1;

  m_is_VBF = -1;
  m_eventCategory = -1;
  m_n_PF_jet1 = -1;
  m_n_PF_jet2 = -1;
  m_n_PF_VBF_charged = -1;
  m_n_PF_VBF_neutral = -1;
  m_n_nonVBF_jets = -1;
  m_HT_nonVBF_jets = -1;
  m_mjj = -1;
  m_Zeppenfeld = -1;
  m_Zeppenfeld_charged = -1;
  m_Zeppenfeld_neutral = -1;
  m_energy_density_ratio = -1;
  m_energy_density_ratio_charged = -1;
  m_energy_density_ratio_neutral = -1;
}

void VBFTaggerEvent::DeleteVectorsVBFTaggerEvent(){
  delete gen_higgs;
  delete gen_higgs_Z;
  delete gen_higgs_leptons;
  delete gen_higgs_decays;
  delete gen_non_higgs_decays;
  delete VBF_genjets;
  delete H_muons;
  delete H_electrons;
  delete H_leptons;
  delete reco_Z_bosons;
  delete reco_H_bosons;
  delete VBF_jets;
  delete non_VBF_jets;
  delete PF_Higgs;
  delete PF_VBF;
  delete PF_UE_charged;
  delete PF_UE_neutral;
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
  delete PF_VBF1_pt;
  delete PF_VBF1_eta;
  delete PF_VBF1_phi;
  delete PF_VBF1_energy;
  delete PF_VBF1_pdgid;
  delete PF_VBF1_charge;
  delete PF_VBF1_puppiweight;
  delete PF_VBF2_pt;
  delete PF_VBF2_eta;
  delete PF_VBF2_phi;
  delete PF_VBF2_energy;
  delete PF_VBF2_pdgid;
  delete PF_VBF2_charge;
  delete PF_VBF2_puppiweight;
  delete PF_UE_charged_pt;
  delete PF_UE_charged_eta;
  delete PF_UE_charged_phi;
  delete PF_UE_charged_energy;
  delete PF_UE_charged_pdgid;
  delete PF_UE_charged_charge;
  delete PF_UE_charged_puppiweight;
  delete PF_UE_neutral_pt;
  delete PF_UE_neutral_eta;
  delete PF_UE_neutral_phi;
  delete PF_UE_neutral_energy;
  delete PF_UE_neutral_pdgid;
  delete PF_UE_neutral_charge;
  delete PF_UE_neutral_puppiweight;
  delete PF_UE_pt;
  delete PF_UE_eta;
  delete PF_UE_phi;
  delete PF_UE_energy;
  delete PF_UE_pdgid;
  delete PF_UE_charge;
  delete PF_UE_puppiweight;
  delete PF_VBF_pt;
  delete PF_VBF_eta;
  delete PF_VBF_phi;
  delete PF_VBF_energy;
  delete PF_VBF_pdgid;
  delete PF_VBF_charge;
  delete PF_VBF_puppiweight;
  delete PF_UE_VBF_pt;
  delete PF_UE_VBF_eta;
  delete PF_UE_VBF_phi;
  delete PF_UE_VBF_energy;
  delete PF_UE_VBF_pdgid;
  delete PF_UE_VBF_charge;
  delete PF_UE_VBF_puppiweight;
  delete PF_UE_VBF_sorted_pt;
  delete PF_UE_VBF_sorted_eta;
  delete PF_UE_VBF_sorted_phi;
  delete PF_UE_VBF_sorted_energy;
  delete PF_UE_VBF_sorted_pdgid;
  delete PF_UE_VBF_sorted_charge;
  delete PF_UE_VBF_sorted_puppiweight;
}

void VBFTaggerEvent::SetZeroVectorsVBFTaggerEvent(){
  gen_higgs = 0;
  gen_higgs_Z = 0;
  gen_higgs_leptons = 0;
  gen_higgs_decays = 0;
  gen_non_higgs_decays = 0;
  VBF_genjets = 0;
  H_muons = 0;
  H_electrons = 0;
  H_leptons = 0;
  reco_Z_bosons = 0;
  reco_H_bosons = 0;
  VBF_jets = 0;
  non_VBF_jets = 0;
  PF_Higgs = 0;
  PF_VBF = 0;
  PF_UE_charged = 0;
  PF_UE_neutral = 0;
  VBFjet_pt = 0;
  VBFjet_eta = 0;
  VBFjet_phi = 0;
  VBFjet_energy = 0;
  VBFjet_score_qgl = 0;
  VBFjet_n_constituents = 0;
  nonVBFjet_pt = 0;
  nonVBFjet_eta = 0;
  nonVBFjet_phi = 0;
  nonVBFjet_energy = 0;
  nonVBFjet_score_qgl = 0;
  nonVBFjet_n_constituents = 0;
  PF_VBF1_pt = 0;
  PF_VBF1_eta = 0;
  PF_VBF1_phi = 0;
  PF_VBF1_energy = 0;
  PF_VBF1_pdgid = 0;
  PF_VBF1_charge = 0;
  PF_VBF1_puppiweight = 0;
  PF_VBF2_pt = 0;
  PF_VBF2_eta = 0;
  PF_VBF2_phi = 0;
  PF_VBF2_energy = 0;
  PF_VBF2_pdgid = 0;
  PF_VBF2_charge = 0;
  PF_VBF2_puppiweight = 0;
  PF_UE_charged_pt = 0;
  PF_UE_charged_eta = 0;
  PF_UE_charged_phi = 0;
  PF_UE_charged_energy = 0;
  PF_UE_charged_pdgid = 0;
  PF_UE_charged_charge = 0;
  PF_UE_charged_puppiweight = 0;
  PF_UE_neutral_pt = 0;
  PF_UE_neutral_eta = 0;
  PF_UE_neutral_phi = 0;
  PF_UE_neutral_energy = 0;
  PF_UE_neutral_pdgid = 0;
  PF_UE_neutral_charge = 0;
  PF_UE_neutral_puppiweight = 0;
  PF_UE_pt = 0;
  PF_UE_eta = 0;
  PF_UE_phi = 0;
  PF_UE_energy = 0;
  PF_UE_pdgid = 0;
  PF_UE_charge = 0;
  PF_UE_puppiweight = 0;
  PF_VBF_pt = 0;
  PF_VBF_eta = 0;
  PF_VBF_phi = 0;
  PF_VBF_energy = 0;
  PF_VBF_pdgid = 0;
  PF_VBF_charge = 0;
  PF_VBF_puppiweight = 0;
  PF_UE_VBF_pt = 0;
  PF_UE_VBF_eta = 0;
  PF_UE_VBF_phi = 0;
  PF_UE_VBF_energy = 0;
  PF_UE_VBF_pdgid = 0;
  PF_UE_VBF_charge = 0;
  PF_UE_VBF_puppiweight = 0;
  PF_UE_VBF_sorted_pt = 0;
  PF_UE_VBF_sorted_eta = 0;
  PF_UE_VBF_sorted_phi = 0;
  PF_UE_VBF_sorted_energy = 0;
  PF_UE_VBF_sorted_pdgid = 0;
  PF_UE_VBF_sorted_charge = 0;
  PF_UE_VBF_sorted_puppiweight = 0;
}


VBFTaggerEvent::VBFTaggerEvent(){
  SetNewVectors();
  SetNewNonVectors();
}

VBFTaggerEvent::~VBFTaggerEvent(){
  DeleteVectorsVBFTaggerEvent();
}

void VBFTaggerEvent::clear(){
  RecoEvent::clear();
  DeleteVectorsVBFTaggerEvent();
  SetZeroVectorsVBFTaggerEvent();
  SetNewNonVectors();
}

void VBFTaggerEvent::reset(){
  RecoEvent::reset();
  DeleteVectorsVBFTaggerEvent();
  SetNewVectors();
  SetNewNonVectors();
}
