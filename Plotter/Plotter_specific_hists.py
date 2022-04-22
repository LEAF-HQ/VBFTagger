from Utils import *

import tdrstyle_all as TDR
TDR.extraText = 'Simulation'
TDR.extraText2 = 'Preliminary'

def ConvertNameForLegend(name):
    legName = ''
    if name == 'VBF_HToZZTo4L_M125':        return 'VBF H'
    if name == 'GluGluHToZZTo4L_M125':      return 'gg->ggH'
    if 'pt1' in name:                       legName += 'p_{T}>1 '
    if 'pt0p2' in name:                     legName += 'p_{T}>0.2 '
    if 'UEin' in name:                      legName += 'UE_{in} '
    if 'UEout' in name:                     legName += 'UE_{out} '
    if 'charged' in name:                   legName += 'charged '
    if 'neutral' in name:                   legName += 'neutral '
    if 'Jets' in name:                      legName += 'inclusive'
    if 'Jets_opp_deta_mjj' in name:         legName += 'selections'
    if name == 'nominal_Jets':              legName += 'inclusive'
    if name == 'nominal_Jets_opp_deta_mjj': legName += 'selections'
    return legName


class Plotter_Specific_Hists(GenericPath):
    def __init__(self, analysis = 'VBFTagger', year = 'UL18', module = 'PFStudies', folder='nominal', pt='1', extraSelection=''):
        GenericPath.__init__(self)
        self.analysis = analysis
        self.year = year
        self.module = module
        self.inputdir  = os.path.join(self.analysis_outpath, self.analysis, self.year, self.module)
        self.outputdir = os.path.join(self.inputdir, 'plots','distributions', 'Plotter_Specific_Hists')
        if not os.path.exists(self.outputdir): os.makedirs(self.outputdir)

        self.histfolder = folder
        self.selection = self.histfolder+'_PFCands_pt'+pt+extraSelection

        self.samples   = ['VBF_HToZZTo4L_M125','GluGluHToZZTo4L_M125']
        self.folders_no = ['', '_UEin', '_UEout', '_charged', '_neutral']
        self.folders_UE = ['in_charged', 'in_neutral', 'out_charged', 'out_neutral']

        self.folders = [self.selection+x for x in (self.folders_UE if 'UE' in extraSelection else self.folders_no)]
        self.histnames = ['n_pfcands', 'n_pfcands_density', 'n_pfcands_density2', 'n_pfcands_density3', 'n_charged_pfcands', 'n_neutral_pfcands', 'UEin_UEout_ratio',
                          'HT_pfcands', 'pf_cand_pt', 'pf_cand_eta', 'pf_cand_puppi_w',
                          'pf_cand_dz', 'pf_cand_dxy', 'pf_cand_dz_err', 'pf_cand_dxy_err',
                          'Zeppenfeld1', 'Zeppenfeld2', 'Zeppenfeld3',
                          ]
        # self.folders   = ['njets_Jets', 'nominal_Jets_opp_deta_mjj']
        # self.histnames = [ 'number_of_jets', 'HT_jets', 'jet_area', 'jet_score_qgl', 'jet_ch_had_efrac', 'jet_ne_em_efrac', 'jet_ne_had_efrac', 'jet_muo_efrac', 'jet_ele_efrac', 'jet_pho_efrac', 'jet_parton_flavor', 'jet_hadron_flavor', 'jet_n_constituents', 'jet1_eta', 'jet2_eta', 'm_jj', 'number_matched_jets',]



        self.style = {'VBF_HToZZTo4L_M125': ROOT.kSolid,
                      'GluGluHToZZTo4L_M125': ROOT.kDashed,
                      'PFCands_pt1': ROOT.kBlack+1,
                      'PFCands_pt1_UEin': ROOT.kRed+1,
                      'PFCands_pt1_UEout': ROOT.kAzure+2,
                      'PFCands_pt1_charged': ROOT.kOrange+1,
                      'PFCands_pt1_neutral': ROOT.kGreen+2,
                      'PFCands_pt1_UEin_charged': ROOT.kGreen+2,
                      'PFCands_pt1_UEin_neutral': ROOT.kRed+1,
                      'PFCands_pt1_UEout_charged': ROOT.kAzure+2,
                      'PFCands_pt1_UEout_neutral': ROOT.kOrange+1,
                      'Jets': ROOT.kGreen+1,
                      'Jets_opp_deta_mjj': ROOT.kRed+1,
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
                    if "n_" in name and "pfcands" in name:
                        self.hists[hname].Rebin(3)
                    if self.hists[hname].Integral()!=0:
                        self.hists[hname].Scale(1./self.hists[hname].Integral())
            f_.Close()

    def Plot(self, doLog=True):
        for name in self.histnames:
            refHist = self.hists[self.samples[0]+self.folders[0]+name]
            # refHist = self.hists[self.hists.keys()[0]]
            PlotXMin = refHist.GetBinLowEdge(1)
            PlotXMax = refHist.GetBinLowEdge(refHist.GetNbinsX()+1)
            if name == 'number_pf_cands' : PlotXMax = 200
            if name == 'HT_pfcands' : PlotXMax = 600
            if name == 'n_pfcands' : PlotXMax = 100
            PlotYMin = 0.0001
            PlotYMax = 1 if doLog else 0.2
            TDR.lumi_13TeV = self.year
            canv = tdrCanvas(name, PlotXMin, PlotXMax, PlotYMin, PlotYMax, refHist.GetXaxis().GetTitle(), refHist.GetYaxis().GetTitle())
            canv.SetLogy(doLog)
            leg = tdrLeg(0.48,0.65,0.89,0.89, textSize = 0.03)
            for sample in self.samples:
                for folder in self.folders:
                    h = self.hists[sample+folder+name]
                    tdrDraw(h, 'hist', lcolor = self.style[folder.replace(self.histfolder+'_','').replace('pt0p2','pt1')]-(int(self.style[sample])-1), lstyle=ROOT.kSolid, fstyle=0, marker = 0)
                    leg.AddEntry(h, ConvertNameForLegend(sample)+': '+ConvertNameForLegend(folder), 'l')

            fname = self.outputdir+'/'+self.selection+'_'+name+'.pdf'
            if doLog: fname = fname.replace('.pdf', '_log.pdf' )
            if os.path.exists(fname):
                os.remove(fname)
            canv.SaveAs(fname)
            canv.Close()







def main():
    for folder in ['nominal', 'low_pt', 'mid_pt']:
        for pt in ['1','0p2']:
            for extraSelection in ['', '_UE']:
                plotter = Plotter_Specific_Hists(folder=folder,pt=pt, extraSelection=extraSelection)
                plotter.LoadHists()
                plotter.Plot(doLog=True)
                plotter.Plot(doLog=False)

if __name__ == '__main__':
    main()
