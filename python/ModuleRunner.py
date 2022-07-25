import os
from printing_utils import green, blue, prettydict
from utils import ensureDirectory
from parallelize import parallelize
from CreateConfigFiles import CreateConfigFiles
from Samples.Sample import SampleContainer
from VBFTagger.Tuplizer.Signals_VBF import Add_Signals_VBFAnalysis
from ModuleRunnerBase import VariablesBase, ModuleRunnerBase

class ModuleRunner(VariablesBase):
    ''' Class container for list of objects for particular year '''
    def __init__(self, years, ModuleName):
        VariablesBase.__init__(self)
        self.years = years
        self.ModuleName = ModuleName
        self.MRB = {}
        for year in years:
            self.MRB[year] = ModuleRunnerBase(year, ModuleName)
        self.ncores = 3
        print(self)

    def __str__(self):
        print(blue('--> ModuleRunner info:'))
        prettydict(self.__dict__)
        return blue('--> ModuleRunner info: end.')

    def CompileCode(self):
        os.system('cd '+self.analysis_path+'; make -j 4; cd -')

    def CreateConfigFiles(self):
        AllSamples = SampleContainer()
        Add_Signals_VBFAnalysis(AllSamples)
        xmlfilename = os.path.join(self.config_path,self.ModuleName+'Config.xml')
        CCF = CreateConfigFiles(xmlfilename= xmlfilename, years = self.years, AllSamples=AllSamples)
        CCF.modifyAllSettings()

    def RunAnalyser(self, options):
        commands = []
        path = os.path.join(self.config_path, 'workdir_'+self.ModuleName)
        for year in self.years:
            xmlfilename = os.path.join(self.config_path, 'workdir_'+self.ModuleName, self.ModuleName+'Config_'+year+'.xml')
            commands.append([path, 'submit.py %s -%s' %(xmlfilename, options)])
        a = parallelize(commands, ncores=self.ncores, cwd=True, remove_temp_files=False)

    def CleanWorkdirs(self):
        self.RunAnalyser(options='c')

    def Split(self):
        self.RunAnalyser(options='d')

    def Submit(self):
        self.CompileCode()
        self.RunAnalyser(options='s')

    def Resubmit(self):
        self.RunAnalyser(options='s')

    def CheckStatus(self):
        self.RunAnalyser(options='o')

    def Merge(self):
        self.RunAnalyser(options='f')
        # self.RunAnalyser(options='p')

    def RunLocal(self,ncores=4):
        import glob, sys
        if not ncores:
            ncores = self.ncores
        print(green('--> Locally running jobs on %i cores' % (ncores)))
        commands = []
        path = os.path.join(self.config_path, 'workdir_'+self.ModuleName)
        for year in self.years:
            for missing_files in glob.glob(os.path.join(self.config_path, 'workdir_'+self.ModuleName, 'workdir_'+self.ModuleName+'Config_'+year,'*','commands_missing_files.txt')):
                with open(missing_files, 'r') as f:
                    for l in f.readlines():
                        commands.append(l.rstrip('\n'))
        commands = [[self.config_path, c] for c in commands]
        parallelize(commands, ncores=ncores, cwd=True)
        print(green('--> Finished running missing jobs locally.'))

    def MergeRunII(self):
        runII_dir = os.path.join(self.analysis_outpath,'RunII',self.ModuleName)
        ensureDirectory(runII_dir)
        commands = []
        for group, samples in self.groups.items():
            for sample in samples:
                # for mode in ['','_standard_RunII']:
                for mode in ['_standard_RunII']:
                    new_file = os.path.join(runII_dir,'MC__'+sample+mode+'.root')
                    command = ['hadd', '-f', new_file]
                    for year in self.years:
                        command.append(new_file.replace('RunII',year))
                    commands.append(command)
        parallelize(commands, ncores=4, remove_temp_files=False)
