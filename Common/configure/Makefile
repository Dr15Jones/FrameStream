##
# Fixed head of Makefile
src_root=.
srcdir=.
#
prefix=/uscms_data/d2/cdj/build/temp/cleo/newer/FrameStream/Common
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
libdir=${exec_prefix}/lib
includedir=${prefix}/include
#
INSTALL=/usr/bin/install -c
#


# -*- Makefile -*-
###
#
# Section of Makefile change by 'configure'
# You do not need to change this part!
#
##


# If you use configure, set this to the name of the guarded Makefile
GUARD_MAKEFILE=

## Any LOCAL area setup?
ifneq (none,$(LOCAL_LIBS)none)
LOCALLIBS = $(LIBPATHSEP)$$LOCAL_LIBS
endif

# configure parameters
cxx_root_transform=s/x/x/
java_root_transform=s/x/x/
#
CC=cc
CXX=c++
LDXX=$(DO_QUANTIFY) $(DO_PURIFY) ${CXX}
LD=
NM=nm
SYSLIBS=
JAVACIDL=@JAVACIDL@
JIDLFLAGS=@JIDLFLAGS@
JAVAC=@JAVAC@
JAVAHELP_INDEXER=@JAVAHELP_INDEXER@
HAVE_JAVAHELP=@HAVE_JAVAHELP@
JFLAGS=@JFLAGS@
SYSCLASSES=@SYSCLASSES@
MTCOMPILEOPTION=
MTLINKOPTION=
MTLIBS=
MTEXT=
DEBUG= 
DEBUG_OPTSW=
DEBUG_DBGSW=
DEBUG_EXT=
CFLAGS=$(EXTRADEFINES) -DHAVE_CONFIG_H    `echo $(INCLUDES) | sed '$(cxx_root_transform)'`
CXXFLAGS=$(EXTRADEFINES) -DHAVE_CONFIG_H    `echo $(INCLUDES) | sed '$(cxx_root_transform)'`
# LDFLAGS and LDXXFLAGS dont need $(EXTRADEFINES)
LDFLAGS=`echo "$(LOCALLIBS) $(LIBDIRS)" | sed '$(cxx_root_transform)'` 
LDXXFLAGS= `echo "$(LOCALLIBS) $(LIBDIRS)" | sed '$(cxx_root_transform)'` -o
RANLIB=@RANLIB@
AR=ar
AR_LINK=ar rv
AWK=gawk
MKDIRHIER=mkdirhier
FIND=find
ORBCXX=@ORBCXX@
ORBCXXFLAGS=-DHAVE_CONFIG_H `echo $(IDLINCLUDES) | sed '$(cxx_root_transform)'` @ORBCXXFLAGS@
ORBJAVA=@ORBJAVA@
ORBJAVAFLAGS=-DHAVE_CONFIG_H `echo $(IDLINCLUDES) | sed '$(cxx_root_transform)'` @ORBJAVAFLAGS@
MTORBLIB=@MTORBLIB@
SNORBLIB=@SNORBLIB@
ORBLIB=@ORBLIB@
ORBPATH=@ORBPATH@
ORBLIBPATH=@ORBLIBPATH@
#
INSTALL_PROGRAM=${INSTALL}
INSTALL_DATA=${INSTALL} -m 644
INSTALL_HEADER=${INSTALL} -m 644
INSTALL_LIBRARY=${INSTALL} -m 644
TEMPLATEDIR=none
TEMPLATELINKDIR=none
#
machsubname=x86_64-unknown-linux-gnu
CPU=unknown
b_transform=s/\/bin/\/bin\/x86_64-unknown-linux-gnu/
l_transform=s/\/lib/\/lib\/x86_64-unknown-linux-gnu/
i_transform=s/\/include/\/include\/x86_64-unknown-linux-gnu/
list_transform=s/x/x/
#
OEXT=.o
AEXT=.a
XEXT=
DOTO=$(DBGEXT).o
DOTA=$(DBGEXT).a
DOTX=$(DBGEXT)
PRELIB=lib
LINKLIBOPT=-l
GNUEXT=
OUTSWITCH=-o
CSWITCH=-c
DEPSWITCH=
PREDEPHEADER=none
LINKEXT=$(DBGEXT)
LIBPATHSEP=-L
CXXRULESLINE=\
	$(CXX) $(CXXFLAGS) $(DEBUG) $(CSWITCH) $< $(OUTSWITCH) $@
CXXRULES = $(shell echo $(CXXRULESLINE))
CRULESLINE=\
	$(CC) $(CFLAGS) $(DEBUG) $(CSWITCH) $< $(OUTSWITCH) $@
CRULES = $(shell echo $(CRULESLINE))
#
.PHONY: all clean distclean install
.SUFFIXES: .cxx .cc .c $(DOTO)  .java .class

.cxx$(DOTO):

	$(CXX) $(CXXFLAGS) $(DEBUG) $(CSWITCH) $< $(OUTSWITCH) $@

.cc$(DOTO):

	$(CXX) $(CXXFLAGS) $(DEBUG) $(CSWITCH) $< $(OUTSWITCH) $@

.c$(DOTO):

	$(CC) $(CFLAGS) $(DEBUG) $(CSWITCH) $< $(OUTSWITCH) $@

ifneq (,$(findstring $(PURIFY),yY)$(findstring $(QUANTIFY),yY))
include $(COM_GMAKE)/purify_quantify_rules.mk
endif

.o:

	$(LDXX) $(LDXXFLAGS) $@ $< $(LIBS)

.java.class:
	$(JAVAC) $(JFLAGS) $<

#
JAVAPACKAGE = @JAVAPACKAGE@
ADDEDJCLASSES = :$(src_root)/src/java:$(prefix)/classes:$(SC_CLASS):$(COM_CLASS)
JAVABASE = $(shell echo $(JAVAPACKAGE) | sed 's+\.+/+g' )
JAVALIST = $(shell echo $(SYSCLASSES) | sed '$(list_transform)' | sed '$(java_root_transform)' )
LOCALCLASSES= $(shell echo $(ADDEDJCLASSES)$(EXTRAJCLASSES) | sed '$(list_transform)' | sed '$(java_root_transform)' )
JCLASSES = $(JAVALIST)
#
IDLHEADERS=@IDLHEADERS@
IDLSOURCE=@IDLSOURCE@
IDLOBJECTS=@IDLOBJECTS@
#
LIBRARY = $(PRELIB)$(LIBNAME)$(GNUEXT)$(DOTA)
ONLINEDIRS = ${exec_prefix}/lib/x86_64-unknown-linux-gnu
#
# Override if used!
DEPFILE=none
LIBDEPFILE=none
#
IDLTRANSLATE=@IDLTRANSLATE@
IDLDEPENDFILE=@IDLDEPENDFILE@
HAVECORBA=@HAVECORBA@
INSTALLCORBA=@INSTALLCORBA@
ISEMBEDDED=notAvailable
INSTALLEMBEDDED=notAvailable
DEPFILEEMBEDDED=none
ISNOTEMBEDDED=notAvailable
INSTALLNOTEMBEDDED=notAvailable
DEPFILENOTEMBEDDED=none
HAVECRYPT=@HAVECRYPT@
INSTALLCRYPT=@INSTALLCRYPT@
#
ALLJAVA=@ALLJAVA@
INSTALLJAVA=@INSTALLJAVA@

# NT Service link objects
SERVICE_OBJ=

#
## Third Party Products ##
#

## Insight
# Special InSight commands
INSIGHT_CXX=
INSIGHT_LDXX=
INSEXT=-ins

#
# Objectivity
HAVEOBJY=@HAVEOBJY@
INSTALLOBJY=@INSTALLOBJY@
PAGE_SIZE=@OODEFAULT_PAGE_SIZE@
LOCKSERVER_HOST=@OODEFAULT_LOCKSERVER_HOST@
OONEWFD=@OONEWFD_CMD@
OODELETEFD=@OODELETEFD_CMD@
OODDLX=@OODDLX_CMD@
OOSCHEMAUPGRADE=@OOSCHEMAUPGRADE_CMD@
DDLFLAGS=@DDLFLAGS@
DDLHEADERS=@DDLHEADERS@
DDLSOURCES=@DDLSOURCES@
DDLOBJECTS=@DDLOBJECTS@
OBJY_HOME=@OBJY_HOME@
OBJYLIBPATH=@OBJYLIBPATH@
DBLIB=@DBLIB@
DBSTLLIB=@DBSTLLIB@
# BDL
HAVEBDLCLIENT=@HAVEBDLCLIENT@
HAVEBDLSERVER=@HAVEBDLSERVER@
HAVEBDLSCLIENT=@HAVEBDLSCLIENT@
HAVEBDLSSERVER=@HAVEBDLSSERVER@
INSTALLBDLCLIENT=@INSTALLBDLCLIENT@
INSTALLBDLSERVER=@INSTALLBDLSERVER@
INSTALLBDLSCLIENT=@INSTALLBDLSCLIENT@
INSTALLBDLSSERVER=@INSTALLBDLSSERVER@
STD_BASEINCS=@STD_BASEINCS@
STD_STDINCS=@STD_STDINCS@
STD_STLINCS=@STD_STLINCS@
STD_STDLIBS=@STD_STDLIBS@
BDL_STL_DEFINE=@BDL_STL_DEFINE@
BDLCOMPILE=@BDL_COMPILE_CMD@
BDLCOMPILE_SS=@BDL_COMPILE_SS_CMD@
BDLCONSTANTSCLIENTOBJECTS=@BDLCONSTANTSCLIENTOBJECTS@
BDLCONSTANTSSERVEROBJECTS=@BDLCONSTANTSSERVEROBJECTS@
BDLSNAPSHOTSCLIENTOBJECTS=@BDLSNAPSHOTSCLIENTOBJECTS@
BDLSNAPSHOTSSERVEROBJECTS=@BDLSNAPSHOTSSERVEROBJECTS@
IDLNAMES=@IDLNAMES@
BDLNAMES=@BDLNAMES@
DDLNAMES=@DDLNAMES@
CONSTANTS_DDL_PREFIX=@CONSTANTS_DDL_PREFIX@
CONSTANTS_BOOT_ID=@CONSTANTS_BOOT_ID@
CONSTANTS_BOOT_FILE=@CONSTANTS_BOOT_FILE@
CONSTANTS_SERVER_LIBNAME=@CONSTANTS_SERVER_LIBNAME@
BDLCLIENTHEADERS=@BDLCLIENTHEADERS@
BDLSERVERHEADERS=@BDLSERVERHEADERS@
BDLSERVEROBJECTS=@BDLSERVEROBJECTS@
BDLDDLHEADERS=@BDLDDLHEADERS@
BDLDDLSOURCES=@BDLDDLSOURCES@
BDLDDLOBJECTS=@BDLDDLOBJECTS@
# Dummies to prevent from being empty
CLIENTLIB=client
SERVERLIB=server
#
CLIENTHEADERS=$(BDLCLIENTHEADERS)
SERVERHEADERS=$(BDLSERVERHEADERS) $(BDLDDLHEADERS)
# $(BDLSERVERHEADERS)
CLIENTOBJECTS=$(BDLCLIENTOBJECTS)
SERVEROBJECTS=$(BDLSERVEROBJECTS)
BDLDEPENDFILE=@BDLDEPENDFILE@
DDLDEPENDFILE=@DDLDEPENDFILE@

###
# Adjustable definitions!
#
# Tailor your Makefile.in to the needs of this directory!
default : all install makeinstall

makeinstall : Makefile
	@echo "Generate user Makefile fragments..."
# Nothing to be done right now...
	@echo "Done."
	@$(MKDIRHIER) $(prefix)/Gmake/$(machsubname)
	$(INSTALL_HEADER) M.templ $(prefix)/Gmake/M.templ
	$(INSTALL_HEADER) Gmake/head.mk $(prefix)/Gmake/$(machsubname)/common_head.mk
	$(INSTALL_HEADER) Gmake/tail_user.mk $(prefix)/Gmake/$(machsubname)/common_tail.mk
	$(INSTALL_HEADER) Gmake/guard_make.mh $(prefix)/Gmake/$(machsubname)/guard_make.mk
	$(INSTALL_HEADER) Gmake/tcl.mk $(prefix)/Gmake/$(machsubname)/tcl.mk
	$(INSTALL_HEADER) makeaddmacro.awk $(prefix)/Gmake/$(machsubname)
	$(INSTALL_HEADER) makedep.awk $(prefix)/Gmake/$(machsubname)
	$(INSTALL_HEADER) makeextract1.awk $(prefix)/Gmake/$(machsubname)
	$(INSTALL_HEADER) makeextract2.awk $(prefix)/Gmake/$(machsubname)
	$(INSTALL_HEADER) makesingle.awk $(prefix)/Gmake/$(machsubname)
	@echo "Makefile fragments installed."
	@$(MKDIRHIER) $(prefix)/bin
	$(INSTALL_PROGRAM) config.guess $(prefix)/bin/config.guess
	$(INSTALL_PROGRAM) config.sub $(prefix)/bin/config.sub
	@echo "System triple tools installed."
	@$(MKDIRHIER) $(prefix)/bin/$(machsubname)
	$(INSTALL_PROGRAM) `echo "$(INSTALL_PROGRAM)"| $(AWK) '{printf("%s%s\n", $$1, "$(DOTX)");}' - | sed 's/.out//' ` $(prefix)/bin/$(machsubname)/install
	@echo "Install tool installed"

#
SUBCLEAN= subdirclean
SUBALL  = subdirdefault
SUBINSTALL = subdirinstall
SUBDEPEND = subdirdepend
SUBDIRS = headers
#

###
##  You normally do not change anything after this line
###


# -*- Makefile -*-
#

none:

notAvailable:
	@echo "Not available on this platform"

## Dependecies of local library
# off OBJECTRULES = $(patsubst %, $(LIBRARY)(%), $(OBJECTS))

$(LIBRARY) : $(OBJECTS)
	$(AR_LINK) $(LIBRARY) $(OBJECTS)
ifneq ($(TEMPLATELINKDIR),none)
	@if test -d $(TEMPLATELINKDIR); then \
	  $(AR_LINK) $(LIBRARY) $(TEMPLATELINKDIR)/*.o; \
	fi
endif

## Service functionality only for NT


## Any LOCAL area setup?
ifneq (none,$(LOCAL_INCS)none)
LOCALINCS_tmp = $(subst $(COM_INCS),$$LOCAL_INCS,$(EXTRAINCLUDES))
LOCALINCS_tmp2 = $(subst $(SC_INCS),$$LOCAL_INCS,$(LOCALINCS_tmp))
LOCALINCS = -I$$LOCAL_INCS -I$$LOCAL_INCS/$(machsubname) $(LOCALINCS_tmp2)
ifneq (none,$(PACKAGEREGISTER)none)
PACKAGEREGISTER = "$(LOCAL_GMAKE)"
endif
endif

## BASICS include and library macros
INCLUDES = $(LOCALINCS) -I$(COM_INCS) -I$(COM_INCS)/$(machsubname) -I. \
	$(addprefix -I, $(EXTRAINCLUDES:-I%=%))
LIBS = $(LINKOBJ) $(LINKOBJFROMLIB) $(LINKLIBS) $(EXTRALIBS) $(INSIGHTLIBS) $(SYSLIBS)

## normal targets
clean : $(GUARD_MAKEFILE) $(SUBCLEAN) remove_template
	@$(RM) core *~ *.o *.obj *.a *.lib *.out $(PROGRAMS) *.exe *.cc *.hh *.mhh
	@$(RM) *.log *.map *.d *.class *.flc
	@$(RM) $(addsuffix -g, $(PROGRAMS)) $(addsuffix -ins, $(PROGRAMS))
	@$(RM) $(addsuffix _r, $(PROGRAMS)) 

template_clean : remove_template
ifneq ($(TEMPLATESUBDIRS),)
	@for tsubdir in $(TEMPLATESUBDIRS); do \
	  cd $$tsubdir; $(MAKE) -f ../Makefile DEPFILE=none remove_template; cd ..; \
	done
endif
ifneq ($(SUBCLEAN),)
ifneq ($(SUBDIRS),)
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    cd $$d; $(MAKE) DEPFILE=none template_clean; cd ..;\
	  fi \
	done
endif
endif

remove_template :
ifneq ($(TEMPLATEDIR),none)
	@if test -d $(TEMPLATEDIR); then \
	  echo "Clean template sources"; \
	  $(RM) *.o *.obj; \
	  echo "Clean template dir"; \
	  rm -rf $(TEMPLATEDIR); \
	fi
endif

programs_template_clean :
	@if test ! "`find . -name programs`"xx = "xx"; then \
	  startDir=`pwd`; \
	  for progdir in "`find . -name programs`"; do \
	    if test -d $$progdir; then \
	      cd $$progdir; $(MAKE) DEPFILE=none template_clean; cd $$startDir; \
	    fi \
	  done; \
	  echo "Programs directories cleaned."; \
	else \
	  echo "No programs directories found."; \
	fi

subdirclean :
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    cd $$d; $(MAKE) DEPFILE=none clean; cd ..;\
	  fi \
	done

distclean : clean
	$(RM) config.log config.status config.cache
	$(RM) sc_config.h sc_config.h_g
#
ALLDEPCXXFILES = $(CXXSOURCES:.cxx=.d)
ALLDEPCCFILES = $(CCSOURCES:.cc=.d)
ALLDEPCFILES = $(CSOURCES:.c=.d)
ALLDEPFILES = $(CXXSOURCES:.cxx=.d) $(CCSOURCES:.cc=.d) $(CSOURCES:.c=.d)
#
$(ALLDEPCXXFILES): %.d : %.cxx

	$(SHELL) -ec '$(CXX) $(CXXFLAGS) $(DEBUG) $(DEPSWITCH) \
 $< | $(AWK) -f $(dep_root)/makedep.awk - | sort -u > $@ '

$(ALLDEPCCFILES): %.d : %.cc

	$(SHELL) -ec '$(CXX) $(CXXFLAGS) $(DEBUG) $(DEPSWITCH) \
 $< | $(AWK) -f $(dep_root)/makedep.awk - | sort -u > $@ '

$(ALLDEPCFILES): %.d : %.c

	$(SHELL) -ec '$(CC) $(CFLAGS) $(DEBUG) $(DEPSWITCH) \
 $< | $(AWK) -f $(dep_root)/makedep.awk - | sort -u > $@ '

depend : $(SUBDEPEND) $(PREDEPHEADER) $(ALLDEPFILES) $(DEPFILE)
	@gmake CONSIDEREDDOTD=$(ALLDEPFILES) $(DEPFILE)
	@echo "Completed dependency check"

ifneq (none,$(DEPFILE))
$(DEPFILE) : $(CXXSOURCES) $(CCSOURCES) $(CSOURCES) $(CONSIDEREDDOTD)

	@touch $(DEPFILE)
	$(MAKE) $(ALLDEPFILES)
	@$(RM) depend.mh1 depend.mh2
	for dep in $(ALLDEPFILES); do \
	  $(AWK) -f $${COM_GMAKE}/makeextract1.awk $$dep >>depend.mh1; \
	  $(AWK) -f $${COM_GMAKE}/makeextract2.awk $$dep >>depend.mh2; \
	done
	@$(RM) $(DEPFILE)
	@echo "# **DO NOT EDIT. Automatically generated by makedep. DO NOT EDIT**" > $(DEPFILE)
	@cat depend.mh1 | sort -u | \
	  $(AWK) -f $${COM_GMAKE}/makeaddmacro.awk - >> $(DEPFILE)
	@cat depend.mh2 >> $(DEPFILE)
	@echo "# **End of dependencies** #" >> $(DEPFILE)
	@$(RM) depend.mh1 depend.mh2
endif

subdirdepend :
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    cd $$d; $(MAKE) depend; cd ..;\
	  fi \
	done

#
idlheader : $(SUBALL) $(GUARD_MAKEFILE) $(IDLHEADERS) $(INCINSTALL)

all : $(SUBALL) $(GUARD_MAKEFILE) $(HEADERS) $(ALLLIBRARY) $(PROGRAMS)

installclasses : $(SUBINSTALL) $(BININSTALL)

appletinstall : packageinstall
	@if test -n "$(LIBNAME)"; then \
	  xfile=`basename $(LIBNAME)` ; \
	  rm -f $(prefix)/bin/$(machsubname)/$$xfile ; \
	  echo "Creating $$xfile link" ; \
	  ln -s ${COM_EXE}/Startup.sh $(prefix)/bin/$(machsubname)/$$xfile ; \
	fi
	@for pg in `ls *.html`; do \
	  $(INSTALL_DATA) $$pg $(prefix)/classes/ ; \
	done

applicationinstall : packageinstall
	@if test -n "$(LIBNAME)"; then \
	  xfile=`basename $(LIBNAME)` ; \
	  rm -f $(prefix)/bin/$(machsubname)/$$xfile ; \
	  echo "Creating $$xfile link" ; \
	  ln -s ${COM_EXE}/Startup.sh $(prefix)/bin/$(machsubname)/$$xfile ; \
	fi

ALLJPACKTARGETS = $(addprefix $(prefix)/classes/$(LIBNAME)/, $(PROGRAMS))

packageinstall : $(ALLJPACKTARGETS)
	@echo "Class files updated"

ifneq (none$(ALLJPACKTARGETS),none)
$(ALLJPACKTARGETS) : $(prefix)/classes/$(LIBNAME)/% : %
	@$(MKDIRHIER) $(prefix)/classes/$(LIBNAME)
	@for cl in `echo $? ; echo $(subst .class,\\$$*.class,$?) | grep -v "*"` ; do \
	  echo Install $(prefix)/classes/$(LIBNAME)/$$cl; \
	  $(INSTALL_DATA) $$cl $(prefix)/classes/$(LIBNAME); \
	done
endif

subdirall :
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    echo "make all in "$$d; \
	    cd $$d; $(MAKE) all; cd ..;\
	  fi \
	done

subdirallj :
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    echo "make allj in "$$d; \
	    cd $$d; $(MAKE) allj; cd ..;\
	  fi \
	done

subdirdefault :
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    echo "make in "$$d; \
	    cd $$d; $(MAKE); cd ..;\
	  fi \
	done

subdiridlheader :
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    echo "make idlheader in "$$d; \
	    cd $$d; $(MAKE) idlheader; cd ..;\
	  fi \
	done
#

normalinstall : libinstalldir $(SUBINSTALL) $(BININSTALL) $(INCINSTALL) $(LIBINSTALL)

bininstall : 
	$(MKDIRHIER) `echo $(bindir) | sed "$(b_transform)"`
	for p in $(PROGRAMS); do \
	  $(INSTALL_PROGRAM) $$p `echo $(bindir) | sed "$(b_transform)" `; \
	done

admininstall : 
	$(MKDIRHIER) $(prefix)/admin/$(machsubname)
	for p in $(PROGRAMS); do \
	  $(INSTALL_PROGRAM) $$p $(prefix)/admin/$(machsubname); \
	done

INSTALLEDADDLIB = $(addprefix $(libdir)/x86_64-unknown-linux-gnu/, $(LIBRARY))
libinstall: $(INSTALLEDADDLIB)

addlibinstall: $(INSTALLEDADDLIB)

$(INSTALLEDADDLIB) : libinstalldir $(OBJECTS)
	@$(AR_LINK) $(INSTALLEDADDLIB) $(OBJECTS)
ifneq ($(TEMPLATELINKDIR),none)
	@if test -d $(TEMPLATELINKDIR); then \
	  $(AR_LINK) $(INSTALLEDADDLIB) $(TEMPLATELINKDIR)/*.o; \
	fi
endif

libinstalldir :
	@$(MKDIRHIER) `echo $(libdir) | sed "$(l_transform)"`
#
ifeq (none$(LIBNAME),none)
LIBINCLUDE = $(includedir)
LIBMACHINCLUDE = $(includedir)/${machsubname}
else
LIBINCLUDE = $(includedir)/$(LIBNAME)
LIBMACHINCLUDE = $(includedir)/${machsubname}/$(LIBNAME)
endif

INSTALLEDDIR=$(LIBINCLUDE)/$(HEADERS_SUBDIR)
INSTALLEDHEADERS = $(addprefix $(LIBINCLUDE)/$(HEADERS_SUBDIR), $(HEADERS))

# Rule to create an empty packages.names file
libpackagefile :
ifneq (none$(PACKAGEREGISTER),none)
	@if test ! -f $(PACKAGEREGISTER)/packages.names; then \
	  $(MKDIRHIER) $(PACKAGEREGISTER); \
	  echo "" > $(PACKAGEREGISTER)/packages.names; \
	  echo "Created empty packages.names"; \
	fi
else
	@echo "PACKAGEREGISTER variable not defined" 
endif

inclibinstall : $(INSTALLEDHEADERS) libpackagefile
ifneq (none$(LIBNAME),none)
	@echo "Headers installed."
ifneq (none$(PACKAGEREGISTER),none)
	@touch $(PACKAGEREGISTER)/packages.names
	@cp $(PACKAGEREGISTER)/packages.names $(src_root)/names.libs
	@echo $(LIBNAME) >> $(src_root)/names.libs
	@sort -u -r $(src_root)/names.libs >$(src_root)/packages.names
	@echo "" >>$(src_root)/packages.names
	@cp $(src_root)/packages.names $(PACKAGEREGISTER)/packages.names
	@rm -f $(src_root)/names.libs $(src_root)/packages.names 
endif
endif
ifeq (none$(LIBNAME),none)
	@echo "Headers installed."
endif

ifneq (none$(INSTALLEDHEADERS),none)
$(INSTALLEDHEADERS) : $(LIBINCLUDE)/$(HEADERS_SUBDIR)% : %
ifneq (none$(INSTALLEDDIR),none)
	@$(MKDIRHIER) $(INSTALLEDDIR)
endif
	@for p in $?; do \
	  $(MKDIRHIER) `dirname $(INSTALLEDDIR)$$p`; \
	  $(INSTALL_HEADER) `basename $$p` $(INSTALLEDDIR)$$p; \
	done
endif

#
INSTALLEDMACHDIR=$(LIBMACHINCLUDE)/$(MACH_HEADERS_SUBDIR)
INSTALLEDMACHHEADERS = $(addprefix $(LIBMACHINCLUDE)/$(MACH_HEADERS_SUBDIR), $(MACH_HEADERS))

ifneq (none$(INSTALLEDMACHHEADERS),none)
$(INSTALLEDMACHHEADERS) : $(LIBMACHINCLUDE)/$(MACH_HEADERS_SUBDIR)% : %
	@$(MKDIRHIER) $(INSTALLEDMACHDIR)
	for p in $?; do \
	  $(MKDIRHIER) `dirname $(INSTALLEDMACHDIR)$$p`; \
	  $(INSTALL_HEADER) `basename $$p` $(INSTALLEDMACHDIR)$$p; \
	done
endif

incmachinstall : $(INSTALLEDMACHHEADERS) libpackagefile
ifneq (none$(LIBNAME),none)
	@echo "Machine dependent Header installed."
ifneq (none$(PACKAGEREGISTER),none)
	@touch $(PACKAGEREGISTER)/packages.names
	@cp $(PACKAGEREGISTER)/packages.names $(src_root)/names.libs
	@echo '$$(machsubname)/'$(LIBNAME) >> $(src_root)/names.libs
	@sort -u -r $(src_root)/names.libs >$(src_root)/packages.names
	@echo "" >>$(src_root)/packages.names
	@cp $(src_root)/packages.names $(PACKAGEREGISTER)/packages.names
	@rm -f $(src_root)/names.libs $(src_root)/packages.names
endif
endif
ifeq (none$(LIBNAME),none)
	@echo "Machine dependent Header installed."
endif

subdirinstall:
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    echo "Install in "$$d; \
	    cd $$d; $(MAKE) install; cd ..;\
	  fi \
	done
#
gifimageinstall:
	@$(MKDIRHIER) $(prefix)/classes/images
	@for d in $(IMAGEDIRS); do \
	  if test -d $$d; then \
	  $(MKDIRHIER) $(prefix)/classes/images/$$d; \
	    echo "Installing GIF images from "$$d; \
	    cp $$d/*.gif $(prefix)/classes/images/$$d/ ; \
          fi \
        done

jpgimageinstall:
	@$(MKDIRHIER) $(prefix)/classes/images
	@for d in $(IMAGEDIRS); do \
	  if test -d $$d; then \
	    $(MKDIRHIER) $(prefix)/classes/images/$$d; \
	    echo "Installing JPEG images from "$$d; \
	    cp $$d/*.jpg $(prefix)/classes/images/$$d/ ; \
          fi \
        done

htmlimageinstall:
	@$(MKDIRHIER) $(prefix)/classes/images
	@for d in $(IMAGEDIRS); do \
	  if test -d $$d; then \
	    $(MKDIRHIER) $(prefix)/classes/images/$$d; \
	    echo "Installing image html files from "$$d; \
	    cp $$d/*.html $(prefix)/classes/images/$$d/ ; \
	  fi \
	done

wavsoundinstall:
	@$(MKDIRHIER) $(prefix)/classes/sounds
	@for d in $(IMAGEDIRS); do \
	  if test -d $$d; then \
	    echo "Installing sound wav files from "$$d; \
	    cp $$d/*.wav $(prefix)/classes/sounds/ ; \
	  fi \
	done

ifneq ($(DEPFILE), none)
include $(DEPFILE)
endif
###
# Elliots library dependency generator
LIBDIRSUSED = $(subst $(LIBPATHSEP), ,$(LOCALLIBS) $(LIBDIRS))
LIBSUSED = $(subst $(LINKEXT), , $(subst $(LINKLIBOPT), ,$(EXTRALIBS) $(LINKLIBS)))

# since I can't comment the shell script this code generates the library
# dependency by doing:
#
# loop over libraries in LIBDIRS
#   loop over directories EXTRALIBS
#      see if library exists in this directory
#        compare to SC_LIBS, COM_LIBS, LOCAL_LIBS 
#        to find out where it came from
#        otherwise just put absolute path in dependencies
#      endif exist in directory
#   endloop over directories
# endloop over libraries
#

ifneq ($(LIBDEPFILE), none)     
$(LIBDEPFILE) : Makefile $(COM_GMAKE)/common_tail.mk
	@$(RM)  $(LIBDEPFILE) foundlibs
	@echo "# library dependencies" >> $(LIBDEPFILE); 
	@for l in $(LIBSUSED); do \
	  for d in $(LIBDIRSUSED); do \
	    if test -f $$d/$(PRELIB)$$l$(DOTA) ; then \
		if test "$$d" = "$(LOCAL_LIBS)" ; then \
	          echo '$$(PROGRAMS) : $$(LOCAL_LIBS)/$$(PRELIB)'$$l'$$(DOTA)' >> $(LIBDEPFILE); \
	          $(LINKOBJFROMLIBDEPEND_LOCALLIB) \
	        elif test "$$d" = "$(SC_LIBS)" ; then \
	          echo '$$(PROGRAMS) : $$(SC_LIBS)/$$(PRELIB)'$$l'$$(DOTA)' >> $(LIBDEPFILE); \
	          $(LINKOBJFROMLIBDEPEND_SCLIB) \
	        elif test "$$d" = "$(COM_LIBS)" ; then \
	          echo '$$(PROGRAMS) : $$(COM_LIBS)/$$(PRELIB)'$$l'$$(DOTA)' >> $(LIBDEPFILE); \
	          $(LINKOBJFROMLIBDEPEND_COMLIB) \
                else \
	          echo '$$(PROGRAMS) : '$$d'/$$(PRELIB)'$$l'.a' >> $(LIBDEPFILE); \
	        fi; \
	        break; \
	    fi;\
	  done; \
	done

include $(LIBDEPFILE)

endif
#
# Rule to force an object to be linked from a library
ifneq ($(LINKOBJFROMLIB),)
# "rules" used in libdepend generation to make the local $(DOTO) depend on 
# on the library it came from 
LINKOBJFROMLIBDEPEND_SCLIB = for o in $(LINKOBJFROMLIB); do \
	   if test -n "`$(AR) t $$d/$(PRELIB)$$l$(DOTA) | grep -x $$o `"; then \
	          echo  $$o' : $$(SC_LIBS)/$$(PRELIB)'$$l'$$(DOTA)'| sed s/\\.o/'$$(DOTO)'/ >> $(LIBDEPFILE); \
	   fi; \
	done; 

LINKOBJFROMLIBDEPEND_COMLIB = for o in $(LINKOBJFROMLIB); do \
	   if test -n "`$(AR) t $$d/$(PRELIB)$$l$(DOTA) | grep -x $$o `"; then \
	          echo  $$o' : $$(COM_LIBS)/$$(PRELIB)'$$l'$$(DOTA)'| sed s/\\.o/'$$(DOTO)'/ >> $(LIBDEPFILE); \
	   fi; \
	done; 

LINKOBJFROMLIBDEPEND_LOCALLIB = for o in $(LINKOBJFROMLIB); do \
	   if test -n "`$(AR) t $$d/$(PRELIB)$$l$(DOTA) | grep -x $$o `"; then \
	          echo  $$o' : $$(LOCAL_LIBS)/$$(PRELIB)'$$l'$$(DOTA)'| sed s/\\.o/'$$(DOTO)'/ >> $(LIBDEPFILE); \
	   fi; \
	done; 


# rules to extract $(DOTO) file from an archive
# should follow same search order as linker
$(LINKOBJFROMLIB) : 
	@for o in $(LINKOBJFROMLIB); do \
	  for l in $(LIBSUSED); do \
	    for d in $(LIBDIRSUSED); do \
	      if test -f $$d/$(PRELIB)$$l$(DOTA) ; then \
	        if test -n "`$(AR) t $$d/$(PRELIB)$$l$(DOTA) | grep -x $$o `"; then \
	          $(AR) x $$d/$(PRELIB)$$l$(DOTA) $$o; \
                  break; \
	        fi; \
	      fi; \
	    done; \
	  done; \
	done; 

endif

#
# Rules to Make a .out file from a set of libraries
# for powerpc
#
# set VXOUTFILE and VXOUTLIBS in main Makefile
#
ifneq ($(VXOUTFILE),)
DOTCC_SYMBOL_REMOVER = $(COM_GMAKE)/dotcc_symbol_remover_ppc
GREP = /usr/xpg4/bin/grep
#
# Dependency on libraries linked
ALLSOURCELIBS1 = $(addprefix $(PRELIB), $(VXOUTLIBS))
ALLSOURCELIBS = $(addsuffix $(DGBEXT)$(DOTA), $(ALLSOURCELIBS1)) 
#
LIBDIRS_stripped =  $(subst $(LIBPATHSEP),,$(LIBDIRS))
vpath %$(DGBEXT)$(DOTA) $(LIBDIRS_stripped)
# Make the $(VXOUTFILE).out!
$(VXOUTFILE)$(DBGEXT).out : Makefile $(ALLSOURCELIBS)
	@echo ""
	@echo "Making $(VXOUTFILE).out for $(machsubname)"
	@echo ""
	- @ $(RM) ctdt.c *.tmp
	@for l in $(VXOUTLIBS); do					\
          for d in $(LIBDIRS_stripped); do				\
              if test -f $$d/lib$$l$(DOTA); then			\
                  echo "Adding $$l from $$d...";			\
                  cp $$d/lib$$l$(DOTA) .;				\
                  break;						\
              fi;							\
          done;								\
	  $(RANLIB) lib$$l$(DOTA);					\
	  $(AR) -t lib$$l$(DOTA) >names.tmp;				\
	  $(AR) -x lib$$l$(DOTA) `cat names.tmp`;			\
	  if test -f allnames.tmp;					\
	  then $(GREP) -v -x -f allnames.tmp names.tmp >> allnames.tmp;	\
	  else cat names.tmp > allnames.tmp; fi;			\
	  $(RM) lib$$l$(DOTA);						\
        done
	@ $(DOTCC_SYMBOL_REMOVER)
	$(LD) $(LD_PARTIAL_FLAGS) -o $(VXOUTFILE).tmp `cat allkeepnames.tmp` 
	$(NM) --no-sort $(VXOUTFILE).tmp | munch > ctdt.c
	$(MAKE) -f Makefile EXTRADEFINES="-traditional" ctdt.o
	$(LD) $(LD_PARTIAL_FLAGS) -o $@ $(VXOUTFILE).tmp ctdt.o
	$(RM) `cat allnames.tmp`
	$(RM) ctdt.o ctdt.c *.tmp
	@echo "done"
endif

CLIENTLIBRARY = $(PRELIB)$(CLIENTLIB)$(GNUEXT)$(DOTA)
SERVERLIBRARY = $(PRELIB)$(SERVERLIB)$(GNUEXT)$(DOTA)
LIBCLIENTINCLUDE = $(includedir)/$(CLIENTLIB)
LIBSERVERINCLUDE = $(includedir)/$(SERVERLIB)

# Federated DB
#
$(DB_BOOT) : 
	@$(MKDIRHIER) $(prefix)/db
	$(OONEWFD)

subdirdbdefault :
	@for d in $(SUBDIRSDB); do \
	  if test -d $$d; then \
	    echo "make in "$$d; \
	    cd $$d; $(MAKE); cd ..;\
	  fi \
	done

# 
# Clean for DB
cleandb :
	@$(RM) -r Templates.DB
	@$(RM) *.hh *.cc core $(PROGRAMS) *.o
#
# Clean for DB + FDB
cleanfd : cleandb
	$(OODELETEFD)
# 
# Clean for bdl
cleanbdl :
	@$(RM) -r Templates.DB *.a idl server client
#
# Subdirclean for DB servers
subdirdbclean : subdirclean
	@for d in $(SUBDIRSDB); do \
	  if test -d $$d; then \
	    cd $$d; $(MAKE) cleandb; cd ..;\
	  fi \
	done

# Subdirclean for bdl tree
subdirbdlclean : 
	@for d in $(SUBDIRS); do \
	  if test -d $$d; then \
	    cd $$d; $(MAKE) cleanbdl; cd ..;\
	  fi \
	done

libidlmake : $(LIBRARY)
	@if test ! -h ../$(LIBRARY); then \
	  cd ..;ln -s idl/$(LIBRARY) $(LIBRARY); \
	fi

#	mv $(LIBRARY) ..

BDLLIBDIR = $(libdir)/$(machsubname)
# Archivation of client code
INSTALLEDADDCLIENTLIB = $(addprefix $(BDLLIBDIR)/, $(CLIENTLIBRARY))
libclientinstall: $(INSTALLEDADDCLIENTLIB)

libclientmake : $(CLIENTLIBRARY)

addlibclientinstall: $(INSTALLEDADDCLIENTLIB)

$(CLIENTLIBRARY) : $(addprefix client/,$(BDLCONSTANTSCLIENTOBJECTS) $(BDLSNAPSHOTSCLIENTOBJECTS))
	cd client;$(AR_LINK) $(CLIENTLIBRARY) $(BDLCONSTANTSCLIENTOBJECTS) $(BDLSNAPSHOTSCLIENTOBJECTS);cd ..
ifneq ($(TEMPLATELINKDIR),none)
	@if test -d client/$(TEMPLATELINKDIR); then \
	  cd client; $(AR_LINK) $(CLIENTLIBRARY) $(TEMPLATELINKDIR)/*.o; \
	fi
endif

$(INSTALLEDADDCLIENTLIB) : $(addprefix client/,$(BDLCONSTANTSCLIENTOBJECTS) $(BDLSNAPSHOTSCLIENTOBJECTS))
	cd client;$(AR_LINK) $(INSTALLEDADDCLIENTLIB) $(BDLCONSTANTSCLIENTOBJECTS) $(BDLSNAPSHOTSCLIENTOBJECTS);cd ..
ifneq ($(TEMPLATELINKDIR),none)
	@if test -d client/$(TEMPLATELINKDIR); then \
	  cd client; $(AR_LINK) $(INSTALLEDADDCLIENTLIB) $(TEMPLATELINKDIR)/*.o; \
	fi
endif

# Archivation of server code
INSTALLEDADDSERVERLIB = $(addprefix $(BDLLIBDIR)/, $(SERVERLIBRARY))
libserverinstall: $(INSTALLEDADDSERVERLIB)

libservermake : $(SERVERLIBRARY)

addlibserverinstall: $(INSTALLEDADDSERVERLIB)

$(SERVERLIBRARY) : $(addprefix server/,$(BDLCONSTANTSSERVEROBJECTS) $(BDLSNAPSHOTSSERVEROBJECTS))
	cd server;$(AR_LINK) $(SERVERLIBRARY) $(BDLCONSTANTSSERVEROBJECTS) $(BDLSNAPSHOTSSERVEROBJECTS) $(BDLDDLOBJECTS);cd ..
ifneq ($(TEMPLATELINKDIR),none)
	@if test -d server/$(TEMPLATELINKDIR); then \
	  cd server; $(AR_LINK) $(SERVERLIBRARY) $(TEMPLATELINKDIR)/*.o; \
	fi
endif

$(INSTALLEDADDSERVERLIB) : $(addprefix server/,$(BDLCONSTANTSSERVEROBJECTS) $(BDLSNAPSHOTSSERVEROBJECTS))
	cd server;$(AR_LINK) $(INSTALLEDADDSERVERLIB) $(BDLCONSTANTSSERVEROBJECTS) $(BDLSNAPSHOTSSERVEROBJECTS) $(BDLDDLOBJECTS);cd ..
ifneq ($(TEMPLATELINKDIR),none)
	@if test -d server/$(TEMPLATELINKDIR); then \
	  cd server; $(AR_LINK) $(INSTALLEDADDSERVERLIB) $(TEMPLATELINKDIR)/*.o; \
	fi
endif

$(INSTALLEDADDSERVERLIB) : $(addprefix server/,$(BDLDDLOBJECTS))

ifeq ($(HAVECORBA),all)
#bdlclient : bdlprecompile bdlidlcompile $(BDLIDLINSTALL) \
# bdlclientcompile $(CLIENTLIBMAKE) $(BDLCLIENTINSTALL)
bdlclient : bdlprecompile $(BDLIDLMAKE) $(BDLIDLINSTALL) bdlclientcompile \
 $(CLIENTLIBMAKE) $(BDLCLIENTINSTALL)
bdlsclient : bdlsprecompile $(BDLIDLMAKE) $(BDLIDLINSTALL) bdlclientcompile \
 $(CLIENTLIBMAKE) $(BDLCLIENTINSTALL)
else
 bdlclient : bdlprecompile bdlclientcompile $(CLIENTLIBMAKE) \
  $(BDLCLIENTINSTALL)
 bdlsclient : bdlsprecompile bdlclientcompile $(CLIENTLIBMAKE) \
  $(BDLCLIENTINSTALL)
endif

# Taken out bdlobjyinit
bdlserver : bdlservercompile $(SERVERLIBMAKE) $(BDLSERVERINSTALL)
	@echo "Bdl server compilation complete"

bdlprecompile : 
	@$(MKDIRHIER) client server idl
ifneq ($(BDLCONSTANTS),)
	@for d in $(BDLCONSTANTS); do \
	  $(MAKE) bdlidlconstants BDLNAME=$$d; \
	done
endif

bdlsprecompile :
	@$(MKDIRHIER) client server idl
ifneq ($(BDLSNAPSHOTS),)
	@for d in $(BDLSNAPSHOTS); do \
	  $(MAKE) bdlidlsnapshots BDLNAME=$$d; \
	done
endif
	@echo "Bdl client precompilation complete"


bdlclientcompile : 
ifneq ($(BDLCONSTANTS),)
	@for d in $(BDLCONSTANTS); do \
	  cd client;$(MAKE)  -f ../Makefile bdlconstclientobjects BDLNAME=$$d;cd ..; \
	done
endif
ifneq ($(BDLSNAPSHOTS),)
	@for d in $(BDLSNAPSHOTS); do \
	  cd client;$(MAKE)  -f ../Makefile bdlsnapclientobjects BDLNAME=S_$$d;cd ..; \
	done
endif
	@echo "Bdl client compilation complete"

bdlservercompile : $(addprefix server/, $(addsuffix .ddl, $(DDLNAMES)))
ifneq ($(DDLNAMES),)
	@for d in $(DDLNAMES); do \
	  cd server;$(MAKE)  -f ../Makefile ddlobject DDLNAME=$$d;cd ..; \
	done
endif
ifneq ($(BDLCONSTANTS),)
	@for d in $(BDLCONSTANTS); do \
	  cd server;$(MAKE)  -f ../Makefile bdlconstserverobject BDLNAME=$$d;cd ..; \
	done
endif
ifneq ($(BDLSNAPSHOTS),)
	@for d in $(BDLSNAPSHOTS); do \
	  cd server;$(MAKE)  -f ../Makefile bdlsnapserverobject BDLNAME=$$d;cd ..; \
	done
endif

#ifneq ($(DBGEXT),$(DEBUG_EXT))
#bdlobjyinit : 
#	@for d in $(BDLCONSTANTS); do \
#	  cd server;$(MAKE)  -f ../Makefile bdldbinit BDLNAME=$$d;cd ..; \
#	done
#else
#bdlobjyinit :
#	@echo No debug dbinit applications are made.
#endif

bdlidlcompile : $(addprefix idl/,$(IDLOBJECTS))
	@for d in $(IDLNAMES); do \
	  cd idl;$(MAKE) -f ../Makefile $(BDLIDLLIB) IDLNAME=$$d;cd ..; \
	done

#	  cd idl;$(MAKE) -f ../Makefile addlibinstall IDLNAME=$$d;cd ..; \

#	  cd idl;$(MAKE) -f ../Makefile $(BDLIDLLIB) IDLNAME=$$d;cd ..; \

bdlidlinstall : libinstalldir
	@for d in $(IDLNAMES); do \
	  cd idl;$(MAKE) -f ../Makefile incmachinstall idlinstall libinstall IDLNAME=$$d;cd ..; \
	done
	@echo "IDL installation complete"

bdlclientinstall : bdlclientincinstall libinstalldir
	@cd idl;$(MAKE)  -f ../Makefile incmachinstall;cd ..
	@echo "Client installation complete"

bdlclientincinstall : 
	@cd client;$(MAKE)  -f ../Makefile bdlclientsubincinstall;cd ..

bdlserverinstall : libinstalldir bdlserverincinstall $(BDLDBINITINSTALL)
	@for d in $(DDLNAMES); do \
	  cd server;$(MAKE)  -f ../Makefile ddlinstall DDLNAME=$$d;cd ..; \
	done
	@echo "Server installation complete"

bdlserverincinstall :
	@cd server;$(MAKE)  -f ../Makefile bdlserversubincinstall;cd ..

idlinstall : $(includedir)/idl/$(IDLNAME).idl

$(includedir)/idl/$(IDLNAME).idl : $(IDLNAME).idl
	@$(MKDIRHIER) $(includedir)/idl
	@$(INSTALL_HEADER) $(IDLNAME).idl $(includedir)/idl/$(IDLNAME).idl

INSTALLEDCLIENTHEADERS = $(addprefix $(LIBCLIENTINCLUDE)/, $(CLIENTHEADERS))
DUMMYCLIENTHEADER = $(addprefix $(LIBCLIENTINCLUDE)/, clientnone)

clientnone : none

bdlclientsubincinstall : $(INSTALLEDCLIENTHEADERS) libpackagefile
	@echo "BDL Client Header installed."
ifneq (none$(PACKAGEREGISTER),none)
	@touch $(PACKAGEREGISTER)/packages.names
	@cp $(PACKAGEREGISTER)/packages.names $(src_root)/names.libs
	@echo "$(CLIENTLIB)" >> $(src_root)/names.libs
	@sort -u -r $(src_root)/names.libs >$(src_root)/packages.names
	@echo "" >>$(src_root)/packages.names
	@cp $(src_root)/packages.names $(PACKAGEREGISTER)/packages.names
	@rm -f $(src_root)/names.libs $(src_root)/packages.names
endif

$(DUMMYCLIENTHEADER) $(INSTALLEDCLIENTHEADERS) : $(LIBCLIENTINCLUDE)/% : %
	@$(MKDIRHIER) $(LIBCLIENTINCLUDE)
	@for p in $?; do \
	  $(INSTALL_HEADER) $$p $(LIBCLIENTINCLUDE)/$$p; \
	done

INSTALLEDSERVERHEADERS = $(addprefix $(LIBSERVERINCLUDE)/, $(SERVERHEADERS))
DUMMYSERVERHEADER = $(addprefix $(LIBSERVERINCLUDE)/, servernone)

servernone : none

bdlserversubincinstall : $(INSTALLEDSERVERHEADERS) libpackagefile
	@echo "BDL Server Header installed."
ifneq (none$(PACKAGEREGISTER),none)
	@touch $(PACKAGEREGISTER)/packages.names
	@cp $(PACKAGEREGISTER)/packages.names $(src_root)/names.libs
	@echo "$(SERVERLIB)" >> $(src_root)/names.libs
	@sort -u -r $(src_root)/names.libs >$(src_root)/packages.names
	@echo "" >>$(src_root)/packages.names
	@cp $(src_root)/packages.names $(PACKAGEREGISTER)/packages.names
	@rm -f $(src_root)/names.libs $(src_root)/packages.names
endif

INSTALLEDBDLDBINIT = $(addprefix $(bindir)/, $(BDLDBINIT)) 
bdldbinitinstall : $(INSTALLEDBDLDBINIT)
 
$(INSTALLEDBDLDBINIT) : $(addprefix server/,$(BDLDBINIT))
	@$(MKDIRHIER) $(bindir)
	@for p in $(BDLDBINIT); do \
	  cd server; $(INSTALL_PROGRAM) $$p $(bindir); cd ..; \
	done

$(DUMMYSERVERHEADER) $(INSTALLEDSERVERHEADERS) : $(LIBSERVERINCLUDE)/% : %
	@$(MKDIRHIER) $(LIBSERVERINCLUDE)
	@for p in $?; do \
	  $(INSTALL_HEADER) $$p $(LIBSERVERINCLUDE)/$$p; \
	done

# UPINSTALLEDMACHHEADERS = $(addprefix $(LIBMACHINCLUDE)/, $(MACH_HEADERS))

DDLINCLUDE = $(includedir)/ddl

# Install ddl files
ddlinstall : $(DDLINCLUDE)/$(notdir $(DDLNAME)).ddl
	@echo "ddl installation complete"

ifneq ($(DDLINSTALL),)
$(DDLINCLUDE)/$(notdir $(DDLNAME)).ddl : $(DDLNAME).ddl
	@$(MKDIRHIER) $(DDLINCLUDE)
	$(INSTALL_HEADER) $(DDLNAME).ddl $(DDLINCLUDE)/$(notdir $(DDLNAME)).ddl
endif

# Install ddl files from bdl compilations
INSTALLEDBDLDDLFILES = $(addprefix $(DDLINCLUDE)/, $(addsuffix .ddl, $(DDLNAMES)))
bdlddlinstall : $(INSTALLEDBDLDDLFILES)

$(INSTALLEDBDLDDLFILES) : $(addsuffix .ddl, $(DDLNAMES))
	@$(MKDIRHIER) $(DDLINCLUDE)
	for p in $(addsuffix .ddl, $(DDLNAMES)); do \
	  $(INSTALL_HEADER) $$p $(DDLINCLUDE)/$$p; \
	done
	@echo "bdl ddl installation complete"

# Some explicit dependencies from bdl compilations
# (obsolete if makedepend is updated for bdl)
IDLSAVENAME:=$(IDLNAME)
IDLNAME:=$(COM_INCS)/$(machsubname)/CLEORB/Time
TIME_HH:=$(IDLHEADERS)
IDLNAME:=$(COM_INCS)/$(machsubname)/CLEORB/DBVersion
DBVVERSION_HH:=$(IDLHEADERS)
IDLNAME:=$(IDLSAVENAME)

DB$(BDLNAME)$(DOTO) : DB$(BDLNAME).hh
DB$(BDLNAME)$(DOTO) : $(COM_INCS)/version/VersionInfo.hxx
DB$(BDLNAME)$(DOTO) : $(COM_INCS)/time/CleoTimeBase.hxx
DB$(BDLNAME)$(DOTO) : $(COM_INCS)/version/VersionSelect.hxx
DB$(BDLNAME)$(DOTO) : $(COM_INCS)/ConstantsUtility/CLEOConstants.hxx
DB$(BDLNAME)$(DOTO) : $(COM_INCS)/ConstantsUtility/CLEOConstBase.hxx

DBS_$(BDLNAME)$(DOTO) : DBS_$(BDLNAME).hh
DBS_$(BDLNAME)$(DOTO) : $(COM_INCS)/version/VersionInfo.hxx
DBS_$(BDLNAME)$(DOTO) : $(COM_INCS)/time/CleoTimeBase.hxx
DBS_$(BDLNAME)$(DOTO) : $(COM_INCS)/version/VersionSelect.hxx
DBS_$(BDLNAME)$(DOTO) : $(COM_INCS)/versionutil/VersionSelectUtility.hxx

DB$(BDLNAME)Utilities$(DOTO) : DB$(BDLNAME).hh
DB$(BDLNAME)Utilities$(DOTO) : DB$(BDLNAME)Utilities.hh
DB$(BDLNAME)Utilities$(DOTO) : $(COM_INCS)/$(machsubname)/CLEORB/CLEORB.hxx
DB$(BDLNAME)Utilities$(DOTO) : $(COM_INCS)/idl/Time.idl
DB$(BDLNAME)Utilities$(DOTO) : $(COM_INCS)/idl/DBVersion.idl
DB$(BDLNAME)Utilities$(DOTO) : $(TIME_HH)
DB$(BDLNAME)Utilities$(DOTO) : $(DBVERSION_HH)
DB$(BDLNAME)Utilities$(DOTO) : $(COM_INCS)/version/VersionInfo.hxx
DB$(BDLNAME)Utilities$(DOTO) : $(COM_INCS)/basics/bsobject.hxx

DB$(BDLNAME)Factory$(DOTO) : DB$(BDLNAME).hh
DB$(BDLNAME)Factory$(DOTO) : DB$(BDLNAME)Factory.hh
DB$(BDLNAME)Factory$(DOTO) : DB$(BDLNAME)Utilities.hh
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/$(machsubname)/CLEORB/CLEORB.hxx
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/idl/Time.idl
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/idl/DBVersion.idl
DB$(BDLNAME)Factory$(DOTO) : $(DBVERSION_HH)
DB$(BDLNAME)Factory$(DOTO) : $(TIME_HH)
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/basics/bsobject.hxx
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/version/VersionInfo.hxx
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/versionutil/VersionInfoUtility.hxx
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/time/CleoTimeBase.hxx
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/timeutil/CleoTime.hxx
DB$(BDLNAME)Factory$(DOTO) : $(COM_INCS)/ConstantsUtility/DBConstants.hxx

ifeq ($(CONSTANTS_DDL_PREFIX),CODI)
 CODI$(BDLNAME)_new$(DOTO) : CODI$(BDLNAME).hh
 CODI$(BDLNAME)_new$(DOTO) : $(COM_INCS)/Codi/CODIHandle.h
 CODI$(BDLNAME)_new$(DOTO) : $(COM_INCS)/Codi/CODIVersion.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/Codi/CODIThread.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/Codi/Credentials.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/Codi/CODIHandle.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/Codi/CODIVersion.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/Codi/CODIVGraph.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/Codi/ObjyDriver.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/Codi/Session.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/ObjyUtility/ObjySession.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/BDLserver/MetaVersionConstantsServer.hh
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/BDLserver/CODIMetaVersion.hh
# $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/BDLserver/MetaBaseConstantsServer.h
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/BDLserver/BaseConstantsServer.h
else
 CleoConstants$(BDLNAME)_new$(DOTO) : CleoConstants$(BDLNAME).hh
 CleoConstants$(BDLNAME)_new$(DOTO) : $(COM_INCS)/$(machsubname)/CleoConstantsDB/CleoConstantsDB.hh
 $(BDLNAME)ConstantsServer$(DOTO) : $(BDLNAME)ConstantsServerNew.hh
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/CleoConstantsDB/ConstantsDBThread.hxx
 $(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/CleoConstantsDB/CleoBaseConstantsServer.hxx
endif

$(BDLNAME)ConstantsServer$(DOTO) : $(BDLNAME)ConstantsServer.hh
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/$(machsubname)/CLEORB/CLEORB.hxx
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/basics/console.hxx
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/basics/bsobject.hxx
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/time/CleoTimeBase.hxx
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/timeutil/CleoTime.hxx
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/timeutil/CleoTimeDB.hxx
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/ConstantsUtility/BootString.hxx
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/idl/DBVersion.idl
$(BDLNAME)ConstantsServer$(DOTO) : $(COM_INCS)/idl/Time.idl
$(BDLNAME)ConstantsServer$(DOTO) : $(TIME_HH)
$(BDLNAME)ConstantsServer$(DOTO) : $(DBVERSION_HH)

S_$(BDLNAME)SnapshotServer$(DOTO) : S_$(BDLNAME)SnapshotServer.hh
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/$(machsubname)/CLEORB/CLEORB.hxx
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/basics/console.hxx
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/basics/bsobject.hxx
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/time/CleoTimeBase.hxx
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/timeutil/CleoTime.hxx
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/ConstantsUtility/BootString.hxx
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/ObjyUtility/ObjySession.h
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/idl/DBVersion.idl
S_$(BDLNAME)SnapshotServer$(DOTO) : $(COM_INCS)/idl/Time.idl
S_$(BDLNAME)SnapshotServer$(DOTO) : $(TIME_HH)
S_$(BDLNAME)SnapshotServer$(DOTO) : $(DBVERSION_HH)

# online database init script installation
ifeq ($(HAVEOBJY),all)
# Special rule for reference database
# onlinedbinitscriptinstall: Installs the shell script $(ONLINEDBINITSCRIPT)
# to be used to create own copy of reference FD.
onlinedbinitscriptinstall : $(bindir)/$(ONLINEDBINITSCRIPT)

$(bindir)/$(ONLINEDBINITSCRIPT) : $(ONLINEDBINITSCRIPT)
	@$(INSTALL) $(ONLINEDBINITSCRIPT) $(bindir)/

else
onlinedbinitscriptinstall : notAvailable
endif

# rules for idl2java and subsequent compilation
# and installation of generated java/class files
ifneq ($(ORBJAVA),missing)
javaidlcompile :
	@$(RM) -f  *tmp*
	@for d in `echo $(SUBDIRS)`; do \
	  echo "#include \"$$d.idl\"" >> tmp.idl ; \
	done
	@for d in `echo $(COMMONIDLS)`; do \
	  echo "#include \"$$d.idl\"" >> tmp.idl ; \
	done

	$(ORBJAVA) $(ORBJAVAFLAGS) \
		-idl2package ::Time edu.osu.daqiii.Time \
		-idl2package ::DBVersion edu.osu.daqiii.DBVersion \
		-idl2package ::RunControl edu.osu.daqiii.RunControl \
		-idl2package ::HVDetectorMapDBModule edu.cornell.cleo3bdl.HVDetectorMapDBModule \
		-package "$(JAVAPACKAGE)" tmp.idl > tmp.log

	@find . -name "*.java" -newer tmp.idl > tmp_changes_java

	@if [ -s tmp_changes_java ] ; then \
	  echo $(JAVACIDL) @tmp_changes_java ; \
	  $(JAVACIDL) -J-Xms32m -J-Xmx64m -classpath . $(JIDLFLAGS) @tmp_changes_java ; \
	fi

javaidlinstall :
	@echo "Installing class files"
	@$(MKDIRHIER) $(prefix)/classes
	@find . -name "*.class" > tmp_all_class
	@tar cf - -I tmp_all_class | ( cd $(prefix)/classes ; tar xf -)
else
javaidlcompile : notAvailable
javaidlinstall : notAvailable
endif

alljavahelp :
	@cd help; $(JAVAHELP_INDEXER) $(JAVAHELP_INDEX); cd ..

ifneq ($(JAVAHELP_INDEX),)
JAVAHELPSEARCH = $(shell echo help/JavaHelpSearch | sed '$(java_root_transform)' )
JAVAHELP_CONTENT_FILES = $(shell find help -name '*.html' -print )
# list of sources to be passed to the jar command.
JAVAHELP_SOURCE_LIST = $(shell cd .. ; find $(JHBASEDIR)/help -name CVS -prune -o -type f -print )
JAVAHELP_SOURCE_DEP = $(shell find help -name CVS -prune -o -type f -print )
endif

JAVAHELP_SEARCH_FILES = \
	$(JAVAHELPSEARCH)/DOCS \
	$(JAVAHELPSEARCH)/DOCS.TAB \
	$(JAVAHELPSEARCH)/OFFSETS \
	$(JAVAHELPSEARCH)/POSITIONS \
	$(JAVAHELPSEARCH)/SCHEMA \
	$(JAVAHELPSEARCH)/TMAP

$(JAVAHELP_SEARCH_FILES) : $(JAVAHELP_CONTENT_FILES)
	@echo Making search index
	@$(MAKE) alljavahelp

makeJavahelp : $(JAVAHELP_SEARCH_FILES)

installJavahelp : $(CLEO3GUIHELPJAR_NOTRANS)

$(CLEO3GUIHELPJAR_NOTRANS) : $(JAVAHELP_SEARCH_FILES) $(JAVAHELP_SOURCE_DEP)
	@echo "Installing javaHelp files in Cleo3 javaHelp jar archive"
	@$(MKDIRHIER) $(prefix)/classes/help
	@if [ -f $(prefix)/classes/help/cleo3GUIhelp.jar ] ; then \
	  (cd ..; jar uf $(CLEO3GUIHELPJAR) $(JAVAHELP_SOURCE_LIST)) ; \
	else \
	  (cd ..; jar cf $(CLEO3GUIHELPJAR) $(JAVAHELP_SOURCE_LIST)); \
	fi

# Need two versions of the path here: One for the Makefile (unix syntax) and one
# for the jar command (OS syntax, which is only different from unix on Win32)
CLEO3GUIHELPJAR_NOTRANS = $(prefix)/classes/help/cleo3GUIhelp.jar
CLEO3GUIHELPJAR = $(shell echo $(CLEO3GUIHELPJAR_NOTRANS) | sed '$(java_root_transform)' )

# Set guard
GUARD_MAKEFILE = Makefile


# Guard Makefile
$(GUARD_MAKEFILE) : $(GUARD_MAKEFILE).in $(src_root)/config.status
	cd $(src_root); ./config.status

config.status : $(src_root)/configure
	cd $(src_root); ./config.status --recheck
