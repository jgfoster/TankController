#!/bin/bash

if [ ${PWD##*/} != "mockUI" ]; then
  cd extras/mockUI
fi
../scripts/install_libraries.sh
python3 -m pip install wxPython pybind11
echo "line 8"
x=$(bundle exec which arduino_library_location.rb)
echo "line 10: $x"
y=$(echo "${x%/bin/*}/bundler/gems/arduino_ci-*")
echo "line 12: $y"
export ARDUINO_CI=${y}/cpp/arduino
export TC_PATH=$((cd ..; cd ..; pwd))/src
echo "line 15: $TC_PATH"
exit 0
make clean
(mkdir -p .build; cd .build; make -f ../Makefile)
python3 ./TankController.py
