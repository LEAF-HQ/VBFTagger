#!/usr/bin/env python
import os, sys, ROOT
from collections import OrderedDict
from DNNTools.SampleSettings import SampleSettings
from DNNRunner import DNNRunner

# All constants to be used
user             = os.environ['USER']
input_base_path  = '/pnfs/iihe/cms/store/user/'+user+'/Analyses/VBFTagger/year/PFStudies'
output_base_path = '/user/anmalara/WorkingArea/DNNOutputs'

samples = {
    'VBF':    SampleSettings(filename='MC__VBF_HToZZTo4L_M125_standard_year.root', samplename='VBF', category='VBF'),
    'GluGlu': SampleSettings(filename='MC__GluGluHToZZTo4L_M125_standard_year.root', samplename='GluGlu', category='GluGlu'),
}

dnnparameters = OrderedDict()
dnnparameters['DenseLayer'] = [256, 50, 10]
# dnnparameters['batchsize'] =  131072
dnnparameters['batch_size'] =  128
dnnparameters['classes'] = {'VBF':1, 'GluGlu':0}
dnnparameters['regularization_method'] =  'dropout'
dnnparameters['regularization_rate'] = 0.01
dnnparameters['batchnorm'] =  False
dnnparameters['epochs'] =  30
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
    Classifier = DNNRunner(dnnparameters=dnnparameters, year='UL18', input_base_path=input_base_path, output_base_path=output_base_path, samples=samples)
    # Classifier.CreateConverter()
    # Classifier.ConvertRootToInputs.Convert()
    # Classifier.CreateInputProcessor()
    # Classifier.PreprocessInputs.Process()
    # Classifier.CreatePlotter()
    # Classifier.Plotter.Plot()
    Classifier.CreateTraining()
    Classifier.LoadInputs()
    Classifier.Training.Train()
    # Classifier.PreprocessInputs(maxfiles_per_sample=None)
    # Classifier.PlotInputs(filepostfix='', plotfoldername='DNNInputDistributions')
    # Classifier.TrainNetwork()
    # Classifier.MakePrediction(filepostfix='')

    # # First network
    # # =============
    # TrainNetwork(parameters)
    # PredictExternal(parameters, inputfolder='input/'+classtag, outputfolder='output/'+tag, filepostfix='')
    # PlotPerformance(parameters, inputfolder='input/'+classtag, outputfolder='output/'+tag, filepostfix='', use_best_model=False, usesignals=[2,4])
    # PlotPerformance(parameters, inputfolder='input/'+classtag, outputfolder='output/'+tag, filepostfix='', plotfolder='Plots/'+tag, use_best_model=True, usesignals=[2,4])
    # PlotInputs(parameters, inputfolder='output/'+tag+'/cut', filepostfix='_pass_best', plotfolder='Plots/'+tag+'/InputDistributions/pass')
    # PlotInputs(parameters, inputfolder='output/'+tag+'/cut', filepostfix='_fail_best', plotfolder='Plots/'+tag+'/InputDistributions/fail')
    # ExportModel(parameters, inputfolder='input/', outputfolder='output/', use_best_model=True)
    # RankNetworks(outputfolder='output/')



if __name__ == '__main__':
    main()
