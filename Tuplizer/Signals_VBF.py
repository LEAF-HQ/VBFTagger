from Samples.Sample import *
from Samples.Storage import *

def Add_Signals_VBF(SampleContainer):
    SampleContainer.add_samples( {
        'VBF_HToZZTo4L_M125': Sample(
            type='MC',
            name='VBF_HToZZTo4L_M125',
            group=YearDependentContainer({'UL18': 'VBF_HToZZTo4L_M125'}),
            minipaths=YearDependentContainer({'UL18': Storage_DAS('/VBF_HToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM')}),
            tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/VBF_HToZZTo4L_M125/UL18')}),
            xsecs=YearDependentContainer(),
            xmlfiles=YearDependentContainer({'UL18':'Analyzer/datasets/UL18/Summer20/MINIAOD/VBF_HToZZTo4L_M125.xml'}),
            nevents_das=YearDependentContainer({'UL18': 477000}),
            nevents_generated=YearDependentContainer({'UL18': 477000}),
            nevents_weighted=YearDependentContainer({'UL18': 1877169.5058000004}),
            ),
        })



def Add_Signals_WH_HToZZTo4L(SampleContainer):
    SampleContainer.add_samples( {
        'WminusH_HToZZTo4L_M125': Sample(
            type='MC',
            name='WminusH_HToZZTo4L_M125',
            group=YearDependentContainer({'UL18': 'WminusH_HToZZTo4L_M125'}),
            minipaths=YearDependentContainer({'UL18': Storage_DAS('/WminusH_HToZZTo4L_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM')}),
            tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/WminusH_HToZZTo4L_M125/UL18')}),
            xsecs=YearDependentContainer(),
            xmlfiles=YearDependentContainer({'UL18':'Analyzer/datasets/UL18/Summer20/MINIAOD/WminusH_HToZZTo4L_M125.xml'}),
            nevents_das=YearDependentContainer({'UL18': 193853}),
            nevents_generated=YearDependentContainer({'UL18': 193853}),
            nevents_weighted=YearDependentContainer({'UL18': 79986.443311}),
            ),
        'WplusH_HToZZTo4L_M125': Sample(
            type='MC',
            name='WplusH_HToZZTo4L_M125',
            group=YearDependentContainer({'UL18': 'WplusH_HToZZTo4L_M125'}),
            minipaths=YearDependentContainer({'UL18': Storage_DAS('/WplusH_HToZZTo4L_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM')}),
            tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/WplusH_HToZZTo4L_M125/UL18')}),
            xsecs=YearDependentContainer(),
            xmlfiles=YearDependentContainer({'UL18':'Analyzer/datasets/UL18/Summer20/MINIAOD/WplusH_HToZZTo4L_M125.xml'}),
            nevents_das=YearDependentContainer({'UL18': 298674}),
            nevents_generated=YearDependentContainer({'UL18': 298674}),
            nevents_weighted=YearDependentContainer({'UL18': 259154.89361}),
            ),
        })


def Add_Signals_GluGlu(SampleContainer):
    SampleContainer.add_samples( {
        'GluGluHToZZTo4L_M125': Sample(
            type='MC',
            name='GluGluHToZZTo4L_M125',
            group=YearDependentContainer({'UL18': 'GluGluHToZZTo4L_M125'}),
            minipaths=YearDependentContainer({'UL18': Storage_DAS('/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM')}),
            tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/GluGluHToZZTo4L_M125/UL18')}),
            xsecs=YearDependentContainer(),
            xmlfiles=YearDependentContainer({'UL18':'Analyzer/datasets/UL18/Summer20/MINIAOD/GluGluHToZZTo4L_M125.xml'}),
            nevents_das=YearDependentContainer({'UL18': 940000}),
            nevents_generated=YearDependentContainer({'UL18': 940000}),
            nevents_weighted=YearDependentContainer({'UL18': 940000}),
            ),
        'GluGluToZH_HToZZTo4L_M125': Sample(
            type='MC',
            name='GluGluToZH_HToZZTo4L_M125',
            group=YearDependentContainer({'UL18': 'GluGluToZH_HToZZTo4L_M125'}),
            minipaths=YearDependentContainer({'UL18': Storage_DAS('/GluGluToZH_HToZZTo4L_M125_TuneCP5_13TeV-jhugenv723-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM')}),
            tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/GluGluToZH_HToZZTo4L_M125/UL18')}),
            xsecs=YearDependentContainer(),
            xmlfiles=YearDependentContainer({'UL18':'Analyzer/datasets/UL18/Summer20/MINIAOD/GluGluToZH_HToZZTo4L_M125.xml'}),
            nevents_das=YearDependentContainer({'UL18': 979940}),
            nevents_generated=YearDependentContainer({'UL18': 979940}),
            nevents_weighted=YearDependentContainer({'UL18': 979940}),
            ),
        'GluGluHToZZTo4Mu_M125': Sample(
            type='MC',
            name='GluGluHToZZTo4Mu_M125',
            group=YearDependentContainer({'UL18': 'GluGluHToZZTo4Mu_M125'}),
            minipaths=YearDependentContainer({'UL18': Storage_DAS('/GluGluHToZZTo4Mu_M125_TuneCP5_13TeV_powheg2_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM')}),
            tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/GluGluHToZZTo4Mu_M125/UL18')}),
            xsecs=YearDependentContainer(),
            xmlfiles=YearDependentContainer({'UL18':'Analyzer/datasets/UL18/Summer20/MINIAOD/GluGluHToZZTo4Mu_M125.xml'}),
            nevents_das=YearDependentContainer({'UL18': 9856200}),
            nevents_generated=YearDependentContainer({'UL18': 9856200}),
            nevents_weighted=YearDependentContainer({'UL18': 9856200}),
            ),
        })

def Add_Signals_ZZTo4L(SampleContainer):
    SampleContainer.add_samples( {
        'ZZTo4L': Sample(
            type='MC',
            name='ZZTo4L',
            group=YearDependentContainer({'UL18': 'ZZTo4L'}),
            minipaths=YearDependentContainer({'UL18': Storage_DAS('/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM')}),
            tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/ZZTo4L/UL18')}),
            xsecs=YearDependentContainer(),
            xmlfiles=YearDependentContainer({'UL18':'Analyzer/datasets/UL18/Summer20/MINIAOD/ZZTo4L.xml'}),
            nevents_das=YearDependentContainer({'UL18': 99191000}),
            nevents_generated=YearDependentContainer({'UL18': 99191000}),
            nevents_weighted=YearDependentContainer({'UL18': 99191000}),
            ),
        })



def Add_Signals_VBFAnalysis(SampleContainer):
    Add_Signals_VBF(SampleContainer)
    Add_Signals_WH_HToZZTo4L(SampleContainer)
    Add_Signals_GluGlu(SampleContainer)
