import os, glob, json, itertools
from collections import OrderedDict

def GetDefaultModel():
    params_base = OrderedDict([
        ('modelName',             'train_with_weights_scale_xsec'),
        ('filterInputs',          'PF_UE_charged'),
        ('classes',               {'VBF':1, 'GluGlu':0}),
        ('DenseLayer',            [64, 32, 8]),
        ('batch_size',            1024),
        ('regularization_method', 'dropout'),
        ('regularization_rate',   0.01),
        ('batchnorm',             True),
        ('epochs',                50),
        ('learningrate',          0.0001),
        ('runonfraction',         1.00),
        ('eqweight',              True),
        ('kernel_initializer',    'glorot_normal'),
        ('bias_initializer',      'ones'),
        ('activation_first',      'relu'),
        ('activation_hidden',     'tanh'),
        ('activation_last',       'softmax'),
        ('optimizer',             'adam'), #'adamax'
        ('metrics',               ['accuracy']),
        ('LSTMLayer',             64),
    ])
    return params_base


def main():

    path = 'MyModels'
    a = os.system('mkdir -p '+path)
    files = glob.glob(path+'/'+GetDefaultModel()['modelName']+'*json')
    tag = max([int(x.strip('.json').split('_')[-1]) for x in files]) if len(files) != 0 else 0
    print('Minimum tag: '+ str(tag))
    hyperParameters = OrderedDict([
        ('DenseLayer',             [[64, 32, 8], [50,50,10], [1024,512,128,32,8]]),
        ('batch_size',             [64, 256, 1024, 4096]),
        # ('regularization_rate',    [0.01]),
        ('learningrate',           [0.01, 0.001]),
        # ('runonfraction',          [1.00]),
        # ('kernel_initializer',     ['glorot_normal']),
        # ('bias_initializer',       ['ones']),
        # ('activation_first',       ['relu']),
        # ('activation_hidden',      ['tanh']),
        # ('activation_last',        ['softmax']),
        # ('optimizer',              ['adam']),
        # ('LSTMLayer',              [32, 64, 128, 512, 1024]),
        # ('filterInputs',           ['PF_noHiggs', 'gen_non_higgs_decays', 'VBF_genjets']),
        # ('filterInputs',           ['VBF_jets','PF_VBF','PF_UE_charged','PF_UE_neutrals',['PF_UE_charged','PF_UE_neutrals'], ['VBF_jets','PF_VBF'], ['VBF_jets','PF_VBF','PF_UE_charged','PF_UE_neutrals']]),
        ('filterInputs',           ['VBF_jets','PF_VBF','PF_UE_charged','PF_UE_neutrals',
                                   ['VBF_jets','PF_VBF'],['PF_UE_charged','PF_UE_neutrals'],
                                   ['VBF_jets', 'PF_UE_charged','PF_UE_neutrals'],['PF_VBF', 'PF_UE_charged','PF_UE_neutrals'],
                                   ['VBF_jets','PF_VBF','PF_UE_charged','PF_UE_neutrals']]),        
    ])

    keys, values = zip(*hyperParameters.items())
    permutations_dicts = [dict(zip(keys, v)) for v in itertools.product(*values)]
    print('Creating: '+ str(len(permutations_dicts)))
    for perm in permutations_dicts:
        tag += 1
        new_dict = GetDefaultModel()
        new_dict.update(perm)
        new_dict['modelName'] += '_'+str(tag).zfill(4)
        filterInputs = new_dict['filterInputs']
        if isinstance(filterInputs, list):
            filterInputs = '_'.join(filterInputs)
        with open(path+'/'+filterInputs+'_'+new_dict['modelName']+'.json','w') as f:
            f.write(json.dumps(new_dict, indent=2))

if __name__ == '__main__':
    main()
