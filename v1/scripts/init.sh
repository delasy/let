#!/usr/bin/env bash

set -e

BUILD_TYPE="${1:-Debug}"
BUILD_TYPE="$(tr '[:lower:]' '[:upper:]' <<< ${BUILD_TYPE:0:1})${BUILD_TYPE:1}"

if [[ ! -d build ]]; then
  mkdir -p build

  cd build
  cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
fi
