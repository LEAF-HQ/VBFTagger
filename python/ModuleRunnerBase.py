import os, sys, itertools
from collections import OrderedDict


class GenericPath:
    ''' Class container for paths '''
    def __init__(self):
        self.username   = os.environ['USER']
        self.cmssw_base = os.environ['CMSSW_BASE']
        self.leaf_path       = os.environ['LEAFPATH']
        self.analyzer_path   = os.environ['ANALYZERPATH']
        self.submitter_path  = os.environ['SUBMITTERPATH']
        self.plotter_path    = os.environ['PLOTTERPATH']
        self.samples_path    = os.environ['SAMPLESPATH']
        self.tuplizer_path   = os.environ['TUPLIZERPATH']
        self.analysis_path   = os.environ['ANALYSISPATH']
        self.config_path     = os.environ['ANALYSISPATHCONFIG']
        self.pnfs_path       = os.path.join('/pnfs/iihe/cms/store/user/',self.username)
        self.ntuples_path    = os.path.join(self.pnfs_path,'Tuples')
        self.analysis_outpath= os.path.join(self.pnfs_path,'Analyses')

    def Get(self, path_to):
        return getattr(self,path_to)

    def GetUsername(self):
        return self.Get('username')



class VariablesBase(GenericPath):
    ''' Class container for list of objects '''
    def __init__(self, isAnalysis=True):
        GenericPath.__init__(self)
        self.PrefixrootFile     = 'uhh2.AnalysisModuleRunner.'
        self.Channels           = ['VBFTagger']
        self.Systematics        = ['nominal']
        self.Systematics_Scale  = []
        # self.SignalSamples      = [self.Signal+mode+'_M'+str(mass) for mass in self.MassPoints for mode in ['','_inv']]
        self.RunPeriods_Dict    = {'EOY16': ['B', 'C', 'D', 'E', 'F', 'G', 'H'],
                                   'EOY17': ['B', 'C', 'D', 'E', 'F'],
                                   'EOY18': ['A', 'B', 'C', 'D'],
                                   'UL16preVFP': ['B', 'C', 'D', 'E', 'Ferly'],
                                   'UL16preVFP': ['Flate', 'G', 'H'],
                                   'UL17': ['B', 'C', 'D', 'E', 'F'],
                                   'UL18': ['A', 'B', 'C', 'D'],
                                   }
        self.years              = sorted(self.RunPeriods_Dict.keys())
        self.AllRunPeriods      = list(set(itertools.chain.from_iterable(self.RunPeriods_Dict.values())))

    #     self.defineGroups()
    #
    # def GetGroup(self,sample):
    #     for group, samples in self.groups.items():
    #         if sample in samples:
    #             return group
    #     return None

    def defineGroups(self):
        self.groups = OrderedDict()
        for year in self.RunPeriods_Dict:
            self.groups["VBF"] = ['VBF_HToZZTo4L_M125']
            self.groups["WH_HToZZTo4L"] = ['WminusH_HToZZTo4L_M125','WplusH_HToZZTo4L_M125']
            self.groups["GluGlu"] = ['GluGluHToZZTo4L_M125','GluGluToZH_HToZZTo4L_M125','GluGluHToZZTo4Mu_M125']

    # def defineType(self):
    #     self.groups = OrderedDict()
    #     for year in self.RunPeriods_Dict:
    #         self.groups["VBF"] = ['VBF_HToZZTo4L_M125']




class ModuleRunnerBase(VariablesBase):
    ''' Class container for list of objects for particular year '''
    def __init__(self,year='2016', isAnalysis=True):
        VariablesBase.__init__(self, isAnalysis=isAnalysis)
        self.year = year
        self.defineDirectories()
        self.lumi_fb  = round(float(self.lumi_map[self.year]['lumi_fb']),1)
        self.lumi_pb  = int(self.lumi_map[self.year]['lumi_pb'])
        self.lumi_sys = round(float(self.lumi_map[self.year]['uncertainty']),1)
        self.Samples_Dict    = self.Samples_Year_Dict[self.year]
        self.SubSamples_Dict = self.SubSamples_Year_Dict[self.year]
        self.Processes_Dict  = self.Processes_Year_Dict[self.year]

    def defineDirectories(self):
        self.Path_SFRAME        = self.Path_SFRAME+self.year+'/'
        self.ConfigDir          = self.Path_ANALYSIS+'config/'
        self.SubmitDir          = self.ConfigDir+'SubmittedJobs/'+self.year+'/'
