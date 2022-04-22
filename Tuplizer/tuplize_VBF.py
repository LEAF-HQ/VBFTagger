#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os

from Tuplizer.TuplizeRunner import *

from Samples.Data_MiniAODv2 import *
from Samples.Backgrounds_MiniAODv2 import *
from Samples.Signals_MiniAODv2 import *
from VBFTagger.Tuplizer.Signals_VBF import *


# make a new workarea for each eventcontent present in the NTuples, for example "Workarea_standard" for "standard" saved in NTuples, another one "Workarea_pfcands" for ntuplizing samples with the content "pfcands" stored. Each sample will have the same name, just a different 'contents' and xml file name
workarea = os.path.join(os.environ['ANALYSISPATHTUPLIZER'], 'Workarea_standard')
username = os.environ['USER']

AllSamples = SampleContainer()
# Add_Data(AllSamples)
# Add_Background(AllSamples)
# Add_Signals_LQ(AllSamples)
Add_Signals_VBFAnalysis(AllSamples)


config_per_year = {
    'UL17': {
        'arch_tag': 'slc7_amd64_gcc700',
        'cmsswtag': 'CMSSW_10_6_28'
    },
    'UL18': {
        'arch_tag': 'slc7_amd64_gcc700',
        'cmsswtag': 'CMSSW_10_6_28'
    }
}




year = 'UL18'
stage = 'mini'
submit = True
# submit = False
nevt_per_job = 100000




def main():
    for samplename, sample in AllSamples.items():
        print(green('--> Working on sample: \'%s\'' % (samplename)))
        Tuplizer = TuplizeRunner(sample=sample, stage=stage, year=year, config=config_per_year[year], workarea=workarea, submit=submit)
        # Tuplizer.CountEvents(check_missing=True)
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00,00), nevt_per_job=nevt_per_job, mode='new')
        # Tuplizer.CleanBrokenFiles(nevt_per_job=nevt_per_job)
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(01,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(02,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(05,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.SubmitTuplize(ncores=1, runtime=(23,00,00), nevt_per_job=nevt_per_job, mode='resubmit')
        # Tuplizer.CreateDatasetXMLFile(force_counting=True, count_weights=True)
        # Tuplizer.PrintDASCrossSection(sample=sample, year=year, recalculate=True)
    # create_default_config(allsamples=AllSamples, year='UL17', configoutname= os.path.join(os.environ['LEAFPATH'], 'LQDM', 'config', 'Default.xml'))



if __name__ == '__main__':
    main()
