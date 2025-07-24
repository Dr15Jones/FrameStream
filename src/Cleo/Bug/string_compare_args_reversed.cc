// -*- C++ -*-
//
// Bug Name:   STRING_COMPARE_ARGS_REVERSED_BUG
// 
// Description: 
//      Bug in new egcs (and probably also older) gnu string class:
//        The string compare function has its arguments reversed.
//        It is possible that the gnu compiler is more up-to-date with
//        respect to the standard, but our 96 standard has them the other way.
//        Anyways, for now let's assume that gnu is wrong.
//
// Existance:
//    cxx: 6.0
//
//
// Author:      Martin Lohner
// Created:     Sat Dec 11 10:08:00 EDT 1999
// $Id: string_compare_args_reversed.cc,v 1.2 2001/01/16 22:25:23 cdj Exp $
//
// Revision history
//
// $Log: string_compare_args_reversed.cc,v $
// Revision 1.2  2001/01/16 22:25:23  cdj
// now closer to C++ standard
//
// Revision 1.1  1999/12/11 18:33:57  mkl
// new linux/gnu bug flag: string compare args reversed
//
//

#include "Experiment/Experiment.h"

#include <string>

#if !defined(NO_STD_NAMESPACE_BUG)
using namespace std;
#endif

int main()
{
   std::string anExample( "Example" );

#ifdef STRING_COMPARE_ARGS_REVERSED
   std::string( "Example" ).compare( anExample,
				0,
				anExample.length() );
#else
   std::string( "Example" ).compare( 0,
				anExample.length(),
				anExample );
#endif

   return 0;
}

