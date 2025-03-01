#=============================================================================
#
# Purpose: Build a user library with name <name>
#
# For the User:
# -------------
#   Here is a quick crib on how to use this file. It is assumed you have
#   a directory 'build' on the machine you wish to compile on. Also it
#   is assumed all the clever source code (if any) exists in and below
#   one directory. This directory is assumed to be $USER_SRC/<name>.
#       (a) Copy this file into the directory build/<name> and name your
#           copy of this file 'Makefile'.
#           (Provided the environment variable JOB is not set, the file
#           will pick up the job <name> from the directory. If you want
#           to build an executable with a different <name> then add
#           'JOB=<new_name>' to the gmake command line. See note below
#           no command line overrides.)
#       (b) If necessary, change the include areas in CLEO_INCS
#       (c) If you have any of your own include areas these should be
#           added to USER_INCS.
#       (d) If you have code stored in subdirectories below the <name>
#           directory include the subdirectories in the variable DIR_LIST.
#       (e) Check that environment variable USER_SRC is set to the
#           directory *above* the source code. Note: this can be an NFSD
#           mounted directory, for instance on the AXP/OSF USER_SRC
#           might be defined as
#                /home/ds/soft/src
#           and the source code and include files are stored in and
#           below the directory
#                          /home/ds/soft/src/<name>
#           (This means you do not have to move the source between platforms)
#       (g) Execute the command:
#                gmake
#
#   The library should appear in build/lib/lib<name>.a
#
#   To compile a debug version execute the line:
#                gmake DEBUG=y
#     (for compatibility with CLEO library syntax you can also use the
#      command
#                gmake depend debug
#      to compile a debug version)
#     This will create a debug version of users code in
#     build/lib/lib<name>_g.a.
#
#   You can override any symbol used in a makefile by specifying the new
#     symbol on the 'gmake' command line, for example
#                gmake USER_OBJS=myfunc.o
#     It is important to remember that this approach OVERRIDES the makefile
#     value. IF you just which to add extra information to the current
#     makefile value the 'XTRA_????' symbols have been created. Look through
#     this file to see which symbols add to the makefile symbols. For
#     example if you just want to trace the calling routines of the function
#     'myfunc_' just once then you can issue the command
#                gmake XTRA_FFLAGS="-Wl,ymyfunc_"
#     and that option will be added to USER_FFLAGS.
#
#=============================================================================
SHELL := /bin/sh
USER_LINK := CXX
#
#----------------------------
# name of job and executable
#----------------------------

ifeq "$(JOB)" ""
  WHERE := $(shell pwd)
  JOB := $(notdir $(WHERE))
endif
EXE = 

#----------------------------------------
# List of subdirectories containing code
#----------------------------------------

DIR_LIST := 	Class \
		$(XTRA_DIR)

#-------------------------------------------------------
# list of include directories
# USER_INCS should be defined with respect to USER_SRC
# CLEO_INCS should be defined with respect to C_CVSSRC
# (don't forget to leave the "." in the CLEO_INCS list)
#-------------------------------------------------------

USER_INCS :=	. $(XTRA_INCS)

OTHR_INCS :=	$(C3_INC) $(C3_OTHER) $(C3_OTHER)/tcltk/include

CLEO_INCS := 	.

#--------------------------------------------------------------
# extra fortran flags (standard and machine flags added later)
#--------------------------------------------------------------

USER_FFLAGS :=	$(XTRA_FFLAGS)

#--------------------------------------------
# USER libraries required for shared library
#--------------------------------------------

USER_LIBS :=	$(XTRA_LIBS)

#---------------------------------------------
# #define for cpp, define SELECT symbols here
#---------------------------------------------

USER_DEFS :=    $(XTRA_DEFS)

#----------------------------------------------------------------
# if your code needs TITLE information, for example a clever BJ
#   routine, then this need to be set CPP_INFO = y
#----------------------------------------------------------------

CPP_INFO := n

#--------------------------------------------------------------
# invoke standard tail to Makefile to execute compile and link
#--------------------------------------------------------------

CXXFLAGS := -Wall

# --------------------------------------------------------------------
# if g++ acts up about instantiating a template
#
#ifeq "$(CXX)" "g++"
#    GUNG_FIX := -fno-implicit-templates
#endif
# --------------------------------------------------------------------

include $(C3_GMAKE)/M.tail

# --------------------------------------------------------------------
# if you need something special done for a particular file, put here:
#
#$(LIBRARY)(special_file.o) : $(USER_SRC)/<Library>/Class/special_file.cc
#	$(CXX) $(CXXFLAGS) $(GUNG_FIX) $(CLEO_DEFS) $(LIST_INCS) $(CXX_INCS) -c $<
#	@$(AR) r $@ $%
#	@$(RM) $%
# --------------------------------------------------------------------

#
# $Id: Makefile,v 1.6 2001/09/21 19:53:18 cleo3 Exp $
#
# $Log: Makefile,v $
# Revision 1.6  2001/09/21 19:53:18  cleo3
# now get tcl and tk headers and libraries from C3_OTHER
#
# Revision 1.5  1998/07/17 16:58:59  cleo3
# change to pwd from awd (only supported on DEC systems)
#
# Revision 1.4  1998/06/25 18:05:44  cleo3
# switched from C_GMAKE to C3_GMAKE
#
# Revision 1.3  1998/06/24 21:08:42  cdj
# added C3_OTHER to include path so that it can find readline/history.h
#
# Revision 1.2  1998/03/23 23:42:38  mkl
# removed FTcl stuff
#
# Revision 1.1.1.1  1998/03/11 18:52:18  mkl
# imported Interpreter sources
#
# Revision 1.2  1998/01/13 15:49:42  cleo3
# added USER_LINK
#
# Revision 1.1  1997/12/08 18:20:58  mkl
# sample Makefiles
#
#
# DO NOT DELETE
