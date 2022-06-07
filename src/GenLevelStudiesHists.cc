#include "LEAF/VBFTagger/include/GenLevelStudiesHists.h"


using namespace std;

GenLevelStudiesHists::GenLevelStudiesHists(TString dir_, TString selection_): BaseHists(dir_), selection(selection_) {
  for (const ParticleID& id : gen_ids) {gen_ids_names.push_back(pdgId2str(id));}

  size_t n_pdgids = gen_ids_names.size();
  size_t n_flags = gen_flags_names.size();

// book all the histograms
  book<TH1F>("sumweights",                    ";sum of event weights; Events / bin",                                              1,  0.5, 1.5);

  // book all the jets histograms
  book<TH1F>("gen_jet_number",                      ";N_{genjets}; Events / bin",                                                     21, -0.5, 20.5);
  book<TH1F>("gen_jet_Pt",                        ";P_{t};Number of jets",                                                            101, -0.5, 600.5);
  book<TH1F>("gen_jet_Eta" ,                      ";#eta; Number of jets",                                                            100, -7, 7);
  book<TH1F>("gen_jet_Phi" ,                      ";#phi; Number of jets",                                                            50, -4, 4);
  book<TH1F>("gen_jet_Mass" ,                     ";Mass (GeV); Number of jets",                                                      101, -0.5, 60.5);
  book<TH1F>("gen_jet_VS_gen_part_dR",                 ";#DeltaR (genjets, genparticles);Events / bin",                               101, -0.5, 20.5);
  book<TH1F>("gen_jet_Ht" ,                       ";H_{t};Events / bin",                                                              101, -0.5, 1000.5);
  book<TH1F>("gen_LJ_dEta" ,                       ";|#Delta #eta|_{leading jets};Events / bin",                                      71, -0.5, 15.5);
  book<TH1F>("gen_LJ_dR",                          ";|#Delta R|_{leading jets};Events / bin",                                         101, -0.5, 20.5);
  book<TH1F>("gen_LJ_Mass" ,                       ";M(jj) (GeV); Events",                                                            101, -0.5, 3000.5);
  book<TH1F>("gen_LJ_Pt",                          ";Leading Jet P_{t}; Number of jets",                                              101, -0.5, 600.5);
  book<TH1F>("gen_SLJ_Pt",                         ";Sub-leading Jet P_{t}; Number of jets",                                          251, -0.5, 500.5);
  book<TH1F>("gen_LJ_Eta",                         ";#eta of the 2 leading jets; Number of jets",                                     100, -7, 7);
  book<TH1F>("gen_!LJ_Eta",                        ";#eta of all jets but the two leading ones; Number of jets",                      35, -7, 7);

  // book<TH1F>("gen_LJ_CMF_Mass",                    ";M(jj) (GeV); Events",                                               301, -0.5, 2000.5);

  // book all the particles histograms
  book<TH1F>("gen_part_number",               ";number of gen part.; Events / bin",                                                    500,  0., (selection=="")? 1000: 500);
  // book<TH1F>("gen_part_number_charged",       ";number of charged gen part.; Events / bin",                                         400,  0., (selection=="Mjj>200__")? 600: 400);
  // book<TH1F>("gen_part_number_neutral",       ";number of neutral gen part.; Events / bin",                                         300,  0., (selection=="Mjj>200__")? 600: 300);
  book<TH1F>("gen_part_ndensity",               ";number of gen part by unit of #eta; Events / bin",                                   100,  0., 100);
  book<TH1F>("gen_part_charged_neutral_ratio",         ";charged/neutral; Events / bin",                                               50,      0.,      4);

  book<TH1F>("gen_part_pdgid",                ";pdgid; Events / bin",                                                             n_pdgids, 0, n_pdgids);
  book<TH1F>("gen_part_pdgid2",               ";pdgid of particles w/ p_{T}>50; Events / bin",                                                             n_pdgids, 0, n_pdgids);
  book<TH1F>("gen_part_statusFlag",           ";status flag; Events / bin",                                                       n_flags, 0, n_flags);

  book<TH1F>("gen_part_pt",                   ";p_{T}; Events / bin",                                                             150,  0., 150);
  book<TH1F>("gen_part_eta",                  ";#eta; Events / bin",                                                              100, -10., 10.);
  book<TH1F>("gen_part_etaXpt",               ";#eta x p_{T}; Events / bin",                                                      100, -10, 10);
  book<TH1F>("gen_part_etaXptsq",             ";#eta x p_{T}^{2}; Events / bin",                                                  100, -60, 60);
  book<TH1F>("gen_part_avg_etaXpt",           ";#eta x p_{T}; Events / bin",                                                      81, -20.05, 20.05);
  book<TH1F>("gen_part_avg_etaXptsq",         ";#eta x p_{T}^{2}; Events / bin",                                                  100, -500, 500);
  book<TH1F>("gen_part_phi",                  ";#phi; Events / bin",                                                              70, -3.5, 3.5);
  book<TH1F>("gen_part_m",                    ";Mass; Events / bin",                                                              50,   0., 2);
  book<TH1F>("gen_part_e",                    ";Energy; Events / bin",                                                            50,   0., 1500);
  book<TH1F>("gen_part_charge",               ";Charge; Events / bin",                                                            3,  -1.5, 1.5);
  book<TH1F>("gen_part_Ht",                   ";Ht; Events / bin",                                                                301, -0.5, 1000.5);

  book<TH1F>("gen_part_MET",                        ";genMET ; Events / bin",                                                     50,  0., 1000);

  book<TH1F>("gen_part_z1",                   ";z;  Events / bin",                                                                 100, 0, 10);
  book<TH1F>("gen_part_z2",                   ";z;  Events / bin",                                                                 180, 0, 3);

  book<TH1F>("gen_part_ratio_InOut",          ";#Inside/#Outside; Events / bin",                                                   50, 0, 10);
  book<TH1F>("gen_part_density_ratio_InOut",  ";Density inside / density outside",                                                 11, -0.5, 10.5);


  book<TH2F>("gen_part_pdgid_vs_statusFlag",  ";pdgid; status flag", n_pdgids, 0, n_pdgids, n_flags, 0, n_flags);
  book<TH2F>("gen_part_dIn_vs_dOut",          ";Density inside; Density outside", 90, 0, 90, 90, 0, 90);

  for(size_t i=1; i<=n_pdgids; i++) {
    hist<TH1F>("gen_part_pdgid")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
    hist<TH1F>("gen_part_pdgid2")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
  }

  for(size_t i=1; i<=n_flags; i++) {
    hist<TH1F>("gen_part_statusFlag")->GetXaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetYaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
  }
}

void GenLevelStudiesHists::fill(const VBFTaggerEvent & event) {


  // declare all the variables needed
  double weight = event.weight;
  double Ht=0, partHt=0;
  double eta_min, eta_max;
  double dEta;
  double density, densityIn, densityOut;
  double etaPT, etaPTsq;
  double z2;
  vector<double> avg1, avg2;
  vector<GenParticle> all_particles, charged_particles, neutral_particles;
  vector<GenParticle> nInside, nOutside;
  vector<GenJet> nJets;
  TLorentzVector genMET;
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
  hist<TH1F>("gen_jet_number")->Fill(nJets.size(), weight);
  hist<TH1F>("gen_jet_Ht")->Fill(Ht, weight);





  // loop over the particles
  for (const GenParticle& gp: *event.genparticles_stable) {

    // Emulation of reco level
    int Pcharge = gp.charge();
    if (FindInString("reco", selection.Data())) {
      if (gp.charge()!=0 && fabs(gp.eta())>2.5) {Pcharge = 0;}
    }


    if (FindInString("status==1", selection.Data()) && gp.status()!=1) continue;
    if (FindInString("partPt>0.2", selection.Data()) && gp.pt()<0.2) continue;
    if (FindInString("partPt<1", selection.Data()) && gp.pt()>1.) continue;
    if (FindInString("partPt>1", selection.Data()) && gp.pt()<1.) continue;
    if (FindInString("gen_selections", selection.Data()) && !gp.isFinalState()) continue;
    if (FindInString("gen_selections", selection.Data()) && !gp.isLastCopy()) continue;
    if (FindInString("gen_selections", selection.Data()) && fabs(gp.pdgid())>1000) continue;
    if (FindInString("charged", selection.Data()) && Pcharge==0) continue;
    if (FindInString("neutral", selection.Data()) && Pcharge!=0) continue;

    if (event.genjets->size()>1) {
      bool is_within = eta_min < gp.eta() && gp.eta() < eta_max;
      if (is_within) {
        nInside.push_back(gp);
        // eta_inside_min = std::min(gp.eta(), eta_inside_min);
        // eta_inside_max = std::max(gp.eta(), eta_inside_max);
      }
      if (!is_within) {nOutside.push_back(gp);}
      if (FindInString("Inside", selection.Data()) && !is_within) continue;
      if (FindInString("Outside", selection.Data()) && is_within) continue;
      double dR_from_LJ = std::min(deltaR(gp, j1), deltaR(gp, j2));
      hist<TH1F>("gen_jet_VS_gen_part_dR")->Fill(dR_from_LJ, weight);

      etaPT = gp.eta() * gp.pt() *1. / (2*5.2);
      etaPTsq = gp.eta() * gp.pt() * gp.pt() * 1. / (2*5.2);
      z2 = fabs(gp.eta()-(j1.eta()+j2.eta())*1. /2.)/(2*5.2);
      if (FindInString("Inside", selection.Data())) {
        etaPT = gp.eta() * gp.pt() *1. / dEta;
        etaPTsq = gp.eta() * gp.pt() * gp.pt() * 1. / dEta;
        z2 = fabs(gp.eta()-(j1.eta()+j2.eta())*1. /2.)/dEta;
      }
      if (FindInString("Outside", selection.Data())) {
        etaPT = gp.eta() * gp.pt() *1. / (2*5.2 - dEta);
        etaPTsq = gp.eta() * gp.pt() * gp.pt() * 1. / (2*5.2 - dEta);
        z2 = fabs(gp.eta()-(j1.eta()+j2.eta())*1. /2.)/(2*5.2 - dEta);
      }
      avg1.push_back(etaPT);
      avg2.push_back(etaPTsq);
      hist<TH1F>("gen_part_etaXpt")->Fill(etaPT, weight);
      hist<TH1F>("gen_part_etaXptsq")->Fill(etaPTsq, weight);
      hist<TH1F>("gen_part_z1")->Fill(Zeppenfeld1(event, gp), weight);
      hist<TH1F>("gen_part_z2")->Fill(z2, weight);
    }

    all_particles.push_back(gp);
    if (Pcharge == 0) {neutral_particles.push_back(gp);}
    if (fabs(Pcharge) != 0) {charged_particles.push_back(gp);}

    partHt += gp.pt();
    genMET += gp.p4();

    // eta_part_min = std::min(gp.eta(), eta_part_min);
    // eta_part_max = std::max(gp.eta(), eta_part_max);


    string pdgid = pdgId2str(fabs(gp.pdgid()));

    hist<TH1F>("gen_part_pt")->Fill(gp.pt(), weight);
    // if (gp.pt()>50) {cout<<"pdgid(id): "<<pdgId2str(gp.pdgid())<<"("<<gp.identifier()<<")"<<"   mother(id): "<<pdgId2str(event.genparticles_pruned->at(gp.pruned_mother_identifier()).pdgid())<<"("<<gp.pruned_mother_identifier()<<")"<<"   Pt: "<<gp.pt()<<"   eta: "<<gp.eta()<<endl;}
    hist<TH1F>("gen_part_eta")->Fill(gp.eta(), weight);
    hist<TH1F>("gen_part_phi")->Fill(gp.phi(), weight);
    hist<TH1F>("gen_part_m")->Fill(gp.m(), weight);
    hist<TH1F>("gen_part_e")->Fill(gp.e(), weight);
    hist<TH1F>("gen_part_charge")->Fill(Pcharge, weight);

    hist<TH1F>("gen_part_pdgid")->Fill(pdgid.c_str(), weight);
    if (gp.pt()>50) {hist<TH1F>("gen_part_pdgid2")->Fill(pdgid.c_str(), weight);}
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
    densityIn = nInside.size()*1./(dEta);
    densityOut = nOutside.size()*1./(2. * 5.2 - dEta);
    // cout<<"In: "<<densityIn<<"   Out: "<<densityOut<<"   ratio: "<<densityIn*1./densityOut<<endl;
    hist<TH1F>("gen_part_ratio_InOut")->Fill(nInside.size()*1./nOutside.size(), weight);
    hist<TH1F>("gen_part_density_ratio_InOut")->Fill(densityIn*1./densityOut, weight);
    hist<TH1F>("gen_part_avg_etaXpt")->Fill(Average(avg1), weight);
    hist<TH1F>("gen_part_avg_etaXptsq")->Fill(Average(avg2), weight);

    hist<TH2F>("gen_part_dIn_vs_dOut")->Fill(densityIn, densityOut, weight);
  }

  density = all_particles.size()*1./(2*5.2);
  if (FindInString("Inside", selection.Data())) {density = all_particles.size()*1./dEta;}
  if (FindInString("Outside", selection.Data())) {density = all_particles.size()*1./(2*5.2 - dEta);}


  hist<TH1F>("gen_part_number")->Fill(all_particles.size(), weight);
  // hist<TH1F>("gen_part_number_charged")->Fill(charged_particles.size()-4, weight);
  // hist<TH1F>("gen_part_number_neutral")->Fill(neutral_particles.size(), weight);
  if (neutral_particles.size()!=0) {
    hist<TH1F>("gen_part_charged_neutral_ratio")->Fill((charged_particles.size())*1./neutral_particles.size(), weight);
  }
  hist<TH1F>("gen_part_MET")->Fill(genMET.Pt(), weight);
  hist<TH1F>("gen_part_Ht")->Fill(partHt, weight);
  hist<TH1F>("gen_part_ndensity")->Fill(density, weight);
}
