import os

basedir = '/pnfs/desy.de/cms/tier2/store/user/rwalsh/Analysis/Ntuples/DATA/Run2017/ntuplizer_94X_2017_rereco31Mar18-v4/JetHT/'
prefix = 'Run2017'
suffix = '-31Mar2018-v1/'

eras = ['C','D','E','F']

for era in eras:
    ntuplelist = []
    print(era)
    with open('filelists/rootFileListJetHT_Run2017'+str(era)+'.txt','w') as filelist:
        times = os.listdir(basedir+prefix+str(era)+suffix)
        for time in times:
            timepath = basedir+prefix+str(era)+suffix+time+'/'
            parts = os.listdir(timepath)
            for part in parts:
                partpath = timepath+part+'/'
                ntuples = os.listdir(partpath)
                for ntuple in ntuples:
                    ntuplepath = partpath+ntuple+'\n'
                    filelist.write(ntuplepath)
