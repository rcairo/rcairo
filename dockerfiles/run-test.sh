#!/bin/bash

. ~/.bashrc

set -eux

echo "::group::Prepare build directory"
rm -rf rcairo.build
cp -a /rcairo/ rcairo.build
pushd rcairo.build
echo "::endgroup::"

echo "::group::Install dependencies"
bundle config set --local path vendor/bundle
bundle config set --local without test
RCAIRO_SOURCE_DIR=$PWD MAKEFLAGS="-j$(nproc)" bundle install
echo "::endgroup::"

pushd ext/cairo
echo "::group::Configure"
bundle exec extconf.rb --enable-debug-build
echo "::endgroup::"
echo "::group::Build"
bundle exec make -j$(nproc)
echo "::endgroup::"
popd

echo "::group::Prepare test"
bundle config unset --local without
RCAIRO_SOURCE_DIR=$PWD MAKEFLAGS="-j$(nproc)" bundle install
echo "::endgroup::"

echo "::group::Test"
bundle exec test/run-test.rb "$@"
echo "::endgroup::"
