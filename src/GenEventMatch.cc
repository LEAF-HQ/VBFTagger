#include "LEAF/VBFTagger/include/GenEventMatch.h"

using namespace std;

int PdgIDToCharge(int pdgid){
  if (abs(pdgid)==(int)ParticleID::u || abs(pdgid)==(int)ParticleID::c) return (pdgid>0)? 2:-2;
  else return (pdgid>0)? -1:1;
}

bool isFromHardProcess(const GenParticle& p){
  return (p.isHardProcess() || p.fromHardProcess() || p.fromHardProcessBeforeFSR()) ;
}

bool XOR_pairs(Decay input1, Decay input2, Decay reference1, Decay reference2) {
  if (input1 == reference1 && input2 == reference2) return true;
  if (input1 == reference2 && input2 == reference1) return true;
  return false;
}

GenEventMatch::GenEventMatch(const Config& cfg){
  skipMatching = !(cfg.dataset_type() == "MC" );
  skipMotherMatching = !FindInString("VBF",cfg.dataset_name().Data());
  gp_printer.reset(new GenParticlePrinter(cfg));
  gp_printer_stable.reset(new GenParticlePrinter(cfg,true));
  gp_status_printer.reset(new GenParticleStatusPrinter(cfg));
}


GenParticle GenEventMatch::FindParticle(VBFTaggerEvent& event, int identifier) {
  for(const auto & gp : *event.genparticles_pruned) {
    if (gp.identifier() == identifier) return gp;
  }
  return GenParticle();
}



GenParticle GenEventMatch::FindParticle(VBFTaggerEvent& event, ParticleID pdgID, GenParticle::StatusFlag status) {
  for(const auto & gp : *event.genparticles_pruned){
    if (gp.pdgid() == (int)pdgID && gp.get_statusflag(status)) return gp;
  }
  return GenParticle();
}


std::vector<GenParticle> GenEventMatch::FindMothers(VBFTaggerEvent& event, GenParticle particle) {

  // Find partons: needed later
  std::vector<GenParticle> partons;
  for(const auto & gp : *event.genparticles_pruned) {
    if (gp.pt() != 0) continue;
    if (!isFromHardProcess(gp)) continue;
    if (gp.identifier()>3) throw std::runtime_error("Selected wrong parton.");
    for(const auto & parton : *event.genparticles_pruned){
      if (!parton.isHardProcess() || !parton.fromHardProcess() || !parton.fromHardProcessBeforeFSR() ) continue;
      if (parton.mother_identifier()!=gp.mother_identifier()) continue;
      if (!isHadronic(parton.pdgid()) && parton.pdgid()!=21) continue;
      partons.push_back(parton);
    }
  }

  if (partons.size()!=2) throw std::runtime_error("Unexpected number of partons.");

  // Find mothers
  std::vector<GenParticle> mothers;
  for(const auto & gp : *event.genparticles_pruned) {
    if (!isFromHardProcess(gp)) continue;
    if (gp.identifier() == particle.identifier()) continue;
    bool to_skip = true;
    for(const auto & parton : partons) { if (gp.mother_identifier() == parton.identifier()) {to_skip = false; break;}}
    if (to_skip) continue;
    if (gp.pt() == 0) continue;
    // if (gp.pt() <= 1) continue;
    // if (gp.eta() > 6) continue;
    if (isHadronic(partons.at(0).pdgid()) && isHadronic(partons.at(1).pdgid()) && !isHadronic(gp.pdgid())) continue;
    mothers.push_back(gp);
  }

  // Clean mothers
  if (mothers.size()==3){
    int number_matched = 0; int matched_index = -1;
    vector<int> indices = {0,1,2};
    do {
      vector<int> charges; vector<float> etas;
      for (const auto &i: indices){
        charges.push_back(PdgIDToCharge(mothers.at(i).pdgid()));
        etas.push_back(mothers.at(i).eta());
      }
      if(charges.at(0)+charges.at(1)==3  && etas.at(0)*etas.at(2)<0 ) { matched_index = 1; number_matched += 1;}
      if(charges.at(0)+charges.at(1)==-3 && etas.at(0)*etas.at(2)<0 ) { matched_index = 1; number_matched += 1;}
    } while(next_permutation(indices.begin(),indices.end()));
    if (number_matched==1) mothers.erase(mothers.begin()+matched_index);
  }

  if (mothers.size()>3){
    std::vector<string> mothers_names, mothers_ids;
    for (const auto &m: mothers) {
      mothers_names.push_back(pdgId2str(m.pdgid()));
      mothers_ids.push_back(to_string(m.identifier()));
    }
    cout << "Found 4 mothers " << mothers_names << " " << mothers_ids << endl;
    throw std::runtime_error("Unexpected number of mothers: more than 3 was never tested.");
  }

  if (mothers.size()<2) throw std::runtime_error("Unexpected number of mothers.");
  return mothers;
}

std::vector<GenParticle> GenEventMatch::FindDaughters(VBFTaggerEvent& event, GenParticle particle, bool check_PhaseSpace) {
  std::vector<GenParticle> daughters;
  for(const auto & gp : *event.genparticles_pruned){
    if (gp.mother_identifier()==particle.identifier()){
      if (check_PhaseSpace && gp.pt()<2) continue;
      if (check_PhaseSpace && fabs(gp.eta())>3) continue;
      daughters.push_back(gp);
    }
  }
  return daughters;
}

GenParticle GenEventMatch::FindMother(VBFTaggerEvent& event, int mother_id){
  int mother_index = -1;
  for(size_t i=0; i<event.genparticles_pruned->size(); i++){
    if(event.genparticles_pruned->at(i).identifier() == mother_id){
      mother_index = i; break;
    }
  }
  return event.genparticles_pruned->at(mother_index);
}

bool GenEventMatch::isHiggsDecay(VBFTaggerEvent& event, const GenParticle& particle) {
  int mother_id = particle.pruned_mother_identifier();

  if (mother_id<=1) return false;

  vector<int> higgs_chain = {};
  for (const auto& p: *event.gen_higgs) higgs_chain.push_back(p.identifier());
  for (const auto& p: *event.gen_higgs_Z) higgs_chain.push_back(p.identifier());
  for (const auto& p: *event.gen_higgs_leptons) higgs_chain.push_back(p.identifier());

  if (FindInVector(higgs_chain, mother_id)>=0) return true;
  return isHiggsDecay(event, FindMother(event, mother_id));
}

void GenEventMatch::ClearGenParticles(VBFTaggerEvent& event){
  for (const GenParticle &p: *event.genparticles_stable) {
    if (isHiggsDecay(event, p)) event.gen_higgs_decays->push_back(p);
    else event.gen_non_higgs_decays->push_back(p);
  }

  sort_by_pt<GenParticle>(*event.gen_higgs_decays);
  sort_by_pt<GenParticle>(*event.gen_non_higgs_decays);
}


/*

# PPPPPPPPPPPPPPPPP   RRRRRRRRRRRRRRRRR        OOOOOOOOO             CCCCCCCCCCCCCEEEEEEEEEEEEEEEEEEEEEE   SSSSSSSSSSSSSSS    SSSSSSSSSSSSSSS
# P::::::::::::::::P  R::::::::::::::::R     OO:::::::::OO        CCC::::::::::::CE::::::::::::::::::::E SS:::::::::::::::S SS:::::::::::::::S
# P::::::PPPPPP:::::P R::::::RRRRRR:::::R  OO:::::::::::::OO    CC:::::::::::::::CE::::::::::::::::::::ES:::::SSSSSS::::::SS:::::SSSSSS::::::S
# PP:::::P     P:::::PRR:::::R     R:::::RO:::::::OOO:::::::O  C:::::CCCCCCCC::::CEE::::::EEEEEEEEE::::ES:::::S     SSSSSSSS:::::S     SSSSSSS
#   P::::P     P:::::P  R::::R     R:::::RO::::::O   O::::::O C:::::C       CCCCCC  E:::::E       EEEEEES:::::S            S:::::S
#   P::::P     P:::::P  R::::R     R:::::RO:::::O     O:::::OC:::::C                E:::::E             S:::::S            S:::::S
#   P::::PPPPPP:::::P   R::::RRRRRR:::::R O:::::O     O:::::OC:::::C                E::::::EEEEEEEEEE    S::::SSSS          S::::SSSS
#   P:::::::::::::PP    R:::::::::::::RR  O:::::O     O:::::OC:::::C                E:::::::::::::::E     SS::::::SSSSS      SS::::::SSSSS
#   P::::PPPPPPPPP      R::::RRRRRR:::::R O:::::O     O:::::OC:::::C                E:::::::::::::::E       SSS::::::::SS      SSS::::::::SS
#   P::::P              R::::R     R:::::RO:::::O     O:::::OC:::::C                E::::::EEEEEEEEEE          SSSSSS::::S        SSSSSS::::S
#   P::::P              R::::R     R:::::RO:::::O     O:::::OC:::::C                E:::::E                         S:::::S            S:::::S
#   P::::P              R::::R     R:::::RO::::::O   O::::::O C:::::C       CCCCCC  E:::::E       EEEEEE            S:::::S            S:::::S
# PP::::::PP          RR:::::R     R:::::RO:::::::OOO:::::::O  C:::::CCCCCCCC::::CEE::::::EEEEEEEE:::::ESSSSSSS     S:::::SSSSSSSS     S:::::S
# P::::::::P          R::::::R     R:::::R OO:::::::::::::OO    CC:::::::::::::::CE::::::::::::::::::::ES::::::SSSSSS:::::SS::::::SSSSSS:::::S
# P::::::::P          R::::::R     R:::::R   OO:::::::::OO        CCC::::::::::::CE::::::::::::::::::::ES:::::::::::::::SS S:::::::::::::::SS
# PPPPPPPPPP          RRRRRRRR     RRRRRRR     OOOOOOOOO             CCCCCCCCCCCCCEEEEEEEEEEEEEEEEEEEEEE SSSSSSSSSSSSSSS    SSSSSSSSSSSSSSS
*/


// DoMotherMatching
void GenEventMatch::DoDecayMatching(VBFTaggerEvent& event){

  event.gen_higgs->push_back(FindParticle(event, ParticleID::H, GenParticle::StatusFlag::isFirstCopy));
  event.gen_higgs->push_back(FindParticle(event, ParticleID::H, GenParticle::StatusFlag::isLastCopy));

  for (const auto &dau: FindDaughters(event, (*event.gen_higgs).at(1), false)) {
    event.gen_higgs_Z->push_back(dau);
    for (const auto &dd: FindDaughters(event, dau, false)) {
      event.gen_higgs_leptons->push_back(dd);
    }
  }

  if ((*event.gen_higgs_Z).size()!=2) throw std::runtime_error("Unexpected number of Higgs daughters.");
  if ((*event.gen_higgs_leptons).size()!=4) throw std::runtime_error("Unexpected number of Higgs sub-daughters.");

  ClearGenParticles(event);
  Decay H_decay_0 = GetDecayMode((*event.gen_higgs_Z).at(0).pdgid(),(*event.gen_higgs_Z).at(1).pdgid());
  Decay H_decay_1 = GetDecayMode((*event.gen_higgs_leptons).at(0).pdgid(),(*event.gen_higgs_leptons).at(1).pdgid());
  Decay H_decay_2 = GetDecayMode((*event.gen_higgs_leptons).at(2).pdgid(),(*event.gen_higgs_leptons).at(3).pdgid());
  event.set_gen_higgs_decay(H_decay_0);

  if (H_decay_0 == Decay::ZZ) {
    if (XOR_pairs(H_decay_1, H_decay_2,      Decay::tautau, Decay::tautau)) event.set_gen_higgs_decay(Decay::ZZtautautautau);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::mumu,   Decay::mumu))   event.set_gen_higgs_decay(Decay::ZZmumumumu);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::ee,     Decay::ee))     event.set_gen_higgs_decay(Decay::ZZeeee);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::vv,     Decay::vv))     event.set_gen_higgs_decay(Decay::ZZvvvv);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::ee,     Decay::mumu))   event.set_gen_higgs_decay(Decay::ZZeemumu);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::ee,     Decay::tautau)) event.set_gen_higgs_decay(Decay::ZZeetautau);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::ee,     Decay::vv))     event.set_gen_higgs_decay(Decay::ZZeevv);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::mumu,   Decay::tautau)) event.set_gen_higgs_decay(Decay::ZZmumutautau);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::mumu,   Decay::vv))     event.set_gen_higgs_decay(Decay::ZZmumuvv);
    else if (XOR_pairs(H_decay_1, H_decay_2, Decay::tautau, Decay::vv))     event.set_gen_higgs_decay(Decay::ZZtautauvv);
    else throw runtime_error("Unexpected HZZ decay mode.");
  } else throw runtime_error("Unexpected Higgs decay mode.");

}


bool GenEventMatch::process(VBFTaggerEvent& event) {
  if(event.is_data) return true;
  if(skipMatching) return true;
  // cout << blue << " New Event" << reset << endl;

  // gp_printer->process(event);
  // gp_printer_stable->process(event);
  // gp_status_printer->process(event);

  DoDecayMatching(event);
  return true;
  // if(skipMotherMatching) return true;

  std::vector<GenParticle> H_mothers_all = FindMothers(event, (*event.gen_higgs).at(0));
  std::vector<GenParticle> H_mothers;
  // std::vector<bool> VBF_jets_to_use((*event.genjets).size(), false);

  for(unsigned m_index = 0; m_index < H_mothers_all.size(); m_index++ ){
    auto m = H_mothers_all.at(m_index);
    if (!isHadronic(m.pdgid())) continue;
    float dr_min =100;  float deta_dr_min = 100; int jet_index = -1;
    for(unsigned j_index = 0; j_index < (*event.genjets).size(); j_index++ ) {
      // if (VBF_jets_to_use.at(j_index)) continue;
      GenJet j = (*event.genjets).at(j_index);
      float dr = deltaR(j,m);
      if (dr<dr_min){ jet_index = j_index; dr_min = dr; deta_dr_min = deltaEta(j,m);}
      if (dr_min<0.4) break;
    }
    if (dr_min<0.8 || (deta_dr_min < 0.2 && dr_min<1)) {
      // VBF_jets_to_use.at(jet_index) = true;
      H_mothers.push_back(m);
      event.VBF_genjets->push_back((*event.genjets).at(jet_index));
    }
    if ((*event.VBF_genjets).size()>2) {
      int to_remove = -1;
      for(unsigned index_j1 = 0; index_j1 < (*event.VBF_genjets).size(); index_j1++ ) {
        GenJet j1 = (*event.VBF_genjets).at(index_j1);
        for(unsigned index_j2 = 0; index_j2 < (*event.VBF_genjets).size(); index_j2++ ) {
          GenJet j2 = (*event.VBF_genjets).at(index_j2);
          if (deltaR(j1,j2)<0.4) to_remove = (j1.pt()<j2.pt())? index_j1 : index_j2;
          if (to_remove>=0) break;
        }
        if (to_remove>=0) break;
      }
      if (to_remove>=0) (*event.VBF_genjets).erase( (*event.VBF_genjets).begin() + to_remove );
    }
  }

  if ((*event.VBF_genjets).size()==1) {
    GenJet j0 = (*event.VBF_genjets).at(0);
    int index_to_add = -1; float dr_min = 100;
    for(unsigned j_index = 0; j_index < (*event.genjets).size(); j_index++ ) {
      GenJet j = (*event.genjets).at(j_index);
      if (j.pt()==j0.pt() && j.eta()==j0.eta() && j.phi()==j0.phi()) continue;
      for(unsigned jj_index = j_index+1; jj_index < (*event.genjets).size(); jj_index++ ) {
        GenJet jj = (*event.genjets).at(jj_index);
        if (jj.pt()==j0.pt() && jj.eta()==j0.eta() && jj.phi()==j0.phi()) continue;
        TLorentzVector jjj = j.p4() + jj.p4();
        bool is_matched = false;
        for(unsigned m_index = 0; m_index < H_mothers_all.size(); m_index++ ){
          float dR = jjj.DeltaR(H_mothers_all.at(m_index).p4());
          if (dR<dr_min && dR<0.4) {
            is_matched=true;
            dr_min = dR;
          }
        }
        if (is_matched) index_to_add = (j.pt()<jj.pt())? jj_index : j_index;
      }
    }
    if(index_to_add>=0) event.VBF_genjets->push_back((*event.genjets).at(index_to_add));
  }

  if ((*event.VBF_genjets).size()>2) throw std::runtime_error("Found more than 2 VBF genjets.");

  if (H_mothers.size()<2) { for(unsigned i = 0; i <= 2-H_mothers.size(); i++ ) {GenParticle m; H_mothers.push_back(m);}}


  event.set_identifier_VBFgenparticle1(H_mothers.at(0).identifier());
  event.set_identifier_VBFgenparticle2(H_mothers.at(1).identifier());


  return true;
}
