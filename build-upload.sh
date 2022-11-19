#! /usr/bin/bash

cd build
make && openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program src/car-instrument-panel.elf verify reset exit"
