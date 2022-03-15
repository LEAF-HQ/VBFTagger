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
      book<TH1F>(Title + "ngenjets" + tresh + na, Axis + ";N_{genjets} w/ Pt > " + tresh + "GeV" + na + "; Events / bin", 26, -0.5, 25.5);
    }
    book<TH1F>(Title + "jetsPT" + na, ";P_t"+na+";Number of jets", 251, -0.5, 250.5);
    book<TH1F>(Title + "jetsEta" + na, ";#Eta"+na+"; Number of jets", 100, -7, 7);
    book<TH1F>(Title + "jetsPhi" + na, ";#Phi"+na+"; Number of jets", 50, -4, 4);
    book<TH1F>(Title + "jetsMass" + na, ";Mass (GeV)"+na+"; Number of jets", 51, -0.5, 50.5);
    book<TH1F>(Title + "jetsdR" + na, ";#DeltaR (genjets, genparticles)"+na+";Events / bin", 100, 0, 5);
    book<TH1F>(Title + "jetsHt" + na, ";#H_t"+na+";Events / bin", 1001, -0.5, 1000.5);
    book<TH1F>(Title + "deltaEtaLeadingJets" + na, ";|#Delta #Eta|_{leading jets}"+na+";Events / bin", 1001, -0.5, 1000.5);
  }
  book<TH1F>("dijetsMass", "; Dijets mass (GeV); Events", 1001, -0.5, 1000.5);
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

  GenJet j1 = event.genjets->at(0);
  GenJet j2 = event.genjets->at(1);
  double dEta = deltaEta(j1, j2);
  TLorentzVector v = j1.p4() + j2.p4();
  hist<TH1F>(Title + "deltaEtaLeadingJets")->Fill(dEta, weight);
  hist<TH1F>("dijetsMass")->Fill(v.M(), weight);

  // looping over all jets from the event
  for(size_t i=0; i<event.genjets->size(); i++){
    GenJet j = event.genjets->at(i);

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
    int leptonFlag = 0;
    for (size_t k=0; k<event.genparticles_all->size(); k++) {
      GenParticle gp = event.genparticles_all->at(k);

      if (gp.status()!=1 || !gp.get_statusflag(GenParticle::isLastCopy)) continue;

      double dR = deltaR(j, gp);
      hist<TH1F>(Title + "jetsdR")->Fill(dR, weight);

      if (abs(gp.pdgid()) <= 11 || abs(gp.pdgid()) >= 18) {
          double dR_filter = deltaR(j, gp);
          if (dR_filter < 0.4) {
            leptonFlag = 1;
            break;
          }
      }
    }
    if (leptonFlag == 0) {
      for (size_t u=0; u<threshold.size(); u++) {
        if (j.pt() > threshold[u]) {
          treshsizeFilter[u] += 1;
        }
      }
      htLeptonFilter += j.pt();
      hist<TH1F>(Title + "jetsPT& lepton filter")->Fill(j.pt(), weight);
      hist<TH1F>(Title + "jetsEta& lepton filter")->Fill(j.eta(), weight);
      hist<TH1F>(Title + "jetsPhi& lepton filter")->Fill(j.phi(), weight);
      hist<TH1F>(Title + "jetsMass& lepton filter")->Fill(j.m(), weight);
    }
  }
  for (size_t u=0; u<threshold.size(); u++) {
    hist<TH1F>(Title + "ngenjets" + threshold[u])->Fill(treshsize[u], weight);
    hist<TH1F>(Title + "ngenjets" + threshold[u] + "& lepton filter")->Fill(treshsizeFilter[u], weight);
  }
  hist<TH1F>(Title + "jetsHt")->Fill(ht, weight);
  hist<TH1F>(Title + "jetsHt& lepton filter")->Fill(htLeptonFilter, weight);
}
