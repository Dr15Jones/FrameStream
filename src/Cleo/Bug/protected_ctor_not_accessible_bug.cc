// -*- C++ -*-
//
// Bug Name:    PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
// 
// Description: 
//     A protected constructor is not accessible by it subclass.
//
// Existence:
//   g++: v2.7.2
//
// Author:      Simon Patton
// Created:     Tue Aug  26 20:38:25 EDT 1997
// $Id: protected_ctor_not_accessible_bug.cc,v 1.3 2001/01/16 22:25:22 cdj Exp $
//
// Revision history
//
// $Log: protected_ctor_not_accessible_bug.cc,v $
// Revision 1.3  2001/01/16 22:25:22  cdj
// now closer to C++ standard
//
// Revision 1.2  1999/10/23 20:53:43  cdj
// bug fix: removed void return value from constructor
//
// Revision 1.1  1998/03/16 22:59:59  mkl
// Simon's bug code snipplets for bug/feature flags
//
//

#include "Experiment/Experiment.h"

class Base
{
   protected:
#if defined(PROTECTED_CTOR_NOT_ACCESSIBLE_BUG)
   public:
      Base() ;
   protected:
#else
      Base() ;
#endif // PROTECTED_CTOR_NOT_ACCESSIBLE_BUG 
} ;

class Derived : public Base
{
   public:
      void function() ;
} ;

Base::Base()
{
}

void Derived::function()
{
   Base a ;
}

