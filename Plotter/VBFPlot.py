import glob, os, ROOT
ROOT.gROOT.SetBatch(ROOT.kTRUE)
# ROOT.gStyle.SetOptStat(000112211)
ROOT.gStyle.SetOptFit(0)
import numpy as np
from tdrstyle_all import *
import tdrstyle_all as TDR
TDR.extraText  = ""
TDR.lumi_13TeV = ""

pdgidlist = ["other", "e", "#mu", "#nu_{e}", "#nu_{#mu}", "#nu_{#tau}",
             "#gamma",
             # "Z", "W", "H", "#pi^{0}",
             "#pi^{+}", "K^{0}_{L}",
             "K^{0}_{S}", "K^{+}", "#Lambda", "p"]


class MyPlot():
    def __init__(self):
        self.inputPath = "/user/dadelatt/CMSSW_10_6_28/src/LEAF/../../../WorkingArea/VBFTagger/UL18/GenLevelStudies/"
        self.outputPath = "/user/dadelatt/CMSSW_10_6_28/src/LEAF/../../../WorkingArea/VBFTagger/UL18/GenLevelStudies/plots/"
        self.fname  = ["MC__VBF_HToZZTo4L_M125_standard_UL18.root",
                       "MC__GluGluHToZZTo4L_M125_standard_UL18.root"
                       ]
        self.color = {"VBF_HToZZTo4L": ROOT.kRed+1,
                      "GluGluHToZZTo4L": ROOT.kAzure+2}

        self.style = {'VBF_HToZZTo4L': ROOT.kSolid,
                      'GluGluHToZZTo4L': ROOT.kDashed}

        self.legend = {"VBF_HToZZTo4L": "VBF H",
                       "GluGluHToZZTo4L": "gg->ggH"}
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
            hname = i.replace("MC__","").replace("_M125_standard_UL18.root","")
            self.hlist[hname] = hist
            f_.Close()



    def Plot(self, directory, name):
        self.Get_Hist(directory, name)
        # TDR.cms_lumi_TeV = TDR.commonScheme["legend"]["Run2"]+" Legacy, "+TDR.commonScheme["lumi"]["Run2"]+" fb^{-1}"
        # TDR.extraText3.append("#bf{Anti-k_{T} (R = 0.4), PF+CHS}")
        # TDR.extraText3.append("#bf{p_{T}^{jet} > 100 GeV}")
        refhist = self.hlist["VBF_HToZZTo4L"]
        print(refhist)
        PlotXMin = refhist.GetBinLowEdge(1)
        PlotXMax = refhist.GetBinLowEdge(refhist.GetNbinsX()+1)
        PlotYMin = 0.0001
        PlotYMax = 1
        canv = tdrCanvas("H->4L", PlotXMin, PlotXMax, PlotYMin, PlotYMax, refhist.GetXaxis().GetTitle(), refhist.GetYaxis().GetTitle())
        if name == 'gen_part_pdgid2' or name == 'gen_part_pdgid':
            #print(list(canv.GetListOfPrimitives()))
            testhist = canv.GetPrimitive("hframe")
            testhist.SetBins(refhist.GetNbinsX(), 0, refhist.GetNbinsX())
            #print("nBins: ", testhist.GetNbinsX())
            for i in range(1, testhist.GetNbinsX()+1):
                testhist.GetXaxis().SetBinLabel(i,str(pdgidlist[i-1]))
        canv.SetLogy(True)
        leg = tdrLeg(0.50,0.8,0.89,0.89, textSize = 0.03)

        for na, h in self.hlist.items():
            tdrDraw(h, "h", lcolor = self.color[na], lstyle=self.style[na], fstyle=0, marker = 0)
            ent = h.GetEntries()
            leg.AddEntry(h, self.legend[na] + ". Entries: " + str(ent), "l")

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
        outname = self.outputPath+str(name)+".pdf"
        if os.path.exists(outname):
            os.remove(outname)
        canv.SaveAs(outname)

def main():
    # MyPlot().Plot("nominal_GenLevel_Mjj>200__", "gen_jet_number")
    # MyPlot().Plot("nominal_GenLevel_Mjj>200__", "gen_jet_Pt")
    # MyPlot().Plot("nominal_GenLevel_Mjj>200__", "gen_jet_Eta")
    # MyPlot().Plot("nominal_GenLevel_Mjj>200__", "gen_jet_Ht")
    # MyPlot().Plot("nominal_GenLevel_Mjj>200__", "gen_LJ_dEta")
    # MyPlot().Plot("nominal_GenLevel_Mjj>200__", "gen_LJ_dR")
    # MyPlot().Plot("nominal_GenLevel_Mjj>200__", "gen_LJ_Mass")
    MyPlot().Plot("nominal_GenLevel", "gen_part_pdgid2")
    MyPlot().Plot("nominal_GenLevel", "gen_part_pdgid")

if __name__ == '__main__':
    main()
