import glob, os, ROOT
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(11)
ROOT.gStyle.SetOptFit(0)
import numpy as np
from tdrstyle_all import *
import tdrstyle_all as TDR
TDR.extraText  = ""
TDR.lumi_13TeV = ""


def Draw2d(h, opt, axistitles):
  h.GetXaxis().SetTitle(axistitles[0])
  h.GetYaxis().SetTitle(axistitles[1])
  h.GetZaxis().SetTitle(axistitles[2])
  h.GetYaxis().SetTitleOffset(1.15)
  h.GetZaxis().SetTitleOffset(1.3)
  TDR.SetAlternative2DColor(h)
  TDR.HistCosmetics(h)
  h.Draw('AXIS')
  h.Draw(opt)
  # h.GetZaxis().SetRangeUser(zmin, zmax)
  ROOT.gPad.RedrawAxis()


class MyPlot():
    def __init__(self):
        self.inputPath = "/user/dadelatt/CMSSW_10_6_28/src/LEAF/../../../VBFTagger/UL18/GenLevelStudies/"
        self.outputPath = "/user/dadelatt/CMSSW_10_6_28/src/LEAF/../../../VBFTagger/UL18/GenLevelStudies/plots/distributions/"
        self.fname  = ["MC__VBF_HToZZTo4L_M125_UL18.root",
                       "MC__GluGluHToZZTo4L_M125_UL18.root"
                       ]
        self.color = {"VBF_HToZZTo4L": ROOT.kRed,
                      "GluGluHToZZTo4L": ROOT.kBlue}
        self.legend = {"VBF_HToZZTo4L": "VBF",
                       "GluGluHToZZTo4L": "GluGlu"}
        # self.dirname = ["input", "weight", "cleaner", "njets", "nominal"]
        # self.dirname2 = ["General", "Jets"]


    def Get_Hist(self, directory, name):
        self.hlist = {}
        for i in self.fname:
            f_=ROOT.TFile(self.inputPath + i)
            # ROOT.TFile(MyPlot().inputPath + i).ls()
            hist = f_.Get(str(directory)+"/"+str(name))
            hist.Scale(1./hist.Integral())
            hist.SetDirectory(0)
            hname = i.replace("MC__","").replace("_M125_UL18.root","")
            self.hlist[hname] = hist
            f_.Close()



    def Plot(self, directory, name):
        self.Get_Hist(directory, name)
        # TDR.cms_lumi_TeV = TDR.commonScheme["legend"]["Run2"]+" Legacy, "+TDR.commonScheme["lumi"]["Run2"]+" fb^{-1}"
        # TDR.extraText3.append("#bf{Anti-k_{T} (R = 0.4), PF+CHS}")
        # TDR.extraText3.append("#bf{p_{T}^{jet} > 100 GeV}")
        NbinX = 8001
        PlotXMin = -4000.5
        PlotXMax = 4000.5
        NbinY = 9
        PlotYMin = 0
        PlotYMax = 8
        ZMin = 0
        ZMax = 10^7

        for na, h in self.hlist.items():
            canv = tdrCanvas2d("PdgId & Status")
            # leg = tdrLeg(0.68,0.60,0.89,0.89, textSize = 0.025)
            Draw2d(h, "colz", ["PdgID", "Status", "Number"])
            # ent = h.GetEntries()
            # leg.AddEntry(h, self.legend[na] + ". Entries: " + str(ent), "l")
            canv.SaveAs(self.outputPath+str(directory)+"_"+name+na+"2D.pdf")

        # for year in self.years+["Run2"]:
        #     color = self.SFs[year]["color"]
        #     marker = self.SFs[year]["marker"]
        #     if "Run2"== year:
        #         tdrDraw(self.SFs[year]["graph"], "E2", mcolor=color, fcolor=color, alpha=0.15)
        #     else:
        #         tdrDraw(self.SFs[year]["graph"], "P5", marker=marker, mcolor=color, fcolor=color, alpha=0.15)
        #     leg.AddEntry(self.SFs[year]["graph"], self.SFs[year]["legend"], "f" if "Run2" in year else "fp")
        # line_MC = ROOT.TLine(PlotXMin, 1, PlotXMax, 1)
        # line_MC.SetLineWidth(1)
        # line_MC.SetLineStyle(ROOT.kDotted)
        # line_MC.SetLineColor(ROOT.kBlack)
        # line_MC.Draw("same")

def main():
    MyPlot().Plot("weight_General", "ParticleStatusFlag")

if __name__ == '__main__':
    main()
