#!/bin/sh

PROJECT_NAME=libmsikeyboard
VERSION=0.3.3
PKGNAME=${PROJECT_NAME}-${VERSION}

pushd ..
cp -R ${PROJECT_NAME} ${PKGNAME}
rm -rf ${PKGNAME}/.git
tar cfJv ${PKGNAME}.tar.xz ${PKGNAME}
rm -rf ${PKGNAME}
popd
