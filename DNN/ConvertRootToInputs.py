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
        self.GetVariables(varName='gen_non_higgs_decays', max=100)
        self.GetVariables(varName='VBF_genjets', max=2)
        self.GetVariables(varName='VBF_jets', max=2)
        properties=['pt','eta','phi','m', 'pdgid', 'charge', 'puppiweight']
        for pfName in ['PF_VBF','PF_UE_charged','PF_UE_neutrals']:
            self.GetVariables(varName=pfName, max=200, properties=properties)
            self.var_names.append('Events.m_%s' % (pfName+'_size'))
            self.col_names.append('%s' % (pfName+'_size'))
        return (self.var_names,self.col_names)


# for v in ['m_pt', 'm_eta', 'm_phi', 'm_m']:
#     for i in range(2):
#         var_names.append(('Events.jets_ak4chs.%s[%i]' % (v, i), 0., 1))
#         col_names.append('jet_%s_%i' % (v.replace('m_',''), i))
# var_names.append(('Events.gen_higgs.m_%s[1]' % var , 0., 1))
# col_names.append('gen_higgs_'+var)
# for i in range(2):
#     var_names.append(('Events.gen_higgs_Z.m_%s[%i]' % (var, i), 0., 1))
#     col_names.append('gen_Z%i_%s' % (i, var))
# for i in range(4):
#     var_names.append(('Events.gen_higgs_leptons.m_%s[%i]' % (var, i), 0., 1))
#     col_names.append('gen_lep%i_%s' % (i, var))
# for i in range(30):
#     var_names.append(('Events.gen_higgs_decays.m_%s[%i]' % (var, i), 0., 1))
#     col_names.append('gen_higgs_decays%i_%s' % (i, var))
# for i in range(50):
