#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>

#include "LEAF/Analyzer/include/BaseTool.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include <sys/stat.h>
#include "LEAF/Analyzer/include/Registry.h"
#include "LEAF/Analyzer/include/JetHists.h"
#include "LEAF/Analyzer/include/MuonHists.h"
#include "LEAF/Analyzer/include/ElectronHists.h"
#include "LEAF/Analyzer/include/TauHists.h"
#include "LEAF/Analyzer/include/JetIds.h"
#include "LEAF/Analyzer/include/MuonIds.h"
#include "LEAF/Analyzer/include/ElectronIds.h"
#include "LEAF/Analyzer/include/TauIds.h"

#include "LEAF/Analyzer/include/NJetSelection.h"


#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/GenParticlesHists.h"
#include "LEAF/VBFTagger/include/PFCandsHists.h"
#include "LEAF/VBFTagger/include/Utils.h"
#include "LEAF/VBFTagger/include/GenEventMatch.h"

using namespace std;

class PFStudiesTool : public BaseTool {

public:
  // Constructors, destructor
  PFStudiesTool(const Config & cfg);
  ~PFStudiesTool() = default;
  void ProcessDataset(const Config & cfg) override {LoopEvents<PFStudiesTool, VBFTaggerEvent>(cfg, event, *this);};
  virtual bool Process() override;
  void book_histograms();
  void fill_histograms(TString);
  void PrintInputs();

private:
  VBFTaggerEvent* event;

  string NameTool = "GenLevelStudiesTool";
  vector<string> histogram_tags = {"input", "cleaner", "njets", "nominal"};

  unordered_map<string, string> input_strings;
  unordered_map<string, bool> input_bools;

  // Modules used in the analysis
  unique_ptr<JetCleaner> cleaner_jet;
  unique_ptr<PFCandCleaner> cleaner_pfcand;


  // Selections used in the analysis
  unique_ptr<NJetSelection> selection_njets;

};


void PFStudiesTool::PrintInputs() {
  cout << blue << string(40, '*' ) << reset << endl;
  PrintHeader(NameTool);
  for (auto x : input_strings) cout << x.first << string( 18-x.first.size(), ' ' ) << x.second << '\n';
  for (auto x : input_bools)   cout << x.first << string( 18-x.first.size(), ' ' ) << BoolToTString(x.second) << '\n';
  cout << blue << string(40, '*' ) << reset << endl;
}

void PFStudiesTool::book_histograms(){
  for(const TString & tag : histogram_tags){
    TString mytag;

    mytag = tag+"_GenParts";      book_HistFolder(mytag, new GenParticlesHists(mytag));
    mytag = tag+"_GenParts_pt>1"; book_HistFolder(mytag, new GenParticlesHists(mytag, "pt>1"));
    mytag = tag+"_PFCands";       book_HistFolder(mytag, new PFCandsHists(mytag));
    mytag = tag+"_PFCands_pt>1";  book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1"));
    mytag = tag+"_Jets";          book_HistFolder(mytag, new JetHists(mytag));
  }
}

void PFStudiesTool::fill_histograms(TString tag){
  TString mytag;
  mytag = tag+"_GenParts";      HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts_pt>1"; HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands";       HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_pt>1";  HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_Jets";  HistFolder<JetHists>(mytag)->fill(*event);
}



PFStudiesTool::PFStudiesTool(const Config & cfg) : BaseTool(cfg){

  event = new VBFTaggerEvent();
  event->reset();

  MultiID<Jet> jet_id = {PtEtaId(20, 4.7), JetID(JetID::WP_TIGHT), JetPUID(JetPUID::WP_TIGHT)};
  cleaner_jet.reset(new JetCleaner(jet_id));

  MultiID<PFCandidate> pfcand_id = {PtEtaId(1, 5.2)};
  cleaner_pfcand.reset(new PFCandCleaner(pfcand_id));

  selection_njets.reset(new NJetSelection(cfg, 2, -1));

  book_histograms();
  PrintInputs();
}




bool PFStudiesTool::Process(){
  // cout << "+++ NEW EVENT" << endl;

  // order all objecs in pT
  // sort_by_pt<GenParticle>(*event->genparticles_visibletaus);
  // sort_by_pt<GenParticle>(*event->genparticles_all);
  // sort_by_pt<GenJet>(*event->genjets);
  // sort_by_pt<Jet>(*event->jets_ak4chs);
  // sort_by_pt<PFCandidate>(*event->pfcands);
  fill_histograms("input");


  // run example cleaner
  cleaner_jet->process(*event);
  cleaner_pfcand->process(*event);
  fill_histograms("cleaner");

  // run example selection
  if(!selection_njets->passes(*event)) return false;
  fill_histograms("njets");

  // fill one set of histograms called "nominal", which is necessary for PostAnalyzer scripts
  fill_histograms("nominal");

  // store events passing the full selection for the next step
  return true;
}




REGISTER_TOOL(PFStudiesTool)
