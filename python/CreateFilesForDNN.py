#! /usr/bin/env python

import os, glob
from parallelize import timeit
from printing_utils import green, blue

def DoCondor(args_list):
    print(blue('  --> Submitting to htcondor...'))
    from Submitter.CondorBase import CondorBase
    CB = CondorBase(JobName='FlattenTree', Time='00:10:00')
    CB.CreateJobInfo(executable=os.path.abspath('FlattenTree.py'))
    CB.ModifyJobInfo('outdir', os.getcwd()+'/jobout/')
    CB.SubmitManyJobs(job_args=args_list)


@timeit
def Run(arglist, command, ncores, debug):
    # arglist = arglist[0:2]
    print(blue('  --> Running on '+str(len(arglist))+' files ...'))
    if not debug:
        if command=='MultiProcess':
            from parallelize import MultiProcess
            from FlattenTree import FlattenTree
            MultiProcess(FlattenTree, arglist, ncores=ncores)
        else:
            commands = [' '.join(['-'+key[0]+' '+val+'' for key,val in el.items()]) for el in arglist]
            if command=='Condor':
                DoCondor(commands)
            elif command=='parallelize':
                from parallelize import parallelize
                commands = ['./FlattenTree.py '+cmd for cmd in commands]
                parallelize(commands, ncores=ncores)
            else:
                raise ValueError('Not implemented command as '+str(command))
    print(green('  --> Done'))


def Filtering_Original(file_list, outdir, command, ncores, debug):
    arglist = []
    for input_name in file_list:
        arglist.append({'input_name':input_name, 'output_name':outdir+'/'+input_name.split('/')[-1]})
    print(blue('  --> Filtering '+str(len(arglist))+' original files ...'))
    Run(arglist, command, ncores, debug)

def Filtering_Categories(file_list, dirs, outdir, command, ncores, debug):
    arglist = []
    for input_name in file_list:
        for dir,selection in dirs.items():
            arglist.append({'input_name':input_name, 'output_name':outdir+dir+'/'+input_name.split('/')[-1], 'selection': selection})
    print(blue('  --> Filtering '+str(len(arglist))+' files by category ...'))
    Run(arglist, command, ncores, debug)

@timeit
def main(command, ncores=8, debug=False):
    input_dir = '/pnfs/iihe/cms/store/user/'+os.getenv('USER')+'/Analyses/VBFTagger/'
    output_dir = '/pnfs/iihe/cms/store/user/'+os.getenv('USER')+'/Analyses/VBFTagger/DNNInputs/'
    orignal_files_list = sorted(glob.glob(input_dir+'/UL1*/PFStudies/workdir_*_UL1*/*/*root'))

    dirs ={'eventCategory_0':  'm_eventCategory==0',
           'eventCategory_1':  'm_eventCategory==1',
           'eventCategory_2':  'm_eventCategory==2',
           'eventCategory_-1': 'm_eventCategory==-1',
           'eventCategory_-2': 'm_eventCategory==-2',
           'eventCategory_-3': 'm_eventCategory==-3',
           }
    for dir in dirs:
        os.system('mkdir -p '+output_dir+dir)

    orignal_merged_files_list = sorted(glob.glob(input_dir+'/UL1*/PFStudies/*root'))
    # Filtering_Original(file_list=orignal_merged_files_list, outdir=output_dir+'all', command=command, ncores=ncores, debug=debug)

    file_list = sorted(glob.glob(output_dir+'all/*root'))
    # Filtering_Categories(file_list=file_list, dirs=dirs, outdir=output_dir, command=command, ncores=ncores, debug=debug)





if __name__ == '__main__':
    debug=False
    debug=True
    ncores=4
    command='MultiProcess'
    command='parallelize'
    command='Condor'
    main(command=command, ncores=ncores, debug=debug)
