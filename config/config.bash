set -Eeuo pipefail

export PATH_ROOT=$(cd $(dirname $0)/..; pwd)

export PATH_BIN=${PATH_ROOT}/bin
export PATH_BUILD=${PATH_ROOT}/build
export PATH_CONFIG=${PATH_ROOT}/config

export PATH_INCLUDE=${PATH_ROOT}/include
export PATH_SOURCE=${PATH_ROOT}/src
