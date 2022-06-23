from DNNTools.ConvertRootToInputsBase import *

class ConvertRootToInputs(ConvertRootToInputsBase):
    def __init__(self, inputdir, outdir, samples):
        chunksize = 1000
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

    def DefineVariables(self):
        var_names = []
        col_names = []
        for v in ['m_pt', 'm_eta', 'm_phi', 'm_m']:
            for i in range(2):
                var_names.append(('Events.jets_ak4chs.%s[%i]' % (v, i), 0., 1))
                col_names.append('jet_%s_%i' % (v.replace('m_',''), i))

        for var in ['pt', 'eta', 'phi', 'm']:
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
            for i in range(100):
                var_names.append(('Events.gen_non_higgs_decays.m_%s[%i]' % (var, i), 0., 1))
                col_names.append('gen_non_higgs_decays%i_%s' % (i, var))

        return (var_names,col_names)
