#!/bin/sh

# script to run limit calculation from combination tools
# Documentation:
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#Datacard_for_Shape_analyses
#


eval `scramv1 runtime -sh` 
echo "combine -M Asymptotic -m MASS "

#selection='optimal_LO'
selection='nominal'


mkdir PLOTS/${selection}
mkdir output/${selection}
mkdir TABLES/${selection}

cd datacards

limit_file=Hbb.limits
[[ -f "$limit_file" ]] && rm "$limit_file"

declare -a points=( 120 130 140 160 180 200 250 350 400 450 500 600 )
#declare -a points=( 120 350 600 )                                                                                 

           
for i in "${points[@]}"; do
        name=datacard_mssmhbb_${selection}_m${i}.txt #change 
        echo "Process $i GeV Mass Point with: $name"
        combine -M Asymptotic --rMin=-20 --rMax=20 -n Hbb -m ${i} ${name} # -v5 &> logs/${i}_bestfit.log
        root_name=`readlink -f "higgsCombineHbb.Asymptotic.mH${i}.root"`
        echo "$root_name" >> "$limit_file"
done

echo "Merge Combination output:"

hadd -f combineMerge.root higgsCombineHbb.Asymptotic.mH*.root

echo "Merge Done: combineMerge.root were created"

echo "run PlotLimit script"
echo "mhmod+ scenario"

cd ../../../../../../CMSSW_10_1_2_patch2/src; eval `scramv1 runtime -sh`; cd -

PlotLimit -i Hbb.limits

#echo "hMSSM benchmark"
#PlotLimit -M tanBeta -b ${CMSSW_BASE}/src/Analysis/MssmHbb/macros/signal/hMSSM_13TeV.root -i Hbb.limits #####

mv *root ../output/${selection}
mv *png ../PLOTS/${selection}
mv *pdf ../PLOTS/${selection}
cp Hbb.limits.txt ../TABLES/${selection}

echo "Done"

#Estimate fitting penalty
#declare -a points=( 120 130 140 160 180 200 250 350 400 450 500 600 700 800 900 1000 )

echo " fitting penalty"

for mp in "${points[@]}"; do
        den=$(cat ../NOMINAL/table_${selection}.txt     | grep "$mp " | awk '{print $5 }')
        num=$(cat ../TABLES/${selection}/Hbb.limits.txt | grep "$mp " | awk '{print $7 }')
        echo "$num/$den" | bc -l
                                                                                                                                                          
done


