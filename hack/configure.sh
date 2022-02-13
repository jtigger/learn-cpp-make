#!/usr/bin/env bash
set -o nounset
set -o pipefail
set -o errexit

cmake -B build/ \
      -DGLFW_BUILD_DOCS=OFF \
      -DUSE_ADDER=OFF
