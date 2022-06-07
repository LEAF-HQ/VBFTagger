from Utils import *
extraText  = ""
lumi_13TeV = ""

SFlist = ["isDecayedLeptonHadron", "isDirectHadronDecayProduct", "fromHardProcessFinalState", "fromHardProcessDecayed"
"isPrompt", "isPromptFinalState", "isPromptDecayed", "isHardProcess", "fromHardProcess", "fromHardProcessBeforeFSR"]

pdgidlist = ["other", "e", "#mu", "#tau", "#nu_{e}", "#nu_{#mu}", "#nu_{#tau}",
             "#gamma",
             # "Z", "W", "H", "#pi^{0}",
             "#pi^{+}", "K^{0}_{L}",
             "K^{0}_{S}", "K^{+}", "#Lambda", "p", "n"]

def ConvertNameForLegend(name):
    if name == 'VBF_HToZZTo4L_M125':    return 'VBF H'
    if name == 'GluGluHToZZTo4L_M125':  return 'gg->ggH'
    # if name == 'nominal_PFCands_pt':    return 'p_{T}>1'
    if name == 'nominal_GenLevel':  return ''
    if name == 'nominal_GenLevel_Inside':  return 'UE_{in}'
    if name == 'nominal_GenLevel_Outside': return 'UE_{out}'
    if name == 'nominal_GenLevel_neutral': return 'neutral'
    if name == 'nominal_GenLevel_charged': return 'charged'
    if name == 'nominal_GenLevel_Inside_charged':  return 'UE_{in} & charged'
    if name == 'nominal_GenLevel_Inside_neutral':  return 'UE_{in} & neutral'
    if name == 'nominal_GenLevel_Outside_charged': return 'UE_{out} & charged'
    if name == 'nominal_GenLevel_Outside_neutral': return 'UE_{out} & neutral'
    if name == 'cleaner_GenLevel_Inside_charged':  return 'UE_{in} & charged'
    if name == 'cleaner_GenLevel_Inside_neutral':  return 'UE_{in} & neutral'
    if name == 'cleaner_GenLevel_Outside_charged': return 'UE_{out} & charged'
    if name == 'cleaner_GenLevel_Outside_neutral': return 'UE_{out} & neutral'
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
        self.outputdir = os.path.join(self.inputdir, 'plots', 'Plotter_Specific_Hists')
        ensureDirectory(self.outputdir)

        self.samples   = ['VBF_HToZZTo4L_M125','GluGluHToZZTo4L_M125']
        self.folders1   = ['nominal_GenLevel']
        self.histnames1 = ['gen_jet_number', 'gen_jet_Pt', 'gen_jet_Eta', 'gen_jet_Ht', 'gen_LJ_dEta', 'gen_LJ_dR', 'gen_LJ_Mass', 'gen_LJ_Pt', 'gen_SLJ_Pt', 'gen_LJ_Eta', 'gen_!LJ_Eta']

        self.folders2 = ['nominal_GenLevel', 'nominal_GenLevel_Inside','nominal_GenLevel_Outside']
        self.histnames2 = ['gen_part_charged_neutral_ratio']

        self.folders3 = ['nominal_GenLevel_neutral','nominal_GenLevel_charged']
        self.histnames3 = ['gen_part_ratio_InOut', 'gen_part_density_ratio_InOut', 'gen_part_pt', 'gen_part_Ht', 'gen_part_number']

        self.folders4   = ['nominal_GenLevel_Inside_charged', 'nominal_GenLevel_Inside_neutral', 'nominal_GenLevel_Outside_charged', 'nominal_GenLevel_Outside_neutral']
        self.histnames4 = ['gen_part_pdgid', 'gen_part_statusFlag',
                          # 'gen_part_pt',
                           'gen_part_pdgid2', 'gen_part_eta', 'gen_part_charge',
                          'gen_part_MET', 'gen_jet_VS_gen_part_dR', 'gen_part_ndensity',
                          'gen_part_z1', 'gen_part_z2', 'gen_part_etaXpt', 'gen_part_etaXptsq', 'gen_part_avg_etaXpt', 'gen_part_avg_etaXptsq'
                          ]

        # self.folders   = ['cleaner_GenLevel_Inside_charged', 'cleaner_GenLevel_Inside_neutral', 'cleaner_GenLevel_Outside_charged', 'cleaner_GenLevel_Outside_neutral']
        # self.histnames = ['gen_part_number', 'gen_part_pdgid', 'gen_part_statusFlag',
        #                   'gen_part_pt', 'gen_part_eta', 'gen_part_charge', 'gen_part_Ht',
        #                   'gen_part_MET', 'gen_jet_VS_gen_part_dR', 'gen_part_ndensity',
        #                   'gen_part_z1', 'gen_part_z2'
        #                   ]


        # self.folders   = ['njets_Jets', 'nominal_Jets_opp_deta_mjj']
        # self.histnames = [ 'number_of_jets', 'HT_jets', 'jet_area', 'jet_score_qgl', 'jet_ch_had_efrac', 'jet_ne_em_efrac', 'jet_ne_had_efrac', 'jet_muo_efrac', 'jet_ele_efrac', 'jet_pho_efrac', 'jet_parton_flavor', 'jet_hadron_flavor', 'jet_n_constituents', 'jet1_eta', 'jet2_eta', 'm_jj', 'number_matched_jets',]

        self.style = {'VBF_HToZZTo4L_M125': ROOT.kSolid,
                      'GluGluHToZZTo4L_M125': ROOT.kDashed,
                      'nominal_GenLevel': ROOT.kAzure+2,
                      'nominal_GenLevel_Inside': ROOT.kRed+1,
                      'nominal_GenLevel_Outside': ROOT.kGreen+1,
                      'nominal_GenLevel_neutral': ROOT.kGreen+1,
                      'nominal_GenLevel_charged': ROOT.kRed+1,
                      'nominal_GenLevel_Inside_charged': ROOT.kGreen+1,
                      'nominal_GenLevel_Inside_neutral': ROOT.kRed+1,
                      'nominal_GenLevel_Outside_charged': ROOT.kAzure+2,
                      'nominal_GenLevel_Outside_neutral': ROOT.kOrange+1,
                      'cleaner_GenLevel_Inside_charged': ROOT.kGreen+1,
                      'cleaner_GenLevel_Inside_neutral': ROOT.kRed+1,
                      'cleaner_GenLevel_Outside_charged': ROOT.kAzure+2,
                      'cleaner_GenLevel_Outside_neutral': ROOT.kOrange+1,
                      # 'nominal_Jets': ROOT.kGreen+1,
                      # 'nominal_Jets_opp_deta_mjj': ROOT.kRed+1,
                      # 'njets_Jets': ROOT.kAzure+2,
                      # 'njets_Jets_opp_deta_mjj': ROOT.kOrange+1,
                      }


    def LoadHists(self):
        self.hists1 = {}
        self.hists2 = {}
        self.hists3 = {}
        self.hists4 = {}
        for sample in self.samples:
            f_ = ROOT.TFile.Open(self.inputdir+'/MC__'+sample+'_standard_UL18.root')
            for folder in self.folders1:
                for name in self.histnames1:
                    hname = sample+folder+name
                    self.hists1[hname] = f_.Get(folder+'/'+name)
                    self.hists1[hname].SetDirectory(0)
                    if self.hists1[hname].Integral()!=0:
                        self.hists1[hname].Scale(1./self.hists1[hname].Integral())
            for folder in self.folders2:
                for name in self.histnames2:
                    hname = sample+folder+name
                    self.hists2[hname] = f_.Get(folder+'/'+name)
                    self.hists2[hname].SetDirectory(0)
                    if self.hists2[hname].Integral()!=0:
                        self.hists2[hname].Scale(1./self.hists2[hname].Integral())
            for folder in self.folders3:
                for name in self.histnames3:
                    hname = sample+folder+name
                    self.hists3[hname] = f_.Get(folder+'/'+name)
                    self.hists3[hname].SetDirectory(0)
                    if self.hists3[hname].Integral()!=0:
                        self.hists3[hname].Scale(1./self.hists3[hname].Integral())
            for folder in self.folders4:
                for name in self.histnames4:
                    hname = sample+folder+name
                    self.hists4[hname] = f_.Get(folder+'/'+name)
                    self.hists4[hname].SetDirectory(0)
                    if self.hists4[hname].Integral()!=0:
                        self.hists4[hname].Scale(1./self.hists4[hname].Integral())

            f_.Close()

    def Plot(self):
        for name in self.histnames1:
            refHist = self.hists1[self.samples[0]+self.folders1[0]+name]
            PlotXMin = refHist.GetBinLowEdge(1)
            PlotXMax = refHist.GetBinLowEdge(refHist.GetNbinsX()+1)
            if name == 'gen_part_number' : PlotXMax = 300
            if name == 'gen_part_Ht': PlotXMax = 650
            if name == 'gen_part_ndensity': PlotXMax = 60
            # if name == 'gen_part_z2': PlotXMax = 15
            PlotYMin = 0.0001
            PlotYMax = 1
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt': PlotYMax = 0.1
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
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt': canv.SetLogy(False)
            leg = tdrLeg(0.48,0.69,0.89,0.89, textSize = 0.03)
            for sample in self.samples:
                for folder in self.folders1:
                    h = self.hists1[sample+folder+name]
                    if (name=='gen_part_Ht'): h.Rebin(3)
                    if name=='gen_part_number': h.Rebin(4)
                    tdrDraw(h, 'h', lcolor = self.style[folder], lstyle=self.style[sample], fstyle=0, marker = 0)
                    leg.AddEntry(h, ConvertNameForLegend(sample)+'  '+ConvertNameForLegend(folder), 'l')

            fname = self.outputdir+'/'+name+'.pdf'
            if os.path.exists(fname):
                os.remove(fname)
            canv.SaveAs(fname)


        for name in self.histnames2:
            refHist = self.hists2[self.samples[0]+self.folders2[0]+name]
            PlotXMin = refHist.GetBinLowEdge(1)
            PlotXMax = refHist.GetBinLowEdge(refHist.GetNbinsX()+1)
            if name == 'gen_part_number' : PlotXMax = 300
            if name == 'gen_part_Ht': PlotXMax = 650
            if name == 'gen_part_ndensity': PlotXMax = 60
            # if name == 'gen_part_z2': PlotXMax = 15
            PlotYMin = 0.0001
            PlotYMax = 1
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt': PlotYMax = 0.1
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
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt': canv.SetLogy(False)
            leg = tdrLeg(0.48,0.69,0.89,0.89, textSize = 0.03)
            for sample in self.samples:
                for folder in self.folders2:
                    h = self.hists2[sample+folder+name]
                    if (name=='gen_part_Ht'): h.Rebin(3)
                    if name=='gen_part_number': h.Rebin(4)
                    tdrDraw(h, 'h', lcolor = self.style[folder], lstyle=self.style[sample], fstyle=0, marker = 0)
                    leg.AddEntry(h, ConvertNameForLegend(sample)+'  '+ConvertNameForLegend(folder), 'l')

            fname = self.outputdir+'/'+name+'.pdf'
            if os.path.exists(fname):
                os.remove(fname)
            canv.SaveAs(fname)


        for name in self.histnames3:
            refHist = self.hists3[self.samples[0]+self.folders3[0]+name]
            PlotXMin = refHist.GetBinLowEdge(1)
            PlotXMax = refHist.GetBinLowEdge(refHist.GetNbinsX()+1)
            if name == 'gen_part_number' : PlotXMax = 400
            if name == 'gen_part_Ht': PlotXMax = 650
            if name == 'gen_part_ndensity': PlotXMax = 60
            if name == 'gen_part_z2': PlotXMax = 1
            if name == 'gen_part_pt': PlotXMax = 30
            PlotYMin = 0.0001
            PlotYMax = 1
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt': PlotYMax = 0.1
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
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt' or name == 'gen_part_z2': canv.SetLogy(False)
            leg = tdrLeg(0.48,0.69,0.89,0.89, textSize = 0.03)
            for sample in self.samples:
                for folder in self.folders3:
                    h = self.hists3[sample+folder+name]
                    if (name=='gen_part_Ht'): h.Rebin(3)
                    if name=='gen_part_number': h.Rebin(4)
                    tdrDraw(h, 'h', lcolor = self.style[folder], lstyle=self.style[sample], fstyle=0, marker = 0)
                    leg.AddEntry(h, ConvertNameForLegend(sample)+'  '+ConvertNameForLegend(folder), 'l')

            fname = self.outputdir+'/'+name+'.pdf'
            if os.path.exists(fname):
                os.remove(fname)
            canv.SaveAs(fname)



        for name in self.histnames4:
            refHist = self.hists4[self.samples[0]+self.folders4[0]+name]
            PlotXMin = refHist.GetBinLowEdge(1)
            PlotXMax = refHist.GetBinLowEdge(refHist.GetNbinsX()+1)
            if name == 'gen_part_number' : PlotXMax = 300
            if name == 'gen_part_Ht': PlotXMax = 650
            if name == 'gen_part_ndensity': PlotXMax = 60
            if name == 'gen_part_z2': PlotXMax = 1
            if name == 'gen_part_pt': PlotXMax = 30
            PlotYMin = 0.0001
            PlotYMax = 1
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt': PlotYMax = 0.1
            if name == 'gen_part_z2': PlotYMax = 0.26
            canv = tdrCanvas(name, PlotXMin, PlotXMax, PlotYMin, PlotYMax, refHist.GetXaxis().GetTitle(), refHist.GetYaxis().GetTitle())
            if name == 'gen_part_pdgid':
                #print(list(canv.GetListOfPrimitives()))
                testhist = canv.GetPrimitive("hframe")
                testhist.SetBins(refHist.GetNbinsX(), 0, refHist.GetNbinsX())
                #print("nBins: ", testhist.GetNbinsX())
                for i in range(1, testhist.GetNbinsX()+1):
                    testhist.GetXaxis().SetBinLabel(i,str(pdgidlist[i-1]))
            if name == 'gen_part_pdgid2':
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
            if name == 'gen_LJ_Pt' or name == 'gen_SLJ_Pt' or name == 'gen_part_z2': canv.SetLogy(False)
            leg = tdrLeg(0.48,0.69,0.89,0.89, textSize = 0.03)
            for sample in self.samples:
                for folder in self.folders4:
                    h = self.hists4[sample+folder+name]
                    if (name=='gen_part_Ht'): h.Rebin(3)
                    if name=='gen_part_number': h.Rebin(4)
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
