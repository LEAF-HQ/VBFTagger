import os
from DNNTools.DNNRunnerBase import DNNRunnerBase


class DNNRunner(DNNRunnerBase):
    def __init__(self, dnnparameters, year, input_base_path, output_base_path, samples):
        self.dnnparameters = dnnparameters
        self.year = year
        self.input_base_path  = input_base_path.replace('year',self.year)
        self.output_base_path = output_base_path.replace('year',self.year)
        _samples = {}
        for (key, value) in samples.items():
            _val = value
            _val['filename'] = _val['filename'].replace('year',self.year)
            _samples[key.replace('year',self.year)] = _val
        DNNRunnerBase.__init__(self, self.dnnparameters, self.year, _samples)

        self.DefinePaths()

        # print('input_train', len(self.input_train))
        # print('input_val', len(self.input_val))
        # print('input_test', len(self.input_test))
        # print('label_train', len(self.label_train))
        # print('label_val', len(self.label_val))
        # print('label_test', len(self.label_test))
        # print('weights_train', len(self.weights_train))
        # print('weights_val', len(self.weights_val))
        # print('weights_test', len(self.weights_test))
        # self.PreprocessInputs  = PreprocessInputs
        # PreprocessInputsOld(self, None)

        # self.PlotInputs  = PlotInputs.PlotInputs
        # self.TrainNetwork  = TrainNetwork.TrainNetwork

    def DefinePaths(self):
        paths = {
            # 'root':    self.input_base_path,
            'root':    os.path.join(self.output_base_path, 'DNN', 'root'),
            'raw':     os.path.join(self.output_base_path, 'DNN', 'raw'),
            'preproc': os.path.join(self.output_base_path, 'DNN', 'preproc'),
            'input':   os.path.join(self.output_base_path, 'DNN', 'input'),
            'train':   os.path.join(self.output_base_path, 'DNN', 'train'),
            'plots':   os.path.join(self.output_base_path, 'DNN', 'plots'),
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
        self.Plotter = Plotter(self.filepath['preproc'], os.path.join(self.filepath['preproc'],'InputDistributions'), classes=self.dnnparameters['classes'])

    def CreateTraining(self):
        from Training import Training
        self.Training = Training(DNNparams=self.dnnparameters, inputdir=self.filepath['preproc'], outputdir=self.filepath['train'])
