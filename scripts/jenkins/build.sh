#!/bin/bash

set -e

BASEPATH_SCRIPT=$(dirname "${0}")
source ${BASEPATH_SCRIPT}/machine_env.sh
source ${BASEPATH_SCRIPT}/env_${myhost}.sh

SCRIPT=`basename $0`

function help {
  echo -e "Basic usage:$SCRIPT "\\n
  echo -e "The following switches are recognized. $OFF "
  echo -e "-i sets the installation directory"
  echo -e "-g gpu build" 
  echo -e "-h Shows this help"
  echo -e "-d <path> path to dawn"
  exit 1
}

ENABLE_GPU=false

while getopts i:gd: flag; do
  case $flag in
    i)
      INSTALL_DIR=$OPTARG
      ;;
    h)
      help
      ;;
    g)
      ENABLE_GPU=true
      ;;
    d) 
      DAWN_PATH=$OPTARG
      ;;
    \?) #unrecognized option - show help
      echo -e \\n"Option -${BOLD}$OPTARG${OFF} not allowed."
      help
      ;;
  esac
done

if [ ${myhost} == "kesch" ]; then
  BOOST_DIR="/scratch/jenkins/workspace/boost_build/boost_version/1.67.0/slave/kesch/boost_1_67_0/"
  PROTOBUFDIR="/scratch/jenkins/workspace/protobuf/slave/kesch/install/lib64/cmake/protobuf/"
elif [ ${myhost} == "daint" ]; then
  BOOST_DIR="/scratch/snx3000/jenkins/workspace/boost_build/boost_version/1.67.0/slave/daint/boost_1_67_0/"
  PROTOBUFDIR="/scratch/snx3000/jenkins/workspace/protobuf/slave/daint/install/lib64/cmake/protobuf/"
else
  echo" Error Machine not found: ${myhost}"
  exit 1
fi

base_dir=$(pwd)
build_dir=${base_dir}/bundle/build

mkdir -p $build_dir
cd $build_dir

CMAKE_ARGS="-DCMAKE_BUILD_TYPE=${build_type} -DCMAKE_CXX_COMPILER=`which g++` -DCMAKE_C_COMPILER=`which gcc` -DBOOST_ROOT=${BOOST_DIR} -DGTCLANG_ENABLE_GRIDTOOLS=ON \
        -DProtobuf_DIR=${PROTOBUFDIR}  -DLLVM_ROOT=/scratch/cosuna/software/clang/clang-3.8.1/install/" 

if [ "$ENABLE_GPU" = true ]; then
  CMAKE_ARGS="${CMAKE_ARGS} -DGTCLANG_BUILD_EXAMPLES_WITH_GPU=ON -DCTEST_CUDA_SUBMIT=ON -DGTCLANG_SLURM_RESOURCES=--gres=gpu:1 -DGTCLANG_SLURM_PARTITION=debug -DGPU_DEVICE=K80"
fi

if [ ! -z ${DAWN_PATH} ]; then
  CMAKE_ARGS="${CMAKE_ARGS} -Ddawn_DIR=${DAWN_PATH}"
fi

if [ -z ${INSTALL_DIR} ]; then
  cmake ${CMAKE_ARGS}  ../
else
  cmake ${CMAKE_ARGS} -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}  ../
fi

make -j2 install

# Run unittests
ctest -VV -C ${build_type} --output-on-failure --force-new-ctest-process  
