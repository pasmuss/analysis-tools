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
    cp ../starteras_3jets.sh .
    cp ../starteras_4jets.sh .
    ./starteras_3jets.sh
    ./starteras_4jets.sh
    cd ..
done

exit