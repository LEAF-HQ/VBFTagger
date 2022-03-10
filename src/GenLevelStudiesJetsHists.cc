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
  book<TH1F>("sumweights",      ";sum of event weights; Events / bin",      1,  0.5, 1.5);

  book<TH1F>("jetsPT", ";Pt;Number of particles", 1001, -0.5, 1100.5);
  book<TH1F>("jetsEta", ";Eta; Number of particles", 100, -7, 7);
  book<TH1F>("jetsPhi", ";Phi; Number of particles", 50, -4, 4);
  book<TH1F>("jetsMass", ";Mass; Number of particles", 141, -0.5, 140.5);
}

void GenLevelStudiesJetsHists::fill(const RecoEvent & event){
  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);

  for(size_t i=0; i<event.genjets->size(); i++){
    GenJet j = event.genjets->at(i);

    hist<TH1F>("jetsPT")->Fill(j.pt());
    hist<TH1F>("jetsEta")->Fill(j.eta());
    hist<TH1F>("jetsPhi")->Fill(j.phi());
    hist<TH1F>("jetsMass")->Fill(j.m());

  }
}
