from DNNTools.TrainingBase import *

class Training(TrainingBase):
    def __init__(self, DNNparams={}, inputdir='', outputdir=''):
        TrainingBase.__init__(self, DNNparams=DNNparams, inputdir=inputdir, outputdir=outputdir, do_weights=DNNparams['eqweight'])
        self.modes = ['train','val','test']

    def LoadInputs(self, df_inputs, df_labels, df_weights):
        from DNNTools.DNNutils import FromNumpyToOneHotEncoder
        print('Loading for Training')
        self.inputs  = df_inputs
        self.weights = df_weights
        self.labels  = {}
        for name, df in df_labels.items():
            self.labels[name] = FromNumpyToOneHotEncoder(df)
        print('Loaded for Training')

    def MakeModel(self):
        from DNNTools.Models import SequentialModel
        self.model = SequentialModel(input_shape = (self.inputs['train'].shape[1],), output_shape=self.labels['train'].shape[1], params=self.DNNparams)

    def DefineCallbacks(self):
        from DNNTools.CallBacksBase import PlotOnTrainingBase
        from keras.callbacks import History
        # self.callbacks = DefineCallbacksBase(self.modelpath)
        self.callbacks = [History()]
        self.callbacks.append(PlotOnTrainingBase(modelPath=self.modelpath, eachEpoch=True))

    def SavePredictions(self, format='csv'):
        from DNNTools.DNNutils import SavePandas
        for mode in self.modes:
            SavePandas(self.predictions[mode], os.path.join(self.modelpath,'predictions_%s_%s.%s' %(mode,self.frac,format)))

    def UpdatePredictions(self):
        self.LoadModel()
        self.Predict(column_basename='score', columns=[i for i in range(self.labels['train'].shape[1])])
        self.SavePredictions()
