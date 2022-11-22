#! /usr/bin/env python

def FlattenTree(input_name,output_name, tree_name='AnalysisTree', selection = None):
    import ROOT
    from uproot.const import kLZ4
    branches_to_keep = [
        "VBFjet_pt",
        "VBFjet_eta",
        "VBFjet_phi",
        "VBFjet_energy",
        "VBFjet_score_qgl",
        "VBFjet_n_constituents",
        "nonVBFjet_pt",
        "nonVBFjet_eta",
        "nonVBFjet_phi",
        "nonVBFjet_energy",
        "nonVBFjet_score_qgl",
        "nonVBFjet_n_constituents",
        "PF_VBF1_pt",
        "PF_VBF1_eta",
        "PF_VBF1_phi",
        "PF_VBF1_energy",
        "PF_VBF1_pdgid",
        "PF_VBF1_charge",
        "PF_VBF1_puppiweight",
        "PF_VBF2_pt",
        "PF_VBF2_eta",
        "PF_VBF2_phi",
        "PF_VBF2_energy",
        "PF_VBF2_pdgid",
        "PF_VBF2_charge",
        "PF_VBF2_puppiweight",
        "PF_UE_charged_pt",
        "PF_UE_charged_eta",
        "PF_UE_charged_phi",
        "PF_UE_charged_energy",
        "PF_UE_charged_pdgid",
        "PF_UE_charged_charge",
        "PF_UE_charged_puppiweight",
        "PF_UE_neutral_pt",
        "PF_UE_neutral_eta",
        "PF_UE_neutral_phi",
        "PF_UE_neutral_energy",
        "PF_UE_neutral_pdgid",
        "PF_UE_neutral_charge",
        "PF_UE_neutral_puppiweight",
        "PF_UE_pt",
        "PF_UE_eta",
        "PF_UE_phi",
        "PF_UE_energy",
        "PF_UE_pdgid",
        "PF_UE_charge",
        "PF_UE_puppiweight",
        "PF_VBF_pt",
        "PF_VBF_eta",
        "PF_VBF_phi",
        "PF_VBF_energy",
        "PF_VBF_pdgid",
        "PF_VBF_charge",
        "PF_VBF_puppiweight",
        "PF_UE_VBF_pt",
        "PF_UE_VBF_eta",
        "PF_UE_VBF_phi",
        "PF_UE_VBF_energy",
        "PF_UE_VBF_pdgid",
        "PF_UE_VBF_charge",
        "PF_UE_VBF_puppiweight",
        "PF_UE_VBF_sorted_pt",
        "PF_UE_VBF_sorted_eta",
        "PF_UE_VBF_sorted_phi",
        "PF_UE_VBF_sorted_energy",
        "PF_UE_VBF_sorted_pdgid",
        "PF_UE_VBF_sorted_charge",
        "PF_UE_VBF_sorted_puppiweight",
        "m_PF_VBF_size",
        "m_PF_UE_charged_size",
        "m_PF_UE_neutral_size",
        "m_is_VBF",
        "m_eventCategory",
        "m_n_PF_jet1",
        "m_n_PF_jet2",
        "m_n_PF_VBF_charged",
        "m_n_PF_VBF_neutral",
        "m_n_nonVBF_jets",
        "m_HT_nonVBF_jets",
        "m_Zeppenfeld",
        "m_Zeppenfeld_charged",
        "m_Zeppenfeld_neutral",
        "m_energy_density_ratio",
        "m_energy_density_ratio_charged",
        "m_energy_density_ratio_neutral",
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
