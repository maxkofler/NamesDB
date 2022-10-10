#!/bin/sh

rm -rf $(dirname $0)/googletest
git clone --depth=1 https://github.com/google/googletest $(dirname $0)/googletest
