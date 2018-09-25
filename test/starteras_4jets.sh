##
## naf_submit.csh ntupleslist.txt SimpleMssmHbbAnalysis (or other plugin to use) config.cfg 50(number of files handled in one job) JSON.txt(no JSON for MC)
##
## RERECO
##
naf_submit.csh filelists/rootFileListCrerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/C-CR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
naf_submit.csh filelists/rootFileListCrerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/C-SR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
naf_submit.csh filelists/rootFileListDrerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/D-CR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
naf_submit.csh filelists/rootFileListDrerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/D-SR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
naf_submit.csh filelists/rootFileListErerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/E-CR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
naf_submit.csh filelists/rootFileListErerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/E-SR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
naf_submit.csh filelists/rootFileListFrerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/F-CR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
naf_submit.csh filelists/rootFileListFrerecoMar18.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/F-SR-deep-rerecoc1.cfg 50 jsonfiles/jsondata17rerecoMar18.txt
##
## RERECO - CASE 2
##
##naf_submit.csh filelists/rootFileListErereco.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/E-CR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##naf_submit.csh filelists/rootFileListErereco.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/E-SR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##naf_submit.csh filelists/rootFileListFrereco.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/F-CR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##naf_submit.csh filelists/rootFileListFrereco.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigRereco/F-SR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##
## MC - SIGNAL - LO
##
naf_submit.csh filelists/rootFileListMCsig350.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/350-CR-deep-MC-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig350.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/350-SR-deep-MC-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig600.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/600-CR-deep-MC-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig600.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/600-SR-deep-MC-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1200.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1200-CR-deep-MC-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1200.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1200-SR-deep-MC-sig.cfg 50
##
## MC - SIGNAL - NLO
##
naf_submit.csh filelists/rootFileListMCsig200NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/200-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig200NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/200-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig250NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/250-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig250NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/250-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig350NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/350-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig350NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/350-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig400NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/400-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig400NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/400-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig450NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/450-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig450NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/450-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig500NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/500-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig500NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/500-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig600NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/600-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig600NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/600-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig700NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/700-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig700NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/700-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig800NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/800-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig800NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/800-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig900NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/900-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig900NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/900-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1000NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1000-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1000NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1000-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1200NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1200-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1200NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1200-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1400NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1400-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1400NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1400-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1600NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1600-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1600NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1600-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1800NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1800-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig1800NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/1800-SR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig2000NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/2000-CR-deep-MC-NLO-sig.cfg 50
naf_submit.csh filelists/rootFileListMCsig2000NLOFall17.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/2000-SR-deep-MC-NLO-sig.cfg 50

##
## MC - BG
##
naf_submit.csh filelists/rootFileListMCbgPT30to50.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-30-50-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT30to50.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-30-50-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT50to80.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-50-80-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT50to80.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-50-80-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT80to120.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-80-120-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT80to120.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-80-120-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT120to170.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-120-170-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT120to170.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-120-170-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT170to300.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-170-300-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT170to300.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-170-300-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT300to470.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-300-470-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT300to470.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-300-470-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT470to600.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-470-600-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT470to600.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-470-600-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT600to800.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-600-800-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT600to800.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-600-800-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT800to1000.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-800-1000-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT800to1000.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-800-1000-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT1000to1400.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-1000-1400-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT1000to1400.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-1000-1400-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT1400to1800.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-1400-1800-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT1400to1800.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-1400-1800-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT1800to2400.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-1800-2400-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT1800to2400.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-1800-2400-SR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT2400to3200.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-2400-3200-CR-deep-MC-bg.cfg 50
naf_submit.csh filelists/rootFileListMCbgPT2400to3200.txt SimpleMssmHbbAnalysis Configs/4jets/ConfigMC/pt-2400-3200-SR-deep-MC-bg.cfg 50
