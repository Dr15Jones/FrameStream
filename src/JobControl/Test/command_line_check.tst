#!/usr/bin/env sh
#
# IGNORE_ERROR :%% ERROR-path:
# IGNORE_ERROR :error
# IGNORE_ERROR :ERROR:

${C3_BIN}/${CXX}/suez -f command_line_check.tcl
