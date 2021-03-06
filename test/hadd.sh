mkdir rootfiles
mkdir rootfiles/rereco
#mkdir rootfiles/mcbg
mkdir rootfiles/mcsig

### MC BG

#hadd rootfiles/mcbg/mc-bg-1000-1400-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-1000-1400-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-120-170-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-120-170-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1400-1800-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-1400-1800-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-170-300-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-170-300-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1800-2400-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-1800-2400-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-2400-3200-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-2400-3200-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-30-50-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-30-50-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-300-470-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-300-470-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-470-600-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-470-600-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-50-80-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-50-80-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-600-800-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-600-800-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-80-120-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-80-120-SR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-800-1000-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_pt-800-1000-SR-deep-MC-bg/*/*.root`

#hadd rootfiles/mcbg/mc-bg-1000-1400-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-1000-1400-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-120-170-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-120-170-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1400-1800-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-1400-1800-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-170-300-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-170-300-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1800-2400-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-1800-2400-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-2400-3200-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-2400-3200-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-30-50-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-30-50-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-300-470-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-300-470-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-470-600-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-470-600-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-50-80-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-50-80-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-600-800-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-600-800-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-80-120-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-80-120-CR-deep-MC-bg/*/*.root`
#hadd rootfiles/mcbg/mc-bg-800-1000-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_pt-800-1000-CR-deep-MC-bg/*/*.root`

### RERECO

hadd rootfiles/rereco/rereco-C-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_C-SR-deep-rerecoc1/*/*.root`
hadd rootfiles/rereco/rereco-D-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_D-SR-deep-rerecoc1/*/*.root`
hadd rootfiles/rereco/rereco-E-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_E-SR-deep-rerecoc1/*/*.root`
hadd rootfiles/rereco/rereco-F-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_F-SR-deep-rerecoc1/*/*.root`

hadd rootfiles/rereco/rereco-C-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_C-CR-deep-rerecoc1/*/*.root`
hadd rootfiles/rereco/rereco-D-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_D-CR-deep-rerecoc1/*/*.root`
hadd rootfiles/rereco/rereco-E-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_E-CR-deep-rerecoc1/*/*.root`
hadd rootfiles/rereco/rereco-F-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_F-CR-deep-rerecoc1/*/*.root`

hadd rootfiles/rereco/rereco-CDE-deep-CR.root rootfiles/rereco/rereco-C-deep-CR.root rootfiles/rereco/rereco-D-deep-CR.root rootfiles/rereco/rereco-E-deep-CR.root
hadd rootfiles/rereco/rereco-CDE-deep-SR.root rootfiles/rereco/rereco-C-deep-SR.root rootfiles/rereco/rereco-D-deep-SR.root rootfiles/rereco/rereco-E-deep-SR.root
hadd rootfiles/rereco/rereco-CDEF-deep-CR.root rootfiles/rereco/rereco-C-deep-CR.root rootfiles/rereco/rereco-D-deep-CR.root rootfiles/rereco/rereco-E-deep-CR.root rootfiles/rereco/rereco-F-deep-CR.root
hadd rootfiles/rereco/rereco-CDEF-deep-SR.root rootfiles/rereco/rereco-C-deep-SR.root rootfiles/rereco/rereco-D-deep-SR.root rootfiles/rereco/rereco-E-deep-SR.root rootfiles/rereco/rereco-F-deep-SR.root

### MC SIGNAL LO

hadd rootfiles/mcsig/mc-sig-350-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_350-SR-deep-MC-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_600-SR-deep-MC-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_1200-SR-deep-MC-sig/*/*.root`

hadd rootfiles/mcsig/mc-sig-350-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_350-CR-deep-MC-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_600-CR-deep-MC-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_1200-CR-deep-MC-sig/*/*.root`

### MC SIGNAL NLO

hadd rootfiles/mcsig/mc-sig-200-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_200-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-250-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_250-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-350-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_350-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-400-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_400-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-450-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_450-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-500-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_500-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_600-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-700-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_700-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-800-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_800-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-900-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_900-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1000-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_1000-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_1200-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1400-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_1400-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1600-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_1600-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1800-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_1800-SR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-2000-NLO-deep-SR.root `find Condor_SimpleMssmHbbAnalysis_2000-SR-deep-MC-NLO-sig/*/*.root`

hadd rootfiles/mcsig/mc-sig-200-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_200-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-250-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_250-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-350-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_350-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-400-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_400-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-450-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_450-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-500-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_500-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_600-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-700-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_700-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-800-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_800-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-900-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_900-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1000-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_1000-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_1200-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1400-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_1400-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1600-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_1600-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-1800-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_1800-CR-deep-MC-NLO-sig/*/*.root`
hadd rootfiles/mcsig/mc-sig-2000-NLO-deep-CR.root `find Condor_SimpleMssmHbbAnalysis_2000-CR-deep-MC-NLO-sig/*/*.root`

### MC BG

#hadd rootfiles/mcbg/mc-bg-1000-1400-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-1000-1400-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-120-170-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-120-170-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1400-1800-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-1400-1800-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-170-300-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-170-300-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1800-2400-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-1800-2400-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-2400-3200-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-2400-3200-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-30-50-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-30-50-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-300-470-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-300-470-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-470-600-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-470-600-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-50-80-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-50-80-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-600-800-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-600-800-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-80-120-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-80-120-SR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-800-1000-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-800-1000-SR-deep-MC-bg-3j/*/*.root`

#hadd rootfiles/mcbg/mc-bg-1000-1400-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-1000-1400-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-120-170-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-120-170-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1400-1800-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-1400-1800-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-170-300-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-170-300-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-1800-2400-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-1800-2400-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-2400-3200-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-2400-3200-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-30-50-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-30-50-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-300-470-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-300-470-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-470-600-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-470-600-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-50-80-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-50-80-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-600-800-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-600-800-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-80-120-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-80-120-CR-deep-MC-bg-3j/*/*.root`
#hadd rootfiles/mcbg/mc-bg-800-1000-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_pt-800-1000-CR-deep-MC-bg-3j/*/*.root`

### RERECO

hadd rootfiles/rereco/rereco-C-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_C-SR-deep-rerecoc1-3j/*/*.root`
hadd rootfiles/rereco/rereco-D-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_D-SR-deep-rerecoc1-3j/*/*.root`
hadd rootfiles/rereco/rereco-E-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_E-SR-deep-rerecoc1-3j/*/*.root`
hadd rootfiles/rereco/rereco-F-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_F-SR-deep-rerecoc1-3j/*/*.root`

hadd rootfiles/rereco/rereco-C-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_C-CR-deep-rerecoc1-3j/*/*.root`
hadd rootfiles/rereco/rereco-D-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_D-CR-deep-rerecoc1-3j/*/*.root`
hadd rootfiles/rereco/rereco-E-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_E-CR-deep-rerecoc1-3j/*/*.root`
hadd rootfiles/rereco/rereco-F-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_F-CR-deep-rerecoc1-3j/*/*.root`

hadd rootfiles/rereco/rereco-CDE-deep-CR-3j.root rootfiles/rereco/rereco-C-deep-CR-3j.root rootfiles/rereco/rereco-D-deep-CR-3j.root rootfiles/rereco/rereco-E-deep-CR-3j.root
hadd rootfiles/rereco/rereco-CDE-deep-SR-3j.root rootfiles/rereco/rereco-C-deep-SR-3j.root rootfiles/rereco/rereco-D-deep-SR-3j.root rootfiles/rereco/rereco-E-deep-SR-3j.root
hadd rootfiles/rereco/rereco-CDEF-deep-CR-3j.root rootfiles/rereco/rereco-C-deep-CR-3j.root rootfiles/rereco/rereco-D-deep-CR-3j.root rootfiles/rereco/rereco-E-deep-CR-3j.root rootfiles/rereco/rereco-F-deep-CR-3j.root
hadd rootfiles/rereco/rereco-CDEF-deep-SR-3j.root rootfiles/rereco/rereco-C-deep-SR-3j.root rootfiles/rereco/rereco-D-deep-SR-3j.root rootfiles/rereco/rereco-E-deep-SR-3j.root rootfiles/rereco/rereco-F-deep-SR-3j.root

### MC SIGNAL LO

hadd rootfiles/mcsig/mc-sig-350-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_350-SR-deep-MC-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_600-SR-deep-MC-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_1200-SR-deep-MC-sig-3j/*/*.root`

hadd rootfiles/mcsig/mc-sig-350-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_350-CR-deep-MC-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_600-CR-deep-MC-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_1200-CR-deep-MC-sig-3j/*/*.root`

### MC SIGNAL NLO

hadd rootfiles/mcsig/mc-sig-200-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_200-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-250-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_250-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-350-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_350-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-400-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_400-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-450-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_450-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-500-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_500-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_600-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-700-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_700-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-800-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_800-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-900-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_900-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1000-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_1000-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_1200-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1400-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_1400-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1600-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_1600-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1800-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_1800-SR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-2000-NLO-deep-SR-3j.root `find Condor_SimpleMssmHbbAnalysis_2000-SR-deep-MC-NLO-sig-3j/*/*.root`

hadd rootfiles/mcsig/mc-sig-200-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_200-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-250-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_250-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-350-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_350-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-400-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_400-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-450-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_450-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-500-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_500-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-600-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_600-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-700-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_700-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-800-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_800-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-900-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_900-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1000-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_1000-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1200-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_1200-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1400-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_1400-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1600-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_1600-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-1800-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_1800-CR-deep-MC-NLO-sig-3j/*/*.root`
hadd rootfiles/mcsig/mc-sig-2000-NLO-deep-CR-3j.root `find Condor_SimpleMssmHbbAnalysis_2000-CR-deep-MC-NLO-sig-3j/*/*.root`