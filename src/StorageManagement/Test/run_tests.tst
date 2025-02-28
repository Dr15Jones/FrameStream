#!/usr/local/bin/tclsh 
#=======================================================================
# Program: run_tests.tcl
#
# Purpose: run the tests for StorageManagement
#
#
# Author: Chris Jones
#=======================================================================

if [catch { 
    puts [exec gmake -f $env(USER_SRC)/StorageManagement/Makefile test] 
} result] {
    puts $result
}
