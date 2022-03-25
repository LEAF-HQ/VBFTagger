from Utils import *

def ConvertNameForLegend(name):
    if name == 'VBF_HToZZTo4L_M125':    return 'VBF H'
    if name == 'GluGluHToZZTo4L_M125':  return 'gg->ggH'
    if name == 'nominal_PFCands_pt':    return 'p_{T}>1'
    if name == 'nominal_PFCands_UEin':  return 'UE_{in}'
    if name == 'nominal_PFCands_UEout': return 'UE_{out}'
    if name == 'nominal_PFCands_UEin_charged':  return 'UE_{in} & charged'
    if name == 'nominal_PFCands_UEin_neutral':  return 'UE_{out} & neutral'
    if name == 'nominal_PFCands_UEout_charged': return 'UE_{in} & charged'
    if name == 'nominal_PFCands_UEout_neutral': return 'UE_{out} & neutral'
    if name == 'njets_Jets':            return 'inclusive'
    if name == 'njets_Jets_opp_deta_mjj': return 'selections'
    if name == 'nominal_Jets':          return 'inclusive'
    if name == 'nominal_Jets_opp_deta_mjj': return 'selections'


class Plotter_Specific_Hists(GenericPath):
    def __init__(self, analysis = 'VBFTagger', year = 'UL18', module = 'PFStudies'):
        GenericPath.__init__(self)
        self.analysis = analysis
        self.year = year
        self.module = module
        self.inputdir  = os.path.join(self.analysis_outpath, self.analysis, self.year, self.module)
        self.outputdir = os.path.join(self.inputdir, 'plots','distributions', 'Plotter_Specific_Hists')
        ensureDirectory(self.outputdir)

        self.samples   = ['VBF_HToZZTo4L_M125','GluGluHToZZTo4L_M125']
        self.folders   = ['nominal_PFCands_pt', 'nominal_PFCands_UEin','nominal_PFCands_UEout']
        self.folders   = ['nominal_PFCands_UEin_charged', 'nominal_PFCands_UEin_neutral', 'nominal_PFCands_UEout_charged', 'nominal_PFCands_UEout_neutral']
        self.histnames = ['n_pfcands', 'n_charged_pfcands', 'n_neutral_pfcands', 'charged_neutral_ratio',
                          'HT_pfcands', 'pf_cand_pt', 'pf_cand_eta', 'pf_cand_type',
                          'pf_cand_puppi_w', 'pf_cand_calo_frac', 'pf_cand_hcal_frac',
                          'pf_cand_dz', 'pf_cand_dxy', 'pf_cand_dz_err', 'pf_cand_dxy_err',
                          'pf_cand_DR_from_jet'
                          ]
        # self.folders   = ['njets_Jets', 'nominal_Jets_opp_deta_mjj']
        # self.histnames = [ 'number_of_jets', 'HT_jets', 'jet_area', 'jet_score_qgl', 'jet_ch_had_efrac', 'jet_ne_em_efrac', 'jet_ne_had_efrac', 'jet_muo_efrac', 'jet_ele_efrac', 'jet_pho_efrac', 'jet_parton_flavor', 'jet_hadron_flavor', 'jet_n_constituents', 'jet1_eta', 'jet2_eta', 'm_jj', 'number_matched_jets',]

        self.style = {'VBF_HToZZTo4L_M125': ROOT.kSolid,
                      'GluGluHToZZTo4L_M125': ROOT.kDashed,
                      'nominal_PFCands_pt': ROOT.kGreen+1,
                      'nominal_PFCands_UEin': ROOT.kRed+1,
                      'nominal_PFCands_UEout': ROOT.kAzure+2,
                      'nominal_PFCands_UEin_charged': ROOT.kGreen+1,
                      'nominal_PFCands_UEin_neutral': ROOT.kRed+1,
                      'nominal_PFCands_UEout_charged': ROOT.kAzure+2,
                      'nominal_PFCands_UEout_neutral': ROOT.kOrange+1,
                      'nominal_Jets': ROOT.kGreen+1,
                      'nominal_Jets_opp_deta_mjj': ROOT.kRed+1,
                      'njets_Jets': ROOT.kAzure+2,
                      'njets_Jets_opp_deta_mjj': ROOT.kOrange+1,
                      }


    def LoadHists(self):
        self.hists = {}
        for sample in self.samples:
            f_ = ROOT.TFile.Open(self.inputdir+'/MC__'+sample+'.root')
            for folder in self.folders:
                for name in self.histnames:
                    hname = sample+folder+name
                    self.hists[hname] = f_.Get(folder+'/'+name)
                    self.hists[hname].SetDirectory(0)
                    if self.hists[hname].Integral()!=0:
                        self.hists[hname].Scale(1./self.hists[hname].Integral())
            f_.Close()

    def Plot(self):
        for name in self.histnames:
            refHist = self.hists[self.samples[0]+self.folders[0]+name]
            PlotXMin = refHist.GetBinLowEdge(1)
            PlotXMax = refHist.GetBinLowEdge(refHist.GetNbinsX()+1)
            if name == 'number_pf_cands' : PlotXMax = 200
            PlotYMin = 0.0001
            PlotYMax = 1
            canv = tdrCanvas(name, PlotXMin, PlotXMax, PlotYMin, PlotYMax, refHist.GetXaxis().GetTitle(), refHist.GetYaxis().GetTitle())
            canv.SetLogy(True)
            leg = tdrLeg(0.48,0.69,0.89,0.89, textSize = 0.03)
            for sample in self.samples:
                for folder in self.folders:
                    h = self.hists[sample+folder+name]
                    tdrDraw(h, 'h', lcolor = self.style[folder], lstyle=self.style[sample], fstyle=0, marker = 0)
                    leg.AddEntry(h, ConvertNameForLegend(sample)+': '+ConvertNameForLegend(folder), 'l')

            fname = self.outputdir+'/'+name+'.pdf'
            if os.path.exists(fname):
                os.remove(fname)
            canv.SaveAs(fname)







def main():
    plotter = Plotter_Specific_Hists()
    plotter.LoadHists()
    plotter.Plot()

if __name__ == '__main__':
    main()
