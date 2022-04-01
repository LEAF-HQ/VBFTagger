#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/GenParticlePrinter.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/GenParticleStatusPrinter.h"


GenParticle ParticleFinder( const VBFTaggerEvent& event, int );
GenParticle ParticleFinder(const VBFTaggerEvent&, ParticleID , GenParticle::StatusFlag status= GenParticle::StatusFlag::isLastCopy);
std::vector<GenParticle> DaughtersFinder(const VBFTaggerEvent&, GenParticle);
