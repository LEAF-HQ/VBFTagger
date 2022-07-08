#!/usr/bin/env python
import os, sys, ROOT
from collections import OrderedDict
from DNNTools.SampleSettings import SampleSettings
from DNNRunner import DNNRunner

# All constants to be used
user             = os.environ['USER']
module           = 'GenLevelStudies'
module           = 'PFStudies'
input_base_path  = '/pnfs/iihe/cms/store/user/anmalara/Analyses/VBFTagger/RunII/'+module+'/'
# input_base_path  = '/user/'+user+'/WorkingArea/DNNOutputs/DNN/root/PFStudies'
output_base_path = '/user/'+user+'/WorkingArea/DNNOutputs/'+module+'/'

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

dnnparameters = OrderedDict([
    ('modelName',             'test_1'),
    ('DenseLayer',            [32, 32, 8]),
    ('batch_size',            1024),
    ('classes',               {'VBF':1, 'GluGlu':0}),
    ('regularization_method', 'dropout'),
    ('regularization_rate',   0.01),
    ('batchnorm',             True),
    ('epochs',                10),
    ('learningrate',          0.0001),
    ('runonfraction',         1.00),
    ('eqweight',              False),
    ('activation',            'relu'),
    ('kernel_initializer',    'glorot_normal'),
    ('bias_initializer',      'ones'),
    ('activation_last',       'softmax'),
    ('optimizer',             'adam'), #'adamax'
    ('metrics',               ['accuracy']),
])

def main():
    # years = ['UL17', 'UL18']
    years = ['RunII']
    for year in years:
        Classifier = DNNRunner(dnnparameters=dnnparameters, input_base_path=input_base_path, output_base_path=output_base_path, year=year, samples=samples)
        # Classifier.CreateConverter()
        # Classifier.ConvertRootToInputs.Convert()
        # Classifier.CreateInputProcessor()
        # Classifier.PreprocessInputs.Process()
        # Classifier.CreatePlotter()
        # Classifier.DoPlots()
        # Classifier.CreateTraining()
        # Classifier.Training.Train()
        Classifier.PlotPredictions()


if __name__ == '__main__':
    main()
