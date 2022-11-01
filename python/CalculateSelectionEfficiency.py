import ROOT

# samples = ['VBF_HToZZTo4L_M125', 'VBF_HToZZTo4L_M120', 'VBF_HToZZTo4L_M124', 'VBF_HToZZTo4L_M126', 'VBF_HToZZTo4L_M130', 'GluGluHToZZTo4L_M125', 'GluGluHToZZTo4L_M120', 'GluGluHToZZTo4L_M124', 'GluGluHToZZTo4L_M126', 'GluGluHToZZTo4L_M130']
samples = ['VBF_HToZZTo4L_M125', 'GluGluHToZZTo4L_M125']
cuts = ['weights', 'phasespace', 'checkpointgenlevel', 'nogentau', 'notau', 'VBFSelection', 'low_pt', 'nominal']
cuts = ['weights', 'notau_Selection', 'nogentau_Selection','NObject_Selection',
        'phasespace_Selection', 'Higgs4LeptonsReco', 'Higgs4Leptons_Selection',
        'VBF_Selection', 'nominal'
        ]
# cuts = ['weights','nominal']

for sample in samples:
    fname = '/pnfs/iihe/cms/store/user/anmalara/Analyses/VBFTagger/RunII/PFStudies/MC__'+sample+'_standard_RunII.root'
    # fname = '/pnfs/iihe/cms/store/user/anmalara/Analyses/VBFTagger/UL18//PFStudies/workdir_PFStudiesConfig_UL18/'+sample+'_standard_UL18/MC__'+sample+'_standard_UL18_10.root'

    f_ = ROOT.TFile(fname)
    den = -1
    den0 = -1
    for cut in cuts:
        h = f_.Get(cut+'_VBFGenJets/sumweights')
        num = h.GetBinContent(1)
        if den<0: den = num
        if den0<0: den0 = num
        print round(num*1.0/den*100,2),'%', round(num*1.0/den0*100,2),'%', cut, sample
        den = num

    f_.Close()
