#include "LEAF/VBFTagger/include/GenParticlesHists.h"

using namespace std;

GenParticlesHists::GenParticlesHists(TString dir_, TString selection_, bool do_stablegenparticles_) : BaseHists(dir_), selection(selection_), do_stablegenparticles(do_stablegenparticles_) {

  for ( const ParticleID& id : gen_ids ) { gen_ids_names.push_back(pdgId2str(id));}

  size_t n_pdgids = gen_ids_names.size();
  size_t n_flags = gen_flags_names.size();

  book<TH1F>("sumweights",        ";sum of event weights; Events / bin",  1,       0.5,     1.5);
  book<TH1F>("number_genparts",   ";number of gen part.; Events / bin", 300,       0.,    300);

  book<TH1F>("gen_MET",           ";genMET; Events / bin",              100,       0.,   1000);
  book<TH1F>("gen_HT",            ";genHT; Events / bin",               100,       0.,   1000);

  book<TH1F>("gen_part_pt",       ";p_{T}; Events / bin",               100,       0.,    500);
  book<TH1F>("gen_part_eta",      ";#eta; Events / bin",                100,      -5.,      5.);
  book<TH1F>("gen_part_phi",      ";#phi; Events / bin",                 70,      -3.5,     3.5);
  book<TH1F>("gen_part_m",        ";mass; Events / bin",                 50,       0.,      2);
  book<TH1F>("gen_part_e",        ";Energy; Events / bin",               50,       0.,   1500);
  book<TH1F>("gen_part_charge",   ";charge; Events / bin",                3,      -1.5,     1.5);

  book<TH1F>("gen_part_pdgid",  ";pdgid; Events / bin",                   n_pdgids, 0, n_pdgids);
  book<TH1F>("gen_part_statusFlag", ";status flag; Events / bin",         n_flags, 0, n_flags);
  book<TH2F>("gen_part_pdgid_vs_statusFlag", ";pdgid; status flag", n_pdgids, 0, n_pdgids, n_flags, 0, n_flags);

  for(size_t i=1; i<=n_pdgids; i++) {
    hist<TH1F>("gen_part_pdgid")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
  }

  for(size_t i=1; i<=n_flags; i++) {
    hist<TH1F>("gen_part_statusFlag")->GetXaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetYaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
  }


  book<TH1F>("gen_H_pt",          ";p_{T}^{H}; Events / bin",           200,       0.,    200);
  book<TH1F>("gen_Z_pt",          ";p_{T}^{Z}; Events / bin",           200,       0.,    200);
  book<TH1F>("gen_lep_pt",        ";p_{T}^{lep}; Events / bin",         200,       0.,    200);
  book<TH1F>("gen_H_eta",         ";#eta^{H}; Events / bin",            100,      -5.,      5.);
  book<TH1F>("gen_Z_eta",         ";#eta^{Z}; Events / bin",            100,      -5.,      5.);
  book<TH1F>("gen_lep_eta",       ";#eta^{lep}; Events / bin",          100,      -5.,      5.);
  book<TH1F>("gen_H_m",           ";mass^{H}; Events / bin",            150,       0.,    150);
  book<TH1F>("gen_Z_m",           ";mass^{Z}; Events / bin",            150,       0.,    150);
  book<TH2F>("gen_H_ptvseta",     ";p_{T}^{H}; #eta^{H}",               200,       0.,    200,   100,      -5.,      5.);
  book<TH2F>("gen_Z_ptvseta",     ";p_{T}^{Z}; #eta^{Z}",               200,       0.,    200,   100,      -5.,      5.);
  book<TH2F>("gen_lep_ptvseta",   ";p_{T}^{lep}; #eta^{Z}",             200,       0.,    200,   100,      -5.,      5.);
  book<TH2F>("gen_H_ptvsmass",    ";p_{T}^{H}; mass^{H}",               200,       0.,    200,   150,       0.,    150);
  book<TH2F>("gen_Z_ptvsmass",    ";p_{T}^{Z}; mass^{Z}",               200,       0.,    200,   150,       0.,    150);
  book<TH2F>("gen_Z1ptvsZ2pt",    ";p_{T}_{T}^{Z1}; p_{T}_{T}^{Z2}",    200,       0.,    200,   200,       0.,    200);
  book<TH2F>("gen_Z1mvsZ2m",      ";mass_{T}^{Z1}; mass_{T}^{Z2}",      150,       0.,    150,   150,       0.,    150);

}

void GenParticlesHists::fill(const VBFTaggerEvent & event){
  if(event.is_data) return;
  if (do_stablegenparticles) genparticles = event.genparticles_stable;
  else genparticles = event.genparticles_pruned;

  
  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);
  hist<TH1F>("number_genparts")->Fill(genparticles->size(), weight);

  TLorentzVector gen_MET;
  float gen_HT = 0;

  for(const GenParticle& gp: *genparticles){

    if (FindInString("pt>1",   selection.Data()) && gp.pt()<1) continue;
    if (FindInString("pt>0.2", selection.Data()) && gp.pt()<0.2) continue;

    gen_MET += gp.p4();
    gen_HT += gp.pt();

    string pdgid = pdgId2str(fabs(gp.pdgid()));

    hist<TH1F>("gen_part_pt")->Fill(gp.pt(), weight);
    hist<TH1F>("gen_part_eta")->Fill(gp.eta(), weight);
    hist<TH1F>("gen_part_phi")->Fill(gp.phi(), weight);
    hist<TH1F>("gen_part_m")->Fill(gp.m(), weight);
    hist<TH1F>("gen_part_e")->Fill(gp.e(), weight);
    hist<TH1F>("gen_part_charge")->Fill(gp.charge(), weight);

    hist<TH1F>("gen_part_pdgid")->Fill(pdgid.c_str(), weight);
    for ( const auto& flag : gen_flags_names ) {
      bool fill = false;
      if (flag == "isHardProcess") fill = gp.isHardProcess();
      if (flag == "fromHardProcess") fill = gp.fromHardProcess();
      if (flag == "fromHardProcessBeforeFSR") fill = gp.fromHardProcessBeforeFSR();
      if (flag == "isPrompt") fill = gp.isPrompt();
      if (flag == "isPromptFinalState") fill = gp.isPromptFinalState();
      if (flag == "isPromptDecayed") fill = gp.isPromptDecayed();
      if (flag == "isDecayedLeptonHadron") fill = gp.isDecayedLeptonHadron();
      if (flag == "isDirectHadronDecayProduct") fill = gp.isDirectHadronDecayProduct();
      if (flag == "fromHardProcessFinalState") fill = gp.fromHardProcessFinalState();
      if (flag == "fromHardProcessDecayed") fill = gp.fromHardProcessDecayed();

      if (fill) {
        hist<TH1F>("gen_part_statusFlag")->Fill(flag.c_str(), weight);
        hist<TH2F>("gen_part_pdgid_vs_statusFlag")->Fill(pdgid.c_str(), flag.c_str(), weight);
      }
    }
  }

  for (const auto &gp: *(event.gen_higgs)) {
    hist<TH1F>("gen_H_pt")->Fill(gp.pt(), weight);
    hist<TH1F>("gen_H_eta")->Fill(gp.eta(), weight);
    hist<TH1F>("gen_H_m")->Fill(gp.m(), weight);
    hist<TH2F>("gen_H_ptvseta")->Fill(gp.pt(), gp.eta(), weight);
    hist<TH2F>("gen_H_ptvsmass")->Fill(gp.pt(), gp.m(), weight);
  }
  for (const auto &gp: *(event.gen_higgs_Z)) {
    hist<TH1F>("gen_Z_pt")->Fill(gp.pt(), weight);
    hist<TH1F>("gen_Z_eta")->Fill(gp.eta(), weight);
    hist<TH1F>("gen_Z_m")->Fill(gp.m(), weight);
    hist<TH2F>("gen_Z_ptvseta")->Fill(gp.pt(), gp.eta(), weight);
    hist<TH2F>("gen_Z_ptvsmass")->Fill(gp.pt(), gp.m(), weight);
  }
  for (const auto &gp: *(event.gen_higgs_leptons)) {
    hist<TH1F>("gen_lep_pt")->Fill(gp.pt(), weight);
    hist<TH1F>("gen_lep_eta")->Fill(gp.eta(), weight);
    hist<TH2F>("gen_lep_ptvseta")->Fill(gp.pt(), gp.eta(), weight);
  }

  if ((*event.gen_higgs_Z).size()>=2){
    GenParticle z1 = (*event.gen_higgs_Z).at(0);
    GenParticle z2 = (*event.gen_higgs_Z).at(1);
    hist<TH2F>("gen_Z1ptvsZ2pt")->Fill(z1.pt(), z2.pt(), weight);
    hist<TH2F>("gen_Z1mvsZ2m")->Fill(z1.m(), z2.m(), weight);
  }

  hist<TH1F>("gen_MET")->Fill(gen_MET.Pt(), weight);
  hist<TH1F>("gen_HT")->Fill(gen_HT, weight);

}
