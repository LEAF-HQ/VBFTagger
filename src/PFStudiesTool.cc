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
  void sort_objects();
  void clean_objects();
  bool select_Nobjects();
  void study_LeptonID();

private:
  VBFTaggerEvent* event;

  string NameTool = "GenLevelStudiesTool";
  vector<string> histogram_tags = {"input", "weights", "notau_Selection", "nogentau_Selection",
  "NObject_Selection", "phasespace_Selection", "Higgs4LeptonsReco", "Higgs4Leptons_Selection",
  "VBF_Selection", "nominal"};

  unordered_map<string, string> input_strings;
  unordered_map<string, bool> input_bools;

  // Modules used in the analysis
  unique_ptr<GenJetCleaner> cleaner_genjet;
  unique_ptr<GenEventMatch> genEvent_match;
  unique_ptr<LumiWeightApplicator> lumiweight_applicator;

  std::vector<unique_ptr<MuonCleaner>> muo_cleaners;
  std::vector<unique_ptr<ElectronCleaner>> ele_cleaners;

  unique_ptr<MuonCleaner> muo_cleaner;
  unique_ptr<ElectronCleaner> ele_cleaner;
  unique_ptr<TauCleaner> tau_cleaner;
  unique_ptr<JetCleaner> jet_cleaner;
  unique_ptr<PFCandCleaner> pfcand_cleaner;

  unique_ptr<Higgs4LeptonsFinder> Higgs4Leptons_finder;

  unique_ptr<VBFJetDefinition> VBFJet_definition_low_pt;
  unique_ptr<VBFJetDefinition> VBFJet_definition;

  unique_ptr<PFUESelector> PFUE_selector;

  // Selections used in the analysis
  unique_ptr<NJetSelection> njets_selection;
  unique_ptr<NTauSelection> ntaus_selection;
  unique_ptr<NoGenTauSelection> nogentau_selection;
  unique_ptr<GenLeptonPhaseSpaceSelection> genLeptonPhaseSpace_selection;

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
    mytag = tag+"_VBFGenJets";                  book_HistFolder(mytag, new VBFGenJetsHists(mytag));
    mytag = tag+"_GenParts";                    book_HistFolder(mytag, new GenParticlesHists(mytag, "", false));
    if (tag == "input" || tag == "weights" || tag == "notau" || tag == "nogentau" || tag == "phasespace") continue;
    // mytag = tag+"_GenParts_stable";             book_HistFolder(mytag, new GenParticlesHists(mytag, ""));
    // mytag = tag+"_GenParts_pt200MeV";           book_HistFolder(mytag, new GenParticlesHists(mytag, "pt>0.2"));
    // // mytag = tag+"_GenParts_pt1GeV";             book_HistFolder(mytag, new GenParticlesHists(mytag, "pt>1"));
    // mytag = tag+"_PFCands";                     book_HistFolder(mytag, new PFCandsHists(mytag));
    // mytag = tag+"_PFCands_pt1";                 book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1"));
    // mytag = tag+"_PFCands_pt1_UEin";            book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && UEin"));
    // mytag = tag+"_PFCands_pt1_UEout";           book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && UEout"));
    // // mytag = tag+"_PFCands_pt1_charged";         book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && charge!=0" ));
    // mytag = tag+"_PFCands_pt1_neutral";         book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && charge==0" ));
    // // mytag = tag+"_PFCands_pt1_UEin_charged";    book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && UEin  && charge!=0" ));
    // mytag = tag+"_PFCands_pt1_UEin_neutral";    book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && UEin  && charge==0" ));
    // // mytag = tag+"_PFCands_pt1_UEout_charged";   book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && UEout && charge!=0"));
    // mytag = tag+"_PFCands_pt1_UEout_neutral";   book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>1 && UEout && charge==0"));
    // mytag = tag+"_PFCands_pt0p2";               book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2"));
    // // mytag = tag+"_PFCands_pt0p2_UEin";          book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && UEin"));
    // // mytag = tag+"_PFCands_pt0p2_UEout";         book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && UEout"));
    // mytag = tag+"_PFCands_pt0p2_charged";       book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && charge!=0" ));
    // mytag = tag+"_PFCands_pt0p2_neutral";       book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && charge==0" ));
    // mytag = tag+"_PFCands_pt0p2_UEin_charged";  book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && UEin  && charge!=0" ));
    // // mytag = tag+"_PFCands_pt0p2_UEin_neutral";  book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && UEin  && charge==0" ));
    // mytag = tag+"_PFCands_pt0p2_UEout_charged"; book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && UEout && charge!=0"));
    // // mytag = tag+"_PFCands_pt0p2_UEout_neutral"; book_HistFolder(mytag, new PFCandsHists(mytag, "fromPV==3 && pt>0.2 && UEout && charge==0"));
    // mytag = tag+"_Jets";                        book_HistFolder(mytag, new VBFJetsHists(mytag));
    // // mytag = tag+"_Jets_opp";                    book_HistFolder(mytag, new VBFJetsHists(mytag, "eta1*eta2<0"));
    // // mytag = tag+"_Jets_opp_deta";               book_HistFolder(mytag, new VBFJetsHists(mytag, "eta1*eta2<0 && deta>1.4"));
    // mytag = tag+"_Jets_opp_deta_mjj";           book_HistFolder(mytag, new VBFJetsHists(mytag, "eta1*eta2<0 && deta>1.4 && mjj>200"));
    mytag = tag+"_VBFEvent";                    book_HistFolder(mytag, new VBFEventHists(mytag));
  }
}

void PFStudiesTool::fill_histograms(TString tag){
  TString mytag;
  mytag = tag+"_VBFGenJets";        HistFolder<VBFGenJetsHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts";          HistFolder<GenParticlesHists>(mytag)->fill(*event);
  if (tag == "input" || tag == "weights" || tag == "notau" || tag == "nogentau" || tag == "phasespace") return;
  // mytag = tag+"_GenParts_stable";   HistFolder<GenParticlesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenParts_pt200MeV"; HistFolder<GenParticlesHists>(mytag)->fill(*event);
  // // mytag = tag+"_GenParts_pt1GeV";   HistFolder<GenParticlesHists>(mytag)->fill(*event);
  // for(const TString & tag_ : { "_PFCands",
  // "_PFCands_pt1", "_PFCands_pt1_UEin","_PFCands_pt1_UEout","_PFCands_pt1_neutral",
  // "_PFCands_pt1_UEin_neutral","_PFCands_pt1_UEout_neutral",
  // "_PFCands_pt0p2","_PFCands_pt0p2_charged","_PFCands_pt0p2_neutral",
  // // "_PFCands_pt1_charged","_PFCands_pt1_UEin_charged","_PFCands_pt1_UEout_charged",
  // // "_PFCands_pt0p2_UEin", "_PFCands_pt0p2_UEout","_PFCands_pt0p2_UEin_neutral","_PFCands_pt0p2_UEout_neutral",
  // "_PFCands_pt0p2_UEin_charged","_PFCands_pt0p2_UEout_charged"}) {
  //   HistFolder<PFCandsHists>(tag+tag_)->fill(*event);
  // }
  // mytag = tag+"_Jets";              HistFolder<VBFJetsHists>(mytag)->fill(*event);
  // // mytag = tag+"_Jets_opp";          HistFolder<VBFJetsHists>(mytag)->fill(*event);
  // // mytag = tag+"_Jets_opp_deta";     HistFolder<VBFJetsHists>(mytag)->fill(*event);
  // mytag = tag+"_Jets_opp_deta_mjj"; HistFolder<VBFJetsHists>(mytag)->fill(*event);
  mytag = tag+"_VBFEvent";          HistFolder<VBFEventHists>(mytag)->fill(*event);

}



PFStudiesTool::PFStudiesTool(const Config & cfg) : BaseTool(cfg){

  event = new VBFTaggerEvent();
  event->reset();

  GenID<GenJet> genjet_id = {PtEtaId(20, 5.2)};
  cleaner_genjet.reset(new GenJetCleaner(genjet_id));

  genEvent_match.reset(new GenEventMatch(cfg));

  lumiweight_applicator.reset(new LumiWeightApplicator(cfg));

  MultiID<Muon> muon_id_base = {PtEtaId(3, 2.5)};
  MultiID<Electron> electron_id_base = {PtEtaId(5, 2.5), ElectronDetectorHolesID()};
  MultiID<Muon> muo_id = {muon_id_base, MuonID(Muon::IDCutBasedLoose), MuonID(Muon::IsoPFLoose)};
  MultiID<Electron> ele_id = {electron_id_base, ElectronID(Electron::IDMVAIsoLoose)};
  std::vector<MultiID<Muon>> muon_ids;
  muon_ids.push_back(muon_id_base);
  muon_ids.push_back({muon_id_base, MuonID(Muon::IDCutBasedLoose)});
  muon_ids.push_back({muon_id_base, MuonID(Muon::IDCutBasedTight)});
  muon_ids.push_back({muon_id_base, MuonID(Muon::IDCutBasedLoose), MuonID(Muon::IsoPFLoose)});
  muon_ids.push_back({muon_id_base, MuonID(Muon::IDCutBasedTight), MuonID(Muon::IsoPFLoose)});
  muon_ids.push_back({muon_id_base, MuonID(Muon::IDCutBasedTight), MuonID(Muon::IsoPFTight)});

  std::vector<MultiID<Electron>> electron_ids;
  electron_ids.push_back(electron_id_base);
  electron_ids.push_back({electron_id_base, ElectronID(Electron::IDCutBasedLoose)});
  electron_ids.push_back({electron_id_base, ElectronID(Electron::IDCutBasedTight)});
  electron_ids.push_back({electron_id_base, ElectronID(Electron::IDMVAIsoLoose)});
  electron_ids.push_back({electron_id_base, ElectronID(Electron::IDMVAIsoEff90)});
  electron_ids.push_back({electron_id_base, ElectronID(Electron::IDMVANonIsoLoose)});

  if (electron_ids.size()!=muon_ids.size()) throw std::runtime_error("Muon and Electron ids are different in number.");

  for (size_t i = 0; i < muon_ids.size(); i++) {
    muo_cleaners.emplace_back(new MuonCleaner(muon_ids.at(i)));
    ele_cleaners.emplace_back(new ElectronCleaner(electron_ids.at(i)));
    TString mytag = "LeptonEfficiency_"+to_string(i); book_HistFolder(mytag, new LeptonEfficiencyHists(mytag));
  }

  muo_cleaner.reset(new MuonCleaner(muo_id));
  ele_cleaner.reset(new ElectronCleaner(ele_id));

  MultiID<Tau> tau_id = {TauID(Tau::DeepTauVsJetVVVLoose), TauID(Tau::DeepTauVsEleVVVLoose), TauID(Tau::DeepTauVsMuVLoose)};
  tau_cleaner.reset(new TauCleaner(tau_id));

  MultiID<Jet> jet_id = {PtEtaId(20, 5.2), JetID(JetID::WP_TIGHT), JetPUID(JetPUID::WP_TIGHT)};
  jet_cleaner.reset(new JetCleaner(jet_id));

  MultiID<PFCandidate> pfcand_id = {PtEtaId(0.2, 5.2)};
  pfcand_cleaner.reset(new PFCandCleaner(pfcand_id));

  genLeptonPhaseSpace_selection.reset(new GenLeptonPhaseSpaceSelection(cfg));
  njets_selection.reset(new NJetSelection(cfg, 2, -1));
  ntaus_selection.reset(new NTauSelection(cfg, -1, 0));
  nogentau_selection.reset(new NoGenTauSelection(cfg));


  Higgs4Leptons_finder.reset(new Higgs4LeptonsFinder(cfg));

  VBFJet_definition_low_pt.reset(new VBFJetDefinition(cfg, 20));
  VBFJet_definition.reset(new VBFJetDefinition(cfg, 50));

  PFUE_selector.reset(new PFUESelector(cfg));

  book_histograms();
  PrintInputs();
}

void PFStudiesTool::study_LeptonID(){
  vector<Muon> original_muons = *event->muons;
  vector<Electron> original_electrons = *event->electrons;

  for (size_t i = 0; i < muo_cleaners.size(); i++) {
    *event->muons = original_muons;
    *event->electrons = original_electrons;
    muo_cleaners.at(i)->process(*event);
    ele_cleaners.at(i)->process(*event);
    HistFolder<LeptonEfficiencyHists>("LeptonEfficiency_"+to_string(i))->fill(*event);
  }
  *event->muons = original_muons;
  *event->electrons = original_electrons;
}


void PFStudiesTool::sort_objects(){
  sort_by_pt<GenParticle>(*event->genparticles_stable);
  sort_by_pt<GenJet>(*event->genjets);
  sort_by_pt<Jet>(*event->jets_ak4chs);
  sort_by_pt<PFCandidate>(*event->pfcands);
}

void PFStudiesTool::clean_objects(){
  cleaner_genjet->process(*event);
  muo_cleaner->process(*event);
  ele_cleaner->process(*event);
  tau_cleaner->process(*event);
  jet_cleaner->process(*event);
  pfcand_cleaner->process(*event);
}

bool PFStudiesTool::select_Nobjects(){
  if (event->genjets->size()<2) return false;
  if(!njets_selection->passes(*event)) return false;
  return true;
}

bool PFStudiesTool::Process(){

  sort_objects();
  // study_LeptonID();
  fill_histograms("input");

  lumiweight_applicator->process(*event);
  fill_histograms("weights");

  clean_objects();
  if(!ntaus_selection->passes(*event)) return false;
  fill_histograms("notau_Selection");
  if(!nogentau_selection->passes(*event)) return false;
  fill_histograms("nogentau_Selection");

  if (!select_Nobjects()) return false;
  fill_histograms("NObject_Selection");
  genEvent_match->process(*event);
  if(!genLeptonPhaseSpace_selection->passes(*event)) return false;
  fill_histograms("phasespace_Selection");

  bool pass_H4l = Higgs4Leptons_finder->process(*event);
  fill_histograms("Higgs4LeptonsReco");
  if(!pass_H4l) return false;
  fill_histograms("Higgs4Leptons_Selection");

  bool pass_definition = VBFJet_definition_low_pt->process(*event);
  if(!pass_definition) return false;
  fill_histograms("VBF_Selection");

  // pass_definition = VBFJet_definition->process(*event);
  // if(!pass_definition) return false;

  PFUE_selector->process(*event);
  // fill one set of histograms called "nominal", which is necessary for PostAnalyzer scripts
  fill_histograms("nominal");
  // store events passing the full selection for the next step
  return true;
}




REGISTER_TOOL(PFStudiesTool)
