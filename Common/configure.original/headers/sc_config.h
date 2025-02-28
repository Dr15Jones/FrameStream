/* headers/sc_config.h.  Generated automatically by configure.  */
#ifndef SC_CONFIG_H
#define SC_CONFIG_H

/* $Id: sc_config.h.in,v 1.26 2001/09/14 20:35:25 hubert Exp $ */

/* Global switches for correct setup */
/* Types and sizes */
#define HAVE_CONST   1
#define AC_BIGENDIAN 1

#define HAVE_STANDARD_SIZES 1
#define SIZEOF_SIGNED_CHAR 1
#define SIZEOF_UNSIGNED_CHAR 1
#define SIZEOF_UNSIGNED_SHORT 2
#define SIZEOF_UNSIGNED_INT 4
#define SIZEOF_UNSIGNED_LONG 4
#define SIZEOF_UNSIGNED_LONG_LONG 8

#define HAVE_LONG_DOUBLE 1

/* Header files */
#define HAVE_STDLIB_H 1
#define HAVE_STDDEF_H 1
#define HAVE_STDIO_H 1
#define HAVE_ERRNO_H 1
#define HAVE_UNISTD_H 1
#define HAVE_STRING_H 1
#define HAVE_SYSENT_H 0
#define HAVE_PTHREAD_H 1
#define HAVE_SYNCH_H 0
#define HAVE_TIS_H 0
#define HAVE_SEMAPHORE_H 1
#define HAVE_SYS_SEM_H 0
#define HAVE_SYS_MSG_H 0
#define HAVE_TIME_H 1
#define CLASH_SYSENT_UNISTD 0

/* Where do correct types come from */
#define USE_SYS_ERRLIST_IN_STDIO_H 1
#define USE_SYS_ERRLIST_IN_SOURCE  0

/* C++ Exceptions */
#define CXX_HAVE_EXCEPTIONS 1
#define CXX_NEEDS_TYPEINFO 0
#define CXX_HAVE_EXTRA_GNUEXTENSION 0

/* C++ std namesspace */
#define CXX_USE_STD_NAMESPACE 0

/* C++ typename keyword disabled for older solaris compiler */
#define TYPENAME_NOT_RECOGNIZED 0

#if (TYPENAME_NOT_RECOGNIZED == 1)
#ifndef typename
#define typename
#endif
#endif

/*
** Switches for BASICS use of platform dependent APIs
*/
#define HAVE_RWLOCK_SUPPORT 0
#define HAVE_VSNPRINTF 1
#define HAVE_OUTWAITING 0
#define USE_PTHREAD_START_T 0
#define USE_RWLOCK_T 0
#define USE_TISRWLOCK_T 0
#define USE_LOCALTIME_R 0
#define USE_STRTOK_R 1
#define USE_HARD_EXIT_CALL 0
/*
** Special switches for platform dependent bug repairs
*/
#define OSF_SEM_DESTROY_BUG 0
#define OSF_MSG_STRUCT_BUG 0
#define SUN_TEMPLATE_WHILE_BUG   0
#define SUN_SOCKET_BUG 0

#define VXW_ORB_ARGV_BUG 0

#define ALL_SEMGETVALUE_MISSINGCONST 0

/*
** Timezone switches
*/
#define FOUND_TIMEZONE 1

#if (FOUND_TIMEZONE == 1)
#define AC_TIMEZONE_STRING "EST5EDT:M4.1.0:M10.5.0"
#endif

/*
** CORBA flavor switches
*/
#define HAVE_CORBA       0
#define HAVE_ORBSHUTDOWN 0
#define HAVE_BOADESTROY  0

/*
** Password switches
*/
#define HAVE_CRYPT_H 0
/* Default security files location */
#define DEFAULT_SECURITY_FILES_LOCATION "/etc/cleo3/"

/*
** ProcessManager switches
*/
#define USE_SETUID 0
#if (USE_SETUID == 1)
#define AC_PROCESSMANAGER_UID -1
#define AC_PROCESSMANAGER_GID -1
#endif /* USE_SETUID */

#define USE_SPOOLDISK_DIR 0
/* Default spooling dir root */
#if (USE_SPOOLDISK_DIR == 1)
#define AC_SPOOLDISK_DIR ""
#endif /* USE_SPOOLDISK_DIR */

/* Locking mechanism in Password */
#define HAVE_SYS_FILE_H 0
#define HAVE_UNIX_LOCKF 0
#define HAVE_UNIX_FLOCK 0
#define HAVE_FILELOCK_SUPPORT 0

#endif
