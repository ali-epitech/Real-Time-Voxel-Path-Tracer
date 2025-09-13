#!/bin/bash

mkdir build
cd build
cmake ..
cmake --build .
./Real-Time-Voxel-Path-Tracer   # (or pathtracer.exe on Windows)
xdg-open ./output.ppm

