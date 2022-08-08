#!/usr/bin/env python
print('Start import')
import os, sys, yaml, glob, argparse, ROOT
from collections import OrderedDict
from DNNTools.SampleSettings import SampleSettings
from DNN.DNNRunner import DNNRunner

def OpenJsonAndRun(fname):
    with open(fname, 'r') as f:
        print('Running on: '+fname)
        dnnparameters = yaml.safe_load(f)
        RunCommands(dnnparameters)

def main():
    print('Start main')
    parser = argparse.ArgumentParser()
    parser.add_argument('--json', '-j', action='store', dest='json', default='None')
    args = parser.parse_args()

    json_files = []

    if args.json == 'None':
        print('Running on: default')
        dnnparameters = OrderedDict([
            ('modelName',             'train_with_weights_scale_xsec_with_charge'),
            # ('filterInputs',          'gen_non_higgs_decays'),
            # ('filterInputs',          'VBF_genjets'),
            # ('filterInputs',          'VBF_jets'),
            # ('filterInputs',          'PF_VBF'),
            # ('filterInputs',          'PF_UE_charged'),
            # ('filterInputs',          'PF_UE_neutrals'),
            # ('filterInputs',          ['VBF_jets','PF_VBF']),
            # ('filterInputs',          ['PF_UE_charged','PF_UE_neutrals']),
            # ('filterInputs',          ['VBF_jets', 'PF_UE_charged','PF_UE_neutrals']),
            ('filterInputs',          ['PF_VBF', 'PF_UE_charged','PF_UE_neutrals']),
            # ('filterInputs',          ['VBF_jets','PF_VBF','PF_UE_charged','PF_UE_neutrals']),
            ('DenseLayer',            [50, 50, 10]),
            # ('DenseLayer',            [1000, 500, 100, 50, 10]),
            ('batch_size',            1024),
            ('classes',               {'VBF':1, 'GluGlu':0}),
            ('regularization_method', 'dropout'),
            ('regularization_rate',   0.01),
            ('batchnorm',             True),
            ('epochs',                10),
            ('learningrate',          0.01),
            ('runonfraction',         1.00),
            ('eqweight',              True),
            ('kernel_initializer',    'glorot_normal'),
            ('bias_initializer',      'ones'),
            ('activation_first',      'relu'),
            ('activation_hidden',     'tanh'),
            ('activation_last',       'softmax'),
            # ('activation_last',       'sigmoid'),
            ('optimizer',             'adam'), #'adamax'
            ('metrics',               ['accuracy']),
            ('LSTMLayer',             64),
        ])
        RunCommands(dnnparameters)
    elif args.json != 'all':
        OpenJsonAndRun(args.json)
    else:
        runLocal = True
        runLocal = False
        json_files = glob.glob('MyModels/*json')
        json_files = ['MyModels/VBF_jets_train_with_weights_scale_xsec_0001.json',
        'MyModels/VBF_jets_PF_VBF_train_with_weights_scale_xsec_0005.json',
        'MyModels/VBF_jets_PF_VBF_PF_UE_charged_PF_UE_neutrals_train_with_weights_scale_xsec_0009.json',
        'MyModels/VBF_jets_PF_UE_charged_PF_UE_neutrals_train_with_weights_scale_xsec_0007.json',
        'MyModels/PF_VBF_train_with_weights_scale_xsec_0002.json',
        'MyModels/PF_VBF_PF_UE_charged_PF_UE_neutrals_train_with_weights_scale_xsec_0008.json',
        'MyModels/PF_UE_neutrals_train_with_weights_scale_xsec_0004.json',
        'MyModels/PF_UE_charged_train_with_weights_scale_xsec_0003.json',
        'MyModels/PF_UE_charged_PF_UE_neutrals_train_with_weights_scale_xsec_0006.json',
        'MyModels/VBF_jets_non_VBF_jets_train_with_weights_scale_xsec_0010.json',
        'MyModels/VBF_jets_non_VBF_jets_eventCategory-3_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0018.json',
        'MyModels/VBF_jets_non_VBF_jets_eventCategory-2_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0019.json',
        'MyModels/eventCategory_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0017.json',
        'MyModels/eventCategory-3_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0011.json',
        'MyModels/eventCategory2_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0016.json',
        'MyModels/eventCategory-2_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0012.json',
        'MyModels/eventCategory1_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0015.json',
        'MyModels/eventCategory-1_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0013.json',
        'MyModels/eventCategory0_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0014.json',
        'MyModels/VBF_jets_non_VBF_jets_eventCategory_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0024.json',
        'MyModels/VBF_jets_non_VBF_jets_eventCategory2_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0023.json',
        'MyModels/VBF_jets_non_VBF_jets_eventCategory1_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0022.json',
        'MyModels/VBF_jets_non_VBF_jets_eventCategory-1_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0020.json',
        'MyModels/VBF_jets_non_VBF_jets_eventCategory0_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0021.json',
        'MyModels/all_train_with_weights_scale_xsec_0025.json']
        # for f in json_files:
        #     if not os.path.exists(f):
        #         print f
        #         sys.exit()
        # json_files = list(filter(lambda x: 'PF_noHiggs' in x or 'gen_non_higgs_decays' in x, json_files))
        # json_files = list(filter(lambda x: any([y in x for y in ['PF_noHiggs','gen_non_higgs_decays']]), json_files))
        # json_files = list(filter(lambda x: 'PF_noHiggs' in x, json_files))
        # json_files = list(filter(lambda x: 'gen_non_higgs_decays' in x, json_files))
        # json_files = list(filter(lambda x: 'eventCategory-3_Zeppenfeld_energy_density_ratio_nonVBF_jets_train_with_weights_scale_xsec_0011' in x, json_files))
        print('Selected files: '+str(len(json_files)))
        if runLocal:
            for json_file in json_files:
                OpenJsonAndRun(json_file)
        else:
            json_files = ['-j '+os.path.abspath(x) for x in json_files]
            print('--> Submitting to htcondor...')
            from Submitter.CondorBase import CondorBase
            CB = CondorBase(JobName='Training', Disk=10)
            CB.CreateJobInfo(executable=os.path.abspath('steer.py'))
            CB.ModifyJobInfo('outdir', 'MyModels/joboutput/')
            CB.SubmitManyJobs(job_args=json_files)

def RunCommands(dnnparameters_):
    # All constants to be used
    user             = os.environ['USER']
    module           = 'GenLevelStudies'
    # input_base_path  = '/pnfs/iihe/cms/store/user/anmalara/Analyses/VBFTagger/RunII/'+module+'/'
    module           = 'PFStudies'
    input_base_path  = '/user/'+user+'/WorkingArea/DNNOutputs/'+module+'/root/'
    input_base_path  = '/pnfs/iihe/cms/store/user/anmalara/Analyses/VBFTagger/RunII/'+module+'/'
    output_base_path = '/user/'+user+'/WorkingArea/DNNOutputs/'+module+'/'
    dtype = 'float16'

    samples = {
        'VBF_M125':    SampleSettings(filename='MC__VBF_HToZZTo4L_M125_standard_year.root',   samplename='VBF_M125',    category='VBF'),
        'VBF_M120':    SampleSettings(filename='MC__VBF_HToZZTo4L_M120_standard_year.root',   samplename='VBF_M120',    category='VBF'),
        'VBF_M124':    SampleSettings(filename='MC__VBF_HToZZTo4L_M124_standard_year.root',   samplename='VBF_M124',    category='VBF'),
        'VBF_M126':    SampleSettings(filename='MC__VBF_HToZZTo4L_M126_standard_year.root',   samplename='VBF_M126',    category='VBF'),
        'VBF_M130':    SampleSettings(filename='MC__VBF_HToZZTo4L_M130_standard_year.root',   samplename='VBF_M130',    category='VBF'),
        'GluGlu_M125': SampleSettings(filename='MC__GluGluHToZZTo4L_M125_standard_year.root', samplename='GluGlu_M125', category='GluGlu'),
        'GluGlu_M120': SampleSettings(filename='MC__GluGluHToZZTo4L_M120_standard_year.root', samplename='GluGlu_M120', category='GluGlu'),
        'GluGlu_M124': SampleSettings(filename='MC__GluGluHToZZTo4L_M124_standard_year.root', samplename='GluGlu_M124', category='GluGlu'),
        'GluGlu_M126': SampleSettings(filename='MC__GluGluHToZZTo4L_M126_standard_year.root', samplename='GluGlu_M126', category='GluGlu'),
        'GluGlu_M130': SampleSettings(filename='MC__GluGluHToZZTo4L_M130_standard_year.root', samplename='GluGlu_M130', category='GluGlu'),
    }

    # years = ['UL17', 'UL18']
    years = ['RunII']
    for year in years:
        Classifier = DNNRunner(dnnparameters=dnnparameters_, input_base_path=input_base_path, output_base_path=output_base_path, year=year, samples=samples, dtype=dtype)
        # Classifier.ConvertInputs()
        Classifier.Preprocess()
        # Classifier.PlotInputs()
        # Classifier.Train()
        # Classifier.UpdatePredictions()
        # Classifier.PlotPredictions()

if __name__ == '__main__':
    main()
