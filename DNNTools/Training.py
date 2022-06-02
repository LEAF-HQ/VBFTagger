import numpy as np
import pandas as pd
from DNNTools.TrainingBase import *
from DNNTools.Models import SequentialModel

class Training(TrainingBase):
    def __init__(self, DNNparams={}, inputdir='', outputdir=''):
        TrainingBase.__init__(self, DNNparams=DNNparams, inputdir=inputdir, outputdir=outputdir)

    def LoadInputs(self):
        self.inputs = {}
        self.labels = {}
        self.weights = {}
        for mode in ['train','val','test']:
            self.inputs[mode]  = pd.read_pickle(os.path.join(self.inputdir, 'input_%s_%s.pkl' %(mode,self.frac) ))
            self.inputs[mode]  = self.inputs[mode].filter(regex='non_higgs')
            self.inputs[mode]  = self.inputs[mode].to_numpy()
            self.labels[mode]  = np.load(os.path.join(self.inputdir, 'label_%s_%s.npy' %(mode,self.frac) ))
            self.weights[mode] = pd.read_pickle(os.path.join(self.inputdir, 'weights_%s_%s.pkl' %(mode,self.frac) )).to_numpy()

    def MakeModel(self):
        self.model = SequentialModel(input_shape = (self.inputs['train'].shape[1],), output_shape=self.labels['train'].shape[1], params=self.DNNparams)
