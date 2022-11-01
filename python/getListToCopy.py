#! /usr/bin/env python

import os, glob

outpath = os.getcwd()+'/lists/'
os.system('mkdir -p '+outpath)

with open(outpath+'ListFilesToCopy.txt', 'w') as fp:
    fp.write('\n'.join(sorted(glob.glob('/pnfs/iihe/cms/store/user/'+os.getenv('USER')+'/Analyses/VBFTagger/UL1*/PFStudies/workdir_*_UL1*/*/*root'))))

folders = [
    'all',
    'eventCategory_-3',
    'eventCategory_-2',
    'eventCategory_2',
    'eventCategory_-1',
    'eventCategory_1',
    'eventCategory_0',
]

for folder in folders:
    with open(outpath+'ListFilesToCopy_'+folder+'.txt', 'w') as fp:
        fp.write('\n'.join(sorted(glob.glob('/pnfs/iihe/cms/store/user/'+os.getenv('USER')+'/Analyses/VBFTagger/DNNInputs/'+folder+'/*root'))))
