#!/bin/bash
for step in {1..50}; do \
    out/Benchmark.out 1 $step ; \
done
out/Benchmark.out 2;