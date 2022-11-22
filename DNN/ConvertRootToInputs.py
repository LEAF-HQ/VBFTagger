from DNNTools.ConvertRootToInputsBase import *

class ConvertRootToInputs(ConvertRootToInputsBase):
    def __init__(self, inputdir, outdir, samples):
        chunksize = 500
        run_on = '2'
        run_on = 'htcondor'
        treename = 'AnalysisTree'
        namebranch_weight = ('Events.GenEvent.Event.weight','event_weight')
        # ConvertRootToInputsBase.__init__(self, inputdir=inputdir, outdir=outdir, chunksize=chunksize, max_files_per_pool=max_files_per_pool, treename=treename, namebranch_weight=namebranch_weight)
        ConvertRootToInputsBase.__init__(self, inputdir=inputdir, outdir=outdir, chunksize=chunksize, treename=treename, namebranch_weight=namebranch_weight, run_on=run_on)
        self.LoadDependancies('libLEAFVBFTagger.so')
        self.samples = samples

    def DefineSamples(self):
        return self.samples

    def GetVariables(self, varName, properties = ['pt', 'eta', 'phi', 'm'], min=0, max=100):
        for i in range(min, max):
            for var in properties:
                self.var_names.append(('Events.%s.m_%s[%i]' % (varName, var, i), 0., 1))
                self.col_names.append('%s%i_%s' % (varName, i, var))

    def DefineVariables(self):
        self.var_names = []
        self.col_names = []
        # self.GetVariables(varName='gen_non_higgs_decays', max=100)
        # self.GetVariables(varName='VBF_genjets', max=2)
        self.GetVariables(varName='VBF_jets', max=2, properties = ['pt', 'eta', 'phi', 'm', 'score_qgl', 'n_constituents'])
        self.GetVariables(varName='non_VBF_jets', max=5, properties = ['pt', 'eta', 'phi', 'm', 'score_qgl', 'n_constituents'])
        properties=['pt','eta','phi','m', 'pdgid', 'charge', 'puppiweight']
        for pfName in ['PF_VBF','PF_UE_charged','PF_UE_neutrals']:
            self.GetVariables(varName=pfName, max=200, properties=properties)
            self.var_names.append('Events.m_%s' % (pfName+'_size'))
            self.col_names.append('%s' % (pfName+'_size'))
        for pfName in ['eventCategory','Zeppenfeld','Zeppenfeld_charged','Zeppenfeld_neutral',
                       'energy_density_ratio','energy_density_ratio_charged','energy_density_ratio_neutral',
                       'n_nonVBF_jets','HT_nonVBF_jets','n_PF_jet1','n_PF_jet2']:
            self.var_names.append('Events.m_%s' % (pfName))
            self.col_names.append('%s' % (pfName))
        return (self.var_names,self.col_names)
