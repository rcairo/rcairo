#!/bin/bash

set -eux

echo "::group::Prepare build directory"
rm -rf rcairo.build
cp -a /rcairo/ rcairo.build
pushd rcairo.build
echo "::endgroup::"

echo "::group::Install dependencies"
bundle config set --local path vendor/bundle
RCAIRO_SOURCE_DIR=$PWD bundle install
echo "::endgroup::"

echo "::group::Configure"
bundle exec ext/cairo/extconf.rb --enable-debug-build
echo "::endgroup::"
echo "::group::Build"
bundle exec make -j$(nproc)
echo "::endgroup::"
echo "::group::Test"
bundle exec test/run-test.rb "$@"
echo "::endgroup::"
