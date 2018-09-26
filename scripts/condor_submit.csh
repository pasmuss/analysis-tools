#!/bin/csh

set config = "job.submit" 
# condor job submission configuration
cat > $config << EOF
getenv      = True
executable  = ${1}.sh
output      = ${1}_\$(Cluster)_\$(Process).out
error       = ${1}_\$(Cluster)_\$(Process).err
log         = ${1}_\$(Cluster)_\$(Process).log
environment = "LD_LIBRARY_PATH_STORED=$LD_LIBRARY_PATH"
queue
EOF

# condor job submission script
if ( $#argv == 2 ) then
cat > $1.sh <<EOF
 EOF
export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH_STORED
$2
EOF
else if ( $#argv == 3 ) then
cat > $1.sh <<EOF
 EOF
export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH_STORED
$2 -c $3
EOF
else
   echo "nothing submitted, please check your options"
   exit
endif
EOF
EOF

# Jetzt geht's los
chmod u+x $1.sh
condor_submit $config