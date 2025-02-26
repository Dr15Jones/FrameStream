#if !defined(EXPERIMENT_FORTRAN_TYPES_H)
#define EXPERIMENT_FORTRAN_TYPES_H
// -*- C++ -*-
//
// Package:     Experiment
// Module:      fortran_types
// 
// Description: typedefs for Fortran variable types
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Mon Aug 18 10:51:18 EDT 1997
// $Id: fortran_types.h,v 1.3 2002/02/01 18:38:44 ajm36 Exp $
//
// Revision history
//
// $Log: fortran_types.h,v $
// Revision 1.3  2002/02/01 18:38:44  ajm36
// change real->f2c_real, complex->f2c_complex to avoid conflicts
//
// Revision 1.2  1998/03/05 19:39:46  mkl
// added FChar and FCharacter
//
// Revision 1.1  1998/02/10 18:01:27  mkl
// moved fortran_type stuff to Experiment
//
//

// system include files

// user include files
#include "Experiment/f2c.h"
// forward declarations

// constants, enums and typedefs
typedef integer    FInteger;
typedef f2c_real   FReal;
typedef doublereal FDouble;
typedef logical    FLogical;
typedef ftnlen     FLength;
typedef char       FChar ;
typedef char       FCharacter ;


#endif /* EXPERIMENT_FORTRAN_TYPES_H */
