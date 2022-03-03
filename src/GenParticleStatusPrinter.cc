#include "LEAF/VBFTagger/include/GenParticleStatusPrinter.h"

#include "TFile.h"
#include "TTree.h"

using namespace std;


GenParticleStatusPrinter::GenParticleStatusPrinter(const Config & cfg){}

bool GenParticleStatusPrinter::process(RecoEvent & event){
  if(event.is_data) return false;

  cout << "     +=====================+" << endl;
  cout << "     |     GenParticles    |" << endl;
  cout << "     +=====================+" << endl << endl;

  cout << "Number, Identifier, pdgId, mother, isPrompt, isDecayedLeptonHadron, isTauDecayProduct, isPromptTauDecayProduct, isDirectTauDecayProduct, isDirectPromptTauDecayProduct, isDirectHadronDecayProduct, isHardProcess, fromHardProcess, isHardProcessTauDecayProduct, isDirectHardProcessTauDecayProduct,  fromHardProcessBeforeFSR, isFirstCopy, isLastCopy, isLastCopyBeforeFSR" << endl;
  cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

  for(size_t i=0; i<event.genparticles_all->size(); i++){
    int correct_idx = -1;
    for(size_t j=0; j<event.genparticles_all->size(); j++){
      if(event.genparticles_all->at(j).identifier() == (int)i){
        correct_idx = j;
        break;
      }
    }
    GenParticle gp = event.genparticles_all->at(correct_idx);

    // now find mother using the identifier again
    int motherpdgid = -1;
    for(size_t j=0; j<event.genparticles_all->size(); j++){
      if(event.genparticles_all->at(j).identifier() == gp.mother_identifier()){
        motherpdgid = event.genparticles_all->at(j).pdgid();
        break;
      }
    }

    // if(!gp.get_statusflag(GenParticle::isLastCopy)) continue;
    // if(abs(gp.pdgid()) > 30) continue;
    cout << i << "  ,  " << gp.identifier() << "  ,  " << pdgId2str(gp.pdgid()) << "  ,  " << gp.mother_identifier() << " (pdgid: " << pdgId2str(motherpdgid) << ") ,  " << gp.get_statusflag(GenParticle::isPrompt) << "  ,  "<< gp.get_statusflag(GenParticle::isDecayedLeptonHadron) << "  ,  "<< gp.get_statusflag(GenParticle::isTauDecayProduct) << "  ,  "<< gp.get_statusflag(GenParticle::isPromptTauDecayProduct) << "  ,  "<< gp.get_statusflag(GenParticle::isDirectTauDecayProduct) << "  ,  "<< gp.get_statusflag(GenParticle::isDirectPromptTauDecayProduct) << "  ,  "<< gp.get_statusflag(GenParticle::isDirectHadronDecayProduct) << "  ,  "<< gp.get_statusflag(GenParticle::isHardProcess) << "  ,  "<< gp.get_statusflag(GenParticle::fromHardProcess) << "  ,  "<< gp.get_statusflag(GenParticle::isHardProcessTauDecayProduct) << "  ,  "<< gp.get_statusflag(GenParticle::isDirectHardProcessTauDecayProduct) << "  ,  "<< gp.get_statusflag(GenParticle::fromHardProcessBeforeFSR) << "  ,  "<< gp.get_statusflag(GenParticle::isFirstCopy) << "  ,  "<< gp.get_statusflag(GenParticle::isLastCopy) << "  ,  "<< gp.get_statusflag(GenParticle::isLastCopyBeforeFSR) << endl;
  }
  cout << endl << endl << endl << endl;
  return true;

}
