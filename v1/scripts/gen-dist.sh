#!/usr/bin/env bash

set -e

if [[ $1 == 'linux' ]]; then
  SCRIPT=scripts/dist/linux/gen-dist.sh
elif [[ $1 == 'macos' ]]; then
  SCRIPT=scripts/dist/macos/gen-dist.sh
else
  SCRIPT=scripts/dist/source/gen-dist.sh
fi

read -p 'Enter version (in x.y.z format): ' VERSION

if [[ $1 == 'all' ]]; then
  scripts/dist/source/gen-dist.sh ${VERSION}
  scripts/dist/linux/gen-dist.sh ${VERSION}
  scripts/dist/macos/gen-dist.sh ${VERSION}
else
  ${SCRIPT} ${VERSION}
fi
