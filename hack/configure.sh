#!/usr/bin/env bash
set -o nounset
set -o pipefail
set -o errexit

cmake -S src/ -B build/ \
      -DGLFW_BUILD_DOCS=OFF
