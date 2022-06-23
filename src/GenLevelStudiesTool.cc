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
#include "LEAF/Analyzer/include/NTauSelection.h"
#include "LEAF/Analyzer/include/LumiWeightApplicator.h"


#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/Utils.h"
#include "LEAF/VBFTagger/include/GenEventMatch.h"
#include "LEAF/VBFTagger/include/VBFSelections.h"
#include "LEAF/VBFTagger/include/GenParticlesHists.h"
#include "LEAF/VBFTagger/include/VBFGenJetsHists.h"
#include "LEAF/VBFTagger/include/PFCandsHists.h"
#include "LEAF/VBFTagger/include/VBFJetsHists.h"
#include "LEAF/VBFTagger/include/VBFEventHists.h"
#include "LEAF/VBFTagger/include/LeptonEfficiencyHists.h"

using namespace std;

class GenLevelStudiesTool : public BaseTool {

public:
  // Constructors, destructor
  GenLevelStudiesTool(const Config & cfg);
  ~GenLevelStudiesTool() = default;
  void ProcessDataset(const Config & cfg) override {LoopEvents<GenLevelStudiesTool, VBFTaggerEvent>(cfg, event, *this);};
  virtual bool Process() override;
  void book_histograms();
  void fill_histograms(TString);
  void PrintInputs();
  void sort_objects();
  void clean_objects();
  bool select_Nobjects();

private:
  VBFTaggerEvent* event;

  string NameTool = "GenLevelStudiesTool";
  vector<string> histogram_tags = {"input", "phasespace", "nominal"};

  unordered_map<string, string> input_strings;
  unordered_map<string, bool> input_bools;

  // Modules used in the analysis
  unique_ptr<GenJetCleaner> cleaner_genjet;
  unique_ptr<GenEventMatch> genEvent_match;
  unique_ptr<LumiWeightApplicator> lumiweight_applicator;

  // Selections used in the analysis
  unique_ptr<NJetSelection> njets_selection;
  unique_ptr<GenLeptonPhaseSpaceSelection> genLeptonPhaseSpace_selection;
};


void GenLevelStudiesTool::PrintInputs() {
  cout << blue << string(40, '*' ) << reset << endl;
  PrintHeader(NameTool);
  for (auto x : input_strings) cout << x.first << string( 18-x.first.size(), ' ' ) << x.second << '\n';
  for (auto x : input_bools)   cout << x.first << string( 18-x.first.size(), ' ' ) << BoolToTString(x.second) << '\n';
  cout << blue << string(40, '*' ) << reset << endl;
}

void GenLevelStudiesTool::book_histograms(){
  for(const TString & tag : histogram_tags){
    TString mytag;
    mytag = tag+"_VBFGenJets";                  book_HistFolder(mytag, new VBFGenJetsHists(mytag));
    mytag = tag+"_GenParts";                    book_HistFolder(mytag, new GenParticlesHists(mytag, "", false));
    if (tag == "input" || tag == "notau" || tag == "phasespace" || tag == "VBFSelection") continue;
    mytag = tag+"_GenParts_stable";             book_HistFolder(mytag, new GenParticlesHists(mytag, ""));
    mytag = tag+"_GenParts_pt200MeV";           book_HistFolder(mytag, new GenParticlesHists(mytag, "pt>0.2"));
    mytag = tag+"_GenParts_pt1GeV";             book_HistFolder(mytag, new GenParticlesHists(mytag, "pt>1"));
  }
}

void GenLevelStudiesTool::fill_histograms(TString tag){
  TString mytag;
  mytag = tag+"_VBFGenJets";        HistFolder<VBFGenJetsHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts";          HistFolder<GenParticlesHists>(mytag)->fill(*event);
  if (tag == "input" || tag == "notau" || tag == "phasespace" || tag == "VBFSelection") return;
  mytag = tag+"_GenParts_stable";   HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts_pt200MeV"; HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts_pt1GeV";   HistFolder<GenParticlesHists>(mytag)->fill(*event);
}



GenLevelStudiesTool::GenLevelStudiesTool(const Config & cfg) : BaseTool(cfg){

  event = new VBFTaggerEvent();
  event->reset();

  GenID<GenJet> genjet_id = {PtEtaId(20, 5.2)};
  cleaner_genjet.reset(new GenJetCleaner(genjet_id));

  genEvent_match.reset(new GenEventMatch(cfg));

  lumiweight_applicator.reset(new LumiWeightApplicator(cfg));

  genLeptonPhaseSpace_selection.reset(new GenLeptonPhaseSpaceSelection(cfg));
  njets_selection.reset(new NJetSelection(cfg, 2, -1));

  book_histograms();
  PrintInputs();
}


void GenLevelStudiesTool::sort_objects(){
  sort_by_pt<GenParticle>(*event->genparticles_stable);
  sort_by_pt<GenJet>(*event->genjets);
  sort_by_pt<Jet>(*event->jets_ak4chs);
}

void GenLevelStudiesTool::clean_objects(){
  cleaner_genjet->process(*event);
}

bool GenLevelStudiesTool::select_Nobjects(){
  if (event->genjets->size()<2) return false;
  if(!njets_selection->passes(*event)) return false;
  return true;
}

bool GenLevelStudiesTool::Process(){

  sort_objects();
  fill_histograms("input");

  lumiweight_applicator->process(*event);

  clean_objects();
  if (!select_Nobjects()) return false;
  genEvent_match->process(*event);
  fill_histograms("phasespace");
  if(!genLeptonPhaseSpace_selection->passes(*event)) return false;

  // fill one set of histograms called "nominal", which is necessary for PostAnalyzer scripts
  fill_histograms("nominal");
  // store events passing the full selection for the next step
  return true;
}




REGISTER_TOOL(GenLevelStudiesTool)
