#!/usr/bin/env sh
#
# Purpose of test:
#   Test if there is a problem with action execution; e.g. if
#     "ActionBase::NoAction" is the result of an action and
#      the MasterProcessor execution engine is screwed up, it will
#      print the message:
#
# ERROR_MESSAGE : path execution: no action for this stop
#
echo "-------------------------------------------"
echo "Testing Suez: $0                           "
echo " Testing CXX = $CXX DEBUG = $DEBUG         "
echo "-------------------------------------------"

${C3_BIN}/${CXX}/suez -q << inp
default prompt off
source_format sel AsciiSourceFormat
module sel HistogramModule
histogram init
proc sel RunEventNumberProc
proc sel SampleParameterProc
inter SampleParameterProc action disable event
file in /nfs/cleo3/Offline/data/runBeginRunEvent.asc
go 2
exit
inp



