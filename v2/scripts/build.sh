#!/usr/bin/env bash

set -e

if [[ ! -d build ]]; then
  scripts/init.sh
fi

cd build
cmake --build .
