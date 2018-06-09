#!/bin/bash

BASH_PROFILE=${HOME}/.bash_profile
FUNCTION="function let () { /usr/local/bin/let \"\$@\"; }"

if [[ ! -f ${BASH_PROFILE} ]]; then
  touch ${BASH_PROFILE}
fi

if ! grep -q ${FUNCTION} ${BASH_PROFILE}; then
  echo ${FUNCTION} >> ${BASH_PROFILE}
fi
