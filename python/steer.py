#! /usr/bin/env python
from ModuleRunner import ModuleRunner

def main():

    years = ['UL16postVFP', 'UL17', 'UL18']
    # years = ['UL16postVFP', 'UL17']
    # years = ['UL16postVFP']
    # years = ['UL17']
    # years = ['UL18']

    ModuleName = 'GenLevelStudies'
    ModuleName = 'PFStudies'

    # years = ['UL18']
    MR = ModuleRunner(years, ModuleName)
    # MR.CleanWorkdirs()
    # MR.CreateConfigFiles()
    # MR.Split()
    # MR.Submit()
    MR.CheckStatus()
    # MR.Resubmit()
    # MR.RunLocal()
    # MR.Merge()
    # MR.MergeRunII()



if __name__ == '__main__':
    print('Start main')
    main()
