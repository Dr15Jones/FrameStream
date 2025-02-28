#if !defined(EXPERIMENT_EXPERIMENT_H)
#define EXPERIMENT_EXPERIMENT_H
// -*- C++ -*-
//
// Package:     Cleo
// Module:      Cleo
// 
// Description: Experiement specific header
//
// Usage:
//    The file should be included at the start of every ".cc" file
//
// Author:      Simon Patton
// Created:     Mon July 7 08:38:02 EDT 1997
// $Id: Experiment.h,v 1.13 2001/04/13 20:49:36 cdj Exp $
//
// Revision history
//
// $Log: Experiment.h,v $
// Revision 1.13  2001/04/13 20:49:36  cdj
// new flags for Solaris 6.2 compiler
//
// Revision 1.12  1999/10/30 12:41:45  cleo3
// updated to work with cxx 6.2 and new bug checkers
//
// Revision 1.11  1998/05/14 15:01:28  mkl
// submitted bogus change to cause a complete rebuild to check speed of lns131
//
// Revision 1.10  1998/03/05 17:46:42  mkl
// moved typedefs out of Experiment.h into types.h; include types.h in Experiment.h for backwards compatibility
//
// Revision 1.9  1997/12/19 01:31:41  sjp
// Added includes for SUN and AIX compilers
//
// Revision 1.8  1997/10/05 17:06:35  mkl
// added lines to turn on CLHEP
//
// Revision 1.7  1997/09/18 20:53:40  cdj
// Changed Boolean to DABoolean
//
// Revision 1.6  1997/09/07 21:06:22  sjp
// Put in necessary flag for CLHEP
//
// Revision 1.5  1997/09/04 16:07:50  sjp
// Added hook for HP
//
// Revision 1.4  1997/09/01 15:42:07  sjp
// Moved configuration flags into this file
//
// Revision 1.3  1997/08/29 14:18:45  sjp
// Added likelihood typedef
//
// Revision 1.2  1997/08/14 21:26:20  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1.1.1  1997/07/11 16:58:36  sjp
// Cleo's implementation of the EXperiement directory.
//

#if defined(__APPLE__)
#include "Experiment/gnug_flags.h"
#define CLHEP_TARGET_H "CLHEP/config/CLHEP.h"
//#define CLHEP_TARGET_H "CLHEP-powerpc-apple-darwin6.6-c++.h"
//#define CLHEP_TARGET_H "CLHEP/config/CLHEP-alpha-dec-osf4.0-g++.h"
#else
#if defined(__GNUG__)
#include "Experiment/gnug_flags.h"
#define CLHEP_TARGET_H "CLHEP/config/CLHEP-i686-unknown-linux-g++.h"
#endif // __GNUG__
#endif /* __APPLE__ */


#if defined(__DECCXX)
#include "Experiment/deccxx_flags.h"
#define CLHEP_TARGET_H "CLHEP/config/CLHEP-alpha-dec-osf4.0-cxx.h"
#endif /* __DECCXX */

#if defined(__MWERKS__)
#include "Experiment/mwerks_flags.h"
#endif /* __MWERKS__ */

#if defined(SUNCC)
#include "Experiment/SUNCC_flags.h"
#endif /* SUNCC */

#if defined(__GNUG__) && defined(__APPLE__)
#include "Experiment/apple_flags.h"
#endif /* __GNUG__ */

#if defined(__XLC__)
#include "Experiment/xlc_flags.h"
#endif /* __XLC__ */

#if defined(HP1022)
#include "Experiment/HPCC_flags.h"
#endif /* HP1022 */

// use the MessageLog class to handle messaged through report
#if !defined(__MWERKS__)
#define USE_MESSAGELOG_FOR_REPORT
#endif /* __MWERKS__ */

// use implicit instantiation for Codewarrior
#if defined(__MWERKS__)
#define INCLUDE_TEMPLATE_DEFINITIONS
#endif /* __MWERKS__ */

// include types.h for backwards compatibility
#include "Experiment/types.h"

//
// This installation uses CLHEP vectors
#define USE_CLHEP_THREEVECTOR
#define USE_CLHEP_LORENTZVECTOR

#if !defined(STD_PREFIX)
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif
#endif

#if __SUNPRO_CC == 0x420 
#define CLHEP_MAX_MIN_DEFINED
#endif

#endif /* EXPERIMENT_EXPERIMENT_H */
