#! /usr/bin/env python

from ModuleRunnerBase import *
from Submitter.CreateConfigFilesBase import *
from VBFTagger.Tuplizer.Signals_VBF import *
from Utils import *

class CreateConfigFiles(VariablesBase, CreateConfigFilesBase):
    def __init__(self, xmlfilename, years, AllSamples):
        VariablesBase.__init__(self)
        CreateConfigFilesBase.__init__(self, xmlfilename=xmlfilename, xmlfilepath=self.config_path, years=years, AllSamples=AllSamples)

    def modifySpecificSettings(self,year):
        self.modifyConfigAttribute('TargetLumi',  ROOT.Year2Lumi[year])
        self.modifyConfigAttribute('JEC_Version', ROOT.JERC_Info[year]['JEC_Version'])
        self.modifyConfigAttribute('JER_Version', ROOT.JERC_Info[year]['JER_Version'])


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('xmlfilename', type=str, help='Name of the XML file')
    parser.add_argument("--years", nargs="+", default=ROOT.Reco2Years['UL'], help='Years to run over')

    args = parser.parse_args()
    xmlfilename = args.xmlfilename
    years       = args.years

    years = ['UL16postVFP', 'UL17', 'UL18']
    # years = ['UL18']
    #xmlfilename = 'GenLevelStudiesConfig.xml'

    AllSamples = SampleContainer()
    Add_Signals_VBFAnalysis(AllSamples)

    CCF = CreateConfigFiles(xmlfilename= xmlfilename, years = years, AllSamples=AllSamples)
    CCF.modifyAllSettings()

if __name__ == '__main__':
    main()
