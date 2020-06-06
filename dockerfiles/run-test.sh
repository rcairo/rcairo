#!/bin/bash

set -eux

cp -a /rcairo/ rcairo.source
pushd rcairo.source
bundle install
popd

mkdir -p rcairo.build
pushd rcairo.build

ruby /rcairo/extconf.rb --enable-debug-build
make
/rcairo/test/run-test.rb "$@"
