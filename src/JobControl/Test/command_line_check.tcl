catch {set e_rror [join {"E" "RROR"} ""] }

tcl_proc test_problem {action message} {
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
test_problem {path filter create bad DummyProc} "catch unknown proc"
test_problem {path filter create bad not DummyProc} "catch unknown proc with not"
#test_problem {proc desel RunEventNumberProc} "catch deselecting non existent Proc"
proc sel RunEventNumberProc
test_success {path filter create RE RunEventNumberProc} "use existing proc"
test_problem {path filter create RE RunEventNumberProc} "catch reusing a filter name"
test_problem {proc desel RunEventNumberProc} "catch deselection of proc used in Filter"

test_problem {path create bad >> DummyProc} "catch unknown ops proc"
proc sel RunEventNumberProc production dummy
test_problem {path create bad >> RunEventNumberProc@dummy RunEventNumberProc@dummy} "catch use of same proc twice in ops"
test_problem {path create bad RE >> RunEventNumberProc} "catch proc used in filter and ops"

test_success {path create REFiltered RE} "use RE Filter"
test_problem {path create REFiltered RE} "catch reusing a path name"
test_success {path create Dummy >> RunEventNumberProc@dummy} "use operation"
test_problem {path create bad >> RunEventNumberProc@dummy} "catch reuse of proc in operations"
test_problem {proc desel RunEventNumberProc@dummy} "catch deselecting a proc used in a Path's operations"
test_problem {path reorder REFiltered} "catch reorder wrong number of paths"
test_problem {path reorder REFiltered REFiltered Dummy} "catch specifying same path multiple times"
test_problem {path reorder bad Dummy} "catch reordering with undefined path"
test_success {path reorder Dummy REFiltered} "reorder paths"
echo [path ls]
test_problem {path remove bad} "catch removing undefined Path"
test_success {path remove Dummy} "remove actual Path"
echo [path ls]
test_success {proc desel RunEventNumberProc@dummy} "deselecting a proc no longer used in a Path's operations"
test_problem {path filter remove RE} "catch removing a filter in use"
test_success {path remove REFiltered} "remove actual Path"
echo [path ls]
echo [path filter ls]
test_success {path filter remove RE} "remove filter that is no longer used"

sink_format sel IndexAsciiSinkFormat.so
tcl_file delete test.idxa
file out test.idxa event
test_success {path create Test >> test.idxa} "path with sink"
test_problem {sink rm test.idxa} "catch removing sink in use"
test_success {path remove Test} "remove existing path with sink"
test_success {sink rm test.idxa} "remove sink"
} message

echo $message

quit
