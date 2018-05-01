##
## naf_submit.csh ntupleslist.txt SimpleMssmHbbAnalysis config.cfg 50(number of files handled in one job) JSON.txt(no JSON for MC)
##
## PROMPT
##
##
## RERECO - CASE 2
##
naf_submit.csh rootFileListErereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/E-CR-deep-rerecoc2.cfg 50 jsonNoPsL1c100.txt
naf_submit.csh rootFileListErereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/E-SR-deep-rerecoc2.cfg 50 jsonNoPsL1c100.txt
naf_submit.csh rootFileListFrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/F-CR-deep-rerecoc2.cfg 50 jsonNoPsL1c100.txt
naf_submit.csh rootFileListFrereco.txt SimpleMssmHbbAnalysis ConfigRerecoNewJSON/F-SR-deep-rerecoc2.cfg 50 jsonNoPsL1c100.txt
##
## MC - SIGNAL
##
##
## MC - BG
##