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
#include "LEAF/Analyzer/include/LumiWeightApplicator.h"


#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/GenParticlesHists.h"
#include "LEAF/VBFTagger/include/PFCandsHists.h"
#include "LEAF/VBFTagger/include/VBFJetsHists.h"
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
  vector<string> histogram_tags = {"input", "weights", "njets", "nominal"};

  unordered_map<string, string> input_strings;
  unordered_map<string, bool> input_bools;

  // Modules used in the analysis
  unique_ptr<LumiWeightApplicator> lumiweight_applicator;
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

    mytag = tag+"_GenParts";              book_HistFolder(mytag, new GenParticlesHists(mytag));
    mytag = tag+"_GenParts_status";       book_HistFolder(mytag, new GenParticlesHists(mytag, "status==1"));
    mytag = tag+"_GenParts_pt";           book_HistFolder(mytag, new GenParticlesHists(mytag, "status==1 && pt>1"));
    mytag = tag+"_GenParts_gen_sel";      book_HistFolder(mytag, new GenParticlesHists(mytag, "status==1 && pt>1 && gen_selections"));
    mytag = tag+"_PFCands";               book_HistFolder(mytag, new PFCandsHists(mytag));
    mytag = tag+"_PFCands_pt";            book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1"));
    mytag = tag+"_PFCands_UEin";          book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1 && UEin"));
    mytag = tag+"_PFCands_UEout";         book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1 && UEout"));
    mytag = tag+"_PFCands_UEin_charged";  book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1 && UEin  && charge!=0" ));
    mytag = tag+"_PFCands_UEin_neutral";  book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1 && UEin  && charge==0" ));
    mytag = tag+"_PFCands_UEout_charged"; book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1 && UEout && charge!=0"));
    mytag = tag+"_PFCands_UEout_neutral"; book_HistFolder(mytag, new PFCandsHists(mytag, "pt>1 && UEout && charge==0"));
    mytag = tag+"_Jets";                  book_HistFolder(mytag, new VBFJetsHists(mytag));
    mytag = tag+"_Jets_opp";              book_HistFolder(mytag, new VBFJetsHists(mytag, "eta1*eta2<0"));
    mytag = tag+"_Jets_opp_deta";         book_HistFolder(mytag, new VBFJetsHists(mytag, "eta1*eta2<0 && deta>1.4"));
    mytag = tag+"_Jets_opp_deta_mjj";     book_HistFolder(mytag, new VBFJetsHists(mytag, "eta1*eta2<0 && deta>1.4 && mjj>200"));
  }
}

void PFStudiesTool::fill_histograms(TString tag){
  TString mytag;
  mytag = tag+"_GenParts";              HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts_status";       HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts_pt";           HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_GenParts_gen_sel";      HistFolder<GenParticlesHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands";               HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_pt";            HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_UEin";          HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_UEout";         HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_UEin_charged";  HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_UEin_neutral";  HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_UEout_charged"; HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_PFCands_UEout_neutral"; HistFolder<PFCandsHists>(mytag)->fill(*event);
  mytag = tag+"_Jets";                  HistFolder<VBFJetsHists>(mytag)->fill(*event);
  mytag = tag+"_Jets_opp";              HistFolder<VBFJetsHists>(mytag)->fill(*event);
  mytag = tag+"_Jets_opp_deta";         HistFolder<VBFJetsHists>(mytag)->fill(*event);
  mytag = tag+"_Jets_opp_deta_mjj";     HistFolder<VBFJetsHists>(mytag)->fill(*event);
}



PFStudiesTool::PFStudiesTool(const Config & cfg) : BaseTool(cfg){

  event = new VBFTaggerEvent();
  event->reset();

  lumiweight_applicator.reset(new LumiWeightApplicator(cfg));

  MultiID<Jet> jet_id = {PtEtaId(20, 4.7), JetID(JetID::WP_TIGHT), JetPUID(JetPUID::WP_TIGHT)};
  cleaner_jet.reset(new JetCleaner(jet_id));

  MultiID<PFCandidate> pfcand_id = {PtEtaId(1, 5.2)};
  cleaner_pfcand.reset(new PFCandCleaner(pfcand_id));

  selection_njets.reset(new NJetSelection(cfg, 2, -1));

  book_histograms();
  PrintInputs();
}




bool PFStudiesTool::Process(){

  sort_by_pt<GenParticle>(*event->genparticles_stable);
  sort_by_pt<GenJet>(*event->genjets);
  sort_by_pt<Jet>(*event->jets_ak4chs);
  sort_by_pt<PFCandidate>(*event->pfcands);
  fill_histograms("input");

  lumiweight_applicator->process(*event);
  cleaner_jet->process(*event);
  cleaner_pfcand->process(*event);
  fill_histograms("weights");

  if(!selection_njets->passes(*event)) return false;
  fill_histograms("njets");

  bool isSet = false;
  for(const Jet& jet1: *event->jets_ak4chs){
    for(const Jet& jet2: *event->jets_ak4chs){
      if (jet2.identifier() == jet1.identifier()) continue;
      TLorentzVector jj = jet1.p4() + jet2.p4();
      if (jet2.eta()*jet1.eta()>0) continue;
      if (fabs(jet2.eta()-jet1.eta())<1.4) continue;
      if (jj.M()<200) continue;
      event->set_identifier_VBFjet1(jet1.identifier());
      event->set_identifier_VBFjet2(jet2.identifier());
      isSet=true;
      break;
    }
    if (isSet==true) break;
  }

  if (!isSet) return false;

  // fill one set of histograms called "nominal", which is necessary for PostAnalyzer scripts
  fill_histograms("nominal");
  // store events passing the full selection for the next step
  return true;
}




REGISTER_TOOL(PFStudiesTool)
