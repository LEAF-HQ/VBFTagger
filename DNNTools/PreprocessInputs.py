from DNNTools.PreprocessInputsBase import *
from sklearn.compose import ColumnTransformer

class PreprocessInputs(PreprocessInputsBase):
    def __init__(self, inputdir, outdir, samples, classes):
        PreprocessInputsBase.__init__(self, inputdir=inputdir, outdir=outdir)
        self.samples = samples
        self.classes = classes

    def DefineSamples(self):
        return self.samples

    def DefineClasses(self):
        return self.classes

    def FitScalers(self):
        self.scalers = {}
        self.scalers['standard'] = ColumnTransformer(list((col+'st',preprocessing.StandardScaler(), [col]) for col in  self.inputs['train'].columns.tolist()))
        self.scalers['standard'].fit(self.inputs['train'])

    def Process(self):
        self.GetInputs(format='pkl')
        self.RemoveNanInf()
        self.SampleEvents(fraction=self.runonfraction)
        self.Split()
        self.FitScalers()
        self.Transform()
        self.RemoveNanInf()
        self.Save()
