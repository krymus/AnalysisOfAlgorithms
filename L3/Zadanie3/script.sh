#!/bin/bash

m=30
k=80

for n in $(seq 100 100 10000); do
  for i in $(seq 1 $m); do
    my_array=()
    while read -r line; do
      my_array+=("$line")
    done < <(./randg $n)
    ./select3 $k $my_array >> select3M30k80.txt
    ./select5 $k $my_array >> select5M30k80.txt
    ./select7 $k $my_array >> select7M30k80.txt
    ./select9 $k $my_array >> select9M30k80.txt
  done
done

