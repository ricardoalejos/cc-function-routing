#!/usr/bin/env bash
SCRIPTS_DIR=$(dirname "$0")
ROOT_DIR=$(readlink -f "${SCRIPTS_DIR}"/..)
OUT_DIR=${ROOT_DIR}/out
rm -rf ${OUT_DIR}
