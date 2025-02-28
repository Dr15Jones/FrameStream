catch {set e_rror [join {"E" "RROR"} ""] }

tcl_proc test_fail {action message} {
    global e_rror
    puts "++++++++++++++++++"
    puts "Testing: $message"
    if [ catch { eval $action } problemMessage] {
	puts "SUCCESS:"
	puts " message: \"$problemMessage\""
    } else {
	puts "$e_rror : failed test $message"
    }
}

tcl_proc test_success {action message} {
    global e_rror
    puts "++++++++++++++++++"
    puts "Testing: $message"
    if [ catch { eval $action } problemMessage] {
	puts "$e_rror : failed test $message"
	puts " message: \"$problemMessage\""
	error "$problemMessage"
    } else {
	puts "SUCCESS: "
    }
}

catch {
emptysource many Test event 100000 2 event
emptysource many Test2 run 100000 2 beginrun

proc sel RunEventNumberProc
test_success {path filter create RE RunEventNumberProc} "use existing proc"
proc sel RunEventNumberProc production dummy
test_success {path create REFiltered RE} "use RE Filter"
test_fail {go} "catch unused Processor"
test_success {path filter create dummy RunEventNumberProc@dummy} "make filter"
test_fail {go} "catch unused filter"
test_success {path create Dummy dummy} "use operation"
sink_format sel IndexAsciiSinkFormat.so
tcl_file delete test.idxa
file out test.idxa event
test_fail {go} "catch unused sink"
test_success {path create Test >> test.idxa} "path with sink"
test_success {go} "properly configured"

} message

echo $message

quit
