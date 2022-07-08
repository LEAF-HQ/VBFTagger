from DNNTools.PreprocessInputsBase import *
from sklearn.compose import ColumnTransformer

class PreprocessInputs(PreprocessInputsBase):
    def __init__(self, inputdir, outdir, samples, classes, maxfiles_per_sample=None):
        PreprocessInputsBase.__init__(self, inputdir=inputdir, outdir=outdir)
        self.samples = samples
        self.classes = classes

    def DefineSamples(self):
        return self.samples

    def DefineClasses(self):
        return self.classes

    def FitScalers(self):
        from sklearn import preprocessing
        self.scalers = {}
        # self.scalers['standard'] = ColumnTransformer(list((col+'st',preprocessing.StandardScaler() if 'pt' in col else preprocessing.FunctionTransformer(), [col]) for col in self.inputs['train'].columns.tolist()))
        # self.scalers['standard'].fit(self.inputs['train'])

    def Process(self):
        self.GetInputs(format='pkl')
        self.RemoveNanInf(df=self.df)
        self.SampleEvents(fraction=self.runonfraction, random_state=42)
        self.Split(ratios={'train':0.7, 'validation':0.15, 'test':0.15})
        self.FitScalers()
        self.Transform()
        self.Save()
