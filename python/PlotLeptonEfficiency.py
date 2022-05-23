from Utils import *

import tdrstyle_all as TDR
TDR.writeExtraText = True
TDR.extraText  = 'Simulation'
TDR.extraText2 = 'Work in progress'

'''
Module to plot LeptonID Efficiency
'''

# map ID name to line color and marker style
colors = {'eclean_1':   (ROOT.kBlack,    ROOT.kFullCircle,       'nominal (p_{T}>5 GeV, |#eta|<2.5)'),
          'eclean_2':   (ROOT.kRed+1,    ROOT.kFullTriangleDown, 'ID (wp loose)'),
          'eclean_3':   (ROOT.kGray,     ROOT.kFullSquare,       'ID (wp tight)'),
          'eclean_4':   (ROOT.kAzure+10, ROOT.kFullCross,        'ID (MVAIsoLoose)'),
          'eclean_5':   (ROOT.kGreen+2,  ROOT.kFullTriangleUp,   'ID (MVAIsoEff90)'),
          'eclean_6':   (ROOT.kOrange+1, ROOT.kFullDiamond,      'ID (MVANonIsoLoose)'),
          '#muclean_1': (ROOT.kBlack,    ROOT.kFullCircle,       'nominal (p_{T}>3 GeV, |#eta|<2.5)'),
          '#muclean_2': (ROOT.kRed+1,    ROOT.kFullTriangleDown, 'ID (wp loose)'),
          '#muclean_3': (ROOT.kGray,     ROOT.kFullSquare,       'ID (wp tight)'),
          '#muclean_4': (ROOT.kAzure+10, ROOT.kFullCross,        'ID (wp loose) + iso (wp loose)'),
          '#muclean_5': (ROOT.kGreen+2,  ROOT.kFullTriangleUp,   'ID (wp tight) + iso (wp loose)'),
          '#muclean_6': (ROOT.kOrange+1, ROOT.kFullDiamond,      'ID (wp tight) + iso (wp tight)'),
}

class PlotLeptonEfficiency(GenericPath):
    def __init__(self, year='UL16', analysis = 'VBFTagger', module='PFStudies'):
        GenericPath.__init__(self)
        self.year      = year
        self.analysis  = analysis
        self.module    = module
        TDR.lumi_13TeV = str(round(float(self.lumi_map[year]['lumi_fb']),1))+' fb^{-1}' if TDR.extraText!='Simulation' else 'MC '+year
        self.inputdir  = os.path.join(self.analysis_outpath, self.analysis, self.year, self.module)
        self.outputdir = os.path.join(self.inputdir, 'plots','efficiency')
        self.objects   = ['e','#mu']
        self.Samples   = ['VBF_HToZZTo4L_M125']
        self.Samples   = ['VBF_HToZZTo4L_M125', 'GluGluHToZZTo4L_M125']
        os.system('mkdir -p '+self.outputdir)

    def LoadHistos(self):
        self.histos = {}
        for sample in self.Samples:
            file_ = ROOT.TFile(os.path.join(self.inputdir,'MC__'+sample+'.root'))
            for obj in self.objects:
                folders = ['clean_1','clean_2','clean_3','clean_4','clean_5','clean_6']
                for folder in folders:
                    hname = sample+obj+folder
                    den = file_.Get(folder+'_LeptonEfficiency/gen_'+obj+'_pt').Clone(hname+'den')
                    num = file_.Get(folder+'_LeptonEfficiency/match_'+obj+'_pt').Clone(hname+'num')
                    self.histos[hname] = CreateEfficiencyPlot(num,den)
                    self.histos[hname].SetDirectory(0)
            file_.Close()

    def PlotHistos(self):
        for sample in self.Samples:
            for obj in self.objects:
                isMu = '#mu' in obj
                canv = tdrCanvas('canv_'+sample+obj, 0, 200, 0.6 if isMu else 0., 1.15 if isMu else 1.4, 'p_{T} [GeV]','Efficiency')
                leg = tdrLeg(0.23,0.20,0.95,0.5, 0.045, 42, ROOT.kBlack)
                leg.SetNColumns(1)
                line = rt.TLine(0,1,200,1)
                line.SetLineStyle(rt.kDashed)
                line.Draw('same')
                histos = sorted(list(filter(lambda x: sample in x and ('#mu' in x if isMu else not '#mu' in x), self.histos.keys())))
                for hname in histos:
                    hist = self.histos[hname]
                    color = colors[hname.replace(sample,'')][0]
                    marker = colors[hname.replace(sample,'')][1]
                    lname = colors[hname.replace(sample,'')][2]
                    tdrDraw(hist, 'P', marker, color, 1, color, 0, color)
                    leg.AddEntry(hist, lname, 'lp')
                fname = os.path.join(self.outputdir,'_'.join(['LeptonEfficiency',self.year,sample,obj.replace('#','')])+'.pdf')
                if os.path.exists(fname): os.remove(fname)
                canv.SaveAs(fname)
                canv.Close()

def main():
    years = ['UL18']
    # for year,channel,isDR in list(itertools.product(years, Channels, [True,False])):
    for year in years:
        PlotSyst = PlotLeptonEfficiency(year=year)
        PlotSyst.LoadHistos()
        PlotSyst.PlotHistos()

if __name__ == '__main__':
    main()
