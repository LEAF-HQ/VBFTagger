#include "LEAF/VBFTagger/include/GenLevelStudiesHists.h"
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

GenLevelStudiesHists::GenLevelStudiesHists(TString dir_) : BaseHists(dir_){

  book<TH1F>("sumweights",      ";sum of event weights; Events / bin",      1,  0.5, 1.5);

  book<TH1F>("geninfoscalepdf", ";PDF scale; Events / bin",               200,    0, 3000);
  book<TH1F>("geninfoid1",      ";ID of initial state 1; Events / bin",    27, -5.5, 21.5);
  book<TH1F>("geninfoid2",      ";ID of initial state 2; Events / bin",    27, -5.5, 21.5);
  book<TH1F>("geninfox1",       ";x of initial state 1; Events / bin",     50,    0, 1);
  book<TH1F>("geninfox2",       ";x of initial state 2; Events / bin",     50,    0, 1);
  book<TH1F>("geninfoxg",       ";x of all gluons; Events / bin",          50,    0, 1);
  book<TH1F>("geninfoxlight",   ";x of all light quarks; Events / bin",    50,    0, 1);

  book<TH1F>("genmet",          ";gen. p_{T}^{miss} [GeV]; Events / bin", 100,    0, 1000);
  book<TH1F>("genmet_phi",      ";#phi(gen. p_{T}^{miss}); Events / bin",  60, -3.5, 3.5);
  book<TH2D>("genmet_phi_pt",   ";metphi;pt; Events / bin", 60, -3.5, 3.5, 100,    0, 1000);

  book<TH1F>("NumberOfParticles","; Number of particles ; Events",100, 0, 350);
  book<TH1F>("NumberOfChargedParticles","; Number of charged particles ; Events",100, 0, 200);


}

void GenLevelStudiesHists::fill(const RecoEvent & event){


  double weight = event.weight;
  int id1 = event.geninfo->id1();
  int id2 = event.geninfo->id1();
  hist<TH1F>("sumweights")->Fill(1, weight);

  hist<TH1F>("geninfoscalepdf")->Fill(event.geninfo->scale_pdf(), weight);
  hist<TH1F>("geninfoid1")->Fill(id1, weight);
  hist<TH1F>("geninfoid2")->Fill(id2, weight);
  hist<TH1F>("geninfox1")->Fill(event.geninfo->x1(), weight);
  hist<TH1F>("geninfox2")->Fill(event.geninfo->x2(), weight);


  if(abs(id1) == 21) {
    hist<TH1F>("geninfoxg")->Fill(event.geninfo->x1(), weight);
    hist<TH1F>("geninfoxg")->Fill(event.geninfo->x2(), weight);
  }
  if(abs(id1) >= 1 && abs(id1) <= 3) {
    hist<TH1F>("geninfoxlight")->Fill(event.geninfo->x1(), weight);
    hist<TH1F>("geninfoxlight")->Fill(event.geninfo->x2(), weight);
  }

  hist<TH1F>("genmet")->Fill(event.genmet->pt(), weight);
  hist<TH1F>("genmet_phi")->Fill(event.genmet->phi(), weight);
  hist<TH2D>("genmet_phi_pt")->Fill(event.genmet->phi(), event.genmet->pt(), weight);

  hist<TH1F>("NumberOfParticles")->Fill(event.genparticles_all->size(),weight);

  int NChargedParticles = 0;                                      // Initialise counter
  for(size_t i=0; i<event.genparticles_all->size(); i++){
    GenParticle p = event.genparticles_all->at(i);
    if(abs(p.charge()) == 1) {
      //hist<TH1F>("NumberOfChargedParticles")->Fill(event.genparticles_all->size(), weight);
      NChargedParticles += 1;                                     // If particle is charged, counter +1
    }
  }
  hist<TH1F>("NumberOfChargedParticles")->Fill(NChargedParticles, weight);



}
