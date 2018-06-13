##
## naf_submit.csh ntupleslist.txt SimpleMssmHbbAnalysis (or other plugin to use) config.cfg 50(number of files handled in one job) JSON.txt(no JSON for MC)
##
## PROMPT
##
##naf_submit.csh rootFileListC.txt SimpleMssmHbbAnalysis ConfigPrompt/C-CR-deep-prompt.cfg 100 jsonrereco17.txt
##naf_submit.csh rootFileListC.txt SimpleMssmHbbAnalysis ConfigPrompt/C-SR-deep-prompt.cfg 100 jsonrereco17.txt
##naf_submit.csh rootFileListD.txt SimpleMssmHbbAnalysis ConfigPrompt/D-CR-deep-prompt.cfg 100 jsonrereco17.txt
##naf_submit.csh rootFileListD.txt SimpleMssmHbbAnalysis ConfigPrompt/D-SR-deep-prompt.cfg 100 jsonrereco17.txt
##naf_submit.csh rootFileListE.txt SimpleMssmHbbAnalysis ConfigPrompt/E-CR-deep-prompt.cfg 100 jsonrereco17.txt
##naf_submit.csh rootFileListE.txt SimpleMssmHbbAnalysis ConfigPrompt/E-SR-deep-prompt.cfg 100 jsonrereco17.txt
##naf_submit.csh rootFileListF.txt SimpleMssmHbbAnalysis ConfigPrompt/F-CR-deep-prompt.cfg 100 jsonrereco17.txt
##naf_submit.csh rootFileListF.txt SimpleMssmHbbAnalysis ConfigPrompt/F-SR-deep-prompt.cfg 100 jsonrereco17.txt
##
## RERECO
##
naf_submit.csh rootFileListCrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/C-CR-deep-rerecoc1.cfg 25 jsonrereco17.txt
naf_submit.csh rootFileListCrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/C-SR-deep-rerecoc1.cfg 25 jsonrereco17.txt
naf_submit.csh rootFileListDrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/D-CR-deep-rerecoc1.cfg 25 jsonrereco17.txt
naf_submit.csh rootFileListDrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/D-SR-deep-rerecoc1.cfg 25 jsonrereco17.txt
naf_submit.csh rootFileListErereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/E-CR-deep-rerecoc1.cfg 25 jsonrereco17.txt
naf_submit.csh rootFileListErereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/E-SR-deep-rerecoc1.cfg 25 jsonrereco17.txt
naf_submit.csh rootFileListFrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/F-CR-deep-rerecoc1.cfg 25 jsonrereco17.txt
naf_submit.csh rootFileListFrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/F-SR-deep-rerecoc1.cfg 25 jsonrereco17.txt
##
## RERECO - CASE 2
##
##naf_submit.csh rootFileListErereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/E-CR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##naf_submit.csh rootFileListErereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/E-SR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##naf_submit.csh rootFileListFrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/F-CR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##naf_submit.csh rootFileListFrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/F-SR-deep-rerecoc2.cfg 100 jsonNoPsL1c100.txt
##
## MC - SIGNAL
##
naf_submit.csh rootFileListMCsig350.txt SimpleMssmHbbAnalysis ConfigMC/350-CR-deep-MC-sig.cfg 25
naf_submit.csh rootFileListMCsig350.txt SimpleMssmHbbAnalysis ConfigMC/350-SR-deep-MC-sig.cfg 25
naf_submit.csh rootFileListMCsig600.txt SimpleMssmHbbAnalysis ConfigMC/600-CR-deep-MC-sig.cfg 25
naf_submit.csh rootFileListMCsig600.txt SimpleMssmHbbAnalysis ConfigMC/600-SR-deep-MC-sig.cfg 25
naf_submit.csh rootFileListMCsig1200.txt SimpleMssmHbbAnalysis ConfigMC/1200-CR-deep-MC-sig.cfg 25
naf_submit.csh rootFileListMCsig1200.txt SimpleMssmHbbAnalysis ConfigMC/1200-SR-deep-MC-sig.cfg 25
##
## MC - BG
##
naf_submit.csh rootFileListMCbgPT30to50.txt SimpleMssmHbbAnalysis ConfigMC/pt-30-50-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT30to50.txt SimpleMssmHbbAnalysis ConfigMC/pt-30-50-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT50to80.txt SimpleMssmHbbAnalysis ConfigMC/pt-50-80-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT50to80.txt SimpleMssmHbbAnalysis ConfigMC/pt-50-80-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT80to120.txt SimpleMssmHbbAnalysis ConfigMC/pt-80-120-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT80to120.txt SimpleMssmHbbAnalysis ConfigMC/pt-80-120-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT120to170.txt SimpleMssmHbbAnalysis ConfigMC/pt-120-170-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT120to170.txt SimpleMssmHbbAnalysis ConfigMC/pt-120-170-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT170to300.txt SimpleMssmHbbAnalysis ConfigMC/pt-170-300-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT170to300.txt SimpleMssmHbbAnalysis ConfigMC/pt-170-300-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT300to470.txt SimpleMssmHbbAnalysis ConfigMC/pt-300-470-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT300to470.txt SimpleMssmHbbAnalysis ConfigMC/pt-300-470-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT470to600.txt SimpleMssmHbbAnalysis ConfigMC/pt-470-600-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT470to600.txt SimpleMssmHbbAnalysis ConfigMC/pt-470-600-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT600to800.txt SimpleMssmHbbAnalysis ConfigMC/pt-600-800-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT600to800.txt SimpleMssmHbbAnalysis ConfigMC/pt-600-800-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT800to1000.txt SimpleMssmHbbAnalysis ConfigMC/pt-800-1000-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT800to1000.txt SimpleMssmHbbAnalysis ConfigMC/pt-800-1000-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT1000to1400.txt SimpleMssmHbbAnalysis ConfigMC/pt-1000-1400-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT1000to1400.txt SimpleMssmHbbAnalysis ConfigMC/pt-1000-1400-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT1400to1800.txt SimpleMssmHbbAnalysis ConfigMC/pt-1400-1800-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT1400to1800.txt SimpleMssmHbbAnalysis ConfigMC/pt-1400-1800-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT1800to2400.txt SimpleMssmHbbAnalysis ConfigMC/pt-1800-2400-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT1800to2400.txt SimpleMssmHbbAnalysis ConfigMC/pt-1800-2400-SR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT2400to3200.txt SimpleMssmHbbAnalysis ConfigMC/pt-2400-3200-CR-deep-MC-bg.cfg 25
naf_submit.csh rootFileListMCbgPT2400to3200.txt SimpleMssmHbbAnalysis ConfigMC/pt-2400-3200-SR-deep-MC-bg.cfg 25
