#=============================================================================
#
# Purpose: Build a standalone executable
#
#   1.) Copy this file to your build area. (Please don't build code in your
#       source area!)
#
#   2.) This makefile includes "M.tail", which contains all the "meat".
#       (suffix rules, platform dependencies etc.)
#
#   3.) Dependencies (ala makedepend) are done via a ".depend" file 
#       which gets created and include by "M.tail".
#
#   4.) Make sure the environment variable USER_SRC is set to the
#       directory *above* the source code:
#         e.g. "setenv USER_SRC /home/mkl/work/cleo3/cvssrc"
#
#   5.) To compile the library, do"
#         unix> gmake CXX=<compiler>
#         e.g. "gmake CXX=cxx"
#
#   6.) The library will appear by default as "../lib/lib<directory>.a", 
#
#   7.) To compile and link in debug mode, use "DEBUG=y":
#          e.g. "gmake CXX=cxx DEBUG=y"
#        This will result in an appended "_g" to the library name.
#
#   8.) You can OVERRIDE any symbol used in a makefile by specifying the new
#       symbol on the command line, for example, 
#          e.g. "gmake USER_OBJS=myfunc.o"
#       Please remember that this will OVERRIDE any value specified in the 
#       Makefile. If you just which to add extra information to the current
#       makefile value the 'XTRA_????' symbols have been created. Look through
#       this file to see which symbols add to the makefile symbols. For
#       example if you just want to trace the calling routines of the function
#       'myfunc_' just once then you can issue the command
#                gmake XTRA_FFLAGS="-Wl,ymyfunc_"
#       and that option will be added to USER_FFLAGS.
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
EXE = ../bin/suez.exe

#----------------------------------------
# List of subdirectories containing code
#----------------------------------------

DIR_LIST := 	. \
		Class \
		Instantiate \
		$(XTRA_DIR)

#---------------------
# Set up CLEO library
#---------------------

CLEO3LIB :=	$(C3_LIB)/lib
OTHRLIB   =     $(C3_OTHER)/lib
CLEOLIB  :=     $(C_LIB)/lib
CERN3LIB :=	$(CERN3_LIB)/lib
SYSLIB	  =	$(GCC_DIR)/lib \
		$(TCL_DIR)/lib $(TK_DIR)/lib \
		/usr/local/lib

#------------------------------------
# USER, CLEO and CERN object modules
#------------------------------------

# SuezMain, UserApplication, etc. are now picked up from libSuez.a, 
# no need to explicitly link to the .o file!
#USER_OBJS :=	$(XTRA_OBJS)  UserApplication.o
USER_OBJS :=	$(XTRA_OBJS)
CLEO3_OBJS :=
OTHR_OBJS :=	
CLEO_OBJS :=	
CERN_OBJS :=

#-------------------------------------------------------
# list of include directories
# USER_INCS should be defined with respect to USER_SRC
# CLEO3_INCS should be set to C3_INC; $USER_SRC/include is implicitly included
# OTHR_INCS should be defined with respect to C3_OTHER
# CLEO_INCS should be defined with respect to C_CVSSRC
# (don't forget to leave the "." in the CLEO_INCS list)
#-------------------------------------------------------

USER_INCS :=	$(XTRA_INCS) .
CLEO3_INCS:=	$(C3_INC)
OTHR_INCS :=	.
CLEO_INCS := 	. 

#--------------------------------------------------------------
# extra fortran flags (standard and machine flags added later)
#--------------------------------------------------------------

USER_FFLAGS :=	$(XTRA_FFLAGS)

#---------------------------------------
# USER, CLEO and CERN libraries to load
#---------------------------------------
# only USER_LIBS get DEBUG flag!

# link with Suez, JobControl in USER_LIBS to pick up debug flag properly
USER_LIBS :=	$(XTRA_LIBS) \
		Suez \
		JobControl

CLEO3_LIBS :=	Processor \
		Interpreter \
		DefaultModule \
		CommandPattern \
		DynamicLoader \
		InteractiveDelivery \
		BlankRecordDelivery \
		DataStorage \
		DataDelivery \
		DataHandler \
		DummyHistogram \
		HistogramInterface \
		ToolBox \
		Utility \
		Signal

#OTHR_LIBS :=	CLHEP
OTHR_LIBS :=
OTHR_LIBS +=	history_cleo3 readline_cleo3
CLEO_LIBS :=
#CERN_LIBS :=	packlib
CERN_LIBS :=

SYS_LIBS  =     tk$(TK_VERS) \
                tcl$(TCL_VERS) \
                X11 \
		curses

#-------------------------------------------------
# list of undefined symbols specified by the user
#-------------------------------------------------

# help gdb find some global symbols
USER_SYMS := procsel prodsel modsel

#--------------------------------------------------------------
# extra compiler/linker flags
#--------------------------------------------------------------

USER_FFLAGS     := $(XTRA_FFLAGS)
USER_CFLAGS     := $(XTRA_CFLAGS)
USER_CXXFLAGS   := $(XTRA_CXXFLAGS)

USER_LFLAGS	:=

#---------------------------------------------
# #define for cpp, define SELECT symbols here
#---------------------------------------------

USER_DEFS :=    $(XTRA_DEFS)

#--------------------------------------------------------------
# invoke standard tail to Makefile to execute compile and link
#--------------------------------------------------------------

include $(C3_GMAKE)/M.tail

#
# $Id: Makefile,v 1.83 2000/12/01 20:33:58 cdj Exp $
#
# DO NOT DELETE

SuezMain.o: ../include/Experiment/Experiment.h ../include/Experiment/types.h
SuezMain.o: /usr/include/limits.h /usr/include/bits/libc-header-start.h
SuezMain.o: /usr/include/features.h /usr/include/stdc-predef.h
SuezMain.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
SuezMain.o: /usr/include/bits/long-double.h /usr/include/gnu/stubs.h
SuezMain.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
SuezMain.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
SuezMain.o: /usr/include/assert.h /usr/include/stdlib.h
SuezMain.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
SuezMain.o: /usr/include/bits/floatn.h /usr/include/bits/floatn-common.h
SuezMain.o: /usr/include/sys/types.h /usr/include/bits/types.h
SuezMain.o: /usr/include/bits/typesizes.h /usr/include/bits/types/clock_t.h
SuezMain.o: /usr/include/bits/types/clockid_t.h
SuezMain.o: /usr/include/bits/types/time_t.h
SuezMain.o: /usr/include/bits/types/timer_t.h /usr/include/bits/stdint-intn.h
SuezMain.o: /usr/include/endian.h /usr/include/bits/endian.h
SuezMain.o: /usr/include/bits/byteswap.h /usr/include/bits/uintn-identity.h
SuezMain.o: /usr/include/sys/select.h /usr/include/bits/select.h
SuezMain.o: /usr/include/bits/types/sigset_t.h
SuezMain.o: /usr/include/bits/types/__sigset_t.h
SuezMain.o: /usr/include/bits/types/struct_timeval.h
SuezMain.o: /usr/include/bits/types/struct_timespec.h
SuezMain.o: /usr/include/bits/pthreadtypes.h
SuezMain.o: /usr/include/bits/thread-shared-types.h
SuezMain.o: /usr/include/bits/pthreadtypes-arch.h /usr/include/alloca.h
SuezMain.o: /usr/include/bits/stdlib-float.h /usr/include/unistd.h
SuezMain.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
SuezMain.o: /usr/include/bits/confname.h /usr/include/bits/getopt_posix.h
SuezMain.o: /usr/include/bits/getopt_core.h Suez/testBoolean.h
SuezMain.o: Suez/forceLinkStorageManagement.h ../include/Experiment/report.h
SuezMain.o: ../include/Utility/Severity.h ../include/C++Std/fwd_ostream.h
SuezMain.o: ../include/C++Std/fwd_string.h
SuezMain.o: ../include/ToolBox/ToolBox_report.h
SuezMain.o: ../include/ToolBox/MessageLog.h
SuezMain.o: ../include/DataHandler/FrameLogger.h /usr/include/time.h
SuezMain.o: /usr/include/bits/time.h /usr/include/bits/types/struct_tm.h
SuezMain.o: /usr/include/bits/types/struct_itimerspec.h
SuezMain.o: /usr/include/bits/types/locale_t.h
SuezMain.o: /usr/include/bits/types/__locale_t.h
SuezMain.o: ../include/JobControl/JobControl.h
SuezMain.o: ../include/CommandPattern/LoaderModule.h
SuezMain.o: ../include/CommandPattern/CompositeModule.h
SuezMain.o: ../include/CommandPattern/Module.h
SuezMain.o: ../include/CommandPattern/ExitCommand.h
SuezMain.o: ../include/CommandPattern/Command.h
SuezMain.o: ../include/CommandPattern/SubcommandBase.h
SuezMain.o: ../include/CommandPattern/Subcommand.h
SuezMain.o: ../include/STLUtility/fwd_map.h
SuezMain.o: ../include/STLUtility/fwd_multimap.h
SuezMain.o: ../include/CommandPattern/QuitCommand.h
SuezMain.o: ../include/CommandPattern/HelpCommand.h
SuezMain.o: ../include/CommandPattern/EchoCommand.h
SuezMain.o: ../include/CommandPattern/HistoryCommand.h
SuezMain.o: ../include/CommandPattern/RunCommandFileCommand.h
SuezMain.o: ../include/STLUtility/fwd_vector.h
SuezMain.o: ../include/CommandPattern/Loader.h
SuezMain.o: ../include/DynamicLoader/DLFactoryManager.h
SuezMain.o: ../include/DynamicLoader/DLSharedObjectHandler.h
SuezMain.o: /usr/include/dlfcn.h /usr/include/bits/dlfcn.h
SuezMain.o: ../include/DataHandler/Stream.h
SuezMain.o: ../include/DataHandler/StreamType.h
SuezMain.o: ../include/Utility/UTIdentifier.h ../include/C++Std/fwd_istream.h
SuezMain.o: ../include/Utility/UTIdentifierLess.h
SuezMain.o: ../include/Experiment/StreamConstants_decl.h
SuezMain.o: ../include/JobControl/StopCounter.h
SuezMain.o: ../include/DataHandler/StreamSet.h
SuezMain.o: ../include/STLUtility/fwd_set.h
SuezMain.o: ../include/STLUtility/fwd_multiset.h
SuezMain.o: ../include/HistogramInterface/HIHistoManager.h
SuezMain.o: ../include/HistogramInterface/HIHistProf.h
SuezMain.o: ../include/HistogramInterface/HIHist.h
SuezMain.o: ../include/JobControl/StartCommand.h
SuezMain.o: ../include/JobControl/SkipCommand.h
SuezMain.o: ../include/JobControl/GotoCommand.h
SuezMain.o: ../include/JobControl/ReprocessCommand.h
SuezMain.o: ../include/JobControl/ParameterCommand.h
SuezMain.o: ../include/JobControl/InteractCommand.h
SuezMain.o: ../include/JobControl/ExceptionControlCommand.h
SuezMain.o: Suez/UserApplication.h ../include/JobControl/ReportModule.h
SuezMain.o: ../include/JobControl/ReportModuleCommand.h
SuezMain.o: ../include/Interpreter/TclInterpreter.h
SuezMain.o: ../include/Interpreter/Tcl.h /usr/include/tcl.h
SuezMain.o: /usr/include/stdio.h /usr/include/bits/types/__fpos_t.h
SuezMain.o: /usr/include/bits/types/__mbstate_t.h
SuezMain.o: /usr/include/bits/types/__fpos64_t.h
SuezMain.o: /usr/include/bits/types/__FILE.h /usr/include/bits/types/FILE.h
SuezMain.o: /usr/include/bits/types/struct_FILE.h
SuezMain.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
SuezMain.o: /usr/include/tclDecls.h /usr/include/tclPlatDecls.h
SuezMain.o: ../include/CommandPattern/Interpreter.h
SuezMain.o: ../include/Utility/StringTokenizer.h
SuezMain.o: ../include/STLUtility/fwd_deque.h
SuezMain.o: ../include/Signal/SignalHandler.h /usr/include/signal.h
SuezMain.o: /usr/include/bits/signum.h /usr/include/bits/signum-generic.h
SuezMain.o: /usr/include/bits/types/sig_atomic_t.h
SuezMain.o: /usr/include/bits/types/siginfo_t.h
SuezMain.o: /usr/include/bits/types/__sigval_t.h
SuezMain.o: /usr/include/bits/siginfo-arch.h
SuezMain.o: /usr/include/bits/siginfo-consts.h
SuezMain.o: /usr/include/bits/types/sigval_t.h
SuezMain.o: /usr/include/bits/types/sigevent_t.h
SuezMain.o: /usr/include/bits/sigevent-consts.h /usr/include/bits/sigaction.h
SuezMain.o: /usr/include/bits/sigcontext.h /usr/include/bits/types/stack_t.h
SuezMain.o: /usr/include/sys/ucontext.h /usr/include/bits/sigstack.h
SuezMain.o: /usr/include/bits/ss_flags.h
SuezMain.o: /usr/include/bits/types/struct_sigstack.h
SuezMain.o: /usr/include/bits/sigthread.h ../include/Signal/SIGINT_Handler.h
SuezMain.o: ../include/Signal/EventHandler.h
SuezMain.o: ../include/DAException/DAException.h Suez/externConst.h
