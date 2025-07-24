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


// include types.h for backwards compatibility
#include "Experiment/types.h"

#endif /* EXPERIMENT_EXPERIMENT_H */
