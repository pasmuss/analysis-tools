from subprocess import call
import os

NLO = True
selection = 'optimal'

if not (NLO) :
	selection += '_LO'
n_observed = -1 # NUMBER IN BACKGROUND


def CopyTemplateDatacard(path_to_template,path_to_new ): 
	if not os.path.exists(path_to_template):
		raise AttributeError("No txt file at " + path_to_template)
	call('cp ' + path_to_template + ' ' + path_to_new,shell=True)


def CreateDatacard(path_to_new, path_to_rootfile, n_observed): #n observed events
	if not os.path.exists(path_to_new):
		raise AttributeError("No txt file at " + path_to_new)
	print path_to_new
	call("sed -i 's/OBSERVATION/" + str(n_observed) + "/g' " + path_to_new,shell=True)
	call("sed -i 's|PATH_TO_ROOT|" + path_to_rootfile +"|g' "+path_to_new,shell=True)                                                                      
 

#CMSSW_BASE = os.environ('CMSSW_BASE') # cwd is the CMSSW_7 env 
path_to_dir = '/afs/desy.de/user/v/vagneria/cms/analysis2017/2017data/TTBar/Combine/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/combine/'

basename_of_template  = ( 'datacard_mssmhbb_' + selection ) 
basename_of_inputfile = ( 'inputfiles/histograms_'       + selection )

path_to_template  = (path_to_dir + 'datacards/'  + basename_of_template + '.txt')
 

if (NLO ):
	masses = [120, 130, 140, 160, 180, 200, 250, 350, 400, 450, 500, 600 ]
else :
	masses = [120,350,600]     

for m in masses:

        #For each m define datacard output file 
        basename_of_datacard = ( basename_of_template + '_m' + str(m) )
        path_to_datacard =  (path_to_dir + 'datacards/' + basename_of_datacard + '.txt')
	path_to_rootfile = (path_to_dir + basename_of_inputfile + '_m' + str(m) + '.root')

        #Copy and create for len(masses) datacards from template 
       	CopyTemplateDatacard(path_to_template,path_to_datacard) # cp template into datacard
	CreateDatacard(path_to_datacard, path_to_rootfile, n_observed)
