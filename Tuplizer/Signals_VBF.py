from Samples.Sample import *
from Samples.Storage import *

def Path_T2B():
    return '/store/user/'+os.environ['USER']+'/Tuples/'

def XML_path():
    return 'Analyzer/datasets/year/Summer20/MINIAOD/'

def FixYear(name, year):
    return name.replace('year',year)

def Get_xml(path, Name, year):
    return FixYear(path,year)+Name+'.xml'

def Get_T2Path(path, Name, year):
    return FixYear(path,year)+Name+'.xml'

def GetValuesForAllYear(Name, years):
    return YearDependentContainer(dict((year,Name) for year in years))

def Get_xmls(Name, years):
    return YearDependentContainer(dict((year,Get_xml(XML_path(), Name, year)) for year in years))

def Get_T2Paths(Name, mode, years):
    return YearDependentContainer(dict((year,Storage_T2ULB(os.path.join(Path_T2B(),year, mode,Name))) for year in years))


def Add_Generic_Sample(SampleContainer, Name, modes, years, Default_Info):
    for mode in modes:
        SampleContainer.add_samples( {
            Name+'_'+mode: Sample(
                name = Name+'_'+mode,
                tuplepaths = Get_T2Paths(Name, mode, years),
                xmlfiles = Get_xmls(Name+'_'+mode, years),
                contents = GetValuesForAllYear(mode.split('_plus_'),years),
                **Default_Info
                )
            })


def Add_Signals_VBF(SampleContainer):
    type = 'MC'
    Name = 'VBF_HToZZTo4L_M125'
    DAS_Names = {
        'UL18': Storage_DAS('/VBF_HToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    xsecs = YearDependentContainer()
    nevents_das = YearDependentContainer({'UL18': 477000})
    nevents_generated = YearDependentContainer({'UL18': 477000})
    nevents_weighted = YearDependentContainer({'UL18': 1877169.5058})
    Default_Info = {
        'type': type, 'group': GetValuesForAllYear(Name,years), 'minipaths': YearDependentContainer(DAS_Names),
        'xsecs': xsecs, 'nevents_das': nevents_das, 'nevents_generated': nevents_generated, 'nevents_weighted': nevents_weighted,
    }
    # modes = ['standard','pfcands', 'extrajets', 'standard_plus_extrajets', 'standard_plus_pfcands', 'pfcands_plus_extrajets', 'extrajets_plus_pfcands', 'standard_plus_extrajets_plus_pfcands', 'standard_plus_pfcands_plus_extrajets']
    modes = ['standard','pfcands', 'extrajets']
    Add_Generic_Sample(SampleContainer, Name, modes, years, Default_Info)



def Add_Signals_GluGlu(SampleContainer):
    type = 'MC'
    Name = 'GluGluHToZZTo4L_M125'
    DAS_Names = {
        'UL18': Storage_DAS('/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    xsecs = YearDependentContainer()
    nevents_das = YearDependentContainer({'UL18': 940000})
    nevents_generated = YearDependentContainer({'UL18': 813000.0})
    nevents_weighted = YearDependentContainer({'UL18': 23470646.4338})
    Default_Info = {
        'type': type, 'group': GetValuesForAllYear(Name,years), 'minipaths': YearDependentContainer(DAS_Names),
        'xsecs': xsecs, 'nevents_das': nevents_das, 'nevents_generated': nevents_generated, 'nevents_weighted': nevents_weighted,
    }
    modes = ['standard','pfcands', 'extrajets']
    Add_Generic_Sample(SampleContainer, Name, modes, years, Default_Info)

    # Name = 'GluGluToZH_HToZZTo4L_M125'
    # DAS_Names = {
    #     'UL18': Storage_DAS('/GluGluToZH_HToZZTo4L_M125_TuneCP5_13TeV-jhugenv723-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'),
    #     }
    # years = DAS_Names.keys()
    # xsecs = YearDependentContainer()
    # nevents_das = YearDependentContainer({'UL18': 979940})
    # nevents_generated = YearDependentContainer({'UL18': 0})
    # nevents_weighted = YearDependentContainer({'UL18': 0})
    # Default_Info = {
    #     'type': type, 'group': GetValuesForAllYear(Name,years), 'minipaths': YearDependentContainer(DAS_Names),
    #     'xsecs': xsecs, 'nevents_das': nevents_das, 'nevents_generated': nevents_generated, 'nevents_weighted': nevents_weighted,
    # }
    # modes = ['standard','pfcands', 'standard_plus_pfcands']
    # Add_Generic_Sample(SampleContainer, Name, modes, years, Default_Info)


        # 'GluGluHToZZTo4Mu_M125': Sample(
        #     type='MC',
        #     name='GluGluHToZZTo4Mu_M125',
        #     group=YearDependentContainer({'UL18': 'GluGluHToZZTo4Mu_M125'}),
        #     minipaths=YearDependentContainer({'UL18': Storage_DAS('/GluGluHToZZTo4Mu_M125_TuneCP5_13TeV_powheg2_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM')}),
        #     tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/GluGluHToZZTo4Mu_M125/UL18')}),
        #     xsecs=YearDependentContainer(),
        #     xmlfiles=YearDependentContainer({'UL18': FixYear(xml_path,'UL18')+'/GluGluHToZZTo4Mu_M125.xml'}),
        #     nevents_das=YearDependentContainer({'UL18': 9856200}),
        #     nevents_generated=YearDependentContainer({'UL18': 9856200}),
        #     nevents_weighted=YearDependentContainer({'UL18': 9856200}),
        #     ),

# def Add_Signals_WH_HToZZTo4L(SampleContainer):
#     SampleContainer.add_samples( {
#         'WminusH_HToZZTo4L_M125': Sample(
#             type='MC',
#             name='WminusH_HToZZTo4L_M125',
#             group=YearDependentContainer({'UL18': 'WminusH_HToZZTo4L_M125'}),
#             minipaths=YearDependentContainer({'UL18': Storage_DAS('/WminusH_HToZZTo4L_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM')}),
#             tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/WminusH_HToZZTo4L_M125/UL18')}),
#             xsecs=YearDependentContainer(),
#             xmlfiles=YearDependentContainer({'UL18': FixYear(xml_path,'UL18')+'/WminusH_HToZZTo4L_M125.xml'}),
#             nevents_das=YearDependentContainer({'UL18': 193853}),
#             nevents_generated=YearDependentContainer({'UL18': 193853}),
#             nevents_weighted=YearDependentContainer({'UL18': 79986.443311}),
#             ),
#         'WplusH_HToZZTo4L_M125': Sample(
#             type='MC',
#             name='WplusH_HToZZTo4L_M125',
#             group=YearDependentContainer({'UL18': 'WplusH_HToZZTo4L_M125'}),
#             minipaths=YearDependentContainer({'UL18': Storage_DAS('/WplusH_HToZZTo4L_M125_TuneCP5_13TeV_powheg2-minlo-HWJ_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM')}),
#             tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/WplusH_HToZZTo4L_M125/UL18')}),
#             xsecs=YearDependentContainer(),
#             xmlfiles=YearDependentContainer({'UL18': FixYear(xml_path,'UL18')+'/WplusH_HToZZTo4L_M125.xml'}),
#             nevents_das=YearDependentContainer({'UL18': 298674}),
#             nevents_generated=YearDependentContainer({'UL18': 298674}),
#             nevents_weighted=YearDependentContainer({'UL18': 259154.89361}),
#             ),
#         })
#
# def Add_Signals_ZZTo4L(SampleContainer):
#     SampleContainer.add_samples( {
#         'ZZTo4L': Sample(
#             type='MC',
#             name='ZZTo4L',
#             group=YearDependentContainer({'UL18': 'ZZTo4L'}),
#             minipaths=YearDependentContainer({'UL18': Storage_DAS('/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM')}),
#             tuplepaths=YearDependentContainer({'UL18': Storage_T2ULB('/store/user/anmalara/Tuples/VBF/ZZTo4L/UL18')}),
#             xsecs=YearDependentContainer(),
#             xmlfiles=YearDependentContainer({'UL18': FixYear(xml_path,'UL18')+'/ZZTo4L.xml'}),
#             nevents_das=YearDependentContainer({'UL18': 99191000}),
#             nevents_generated=YearDependentContainer({'UL18': 99191000}),
#             nevents_weighted=YearDependentContainer({'UL18': 99191000}),
#             ),
#         })



def Add_Signals_VBFAnalysis(SampleContainer):
    Add_Signals_VBF(SampleContainer)
    Add_Signals_GluGlu(SampleContainer)
    # Add_Signals_WH_HToZZTo4L(SampleContainer)
