import os
import numpy as np
import pandas as pd
from utils import timeit
from DNNTools.DNNRunnerBase import DNNRunnerBase


class DNNRunner(DNNRunnerBase):
    def __init__(self, dnnparameters, input_base_path, output_base_path, year, samples, dtype):
        self.dnnparameters = dnnparameters
        self.input_base_path  = input_base_path
        self.output_base_path = output_base_path
        _samples = {}
        for (key, value) in samples.items():
            _val = value
            _val['filename'] = _val['filename'].replace('year',year)
            _samples[key.replace('year',year)] = _val
        DNNRunnerBase.__init__(self, self.dnnparameters, _samples, dtype=dtype)
        self.DefinePaths()

    def DefinePaths(self):
        filterInputs = self.dnnparameters['filterInputs']
        if isinstance(filterInputs, list):
            filterInputs = '_'.join(filterInputs)
        paths = {
            'root':             os.path.join(self.input_base_path),
            'raw':              os.path.join(self.output_base_path, 'raw'),
            'preproc':          os.path.join(self.output_base_path, 'preproc', filterInputs),
            'plot_inputs':      os.path.join(self.output_base_path, 'plots','InputDistributions', filterInputs),
            'train':            os.path.join(self.output_base_path, 'train', filterInputs, self.dnnparameters['modelName']),
            'predictions':      os.path.join(self.output_base_path, 'train', filterInputs, self.dnnparameters['modelName']),
            'plot_predictions': os.path.join(self.output_base_path, 'plots','Predictions', filterInputs, self.dnnparameters['modelName']),

        }
        self.DefinePathsBase(**paths)

    def CreateConverter(self):
        from DNN.ConvertRootToInputs import ConvertRootToInputs
        self.ConvertRootToInputs = ConvertRootToInputs(self.filepath['root'], self.filepath['raw'], samples=self.samples)

    def ConvertInputs(self):
        self.CreateConverter()
        self.ConvertRootToInputs.Convert()

    def CreateInputProcessor(self):
        from DNN.PreprocessInputs import PreprocessInputs
        self.PreprocessInputs = PreprocessInputs(self.filepath['raw'], self.filepath['preproc'], samples=self.samples, classes=self.dnnparameters['classes'], dtype=self.dtype)

    def Preprocess(self):
        self.CreateInputProcessor()
        self.PreprocessInputs.Process(filter_regex=self.dnnparameters['filterInputs'])

    def CreatePlotter(self):
        from DNN.Plotter import Plotter
        self.Plotter = Plotter(classes=self.dnnparameters['classes'])

    def PlotInputs(self):
        self.CreatePlotter()
        self.LoadInputs()
        self.Plotter.PlotDF(dfs=self.inputs, weights=self.weights, labels=self.labels, outdir=self.filepath['plot_inputs'])

    def CreateTraining(self):
        from Training import Training
        self.LoadInputs()
        self.Training = Training(DNNparams=self.dnnparameters, inputdir=self.filepath['preproc'], outputdir=self.filepath['train'])
        for mode in self.weights.keys():
            if 'scale' in self.dnnparameters['modelName']:
                self.weights[mode] *= 10000
            if 'xsec' in self.dnnparameters['modelName']:
                self.weights[mode][self.labels[mode]==0] *= 13
        self.Training.LoadInputs(self.inputs, self.labels, self.weights)

    def Train(self):
        from printing_utils import cyan
        self.CreateTraining()
        print (cyan('Inputs for training: '+str(self.inputs['train'].shape)))
        self.Training.Train()

    def UpdatePredictions(self):
        if not hasattr(self, 'Training'):
            self.CreateTraining()
        self.Training.UpdatePredictions()

    def PlotPredictions(self):
        from Plotter import Plotter
        self.PlotterPredictions = Plotter(classes=self.dnnparameters['classes'])
        self.LoadPredictions()
        self.PlotterPredictions.PlotDF(dfs=self.predictions, weights=self.weights, labels=self.labels, outdir=self.filepath['plot_predictions'])
        self.PlotterPredictions.PlotPerformance(predictions=self.predictions['test'], weights=self.weights['test'], labels=self.labels['test'], outdir=self.filepath['plot_predictions'])
