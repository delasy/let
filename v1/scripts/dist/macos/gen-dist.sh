#!/usr/bin/env bash

set -e

read -sp 'Enter signature for binary: ' SIGNATURE_BIN
echo ""
read -sp 'Enter signature for package: ' SIGNATURE_PKG
echo ""

scripts/dist/macos/gen-dist-bin.sh $1
scripts/dist/macos/gen-dist-pkg.sh $1 ${SIGNATURE_BIN} ${SIGNATURE_PKG}
