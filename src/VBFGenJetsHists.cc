#include "LEAF/VBFTagger/include/VBFGenJetsHists.h"

using namespace std;

VBFGenJetsHists::VBFGenJetsHists(TString dir_, TString selection_) : BaseHists(dir_), selection(selection_) {

  const vector<Decay> higgs_decay = {Decay::ZZ, Decay::ZZtautautautau, Decay::ZZmumumumu, Decay::ZZeeee, Decay::ZZvvvv, Decay::ZZeemumu, Decay::ZZeetautau, Decay::ZZeevv, Decay::ZZmumutautau, Decay::ZZmumuvv, Decay::ZZtautauvv
  };
  vector<string> higgs_decay_names;
  for ( const Decay& decay : higgs_decay ) { higgs_decay_names.push_back(decay2str(decay));}

  size_t n_higgs_decay = higgs_decay.size();

  book<TH1F>("sumweights",        ";sum of event weights; Events / bin",  1,       0.5,     1.5);
  book<TH1F>("n_genjets",         ";number of gen jets ; Events / bin",   6,      -0.5,     5.5);
  book<TH1F>("gen_higgs_decay",   ";gen_higgs_decay; Events / bin", n_higgs_decay, 0, n_higgs_decay);

  for(size_t i=1; i<=n_higgs_decay; i++) {
    hist<TH1F>("gen_higgs_decay")->GetXaxis()->SetBinLabel(i,higgs_decay_names[i-1].c_str());
  }

  book<TH1F>("jet_pt",            ";p_{T}; Events / bin",                 50,      0.,   1000);
  book<TH1F>("jet_eta",           ";#eta; Events / bin",                 100,     -5.,      5.);
  book<TH1F>("jet_phi",           ";#phi; Events / bin",                  70,     -3.5,     3.5);
  book<TH1F>("jet_m",             ";mass; Events / bin",                  50,      0.,    200);
  book<TH1F>("jet_e",             ";Energy; Events / bin",                50,      0.,   1000);

  book<TH2F>("jet_pt_vs_eta",     ";p_{T}; #eta",                         50,      0.,   1000,    100,     -5.,      5.);
  book<TH2F>("jet_eta_vs_phi",    ";#eta; #phi",                         100,     -5.0,     5.0,   70,     -3.5,     3.5);

  book<TH2F>("jet1_eta_vs_jet2",    ";#eta_{jet1}; #eta_{jet2}",         100,     -5.0,     5.0,  100,     -5.0,     5.0);
  book<TH1F>("m_jj",                ";m(jj); Events / bin",              500,      0.,    1500);
  book<TH1F>("DR_jj",               ";#Delta R(jj); Events / bin",       160,      0,        8);
  book<TH1F>("Deta_jj",             ";#Delta#eta(jj); Events / bin",     160,      0,        8);
  book<TH1F>("eta1*eta2",           ";#eta_1*#eta_2; Events / bin",      160,    -20,       20);

}

void VBFGenJetsHists::fill(const VBFTaggerEvent & event){
  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);
  hist<TH1F>("n_genjets")->Fill((*event.VBF_genjets).size(), weight);
  hist<TH1F>("gen_higgs_decay")->Fill(decay2str(event.gen_higgs_decay()).c_str(), weight);

  for(unsigned index_jet1 = 0; index_jet1 < (*event.VBF_genjets).size(); index_jet1++ ){
    const GenJet jet = (*event.VBF_genjets).at(index_jet1);
    hist<TH1F>("jet_pt")->Fill(jet.pt(), weight);
    hist<TH1F>("jet_eta")->Fill(jet.eta(), weight);
    hist<TH1F>("jet_phi")->Fill(jet.phi(), weight);
    hist<TH1F>("jet_m")->Fill(jet.m(), weight);
    hist<TH1F>("jet_e")->Fill(jet.e(), weight);

    hist<TH2F>("jet_pt_vs_eta")->Fill(jet.pt(), jet.eta(), weight);
    hist<TH2F>("jet_eta_vs_phi")->Fill(jet.eta(), jet.phi(), weight);

    for(unsigned index_jet2 = index_jet1+1; index_jet2 < (*event.VBF_genjets).size(); index_jet2++ ){
      const GenJet jet2 = (*event.VBF_genjets).at(index_jet2);
      TLorentzVector jj = jet.p4() + jet2.p4();
      hist<TH2F>("jet1_eta_vs_jet2")->Fill(jet.eta(), jet2.eta(), weight);
      hist<TH1F>("m_jj")->Fill(jj.M(), weight);
      hist<TH1F>("DR_jj")->Fill(deltaR(jet, jet2), weight);
      hist<TH1F>("Deta_jj")->Fill(deltaEta(jet, jet2), weight);
      hist<TH1F>("eta1*eta2")->Fill(jet.eta()*jet2.eta(), weight);
    }
  }

}
