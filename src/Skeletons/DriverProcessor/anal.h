// -*- C++ -*-
#if !defined(DRIVERPROCESSOR_ANAL_H)
#define DRIVERPROCESSOR_ANAL_H
//
// Package:     DriverProcessor
// Module:      anal
// 
// Description: C++ prototypes of fortran subroutines
//
// Usage:       The User shouldn't touch these!
//
// Author:      Martin Lohner
// Created:     Thu Jun 19 16:02:16 EDT 1997
// $Id: anal.h,v 1.2 2000/11/18 03:48:55 marsh Exp $
//
// Revision history
//
// $Log: anal.h,v $
// Revision 1.2  2000/11/18 03:48:55  marsh
// Moved emacs mode hint to the top of the file, where emacs will actually
// look at it.
//
// Revision 1.1  1998/02/10 03:44:44  mkl
// moved (obsolete) DriverProcessor skeletons to own subdirectory
//
// Revision 1.2  1997/08/29 04:12:21  mkl
// simplify processors for users
//
// Revision 1.1  1997/06/19 21:18:08  mkl
// added DriverProcessor as skeletons
//

// system include files

// user include files

// forward declarations

extern "C"
{
   // and the user anal routines
   void anal1_( void );
   void anal2_( void );
   void anal3_( void );
   void anal4_( void );
   void anal5_( void );
   void anal10_( void );
  
}

// inline function definitions

#endif /* DRIVERPROCESSOR_ANAL_H */
