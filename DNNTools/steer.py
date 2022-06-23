#!/usr/bin/env python
import os, sys, ROOT
from collections import OrderedDict
from DNNTools.SampleSettings import SampleSettings
from DNNRunner import DNNRunner

# All constants to be used
user             = os.environ['USER']
# input_base_path  = '/pnfs/iihe/cms/store/user/'+user+'/Analyses/VBFTagger/year/PFStudies'
# input_base_path = '/user/'+user+'/WorkingArea/DNNOutputs/DNN/root/GenLevelStudies'
input_base_path = '/user/'+user+'/WorkingArea/DNNOutputs/DNN/root/PFStudies'
output_base_path = '/user/'+user+'/WorkingArea/DNNOutputs'

samples = {
    'VBF_M125':    SampleSettings(filename='MC__VBF_HToZZTo4L_M125_standard_year.root', samplename='VBF_M125', category='VBF'),
    'VBF_M120':    SampleSettings(filename='MC__VBF_HToZZTo4L_M120_standard_year.root', samplename='VBF_M120', category='VBF'),
    'VBF_M124':    SampleSettings(filename='MC__VBF_HToZZTo4L_M124_standard_year.root', samplename='VBF_M124', category='VBF'),
    'VBF_M126':    SampleSettings(filename='MC__VBF_HToZZTo4L_M126_standard_year.root', samplename='VBF_M126', category='VBF'),
    'VBF_M130':    SampleSettings(filename='MC__VBF_HToZZTo4L_M130_standard_year.root', samplename='VBF_M130', category='VBF'),
    'GluGlu_M125': SampleSettings(filename='MC__GluGluHToZZTo4L_M125_standard_year.root', samplename='GluGlu_M125', category='GluGlu'),
    'GluGlu_M120': SampleSettings(filename='MC__GluGluHToZZTo4L_M120_standard_year.root', samplename='GluGlu_M120', category='GluGlu'),
    'GluGlu_M124': SampleSettings(filename='MC__GluGluHToZZTo4L_M124_standard_year.root', samplename='GluGlu_M124', category='GluGlu'),
    'GluGlu_M126': SampleSettings(filename='MC__GluGluHToZZTo4L_M126_standard_year.root', samplename='GluGlu_M126', category='GluGlu'),
    'GluGlu_M130': SampleSettings(filename='MC__GluGluHToZZTo4L_M130_standard_year.root', samplename='GluGlu_M130', category='GluGlu'),

}

dnnparameters = OrderedDict()
dnnparameters['DenseLayer'] = [256, 50, 10]
# dnnparameters['batchsize'] =  131072
dnnparameters['batch_size'] =  128
dnnparameters['classes'] = {'VBF':1, 'GluGlu':0}
dnnparameters['regularization_method'] =  'dropout'
dnnparameters['regularization_rate'] = 0.01
dnnparameters['batchnorm'] =  False
dnnparameters['epochs'] =  2
dnnparameters['learningrate'] =  0.00050
dnnparameters['runonfraction'] =  1.00
dnnparameters['eqweight'] = False
dnnparameters['activation'] = 'relu'
dnnparameters['kernel_initializer'] = 'glorot_normal'
dnnparameters['bias_initializer'] = 'ones'
dnnparameters['activation_last'] = 'softmax'
dnnparameters['optimizer'] = 'adam' #'adamax'
dnnparameters['metrics'] = ['accuracy']

def main():
    years = ['UL17', 'UL18']
    years = ['RunII']
    for year in years:
        Classifier = DNNRunner(dnnparameters=dnnparameters, input_base_path=input_base_path, output_base_path=output_base_path, year=year, samples=samples)
        # Classifier.CreateConverter()
        # Classifier.ConvertRootToInputs.Convert()
        # Classifier.CreateInputProcessor()
        # Classifier.PreprocessInputs.Process()
        # Classifier.CreatePlotter()
        # Classifier.DoPlots()
        Classifier.CreateTraining()
        Classifier.Training.Train()


if __name__ == '__main__':
    main()
