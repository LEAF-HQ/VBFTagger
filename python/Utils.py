import glob, argparse
import math
import numpy as np
import pandas as pd
from array import array

from ModuleRunnerBase import GenericPath, VariablesBase
from tdrstyle_all import *
# from StatisticFunctions import *

import ROOT
ROOT.gSystem.Load('libConstants.so')
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)

def PrintFormattedLine(listArgs=[], space=10):
    for x in listArgs: print x, " "*(space-len(str(x)) if space-len(str(x))>0 else 2*space-len(str(x))),
    print "\t"


def CreateEfficiencyPlot(num,den):
    eff = num.Clone(num.GetName()+'Efficiency')
    eff.Divide(eff,den,1,1,'B')
    return eff
