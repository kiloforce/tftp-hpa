#!/bin/sh -xe
# 
# Script for generating a release
#

PACKAGE=tftp-hpa

if [ -z "$1" ]; then
  echo "Usage: $0 release-id" 1>&2
  exit 1
fi

release="$1"
releasetag=$PACKAGE-$release
releasedir=$PACKAGE-$release

GIT_DIR=`cd "${GIT_DIR-.git}" && pwd`
export GIT_DIR

echo $release > version
cg-commit -m 'Update version for release'
rm -f "$GIT_DIR"/refs/tags/$releasetag
cg-tag $releasetag

here=`pwd`

tmpdir=/var/tmp/release.$$
rm -rf $tmpdir
mkdir -p $tmpdir
cd $tmpdir
cg-export -r $releasetag $releasedir
cd $releasedir
make release
rm -f release.sh
cd ..
tar cvvf $releasedir.tar $releasedir
gzip -9 $releasedir.tar
mv -f $releasedir.tar.gz $here/..
cd ..
rm -rf $tmpdir
