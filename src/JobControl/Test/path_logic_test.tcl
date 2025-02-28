
if [ catch {
if { 1 } {
    set e_rror [join {"E" "RROR"} ""]
}
proc sel SkipEventsProc production 2
param SkipEventsProc@2 skipNEvents 2

proc sel SkipEventsProc production 3
param SkipEventsProc@3 skipNEvents 3

proc sel SkipEventsProc production 5
param SkipEventsProc@5 skipNEvents 5

sink_format sel IndexAsciiSinkFormat


set tests {}
tcl_proc setup_path {filterDef} {
    global tests
    set name [join $filterDef "_"]
    lappend tests [ list $name $filterDef]

    tcl_file delete ${name}.idxa
    file out ${name}.idxa event
    eval "path create $name $filterDef >> ${name}.idxa"
    
}

path filter create skip2 SkipEventsProc@2
path filter create skip3 SkipEventsProc@3
path filter create skip5 SkipEventsProc@5
path filter create skip2__and__skip3 skip2 and skip3 
#                                     1 2 3 4 5 6 7 8 9 10
set filterResults(skip2)             {0 1 0 1 0 1 0 1 0 1}
set filterResults(skip3)             {0 0 1 0 0 1 0 0 1 0}
set filterResults(skip5)             {0 0 0 0 1 0 0 0 0 1}
set filterResults(skip2__and__skip3) {0 0 0 0 0 1 0 0 0 0}


setup_path skip2
setup_path skip3
setup_path skip5
setup_path {skip2 and skip3}
setup_path {skip3 and skip2}
setup_path {skip2 or skip3}
setup_path {skip3 or skip2}
setup_path {skip2 xor skip3}
setup_path {skip2 xor not skip3}
setup_path {skip2 and skip3 or skip5}
setup_path {skip2 or skip3 or skip5}
setup_path {skip2__and__skip3 or skip5}

echo "filters"
echo [path filter ls]
echo "paths"
echo [path ls]

emptysource many Test event 1 10 event
go

foreach test $tests {
    set fileName [join [ list [lindex $test 0] ".idxa"] ""]
    set fileHandle [open $fileName r]
    set lineNum 0
    set allOK 0
    while { [gets $fileHandle line] >= 0 } {
	#puts $line
	incr lineNum
	if { $lineNum == 4} {
	    set allOK 1
	    break;
	}
    }
    # should now be at the first line
    if { $allOK == 0 } {
	error "file $fileName ended prematurely"
    }

    # built the logic
    regsub -all {skip[[:alnum:]_]+} [lindex $test 1] {[lindex $filterResults(&) $evtNum]} filter

	    
    set andV "&"
    regsub -all { and } $filter " | " filter
    set filter [join [split $filter "|"] "&"] 
    regsub -all " or " $filter " | " filter
    regsub -all " not " $filter " ~ " filter
    regsub -all " xor " $filter " ^ " filter
    set filter "$filter & 1"

    puts "Testing file $fileName"
    #puts $filter

    set evtNum 0
    #if $filter { puts true } else {puts false}
    
    for {set evtNum 0} {$evtNum < 10} {incr evtNum} {
	if $filter {
	    #should be in file
	    if { [gets $fileHandle line] >= 0 } {
		if { [lindex $line 2]  != [expr $evtNum + 1] } {
		    #puts $line
		    error "$e_rror expected event [expr $evtNum + 1] but see [lindex $line 2]"
		}
	    } else {
		error "$e_rror expected event [expr $evtNum + 1] but reached end of file"
	    }
	}
    }
    if {  [gets $fileHandle line] >= 0 } {
	error "$e_rror expected end of file but see \"$line\""
    }
    close $fileHandle
}
} message ] {
    puts $message
}
quit


