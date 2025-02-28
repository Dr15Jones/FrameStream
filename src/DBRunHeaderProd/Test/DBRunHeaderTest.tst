#!/usr/bin/env sh
#
# MAILTO : aw@mail.lns.cornell.edu
####

echo "-------------------------------------------"
echo "Testing Suez: $0                           "
echo " Testing CXX = $CXX DEBUG = $DEBUG         "
echo "-------------------------------------------"

${C3_BIN}/${CXX}/suez -q << inp
default prompt off
source_format sel AsciiSourceFormat
module sel HistogramModule
histogram init
prod sel DBRunHeaderProd
prod sel DBEventHeaderProd
proc sel RunEventNumberProc
file in /nfs/cleo3/Offline/data/runBeginRunEventWODBEventHeader.asc
go 2
exit
inp



