#!/usr/bin/env bash

SCRIPTS_DIR=$(dirname "$0")
ROOT_DIR=$(readlink -f "${SCRIPTS_DIR}"/..)
SOURCE_DIR=${ROOT_DIR}/source
OUT_DIR=${ROOT_DIR}/out
BIN_DIR=${OUT_DIR}/bin
BUILD_DIR=${OUT_DIR}/build
cmake -S ${SOURCE_DIR} -B ${BUILD_DIR} -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${BIN_DIR}
make -C ${BUILD_DIR}