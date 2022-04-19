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

#include "LEAF/VBFTagger/include/Utils.h"

#include "LEAF/Analyzer/include/CleaningModules.h"
#include "LEAF/VBFTagger/include/SelectionModules.h"
#include "LEAF/Analyzer/include/NJetSelection.h"
#include "LEAF/Analyzer/include/LumiWeightApplicator.h"


#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/GenLevelStudiesHists.h"
#include "LEAF/VBFTagger/include/GenLevelStudiesPrunedHists.h"
#include "LEAF/VBFTagger/include/GenLevelStudiesJetsHists.h"
#include "LEAF/VBFTagger/include/Utils.h"
#include "LEAF/VBFTagger/include/GenEventMatch.h"

using namespace std;

class GenLevelStudiesTool : public BaseTool {

public:
  // Constructors, destructor
  GenLevelStudiesTool(const Config & cfg);
  ~GenLevelStudiesTool() = default;
  void ProcessDataset(const Config & cfg) override {LoopEvents<GenLevelStudiesTool, VBFTaggerEvent>(cfg, event, *this);};
  virtual bool Process() override;
  void book_histograms();
  void fill_histograms(string);
  void PrintInputs();

private:
  VBFTaggerEvent* event;

  string NameTool = "GenLevelStudiesTool";
  vector<string> histogram_tags = {"input", "cleaner", "nominal"};

  unordered_map<string, string> input_strings;
  unordered_map<string, bool> input_bools;

  // Modules used in the analysis
  unique_ptr<LumiWeightApplicator> lumiweight_applicator;
  unique_ptr<GenJetIDLeptonRemoval> gen_jet_lepton_cleaner;
  // unique_ptr<GenEventMatch> gen_event_match;
  unique_ptr<GenJetCleaner> cleaner_genjet;
  unique_ptr<GenParticleCleaner> cleaner_genpart;
  unique_ptr<GenLJCleaner> cleaner_LJpart;

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
  vector<string> particlesTresh = {"partPt>0.2"};
  vector<string> jetsTresh = {"jetPt>20"};
  vector<string> jetsCut = {"Mjj>200"};
  vector<string> insideLJ = {"", "Inside", "Outside"};
  vector<string> chargeState = {"", "charged", "neutral"};
  for(const string & tag : histogram_tags){
    string mytag;
    // mytag = tag+"_GenLevel"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag));
    // mytag = tag+"_GenLevel_Stable"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1"));
    // mytag = tag+"_GenLevel_Stable_pt<1"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt<1"));
    // mytag = tag+"_GenLevel_Stable_pt>1"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt>1"));
    // mytag = tag+"_GenLevel_Stable_pt<1_selection"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt<1 && gen_selections"));
    // mytag = tag+"_GenLevel_Stable_pt>1_selection"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt>1 && gen_selections"));

    // for (const string & ptresh : particlesTresh) {
    //   for (const string & jtresh : jetsTresh) {
        for (const string& jCut : jetsCut) {
          for (const string & inLJ : insideLJ) {
            for (const string & cha : chargeState) {
              string sel = jCut+"_"+inLJ+"_"+cha; //ptresh+"_"+jtresh+"_"+jCut+"_"+inLJ+"_"+cha;
              mytag = tag+"_GenLevel_"+sel; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, sel));
              cout << mytag <<endl;
            }
          }
        }
    //   }
    // }
    // mytag = tag+"_GenLevel_partPt>0.2"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2"));
    // mytag = tag+"_GenLevel_partPt>0.2_Inside"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && In"));
    // mytag = tag+"_GenLevel_partPt>0.2_Outside"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && Out"));
    // mytag = tag+"_GenLevel_partPt>0.2_charged"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && charge!=0"));
    // mytag = tag+"_GenLevel_partPt>0.2_Inside_charged"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && In && charge!=0"));
    // mytag = tag+"_GenLevel_partPt>0.2_Outside_charged"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && Out && charge!=0"));
    // mytag = tag+"_GenLevel_partPt>0.2_neutral"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && charge==0"));
    // mytag = tag+"_GenLevel_partPt>0.2_Inside_neutral"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && In && charge==0"));
    // mytag = tag+"_GenLevel_partPt>0.2_Outside_neutral"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>0.2 && Out && charge==0"));
    // mytag = tag+"_GenLevel_partPt>1"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1"));
    // mytag = tag+"_GenLevel_partPt>1_Inside"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && In"));
    // mytag = tag+"_GenLevel_partPt>1_Outside"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && Out"));
    // mytag = tag+"_GenLevel_partPt>1_charged"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && charge!=0"));
    // mytag = tag+"_GenLevel_partPt>1_Inside_charged"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && In && charge!=0"));
    // mytag = tag+"_GenLevel_partPt>1_Outside_charged"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && Out && charge!=0"));
    // mytag = tag+"_GenLevel_partPt>1_neutral"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && charge==0"));
    // mytag = tag+"_GenLevel_partPt>1_Inside_neutral"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && In && charge==0"));
    // mytag = tag+"_GenLevel_partPt>1_Outside_neutral"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "partPt>1 && Out && charge==0"));

    // mytag = tag+"_Pruned_GenLevel"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag));
    mytag = tag+"_Pruned_GenLevel_Stable"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1"));
    mytag = tag+"_Pruned_GenLevel_Stable_pt<1"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt<1"));
    mytag = tag+"_Pruned_GenLevel_Stable_pt>1"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt>1"));
    mytag = tag+"_Pruned_GenLevel_Stable_pt<1_selection"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt<1 && gen_selections"));
    mytag = tag+"_Pruned_GenLevel_Stable_pt>1_selection"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt>1 && gen_selections"));
  }
}

void GenLevelStudiesTool::fill_histograms(string tag){
  vector<string> particlesTresh = {"partPt>0.2"};
  vector<string> jetsTresh = {"jetPt>20"};
  vector<string> jetsCut = {"Mjj>200"};
  vector<string> insideLJ = {"", "Inside", "Outside"};
  vector<string> chargeState = {"", "charged", "neutral"};
  string mytag;
  // mytag = tag+"_GenLevel"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt<1"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt>1"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt<1_selection"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt>1_selection"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);

  // for (const string & ptresh : particlesTresh) {
  //   for (const string & jtresh : jetsTresh) {
      for (const string& jCut : jetsCut) {
        for (const string & inLJ : insideLJ) {
          for (const string & cha : chargeState) {
            string sel = jCut+"_"+inLJ+"_"+cha; //ptresh+"_"+jtresh+"_"+jCut+"_"+inLJ+"_"+cha;
            mytag = tag+"_GenLevel_"+sel; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
          }
        }
      }
  //   }
  // }

  // mytag = tag+"_Pruned_GenLevel"; HistFolder<GenLevelStudiesPrunedHists>(mytag)->fill(*event);
  // mytag = tag+"_Pruned_GenLevel_Stable"; HistFolder<GenLevelStudiesPrunedHists>(mytag)->fill(*event);
  // mytag = tag+"_Pruned_GenLevel_Stable_pt<1"; HistFolder<GenLevelStudiesPrunedHists>(mytag)->fill(*event);
  // mytag = tag+"_Pruned_GenLevel_Stable_pt>1"; HistFolder<GenLevelStudiesPrunedHists>(mytag)->fill(*event);
  // mytag = tag+"_Pruned_GenLevel_Stable_pt<1_selection"; HistFolder<GenLevelStudiesPrunedHists>(mytag)->fill(*event);
  // mytag = tag+"_Pruned_GenLevel_Stable_pt>1_selection"; HistFolder<GenLevelStudiesPrunedHists>(mytag)->fill(*event);
}



GenLevelStudiesTool::GenLevelStudiesTool(const Config & cfg) : BaseTool(cfg){

  event = new VBFTaggerEvent();
  event->reset();

  lumiweight_applicator.reset(new LumiWeightApplicator(cfg));

  // gen_event_match.reset(new GenEventMatch(cfg));

  gen_jet_lepton_cleaner.reset(new GenJetIDLeptonRemoval(0.4));

  cleaner_LJpart.reset(new GenLJCleaner(0.4));

  GenID<GenJet> genjet_id = {PtEtaId(20, 100)};
  cleaner_genjet.reset(new GenJetCleaner(genjet_id));

  GenID<GenParticle> gen_particle_id = {PtEtaId(0.2, 100)};
  cleaner_genpart.reset(new GenParticleCleaner(gen_particle_id));

  // MultiID<Jet> jet_id = {PtEtaId(20, 2.5), JetID(JetID::WP_TIGHT), JetPUID(JetPUID::WP_TIGHT)};
  // cleaner_jet.reset(new JetCleaner(jet_id));

  //selection_njets.reset(new NJetSelection(cfg, 4, -1));

  book_histograms();
  PrintInputs();
}




bool GenLevelStudiesTool::Process(){
  cout << "+++ NEW EVENT" << endl;
  // cout << event->genparticles_stable->size() << endl;
  // order all objecs in pT
  // sort_by_pt<GenParticle>(*event->genparticles_visibletaus);
  sort_by_pt<GenParticle>(*event->genparticles_stable);
  sort_by_pt<GenJet>(*event->genjets);
  // sort_by_pt<Jet>(*event->jets);
  // sort_by_pt<Muon>(*event->muons);
  // sort_by_pt<Electron>(*event->electrons);
  // sort_by_pt<Tau>(*event->taus);

  fill_histograms("input");
  lumiweight_applicator->process(*event);
  // fill_histograms("weight");

  gen_jet_lepton_cleaner->process(*event);
  cleaner_LJpart->process(*event);
  cleaner_genjet->process(*event);
  cleaner_genpart->process(*event);
  if (event->genjets->size()==0) return false;
  fill_histograms("cleaner");

  // // run example cleaner
  // cleaner_jet->process(*event);
  // fill_histograms("cleaner");
  //
  // // run example selection
  // if(!selection_njets->passes(*event)) return false;
  // fill_histograms("njets");

  // fill one set of histograms called "nominal", which is necessary for PostAnalyzer scripts
  fill_histograms("nominal");

  // gen_event_match->process(*event);


  // store events passing the full selection for the next step
  return true;
}




REGISTER_TOOL(GenLevelStudiesTool)
