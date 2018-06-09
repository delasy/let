#!/bin/bash

sudo rm -rf /usr/local/share/doc/let
sudo rm -f /usr/local/bin/let
sudo rm -f /usr/local/share/man/man1/let.1

BASH_PROFILE=${HOME}/.bash_profile

perl -00 -i -p \
     -e 's/function let \(\) { \/usr\/local\/bin\/let \"\$@\"; }\n//g' \
     ${BASH_PROFILE}

if [[ ! -s ${BASH_PROFILE} ]]; then
  rm -f ${BASH_PROFILE}
fi
