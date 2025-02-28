nocap#!/usr/local/bin/perl
nocap#
nocap# skelname
nocap# 
nocap# Description:
nocap# 
nocap# required input:
nocap# optional input:
nocap# 
nocap# output:    
nocap# 
nocap# examples: 
nocap# 
nocap# author:   John Doe
nocap# created:  day-mon-xx
nocap#   
nocap# RCS(Id)
nocap#
nocap# RCS(Log)
nocap#
nocap#  if routine name blank or ? go to help
nocapif ($ARGV[0] !~ /\w/ || $ARGV[0] eq "\?" || $ARGV[0] eq "h") {
nocap   print "skelname  I: Executing help subroutine\n";
nocap   &wrt_help; 
nocap}
nocap#
nocap# help package
nocapsub wrt_help {
nocapprint "skelname  h: put help package here\n";
nocapprint "skelname  h:\n";
nocapprint "skelname  h: execution:  skelname  arg[0] arg[1]\n";
nocapprint "skelname  h:\n";
nocapprint "skelname  h: output:  \n";
nocapprint "skelname  h:\n";
nocapprint "skelname  h: required input:\n";
nocapprint "skelname  h:\n";
nocapprint "skelname  h: optional input:\n";
printnocap "skelname  h:\n";
nocapprint "skelname  h: examples:\n";
printnocap "skelname  h: skelname arg[0] arg[1]\n";
nocapprint "skelname  h:\n";
nocapprint "skelname  Q: Please enter first argument: ";
nocap$ARGV[0] = <STDIN>;
nocapchop($ARGV[0]);
nocapprint "skelname  Q: Please enter second argument: ";
nocap$ARGV[1] = <STDIN>;
nocapchop($ARGV[1]);
nocapprint "skelname  h: Thank you and have a most pleasant day \n";
nocap}


