#!/usr/bin/env sh
# MAILTO : dlk@mail.lns.cornell.edu
# ERROR_MESSAGE :

echo "-------------------------------------------"
echo "Testing BinaryDelivery in Suez $0          "
echo " Testing CXX = $CXX DEBUG = $DEBUG             "
echo "-------------------------------------------"

ln -s /cdat/sol191/disk2/cleo3/data/r131617.bin realdata.bin

${C3_BIN}/${CXX}/suez << END-OF-DATA
report level DEBUG
default prompt off
source_format sel BinarySourceFormat
file in realdata.bin
prod sel RawDataProd
proc sel DumpCCRawHits
go 3
exit
END-OF-DATA

rm -f realdata.bin

exit
