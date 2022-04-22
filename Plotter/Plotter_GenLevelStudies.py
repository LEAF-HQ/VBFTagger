from Utils import *
extraText  = ""
lumi_13TeV = ""

SFlist = ["isDecayedLeptonHadron", "isDirectHadronDecayProduct", "fromHardProcessFinalState", "fromHardProcessDecayed"
"isPrompt", "isPromptFinalState", "isPromptDecayed", "isHardProcess", "fromHardProcess", "fromHardProcessBeforeFSR"]

pdgidlist = ["unknown", "e", "#mu", "#nu_{e}", "#nu_{#mu}", "#nu_{#tau}",
             "#gamma", "Z", "W", "H", "#pi^{0}", "#pi^{+}", "K^{0}_{L}",
             "K^{0}_{S}", "K^{+}", "#Lambda", "p"]

def ConvertNameForLegend(name):
    if name == 'VBF_HToZZTo4L_M125':    return 'VBF H'
    if name == 'GluGluHToZZTo4L_M125':  return 'gg->ggH'
    # if name == 'nominal_PFCands_pt':    return 'p_{T}>1'
    if name == 'nominal_GenLevel_Mjj>200__':  return ''
    if name == 'nominal_GenLevel_Mjj>200_Inside_':  return 'UE_{in}'
    if name == 'nominal_GenLevel_Mjj>200_Outside_': return 'UE_{out}'
    if name == 'nominal_GenLevel_Mjj>200_Inside_charged':  return 'UE_{in} & charged'
    if name == 'nominal_GenLevel_Mjj>200_Inside_neutral':  return 'UE_{in} & neutral'
    if name == 'nominal_GenLevel_Mjj>200_Outside_charged': return 'UE_{out} & charged'
    if name == 'nominal_GenLevel_Mjj>200_Outside_neutral': return 'UE_{out} & neutral'
    # if name == 'njets_Jets':            return 'inclusive'
    # if name == 'njets_Jets_opp_deta_mjj': return 'selections'
    # if name == 'nominal_Jets':          return 'inclusive'
    # if name == 'nominal_Jets_opp_deta_mjj': return 'selections'


class Plotter_Specific_Hists(GenericPath):
    def __init__(self, analysis = 'VBFTagger', year = 'UL18', module = 'GenLevelStudies'):
        GenericPath.__init__(self)
        self.analysis = analysis
        self.year = year
        self.module = module
        self.inputdir  = os.path.join(os.path.expanduser('~'), "WorkingArea", self.analysis, self.year, self.module) #os.path.join(self.analysis_outpath, self.analysis, self.year, self.module)
        self.outputdir = os.path.join(self.inputdir, 'plots','distributions', 'Plotter_Specific_Hists')
        ensureDirectory(self.outputdir)

        self.samples   = ['VBF_HToZZTo4L_M125','GluGluHToZZTo4L_M125']
        # self.folders   = ['nominal_GenLevel_Mjj>200__']
        # self.histnames = ['gen_jet_number', 'gen_jet_Pt', 'gen_jet_Eta', 'gen_jet_Ht', 'gen_LJ_dEta', 'gen_LJ_dR', 'gen_LJ_Mass']

        # self.folders = ['nominal_GenLevel_Mjj>200__', 'nominal_GenLevel_Mjj>200_Inside_','nominal_GenLevel_Mjj>200_Outside_']
        # self.histnames = ['gen_part_charged_neutral_ratio']

        self.folders   = ['nominal_GenLevel_Mjj>200_Inside_charged', 'nominal_GenLevel_Mjj>200_Inside_neutral', 'nominal_GenLevel_Mjj>200_Outside_charged', 'nominal_GenLevel_Mjj>200_Outside_neutral']
        self.histnames = ['gen_part_number', 'gen_part_pdgid', 'gen_part_statusFlag',
                          'gen_part_pt', 'gen_part_eta', 'gen_part_charge', 'gen_part_Ht',
                          'gen_part_MET'
                          ]


        # self.folders   = ['njets_Jets', 'nominal_Jets_opp_deta_mjj']
        # self.histnames = [ 'number_of_jets', 'HT_jets', 'jet_area', 'jet_score_qgl', 'jet_ch_had_efrac', 'jet_ne_em_efrac', 'jet_ne_had_efrac', 'jet_muo_efrac', 'jet_ele_efrac', 'jet_pho_efrac', 'jet_parton_flavor', 'jet_hadron_flavor', 'jet_n_constituents', 'jet1_eta', 'jet2_eta', 'm_jj', 'number_matched_jets',]

        self.style = {'VBF_HToZZTo4L_M125': ROOT.kSolid,
                      'GluGluHToZZTo4L_M125': ROOT.kDashed,
                      'nominal_GenLevel_Mjj>200__': ROOT.kGreen+1,
                      'nominal_GenLevel_Mjj>200_Inside_': ROOT.kRed+1,
                      'nominal_GenLevel_Mjj>200_Outside_': ROOT.kAzure+2,
                      'nominal_GenLevel_Mjj>200_Inside_charged': ROOT.kGreen+1,
                      'nominal_GenLevel_Mjj>200_Inside_neutral': ROOT.kRed+1,
                      'nominal_GenLevel_Mjj>200_Outside_charged': ROOT.kAzure+2,
                      'nominal_GenLevel_Mjj>200_Outside_neutral': ROOT.kOrange+1,
                      # 'nominal_Jets': ROOT.kGreen+1,
                      # 'nominal_Jets_opp_deta_mjj': ROOT.kRed+1,
                      # 'njets_Jets': ROOT.kAzure+2,
                      # 'njets_Jets_opp_deta_mjj': ROOT.kOrange+1,
                      }


    def LoadHists(self):
        self.hists = {}
        for sample in self.samples:
            f_ = ROOT.TFile.Open(self.inputdir+'/MC__'+sample+'_standard_UL18.root')
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
            if name == 'gen_part_number' : PlotXMax = 350
            PlotYMin = 0.0001
            PlotYMax = 1
            canv = tdrCanvas(name, PlotXMin, PlotXMax, PlotYMin, PlotYMax, refHist.GetXaxis().GetTitle(), refHist.GetYaxis().GetTitle())
            if name == 'gen_part_pdgid':
                #print(list(canv.GetListOfPrimitives()))
                testhist = canv.GetPrimitive("hframe")
                testhist.SetBins(refHist.GetNbinsX(), 0, refHist.GetNbinsX())
                #print("nBins: ", testhist.GetNbinsX())
                for i in range(1, testhist.GetNbinsX()+1):
                    testhist.GetXaxis().SetBinLabel(i,str(pdgidlist[i-1]))
            if name == 'gen_part_statusFlag':
                testhist = canv.GetPrimitive("hframe")
                testhist.SetBins(refHist.GetNbinsX(), 0, refHist.GetNbinsX())
                for i in range(1, testhist.GetNbinsX()+1):
                    testhist.GetXaxis().SetBinLabel(i,str(SFlist[i-1]))
            canv.SetLogy(True)
            leg = tdrLeg(0.48,0.69,0.89,0.89, textSize = 0.03)
            for sample in self.samples:
                for folder in self.folders:
                    h = self.hists[sample+folder+name]
                    tdrDraw(h, 'h', lcolor = self.style[folder], lstyle=self.style[sample], fstyle=0, marker = 0)
                    leg.AddEntry(h, ConvertNameForLegend(sample)+'  '+ConvertNameForLegend(folder), 'l')



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
