#pragma once
#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/Config.h"
#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/Analyzer/include/constants.h"
#include "LEAF/Analyzer/include/GenParticlePrinter.h"
#include "LEAF/Analyzer/include/GenLevelUtils.h"
#include "LEAF/Analyzer/include/GenParticle.h"
#include "LEAF/VBFTagger/include/VBFTaggerEvent.h"
#include "LEAF/VBFTagger/include/GenParticleStatusPrinter.h"
#include <numeric>


GenParticle ParticleFinder( const VBFTaggerEvent& event, int );
GenParticle ParticleFinder(const VBFTaggerEvent&, ParticleID , GenParticle::StatusFlag status= GenParticle::StatusFlag::isLastCopy);
std::vector<GenParticle> DaughtersFinder(const VBFTaggerEvent&, GenParticle);

// std::vector<GenParticle> Decay_Products_Finder(const VBFTaggerEvent&, GenParticle, vector<GenParticle>);

double Zeppenfeld1(const VBFTaggerEvent& event,GenParticle);
// double Zeppenfeld2(const VBFTaggerEvent& event,GenParticle);

template<typename T>
double Average(std::vector<T> const& v) {
    if (v.empty()) {
        return 0;
    }
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

// bool FindParticleInVector(std::vector<GenParticle>, GenParticle);
