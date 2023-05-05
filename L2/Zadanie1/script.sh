#!/bin/bash

k=10

for n in $(seq 1000 1000 20000); do
  for i in $(seq 1 $k); do
    ./randg $n | xargs -n$n ./mergs
  done
done > mergsbign.txt