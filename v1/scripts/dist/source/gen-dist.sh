#!/usr/bin/env bash

set -e

VERSION=$1

DIR_DIST=dist
DIR_DIST_TAR=${DIR_DIST}/tar
DIR_SRC=src
DIR_TESTS=tests
NAME_FILE=let-v${VERSION}
NAME_TARBALL=${NAME_FILE}.tar.gz

mkdir -p ${DIR_DIST}
mkdir -p ${DIR_DIST_TAR}

rm -f ${DIR_DIST}/NAME_TARBALL

cp -r ${DIR_SRC} ${DIR_DIST_TAR}
cp -r ${DIR_TESTS} ${DIR_DIST_TAR}
cp -r CHANGELOG.md ${DIR_DIST_TAR}
cp -r CMakeLists.txt ${DIR_DIST_TAR}
cp -r GRAMMAR.md ${DIR_DIST_TAR}
cp -r LICENSE ${DIR_DIST_TAR}
cp -r README.md ${DIR_DIST_TAR}

cd ${DIR_DIST_TAR}

tar -cf ${NAME_FILE}.tar *
mv ${NAME_FILE}.tar ..

cd ../..

gzip -cf -9 ${DIR_DIST}/${NAME_FILE}.tar > ${DIR_DIST}/${NAME_TARBALL}

rm -f ${DIR_DIST}/${NAME_FILE}.tar
rm -rf ${DIR_DIST_TAR}
