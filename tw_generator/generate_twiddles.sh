#!/bin/bash
for i in {1..14}
do
./tw_generator.py $((2**i))
done
