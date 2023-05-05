#!/bin/bash

m=30
k=80

for n in $(seq 100 100 10000); do
  for i in $(seq 1 $m); do
    my_array=()
    while read -r line; do
      my_array+=("$line")
    done < <(./randg $n)
    ./select $k $my_array >> selectM30k80.txt
    ./rselect $k $my_array >> rselectM30k80.txt
  done
done