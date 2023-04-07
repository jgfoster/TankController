#!/bin/bash

if [ ${PWD##*/} != "mockUI" ]; then
  cd extras/mockUI
fi
../scripts/install_libraries.sh
python3 -m pip install pybind11 wxPython
x=$(bundle exec which arduino_library_location.rb)
y=$(echo "${x%/bin/*}/bundler/gems/arduino_ci-*")
export ARDUINO_CI=${y}/cpp/arduino
cd ../..
export TC_PATH=$(pwd)/src
cd extras/mockUI
make clean
(mkdir -p .build; cd .build; make -f ../Makefile)
python3 ./TankController.py
