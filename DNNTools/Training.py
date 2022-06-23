from DNNTools.TrainingBase import *

class Training(TrainingBase):
    def __init__(self, DNNparams={}, inputdir='', outputdir=''):
        TrainingBase.__init__(self, DNNparams=DNNparams, inputdir=inputdir, outputdir=outputdir)
        self.modes = ['train','val','test']

    def LoadInputs(self, format='csv'):
        import numpy as np
        import pandas as pd
        from DNNTools.DNNutils import LoadPandas
        self.inputs = {}
        self.index = {}
        self.labels = {}
        self.weights = {}
        for mode in self.modes:
            self.inputs[mode]  = LoadPandas(os.path.join(self.inputdir, 'input_%s_%s.%s' %(mode,self.frac,format) ))
            self.inputs[mode]  = self.inputs[mode].filter(regex='non_higgs')
            self.index[mode]   = self.inputs[mode].index
            self.inputs[mode]  = self.inputs[mode].to_numpy()
            self.labels[mode]  = np.load(os.path.join(self.inputdir, 'label_%s_%s.npy' %(mode,self.frac) ))
            self.weights[mode] = pd.read_pickle(os.path.join(self.inputdir, 'weights_%s_%s.pkl' %(mode,self.frac) )).to_numpy()
            self.weights[mode] = LoadPandas(os.path.join(self.inputdir, 'weights_%s_%s.%s' %(mode,self.frac,format)))

    def MakeModel(self):
        from DNNTools.Models import SequentialModel
        self.model = SequentialModel(input_shape = (self.inputs['train'].shape[1],), output_shape=self.labels['train'].shape[1], params=self.DNNparams)

    def DefineCallbacks(self):
        from DNNTools.CallBacksBase import PlotOnTrainingBase
        self.callbacks = DefineCallbacksBase(self.modelpath)
        self.callbacks.append(PlotOnTrainingBase(modelPath=self.modelpath, eachEpoch=True))

    def SavePredictions(self, format='csv'):
        from DNNTools.DNNutils import SavePandas
        for mode in self.modes:
            SavePandas(self.predictions[mode], os.path.join(self.outputdir,'prediction_%s_%s.%s' %(mode,self.frac,format)))
