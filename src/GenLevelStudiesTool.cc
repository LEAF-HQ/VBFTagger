#include <iostream>
#include <string.h>
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
#include "LEAF/VBFTagger/include/GenLevelStudiesHists.h"
#include "LEAF/VBFTagger/include/Utils.h"

using namespace std;

class GenLevelStudiesTool : public BaseTool {

public:
  // Constructors, destructor
  GenLevelStudiesTool(const Config & cfg);
  ~GenLevelStudiesTool() = default;
  void ProcessDataset(const Config & cfg) override {LoopEvents<GenLevelStudiesTool, RecoEvent>(cfg, event, *this);};
  virtual bool Process() override;
  void book_histograms();
  void fill_histograms(string);
  void PrintInputs();

private:
  RecoEvent* event;

  string NameTool = "GenLevelStudiesTool";
  vector<string> histogram_tags = {"input", "cleaner", "njets", "nominal"};

  unordered_map<string, string> input_strings;
  unordered_map<string, bool> input_bools;

  // Modules used in the analysis
  unique_ptr<JetCleaner> cleaner_jet;

  // Selections used in the analysis
  unique_ptr<NJetSelection> selection_njets;
};


void GenLevelStudiesTool::PrintInputs() {
  cout << blue << string(40, '*' ) << reset << endl;
  PrintHeader(NameTool);
  for (auto x : input_strings) cout << x.first << string( 18-x.first.size(), ' ' ) << x.second << '\n';
  for (auto x : input_bools)   cout << x.first << string( 18-x.first.size(), ' ' ) << BoolToTString(x.second) << '\n';
  cout << blue << string(40, '*' ) << reset << endl;
}

void GenLevelStudiesTool::book_histograms(){
  for(const string & tag : histogram_tags){
    string mytag;
    mytag = tag+"_General"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag));
    mytag = tag+"_Jets";    book_HistFolder(mytag, new JetHists(mytag));
  }
}

void GenLevelStudiesTool::fill_histograms(string tag){
  string mytag;
  mytag = tag+"_General"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  mytag = tag+"_Jets";    HistFolder<JetHists>(mytag)->fill(*event);
}



GenLevelStudiesTool::GenLevelStudiesTool(const Config & cfg) : BaseTool(cfg){

  event = new RecoEvent();
  event->reset();

  MultiID<Jet> jet_id = {PtEtaId(20, 2.5), JetID(JetID::WP_TIGHT), JetPUID(JetPUID::WP_TIGHT)};
  cleaner_jet.reset(new JetCleaner(jet_id));

  selection_njets.reset(new NJetSelection(cfg, 4, -1));

  book_histograms();
  PrintInputs();
}




bool GenLevelStudiesTool::Process(){
  // cout << "+++ NEW EVENT" << endl;

  // order all objecs in pT
  sort_by_pt<GenParticle>(*event->genparticles_visibletaus);
  sort_by_pt<GenParticle>(*event->genparticles_all);
  sort_by_pt<GenJet>(*event->genjets);
  sort_by_pt<Jet>(*event->jets);
  sort_by_pt<Muon>(*event->muons);
  sort_by_pt<Electron>(*event->electrons);
  sort_by_pt<Tau>(*event->taus);
  fill_histograms("input");

  // run example cleaner
  cleaner_jet->process(*event);
  fill_histograms("cleaner");

  // run example selection
  if(!selection_njets->passes(*event)) return false;
  fill_histograms("njets");

  // fill one set of histograms called "nominal", which is necessary for PostAnalyzer scripts
  fill_histograms("nominal");

  // store events passing the full selection for the next step
  return true;
}




REGISTER_TOOL(GenLevelStudiesTool)
