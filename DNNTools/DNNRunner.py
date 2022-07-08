import os
import numpy as np
import pandas as pd
from utils import timeit
from DNNTools.DNNRunnerBase import DNNRunnerBase


class DNNRunner(DNNRunnerBase):
    def __init__(self, dnnparameters, input_base_path, output_base_path, year, samples):
        self.dnnparameters = dnnparameters
        self.input_base_path  = input_base_path
        self.output_base_path = output_base_path
        _samples = {}
        for (key, value) in samples.items():
            _val = value
            _val['filename'] = _val['filename'].replace('year',year)
            _samples[key.replace('year',year)] = _val
        DNNRunnerBase.__init__(self, self.dnnparameters, _samples)
        self.DefinePaths()

    def DefinePaths(self):
        paths = {
            'root':             os.path.join(self.input_base_path),
            'raw':              os.path.join(self.output_base_path, 'raw'),
            'preproc':          os.path.join(self.output_base_path, 'preproc'),
            'plot_inputs':      os.path.join(self.output_base_path, 'plots','InputDistributions'),
            'train':            os.path.join(self.output_base_path, 'train', self.dnnparameters['modelName']),
            'predictions':      os.path.join(self.output_base_path, 'train', self.dnnparameters['modelName']),
            'plot_predictions': os.path.join(self.output_base_path, 'plots','Predictions'),

        }
        self.DefinePathsBase(**paths)

    def CreateConverter(self):
        from ConvertRootToInputs import ConvertRootToInputs
        self.ConvertRootToInputs = ConvertRootToInputs(self.filepath['root'], self.filepath['raw'], samples=self.samples)

    def CreateInputProcessor(self):
        from PreprocessInputs import PreprocessInputs
        self.PreprocessInputs = PreprocessInputs(self.filepath['raw'], self.filepath['preproc'], samples=self.samples, classes=self.dnnparameters['classes'])

    def CreatePlotter(self):
        from Plotter import Plotter
        self.Plotter = Plotter(classes=self.dnnparameters['classes'])

    def PlotInputs(self):
        self.CreatePlotter()
        self.LoadInputs()
        self.Plotter.PlotDF(dfs=self.inputs, weights=self.weights, labels=self.labels, outdir=self.filepath['plot_inputs'])

    def CreateTraining(self):
        from Training import Training
        self.LoadInputs()
        self.Training = Training(DNNparams=self.dnnparameters, inputdir=self.filepath['preproc'], outputdir=self.filepath['train'])
        self.Training.LoadInputs(self.inputs, self.labels, self.weights)

    def Train(self):
        self.CreateTraining()
        self.Training.Train()

    def PlotPredictions(self):
        from Plotter import Plotter
        self.PlotterPredictions = Plotter(classes=self.dnnparameters['classes'])
        self.LoadPredictions()
        self.PlotterPredictions.PlotDF(dfs=self.predictions, weights=self.weights, labels=self.labels, outdir=self.filepath['plot_predictions'])
        self.PlotterPredictions.PlotPerformance(predictions=self.predictions['test'], weights=self.weights['test'], labels=self.labels['test'], outdir=self.filepath['plot_predictions'])
