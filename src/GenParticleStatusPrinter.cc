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

    // if(!gp.isLastCopy()) continue;
    // if(abs(gp.pdgid()) > 30) continue;
    cout << i << "  ,  " << gp.identifier() << "  ,  " << pdgId2str(gp.pdgid()) << "  ,  " << gp.mother_identifier() << " (pdgid: " << pdgId2str(motherpdgid) << ") ,  " << gp.isPrompt() << "  ,  "<< gp.isDecayedLeptonHadron() << "  ,  "<< gp.isTauDecayProduct() << "  ,  "<< gp.isPromptTauDecayProduct() << "  ,  "<< gp.isDirectTauDecayProduct() << "  ,  "<< gp.isDirectPromptTauDecayProduct() << "  ,  "<< gp.isDirectHadronDecayProduct() << "  ,  "<< gp.isHardProcess() << "  ,  "<< gp.fromHardProcess() << "  ,  "<< gp.isHardProcessTauDecayProduct() << "  ,  "<< gp.isDirectHardProcessTauDecayProduct() << "  ,  "<< gp.fromHardProcessBeforeFSR() << "  ,  "<< gp.isFirstCopy() << "  ,  "<< gp.isLastCopy() << "  ,  "<< gp.isLastCopyBeforeFSR() << endl;
  }
  cout << endl << endl << endl << endl;
  return true;

}
