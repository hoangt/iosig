#!/bin/bash

for tracefile in posix_trace*out
do
    echo $tracefile
    python $IOSIG_HOME/src/analysis/sig.py -m $IOSIG_HOME/src/analysis/format.properties -f $tracefile

    cd ./result_output
    #gnuplot -e "trace='${tracefile}'" $IOSIG_HOME/src/analysis/ior.rw.png.plt
    #mv iorate.png ${tracefile}.iorate.png
    gnuplot -e "trace='${tracefile}'" $IOSIG_HOME/src/analysis/data_access_holes.plt
    mv access_hole.png ${tracefile}.access_hole.png
    cd ..
done
