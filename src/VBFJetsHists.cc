#include "LEAF/VBFTagger/include/VBFJetsHists.h"

using namespace std;

VBFJetsHists::VBFJetsHists(TString dir_, TString selection_) : BaseHists(dir_), selection(selection_) {

  is_etaprod = FindInString("eta1*eta2<0", selection.Data());
  is_deta    = FindInString("deta>1.4", selection.Data());
  is_mjj     = FindInString("mjj>200", selection.Data());

  book<TH1F>("sumweights",        ";sum of event weights; Events / bin",  1,       0.5,     1.5);
  book<TH1F>("number_of_jets",    ";number of jets ; Events / bin",      11,      -0.5,    10.5);

  book<TH1F>("HT_jets",           ";H_{T} from jets; Events / bin",      150,      0.,   1500);

  book<TH1F>("jet_pt",            ";p_{T}; Events / bin",                 50,      0.,   1000);
  book<TH1F>("jet_eta",           ";#eta; Events / bin",                 100,     -5.,      5.);
  book<TH1F>("jet_phi",           ";#phi; Events / bin",                  70,     -3.5,     3.5);
  book<TH1F>("jet_m",             ";mass; Events / bin",                  50,      0.,    200);
  book<TH1F>("jet_e",             ";Energy; Events / bin",                50,      0.,   1000);

  book<TH2F>("jet_pt_vs_eta",     ";p_{T}; #eta",                         50,      0.,   1000,    100,     -5.,      5.);
  book<TH2F>("jet_eta_vs_phi",    ";#eta; #phi",                         100,     -5.0,     5.0,   70,     -3.5,     3.5);

  book<TH1F>("jet_area",            ";area; Events / bin",               100,      0.,      2);
  book<TH1F>("jet_score_CSVv2",     ";CSVv2; Events / bin",              102,     -0.01,    1.01);
  book<TH1F>("jet_score_DeepB",     ";DeepB; Events / bin",              102,     -0.01,    1.01);
  book<TH1F>("jet_score_DeepFlavB", ";DeepFlavB; Events / bin",          102,     -0.01,    1.01);
  book<TH1F>("jet_score_qgl",       ";qgl; Events / bin",                102,     -0.01,    1.01);
  book<TH1F>("jet_ch_had_efrac",    ";ch. had. efrac; Events / bin",      20,      0.,      1.);
  book<TH1F>("jet_ne_em_efrac",     ";ne. em. efrac; Events / bin",       20,      0.,      1.);
  book<TH1F>("jet_ne_had_efrac",    ";ne. had. efrac; Events / bin",      20,      0.,      1.);
  book<TH1F>("jet_muo_efrac",       ";muo. efrac; Events / bin",          20,      0.,      1.);
  book<TH1F>("jet_ele_efrac",       ";ele. efrac; Events / bin",          20,      0.,      1.);
  book<TH1F>("jet_pho_efrac",       ";pho. efrac; Events / bin",          20,      0.,      1.);
  book<TH1F>("jet_parton_flavor",   ";part. flav.; Events / bin",         20,      0.,     20);
  book<TH1F>("jet_hadron_flavor",   ";had. flav.; Events / bin",          20,      0.,     20);
  book<TH1F>("jet_n_constituents",  ";# const.; Events / bin",            50,      0.,    100);
  book<TH1F>("jet_n_muons",         ";# muo.; Events / bin",              50,      0.,     10);
  book<TH1F>("jet_n_electrons",     ";# ele.; Events / bin",              50,      0.,     10);

  book<TH1F>("jet1_eta",            ";#eta_{jet1}; Events / bin",        100,     -5.0,     5.0);
  book<TH1F>("jet2_eta",            ";#eta_{jet2}; Events / bin",        100,     -5.0,     5.0);
  book<TH2F>("jet1_eta_vs_jet2",    ";#eta_{jet1}; #eta_{jet2}",         100,     -5.0,     5.0,  100,     -5.0,     5.0);
  book<TH1F>("m_jj",                ";m(jj); Events / bin",              500,      0.,    1500);

  book<TH1F>("number_matched_jets", ";# of matched jets ; Events / bin", 11,      -0.5,    10.5);

}

void VBFJetsHists::fill(const VBFTaggerEvent & event){
  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);

  int njets = 0;
  double HT_jets = 0;

  for(const Jet& jet: *event.jets_ak4chs){

    HT_jets += jet.pt();

    int n_matched_jets = 0;
    int jet2_index = -1;
    Jet jet2_matched;
    TLorentzVector jj_matched;

    if (is_etaprod || is_deta || is_mjj) { if(jet.identifier()!= event.identifier_VBFjet1() && jet.identifier()!= event.identifier_VBFjet2()) continue;}

    bool found_match = false;
    for(unsigned index = 0; index < event.jets_ak4chs->size(); index++ ){
      Jet jet2 = event.jets_ak4chs->at(index);
      if (jet2.identifier() == jet.identifier()) continue;

      if (is_etaprod || is_deta || is_mjj) { if(jet2.identifier()!= event.identifier_VBFjet1() && jet2.identifier()!= event.identifier_VBFjet2()) continue;}
      
      TLorentzVector jj = jet.p4() + jet2.p4();
      if (is_etaprod && jet2.eta()*jet.eta()>0) continue;
      if (is_deta    && fabs(jet2.eta()-jet.eta())<1.4) continue;
      if (is_mjj     && jj.M()<200) continue;
      found_match = true;
      n_matched_jets++;
      if (jet2_index<0) {
        jet2_index = index;
        jet2_matched = event.jets_ak4chs->at(index);
        jj_matched = jet.p4() + jet2.p4();
      }
    }

    if (selection != "" && !found_match ) continue;

    njets++;

    hist<TH1F>("jet_pt")->Fill(jet.pt(), weight);
    hist<TH1F>("jet_eta")->Fill(jet.eta(), weight);
    hist<TH1F>("jet_phi")->Fill(jet.phi(), weight);
    hist<TH1F>("jet_m")->Fill(jet.m(), weight);
    hist<TH1F>("jet_e")->Fill(jet.e(), weight);

    hist<TH2F>("jet_pt_vs_eta")->Fill(jet.pt(), jet.eta(), weight);
    hist<TH2F>("jet_eta_vs_phi")->Fill(jet.eta(), jet.phi(), weight);

    hist<TH1F>("jet_area")->Fill(jet.area(), weight);
    hist<TH1F>("jet_score_CSVv2")->Fill(jet.score_CSVv2(), weight);
    hist<TH1F>("jet_score_DeepB")->Fill(jet.score_DeepB(), weight);
    hist<TH1F>("jet_score_DeepFlavB")->Fill(jet.score_DeepFlavB(), weight);
    hist<TH1F>("jet_score_qgl")->Fill(jet.score_qgl(), weight);
    hist<TH1F>("jet_ch_had_efrac")->Fill(jet.ch_had_efrac(), weight);
    hist<TH1F>("jet_ne_em_efrac")->Fill(jet.ne_em_efrac(), weight);
    hist<TH1F>("jet_ne_had_efrac")->Fill(jet.ne_had_efrac(), weight);
    hist<TH1F>("jet_muo_efrac")->Fill(jet.muo_efrac(), weight);
    hist<TH1F>("jet_ele_efrac")->Fill(jet.ele_efrac(), weight);
    hist<TH1F>("jet_pho_efrac")->Fill(jet.pho_efrac(), weight);
    hist<TH1F>("jet_parton_flavor")->Fill(jet.parton_flavor(), weight);
    hist<TH1F>("jet_hadron_flavor")->Fill(jet.hadron_flavor(), weight);
    hist<TH1F>("jet_n_constituents")->Fill(jet.n_constituents(), weight);
    hist<TH1F>("jet_n_muons")->Fill(jet.n_muons(), weight);
    hist<TH1F>("jet_n_electrons")->Fill(jet.n_electrons(), weight);

    if (jet2_index>=0){
      hist<TH1F>("jet1_eta")->Fill(jet.eta(), weight);
      hist<TH1F>("jet2_eta")->Fill(jet2_matched.eta(), weight);
      hist<TH2F>("jet1_eta_vs_jet2")->Fill(jet.eta(), jet2_matched.eta(), weight);
      hist<TH1F>("m_jj")->Fill(jj_matched.M(), weight);
    }

    hist<TH1F>("number_matched_jets")->Fill(n_matched_jets, weight);

  }

  hist<TH1F>("number_of_jets")->Fill(njets, weight);
  hist<TH1F>("HT_jets")->Fill(HT_jets, weight);

}
