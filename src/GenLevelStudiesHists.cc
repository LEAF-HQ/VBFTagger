#include "LEAF/VBFTagger/include/GenLevelStudiesHists.h"


using namespace std;

GenLevelStudiesHists::GenLevelStudiesHists(TString dir_, TString selection_): BaseHists(dir_), selection(selection_) {
  for (const ParticleID& id : gen_ids) {gen_ids_names.push_back(pdgId2str(id));}

  size_t n_pdgids = gen_ids_names.size();
  size_t n_flags = gen_flags_names.size();

// book all the histograms
  book<TH1F>("sumweights",                    ";sum of event weights; Events / bin",                                              1,  0.5, 1.5);

  // book all the jets histograms
  book<TH1F>("ngenjets",                      ";N_{genjets} w/ P_{t} > GeV; Events / bin",                                        21, -0.5, 20.5);
  book<TH1F>("jetsPT",                        ";P_{t};Number of jets",                                                            251, -0.5, 500.5);
  book<TH1F>("jetsEta" ,                      ";#eta; Number of jets",                                                            100, -7, 7);
  book<TH1F>("jetsPhi" ,                      ";#phi; Number of jets",                                                            50, -4, 4);
  book<TH1F>("jetsMass" ,                     ";Mass (GeV); Number of jets",                                                      101, -0.5, 50.5);
  book<TH1F>("jetsVSpartsdR",                 ";#DeltaR (genjets, genparticles);Events / bin",                              101, -0.5, 20.5);
  book<TH1F>("jetsHt" ,                       ";H_{t};Events / bin",                                                              201, -0.5, 1000.5);
  book<TH1F>("dEtaLJ" ,                       ";|#Delta #eta|_{leading jets};Events / bin",                                       71, -0.5, 15.5);
  book<TH1F>("dRLJ",                          ";|#Delta R|_{leading jets};Events / bin",                                          101, -0.5, 20.5);
  book<TH1F>("LJMass" ,                       ";2 leading jets mass (GeV); Events",                                               301, -0.5, 2000.5);

  // book all the particles histograms
  book<TH1F>("number_genparts",               ";number of gen part.; Events / bin",                                               1000,  0., 1000);
  book<TH1F>("number_charged_genparts",       ";number of charged gen part.; Events / bin",                                       600,  0., 600);
  book<TH1F>("number_neutral_genparts",       ";number of neutral gen part.; Events / bin",                                       600,  0., 600);
  book<TH1F>("charged_neutral_ratio",         ";charged/neutral; Events / bin",                                                   1000,      0.,      10);

  book<TH1F>("gen_part_pdgid",                ";pdgid; Events / bin",                                                             n_pdgids, 0, n_pdgids);
  book<TH1F>("gen_part_statusFlag",           ";status flag; Events / bin",                                                       n_flags, 0, n_flags);

  book<TH1F>("gen_part_pt",                   ";p_{T}; Events / bin",                                                             150,  0., 150);
  book<TH1F>("gen_part_eta",                  ";#eta; Events / bin",                                                              100, -10., 10.);
  book<TH1F>("gen_part_phi",                  ";#phi; Events / bin",                                                              70, -3.5, 3.5);
  book<TH1F>("gen_part_m",                    ";Mass; Events / bin",                                                              50,   0., 2);
  book<TH1F>("gen_part_e",                    ";Energy; Events / bin",                                                            50,   0., 1500);
  book<TH1F>("gen_part_charge",               ";Charge; Events / bin",                                                            3,  -1.5, 1.5);
  book<TH1F>("gen_part_Ht",                   ";Ht; Events / bin",                                                                1001, -0.5, 1000.5);

  book<TH1F>("genMET",                        ";genMET (status==1); Events / bin",                                                100,  0., 1000);


  book<TH2F>("gen_part_pdgid_vs_statusFlag",  ";pdgid; status flag", n_pdgids, 0, n_pdgids, n_flags, 0, n_flags);

  for(size_t i=1; i<=n_pdgids; i++) {
    hist<TH1F>("gen_part_pdgid")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
  }

  for(size_t i=1; i<=n_flags; i++) {
    hist<TH1F>("gen_part_statusFlag")->GetXaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetYaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
  }
}

void GenLevelStudiesHists::fill(const VBFTaggerEvent & event) {

  // removing the events containing taus
  for (const GenParticle& t: *event.genparticles_stable) {if (t.pdgid() == 15) return;}

  // declare all the variables needed
  double weight = event.weight;
  double Ht=0, partHt=0;
  double eta_min, eta_max, dEta;
  vector<GenParticle> all_particles, charged_particles, neutral_particles;
  vector<GenJet> nJets;
  TLorentzVector genMET;
  GenJet j1, j2;

  // fill the histograms that don't need loop
  hist<TH1F>("sumweights")->Fill(1, weight);
  hist<TH1F>("number_genparts")->Fill(event.genparticles_stable->size(), weight);

  // loop over the jets
  for (size_t i=0; i<event.genjets->size(); i++) {
    GenJet gj = event.genjets->at(i);

    if (FindInString("jetPt>10", selection.Data()) && gj.pt()<10) continue;
    if (FindInString("jetPt>20", selection.Data()) && gj.pt()<20) continue;
    if (FindInString("jetPt>30", selection.Data()) && gj.pt()<30) continue;

    nJets.push_back(gj);
    Ht += gj.pt();

    // filling basic histograms
    hist<TH1F>("jetsPT")->Fill(gj.pt(), weight);
    hist<TH1F>("jetsEta")->Fill(gj.eta(), weight);
    hist<TH1F>("jetsPhi")->Fill(gj.phi(), weight);
    hist<TH1F>("jetsMass")->Fill(gj.m(), weight);

    // fill histograms for the 2 leading jets
    if (event.genjets->size() > 1 && i==0) {
      j1 = event.genjets->at(i);
      j2 = event.genjets->at(i+1);
      eta_min = std::min(j1.eta(), j2.eta());
      eta_max = std::max(j1.eta(), j2.eta());
      dEta = deltaEta(j1, j2);
      TLorentzVector v = j1.p4() + j2.p4();
      hist<TH1F>("dEtaLJ")->Fill(dEta, weight);
      hist<TH1F>("dRLJ")->Fill(deltaR(j1, j2), weight);
      hist<TH1F>("LJMass")->Fill(v.M(), weight);
    }

  // end of the loop on the jets
  }

  //fill histograms after the loop
  hist<TH1F>("ngenjets")->Fill(nJets.size(), weight);
  hist<TH1F>("jetsHt")->Fill(Ht, weight);

  // loop on the particles
  for (const GenParticle& gp: *event.genparticles_stable) {

    if (FindInString("status==1", selection.Data()) && gp.status()!=1) continue;
    if (FindInString("partPt>0.2", selection.Data()) && gp.pt()<0.2) continue;
    if (FindInString("partPt<1", selection.Data()) && gp.pt()>1.) continue;
    if (FindInString("partPt>1", selection.Data()) && gp.pt()<1.) continue;
    if (FindInString("gen_selections", selection.Data()) && !gp.isFinalState()) continue;
    if (FindInString("gen_selections", selection.Data()) && !gp.isLastCopy()) continue;
    if (FindInString("gen_selections", selection.Data()) && fabs(gp.pdgid())>1000) continue;
    if (FindInString("charged", selection.Data()) && gp.charge()==0) continue;
    if (FindInString("neutral", selection.Data()) && gp.charge()!=0) continue;

    if (event.genjets->size()>1) {
      bool is_within = eta_min < gp.eta() && gp.eta() < eta_max;
      double dR_from_LJ = std::min(deltaR(gp, j1), deltaR(gp, j2));
      hist<TH1F>("jetsVSpartsdR")->Fill(dR_from_LJ, weight);
      if (FindInString("Inside", selection.Data()) && !is_within) continue;
      if (FindInString("Outside", selection.Data()) && is_within) continue;
    }

    all_particles.push_back(gp);
    if (gp.charge() == 0) {neutral_particles.push_back(gp);}
    if (fabs(gp.charge()) != 0) {charged_particles.push_back(gp);}

    partHt += gp.pt();
    genMET += gp.p4();

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
  // end of the loop on the particles
  }
  hist<TH1F>("number_charged_genparts")->Fill(charged_particles.size(), weight);
  hist<TH1F>("number_neutral_genparts")->Fill(neutral_particles.size(), weight);
  if (neutral_particles.size()!=0) {
    hist<TH1F>("charged_neutral_ratio")->Fill(charged_particles.size()*1./neutral_particles.size(), weight);
  }
  hist<TH1F>("genMET")->Fill(genMET.Pt(), weight);
  hist<TH1F>("gen_part_Ht")->Fill(partHt, weight);
}
