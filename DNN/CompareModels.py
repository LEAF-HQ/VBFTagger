import os, glob, yaml, itertools
from collections import OrderedDict
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


def main():
    print 'start main'
    modelName = 'train_with_weights_scale_xsec*'
    filterInputs = 'VBF_jets'
    filterInputs = 'PF_VBF'
    filterInputs = 'PF_UE_charged'
    filterInputs = 'PF_UE_neutrals'
    filterInputs = 'VBF_jets_PF_VBF'
    filterInputs = 'PF_UE_charged_PF_UE_neutrals'
    filterInputs = 'VBF_jets_PF_UE_charged_PF_UE_neutrals'
    filterInputs = 'PF_VBF_PF_UE_charged_PF_UE_neutrals'
    filterInputs = 'VBF_jets_PF_VBF_PF_UE_charged_PF_UE_neutrals'

    plotDir = '/user/'+os.environ['USER']+'/WorkingArea/DNNOutputs/PFStudies/plots/Predictions/'
    hyperParameters = OrderedDict([
        ('DenseLayer',             [[64, 32, 8], [50,50,10], [1024,512,128,32,8]]),
        ('batch_size',             [64, 256, 1024, 4096]),
        ('learningrate',           [0.01, 0.001]),
    ])
    Ref_parameters =  OrderedDict([
    ])
    models = {}
    max_auc = ('',-1)
    for fname in glob.glob(os.path.join(plotDir,filterInputs,modelName)):
        roc_json = os.path.join(fname,'ROC_summary.json')
        if not os.path.exists(roc_json): continue
        with open(roc_json, 'r') as f:
            rocs = yaml.safe_load(f)
        filterInputs_, modelName_ = fname.replace(plotDir, '').split('/')
        jsonName = 'MyModels/'+filterInputs_+'_'+modelName_+'.json'
        if not os.path.exists(jsonName): continue
        with open(jsonName, 'r') as f:
            dnnparameters = yaml.safe_load(f)
            for parName, value in Ref_parameters.items():
                if dnnparameters[parName] != value: continue
            for parName, values in hyperParameters.items():
                for val in values:
                    name = parName+str(val)
                    if dnnparameters[parName] == val:
                        if not name in models: models[name] = []
                        auc = np.array(rocs.values()).mean()
                        models[name].append(auc)
                        if auc > max_auc[1]:
                            max_auc = (fname,auc)
    print max_auc
    plt.clf()
    fig = plt.figure()
    for parName in models:
        # plt.hist(models[parName], label=parName, bins=50, histtype='step')
        plt.hist(models[parName], label=parName, bins=50, alpha=0.5)
    plt.legend(loc='upper left')
    plt.xlabel('AUC')
    plt.ylabel('A.U.')
    fig.savefig('aucs_'+filterInputs+'.pdf')
plt.close()

if __name__ == '__main__':
    main()
