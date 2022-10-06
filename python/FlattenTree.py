#! /usr/bin/env python

def FlattenTree(input_name,output_name, tree_name='AnalysisTree', selection = None):
    import ROOT
    from uproot.const import kLZ4
    branches_to_keep = [
        'PF_pt',
        'PF_eta',
        'PF_phi',
        'PF_energy',
        'PF_pdgid',
        'PF_charge',
        'PF_puppiweight',
        'VBFjet_pt',
        'VBFjet_eta',
        'VBFjet_phi',
        'VBFjet_energy',
        'VBFjet_score_qgl',
        'VBFjet_n_constituents',
        'nonVBFjet_pt',
        'nonVBFjet_eta',
        'nonVBFjet_phi',
        'nonVBFjet_energy',
        'nonVBFjet_score_qgl',
        'nonVBFjet_n_constituents',
        'm_eventCategory',
        'm_Zeppenfeld',
        'm_Zeppenfeld_charged',
        'm_Zeppenfeld_neutral',
        'm_energy_density_ratio',
        'm_energy_density_ratio_charged',
        'm_energy_density_ratio_neutral',
        'm_n_nonVBF_jets',
        'm_HT_nonVBF_jets',
        'm_n_PF_jet1',
        'm_n_PF_jet2',
        'm_is_VBF',
    ]
    input_file = ROOT.TFile(input_name)
    output_file = ROOT.TFile(output_name,'recreate')
    output_file.SetCompressionAlgorithm(kLZ4)
    output_file.SetCompressionLevel(4)
    input_tree = input_file.Get(tree_name)
    input_tree.SetBranchStatus('*',0)
    for branch in branches_to_keep:
        input_tree.SetBranchStatus(branch,1)
    if selection:
        output_tree = input_tree.CopyTree(selection)
    else:
        output_tree = input_tree.CloneTree()
    output_file.cd()
    output_tree.Write()
    input_file.Close()
    output_file.Close()
    return " input_name:"+str(input_name)+" output_name:"+str(output_name)+" tree_name:"+str(tree_name)+" selection:"+str(selection)


if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input',     type=str)
    parser.add_argument('-o', '--output',    type=str)
    parser.add_argument('-t', '--tree',      type=str, default='AnalysisTree')
    parser.add_argument('-s', '--selection', type=str, default=None)
    args = parser.parse_args()
    result = FlattenTree(input_name=args.input,output_name=args.output, tree_name=args.tree, selection=args.selection)
    print("Done with:"+result)
