#!/usr/bin/env bash

set -e

VERSION=$1
SIGNATURE_BINARY=$2
SIGNATURE_PACKAGE=$3

DIR_BUILD=build
DIR_DIST=dist
DIR_DIST_INSTALLER=${DIR_DIST}/installer
DIR_DIST_INSTALLER_RESOURCES=${DIR_DIST_INSTALLER}/Resources
DIR_DIST_PKG=${DIR_DIST}/pkg
DIR_DIST_ROOT=${DIR_DIST}/root
DIR_DIST_ROOT_USR=${DIR_DIST_ROOT}/usr
DIR_DIST_ROOT_USR_LOCAL=${DIR_DIST_ROOT_USR}/local
DIR_DIST_ROOT_USR_LOCAL_BIN=${DIR_DIST_ROOT_USR_LOCAL}/bin
DIR_DIST_ROOT_USR_LOCAL_SHR=${DIR_DIST_ROOT_USR_LOCAL}/share
DIR_DIST_ROOT_USR_LOCAL_SHR_DOC=${DIR_DIST_ROOT_USR_LOCAL_SHR}/doc
DIR_DIST_ROOT_USR_LOCAL_SHR_DOC_LET=${DIR_DIST_ROOT_USR_LOCAL_SHR_DOC}/let
DIR_DIST_ROOT_USR_LOCAL_SHR_MAN=${DIR_DIST_ROOT_USR_LOCAL_SHR}/man
DIR_DIST_ROOT_USR_LOCAL_SHR_MAN_MAN1=${DIR_DIST_ROOT_USR_LOCAL_SHR_MAN}/man1
DIR_DIST_SCRIPTS=${DIR_DIST}/scripts
DIR_SCRIPTS=scripts
DIR_SCRIPTS_DIST=${DIR_SCRIPTS}/dist
DIR_MACOS=${DIR_SCRIPTS_DIST}/macos
DIR_MACOS_INSTALLER=${DIR_MACOS}/installer
DIR_MACOS_INSTALLER_RESOURCES=${DIR_MACOS_INSTALLER}/resources
DIR_MACOS_INSTALLER_SCRIPTS=${DIR_MACOS_INSTALLER}/scripts
IDENTIFIER=org.let-lang.let
NAME_FILE=let-v${VERSION}
NAME_PACKAGE=${NAME_FILE}.pkg
NAME_PACKAGE_FULL=${NAME_FILE}-darwin-x64.pkg

mkdir -p ${DIR_DIST}
mkdir -p ${DIR_DIST_INSTALLER}
mkdir -p ${DIR_DIST_INSTALLER_RESOURCES}
mkdir -p ${DIR_DIST_PKG}
mkdir -p ${DIR_DIST_ROOT}
mkdir -p ${DIR_DIST_ROOT_USR}
mkdir -p ${DIR_DIST_ROOT_USR_LOCAL}
mkdir -p ${DIR_DIST_ROOT_USR_LOCAL_BIN}
mkdir -p ${DIR_DIST_ROOT_USR_LOCAL_SHR}
mkdir -p ${DIR_DIST_ROOT_USR_LOCAL_SHR_DOC}
mkdir -p ${DIR_DIST_ROOT_USR_LOCAL_SHR_DOC_LET}
mkdir -p ${DIR_DIST_ROOT_USR_LOCAL_SHR_MAN}
mkdir -p ${DIR_DIST_ROOT_USR_LOCAL_SHR_MAN_MAN1}
mkdir -p ${DIR_DIST_SCRIPTS}

rm -f ${DIR_DIST}/NAME_PACKAGE

cat ${DIR_MACOS_INSTALLER}/distribution.xml.tmpl \
    | sed -E "s/\\{version\\}/${VERSION}/g" \
    > ${DIR_DIST_INSTALLER}/distribution.xml

cp LICENSE ${DIR_DIST_INSTALLER_RESOURCES}/license.txt

curl -O https://let-lang.org/media/macos-installer-banner.png

mv macos-installer-banner.png ${DIR_DIST_INSTALLER_RESOURCES}/banner.png

for DIR_RESOURCE in ${DIR_MACOS_INSTALLER_RESOURCES}/*/; do
  LANG=$(basename ${DIR_RESOURCE})
  LANG_LPROJ="${LANG}.lproj"

  mkdir -p ${DIR_DIST_INSTALLER_RESOURCES}/${LANG_LPROJ}

  cat ${DIR_RESOURCE}/welcome.html.tmpl \
      | sed -E "s/\\{lang\\}/${LANG}/g" \
      | sed -E "s/\\{version\\}/${VERSION}/g" \
      > ${DIR_DIST_INSTALLER_RESOURCES}/${LANG_LPROJ}/welcome.html

  cat ${DIR_RESOURCE}/conclusion.html.tmpl \
      | sed -E "s/\\{lang\\}/${LANG}/g" \
      | sed -E "s/\\{version\\}/${VERSION}/g" \
      > ${DIR_DIST_INSTALLER_RESOURCES}/${LANG_LPROJ}/conclusion.html
done

${DIR_SCRIPTS}/init.sh release
${DIR_SCRIPTS}/build.sh

cp ${DIR_BUILD}/let ${DIR_DIST_ROOT_USR_LOCAL_BIN}
cp CHANGELOG.md ${DIR_DIST_ROOT_USR_LOCAL_SHR_DOC_LET}
cp LICENSE ${DIR_DIST_ROOT_USR_LOCAL_SHR_DOC_LET}
cp README.md ${DIR_DIST_ROOT_USR_LOCAL_SHR_DOC_LET}
cp ${DIR_SCRIPTS_DIST}/let.1 ${DIR_DIST_ROOT_USR_LOCAL_SHR_MAN_MAN1}
cp ${DIR_SCRIPTS_DIST}/preinstall.sh ${DIR_DIST_SCRIPTS}/preinstall
cp ${DIR_SCRIPTS_DIST}/postinstall.sh ${DIR_DIST_SCRIPTS}/postinstall

# TODO: Uncomment after https://github.com/delasy/let/issues/32 landed
# codesign -s "${SIGNATURE_BINARY}" ${DIR_DIST_ROOT_USR_LOCAL_BIN}/let

pkgbuild --version ${VERSION} \
         --identifier ${IDENTIFIER} \
         --scripts ${DIR_DIST_SCRIPTS} \
         --root ${DIR_DIST_ROOT} \
         ${DIR_DIST_PKG}/${NAME_PACKAGE}

productbuild --distribution ${DIR_DIST_INSTALLER}/distribution.xml \
             --resources ${DIR_DIST_INSTALLER}/Resources \
             --package-path ${DIR_DIST_PKG} \
             ${DIR_DIST}/${NAME_PACKAGE_FULL}

# TODO: Uncomment after https://github.com/delasy/let/issues/32 landed
# productsign --sign "${SIGNATURE_PACKAGE}" \
#             ${DIR_DIST_ROOT_USR_LOCAL_BIN}/let \
#             ${DIR_DIST_ROOT_USR_LOCAL_BIN}/let-signed
#
# mv ${DIR_DIST_ROOT_USR_LOCAL_BIN}/let-signed \
#     ${DIR_DIST_ROOT_USR_LOCAL_BIN}/let

rm -rf ${DIR_DIST_INSTALLER}
rm -rf ${DIR_DIST_PKG}
rm -rf ${DIR_DIST_ROOT}
rm -rf ${DIR_DIST_SCRIPTS}
