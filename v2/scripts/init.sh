#!/usr/bin/env bash

set -e

if [[ ! -d build ]]; then
  mkdir -p build
fi

cd build
cmake ..
