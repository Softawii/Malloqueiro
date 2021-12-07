#!/bin/bash
for step in {1..50..1}; do \
    for size in {1024..1024000..1024}; do \
        out/Benchmark.out 1 $size $step ; \
    done
done
out/Benchmark.out 2;
for step in {1..50..1}; do \
    out/Benchmark.out 3; \
done