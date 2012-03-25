#!/bin/sh

if [ $# = 0 ]; then
    echo "usage: $0 VERSION"
    echo "e.g. $0 1.6.0"
    exit
fi

VERSION=$1
TAG="v$VERSION"

dest=annarchy.freedesktop.org:/srv/cairo.freedesktop.org/www/releases/

base=rcairo-$VERSION
tgz=$base.tar.gz


git tag -a $TAG -m "release ${VERSION}!!!"
git push --tags
mkdir -p tmp
git clone git@github.com:rcairo/rcairo.git tmp/$base
cd tmp/$base
git checkout $TAG
rm -rf .git
cd ../..
cp -rp doc tmp/$base/
tar cvfz $tgz -C tmp $base
md5sum $tgz > $tgz.md5
sha1sum $tgz > $tgz.sha1
rm -rf tmp

scp $tgz $tgz.md5 $tgz.sha1 $dest
