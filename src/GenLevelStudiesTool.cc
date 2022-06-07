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
#include "LEAF/VBFTagger/include/Functions.h"

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
  // vector<string> histogram_tags = {"input", "cleaner", "nominal"};
  vector<string> histogram_tags = {"input", "nominal"};

  unordered_map<string, string> input_strings;
  unordered_map<string, bool> input_bools;

  // Modules used in the analysis
  unique_ptr<LumiWeightApplicator> lumiweight_applicator;
  unique_ptr<GenJetIDLeptonRemoval> gen_jet_lepton_cleaner;
  // unique_ptr<GenEventMatch> gen_event_match;
  unique_ptr<GenJetCleaner> cleaner_genjet;
  unique_ptr<GenParticleCleaner> cleaner_genpart;
  unique_ptr<GenLJCleaner> cleaner_LJpart;
  // unique_ptr<RemoveParticlesFromJets> part_rm_from_jets;

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
  // vector<string> insideLJ = {""}; // , "_Inside", "_Outside"};
  vector<string> emu = {"", "_reco"}; // , "_charged", "_neutral"};
  vector<string> insideLJ = {"", "_Inside", "_Outside"};
  vector<string> chargeState = {"", "_charged", "_neutral"};
  for(const string & tag : histogram_tags){
    string mytag;
    // mytag = tag+"_GenLevel"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag));
    // mytag = tag+"_GenLevel_Stable"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1"));
    // mytag = tag+"_GenLevel_Stable_pt<1"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt<1"));
    // mytag = tag+"_GenLevel_Stable_pt>1"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt>1"));
    // mytag = tag+"_GenLevel_Stable_pt<1_selection"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt<1 && gen_selections"));
    // mytag = tag+"_GenLevel_Stable_pt>1_selection"; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, "status==1 && partPt>1 && gen_selections"));

    for (const string & a : emu) {
      for (const string & inLJ : insideLJ) {
        for (const string & cha : chargeState) {
          string sel = a+inLJ+cha;
          mytag = tag+"_GenLevel"+sel; book_HistFolder(mytag, new GenLevelStudiesHists(mytag, sel));
          cout << mytag <<endl;
        }
      }
    }

    // mytag = tag+"_Pruned_GenLevel"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag));
    // mytag = tag+"_Pruned_GenLevel_Stable"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1"));
    // mytag = tag+"_Pruned_GenLevel_Stable_pt<1"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt<1"));
    // mytag = tag+"_Pruned_GenLevel_Stable_pt>1"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt>1"));
    // mytag = tag+"_Pruned_GenLevel_Stable_pt<1_selection"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt<1 && gen_selections"));
    // mytag = tag+"_Pruned_GenLevel_Stable_pt>1_selection"; book_HistFolder(mytag, new GenLevelStudiesPrunedHists(mytag, "status==1 && pt>1 && gen_selections"));
  }
}

void GenLevelStudiesTool::fill_histograms(string tag){
  // vector<string> insideLJ = {""}; // , "_Inside", "_Outside"};
  vector<string> emu = {"", "_reco"}; // , "_charged", "_neutral"};
  vector<string> insideLJ = {"", "_Inside", "_Outside"};
  vector<string> chargeState = {"", "_charged", "_neutral"};
  string mytag;
  // mytag = tag+"_GenLevel"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt<1"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt>1"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt<1_selection"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
  // mytag = tag+"_GenLevel_Stable_pt>1_selection"; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);


  for (const string & a : emu) {
    for (const string & inLJ : insideLJ) {
      for (const string & cha : chargeState) {
        string sel = a+inLJ+cha;
        mytag = tag+"_GenLevel"+sel; HistFolder<GenLevelStudiesHists>(mytag)->fill(*event);
      }
    }
  }

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

  // part_rm_from_jets.reset(new RemoveParticlesFromJets(0.4));

  GenID<GenJet> genjet_id = {PtEtaId(20, 5.2)};
  cleaner_genjet.reset(new GenJetCleaner(genjet_id));

  GenID<GenParticle> gen_particle_id = {PtEtaId(0.2, 5.2)};
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
  // lumiweight_applicator->process(*event);
  // fill_histograms("weight");

  // // removing events where H decays to taus
  // vector<GenParticle> H_daughters, H_daughters_daughters, H_decay;
  // GenParticle higgs = ParticleFinder(*event, ParticleID::H, GenParticle::StatusFlag::isLastCopy);
  // H_decay.push_back(higgs);
  // H_daughters = DaughtersFinder(*event, higgs);
  // for (const GenParticle &d: H_daughters) {
  //   H_decay.push_back(d);
  //   for (const GenParticle &dd: DaughtersFinder(*event, d)) {
  //     H_decay.push_back(dd);
  //     if (fabs(dd.pdgid())==15) return false;
  //     H_daughters_daughters.push_back(dd);
  //     // cout << "daughter: "<<pdgId2str(d.pdgid())<<"   daughter_daughter: "<<pdgId2str(dd.pdgid())<<endl;
  //     for (const GenParticle & ddd: DaughtersFinder(*event, dd)) {
  //       H_decay.push_back(ddd);
  //     }
  //   }
  // }

  vector<GenParticle> H_daughters, H_daughters_daughters, H_decay;
  GenParticle higgs = ParticleFinder(*event, ParticleID::H, GenParticle::StatusFlag::isLastCopy);
  // H_decay.push_back(higgs);
  H_daughters = DaughtersFinder(*event, higgs);
  for (const GenParticle &d: H_daughters) {
    // H_decay.push_back(d);
    for (const GenParticle &dd: DaughtersFinder(*event, d)) {
      // H_decay.push_back(dd);
      if (fabs(dd.pdgid())==15) return false;
    }
  }
  vector<GenParticle> search_list = {higgs};
  while (search_list.empty()==false) {
    GenParticle current = search_list.back();
    search_list.pop_back();
    vector<GenParticle> particle_storage = DaughtersFinder(*event, current);
    if (particle_storage.empty()==false) {
      for (const GenParticle & p : particle_storage) {
        H_decay.push_back(p);
        search_list.push_back(p);
      }
    }
  }


  gen_jet_lepton_cleaner->process(*event);
  cleaner_LJpart->process(*event);
  cleaner_genjet->process(*event);
  cleaner_genpart->process(*event);

  // threshold on leading jets
  if (event->genjets->size()<2) return false;
  GenJet j1 = event->genjets->at(0);
  GenJet j2 = event->genjets->at(1);
  TLorentzVector v = j1.p4() + j2.p4();
  if (v.M()<200.) return false;
  if (j1.pt()<50. || j2.pt()<50.) return false;

  // removing leptons from H decay
  vector<GenParticle> new_v;
  int nkeep=0, nreject=0;
  for (const GenParticle &gp: *event->genparticles_stable) {
    bool keep = true;
    if (fabs(gp.pdgid())==11 || fabs(gp.pdgid())==13 || fabs(gp.pdgid())==22) {
      for (const GenParticle & hd: H_decay) {
        if (gp.pruned_mother_identifier()==hd.identifier()) {
          keep = false;
          // cout<<"rejected particle(id): "<<pdgId2str(gp.pdgid())<<"("<<gp.identifier()<<")"<<endl;
          break;
        }
      }
    }
    if (keep==true) {
      new_v.emplace_back(gp);
      nkeep += 1;
    }
    if (keep==false) {
      nreject += 1;
    }
  }

  // cout<<"nkeep: "<<nkeep<<"   nreject: "<<nreject<<endl;

  swap(new_v, *event->genparticles_stable);


  // if (event->genjets->size()==0) return false;
  // fill_histograms("cleaner");

  //part_rm_from_jets->process(*event);

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
