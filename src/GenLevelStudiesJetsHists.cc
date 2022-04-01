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
TString Title = "";
TString Axis = "";


GenLevelStudiesJetsHists::GenLevelStudiesJetsHists(TString dir_) : BaseHists(dir_){


  // MultiID<GenJet> genjet_id = {PtEtaId(10, 5.2), GenJetIDLeptonRemoval(0.4)};
  // cleaner_genjet.reset(new GenJetCleaner(genjet_id));

  book<TH1F>("sumweights",      ";sum of event weights; Events / bin",      1,  0.5, 1.5);
  for (double tresh : threshold) {
    book<TH1F>(Title + "ngenjets" + tresh, Axis + ";N_{genjets} w/ P_{t} > " + tresh + "GeV; Events / bin", 21, -0.5, 20.5);
  }
    book<TH1F>(Title + "jetsPT", ";P_{t};Number of jets", 251, -0.5, 500.5);
    book<TH1F>(Title + "jetsEta" , ";#eta; Number of jets", 100, -7, 7);
    book<TH1F>(Title + "jetsPhi" , ";#phi; Number of jets", 50, -4, 4);
    book<TH1F>(Title + "jetsMass" , ";Mass (GeV); Number of jets", 101, -0.5, 50.5);
    // book<TH1F>(Title + "jetsdR" + na, ";#DeltaR (genjets, genparticles)"+na+";Events / bin", 101, -0.5, 20.5);
    book<TH1F>(Title + "jetsHt" , ";H_{t};Events / bin", 201, -0.5, 1000.5);
    book<TH1F>(Title + "deltaEtaLeadingJets" , ";|#Delta #eta|_{leading jets};Events / bin", 71, -0.5, 15.5);
    book<TH1F>(Title + "dijetsMass" , "; 2 leading jets mass (GeV); Events", 301, -0.5, 2000.5);

}

void GenLevelStudiesJetsHists::fill(const RecoEvent & event) {

  // cleaner_genjet->process(*event);
  // removing the events containing taus
  for (const GenParticle& t: *event.genparticles_stable) {if (t.pdgid() == 15) return;}

  vector<GenJet> nJets0, nJets10, nJets20, nJets30;

  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);

  double ht = 0.;

  if (event.genjets->size() > 1) {
      GenJet j1 = event.genjets->at(0);
      GenJet j2 = event.genjets->at(1);
      double dEta = deltaEta(j1, j2);
      TLorentzVector v = j1.p4() + j2.p4();
      hist<TH1F>(Title + "deltaEtaLeadingJets")->Fill(dEta, weight);
      hist<TH1F>("dijetsMass")->Fill(v.M(), weight);
  }

  for (const GenJet& j: *event.genjets) {

    nJets0.push_back(j);

    if (j.pt() < 10) continue;

    nJets10.push_back(j);


    if (j.pt() < 20) continue;

    ht += j.pt();

    nJets20.push_back(j);

    // filling basic histograms
    hist<TH1F>(Title + "jetsPT")->Fill(j.pt(), weight);
    hist<TH1F>(Title + "jetsEta")->Fill(j.eta(), weight);
    hist<TH1F>(Title + "jetsPhi")->Fill(j.phi(), weight);
    hist<TH1F>(Title + "jetsMass")->Fill(j.m(), weight);


    if (j.pt() < 30) continue;

    nJets30.push_back(j);


  }
  hist<TH1F>("ngenjets0")->Fill(nJets0.size(), weight);
  hist<TH1F>("ngenjets10")->Fill(nJets10.size(), weight);
  hist<TH1F>("ngenjets20")->Fill(nJets20.size(), weight);
  hist<TH1F>("ngenjets30")->Fill(nJets30.size(), weight);

  hist<TH1F>("jetsHt")->Fill(ht, weight);
}
