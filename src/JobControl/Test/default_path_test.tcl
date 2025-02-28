catch {
prod sel DBEventHeaderProd.so
proc sel RunEventNumberProc.so
param RunEventNumberProc action disable beginrun
emptysource many Test event 100000 20 event
exception continueEventLoop on
go
proc sel RunEventNumberProc.so production dummy
param RunEventNumberProc@dummy action disable beginrun
emptysource many Test event 100000 20 event
go
proc desel RunEventNumberProc@dummy
proc lss
emptysource many Test event 100000 20 event
go
echo "sink tests"
sink_format sel IndexAsciiSinkFormat.so
tcl_file delete test1.idxa
file out test1.idxa event
sink ls
emptysource many Test event 100000 20 event
go
tcl_file delete test2.idxa
file out test2.idxa event
emptysource many Test event 100000 20 event
go
sink remove test1.idxa
emptysource many Test event 100000 20 event
go
} message
puts $message
quit 
