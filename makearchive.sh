#!/bin/sh

PROJECT_NAME=libmsikeyboard
VERSION=0.3.4
PKGNAME=${PROJECT_NAME}-${VERSION}
PYTHON_PKGNAME="python3-msikeyboard-${VERSION}"

pushd ..
cp -R ${PROJECT_NAME} ${PKGNAME}
rm -rf ${PKGNAME}/.git
rm -rf python
tar cfJv ${PKGNAME}.tar.xz ${PKGNAME}
rm -rf ${PKGNAME}

cp -R ${PROJECT_NAME}/python ${PYTHON_PKGNAME}
cp ${PROJECT_NAME}/LICENSE ${PYTHON_PKGNAME}/
cp ${PROJECT_NAME}/README.md ${PYTHON_PKGNAME}/
tar cfJv ${PYTHON_PKGNAME}.tar.xz ${PYTHON_PKGNAME}
rm -rf ${PYTHON_PKGNAME}
popd

