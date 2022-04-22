#include "LEAF/VBFTagger/include/GenLevelStudiesHists.h"


using namespace std;

GenLevelStudiesHists::GenLevelStudiesHists(TString dir_, TString selection_): BaseHists(dir_), selection(selection_) {
  for (const ParticleID& id : gen_ids) {gen_ids_names.push_back(pdgId2str(id));}

  size_t n_pdgids = gen_ids_names.size();
  size_t n_flags = gen_flags_names.size();

// book all the histograms
  book<TH1F>("sumweights",                    ";sum of event weights; Events / bin",                                              1,  0.5, 1.5);

  // book all the jets histograms
  book<TH1F>("gen_jet_number",                      ";N_{genjets}; Events / bin",                                        21, -0.5, 20.5);
  book<TH1F>("gen_jet_Pt",                        ";P_{t};Number of jets",                                                            251, -0.5, 500.5);
  book<TH1F>("gen_jet_Eta" ,                      ";#eta; Number of jets",                                                            100, -7, 7);
  book<TH1F>("gen_jet_Phi" ,                      ";#phi; Number of jets",                                                            50, -4, 4);
  book<TH1F>("gen_jet_Mass" ,                     ";Mass (GeV); Number of jets",                                                      101, -0.5, 50.5);
  book<TH1F>("gen_jet_VS_gen_part_dR",                 ";#DeltaR (genjets, genparticles);Events / bin",                              101, -0.5, 20.5);
  book<TH1F>("gen_jet_Ht" ,                       ";H_{t};Events / bin",                                                              201, -0.5, 1000.5);
  book<TH1F>("gen_LJ_dEta" ,                       ";|#Delta #eta|_{leading jets};Events / bin",                                       71, -0.5, 15.5);
  book<TH1F>("gen_LJ_dR",                          ";|#Delta R|_{leading jets};Events / bin",                                          101, -0.5, 20.5);
  book<TH1F>("gen_LJ_Mass" ,                       ";M(jj) (GeV); Events",                                               301, -0.5, 2000.5);
  book<TH1F>("gen_LJ_Pt",                          ";Leading Jet P_{t}; Number of jets",                                               251, -0.5, 500.5);
  book<TH1F>("gen_SLJ_Pt",                         ";Sub-leading Jet P_{t}; Number of jets",                                           251, -0.5, 500.5);
  book<TH1F>("gen_LJ_Eta",                         ";#eta of the 2 leading jets; Number of jets",                                      100, -7, 7);
  book<TH1F>("gen_!LJ_Eta",                        ";#eta of all jets but the two leading ones; Number of jets",                       100, -7, 7);

  // book<TH1F>("gen_LJ_CMF_Mass",                    ";M(jj) (GeV); Events",                                               301, -0.5, 2000.5);

  // book all the particles histograms
  book<TH1F>("gen_part_number",               ";number of gen part.; Events / bin",                                                    500,  0., (selection=="Mjj>200__")? 1000: 500);
  // book<TH1F>("gen_part_number_charged",       ";number of charged gen part.; Events / bin",                                         400,  0., (selection=="Mjj>200__")? 600: 400);
  // book<TH1F>("gen_part_number_neutral",       ";number of neutral gen part.; Events / bin",                                         300,  0., (selection=="Mjj>200__")? 600: 300);
  book<TH1F>("gen_part_ndensity",               ";number of gen part by unit of #eta; Events / bin",                                   100,  0., 100);
  book<TH1F>("gen_part_charged_neutral_ratio",         ";charged/neutral; Events / bin",                                               400,      0.,      4);

  book<TH1F>("gen_part_pdgid",                ";pdgid; Events / bin",                                                             n_pdgids, 0, n_pdgids);
  book<TH1F>("gen_part_statusFlag",           ";status flag; Events / bin",                                                       n_flags, 0, n_flags);

  book<TH1F>("gen_part_pt",                   ";p_{T}; Events / bin",                                                             150,  0., 150);
  book<TH1F>("gen_part_eta",                  ";#eta; Events / bin",                                                              100, -10., 10.);
  book<TH1F>("gen_part_phi",                  ";#phi; Events / bin",                                                              70, -3.5, 3.5);
  book<TH1F>("gen_part_m",                    ";Mass; Events / bin",                                                              50,   0., 2);
  book<TH1F>("gen_part_e",                    ";Energy; Events / bin",                                                            50,   0., 1500);
  book<TH1F>("gen_part_charge",               ";Charge; Events / bin",                                                            3,  -1.5, 1.5);
  book<TH1F>("gen_part_Ht",                   ";Ht; Events / bin",                                                                501, -0.5, 1000.5);

  book<TH1F>("gen_part_MET",                        ";genMET ; Events / bin",                                                     100,  0., 1000);

  book<TH1F>("gen_part_z1",                   ";z;  Events / bin",                                                                 100, 0, 10);
  book<TH1F>("gen_part_z2",                   ";z;  Events / bin",                                                                 100, 0, 15);

  book<TH1F>("gen_part_ratio_InOut",          ";#Inside/#Outside; Events / bin",                                                   100, 0, 10);
  book<TH1F>("gen_part_density_ratio_InOut",  ";Density inside / density outside",                                                 100, 0, 10);


  book<TH2F>("gen_part_pdgid_vs_statusFlag",  ";pdgid; status flag", n_pdgids, 0, n_pdgids, n_flags, 0, n_flags);
  book<TH2F>("gen_part_dIn_vs_dOut",          ";Density inside; Density outside", 100, 0, 100, 100, 0, 100);

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
  for (const GenParticle& t: *event.genparticles_stable) {if (fabs(t.pdgid()) == 15) return;}

  // declare all the variables needed
  double weight = event.weight;
  double Ht=0, partHt=0;
  double eta_min, eta_max, dEta;
  double eta_part_min = 100.;
  double eta_part_max = -100.;
  double eta_inside_min = 100.;
  double eta_inside_max = -100.;
  double densityIn, densityOut;
  vector<GenParticle> all_particles, charged_particles, neutral_particles;
  vector<GenParticle> nInside, nOutside;
  vector<GenJet> nJets;
  TLorentzVector genMET;
  // bool modif = false;
  GenJet j1, j2;

  // fill the histograms that don't need loop
  hist<TH1F>("sumweights")->Fill(1, weight);

  // fill histograms for the 2 leading jets
  if (event.genjets->size() > 1) {
    j1 = event.genjets->at(0);
    j2 = event.genjets->at(1);
    eta_min = std::min(j1.eta(), j2.eta());
    eta_max = std::max(j1.eta(), j2.eta());
    dEta = deltaEta(j1, j2);
    TLorentzVector v = j1.p4() + j2.p4();
    if (FindInString("Mjj>200", selection.Data()) && v.M()<200) return;
    hist<TH1F>("gen_LJ_dEta")->Fill(dEta, weight);
    hist<TH1F>("gen_LJ_dR")->Fill(deltaR(j1, j2), weight);
    hist<TH1F>("gen_LJ_Mass")->Fill(v.M(), weight);
    hist<TH1F>("gen_LJ_Pt")->Fill(j1.pt(), weight);
    hist<TH1F>("gen_SLJ_Pt")->Fill(j2.pt(), weight);
    hist<TH1F>("gen_LJ_Eta")->Fill(j1.eta(), weight);
    hist<TH1F>("gen_LJ_Eta")->Fill(j2.eta(), weight);
  }

  // loop over the jets
  for (size_t i=0; i<event.genjets->size(); i++) {
    GenJet gj = event.genjets->at(i);

    // if (FindInString("jetPt>10", selection.Data()) && gj.pt()<10) continue;
    // if (FindInString("jetPt>20", selection.Data()) && gj.pt()<20) continue;
    // if (FindInString("jetPt>30", selection.Data()) && gj.pt()<30) continue;
    if (FindInString("Mjj>200", selection.Data()) && event.genjets->size()<2) return;

    // modif = true;
    nJets.push_back(gj);
    Ht += gj.pt();

    // filling basic histograms
    hist<TH1F>("gen_jet_Pt")->Fill(gj.pt(), weight);
    hist<TH1F>("gen_jet_Eta")->Fill(gj.eta(), weight);
    hist<TH1F>("gen_jet_Phi")->Fill(gj.phi(), weight);
    hist<TH1F>("gen_jet_Mass")->Fill(gj.m(), weight);

    if (i>1) {hist<TH1F>("gen_!LJ_Eta")->Fill(gj.eta(), weight);}

  // end of the loop on the jets
  }

  //fill histograms after the loop
  // if (modif) {
  //   hist<TH1F>("gen_jet_number")->Fill(nJets.size(), weight);
  //   hist<TH1F>("gen_jet_Ht")->Fill(Ht, weight);
  // }

  hist<TH1F>("gen_jet_number")->Fill(nJets.size(), weight);
  hist<TH1F>("gen_jet_Ht")->Fill(Ht, weight);

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
    if (FindInString("Mjj>200", selection.Data()) && event.genjets->size()<2) return;

    if (event.genjets->size()>1) {
      bool is_within = eta_min < gp.eta() && gp.eta() < eta_max;
      double dR_from_LJ = std::min(deltaR(gp, j1), deltaR(gp, j2));
      hist<TH1F>("gen_jet_VS_gen_part_dR")->Fill(dR_from_LJ, weight);
      if (is_within) {
        nInside.push_back(gp);
        eta_inside_min = std::min(gp.eta(), eta_inside_min);
        eta_inside_max = std::max(gp.eta(), eta_inside_max);
      }
      if (!is_within) {nOutside.push_back(gp);}
      if (FindInString("Inside", selection.Data()) && !is_within) continue;
      if (FindInString("Outside", selection.Data()) && is_within) continue;
      hist<TH1F>("gen_part_z1")->Fill(Zeppenfeld1(event, gp), weight);
      hist<TH1F>("gen_part_z2")->Fill(Zeppenfeld2(event, gp), weight);
    }

    all_particles.push_back(gp);
    if (gp.charge() == 0) {neutral_particles.push_back(gp);}
    if (fabs(gp.charge()) != 0) {charged_particles.push_back(gp);}

    partHt += gp.pt();
    genMET += gp.p4();

    eta_part_min = std::min(gp.eta(), eta_part_min);
    eta_part_max = std::max(gp.eta(), eta_part_max);


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
  if (event.genjets->size()>1) {
    densityIn = nInside.size()*1./(eta_inside_max - eta_inside_min);
    densityOut = nOutside.size()*1./(eta_part_max - eta_part_min - eta_inside_max + eta_inside_min);
    // cout<<"In: "<<densityIn<<"   Out: "<<densityOut<<"   ratio: "<<densityIn*1./densityOut<<endl;
    hist<TH1F>("gen_part_ratio_InOut")->Fill(nInside.size()*1./nOutside.size(), weight);
    hist<TH1F>("gen_part_density_ratio_InOut")->Fill(densityIn*1./densityOut, weight);

    hist<TH2F>("gen_part_dIn_vs_dOut")->Fill(densityIn, densityOut, weight);
  }


  if (FindInString("neutral", selection.Data())) {
    hist<TH1F>("gen_part_number")->Fill(all_particles.size(), weight);
  }
  else {hist<TH1F>("gen_part_number")->Fill(all_particles.size()-4., weight);}

  // hist<TH1F>("gen_part_number_charged")->Fill(charged_particles.size()-4, weight);
  // hist<TH1F>("gen_part_number_neutral")->Fill(neutral_particles.size(), weight);
  if (neutral_particles.size()!=0) {
    hist<TH1F>("gen_part_charged_neutral_ratio")->Fill((charged_particles.size()-4)*1./neutral_particles.size(), weight);
  }
  hist<TH1F>("gen_part_MET")->Fill(genMET.Pt(), weight);
  hist<TH1F>("gen_part_Ht")->Fill(partHt, weight);
  hist<TH1F>("gen_part_ndensity")->Fill((all_particles.size()-4.)*1./(eta_part_max - eta_part_min), weight);
}
