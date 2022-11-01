#include "LEAF/VBFTagger/include/VBFSelections.h"
#include "LEAF/VBFTagger/include/Utils.h"
#include <algorithm>

using namespace std;


GenParticleSelection::GenParticleSelection(const Config & cfg, ParticleID pdgid_, int nmin_, int nmax_) : pdgid(pdgid_), nmin(nmin_), nmax(nmax_){}

bool GenParticleSelection::passes(VBFTaggerEvent & event){
  int count = 0;
  for(const auto & p : *event.genparticles_pruned) {
    if (abs(p.pdgid()) == (int)pdgid) count++;
  }
  return(count >= nmin && (count <= nmax || nmax == -1));
  return true;
}


NoGenTauSelection::NoGenTauSelection(const Config & cfg) {
  genparticleselection.reset(new GenParticleSelection(cfg, ParticleID::tau, 0, 0));
}

bool NoGenTauSelection::passes(VBFTaggerEvent & event){

  if (event.gen_higgs_decay() == Decay::ZZtautautautau) return false;
  if (event.gen_higgs_decay() == Decay::ZZeetautau) return false;
  if (event.gen_higgs_decay() == Decay::ZZmumutautau) return false;
  if (event.gen_higgs_decay() == Decay::ZZtautauvv) return false;

  if(!genparticleselection->passes(event)) return false;

  return true;
}

GenLeptonPhaseSpaceSelection::GenLeptonPhaseSpaceSelection(const Config& cfg) {};

bool GenLeptonPhaseSpaceSelection::passes(VBFTaggerEvent& event) {

  if ((*event.gen_higgs_leptons).size()==0) return false;
  for (const auto &gp: *event.gen_higgs_leptons) {
    if (fabs(gp.eta())>2.5) return false;
    if (fabs(gp.pt())<3 && abs(gp.pdgid()) == (int)ParticleID::mu) return false;
    if (fabs(gp.pt())<5 && abs(gp.pdgid()) == (int)ParticleID::e) return false;
    if (1.44 < fabs(gp.eta()) && fabs(gp.eta())<1.57 && abs(gp.pdgid()) == (int)ParticleID::e) return false;
  }
  return true;
}



VBFJetDefinition::VBFJetDefinition(const Config& cfg, const float& min_jet_pt_): min_jet_pt(min_jet_pt_) {
}


bool VBFJetDefinition::process(VBFTaggerEvent& event) {

  int n_jets = event.jets_ak4chs->size();
  if (n_jets==0) {
    event.set_eventCategory(-3);
    event.set_n_nonVBF_jets(0);
    event.set_HT_nonVBF_jets(0);
    event.set_mjj(0);
    return true;
  } else if (n_jets==1) {
    const Jet jet = (*event.jets_ak4chs).at(0);
    event.set_eventCategory(-1);
    event.set_n_nonVBF_jets(0);
    event.set_HT_nonVBF_jets(jet.pt());
    event.VBF_jets->push_back(jet);
    event.set_mjj(jet.p4().M());
    return true;
  }

  // now there are events with at least 2 jets
  int n_central_jets = 0;
  bool isSet = false;
  for(const Jet& jet1: *event.jets_ak4chs){
    if (jet1.pt()<min_jet_pt) continue;
    for(const Jet& jet2: *event.jets_ak4chs){
      if (jet2.identifier() == jet1.identifier()) continue;
      if (jet2.pt()<min_jet_pt) continue;
      TLorentzVector jj = jet1.p4() + jet2.p4();
      if (jet2.eta()*jet1.eta()>0) continue;
      // if (deltaEta(jet1,jet2)<1.4) continue;
      if (jj.M()<200) continue;
      event.VBF_jets->push_back(jet1);
      event.VBF_jets->push_back(jet2);
      event.set_mjj(jj.M());
      if (fabs(jet1.eta())<2.4) n_central_jets += 1;
      if (fabs(jet2.eta())<2.4) n_central_jets += 1;
      isSet=true;
      break;
    }
    if (isSet==true) break;
  }

  if (isSet) event.set_eventCategory(n_central_jets);
  else {
    event.set_eventCategory(-2);
    const Jet jet1 = (*event.jets_ak4chs).at(0);
    const Jet jet2 = (*event.jets_ak4chs).at(1);
    TLorentzVector jj = jet1.p4() + jet2.p4();
    event.VBF_jets->push_back(jet1);
    event.VBF_jets->push_back(jet2);
    event.set_mjj(jj.M());
  }

  float HT_nonVBF_jets = 0;
  for(const Jet& jet: *event.jets_ak4chs){
    if(event.VBF_jets->at(0).identifier() == jet.identifier()) continue;
    if(event.VBF_jets->at(1).identifier() == jet.identifier()) continue;
    event.non_VBF_jets->push_back(jet);
    HT_nonVBF_jets += jet.pt();
  }

  event.set_n_nonVBF_jets(event.non_VBF_jets->size());
  event.set_HT_nonVBF_jets(HT_nonVBF_jets);
  sort_by_pt<Jet>(*event.VBF_jets);
  sort_by_pt<Jet>(*event.non_VBF_jets);
  return true;

}


Higgs4LeptonsFinder::Higgs4LeptonsFinder(const Config& cfg) {};

bool Higgs4LeptonsFinder::process(VBFTaggerEvent& event) {
  vector<int>  lep_indices;
  vector<bool> lep_bool;

  for(size_t i=0; i<(*event.electrons).size(); i++){
    const Electron lep1 = (*event.electrons).at(i);
    for(size_t j=i+1; j<(*event.electrons).size(); j++){
      const Electron lep2 = (*event.electrons).at(j);
      if (lep1.charge()==lep2.charge()) continue;
      // TLorentzVector z1 = lep1.p4()+lep2.p4();
      // if (fabs(z1.M()-Z_mass_reco)>Z_width_reco && fabs(z1.M()-Z_mass_offshell_reco)>Z_width_offshell_reco ) continue;
      if ( std::find(lep_indices.begin(), lep_indices.end(), i) == lep_indices.end() ) {
        lep_indices.push_back(i);
        lep_bool.push_back(true);
      }
      if ( std::find(lep_indices.begin(), lep_indices.end(), j) == lep_indices.end() ) {
        lep_indices.push_back(j);
        lep_bool.push_back(true);
      }
      // cout << "checking electrons: " << lep1.charge() << " " << lep2.charge() << " "<< i << " " << j << " " << lep1.charge() << " " << lep2.charge() << " " << z1.M() <<endl;
    }
  }

  for(size_t i=0; i<(*event.muons).size(); i++){
    Muon lep1 = (*event.muons).at(i);
    for(size_t j=i+1; j<(*event.muons).size(); j++){
      const Muon lep2 = (*event.muons).at(j);
      if (lep1.charge()==lep2.charge()) continue;
      // TLorentzVector z1 = lep1.p4()+lep2.p4();
      // if (fabs(z1.M()-Z_mass_reco)>Z_width_reco && fabs(z1.M()-Z_mass_offshell_reco)>Z_width_offshell_reco ) continue;
      if ( std::find(lep_indices.begin(), lep_indices.end(), i) == lep_indices.end() || (std::find(lep_indices.begin(), lep_indices.end(), i) != lep_indices.end() && lep_bool.at(std::find(lep_indices.begin(), lep_indices.end(), i) - lep_indices.begin())) ) {
        lep_indices.push_back(i);
        lep_bool.push_back(false);
      }
      if ( std::find(lep_indices.begin(), lep_indices.end(), j) == lep_indices.end() || (std::find(lep_indices.begin(), lep_indices.end(), j) != lep_indices.end() && lep_bool.at(std::find(lep_indices.begin(), lep_indices.end(), j) - lep_indices.begin())) ) {
        lep_indices.push_back(j);
        lep_bool.push_back(false);
      }
    }
  }

  if (lep_indices.size()<4) return false;

  float min_chi2 = 1000;
  for(size_t i_1=0; i_1<lep_indices.size(); i_1++){
    int index_1 = lep_indices.at(i_1);
    FlavorParticle lep_1;
    bool is_ele_1 = lep_bool.at(i_1);
    if (is_ele_1) lep_1 = (*event.electrons).at(index_1);
    else lep_1 = (*event.muons).at(index_1);
    for(size_t i_2=i_1+1; i_2<lep_indices.size(); i_2++){
      bool is_ele_2 = lep_bool.at(i_2);
      if (is_ele_1!=is_ele_2) continue;
      int index_2 = lep_indices.at(i_2);
      FlavorParticle lep_2;
      if (is_ele_2) lep_2 = (*event.electrons).at(index_2);
      else lep_2 = (*event.muons).at(index_2);
      if (lep_1.charge()==lep_2.charge()) continue;
      for(size_t i_3=0; i_3<lep_indices.size(); i_3++){
        if (i_1==i_3 || i_2==i_3) continue;
        int index_3 = lep_indices.at(i_3);
        FlavorParticle lep_3;
        bool is_ele_3 = lep_bool.at(i_3);
        if (is_ele_3) lep_3 = (*event.electrons).at(index_3);
        else lep_3 = (*event.muons).at(index_3);
        for(size_t i_4=i_3+1; i_4<lep_indices.size(); i_4++){
          if (i_1==i_4 || i_2==i_4) continue;
          bool is_ele_4 = lep_bool.at(i_4);
          if (is_ele_3!=is_ele_4) continue;
          int index_4 = lep_indices.at(i_4);
          FlavorParticle lep_4;
          if (is_ele_4) lep_4 = (*event.electrons).at(index_4);
          else lep_4 = (*event.muons).at(index_4);
          if (lep_3.charge()==lep_4.charge()) continue;
          TLorentzVector h = lep_1.p4()+lep_2.p4()+lep_3.p4()+lep_4.p4();
          TLorentzVector z1 = lep_1.p4()+lep_2.p4();
          TLorentzVector z2 = lep_3.p4()+lep_4.p4();
          float chi2_z1 = fabs(z1.M()-Z_mass_reco)/Z_width_reco;
          float chi2_z2 = fabs(z2.M()-Z_mass_offshell_reco)/Z_width_offshell_reco;
          float chi2_h  = fabs(h.M()-H_mass_reco)/H_width_reco;
          // if (chi2_z1>1) continue;
          // if (chi2_z2>1) continue;
          if (chi2_h>1) continue;
          float chi2 = chi2_z1+chi2_z2+chi2_h;
          if (chi2< min_chi2) {
            min_chi2 = chi2;
            event.set_Z1_chi2(chi2_z1);
            event.set_Z2_chi2(chi2_z2);
            event.set_H_chi2(chi2_h);
            event.set_HZZ_chi2(chi2);
            event.H_leptons->clear();
            event.H_electrons->clear();
            event.H_muons->clear();
            event.reco_Z_bosons->clear();
            event.reco_H_bosons->clear();
            event.reco_H_bosons->push_back(h);
            event.reco_Z_bosons->push_back(z1);
            event.reco_Z_bosons->push_back(z2);
            event.H_leptons->push_back(lep_1);
            event.H_leptons->push_back(lep_2);
            event.H_leptons->push_back(lep_3);
            event.H_leptons->push_back(lep_4);
            if(is_ele_1) event.H_electrons->push_back((*event.electrons).at(index_1));
            else event.H_muons->push_back((*event.muons).at(index_1));
            if(is_ele_2) event.H_electrons->push_back((*event.electrons).at(index_2));
            else event.H_muons->push_back((*event.muons).at(index_2));
            if(is_ele_3) event.H_electrons->push_back((*event.electrons).at(index_3));
            else event.H_muons->push_back((*event.muons).at(index_3));
            if(is_ele_4) event.H_electrons->push_back((*event.electrons).at(index_4));
            else event.H_muons->push_back((*event.muons).at(index_4));
          }
        }
      }
    }
  }
  sort_by_pt<Electron>(*event.H_electrons);
  sort_by_pt<Muon>(*event.H_muons);
  sort_by_pt<FlavorParticle>(*event.H_leptons);

  if (event.H_leptons->size()!=4) return false;
  return true;

}


PFUESelector::PFUESelector(const Config& cfg) {};

bool PFUESelector::process(VBFTaggerEvent& event) {

  float Zeppenfeld_charged = 0;
  float Zeppenfeld_neutral = 0;
  float n_UEin_charged = 0;
  float n_UEin_neutral = 0;
  float n_UEout_charged = 0;
  float n_UEout_neutral = 0;
  Jet jet1; Jet jet2;
  float eta_min = 0; float eta_max = 0; float eta_avg = 0;
  float dEta_jets = 1;

  if (event.VBF_jets->size()>0) {
    jet1 = event.VBF_jets->at(0);
    eta_min = jet1.eta();
    eta_max = jet1.eta();
    eta_avg = jet1.eta();
    dEta_jets = 1;
  }
  if (event.VBF_jets->size()>1) {
    jet2 = event.VBF_jets->at(1);
    eta_min = std::min(jet1.eta(), jet2.eta());
    eta_max = std::max(jet1.eta(), jet2.eta());
    eta_avg = (eta_min+eta_max)/2;
    dEta_jets = deltaEta(jet1, jet2);
  }

  vector<PFCandidate> PF_VBF_1;
  vector<PFCandidate> PF_VBF_2;
  for(const PFCandidate& cand: *event.pfcands){
    if (cand.fromPV()!=3) continue;
    bool is_within;
    if (eta_min+0.4 < cand.eta() && cand.eta() < eta_max-0.4) is_within = true;
    else if (eta_min-0.4 > cand.eta() || cand.eta() > eta_max+0.4) is_within = false;
    else is_within = false;

    auto closest_lep = closestParticle(cand, *event.H_leptons);
    if (closest_lep != nullptr && deltaR(cand, *closest_lep)<0.4 && (FindInVector<int>({11,13,22}, fabs(cand.type()))>=0)) {
      event.PF_Higgs->push_back(cand);
    } else if (deltaR(cand, jet1)<0.4 || ((event.VBF_jets->size()>1)? deltaR(cand, jet2)<0.4 :0)) {
      if (deltaR(cand, jet1)<0.4) PF_VBF_1.push_back(cand);
      else PF_VBF_2.push_back(cand);
    } else {
      if (cand.charge()==0) {
        float cand_pt = cand.pt();
        int cand_id = fabs(cand.type());
        if (cand_id == 22 && cand_pt<1) continue;
        if ((cand_id==0 || cand_id==1 ||cand_id==2 ||cand_id==130) && cand_pt<3) continue;
        if (cand_id==11 || cand_id==13 || cand_id==211) throw std::runtime_error("Neutral PF identified as e/mu/ch: "+to_string(cand_id));
        event.PF_UE_neutral->push_back(cand);
        Zeppenfeld_neutral += fabs(cand.eta()-eta_avg)/dEta_jets;
        if (is_within) n_UEin_neutral += 1;
        else n_UEout_neutral += 1;
      } else {
        event.PF_UE_charged->push_back(cand);
        Zeppenfeld_charged += fabs(cand.eta()-eta_avg)/dEta_jets;
        if (is_within) n_UEin_charged += 1;
        else n_UEout_charged += 1;
      }
    }
  }

  sort_by_pt<PFCandidate>(PF_VBF_1);
  sort_by_pt<PFCandidate>(PF_VBF_2);
  sort_by_pt<PFCandidate>(*event.PF_Higgs);
  sort_by_eta<PFCandidate>(*event.PF_UE_neutral);
  sort_by_eta<PFCandidate>(*event.PF_UE_charged);


  PFCandidate dummy_PF; dummy_PF.set_pt(0); dummy_PF.set_eta(0); dummy_PF.set_phi(0); dummy_PF.set_m(0);

  int max_n_PF_per_jet = 30;
  int count = 0;
  for(const PFCandidate& cand: PF_VBF_1) {
    if (count>=max_n_PF_per_jet) break;
    event.PF_VBF->push_back(cand);
    count++;
  }
  while (count < max_n_PF_per_jet) {event.PF_VBF->push_back(dummy_PF);count++;}
  count = 0;
  for(const PFCandidate& cand: PF_VBF_2) {
    if (count>=max_n_PF_per_jet) break;
    event.PF_VBF->push_back(cand);
    count++;
  }
  while (count < max_n_PF_per_jet) {event.PF_VBF->push_back(dummy_PF);count++;}


  event.set_n_PF_jet1(PF_VBF_1.size());
  event.set_n_PF_jet2(PF_VBF_2.size());
  event.set_n_PF_VBF_charged(event.PF_UE_neutral->size());
  event.set_n_PF_VBF_neutral(event.PF_UE_charged->size());
  event.set_PF_Higgs_size(event.PF_Higgs->size());
  event.set_PF_VBF_size(event.PF_VBF->size());
  event.set_PF_UE_neutral_size(event.PF_UE_neutral->size());
  event.set_PF_UE_charged_size(event.PF_UE_charged->size());



  for(const Jet& jet: *event.VBF_jets){
    event.VBFjet_pt->push_back(jet.pt());
    event.VBFjet_eta->push_back(jet.eta());
    event.VBFjet_phi->push_back(jet.phi());
    event.VBFjet_energy->push_back(jet.e());
    event.VBFjet_score_qgl->push_back(jet.score_qgl());
    event.VBFjet_n_constituents->push_back(jet.n_constituents());
  }

  for(const Jet& jet: *event.non_VBF_jets){
    event.nonVBFjet_pt->push_back(jet.pt());
    event.nonVBFjet_eta->push_back(jet.eta());
    event.nonVBFjet_phi->push_back(jet.phi());
    event.nonVBFjet_energy->push_back(jet.e());
    event.nonVBFjet_score_qgl->push_back(jet.score_qgl());
    event.nonVBFjet_n_constituents->push_back(jet.n_constituents());
  }

  for(const PFCandidate& cand: PF_VBF_1){
    event.PF_VBF1_pt->push_back(cand.pt());
    event.PF_VBF1_eta->push_back(cand.eta());
    event.PF_VBF1_phi->push_back(cand.phi());
    event.PF_VBF1_energy->push_back(cand.e());
    event.PF_VBF1_pdgid->push_back(cand.pdgid());
    event.PF_VBF1_charge->push_back(cand.charge());
    event.PF_VBF1_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: PF_VBF_2){
    event.PF_VBF2_pt->push_back(cand.pt());
    event.PF_VBF2_eta->push_back(cand.eta());
    event.PF_VBF2_phi->push_back(cand.phi());
    event.PF_VBF2_energy->push_back(cand.e());
    event.PF_VBF2_pdgid->push_back(cand.pdgid());
    event.PF_VBF2_charge->push_back(cand.charge());
    event.PF_VBF2_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: *event.PF_UE_neutral){
    event.PF_UE_neutral_pt->push_back(cand.pt());
    event.PF_UE_neutral_eta->push_back(cand.eta());
    event.PF_UE_neutral_phi->push_back(cand.phi());
    event.PF_UE_neutral_energy->push_back(cand.e());
    event.PF_UE_neutral_pdgid->push_back(cand.pdgid());
    event.PF_UE_neutral_charge->push_back(cand.charge());
    event.PF_UE_neutral_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: *event.PF_UE_charged){
    event.PF_UE_charged_pt->push_back(cand.pt());
    event.PF_UE_charged_eta->push_back(cand.eta());
    event.PF_UE_charged_phi->push_back(cand.phi());
    event.PF_UE_charged_energy->push_back(cand.e());
    event.PF_UE_charged_pdgid->push_back(cand.pdgid());
    event.PF_UE_charged_charge->push_back(cand.charge());
    event.PF_UE_charged_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: *event.PF_UE_charged){
    event.PF_UE_pt->push_back(cand.pt());
    event.PF_UE_eta->push_back(cand.eta());
    event.PF_UE_phi->push_back(cand.phi());
    event.PF_UE_energy->push_back(cand.e());
    event.PF_UE_pdgid->push_back(cand.pdgid());
    event.PF_UE_charge->push_back(cand.charge());
    event.PF_UE_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: *event.PF_UE_neutral){
    event.PF_UE_pt->push_back(cand.pt());
    event.PF_UE_eta->push_back(cand.eta());
    event.PF_UE_phi->push_back(cand.phi());
    event.PF_UE_energy->push_back(cand.e());
    event.PF_UE_pdgid->push_back(cand.pdgid());
    event.PF_UE_charge->push_back(cand.charge());
    event.PF_UE_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: PF_VBF_1){
    event.PF_VBF_pt->push_back(cand.pt());
    event.PF_VBF_eta->push_back(cand.eta());
    event.PF_VBF_phi->push_back(cand.phi());
    event.PF_VBF_energy->push_back(cand.e());
    event.PF_VBF_pdgid->push_back(cand.pdgid());
    event.PF_VBF_charge->push_back(cand.charge());
    event.PF_VBF_puppiweight->push_back(cand.puppiweight());
  }
  for(const PFCandidate& cand: PF_VBF_2){
    event.PF_VBF_pt->push_back(cand.pt());
    event.PF_VBF_eta->push_back(cand.eta());
    event.PF_VBF_phi->push_back(cand.phi());
    event.PF_VBF_energy->push_back(cand.e());
    event.PF_VBF_pdgid->push_back(cand.pdgid());
    event.PF_VBF_charge->push_back(cand.charge());
    event.PF_VBF_puppiweight->push_back(cand.puppiweight());
  }


  for(const PFCandidate& cand: *event.PF_UE_charged){
    event.PF_UE_VBF_pt->push_back(cand.pt());
    event.PF_UE_VBF_eta->push_back(cand.eta());
    event.PF_UE_VBF_phi->push_back(cand.phi());
    event.PF_UE_VBF_energy->push_back(cand.e());
    event.PF_UE_VBF_pdgid->push_back(cand.pdgid());
    event.PF_UE_VBF_charge->push_back(cand.charge());
    event.PF_UE_VBF_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: *event.PF_UE_neutral){
    event.PF_UE_VBF_pt->push_back(cand.pt());
    event.PF_UE_VBF_eta->push_back(cand.eta());
    event.PF_UE_VBF_phi->push_back(cand.phi());
    event.PF_UE_VBF_energy->push_back(cand.e());
    event.PF_UE_VBF_pdgid->push_back(cand.pdgid());
    event.PF_UE_VBF_charge->push_back(cand.charge());
    event.PF_UE_VBF_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: PF_VBF_1){
    event.PF_UE_VBF_pt->push_back(cand.pt());
    event.PF_UE_VBF_eta->push_back(cand.eta());
    event.PF_UE_VBF_phi->push_back(cand.phi());
    event.PF_UE_VBF_energy->push_back(cand.e());
    event.PF_UE_VBF_pdgid->push_back(cand.pdgid());
    event.PF_UE_VBF_charge->push_back(cand.charge());
    event.PF_UE_VBF_puppiweight->push_back(cand.puppiweight());
  }

  for(const PFCandidate& cand: PF_VBF_2){
    event.PF_UE_VBF_pt->push_back(cand.pt());
    event.PF_UE_VBF_eta->push_back(cand.eta());
    event.PF_UE_VBF_phi->push_back(cand.phi());
    event.PF_UE_VBF_energy->push_back(cand.e());
    event.PF_UE_VBF_pdgid->push_back(cand.pdgid());
    event.PF_UE_VBF_charge->push_back(cand.charge());
    event.PF_UE_VBF_puppiweight->push_back(cand.puppiweight());
  }



  event.set_Zeppenfeld(Zeppenfeld_charged+Zeppenfeld_neutral);
  event.set_Zeppenfeld_charged(Zeppenfeld_charged);
  event.set_Zeppenfeld_neutral(Zeppenfeld_neutral);
  event.set_energy_density_ratio(((n_UEout_charged+n_UEout_neutral)!=0)? (n_UEin_charged+n_UEin_neutral)/(n_UEout_charged+n_UEout_neutral) : 0);
  event.set_energy_density_ratio_charged((n_UEout_charged!=0)? n_UEin_charged/n_UEout_charged : 0);
  event.set_energy_density_ratio_neutral((n_UEout_neutral!=0)? n_UEin_neutral/n_UEout_neutral : 0);

  return true;

}
