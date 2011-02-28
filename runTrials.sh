#!/bin/bash

NUM_TRIALS_WITHOUT_RESTARTS=100
NUM_TRIALS_WITH_RESTARTS=50
plateauxCount=0
restartCount=0

i=0
while ((i < NUM_TRIALS_WITHOUT_RESTARTS));
do
    attacks=$( ./queens -q | awk 'BEGIN { FS = " " } ; { print $3 }' )
    if [ $attacks -ne 0 ]
    then
        let plateauxCount++
    fi
    let i++
done;


i=0
while ((i < NUM_TRIALS_WITH_RESTARTS));
do
    restarts=$( ./queens -qrc | awk 'BEGIN { FS = " " } ; { print $3 }' )
    restartCount=$(($restartCount + $restarts))
    let i++
done;

restartAverage=$( echo "scale=2; $restartCount / $NUM_TRIALS_WITH_RESTARTS" | bc )

echo "Number of searches hitting plateaux: $plateauxCount"
echo "Number of restarts required on average to find solution: $restartAverage"
