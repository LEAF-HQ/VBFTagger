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
#include <iostream>
#include <sys/stat.h>

using namespace std;

GenLevelStudiesJetsHists::GenLevelStudiesJetsHists(TString dir_) : BaseHists(dir_){
  hsumweights = book<TH1F>("sumweights",      ";sum of event weights; Events / bin",      1,  0.5, 1.5);
  hngenjets = book<TH1F>("ngenjets", ";N_{genjets}; Events / bin", 16, -0.5, 15.5);
  hgenjetpt = book<TH1F>("jetsPT", ";Pt;Number of particles", 1001, -0.5, 1100.5);
  hgenjeteta = book<TH1F>("jetsEta", ";Eta; Number of particles", 100, -7, 7);
  hgenjetphi = book<TH1F>("jetsPhi", ";Phi; Number of particles", 50, -4, 4);
  hgenjetm = book<TH1F>("jetsMass", ";Mass; Number of particles", 141, -0.5, 140.5);
  hgenjetR = book<TH1F>("jetsdR", ";#DeltaR_{min} (genjets, genparticles);Events / bin", 100, 0, 5);
  hgenjetR_ele = book<TH1F>("jetsdR_ele", ";#DeltaR_{min} (genjets, genele);Events / bin", 100, 0, 5);
  hgenjetR_mu = book<TH1F>("jetsdR_mu", ";#DeltaR_{min} (genjets, genmu);Events / bin", 100, 0, 5);
}

void GenLevelStudiesJetsHists::fill(const RecoEvent & event){
  double weight = event.weight;
  hsumweights->Fill(1, weight);

  for(size_t i=0; i<event.genjets->size(); i++){
    GenJet j = event.genjets->at(i);
    double dR = pow(10,15);
    double dR_ele = pow(10,15);
    double dR_mu = pow(10,15);

    hngenjets->Fill(event.genjets->size(), weight);
    hgenjetpt->Fill(j.pt(), weight);
    hgenjeteta->Fill(j.eta(), weight);
    hgenjetphi->Fill(j.phi(), weight);
    hgenjetm->Fill(j.m(), weight);
    for (size_t k=0; k<event.genparticles_all->size(); k++) {
      GenParticle gp = event.genparticles_all->at(k);
      dR = min(dR, deltaR(j, gp));
      if (abs(gp.pdgid()) == 11) {
          dR_ele = min(dR_ele, deltaR(j, gp));
      }
      if (abs(gp.pdgid()) == 13) {
          dR_mu = min(dR_mu, deltaR(j, gp));
      }
    }
    hgenjetR->Fill(dR, weight);
    hgenjetR_ele->Fill(dR_ele, weight);
    hgenjetR_mu->Fill(dR_mu, weight);


  }
}
