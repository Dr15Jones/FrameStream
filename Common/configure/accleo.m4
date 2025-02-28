dnl
dnl Local M4 file to setup CLEOIII CORBA tree with configure
dnl
dnl Recognized Operating systems: UNIX, WindowsNT, VxWorks
dnl
dnl Checks also for some bugs on:
dnl - OSF
dnl - SunOS
dnl
dnl $Id: accleo.m4,v 1.146 2002/02/19 22:23:05 hubert Exp $
dnl


dnl ----------------------------------------------------------------
dnl Find the correct C compiler
AC_DEFUN(AC_PROG_ALLCC,
[
AC_LANG_SAVE
AC_LANG_C

dnl force GNU compiler
AC_ARG_WITH(gcc,
 [  --with-gcc	Use always GNU gcc as compiler],
 ac_gcc_force=yes,
 ac_gcc_force=no)

AC_SUBST(CC)dnl
AC_SUBST(CFLAGS)dnl
AC_SUBST(EXTCFLAGS)dnl
CC=""
CFLAGS=""
EXTCFLAGS=""
AC_SUBST(GNUEXT)dnl
GNU_EXT=""

if test $target = $host; then

  if test $ac_gcc_force = yes; then
    CC="gcc"
    dnl GNUEXT=_g
    dnl AC_DEFINE(HAVE_EXTRA_GNUEXTENSION, 1)
  fi

  AC_CHECKING(for C compiler)
  if test -z "$CC" ; then
    AC_CHECK_PROGS(CC, cc CL gcc, )
  fi
  if test $CC = "CL" ; then
    CFLAGS="/TC /nologo"
    CPP="$CC /TC /EP /nologo"
  elif test $CC = "gcc" ; then
    CFLAGS="-ansi"
  fi
else
  AC_CHECKING(for C cross compiler)
  if test $target_os = vxworks; then
    if test $target_cpu = powerpc; then
      AC_CHECK_PROGS(CC, ccppc, missing)
      if test $CC = missing; then
        AC_MSG_ERROR([VxWorks environment not set up correctly...])
      fi

      case "$target_vendor" in
	PPC604) ac_cpu="PPC604";;
	PPC603) ac_cpu="PPC603";;
	PPC403) ac_cpu="PPC403";;
	*) echo "Unknown CPU version"; exit;;
      esac

      CPPFLAGS="-Dgcc272 -DVXWORKS -D__vxworks -DTHREAD -DCPU=$ac_cpu -I$WIND_BASE/target/h -I$CLEOSTANDARD/ppc"
dnl      CFLAGS="$CPPFLAGS -ansi -fno-builtin -nostdinc -fvolatile -c"
      CFLAGS="$CPPFLAGS -ansi -fno-builtin -nostdinc -c"
    elif test $target_cpu = m68k; then
      AC_CHECK_PROGS(CC, cc68k, missing)
      if test $CC = missing; then
        AC_MSG_ERROR([VxWorks environment not set up correctly...])
      fi

      case "$target_vendor" in
	MC68LC040) ac_cpu="MC68LC040 -m68040 -msoft-float";;
	MC68040) ac_cpu="MC68040 -m68040";;
	MC68030) ac_cpu="MC68020 -m68030";;
	MC68020) ac_cpu="MC68020 -m68020";;
	*) echo "Unknown CPU version"; exit;;
      esac

      CPPFLAGS="-Dgcc272 -DVXWORKS -D__vxworks -DTHREAD -DCPU=$ac_cpu -I$WIND_BASE/target/h -I$CLEOSTANDARD/68k"
      CFLAGS="$CPPFLAGS -ansi -fno-builtin -nostdinc -c"
    else
      AC_MSG_ERROR([Don't know how to handle that target CPU...])
    fi
  else
    AC_MSG_ERROR([Don't know how to handle that target...])
  fi
fi

dnl check for C preprocessor
AC_PROG_CPP

AC_LANG_RESTORE
])


dnl ----------------------------------------------------------------
dnl Find the correct C++ compiler
AC_DEFUN(AC_PROG_ALLCXX,
[
AC_LANG_SAVE
AC_LANG_CPLUSPLUS

dnl Position independent switch
AC_ARG_WITH(noposition-independent,
 [  --with-noposition-independent	compile without 'PIC' switch ],
 ac_noposition_independent=yes,
 ac_noposition_independent=no)

AC_SUBST(CSWITCH)dnl
AC_SUBST(OUTSWITCH)dnl
AC_SUBST(TEMPLATEDIR)dnl
AC_SUBST(TEMPLATELINKDIR)dnl

CSWITCH="-c" dnl default
OUTSWITCH="-o" dnl default
TEMPLATEDIR="none" dnl default
TEMPLATELINKDIR="none" dnl default

AC_SUBST(CXX)dnl
AC_SUBST(CXXFLAGS)dnl
AC_SUBST(EXTCXXFLAGS)dnl
AC_SUBST(LDXX)dnl
AC_SUBST(LDXXFLAGS)dnl
AC_SUBST(LD)dnl
AC_SUBST(LDFLAGS)dnl
AC_SUBST(NM)dnl
AC_SUBST(AR)dnl
AC_SUBST(AR_LINK)dnl
AC_SUBST(TAR_INCLUDE_OPT)dnl
CXX=""
CXXFLAGS=""
EXTCXXFLAGS=""
LDXX="\${CXX}"
LDXXFLAGS="-o"
LD=""
LDFLAGS=""
NM="nm"
AR="ar"
AR_LINK="ar rv"
TAR_INCLUDE_OPT="-I"

ac_cxx_isgnu=no

if test $target = $host; then

  if test $ac_gcc_force = yes; then
    CXX="g++"
  fi

  AC_CHECKING(for C++ compiler)
  if test -z "$CXX" ; then
    AC_CHECK_PROGS(CXX, c++ cxx CC CL g++ gcc, )
  fi

  dnl Sun WorkShop compiler
  if test $CXX = CC; then
    AC_MSG_RESULT(Use Sun WorkShop C++ compiler) 
    dnl Check compiler version
    rm -f tmp_ver
    CC -V 1> tmp_ver 2>&1 
    ac_cxx_version="`head -1 tmp_ver`"
    case "$ac_cxx_version" in
     *4.2*)
	ac_template_path="Templates\$(DBGEXT)"
 	TEMPLATEDIR="Templates\$(DBGEXT)/Templates.DB"
	CXXFLAGS="$CXXFLAGS -ptr$ac_template_path -DOS_NO_ALLOCATORS"
        AC_DEFINE(TYPENAME_NOT_RECOGNIZED, 1)
	LDXXFLAGS="-ptr$ac_template_path $LDXXFLAGS"
        AR_LINK="CC -ptr$ac_template_path -xar -o";;
     *5.*)
	TEMPLATEDIR="SunWS_cache"
	AR_LINK="CC -xar -o"
	AC_DEFINE(CXX_USE_STD_NAMESPACE, 1);;
    esac
    rm -f tmp_ver

    AC_MSG_CHECKING(whether '-PIC' option should be used)
    if test $ac_noposition_independent = no; then
      EXTCFLAGS="$EXTCFLAGS -KPIC"
      EXTCXXFLAGS="$EXTCXXFLAGS -KPIC"
      AC_MSG_RESULT(yes)
    else
      AC_MSG_RESULT(no)
    fi

    dnl UltraSparc optimizations
    AC_MSG_CHECKING(whether we compile for UltraSparcII target)
    AC_ARG_ENABLE(ultrasparc2,
     [  --enable-ultrasparc2	enable optimizations for UltraSparc2 (default = no)],
     ac_cxx_ultrasparc=yes,
     ac_cxx_ultrasparc=no)
    AC_MSG_RESULT($ac_cxx_ultrasparc)
    if test $ac_cxx_ultrasparc = yes; then
      ac_cxx_ultrasparc_flags="-xtarget=ultra2 -xcache=16/32/1:256/64/1"
      CXXFLAGS="$CXXFLAGS $ac_cxx_ultrasparc_flags"
      LDXXFLAGS="$ac_cxx_ultrasparc_flags $LDXXFLAGS"
    fi

  dnl Microsoft Visual C++ compiler for Win32
  elif test $CXX = CL; then
    AC_MSG_RESULT(Use Microsoft Visual C++ compiler)
    CXXFLAGS="/TP /DWIN32 /GX /G6 /Zm400 /nologo"
    CXXCPP="$CXX /TP /EP /nologo"
    CSWITCH="/c"
    OUTSWITCH="/Fo"
    LDXXFLAGS="/nologo /opt:ref /nodefaultlib:libc"
    TAR_INCLUDE_OPT="-T"

  dnl Compaq C++ for Alpha
  elif test $CXX = cxx; then
    AC_MSG_RESULT(Use Compaq C++ compiler for Alpha)
    AC_DEFINE(CXX_USE_STD_NAMESPACE, 1)
    CSWITCH="-Hf"
    LDXXFLAGS="-call_shared $LDXXFLAGS"
    dnl force creation of template object code
    ac_template_path="Templates\$(DBGEXT)"
    TEMPLATEDIR="Templates\$(DBGEXT)"
    TEMPLATELINKDIR="Templates\$(DBGEXT)"
    CXXFLAGS="$CXXFLAGS -ptr $ac_template_path"
    LDXXFLAGS="-ptr $ac_template_path $LDXXFLAGS "
    AC_MSG_CHECKING(whether '-PIC' option should be used)
    if test $ac_noposition_independent = no; then
      EXTCFLAGS="$EXTCFLAGS -kPIC"
      EXTCXXFLAGS="$EXTCXXFLAGS -kPIC"
      AC_MSG_RESULT(yes)
    else
      AC_MSG_RESULT(no)
    fi

dnl bug related options
dnl    if test $target = alphaev6-dec-osf4.0f; then
dnl      CXXCPP="$CXXCPP"
dnl    elif test $target = alphaev56-dec-osf4.0f; then
dnl      CXXCPP="$CXXCPP"
dnl    else
dnl      CXXCPP="$CXXCPP -msg_disable nested_comment"
dnl    fi

  dnl GNU compiler
  elif test $CXX = g++ || test $CXX = gcc; then
    AC_MSG_RESULT(Use Gnu C++ compiler)
    ac_cxx_isgnu=yes

    dnl check compiler version
    AC_MSG_CHECKING(GNU compiler version)
    ac_cxx_gnuversion="`$CXX -v 2>&1 | grep 'gcc version' | sed 's/gcc version //'`"
    case "$ac_cxx_gnuversion" in
	*gnu*2.9*)	AC_DEFINE(CXX_USE_STD_NAMESPACE, 1);;
	*egcs*)		AC_DEFINE(CXX_USE_STD_NAMESPACE, 1);;
	*)		AC_MSG_ERROR(Unsupported version $ac_cxx_gnuversion);;
    esac
    AC_MSG_RESULT($ac_cxx_gnuversion)

    case "$target" in
	*-*-osf*)	LDXXFLAGS="-Wl,-call_shared $LDXXFLAGS";;
    esac
  fi

else
  AC_CHECKING(for C++ cross compiler)
  if test $target_os = vxworks; then
    if test $target_cpu = powerpc; then
      AC_CHECK_PROGS(CXX, c++ppc, missing)
      if test $CXX = missing; then
        AC_MSG_ERROR([VxWorks environment not set up correctly...])
      fi
      ac_cxx_isgnu=yes
dnl      CXXFLAGS="$CPPFLAGS -ansi -fno-builtin -nostdinc -c -fvolatile"
      CXXFLAGS="$CPPFLAGS -ansi -fno-builtin -nostdinc -c"
      LD="ldppc"
      NM="nmppc"
      AR="arppc"
      AR_LINK="arppc rv"
    elif test $target_cpu = m68k; then
      AC_CHECK_PROGS(CXX, c++68k, missing)
      if test $CXX = missing; then
        AC_MSG_ERROR([VxWorks environment not set up correctly...])
      fi
      ac_cxx_isgnu=yes
      CXXFLAGS="$CPPFLAGS -ansi -fno-builtin -nostdinc -c"
      LD="ld68k"
      NM="nm68k"
      AR="ar68k"
      AR_LINK="ar68k rv"
    else
      AC_MSG_ERROR([Don't know how to handle that target CPU...])
    fi

    dnl check compiler version
    AC_MSG_CHECKING(GNU compiler version)
    ac_cxx_gnuversion="`$CXX -v 2>&1 | grep 'gcc version' | sed 's/gcc version //'`"
    AC_MSG_RESULT($ac_cxx_gnuversion)
  else
    AC_MSG_ERROR([Don't know how to handle that target...])
  fi
fi

dnl check for C++ preprocessor
AC_PROG_CXXCPP
dnl workaround for autoconf 2.13 bug in
dnl acspecific.m4 AC_PROG_CXXCPP macro
dnl only affects win32 platform
if test $target_os = cygwin ; then
  CXXCPP="$CXX /TP /EP /nologo"
fi

dnl AC_MSG_CHECKING(whether this is a GNU compiler)
dnl AC_MSG_RESULT($ac_cxx_isgnu)

if test $target_os = vxworks; then
  AC_MSG_CHECKING(which link command to use for partial linking)
  AC_MSG_RESULT($LD)
else
  AC_MSG_CHECKING(which link command to use for C++)
  AC_MSG_RESULT($LDXX $LDXXFLAGS)
fi

AC_LANG_RESTORE
])


dnl ----------------------------------------------------------------
dnl Find the right way to make threaded libraries/programs
AC_DEFUN(AC_PROG_CXX_THREADED,
[
AC_REQUIRE([AC_CANONICAL_SYSTEM])
AC_REQUIRE([AC_PROG_ALLCXX])
AC_LANG_SAVE
AC_LANG_CPLUSPLUS

dnl Switches specific to multi-threading
AC_SUBST(MTCOMPILEOPTION)dnl
AC_SUBST(MTLINKOPTION)dnl
AC_SUBST(MTLIBS)dnl
AC_SUBST(MTEXT)dnl
AC_SUBST(SYSLIBS)dnl

MTCOMPILEOPTION=""
MTLINKOPTION=""
MTLIBS=""
MTEXT=""
dnl SYSLIBS=""

if test $target_os = vxworks; then
 dnl Always use multithreaded version
 ac_mt_switch=yes
 ac_prog_cxx_mtswitch=yes
 MTCOMPILEOPTION="-D_REENTRANT -DRW_MULTI_THREAD"
else
 dnl Allow user to select multithreaded compilation
 AC_MSG_CHECKING(for multithreading)
 AC_ARG_ENABLE(mt,
  [  --enable-mt	do multithreaded compilation (default = no)],
  ac_mt_switch=yes,
  ac_mt_switch=no)
 AC_MSG_RESULT($ac_mt_switch)

 if test $ac_mt_switch = yes; then
  MTEXT="_r"
  MTCOMPILEOPTION="-D_REENTRANT"
 fi

 case $target in
	*-*-osf*)
	dnl allow to force DEC threads on OSF
	AC_ARG_WITH(decthreads,
	 [  --with-decthreads	Always use DEC threads on OSF (default = no)],
	 ac_DECthr_force=yes,
	 ac_DECthr_force=no);;
 esac
fi

if test $ac_mt_switch = yes; then
 ac_prog_cxx_mtswitch=no
 AC_MSG_CHECKING(whether we need compilation switches for threads)

 if test $ac_cxx_isgnu = no; then
   case $target in

	*-*-vxworks*)	ac_prog_cxx_mtswitch=yes
			MTCOMPILEOPTION="${MTCOMPILEOPTION} -DRW_MULTI_THREAD";;

	*-*-cygwin)	ac_prog_cxx_mtswitch=yes
			MTCOMPILEOPTION="${MTCOMPILEOPTION} /MT\$(DBGEXT)";;

	*-*-solaris2*)	ac_prog_cxx_mtswitch=yes
			MTCOMPILEOPTION="${MTCOMPILEOPTION} -mt";;

	*-*-osf3*)	ac_prog_cxx_mtswitch=yes
			MTCOMPILEOPTION="${MTCOMPILEOPTION} -D_THREAD_SAFE -threads";;

	*-*-osf4*)	ac_prog_cxx_mtswitch=yes
			if test $ac_DECthr_force = yes; then
			  MTCOMPILEOPTION="${MTCOMPILEOPTION} -D_THREAD_SAFE -threads"
			else
			  MTCOMPILEOPTION="${MTCOMPILEOPTION} -D_THREAD_SAFE -pthread"
			fi;;
   esac
 fi
 CXXFLAGS="$CXXFLAGS ${MTCOMPILEOPTION}"
 AC_MSG_RESULT($MTCOMPILEOPTION)

 AC_MSG_CHECKING(how to link thread library)
 case "$target" in
	*-*-osf*)
	if test $ac_DECthr_force = yes; then
	  ac_option_pthread_link=no
	  LIBS="-lpthreads"
	  AC_TRY_LINK([#include <pthread.h>],[pthread_t pt;pthread_join(pt,NULL)],
	  [ac_option_pthread_link=yes MTLINKOPTION="-threads" MTLIBS="$LIBS"])
	  if test $ac_option_pthread_link = no; then
	    AC_MSG_ERROR([No DECthreads found on this platform!])
	  fi
	elif test $ac_cxx_isgnu = yes; then
	  LIBS="-L/usr/lib/cmplrs/cxx -lcxxstd -lcxx -lexc -lots -lc_r -lpthreads -lmach -lexc -lc_r"
	  AC_TRY_LINK([#include <pthread.h>],[pthread_t pt;pthread_join(pt,NULL)],
	   [ac_option_pthread_link=yes MTLINKOPTION="" MTLIBS="$LIBS"])
	else
	  ac_option_pthread_link=no
	  LIBS="-lpthread"
	  AC_TRY_LINK([#include <pthread.h>],[pthread_t pt;pthread_join(pt,NULL)],
	   [ac_option_pthread_link=yes MTLINKOPTION="-pthread" MTLIBS="$LIBS"])
	  if test $ac_option_pthread_link = no; then
	    ac_option_pthread_link=no
	    LIBS="-lpthreads"
	    AC_TRY_LINK([#include <pthread.h>],[pthread_t pt;pthread_join(pt,NULL)],
	     [ac_option_pthread_link=yes MTLINKOPTION="-threads" MTLIBS="$LIBS"])
	    if test $ac_option_pthread_link = no; then
	      AC_MSG_ERROR([No thread library found on this platform!])
	    fi
	  fi
	fi ;;

 	*-*-solaris*)
 	ac_option_pthread_link=no
 	LIBS="-lpthread"
 	SYSLIBS="$SYSLIBS -lpthread"
 	AC_TRY_LINK([#include <pthread.h>],[pthread_t pt;pthread_join(pt,NULL)],
 	 [ac_option_pthread_link=yes MTLINKOPTION="-mt" MTLIBS="$LIBS"])
 	if test $ac_option_pthread_link = no; then
 	  AC_MSG_ERROR([No thread library found on this platform!])
 	fi ;;

	*-*-linux-gnu*)
	ac_option_pthread_link=no
	LIBS="$SYSLIBS -lpthread"
	AC_TRY_LINK([#include <pthread.h>],[pthread_t pt;pthread_join(pt,NULL)],
	 [ac_option_pthread_link=yes MTLINKOPTION="" MTLIBS="$LIBS"])
	if test $ac_option_pthread_link = no; then
	  AC_MSG_ERROR([No thread library found on this platform!])
	fi ;;
 esac
 AC_MSG_RESULT($MTLIBS)

 AC_MSG_CHECKING(how to link threaded executable)
 LDXXFLAGS="$MTLINKOPTION $LDXXFLAGS"
 AC_MSG_RESULT($MTLINKOPTION)
fi

AC_LANG_RESTORE
])


dnl ----------------------------------------------------------------
dnl Check if we can make C++ compiler handle nested enums
AC_DEFUN(AC_PROG_CXX_NESTETD_ENUMS
[
dnl Extra switches for OSF enum bug?
AC_MSG_CHECKING(handles nested enums correctly)
AC_MSG_RESULT(yes)
dnl AC_TRY_COMPILE
dnl -distinguish_nested_enums
dnl -arch host
])

dnl ----------------------------------------------------------------
dnl Check if this C++ compiler handles exceptions correctly
AC_DEFUN(AC_PROG_CXX_EXCP,
[
AC_REQUIRE([AC_PROG_ALLCXX])

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

AC_MSG_CHECKING(whether C++ understands exceptions)

CXXFLAGS_SAVE=$CXXFLAGS
ac_prog_cxx_needinfo=no

if test $ac_cxx_isgnu = yes; then
  case "$ac_cxx_gnuversion" in

dnl older GNU compiler only supported on vxworks
   *cygnus*2.7*)	ac_prog_cxx_needinfo=yes;;

dnl Newer version have them as default
   *gnu*2.9*)		ac_prog_cxx_needinfo=yes;;

   *egcs*)		ac_prog_cxx_needinfo=yes;;

  esac
fi

if test $ac_prog_cxx_needinfo = no; then
  AC_TRY_COMPILE( ,
   [try{int foo=0;}catch(int& bar){int foo=bar;}],
   [ac_prog_cxx_excp=yes] ,
   [ac_prog_cxx_excp=no])
elif test $ac_prog_cxx_needinfo = yes; then
  AC_TRY_COMPILE([#include <typeinfo>],
   [try{int foo=0;}catch(int& bar){int foo=bar;}],
   [ac_prog_cxx_excp=yes] ,
   [ac_prog_cxx_excp=no])
fi

AC_MSG_RESULT($ac_prog_cxx_excp)

if test $ac_prog_cxx_excp = no; then
  CXXFLAGS=$CXXFLAGS_SAVE
fi

AC_MSG_CHECKING(Do we use exceptions for this setup)
if test $target_os = vxworks; then
  ac_prog_cxx_excp=no
  AC_MSG_RESULT(don't use exceptions on vxWorks)
else
  AC_MSG_RESULT($ac_prog_cxx_excp)
  if test $ac_prog_cxx_excp = yes; then
    AC_DEFINE(CXX_HAVE_EXCEPTIONS, 1)
    if test $ac_prog_cxx_needinfo = yes; then
      AC_DEFINE(CXX_NEEDS_TYPEINFO, 1)
    fi
  fi
fi

AC_LANG_RESTORE
])


dnl ----------------------------------------------------------------
dnl Check if this C++ compiler handles exceptions correctly
AC_DEFUN(AC_PROG_CXX_DEP,
[
AC_REQUIRE([AC_PROG_ALLCXX])

AC_MSG_CHECKING(how to get dependencies from compiler)

AC_SUBST_FILE(c_rules)dnl
AC_SUBST_FILE(cxx_rules)dnl
AC_SUBST_FILE(cxx_deprules)dnl
AC_SUBST_FILE(c_deprules)dnl
AC_SUBST_FILE(create_depend)dnl
AC_SUBST(DEPSWITCH)dnl
AC_SUBST(DEPFILEFIELD)dnl

if test $CXX = "CL"; then
  c_rules=$srcdir/Gmake/clc_rules.mh
  cxx_rules=$srcdir/Gmake/clcxx.mh
  cxx_deprules=$srcdir/Gmake/cl_dep.mh dnl Just an empty `touch'
  c_deprules=$srcdir/Gmake/cl_dep.mh dnl Just an empty `touch'
  create_depend=$srcdir/Gmake/touch_depend.mh
  DEPSWITCH="no support"
elif test $ac_cxx_isgnu = yes; then
  c_rules=$srcdir/Gmake/c_rules.mh
  cxx_rules=$srcdir/Gmake/cxx.mh
  cxx_deprules=$srcdir/Gmake/gnu_dep.mh
  c_deprules=$srcdir/Gmake/gnu_cdep.mh
  create_depend=$srcdir/Gmake/finish_depend.mh
  DEPSWITCH="-M"
  DEPFILEFIELD="3"
else
  c_rules=$srcdir/Gmake/c_rules.mh
  cxx_rules=$srcdir/Gmake/cxx.mh
  cxx_deprules=$srcdir/Gmake/cxx_dep.mh
  c_deprules=$srcdir/Gmake/c_dep.mh
  create_depend=$srcdir/Gmake/finish_depend.mh
  if test $CXX = "CC"; then
    DEPSWITCH="-xM1"
    DEPFILEFIELD="3"
  elif test $CXX = "cxx"; then
    DEPSWITCH="-M"
    DEPFILEFIELD="2"
  fi
fi

AC_MSG_RESULT($DEPSWITCH)

dnl Setting linking rule(s)
AC_SUBST_FILE(linkxx_rules)dnl
if test $target_os = vxworks; then
  linkxx_rules=$srcdir/Gmake/vx_munch.mh
else
  if test $CXX = "CL"; then
    linkxx_rules=$srcdir/Gmake/linkcl.mh
  else
    linkxx_rules=$srcdir/Gmake/linkxx.mh
  fi
fi

])


dnl ----------------------------------------------------------------
dnl Find the correct way of creating directory trees.
AC_DEFUN(AC_PROG_MKDIRHIER,
[
AC_CHECK_PROG(MKDIRHIER, mkdirhier, mkdirhier, [mkdir -p])
])

dnl ----------------------------------------------------------------
dnl Find the correct way of finding the path of a command
dnl
dnl
AC_DEFUN(AC_PROG_WHICH,
[
if test $host_os = cygwin ; then
  ac_which_use_type_nopath=no;
  AC_CHECK_PROGS(WHICH, which type, )
  if test "$WHICH" = "type"; then
   AC_MSG_CHECKING(if $WHICH works as epxected)
   WHICH="type -path"
   ac_test_which_sed= `type -path sed`
   if eval "test -f $ac_test_which_sed"; then
     AC_MSG_RESULT(yes)
   else
     AC_MSG_ERROR(no)
   fi
  else
  dnl try the real 'which'
   WHICH="which"
   AC_MSG_CHECKING(if $WHICH works as expected)
   ac_test_which_sed=`which sed`
   if eval "test -f $ac_test_which_sed"; then
     AC_MSG_RESULT(yes)
   else
     AC_MSG_ERROR(no)
   fi
  fi
else dnl UNIX platforms
  ac_which_use_type_nopath=yes;
  AC_MSG_RESULT(using shell safe 'type' command)
fi
])

dnl ----------------------------------------------------------------
dnl Find the correct way of searching directory trees.
dnl
dnl This is needed, since WindowsNT's 'find' is a tool to
dnl search through files, not directories...
dnl
AC_DEFUN(AC_PROG_FIND,
[
AC_CHECK_PROGS(FIND, find, )

dnl Just hack this by hand for NT
if test $target_os = cygwin; then
  FIND="/bin/find"
fi
])



dnl ----------------------------------------------------------------
dnl Check for header clashes in C++
AC_DEFUN(AC_CHECK_CLASH_SYSENT,
[
 AC_REQUIRE([AC_PROG_AWK])
 AC_REQUIRE([AC_PROG_ALLCXX])

 if test $ac_cv_header_unistd_h = yes; then
  if test $ac_cv_header_sysent_h = yes; then
   AC_MSG_CHECKING(whether unistd.h and sysent.h clash)
   AC_TRY_LINK([#include <unistd.h>
#include <sysent.h>],
   [uid_t r=0;uid_t e=0;int tst; tst = setreuid(r,e);],
   [ac_clash_sysent_unistd=0
	AC_MSG_RESULT(no)],
   [ac_clash_sysent_unistd=1,
     AC_DEFINE(CLASH_SYSENT_UNISTD, 1)
     AC_MSG_RESULT(yes)])
  else
   ac_clash_sysent_unistd=0
  fi
 else
  ac_clash_sysent_unistd=0
 fi
])

dnl ----------------------------------------------------------------
dnl Find out exaclty where prototype for 'gethostname' is located
dnl to avoid clash between 'unistd.h' and 'systent.h'
AC_DEFUN(AC_CHECK_GETHOSTNAME,
[
  AC_MSG_CHECKING(whether gethostname is in unistd.h or sysent.h)
  AC_MSG_RESULT(unistd.h)
])

dnl ----------------------------------------------------------------
dnl Check for string reentrant APIs
AC_DEFUN(AC_CHECK_STRTOK,
[
 AC_REQUIRE([AC_PROG_AWK])

 if test $ac_cv_header_string_h = yes; then
   AC_MSG_CHECKING(whether reentrant string API is available)
   if test $target_os = "vxworks"; then
     ac_use_strtok_r=1
     AC_DEFINE(USE_STRTOK_R, 1)
     AC_MSG_RESULT(yes)
   else
     AC_TRY_LINK([#include <string.h>],
     [char* last; char* tst; tst = strtok_r(NULL, NULL, &last);],
     [ac_use_strtok_r=1
       AC_DEFINE(USE_STRTOK_R, 1)
       AC_MSG_RESULT(yes)],
       [ac_use_strtok_r=0
       AC_MSG_RESULT(no)])
   fi
 else
   ac_use_strtok_r=0
 fi
])

dnl ----------------------------------------------------------------
dnl Check where system error number list is defined
AC_DEFUN(AC_CHECK_ERRLIST,
[
 AC_REQUIRE([AC_PROG_AWK])

 AC_MSG_CHECKING(where 'sys_errlist' is defined)
 ac_use_sys_errlist_in_stdio=0
 ac_use_sys_errlist_in_source=0

 AC_TRY_COMPILE(
[ #include <stdio.h> ],
[ sys_errlist[0]; ],
[ ac_use_sys_errlist_in_stdio=1
  AC_DEFINE(USE_SYS_ERRLIST_IN_STDIO_H, 1)
  AC_MSG_RESULT(stdio.h)]
 )

 if test $ac_use_sys_errlist_in_stdio = 0; then
   AC_TRY_COMPILE(
  [ #include <errno.h> ],
  [ sys_errlist[0]; ],
  [ AC_MSG_RESULT(errno.h)],
  [  ac_use_sys_errlist_in_source=1
     AC_DEFINE(USE_SYS_ERRLIST_IN_SOURCE, 1)
     AC_MSG_RESULT(in BASICS code)]
  )
 fi
])

dnl ----------------------------------------------------------------
dnl Check how times are handled
AC_DEFUN(AC_CHECK_TIMELIBS,
[
  AC_REQUIRE([AC_PROG_AWK])
  AC_REQUIRE([AC_PROG_ALLCXX])
  AC_REQUIRE([AC_PROG_CXX_THREADED])

  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_CHECK_HEADERS(time.h)
  AC_LANG_RESTORE

  if test $ac_cv_header_time_h = yes; then
   if test $ac_mt_switch = yes; then
    AC_MSG_CHECKING(whether reentrant time API's are available)
    AC_TRY_LINK([#include <time.h>],
    [struct tm* tst; tst = localtime_r(NULL, NULL);],
    [ac_use_localtime_r=1
      AC_DEFINE(USE_LOCALTIME_R, 1)
      AC_MSG_RESULT(yes)],
      [ac_use_localtime_r=0
      AC_MSG_RESULT(no)])
   else
    ac_use_localtime_r=0
   fi
  else
   ac_use_localtime_r=0
  fi

  AC_ARG_WITH(timezone,
  [  --with-timezone=<string>	Use this string to find local timezone],
  ac_timezone_force=yes,
  ac_timezone_force=no)

  if test $ac_timezone_force = no; then
dnl read local date to get timezone string
   ac_zone_abr=`date | $AWK '{print $[5]}' - `
  else
   ac_zone_abr=$withval
  fi

  AC_MSG_CHECKING(trying to recognize local timezone $ac_zone_abr)

dnl read config file to look for this zone
  ac_time_entry=`grep $ac_zone_abr config.tz`
  ac_time_stnd=`echo $ac_time_entry | $AWK '{print $[1]}' - `
  ac_time_par=`echo $ac_time_entry | $AWK '{print $[3]}' - `

  ac_time_stnd=${ac_time_stnd:-"unknown"}

  echo $ac_time_stnd
  if test $ac_time_stnd = "unknown"; then
dnl explain to user
    AC_MSG_RESULT(Revert to UTC time zone!)
  else
dnl Located known timezone
    AC_DEFINE(FOUND_TIMEZONE, 1)
    AC_DEFINE_UNQUOTED(AC_TIMEZONE_STRING, "$ac_time_par")
  fi
])

dnl ----------------------------------------------------------------
dnl Setup the sed scripts for WindowsNT if needed
AC_DEFUN(AC_PATH_ROOT_SET,
[
AC_SUBST(list_transform)dnl
AC_SUBST(cxx_root_transform)dnl
AC_SUBST(java_root_transform)dnl

changequote(<<, >>)dnl
<<
cxx_root_transform='s/x/x/'
java_root_transform='s/x/x/'
ac_internal_roottransform='s/x/x/'
list_transform='s/x/x/'

if test $target_os = cygwin; then
  list_transform='s+:+;+g'
  cxx_root_transform='s+//[^ ;]*+:&+g;s+://.+&//:+g;s+://++g;s+//:+:+g;s+/+//+g;y+/+\\\\+'
  java_root_transform='s+//[^ ;]*+:&+g;s+://.+&//:+g;s+://++g;s+//:+:+g;s+/+//+g;y+/+\\+'
  ac_internal_root_transform='s+//[^ ;]*+:&+g;s+://.+&//:+g;s+://++g;s+//:+:+g;s+/+//+g;y+/+\\+'
fi

>>
changequote([, ])dnl
])

dnl ----------------------------------------------------------------
dnl Set the file extensions
AC_DEFUN(AC_FILES_EXT_SET,
[
AC_SUBST(DOTO)dnl
AC_SUBST(DOTA)dnl
AC_SUBST(DOTX)dnl
AC_SUBST(LINKLIBOPT)dnl
AC_SUBST(LINKEXT)dnl
AC_SUBST(PRELIB)dnl
AC_SUBST(LIBPATHSEP)dnl
DOTO=.o
DOTA=.a
DOTX=
LINKLIBOPT=-l
PRELIB=lib
LINKEXT=
LINKERFLAGS=
LIBPATHSEP="-L"
if test $target_os = cygwin; then
  DOTO=.obj
  DOTA=.lib
  DOTX=.exe
  LINKLIBOPT=
  PRELIB=
  LINKEXT="$DOTA"
  LIBPATHSEP="-LIBPATH:"
fi
if test $target_os = vxworks; then
  DOTX=.out
fi
])

dnl ----------------------------------------------------------------
dnl Find the 'flavor' of this pthread implementation
AC_DEFUN(AC_CHECK_PTHREAD_ARGS,
[
AC_REQUIRE([AC_PROG_ALLCXX])
AC_REQUIRE([AC_PROG_CXX_THREADED])

if test $ac_mt_switch = yes; then
 AC_LANG_SAVE
 AC_LANG_CPLUSPLUS

 AC_MSG_CHECKING(whether pthread uses 'pthread_startroutine_t')
 ac_func_pthread_startroutine=no

 AC_TRY_COMPILE([#include <pthread.h>],pthread_startroutine_t t;, ac_func_pthread_startroutine=yes)

 if test $ac_func_pthread_startroutine = yes; then
  AC_DEFINE(USE_PTHREAD_START_T, 1)
 else
  case "$target" in
dnl problems with xitman on OSF and solaris
  *-*-osf*)
    AC_DEFINE(USE_HARD_EXIT_CALL, 1);;
  *-*-solaris2*)
    AC_DEFINE(USE_HARD_EXIT_CALL, 1);;
  esac
 fi

 AC_MSG_RESULT($ac_func_pthread_startroutine)
 AC_LANG_RESTORE
fi
])

dnl ----------------------------------------------------------------
dnl Set target macros depending on system flavor
AC_DEFUN(AC_SYSTEM_FLAVOR,
[
AC_REQUIRE([AC_CANONICAL_SYSTEM])
AC_REQUIRE([AC_PROG_CXX_THREADED])

AC_SUBST(ISEMBEDDED)dnl
AC_SUBST(INSTALLEMBEDDED)dnl
AC_SUBST(DEPFILEEMBEDDED)dnl
AC_SUBST(ISNOTEMBEDDED)dnl
AC_SUBST(INSTALLNOTEMBEDDED)dnl
AC_SUBST(DEPFILENOTEMBEDDED)dnl

ISEMBEDDED="notAvailable"
INSTALLEMBEDDED="notAvailable"
DEPFILEEMBEDDED="none"
ISNOTEMBEDDED="notAvailable"
INSTALLNOTEMBEDDED="notAvailable"
DEPFILENOTEMBEDDED="none"

case "$target_os" in
solaris*)
  ISNOTEMBEDDED="all"
  INSTALLNOTEMBEDDED="normalinstall"
  DEPFILENOTEMBEDDED="depend.mh"
        ;;
*vxworks*)
  ISEMBEDDED="all"
  INSTALLEMBEDDED="normalinstall"
  DEPFILEEMBEDDED="depend.mh"
        ;;
esac

AC_SUBST(ONLINEDIRS)dnl
ONLINESED=`echo $libdir| sed "s/\/lib/\/lib\/$target$MTEXT$GNUEXT/"`
ONLINEDIRS="$ONLINESED"
])

dnl ----------------------------------------------------------------
dnl Handle --enable options for debuging
AC_DEFUN(AC_DEBUG_OPTIONS,
[
AC_REQUIRE([AC_PROG_CXX_THREADED])
AC_MSG_CHECKING(for default debug/optimization setup)

AC_SUBST(DEBUG)dnl
AC_SUBST(DEBUG_OPTSW)dnl
AC_SUBST(DEBUG_DBGSW)dnl
AC_SUBST(DEBUG_EXT)dnl
DEBUG=""
DEBUG_OPTSW=""
DEBUG_DBGSW=""
DEBUG_EXT=""

dnl The extension used for names
case "$target" in 
	*-*-vxworks*)	DEBUG_EXT="-g" ;;
	*-*-osf*)	DEBUG_EXT="-g" ;;
	*-*-solaris*)	DEBUG_EXT="-g";;
	*-*-cygwin)	DEBUG_EXT="d" ;;
esac

dnl the actual options used for compiling
if test $ac_cxx_isgnu = yes; then
  if test $ac_prog_cxx_excp = yes; then
    case "$ac_cxx_gnuversion" in
	dnl older GNU compiler can not handle optimization
	dnl this compiler version is only supported on vxWorks
	dnl should never come here because vxworks doesn't use exceptions
	*gnu*2.7*)	DEBUG_OPTSW="-O0";;

	dnl Newer version work fine
	*gnu*2.9*)	DEBUG_OPTSW="-O2";;
	*egcs*)		DEBUG_OPTSW="-O2";;
    esac
  else
    DEBUG_OPTSW="-O2"
  fi
  dnl do not use debug switch on vxworks
  if test $target_os = vxworks; then
    DEBUG_DBGSW="";
  else
    DEBUG_DBGSW="-g";
  fi
elif test $CXX = CC ; then
  DEBUG_OPTSW="-xO2"
  dnl Also keep symbols in exec not doto
  DEBUG_DBGSW="-g -xs"
elif test $CXX = CL ; then
  DEBUG_OPTSW="/O2"
  DEBUG_DBGSW="/Z7"
elif test $CXX = cxx ; then
  DEBUG_OPTSW="-O2"
  DEBUG_DBGSW="-g"
fi

dnl look at switches given at configure time
AC_ARG_ENABLE(debug-output,
 [  --enable-debug-output	debug output functions from 'bsobject' (default = no)],
 ac_cxx_debugout=yes,
 ac_cxx_debugout=no)

AC_ARG_ENABLE(debug-compile,
 [  --enable-debug-compile	'debug' or 'optimize' compilation (default = optimize)],
 ac_cxx_debugopts=debug,
 ac_cxx_debugopts=optimize)

AC_ARG_ENABLE(assert,
 [  --disable-assert		disable assert macros in the code (default = no)],
 ac_cxx_disable_assert=yes,
 ac_cxx_disable_assert=no)

dnl setup default switches
if test $ac_cxx_disable_assert = yes; then
  DEBUG="$DEBUG -DNDEBUG"
fi
if test $ac_cxx_debugout = yes; then
  DEBUG="$DEBUG -D_DEBUG"
fi

if test $ac_cxx_debugopts = optimize; then
  DEBUG="$DEBUG_OPTSW $DEBUG"
else
  DEBUG="$DEBUG_DBGSW $DEBUG"
fi

AC_MSG_RESULT($DEBUG)
])

AC_DEFUN(AC_INSIGHT_PROGS,
[
 AC_REQUIRE([AC_PROG_ALLCXX])

 AC_SUBST(INSIGHT_CXX)dnl
 AC_SUBST(INSIGHT_LDXX)dnl
 AC_SUBST(INSEXT)dnl
 INSIGHT_CXX=
 INSIGHT_LDXX=
 INSEXT="-ins"

 AC_CHECK_PROGS(ac_pre_INSIGHT, insure insight, missing)
 if test $ac_pre_INSIGHT != "missing"; then
   ac_opt_INSIGHT_CXX=`echo $CXX | sed 's/CC//;s/cxx//;s/CL//'`
   ac_opt_INSIGHT_LDXX=`echo $CXX | sed 's/CC//;s/cxx//;s/CL//'`
   INSIGHT_CXX="$ac_pre_INSIGHT -D__INSIGHT__ $ac_opt_INSIGHT_CXX"
   INSIGHT_LDXX="$ac_pre_INSIGHT -D__INSIGHT__ $ac_opt_INSIGHT_LDXX"
 fi
])

AC_DEFUN(AC_RULES_NTSERVICE,
[
 AC_REQUIRE([AC_PROG_ALLCXX])

 AC_MSG_CHECKING(for NT services)

 AC_SUBST(SERVICEOBJ)dnl
 SERVICEOBJ=""

 AC_SUBST_FILE(ntservice_setup)dnl
 AC_SUBST_FILE(NTservicerules)dnl
 NTservicerules=""
 ntservice_setup=""

 if test $target_os = cygwin; then
  NTservicerules="Gmake/service_nt_tail.mh"
  ntservice_setup=$srcdir/Gmake/service_nt_tail.mh
  SERVICEOBJ="NTservice\$(DOTO)"
  AC_MSG_RESULT(yes)
 else
  AC_MSG_RESULT(no)
 fi
])

dnl Read library file and create array entries for awk script
AC_DEFUN(AC_DEPENDDIRLIST,
[
 AC_REQUIRE([AC_PROG_AWK])

 AC_SUBST_FILE(SETUPBASEDIRLIST)dnl
 SETUPBASEDIRLIST=""
 ac_dep_check_arg=`echo $1 | $AWK '{print $[1]}' - `

 if test $ac_dep_check_arg = none; then
   AC_MSG_RESULT(skipping library dependency check)
   SETUPBASEDIRLIST="/dev/null"   
 else

  AC_MSG_CHECKING(generating base library dependency list)
  changequote(<<, >>)dnl

dnl Copy all entries into a single file
  rm -f tmp1.dep
  for fl in $1; do
   cat "$COM_GMAKE/${fl}.libs" >>tmp1.dep
  done

dnl Extract all unique entries and create array for
dnl AWK script BEGIN section.
dnl We sort 'reversed' so that entries starting with '$'
dnl show up last. These entries are CORBA/Platform related
dnl headers
  rm -f tmp2.dep
  cat tmp1.dep | sort -r -u | $AWK '{printf("externList[%d]= scincs \"/%s\";\nexternDir[%d]= \"%s\";\n", cnt, $<<0>>, cnt, $<<0>>); ++cnt;}' cnt=0 - >>tmp2.dep
  ac_int_count=`tail -1 tmp2.dep | $AWK -F[\]\[] '{tmp=$<<2>>+1; print tmp;}' -`
  rm -f tmp1.dep

dnl Now replace one of the 'machsubname' strings with
dnl the real name ($target), so we can find them in the result file
dnl of the dependency run with the C++ compiler.
  rm -f tmp.dep
  ac_dep_target_replace="s;/$(machsubname);/$target;"
dnl DEBUG  echo $ac_dep_target_replace
  cat tmp2.dep | sed 's./".".' | sed $ac_dep_target_replace >tmp.dep

  rm -f tmp2.dep

  changequote([, ])dnl
  AC_MSG_RESULT(got $ac_int_count entries)
  SETUPBASEDIRLIST=tmp.dep

 fi
])

AC_DEFUN(AC_DEPENDEXTRADIRLIST,
[

dnl Make correct array for AWK script from file in COM_GMAKE
dnl and user provided name
  rm -f tmpe.dep
  for fl in $1; do

   if eval "test -f ${fl}"; then
     cat ${fl} >>tmpe.dep
   else
    if eval "test -f $COM_GMAKE/${fl}"; then
     cat $COM_GMAKE/${fl} >>tmpe.dep
    else
     echo "Could not find ${fl}"
    fi
   fi

  done

  changequote(<<, >>)dnl

  cnt=0;
  rm -f tmpr.dep
  cat tmpe.dep | $AWK '{printf("exactDir[%d]= \"%s\";\nexactHeader[%d]= \"%s\";\n", cnt,$<<1>>,cnt,$<<2>>); ++cnt;}' cnt=0 - >tmpr.dep

  changequote([, ])dnl

  ac_dependextra_oldfilename=$SETUPBASEDIRLIST
dnl Be aware of empty lists in the beginning
  if test $ac_dependextra_oldfilename = "/dev/null"; then
    SETUPBASEDIRLIST="tmp.dep"
    rm -f $SETUPBASEDIRLIST
    cat tmpr.dep >$SETUPBASEDIRLIST
  else
    cat tmpr.dep >>$SETUPBASEDIRLIST
  fi

  rm -f tmpr.dep
])



AC_DEFUN(AC_CHECK_VSNPRINTF,
[
 AC_REQUIRE([AC_PROG_ALLCXX])

 if test $ac_cv_header_stdio_h = yes; then
  AC_MSG_CHECKING([for vsnprintf()])

  if test $target_os = vxworks; then
   AC_MSG_RESULT(not existing on VxWorks)
  else
   AC_TRY_COMPILE([#include <stdio.h>],[{vsnprintf(NULL,0,"",5);}],[AC_DEFINE(HAVE_VSNPRINTF, 1) AC_MSG_RESULT(yes)],[AC_MSG_RESULT(no)])
  fi
 fi

])

AC_DEFUN(AC_CHECK_OUTWAITING,
[
 AC_REQUIRE([AC_PROG_ALLCXX])

  AC_MSG_CHECKING([for out_waiting()])

  AC_TRY_COMPILE([#include <iostream.h>],[{cout.rdbuf()->out_waiting();}],[AC_DEFINE(HAVE_OUTWAITING, 1) AC_MSG_RESULT(yes)],[AC_MSG_RESULT(no)])

])


AC_DEFUN(AC_CHECK_FILELOCK,
[
  AC_REQUIRE([AC_PROG_ALLCXX])

dnl Just UNIX setup for now
  AC_CHECK_HEADER(sys/file.h)
  AC_CHECK_HEADER(unistd.h)

  if test $ac_cv_header_sys_file_h = yes; then
    AC_LANG_SAVE
    AC_LANG_CPLUSPLUS

dnl Try flock first, since we prefer that!
    AC_MSG_CHECKING(for UNIX flock functions)
    AC_TRY_COMPILE([#include <sys/file.h>],
    [int fd=1; flock(id, LOCK_SH);],
    ac_check_filelock_flock=yes,
    ac_check_filelock_flock=no)

    AC_MSG_RESULT($ac_check_filelock_flock)

    if test $ac_check_filelock_flock = yes; then
      AC_DEFINE(HAVE_FILELOCK_SUPPORT, 1)
      AC_DEFINE(HAVE_UNIX_FLOCK, 1)
    fi
    AC_LANG_RESTORE
  fi

  if test $ac_cv_header_unistd_h = yes; then
    AC_MSG_CHECKING(for UNIX lockf functions)
    AC_TRY_COMPILE([#include <unistd.h>],
    [int fd=1; lockf(fd, F_LOCK, 0);],
    ac_check_filelock_lockf=yes,
    ac_check_filelock_lockf=no)

    AC_MSG_RESULT($ac_check_filelock_lockf)

    if test $ac_check_filelock_lockf = yes; then
      AC_DEFINE(HAVE_FILELOCK_SUPPORT, 1)
      AC_DEFINE(HAVE_UNIX_LOCKF, 1)
    fi
  fi
])

