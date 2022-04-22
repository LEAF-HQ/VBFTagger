#include "LEAF/VBFTagger/include/GenLevelStudiesPrunedHists.h"


using namespace std;

GenLevelStudiesPrunedHists::GenLevelStudiesPrunedHists(TString dir_, TString selection_): BaseHists(dir_), selection(selection_) {
  for (const ParticleID& id : gen_ids) {gen_ids_names.push_back(pdgId2str(id));}

  size_t n_pdgids = gen_ids_names.size();
  size_t n_flags = gen_flags_names.size();

  // book all the histograms
  book<TH1F>("sumweights",      ";sum of event weights; Events / bin",                1,  0.5, 1.5);
  book<TH1F>("number_genparts", ";number of gen part.; Events / bin",                 1000,  0., 1000);
  book<TH1F>("number_charged_genparts", ";number of charged gen part.; Events / bin", 300,  0., 300);
  book<TH1F>("number_neutral_genparts", ";number of neutral gen part.; Events / bin", 300,  0., 300);

  book<TH1F>("gen_part_pdgid",  ";pdgid; Events / bin",                               n_pdgids, 0, n_pdgids);
  book<TH1F>("gen_part_statusFlag", ";status flag; Events / bin",                     n_flags, 0, n_flags);

  book<TH1F>("gen_part_pt",     ";p_{T}; Events / bin",                               150,  0., 150);
  book<TH1F>("gen_part_eta",    ";#eta; Events / bin",                                100, -10., 10.);
  book<TH1F>("gen_part_phi",    ";#phi; Events / bin",                                70, -3.5, 3.5);
  book<TH1F>("gen_part_m",      ";mass; Events / bin",                                50,   0., 2);
  book<TH1F>("gen_part_e",      ";Energy; Events / bin",                              50,   0., 1500);
  book<TH1F>("gen_part_charge", ";charge; Events / bin",                              3,  -1.5, 1.5);

  book<TH1F>("genMET", ";genMET (status==1); Events / bin",                           100,  0., 1000);

  // book<TH1F>("Hmass","H->ZZ->4l (M = 125 GeV); H Mass (GeV) ; Number of particles",501, 0, 500);
  book<TH1F>("ZfromHmass","H->ZZ->4l (M = 125 GeV); Z Mass (GeV) ; Number of particles",201, 0, 200);
  book<TH1F>("4Lmass","H->ZZ->4l (M = 125 GeV); 4 Leptons Mass (GeV) ; Number of particles",151, 0, 150);
  book<TH1F>("4Lpt","H->ZZ->4l (M = 125 GeV); 4 Leptons Pt (GeV) ; Number of particles",300, 0, 800);

  book<TH2F>("gen_part_pdgid_vs_statusFlag", ";pdgid; status flag", n_pdgids, 0, n_pdgids, n_flags, 0, n_flags);

  for(size_t i=1; i<=n_pdgids; i++) {
    hist<TH1F>("gen_part_pdgid")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetXaxis()->SetBinLabel(i,gen_ids_names[i-1].c_str());
  }

  for(size_t i=1; i<=n_flags; i++) {
    hist<TH1F>("gen_part_statusFlag")->GetXaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
    hist<TH2F>("gen_part_pdgid_vs_statusFlag")->GetYaxis()->SetBinLabel(i,gen_flags_names[i-1].c_str());
  }
}

void GenLevelStudiesPrunedHists::fill(const VBFTaggerEvent & event) {

  // removing the events containing taus
  for (const GenParticle& t: *event.genparticles_pruned) {if (t.pdgid() == 15) return;}

  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);
  hist<TH1F>("number_genparts")->Fill(event.genparticles_pruned->size(), weight);

  vector<GenParticle> all_particles, charged_particles, neutral_particles;
  vector<GenParticle> H_daughters, H_daughters_names, H_daughters_daughters;
  TLorentzVector FourLeptons = {0, 0, 0, 0}, zero, genMET;

  H_daughters = DaughtersFinder(event, ParticleFinder(event, ParticleID::H, GenParticle::StatusFlag::isLastCopy));
  for (const GenParticle &d: H_daughters) {
    hist<TH1F>("ZfromHmass")->Fill(d.m(), weight);
    for (const GenParticle &dd: DaughtersFinder(event, d)) {
      H_daughters_daughters.push_back(dd);
      if (dd.pdgid() == 11 || dd.pdgid() == 13) {FourLeptons += dd.p4();}
    }
  }
  if (FourLeptons != zero) {
    hist<TH1F>("4Lmass")->Fill(FourLeptons.M(), weight);
    hist<TH1F>("4Lpt")->Fill(FourLeptons.Pt(), weight);
  }

  for (const GenParticle& gp: *event.genparticles_pruned) {

    if (FindInString("status==1", selection.Data()) && gp.status()!=1) continue;
    if (FindInString("pt<1", selection.Data()) && gp.pt()>1.) continue;
    if (FindInString("pt>1", selection.Data()) && gp.pt()<1.) continue;
    if (FindInString("gen_selections", selection.Data()) && !gp.isFinalState()) continue;
    if (FindInString("gen_selections", selection.Data()) && !gp.isLastCopy()) continue;
    if (FindInString("gen_selections", selection.Data()) && fabs(gp.pdgid())>1000) continue;

    all_particles.push_back(gp);
    if (gp.charge() == 0) {neutral_particles.push_back(gp);}
    if (fabs(gp.charge()) != 0) {charged_particles.push_back(gp);}

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
  }
  hist<TH1F>("number_charged_genparts")->Fill(charged_particles.size(), weight);
  hist<TH1F>("number_neutral_genparts")->Fill(neutral_particles.size(), weight);
  hist<TH1F>("genMET")->Fill(genMET.Pt(), weight);
}
