import os

basedir = '/pnfs/desy.de/cms/tier2/store/user/rwalsh/Analysis/Ntuples/MC/Fall2017/ntuplizer_94X_mc_2017_fall17-v3/'
prefix = 'SUSYGluGluToBBHToBB_M-'
suffix = '_TuneCP5_13TeV-amcatnlo-pythia8/'

masspoints = [120,130,140,160,180,200,250,350,400,450,500,600,700,800,900,1000,1200,1400,1600,1800,2000]

for masspoint in masspoints:
    ntuplelist = []
    print(masspoint)
    filelist = open('filelists/rootFileListMCsig'+str(masspoint)+'NLOFall17.txt','w')
    foldercontent = os.listdir(basedir+prefix+str(masspoint)+suffix)
    for folder in foldercontent:
        folderpath = basedir+prefix+str(masspoint)+suffix+folder+'/'
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
    filelist.close()
