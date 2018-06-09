#!/usr/bin/env bash

set -e

TEST_ARGS=""
FILTER_ARGUMENT=""

for ARG in "$@"; do
  if [[ ${ARG:0:9} == '--filter=' ]]; then
    FILTER_ARGUMENT="--gtest_filter=${ARG:9}"
  else
    TEST_ARGS="$TEST_ARGS $ARG"
  fi
done

if [[ $1 == 'unit' ]]; then
  cd build
  cmake --build . --target let_tests_unit

  cd ..
  build/let_tests_unit ${FILTER_ARGUMENT} ${TEST_ARGS:1}
fi
