import glob, ROOT

import pandas as pd
from root_numpy import root2array, rec2array

ROOT.gSystem.Load('libLEAFClasses.so')
ROOT.gSystem.Load('libLEAFVBFTagger.so')

def main():
    path =  '/pnfs/iihe/cms/store/user/anmalara/Tuples/*/Summer20/MINIAODv2/NTuples_v01/standard/'

    for year in glob.glob(path):
        # print('Checking '+year)
        for sample in glob.glob(year+'/*'):
            if not 'GluGluHToZZTo4L_M130' in sample: continue
            print('Checking '+sample)
            for ntuple in glob.glob(sample+'/*'):
                f_ = ROOT.TFile(ntuple)
                t = f_.Get('AnalysisTree')
                count = t.GetEntriesFast()
                f_.Close()
                for fname in glob.glob(ntuple.replace('/standard/','/*/')):
                    if fname==ntuple: continue
                    f_ = ROOT.TFile(fname)
                    t = f_.Get('AnalysisTree')
                    if count!=t.GetEntriesFast():
                        print(count, t.GetEntriesFast(), fname)
                    f_.Close()
                dfs = {}
                for fname in glob.glob(ntuple.replace('/standard/','/*/')):
                    mymatrix = rec2array(root2array(filenames=fname, treename='AnalysisTree', branches=['Events.run', 'Events.lumiblock', 'Events.number']))
                    dfs[fname] = pd.DataFrame(mymatrix,columns=['run','lumiblock','number'])
                for name in dfs:
                    if len(pd.concat([dfs[ntuple],dfs[name]]).drop_duplicates(keep=False))!=0:
                        print (ntuple, name)


if __name__ == '__main__':
    main()
