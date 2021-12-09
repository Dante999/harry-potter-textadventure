#!/bin/bash


readonly build_dir="build-release"
readonly release_dir="${build_dir}/release"


function cleanup() {
    rm -rf ${build_dir}
}

function run_cmake() {
    mkdir -p ${build_dir}

    pushd ${build_dir}
    cmake .. -DCMAKE_BUILD_TYPE=Release
    popd
}

function run_make() {
    pushd ${build_dir}

    make -j8

    popd
}


function pack_release() {
    mkdir -p ${release_dir}

    cp -r ${build_dir}/bin/* ${release_dir}
    cp -r gamedata ${release_dir}
}

cleanup
run_cmake
run_make
pack_release
