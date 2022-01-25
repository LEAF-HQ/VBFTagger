import glob, argparse
import math
import numpy as np
import pandas as pd
from array import array

from ModuleRunnerBase import *
from utils import *

# from tdrstyle_all import *
# from StatisticFunctions import *

# ROOT.gInterpreter.ProcessLine('#include "'+os.environ["CMSSW_BASE"]+'/src/UHH2/VHResonances/include/constants.hpp"')
ROOT.gInterpreter.Declare('#include "LEAF/Analyzer/include/mytestfolder/TagConstants.h"')
ROOT.gInterpreter.Declare('#include "LEAF/Analyzer/include/mytestfolder/RunConstants.h"')
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)

def PrintFormattedLine(listArgs=[], space=10):
    for x in listArgs: print x, " "*(space-len(str(x)) if space-len(str(x))>0 else 2*space-len(str(x))),
    print "\t"
