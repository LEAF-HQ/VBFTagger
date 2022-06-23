import os
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
            'root':    os.path.join(self.input_base_path),
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
        self.EnsureInputsLoaded()
        self.Plotter = Plotter(classes=self.dnnparameters['classes'])

    def DoPlots(self):
        self.Plotter.PlotDF(df=self.inputs, outdir=os.path.join(self.filepath['preproc'],'InputDistributions'))


    def CreateTraining(self):
        from Training import Training
        self.Training = Training(DNNparams=self.dnnparameters, inputdir=self.filepath['preproc'], outputdir=self.filepath['train'])
