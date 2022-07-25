#include "LEAF/VBFTagger/include/VBFEventHists.h"

using namespace std;

VBFEventHists::VBFEventHists(TString dir_, TString selection_) : BaseHists(dir_), selection(selection_) {

  is_etaprod = FindInString("eta1*eta2<0", selection.Data());
  is_deta    = FindInString("deta>1.4", selection.Data());
  is_mjj     = FindInString("mjj>200", selection.Data());

  book<TH1F>("sumweights",        ";sum of event weights; Events / bin",  1,       0.5,     1.5);
  book<TH1F>("number_of_jets",    ";number of jets ; Events / bin",      11,      -0.5,    10.5);
  book<TH1F>("number_of_ele",     ";number of electrons ; Events / bin", 11,      -0.5,    10.5);
  book<TH1F>("number_of_muo",     ";number of muons ; Events / bin",     11,      -0.5,    10.5);
  book<TH1F>("number_of_lep",     ";number of leptons ; Events / bin",   11,      -0.5,    10.5);
  book<TH2F>("number_of_elevsmuo",";number of electrons; number of muons",5,      -0.5,     4.5,     5,      -0.5,    4.5);

  book<TH1F>("number_of_PF_Higgs", ";# of PF from Higgs; Events / bin", 101,      -0.5,   100);
  book<TH1F>("number_of_PF_VBF", ";# of PF from VBF-like jets; Events / bin", 101,-0.5,   100);
  book<TH1F>("number_of_PF_UE_charged", ";# of PF from UE (ch); Events / bin",101, -0.5,  100);
  book<TH1F>("number_of_PF_UE_neutrals", ";# of PF from UE (neu); Events / bin",101,-0.5, 100);

  for (const TString& name: {"H", "Z1", "Z2"}){
    book<TH1F>(name+"_pt",       ";#p_{T, "+name+"}; Events / bin",    100,      0.,    500);
    book<TH1F>(name+"_eta",      ";#eta_{"+name+"}; Events / bin",     100,     -5.0,     5.0);
    book<TH1F>(name+"_phi",      ";#phi_{"+name+"}; Events / bin",     100,     -4.0,     4.0);
    book<TH1F>(name+"_mass",     ";mass_{"+name+"}; Events / bin",     100,      0,     150.0);
    book<TH1F>(name+"_chi2",     ";chi2_{"+name+"}; Events / bin",     100,      0,      10.0);
  }
  book<TH2F>("Z1_vs_Z2_mass",    ";mass_{Z1}; mass_{Z2}; Events / bin",100,      0,     130.0,   100,      0,     130.0);

  book<TH1F>("HZZ_chi2",         ";chi2_{HZZ}; Events / bin",          100,      0,      10.0);

  max_index = 2;
  for (const TString& lep: {"jet", "ele", "muo", "lep"}){
    TString name;
    for(int i=1; i<=max_index; i++){
      name = lep+to_string(i);
      book<TH1F>(name+"_pt",       ";#p_{T, "+name+"}; Events / bin",    100,      0.,    500);
      book<TH1F>(name+"_eta",      ";#eta_{"+name+"}; Events / bin",     100,     -5.0,     5.0);
      book<TH1F>(name+"_phi",      ";#phi_{"+name+"}; Events / bin",     100,     -4.0,     4.0);
    }
    name = lep+"1vs"+lep+"2";
    book<TH2F>(name+"_pt",          ";#p_{T,"+lep+"1};#p_{T,"+lep+"2}",  50,      0.,    1000,     50,       0.,  1000);
    book<TH2F>(name+"_eta",         ";#eta_{"+lep+"1};#eta_{"+lep+"2}", 100,     -5.0,      5.0,  100,      -5.0,    5.0);
    book<TH2F>(name+"_eta_abs",     ";#eta_{"+lep+"1};#eta_{"+lep+"2}", 100,     -5.0,      5.0,  100,      -5.0,    5.0);
  }

  book<TH2F>("jet1_vs_jet2_eta_abs",";#eta_{jet1}; #eta_{jet2}",         100,     -0.0,     5.0,  100,      -0.0,    5.0);
  book<TH1F>("m_jj",                ";m(jj); Events / bin",              500,      0.,   1500);
  book<TH1F>("DR_jj",               ";#Delta R(jj); Events / bin",       160,      0,       8);
  book<TH1F>("Deta_jj",             ";#Delta#eta(jj); Events / bin",     160,      0,       8);

}

void VBFEventHists::fill(const VBFTaggerEvent & event){
  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);

  int njets = 0;
  double HT_jets = 0;

  int ele_size = (*event.H_electrons).size();
  int muo_size = (*event.H_muons).size();
  int lep_size = (*event.H_leptons).size();

  hist<TH1F>("number_of_ele")->Fill(ele_size, weight);
  hist<TH1F>("number_of_muo")->Fill(muo_size, weight);
  hist<TH1F>("number_of_lep")->Fill(lep_size, weight);
  hist<TH2F>("number_of_elevsmuo")->Fill(ele_size, muo_size, weight);

  hist<TH1F>("number_of_PF_Higgs")->Fill((float)event.PF_Higgs_size(), weight);
  hist<TH1F>("number_of_PF_VBF")->Fill((float)event.PF_VBF_size(), weight);
  hist<TH1F>("number_of_PF_UE_charged")->Fill((float)event.PF_UE_charged_size(), weight);
  hist<TH1F>("number_of_PF_UE_neutrals")->Fill((float)event.PF_UE_neutrals_size(), weight);

  for(unsigned int i=0; i<((*event.reco_Z_bosons).size()+(*event.reco_H_bosons).size()); i++){
    TLorentzVector boson;
    TString name;
    if (i<2) {
      boson = (*event.reco_Z_bosons).at(i);
      name = "Z"+to_string(i+1);
    } else {
      boson = (*event.reco_H_bosons).at(0);
      name = "H";
    }
    hist<TH1F>(name+"_pt")->Fill(boson.Pt(), weight);
    hist<TH1F>(name+"_eta")->Fill(boson.Eta(), weight);
    hist<TH1F>(name+"_phi")->Fill(boson.Phi(), weight);
    hist<TH1F>(name+"_mass")->Fill(boson.M(), weight);
  }

  hist<TH1F>("Z1_chi2")->Fill(event.Z1_chi2(), weight);
  hist<TH1F>("Z2_chi2")->Fill(event.Z2_chi2(), weight);
  hist<TH1F>("H_chi2")->Fill(event.H_chi2(), weight);
  hist<TH1F>("HZZ_chi2")->Fill(event.HZZ_chi2(), weight);

  if ((*event.reco_Z_bosons).size()>=2){
    hist<TH2F>("Z1_vs_Z2_mass")->Fill((*event.reco_Z_bosons).at(0).M(), (*event.reco_Z_bosons).at(1).M(), weight);
  }

  for(int i=0; i<ele_size; i++){
    if (i>=max_index) break;
    const Electron ele = (*event.H_electrons).at(i);
    hist<TH1F>("ele"+to_string(i+1)+"_pt")->Fill(ele.pt(), weight);
    hist<TH1F>("ele"+to_string(i+1)+"_eta")->Fill(ele.eta(), weight);
    hist<TH1F>("ele"+to_string(i+1)+"_phi")->Fill(ele.phi(), weight);
    for(int j=i+1; j<ele_size; j++){
      if (j>=max_index) break;
      const Electron ele2 = (*event.H_electrons).at(j);
      hist<TH2F>("ele1vsele2_pt")->Fill(ele.pt(), ele2.pt(), weight);
      hist<TH2F>("ele1vsele2_eta")->Fill(ele.eta(), ele2.eta(), weight);
      hist<TH2F>("ele1vsele2_eta_abs")->Fill(fabs(ele.eta()), fabs(ele2.eta()), weight);
    }
  }

  for(int i=0; i<muo_size; i++){
    if (i>=max_index) break;
    const Muon muo = (*event.H_muons).at(i);
    hist<TH1F>("muo"+to_string(i+1)+"_pt")->Fill(muo.pt(), weight);
    hist<TH1F>("muo"+to_string(i+1)+"_eta")->Fill(muo.eta(), weight);
    hist<TH1F>("muo"+to_string(i+1)+"_phi")->Fill(muo.phi(), weight);
    for(int j=i+1; j<muo_size; j++){
      if (j>=max_index) break;
      const Muon muo2 = (*event.H_muons).at(j);
      hist<TH2F>("muo1vsmuo2_pt")->Fill(muo.pt(), muo2.pt(), weight);
      hist<TH2F>("muo1vsmuo2_eta")->Fill(muo.eta(), muo2.eta(), weight);
      hist<TH2F>("muo1vsmuo2_eta_abs")->Fill(fabs(muo.eta()), fabs(muo2.eta()), weight);
    }
  }

  for(int i=0; i<lep_size; i++){
    if (i>=max_index) break;
    const FlavorParticle lep = (*event.H_leptons).at(i);
    hist<TH1F>("lep"+to_string(i+1)+"_pt")->Fill(lep.pt(), weight);
    hist<TH1F>("lep"+to_string(i+1)+"_eta")->Fill(lep.eta(), weight);
    hist<TH1F>("lep"+to_string(i+1)+"_phi")->Fill(lep.phi(), weight);
    for(int j=i+1; j<lep_size; j++){
      if (j>=max_index) break;
      const FlavorParticle lep2 = (*event.H_leptons).at(j);
      hist<TH2F>("lep1vslep2_pt")->Fill(lep.pt(), lep2.pt(), weight);
      hist<TH2F>("lep1vslep2_eta")->Fill(lep.eta(), lep2.eta(), weight);
      hist<TH2F>("lep1vslep2_eta_abs")->Fill(fabs(lep.eta()), fabs(lep2.eta()), weight);
    }
  }


  //
  // hist<TH1F>("number_of_jets")->Fill(njets, weight);
  // hist<TH1F>("HT_jets")->Fill(HT_jets, weight);

}
