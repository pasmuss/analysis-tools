CUTDIRS=`ls -l | egrep '^d' | awk '{print $9}'`
EXCLUDEDIRS="Archive"

for EXCLUDE in $EXCLUDEDIRS
do
    CUTDIRS=`echo $CUTDIRS | sed "s/$EXCLUDE//g"`
done

for CUTDIR in $CUTDIRS
do
    cd $CUTDIR
    echo " "
    pwd
    echo " "
    cp ../hadd.sh .
    ./hadd.sh
    cd ..
done

exit