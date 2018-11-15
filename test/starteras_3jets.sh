##
## naf_submit.py -n ntupleslist.txt -e SimpleMssmHbbAnalysis (or other plugin to use) config-3j.cfg -x 50(number of files handled in one job) -j JSON.txt(no JSON for MC)
## If the config file contains a link to the filelist (ntuples) and the json, these parameters need not be defined here
##
## RERECO
##
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/C-CR-deep-rerecoc1-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/C-SR-deep-rerecoc1-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/D-CR-deep-rerecoc1-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/D-SR-deep-rerecoc1-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/E-CR-deep-rerecoc1-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/E-SR-deep-rerecoc1-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/F-CR-deep-rerecoc1-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigRereco/F-SR-deep-rerecoc1-3j.cfg
##
## RERECO - CASE 2
##
##naf_submit.py -n rootFileListErereco.txt -e SimpleMssmHbbAnalysis -c E-CR-deep-rerecoc2-3j.cfg 100 jsonNoPsL1c100.txt
##naf_submit.py -n rootFileListErereco.txt -e SimpleMssmHbbAnalysis -c E-SR-deep-rerecoc2-3j.cfg 100 jsonNoPsL1c100.txt
##naf_submit.py -n rootFileListFrereco.txt -e SimpleMssmHbbAnalysis -c F-CR-deep-rerecoc2-3j.cfg 100 jsonNoPsL1c100.txt
##naf_submit.py -n rootFileListFrereco.txt -e SimpleMssmHbbAnalysis -c F-SR-deep-rerecoc2-3j.cfg 100 jsonNoPsL1c100.txt
##
## MC - SIGNAL - LO
##
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/350-CR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/350-SR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/600-CR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/600-SR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1200-CR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1200-SR-deep-MC-sig-3j.cfg
##
## MC - SIGNAL - NLO
##
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/200-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/200-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/250-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/250-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/350-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/350-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/400-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/400-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/450-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/450-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/500-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/500-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/600-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/600-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/700-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/700-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/800-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/800-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/900-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/900-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1000-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1000-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1200-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1200-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1400-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1400-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1600-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1600-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1800-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/1800-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/2000-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/2000-SR-deep-MC-NLO-sig-3j.cfg
##
## MC - BG
##
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-30-50-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-30-50-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-50-80-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-50-80-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-80-120-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-80-120-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-120-170-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-120-170-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-170-300-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-170-300-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-300-470-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-300-470-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-470-600-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-470-600-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-600-800-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-600-800-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-800-1000-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-800-1000-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-1000-1400-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-1000-1400-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-1400-1800-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-1400-1800-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-1800-2400-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-1800-2400-SR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-2400-3200-CR-deep-MC-bg-3j.cfg
#naf_submit.py -e SimpleMssmHbbAnalysis -x 50 -c Configs/3jets/ConfigMC/pt-2400-3200-SR-deep-MC-bg-3j.cfg