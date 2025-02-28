// -*- C++ -*-
//
// Package:     <package>
// Module:      member_function_arg_in_templated_function_bug
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Apr  7 09:52:31 EDT 2003
// $Id: inherited_member_function_arg_in_templated_function_bug.cc,v 1.2 2003/07/17 19:39:58 cdj Exp $
//
// Revision history
//
// $Log: inherited_member_function_arg_in_templated_function_bug.cc,v $
// Revision 1.2  2003/07/17 19:39:58  cdj
// fixed mistake in test
//
// Revision 1.1  2003/04/07 15:17:25  cdj
// added new bug flags to Solaris 8 compiler
//

#include "Experiment/Experiment.h"

#if !defined(INHERITED_MEMBER_FUNCTION_ARG_IN_TEMPLATED_FUNCTION_BUG)
template<class V, class T>
inline
void test( V* iVar, const V&(T::*iPFunc)() const ) {}
#else
template<class V, class T>
inline
void test( V* iVar, T ) {}
#endif


class Foo
{
   public:
      const unsigned& dummy() const; 
};

class Bar: public Foo
{
};

int main()
{
   unsigned variable; test(&variable, &Bar::dummy);
   
   return 0;
}
