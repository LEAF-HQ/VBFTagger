#pragma once

#include "LEAF/Analyzer/include/AnalysisModule.h"
#include "LEAF/Analyzer/include/GenEvent.h"
#include "LEAF/Analyzer/include/RecoEvent.h"
#include "LEAF/Analyzer/include/ObjectIdUtils.h"
#include "LEAF/Analyzer/include/useful_functions.h"

class GenJetIDLeptonRemoval : public AnalysisModule<GenEvent> {
public:
    GenJetIDLeptonRemoval(const double & dr_);
    virtual bool process(GenEvent & event) override;

private:
    double m_dr;
};

class GenParticleCleaner : public AnalysisModule<GenEvent> {
public:
    GenParticleCleaner(const GenID<GenParticle> & id_);
    virtual bool process(GenEvent & event) override;

private:
    GenID<GenParticle> id;
};

class GenLJCleaner : public AnalysisModule<GenEvent> {
public:
    GenLJCleaner(const double & dr_);
    virtual bool process(GenEvent & event) override;

private:
    double m_dr;
};

// class GenJetInvMassTreshold : public AnalysisModule<GenEvent> {
// public:
//     GenJetInvMassTreshold(const double& tresh_);
//     virtual bool process(GenEvent & event) override;
//
// private:
//     double tresh;
// };
