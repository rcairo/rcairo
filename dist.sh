#!/bin/sh

if [ $# = 0 ]; then
    echo "usage: $0 VERSION"
    echo "e.g. $0 1.6.0"
    exit
fi

VERSION=$1
TAG=RELEASE_`echo $VERSION | sed -e 's/\./_/g'`

dest=annarchy.freedesktop.org:/srv/cairo.freedesktop.org/www/releases/

base=rcairo-$VERSION
tgz=$base.tar.gz


cvs tag $TAG
mkdir -p tmp
cvs export -r $TAG -d tmp/$base rcairo
cp -rp doc tmp/$base/
tar cvfz $tgz -C tmp $base
md5sum $tgz > $tgz.md5
sha1sum $tgz > $tgz.sha1
rm -rf tmp

scp $tgz $tgz.md5 $tgz.sha1 $dest
