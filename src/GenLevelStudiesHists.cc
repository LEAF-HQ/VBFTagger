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

  book_1D<TH1F>("sumweights",      ";sum of event weights; Events / bin",      1,  0.5, 1.5);
  book_1D<TH1F>("genmet",          ";gen. p_{T}^{miss} [GeV]; Events / bin", 100,    0, 1000);
  book_1D<TH1F>("genmet_phi",      ";#phi(gen. p_{T}^{miss}); Events / bin",  60, -3.5, 3.5);

  book_1D<TH1F>("geninfoid1",      ";ID of initial state 1; Events / bin",    11, -5.5, 5.5);
  book_1D<TH1F>("geninfoid2",      ";ID of initial state 2; Events / bin",    11, -5.5, 5.5);
  book_1D<TH1F>("geninfox1",       ";x of initial state 1; Events / bin",     50,    0, 1);
  book_1D<TH1F>("geninfox2",       ";x of initial state 2; Events / bin",     50,    0, 1);
  book_1D<TH1F>("geninfoscalepdf", ";PDF scale; Events / bin",               200,    0, 3000);

}

void GenLevelStudiesHists::fill(const RecoEvent & event){
  double weight = event.weight;
  fill_1D("sumweights", 1, weight);

  fill_1D("genmet",     event.genmet->pt(), weight);
  fill_1D("genmet_phi", event.genmet->phi(), weight);

  fill_1D("geninfoid1",      event.geninfo->id1(), weight);
  fill_1D("geninfoid2",      event.geninfo->id2(), weight);
  fill_1D("geninfox1",       event.geninfo->x1(), weight);
  fill_1D("geninfox2",       event.geninfo->x2(), weight);
  fill_1D("geninfoscalepdf", event.geninfo->scale_pdf(), weight);

}
