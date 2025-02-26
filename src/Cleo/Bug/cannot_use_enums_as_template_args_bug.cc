// -*- C++ -*-
//
// Package:     Bug
// Module:      cannot_use_enums_as_template_args_bug
// 
// Description: Test to see if enums can be used as template arguments
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Oct 23 16:19:54 EDT 1999
// $Id: cannot_use_enums_as_template_args_bug.cc,v 1.2 2001/01/16 22:25:15 cdj Exp $
//
// Revision history
//
// $Log: cannot_use_enums_as_template_args_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:15  cdj
// now closer to C++ standard
//
// Revision 1.1  1999/10/23 20:57:03  cdj
// first submission
//
#include "Experiment/Experiment.h"

#include <iostream.h>

enum Choices { zero, one, two };

#if defined(CANNOT_USE_ENUMS_AS_TEMPLATE_ARGS_BUG)
template < int H >
#else
template < Choices H >
#endif
class TestChoice {
   public:
      Choices choice() const { 
#if defined(CANNOT_USE_ENUMS_AS_TEMPLATE_ARGS_BUG)
	 return static_cast<Choices>(H); 
#else
	 return H; 
#endif
      }
};

int main() {
   cout <<"one " << TestChoice<one>().choice() << endl;
   cout <<"two " << TestChoice<two>().choice() << endl;
}
