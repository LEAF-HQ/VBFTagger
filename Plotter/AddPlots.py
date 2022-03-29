import glob, os, ROOT
ROOT.gROOT.SetBatch(ROOT.kTRUE)
# ROOT.gStyle.SetOptStat(000112211)
ROOT.gStyle.SetOptFit(0)
import numpy as np
from tdrstyle_all import *
import tdrstyle_all as TDR
TDR.extraText  = ""
TDR.lumi_13TeV = ""

name1 = "NumberOfParticles<1GeV"
name2 = "NumberOfChargedParticles<1GeV"

class MyPlot():
    def __init__(self):
        self.inputPath = "/user/dadelatt/CMSSW_10_6_28/src/LEAF/../../../VBFTagger/UL18/GenLevelStudies/"
        self.outputPath = "/user/dadelatt/CMSSW_10_6_28/src/LEAF/../../../VBFTagger/UL18/GenLevelStudies/plots/distributions/"
        self.fname  = ["MC__VBF_HToZZTo4L_M125_UL18.root",
                       "MC__GluGluHToZZTo4L_M125_UL18.root"
                       ]
        self.color = {"VBF_HToZZTo4L " + name1: ROOT.kRed,
                      "GluGluHToZZTo4L " + name1: ROOT.kBlue,
                      "VBF_HToZZTo4L " + name2: ROOT.kBlack,
                      "GluGluHToZZTo4L " + name2: ROOT.kGreen}
        self.ld = {"VBF_HToZZTo4L": "VBF",
                       "GluGluHToZZTo4L": "GluGlu"}
        self.hlist = {}
        self.legend = {}


    def Get_Hist(self, directory, name):
        for i in self.fname:
            f_=ROOT.TFile(self.inputPath + i)
            # ROOT.TFile(MyPlot().inputPath + i).ls()
            hist = f_.Get(str(directory)+"/"+str(name))
            hist.Scale(1./hist.Integral())
            hist.SetDirectory(0)
            hname = i.replace("MC__","").replace("_M125_UL18.root"," "+str(name))
            self.hlist[hname] = hist
            self.legend[hname] = self.ld[hname.split(" ")[0]] + str(name)
            f_.Close()



    def Plot(self, directory1, name1, directory2, name2):
        self.Get_Hist(directory1, name1)
        self.Get_Hist(directory2, name2)
        #print(self.hlist)
        PlotXMin = -0.5
        PlotXMax = 50.5
        PlotYMin = 0.0000001
        PlotYMax = 1.2
        canv = tdrCanvas("H->4L", PlotXMin, PlotXMax, PlotYMin, PlotYMax, "Number of particles", "Events")
        canv.SetLogy(True)
        leg = tdrLeg(0.45,0.8,0.89,0.9, textSize = 0.015)

        for na, h in self.hlist.items():
            tdrDraw(h, "h", lcolor = self.color[na], fstyle=0, marker = 0)
            ent = h.GetEntries()
            leg.AddEntry(h, self.legend[na] + ". Entries: " + str(ent), "l")


        canv.SaveAs(self.outputPath+str(directory1)+"_"+str(name1)+".pdf")

def main():
    MyPlot().Plot("input_General", "NumberOfParticles<1GeV", "input_General", "NumberOfChargedParticles<1GeV")

if __name__ == '__main__':
    main()
