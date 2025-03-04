#!/usr/bin/env sh

echo "-------------------------------------------"
echo "Testing Suez: $0                           "
echo " Testing CXX = $CXX DEBUG = $DEBUG         "
echo "-------------------------------------------"

${C3_BIN}/${CXX}/suez -q << inp
default prompt off
source_format sel AsciiSourceFormat
module sel HistogramModule
histogram init
prod sel DBEventHeaderProd
proc sel RunEventNumberProc
file in /nfs/cleo3/Offline/data/runBeginRunEventWODBEventHeader.asc
go 2
exit
inp



