#include "LEAF/VBFTagger/include/LeptonEfficiencyHists.h"

using namespace std;

LeptonEfficiencyHists::LeptonEfficiencyHists(TString dir_) : BaseHists(dir_) {
  book<TH1F>("sumweights",        ";sum of event weights; Events / bin",  1,       0.5,     1.5);

  for (auto& lep : {ParticleID::e, ParticleID::mu}) {
    TString name = pdgId2str(lep);
    book<TH1F>("gen_"+name,              ";total N^{gen "+name+"}; Events / bin",     1,       0.5,     1.5);
    book<TH1F>("gen_"+name+"_pt",        ";p_{T}^{gen "+name+"}; Events / bin",     100,       0.,    500);
    book<TH1F>("gen_"+name+"_eta",       ";#eta^{gen "+name+"}; Events / bin",      100,      -5.,      5.);
    book<TH2F>("gen_"+name+"_pt_eta",    ";p_{T}^{gen "+name+"}; #eta^{gen #mu};",  100,       0.,    500,     100,      -5.,      5.);

    book<TH1F>("match_"+name,    ";total N^{matched gen "+name+"}; Events / bin",     1,       0.5,     1.5);
    book<TH1F>("match_"+name+"_pt",      ";p_{T}^{gen "+name+"}; Events / bin",     100,       0.,    500);
    book<TH1F>("match_"+name+"_eta",     ";#eta^{gen "+name+"}; Events / bin",      100,      -5.,      5.);
    book<TH2F>("match_"+name+"_pt_eta",  ";p_{T}^{gen "+name+"}; #eta^{gen #mu};",  100,       0.,    500,     100,      -5.,      5.);
  }
}

void LeptonEfficiencyHists::fill(const VBFTaggerEvent & event) {
  if(event.is_data) return;
  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);

  for (const auto &gp: *(event.gen_higgs_leptons)) {
    int pdgid = abs(gp.pdgid());
    TString name = pdgId2str(pdgid);
    hist<TH1F>("gen_"+name)->Fill(1, weight);
    hist<TH1F>("gen_"+name+"_pt")->Fill(gp.pt(), weight);
    hist<TH1F>("gen_"+name+"_eta")->Fill(gp.eta(), weight);
    hist<TH2F>("gen_"+name+"_pt_eta")->Fill(gp.pt(), gp.eta(), weight);

    float dr_min = -1.;

    if (pdgid == (int)ParticleID::e) {
      auto closest_lep = closestParticle(gp, *event.electrons);
      if (closest_lep != nullptr) dr_min = deltaR(gp, *closest_lep);
    }
    if (pdgid== (int)ParticleID::mu) {
      auto closest_lep = closestParticle(gp, *event.muons);
      if (closest_lep != nullptr) dr_min = deltaR(gp, *closest_lep);
    }

    if(dr_min < 0.2 && dr_min > 0.) {
      hist<TH1F>("match_"+name)->Fill(1, weight);
      hist<TH1F>("match_"+name+"_pt")->Fill(gp.pt(), weight);
      hist<TH1F>("match_"+name+"_eta")->Fill(gp.eta(), weight);
      hist<TH2F>("match_"+name+"_pt_eta")->Fill(gp.pt(), gp.eta(), weight);
    }
  }
}
