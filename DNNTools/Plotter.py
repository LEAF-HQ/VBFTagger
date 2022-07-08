from DNNTools.PlotterBase import *
import ROOT as rt

class Plotter(PlotterBase):
    def __init__(self, classes):
        PlotterBase.__init__(self)
        self.classes = classes

    def DefineCommonStyle(self):
        self.common_style = {
            'linewidth': 1.5,
            'histtype': 'step',
            'alpha': 0.99,
            'bins': 100,
            'density': True,
        }

    def DefineStylePerVariable(self):
        self.stylePerVariable = {'phi':{'bins': 25}}

    def DefineStyle(self):
        style = {
            self.classes['GluGlu']: {
                'label': 'GluGlu',
                'linestyle': 'solid',
                'color': 'C0',
                # 'rootcolor': rt.TColor.GetColor('#95BBD9'),
                'rootcolor': rt.kAzure+7,
                },
            self.classes['VBF']: {
                'label': 'VBF',
                'linestyle': 'solid',
                'color': 'C1',
                # 'rootcolor': rt.TColor.GetColor('#FFC08C'),
                'rootcolor': rt.kOrange+1,
                },
        }
        return style

    def PlotPerformance(self, predictions, weights, labels, outdir):
        print(blue('--> Plotting performance'))
        # for class i, the score of the i'th node should be used: 'score_%i' % (i) for the "summary ROC curve".
        self.PlotROCSummary(df=predictions, weights=weights, labels=labels, outdir=outdir)
        # for colname in predictions.columns:
        #     if not 'score' in colname: continue
        #     self.PlotROCSingleVariable(df=predictions, variable_name=colname, outdir=outdir)
