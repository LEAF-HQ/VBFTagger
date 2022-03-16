#include "LEAF/VBFTagger/include/GenLevelStudiesJetsHists.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/useful_functions.h"

#include <TH1F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TString.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

vector<double> threshold = {0., 10., 20., 30.};
vector<TString> name = {"", "& lepton filter"};
TString Title = "";
TString Axis = "";

GenLevelStudiesJetsHists::GenLevelStudiesJetsHists(TString dir_) : BaseHists(dir_){
  book<TH1F>("sumweights",      ";sum of event weights; Events / bin",      1,  0.5, 1.5);
  for (TString na : name) {
    for (double tresh : threshold) {
      book<TH1F>(Title + "ngenjets" + tresh + na, Axis + ";N_{genjets} w/ P_{t} > " + tresh + "GeV" + na + "; Events / bin", 21, -0.5, 20.5);
    }
    book<TH1F>(Title + "jetsPT" + na, ";P_{t}"+na+";Number of jets", 201, -0.5, 200.5);
    book<TH1F>(Title + "jetsEta" + na, ";#eta"+na+"; Number of jets", 100, -7, 7);
    book<TH1F>(Title + "jetsPhi" + na, ";#phi"+na+"; Number of jets", 50, -4, 4);
    book<TH1F>(Title + "jetsMass" + na, ";Mass (GeV)"+na+"; Number of jets", 41, -0.5, 40.5);
    book<TH1F>(Title + "jetsdR" + na, ";#DeltaR (genjets, genparticles)"+na+";Events / bin", 100, 0, 10);
    book<TH1F>(Title + "jetsHt" + na, ";H_{t}"+na+";Events / bin", 401, -0.5, 400.5);
    book<TH1F>(Title + "deltaEtaLeadingJets" + na, ";|#Delta #eta|_{leading jets}"+na+";Events / bin", 11, -0.5, 10.5);
    book<TH1F>(Title + "dijetsMass" + na, "; 2 leading jets mass (GeV)"+na+"; Events", 301, -0.5, 300.5);
  }
  }

void GenLevelStudiesJetsHists::fill(const RecoEvent & event){

  // size of the jets with treshold
  vector<int> treshsize = {0, 0, 0, 0};
  vector<int> treshsizeFilter = {0, 0, 0, 0};

  // removing the events containing taus
  for (size_t k=0; k<event.genparticles_all->size(); k++) {
    GenParticle t = event.genparticles_all->at(k);
    if (t.pdgid() == 15) return;
  }

  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);

  // introdicing the scalar sum of the Pt of the jets
  double ht = 0.;
  double htLeptonFilter = 0.;

  if (event.genjets->size() > 1) {
    GenJet j1 = event.genjets->at(0);
    GenJet j2 = event.genjets->at(1);
    double dEta = deltaEta(j1, j2);
    TLorentzVector v = j1.p4() + j2.p4();
    hist<TH1F>(Title + "deltaEtaLeadingJets")->Fill(dEta, weight);
    hist<TH1F>("dijetsMass")->Fill(v.M(), weight);
  }

  // looping over all jets from the event
  for(size_t i=0; i<event.genjets->size(); i++){
    GenJet j = event.genjets->at(i);
    cout <<"loop over jets "<<"size: "<<event.genjets->size()<< "   i: "<<i <<endl;

    ht += j.pt();

    // njet += 1 if pt > treshold
    for (size_t u=0; u<threshold.size(); u++) {
      if (j.pt() > threshold[u]) {
        treshsize[u] += 1;
      }
    }

    // filling basic histograms
    hist<TH1F>(Title + "jetsPT")->Fill(j.pt(), weight);
    hist<TH1F>(Title + "jetsEta")->Fill(j.eta(), weight);
    hist<TH1F>(Title + "jetsPhi")->Fill(j.phi(), weight);
    hist<TH1F>(Title + "jetsMass")->Fill(j.m(), weight);

    // loop over all the gen particles to remove leptons from the jets using dR < 0.4
    int leptonFlagJet1 = 0;
    int leptonFlagJet2 = 0;
    for (size_t k=0; k<event.genparticles_all->size(); k++) {
      GenParticle gp = event.genparticles_all->at(k);

      if (gp.status()!=1 || !gp.get_statusflag(GenParticle::isLastCopy)) continue;

      double dR = deltaR(j, gp);
      hist<TH1F>(Title + "jetsdR")->Fill(dR, weight);

      if (abs(gp.pdgid()) >= 11 && abs(gp.pdgid()) <= 18) {
          if (dR < 0.4) {
            leptonFlagJet1 = 1;
          }
          if (i == 0 && event.genjets->size() > 1) {
            GenJet jf = event.genjets->at(i+1);
            double dR_filter2 = deltaR(jf, gp);
            if (dR_filter2 < 0.4) {
              leptonFlagJet2 = 1;
            }
          }
      }
    }
    if (leptonFlagJet1 == 0) {
      for (size_t u=0; u<threshold.size(); u++) {
        if (j.pt() > threshold[u]) {
          treshsizeFilter[u] += 1;
        }
      }
      if (i == 0 && leptonFlagJet2 == 0 && event.genjets->size()>1) {
        GenJet jf1 = event.genjets->at(i);
        GenJet jf2 = event.genjets->at(i+1);
        double dEtaf = deltaEta(jf1, jf2);
        TLorentzVector vf = jf1.p4() + jf2.p4();
        hist<TH1F>(Title + "deltaEtaLeadingJets& lepton filter")->Fill(dEtaf, weight);
        hist<TH1F>("dijetsMass& lepton filter")->Fill(vf.M(), weight);
      }
      htLeptonFilter += j.pt();
      hist<TH1F>(Title + "jetsPT& lepton filter")->Fill(j.pt(), weight);
      hist<TH1F>(Title + "jetsEta& lepton filter")->Fill(j.eta(), weight);
      hist<TH1F>(Title + "jetsPhi& lepton filter")->Fill(j.phi(), weight);
      hist<TH1F>(Title + "jetsMass& lepton filter")->Fill(j.m(), weight);
      hist<TH1F>(Title + "jetsdR& lepton filter")->Fill(dR, weight);
    }
  }
  for (size_t u=0; u<threshold.size(); u++) {
    hist<TH1F>(Title + "ngenjets" + threshold[u])->Fill(treshsize[u], weight);
    hist<TH1F>(Title + "ngenjets" + threshold[u] + "& lepton filter")->Fill(treshsizeFilter[u], weight);
  }
  hist<TH1F>(Title + "jetsHt")->Fill(ht, weight);
  hist<TH1F>(Title + "jetsHt& lepton filter")->Fill(htLeptonFilter, weight);
}
