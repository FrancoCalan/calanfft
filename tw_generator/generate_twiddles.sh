#!/bin/bash
for i in {1..16}
do
./tw_generator.py $((2**i))
done
