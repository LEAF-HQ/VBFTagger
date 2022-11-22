from DNNTools.PreprocessInputsBase import *
from sklearn.compose import ColumnTransformer

class PreprocessInputs(PreprocessInputsBase):
    def __init__(self, inputdir, outdir, samples, classes, dtype, maxfiles_per_sample=None):
        PreprocessInputsBase.__init__(self, inputdir=inputdir, outdir=outdir, dtypes=dtype)
        self.samples = samples
        self.classes = classes

    def DefineSamples(self):
        return self.samples

    def DefineClasses(self):
        return self.classes

    def FitScalers(self):
        from sklearn import preprocessing
        self.scalers = {}
        # self.scalers['standard'] = ColumnTransformer(list((col+'st',preprocessing.StandardScaler() if 'pt' in col else preprocessing.FunctionTransformer(), [col]) for col in self.inputs['train'].columns.tolist()))
        # self.scalers['standard'].fit(self.inputs['train'])

    def FilterInputs(self, df, filter_regex):
        if filter_regex==['all'] or filter_regex==None:
            return df
        if isinstance(filter_regex, list):
            filter_regex_ = list(filter_regex)
            eventCategory = list(filter(lambda x: 'eventCategory' in x ,filter_regex_))
            if len(eventCategory)>0:
                for x in eventCategory:
                    filter_regex_.remove(x)
                filter_regex_.append('eventCategory')
                eventCategory = [int(x.replace('eventCategory','')) for x in eventCategory if x!='eventCategory']
                if len(eventCategory)==0:
                    eventCategory = None
            else:
                eventCategory = None
            filter_regex_ = '|'.join(filter_regex_)
        else:
            filter_regex_ = filter_regex
            eventCategory = None
        weights = df.filter(regex=self.colname_weights)
        labels = df.filter(regex=self.colname_category)
        df = df.filter(regex=filter_regex_)
        if eventCategory:
            mask = ~df.eventCategory.isin(eventCategory)
            weights = weights[mask]
            labels = labels[mask]
            df = df[mask]
            df = df.drop(columns=['eventCategory'])
        # to_remove = [x for x in df.columns[:-1] if int(x.replace(filter_regex,'').split('_')[0])>100]
        # df = df.drop(columns=to_remove)
        return pd.concat([df, weights, labels], axis=1, join='inner')

    def Process(self, filter_regex=None):
        self.GetInputs(format='pkl', filter_regex=filter_regex)
        # self.RemoveNanInf(df=self.df)
        self.SampleEvents(fraction=self.runonfraction, random_state=42)
        self.Split(ratios={'train':0.7, 'validation':0.15, 'test':0.15})
        self.FitScalers()
        self.Transform()
        self.Save()
