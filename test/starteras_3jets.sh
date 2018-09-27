##
## naf_submit.py ntupleslist.txt -e SimpleMssmHbbAnalysis (or other plugin to use) config-3j.cfg -x 50(number of files handled in one job) JSON.txt(no JSON for MC)
##
## RERECO
##
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListCrerecoMar18.txt -x 50 -c C-CR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListCrerecoMar18.txt -x 50 -c C-SR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListDrerecoMar18.txt -x 50 -c D-CR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListDrerecoMar18.txt -x 50 -c D-SR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListErerecoMar18.txt -x 50 -c E-CR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListErerecoMar18.txt -x 50 -c E-SR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListFrerecoMar18.txt -x 50 -c F-CR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListFrerecoMar18.txt -x 50 -c F-SR-deep-rerecoc1-3j.cfg -j jsondata17rerecoMar18.txt
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
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig350.txt -x 50 -c 350-CR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig350.txt -x 50 -c 350-SR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig600.txt -x 50 -c 600-CR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig600.txt -x 50 -c 600-SR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1200.txt -x 50 -c 1200-CR-deep-MC-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1200.txt -x 50 -c 1200-SR-deep-MC-sig-3j.cfg
##
## MC - SIGNAL - NLO
##
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig200NLOFall17.txt -x 50 -c 200-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig200NLOFall17.txt -x 50 -c 200-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig250NLOFall17.txt -x 50 -c 250-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig250NLOFall17.txt -x 50 -c 250-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig350NLOFall17.txt -x 50 -c 350-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig350NLOFall17.txt -x 50 -c 350-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig400NLOFall17.txt -x 50 -c 400-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig400NLOFall17.txt -x 50 -c 400-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig450NLOFall17.txt -x 50 -c 450-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig450NLOFall17.txt -x 50 -c 450-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig500NLOFall17.txt -x 50 -c 500-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig500NLOFall17.txt -x 50 -c 500-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig600NLOFall17.txt -x 50 -c 600-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig600NLOFall17.txt -x 50 -c 600-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig700NLOFall17.txt -x 50 -c 700-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig700NLOFall17.txt -x 50 -c 700-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig800NLOFall17.txt -x 50 -c 800-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig800NLOFall17.txt -x 50 -c 800-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig900NLOFall17.txt -x 50 -c 900-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig900NLOFall17.txt -x 50 -c 900-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1000NLOFall17.txt -x 50 -c 1000-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1000NLOFall17.txt -x 50 -c 1000-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1200NLOFall17.txt -x 50 -c 1200-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1200NLOFall17.txt -x 50 -c 1200-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1400NLOFall17.txt -x 50 -c 1400-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1400NLOFall17.txt -x 50 -c 1400-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1600NLOFall17.txt -x 50 -c 1600-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1600NLOFall17.txt -x 50 -c 1600-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1800NLOFall17.txt -x 50 -c 1800-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig1800NLOFall17.txt -x 50 -c 1800-SR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig2000NLOFall17.txt -x 50 -c 2000-CR-deep-MC-NLO-sig-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCsig2000NLOFall17.txt -x 50 -c 2000-SR-deep-MC-NLO-sig-3j.cfg
##
## MC - BG
##
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT30to50.txt -x 50 -c pt-30-50-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT30to50.txt -x 50 -c pt-30-50-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT50to80.txt -x 50 -c pt-50-80-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT50to80.txt -x 50 -c pt-50-80-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT80to120.txt -x 50 -c pt-80-120-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT80to120.txt -x 50 -c pt-80-120-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT120to170.txt -x 50 -c pt-120-170-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT120to170.txt -x 50 -c pt-120-170-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT170to300.txt -x 50 -c pt-170-300-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT170to300.txt -x 50 -c pt-170-300-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT300to470.txt -x 50 -c pt-300-470-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT300to470.txt -x 50 -c pt-300-470-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT470to600.txt -x 50 -c pt-470-600-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT470to600.txt -x 50 -c pt-470-600-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT600to800.txt -x 50 -c pt-600-800-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT600to800.txt -x 50 -c pt-600-800-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT800to1000.txt -x 50 -c pt-800-1000-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT800to1000.txt -x 50 -c pt-800-1000-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT1000to1400.txt -x 50 -c pt-1000-1400-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT1000to1400.txt -x 50 -c pt-1000-1400-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT1400to1800.txt -x 50 -c pt-1400-1800-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT1400to1800.txt -x 50 -c pt-1400-1800-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT1800to2400.txt -x 50 -c pt-1800-2400-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT1800to2400.txt -x 50 -c pt-1800-2400-SR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT2400to3200.txt -x 50 -c pt-2400-3200-CR-deep-MC-bg-3j.cfg
naf_submit.py -e SimpleMssmHbbAnalysis -n rootFileListMCbgPT2400to3200.txt -x 50 -c pt-2400-3200-SR-deep-MC-bg-3j.cfg