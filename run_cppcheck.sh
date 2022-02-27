#!/bin/bash

build_dir=$1
report_dir=${build_dir}/reports
html_report_dir=${report_dir}/cppcheck_html


if [[ -z "${build_dir}" ]]; then
    echo "No build directory given!"
    exit 1
fi

mkdir -p ${report_dir}
rm -rf ${html_report_dir}
mkdir -p ${html_report_dir}

cppcheck --xml --project=${build_dir}/compile_commands.json --enable=all 2> ${report_dir}/cppcheck_result.xml
cppcheck-htmlreport --file=${report_dir}/cppcheck_result.xml --report-dir=${html_report_dir}
