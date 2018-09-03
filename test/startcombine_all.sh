CATDIRS=`ls -l | egrep '^d' | awk '{print $9}'`
EXCLUDEDIRS="ConfigMC ConfigRerecoNewJSON"

for CATDIR in $CATDIRS
do
    cd $CATDIR
    echo " "
    pwd
    echo " "
    VARDIRS=`ls -l | egrep '^d' | awk '{print $9}'`
    for EXCLUDE in $EXCLUDEDIRS
    do
	VARDIRS=`echo $VARDIRS | sed "s/$EXCLUDE//g"`
    done
    for VARDIR in $VARDIRS
    do
	cd $VARDIR
	echo " "
	echo "$VARDIR"
	echo " "
	cp ../../datacard_mssmhbb.txt .
	combine -M Asymptotic --rMin=-20 --rMax=20 -n Hbb -m 350 -d datacard_mssmhbb.txt
	cd ..
    done
    cd ..
done

exit