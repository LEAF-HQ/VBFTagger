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
  //
  // book<TH1F>("geninfoscalepdf", ";PDF scale; Events / bin",               200,    0, 3000);
  // book<TH1F>("geninfoid1",      ";ID of initial state 1; Events / bin",    27, -5.5, 21.5);
  // book<TH1F>("geninfoid2",      ";ID of initial state 2; Events / bin",    27, -5.5, 21.5);
  // book<TH1F>("geninfox1",       ";x of initial state 1; Events / bin",     50,    0, 1);
  // book<TH1F>("geninfox2",       ";x of initial state 2; Events / bin",     50,    0, 1);
  // book<TH1F>("geninfoxg",       ";x of all gluons; Events / bin",          50,    0, 1);
  // book<TH1F>("geninfoxlight",   ";x of all light quarks; Events / bin",    50,    0, 1);
  //
  // book<TH1F>("genmet",          ";gen. p_{T}^{miss} [GeV]; Events / bin", 100,    0, 1000);
  // book<TH1F>("genmet_phi",      ";#phi(gen. p_{T}^{miss}); Events / bin",  60, -3.5, 3.5);
  // book<TH2D>("genmet_phi_pt",   ";metphi;pt; Events / bin", 60, -3.5, 3.5, 100,    0, 1000);

  book<TH1F>("NumberOfParticles<1GeV","; Number of particles with Pt < 1 GeV; Events",51, -0.5, 50.5);
  book<TH1F>("NumberOfParticles>1GeV","; Number of particles with Pt > 1 GeV; Events",51, -0.5, 50.5);
  book<TH1F>("NumberOfChargedParticles<1GeV","; Number of charged particles with Pt < 1 GeV; Events",51, -0.5, 50.5);
  book<TH1F>("NumberOfChargedParticles>1GeV","; Number of charged particles with Pt > 1 GeV; Events",51, -0.5, 50.5);

  double NPdgId = 4000;
  book<TH1F>("PdgId","H->ZZ->4l (M = 125 GeV); Particle Id ; Number of particles",2*NPdgId+1, -NPdgId-0.5, NPdgId+0.5);
  hist<TH1F>("PdgId")->GetXaxis()->SetBinLabel(NPdgId + 1 + 1,"Quarks");
  hist<TH1F>("PdgId")->GetXaxis()->SetBinLabel(NPdgId + 1 +11,"Leptons");
  hist<TH1F>("PdgId")->GetXaxis()->SetBinLabel(NPdgId + 1 +23,"Z");
  hist<TH1F>("PdgId")->GetXaxis()->SetBinLabel(NPdgId + 1 +25,"H");
  hist<TH1F>("PdgId")->GetXaxis()->SetBinLabel(NPdgId + 1 +111,"Mesons");
  hist<TH1F>("PdgId")->GetXaxis()->SetBinLabel(NPdgId + 1 +2112,"Baryons");

  book<TH1F>("PdgIdZoom","H->ZZ->4l (M = 125 GeV); Particle Id ; Number of particles",61, -30.5, 30.5);
  hist<TH1F>("PdgIdZoom")->GetXaxis()->SetBinLabel(30 + 1 + 1,"Quarks");
  hist<TH1F>("PdgIdZoom")->GetXaxis()->SetBinLabel(30 + 1 +11,"Leptons");
  hist<TH1F>("PdgIdZoom")->GetXaxis()->SetBinLabel(30 + 1 +23,"Z");
  hist<TH1F>("PdgIdZoom")->GetXaxis()->SetBinLabel(30 + 1 +25,"H");


  book<TH1F>("verifH","H->ZZ->4l (M = 125 GeV); Mass (GeV) ; Number of particles",501, 0, 500);
  book<TH1F>("verifZ","H->ZZ->4l (M = 125 GeV); Mass (GeV) ; Number of particles",201, 0, 200);
  book<TH1F>("4Lmass","H->ZZ->4l (M = 125 GeV); Mass (GeV) ; Number of particles",151, 0, 150);
  book<TH1F>("4Lpt","H->ZZ->4l (M = 125 GeV); Pt (GeV) ; Number of particles",300, 0, 800);

  book<TH2D>("ParticleStatusFlag", ";PdgID;Status;Number of particles", 2*NPdgId+1, -NPdgId-0.5, NPdgId+0.5, 8, 0, 8);
  hist<TH2D>("ParticleStatusFlag")->GetYaxis()->SetBinLabel(1,"isPrompt");
  hist<TH2D>("ParticleStatusFlag")->GetYaxis()->SetBinLabel(3,"isFirstCopy");
  hist<TH2D>("ParticleStatusFlag")->GetYaxis()->SetBinLabel(5,"isLastCopy");
  hist<TH2D>("ParticleStatusFlag")->GetYaxis()->SetBinLabel(7,"isLastCopyBeforeFSR");

  book<TH2D>("ParticleStatus", ";PdgID;Status;Number of particles", 61, -30.5, 30.5, 95, 0, 95);


}

void GenLevelStudiesHists::fill(const VBFTaggerEvent & event){


  double weight = event.weight;
  // int id1 = event.geninfo->id1();
  // int id2 = event.geninfo->id1();
  hist<TH1F>("sumweights")->Fill(1, weight);
  //
  // hist<TH1F>("geninfoscalepdf")->Fill(event.geninfo->scale_pdf(), weight);
  // hist<TH1F>("geninfoid1")->Fill(id1, weight);
  // hist<TH1F>("geninfoid2")->Fill(id2, weight);
  // hist<TH1F>("geninfox1")->Fill(event.geninfo->x1(), weight);
  // hist<TH1F>("geninfox2")->Fill(event.geninfo->x2(), weight);
  //
  //
  // if(abs(id1) == 21) {
  //   hist<TH1F>("geninfoxg")->Fill(event.geninfo->x1(), weight);
  //   hist<TH1F>("geninfoxg")->Fill(event.geninfo->x2(), weight);
  // }
  // if(abs(id1) >= 1 && abs(id1) <= 3) {
  //   hist<TH1F>("geninfoxlight")->Fill(event.geninfo->x1(), weight);
  //   hist<TH1F>("geninfoxlight")->Fill(event.geninfo->x2(), weight);
  // }
  //
  // hist<TH1F>("genmet")->Fill(event.genmet->pt(), weight);
  // hist<TH1F>("genmet_phi")->Fill(event.genmet->phi(), weight);
  // hist<TH2D>("genmet_phi_pt")->Fill(event.genmet->phi(), event.genmet->pt(), weight);

  // removing the events containing taus
  for (size_t k=0; k<event.genparticles_stable->size(); k++) {
    GenParticle t = event.genparticles_stable->at(k);
    if (t.pdgid() == 15) return;
  }

  vector<GenParticle> gen_part_w_pT_lower_than_tresh;
  vector<GenParticle> charged_gen_part_w_pT_lower_than_tresh;
  vector<GenParticle> gen_part_w_pT_higher_than_tresh;
  vector<GenParticle> charged_gen_part_w_pT_higher_than_tresh;
  TLorentzVector FourLeptons;
  for(size_t i=0; i<event.genparticles_stable->size(); i++){
    GenParticle m = event.genparticles_stable->at(i);

    hist<TH2D>("ParticleStatusFlag")->Fill(m.pdgid(), m.isPrompt(), weight);
    hist<TH2D>("ParticleStatusFlag")->Fill(m.pdgid(), m.isFirstCopy()+2, weight);
    hist<TH2D>("ParticleStatusFlag")->Fill(m.pdgid(), m.isLastCopy()+4, weight);
    hist<TH2D>("ParticleStatusFlag")->Fill(m.pdgid(), m.isLastCopyBeforeFSR()+6, weight);

    hist<TH2D>("ParticleStatus")->Fill(m.pdgid(), m.status(), weight);

    if (!m.isHardProcess() && !m.fromHardProcessBeforeFSR()) continue;
    hist<TH1F>("PdgId")->Fill(m.pdgid(), weight);

    if (m.pdgid() == 25 && m.isLastCopy())  {
      if (!m.isHardProcess() && !m.fromHardProcessBeforeFSR()) continue;
      hist<TH1F>("verifH")->Fill(m.m(), weight);
      for(size_t j=0; j<event.genparticles_stable->size(); j++) {
        GenParticle z = event.genparticles_stable->at(j);
        if (z.mother_identifier() == m.identifier()) {
          hist<TH1F>("verifZ")->Fill(z.m(), weight);
          for(size_t k=0; k<event.genparticles_stable->size(); k++) {
            GenParticle l = event.genparticles_stable->at(k);
            if (l.mother_identifier() == z.identifier()) {
              FourLeptons += l.p4();
            }
          }
        }
      }
    }
    TLorentzVector zero;
    if (FourLeptons != zero) {
      hist<TH1F>("4Lmass")->Fill(FourLeptons.M(), weight);
      hist<TH1F>("4Lpt")->Fill(FourLeptons.Pt(), weight);
    }

    if (m.status()!=1 || !m.isLastCopy()) continue;
    hist<TH1F>("PdgId")->Fill(m.pdgid(), weight);
    hist<TH1F>("PdgIdZoom")->Fill(m.pdgid(), weight);

    if (m.pt() < 1.) {
      gen_part_w_pT_lower_than_tresh.push_back(m);
      if(abs(m.charge()) == 1) {
        charged_gen_part_w_pT_lower_than_tresh.push_back(m);                                  // If particle is charged, counter +1
      }
    }

    if (m.pt() >= 1.) {
      gen_part_w_pT_higher_than_tresh.push_back(m);
      if(abs(m.charge()) == 1) {
        charged_gen_part_w_pT_higher_than_tresh.push_back(m);                                  // If particle is charged, counter +1
      }
    }

  }
  hist<TH1F>("NumberOfParticles<1GeV")->Fill(gen_part_w_pT_lower_than_tresh.size(), weight);
  hist<TH1F>("NumberOfParticles>1GeV")->Fill(gen_part_w_pT_higher_than_tresh.size(), weight);
  hist<TH1F>("NumberOfChargedParticles<1GeV")->Fill(charged_gen_part_w_pT_lower_than_tresh.size(), weight);
  hist<TH1F>("NumberOfChargedParticles>1GeV")->Fill(charged_gen_part_w_pT_higher_than_tresh.size(), weight);



}
