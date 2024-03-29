from Samples.SampleContainer_template import *


def Add_Signals_VBF(SampleContainer):
    type = 'MC'
    name = 'VBF_HToZZTo4L_M125'
    DAS_Names = {
        # 'UL16preVFP': Storage_DAS('/VBF_HToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM'),
        'UL16postVFP': Storage_DAS('/VBF_HToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/VBF_HToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/VBF_HToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 498000,        'UL17': 499000,       'UL18': 477000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 498000.0,      'UL17': 499000.0 ,    'UL18': 477000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 1959725.49446, 'UL17': 1963555.777,  'UL18': 1877169.5058}),
    }
    # modes = ['standard','pfcands', 'extrajets', 'standard_plus_extrajets', 'standard_plus_pfcands', 'pfcands_plus_extrajets', 'extrajets_plus_pfcands', 'standard_plus_extrajets_plus_pfcands', 'standard_plus_pfcands_plus_extrajets']
    modes = [['standard'],['pfcands'], ['extrajets'], ['stablegenparticles']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)

    name = 'VBF_HToZZTo4L_M120'
    DAS_Names = {
        # 'UL16preVFP': Storage_DAS('/VBF_HToZZTo4L_M120_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM'),
        'UL16postVFP': Storage_DAS('/VBF_HToZZTo4L_M120_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/VBF_HToZZTo4L_M120_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/VBF_HToZZTo4L_M120_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 499000,       'UL17': 488000,       'UL18': 489000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 499000.0,     'UL17': 488000.0,     'UL18': 489000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 2044527.5477, 'UL17': 1999340.3576, 'UL18': 2003624.3584}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)

    name = 'VBF_HToZZTo4L_M124'
    DAS_Names = {
        # 'UL16preVFP': Storage_DAS('/VBF_HToZZTo4L_M124_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM'),
        'UL16postVFP': Storage_DAS('/VBF_HToZZTo4L_M124_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/VBF_HToZZTo4L_M124_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/VBF_HToZZTo4L_M124_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 500000,        'UL17': 500000,      'UL18': 410000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 500000.0,      'UL17': 500000.0,    'UL18': 410000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 1983832.4496,  'UL17': 1983546.437, 'UL18': 1626467.4004}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)

    name = 'VBF_HToZZTo4L_M126'
    DAS_Names = {
        # 'UL16preVFP': Storage_DAS('/VBF_HToZZTo4L_M126_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM'),
        'UL16postVFP': Storage_DAS('/VBF_HToZZTo4L_M126_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/VBF_HToZZTo4L_M126_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/VBF_HToZZTo4L_M126_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 468000,        'UL17': 500000,       'UL18': 475000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 468000.0,      'UL17': 500000.0,     'UL18': 475000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 1827124.04626, 'UL17': 1951914.8045, 'UL18': 1854433.99902}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)

    name = 'VBF_HToZZTo4L_M130'
    DAS_Names = {
        # 'UL16preVFP': Storage_DAS('/VBF_HToZZTo4L_M130_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM'),
        'UL16postVFP': Storage_DAS('/VBF_HToZZTo4L_M130_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/VBF_HToZZTo4L_M130_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/VBF_HToZZTo4L_M130_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 479000,        'UL17': 498000,      'UL18': 483000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 475000.0,      'UL17': 498000.0,    'UL18': 479000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 1779240.40318, 'UL17': 1865338.487, 'UL18': 1794152.66862}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)


def Add_Signals_GluGlu(SampleContainer):
    type = 'MC'
    name = 'GluGluHToZZTo4L_M125'
    DAS_Names = {
        'UL16postVFP': Storage_DAS('/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/GluGluHToZZTo4L_M125_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 1000000,      'UL17': 998000,       'UL18': 940000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 1000000.0,    'UL17': 998000.0,     'UL18': 940000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 28869643.666, 'UL17': 28814099.991, 'UL18': 27138279.5348}),
    }
    modes = [['standard'],['pfcands'], ['extrajets'], ['stablegenparticles']]
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)

    name = 'GluGluHToZZTo4L_M120'
    DAS_Names = {
        'UL16postVFP': Storage_DAS('/GluGluHToZZTo4L_M120_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/GluGluHToZZTo4L_M120_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/GluGluHToZZTo4L_M120_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 1000000,       'UL17': 1000000,      'UL18': 990000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 1000000.0,     'UL17': 1000000.0,    'UL18': 990000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 31017227.6888, 'UL17': 31011962.474, 'UL18': 30712785.107}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)

    name = 'GluGluHToZZTo4L_M124'
    DAS_Names = {
        'UL16postVFP': Storage_DAS('/GluGluHToZZTo4L_M124_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/GluGluHToZZTo4L_M124_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/GluGluHToZZTo4L_M124_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 989000,        'UL17': 994000,        'UL18': 994000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 989000.0,      'UL17': 994000.0,      'UL18': 994000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 28965270.4862, 'UL17': 29114927.1322, 'UL18': 29107175.0076}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)


    name = 'GluGluHToZZTo4L_M126'
    DAS_Names = {
        'UL16postVFP': Storage_DAS('/GluGluHToZZTo4L_M126_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/GluGluHToZZTo4L_M126_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/GluGluHToZZTo4L_M126_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 999000,       'UL17': 994000,        'UL18': 957000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 999000.0,     'UL17': 994000.0,      'UL18': 957000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 28442284.516, 'UL17': 28306472.6556, 'UL18': 27253642.9674}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)

    name = 'GluGluHToZZTo4L_M130'
    DAS_Names = {
        'UL16postVFP': Storage_DAS('/GluGluHToZZTo4L_M130_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM'),
        'UL17': Storage_DAS('/GluGluHToZZTo4L_M130_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM'),
        'UL18': Storage_DAS('/GluGluHToZZTo4L_M130_TuneCP5_13TeV_powheg2_JHUGenV7011_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'),
        }
    years = DAS_Names.keys()
    default_info = {
        'type': type, 'minipaths': YearDependentContainer(DAS_Names),
        'group': YearDependentContainer(dict.fromkeys(years, name)),
        'nevents_das':       YearDependentContainer({'UL16postVFP': 1000000,       'UL17': 996000,       'UL18': 992000}),
        'nevents_generated': YearDependentContainer({'UL16postVFP': 1000000.0,     'UL17': 996000.0,     'UL18': 992000.0}),
        'nevents_weighted':  YearDependentContainer({'UL16postVFP': 26955694.4126, 'UL17': 26849461.527, 'UL18': 26737018.1176}),
    }
    Add_Generic_Sample(SampleContainer, name, modes, years, Storage_T2ULB, '/store/user/anmalara/Tuples/', get_common_path(), default_info)


    # name = 'GluGluToZH_HToZZTo4L_M125'
    # DAS_Names = {
    #     'UL18': Storage_DAS('/GluGluToZH_HToZZTo4L_M125_TuneCP5_13TeV-jhugenv723-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'),
    #     }
    # years = DAS_Names.keys()
    # xsecs = YearDependentContainer()
    # nevents_das = YearDependentContainer({'UL18': 979940})
    # nevents_generated = YearDependentContainer({'UL18': 0})
    # nevents_weighted = YearDependentContainer({'UL18': 0})
    # default_info = {
    #     'type': type, 'group': GetValuesForAllYear(name,years), 'minipaths': YearDependentContainer(DAS_Names),
    #     'xsecs': xsecs, 'nevents_das': nevents_das, 'nevents_generated': nevents_generated, 'nevents_weighted': nevents_weighted,
    # }
    # modes = ['standard','pfcands', 'standard_plus_pfcands']
    # Add_Generic_Sample(SampleContainer, name, modes, years, default_info)


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
