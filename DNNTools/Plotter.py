from DNNTools.PlotterBase import *

class Plotter(PlotterBase):
    def __init__(self, classes):
        PlotterBase.__init__(self)
        self.classes = classes

    def DefineCommonStyle(self):
        self.common_style = {
            'linewidth': 1.5,
            'histtype': 'step',
            'alpha': 0.5,
            'bins': 100,
            'density': True,
        }

    def DefineStylePerVariable(self):
        self.stylePerVariable = {'phi':{'bins': 25}}

    def DefineClasses(self):
        return self.classes

    def DefineStyle(self):
        style = {
            self.classes['GluGlu']: {
                'label': 'GluGlu: training sample',
                'linestyle': 'solid',
                'color': 'C0'
                },
            self.classes['VBF']: {
                'label': 'VBF: training sample',
                'linestyle': 'solid',
                'color': 'C1'
                },
        }
        return style
