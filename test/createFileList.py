import os

basedir = '/pnfs/desy.de/cms/tier2/store/user/rwalsh/Analysis/Ntuples/MC/Fall17/ntuplizer_94X_mc_2017_fall17-v4/'
prefix = 'QCD_HT'
suffix = '_TuneCP5_13TeV-madgraph-pythia8/'
eras = ['200to300','300to500','500to700','700to1000','1000to1500','1500to2000','2000toInf']

for era in eras:
    ntuplelist = []
    print(era)
    with open('filelists/rootFileList_MadgraphQCDHT'+str(era)+'.txt','w') as filelist:
        folders = os.listdir(basedir+prefix+str(era)+suffix)
        for folder in folders:
            folderpath = basedir+prefix+str(era)+suffix+folder+'/'
            times = os.listdir(folderpath)
            for time in times:
                timepath = folderpath+time+'/'
                parts = os.listdir(timepath)
                for part in parts:
                    partpath = timepath+part+'/'
                    ntuples = os.listdir(partpath)
                    for ntuple in ntuples:
                        ntuplepath = partpath+ntuple+'\n'
                        filelist.write(ntuplepath)
