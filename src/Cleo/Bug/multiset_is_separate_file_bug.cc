// -*- C++ -*-
//
// Bug Name:    MULTISET_IS_SEPARATE_FILE_BUG
// 
// Description: 
//     The g++ compiler did not include the declaration of multiset in
// the standard <set> header file.
//
// Existance:
//   g++: v2.7.2
//
// Author:      Simon Patton
// Created:     Thu May  17 13:06:83 EDT 1996
// $Id: multiset_is_separate_file_bug.cc,v 1.2 2001/01/16 22:25:18 cdj Exp $
//
// Revision history
//
// $Log: multiset_is_separate_file_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:18  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 22:59:55  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

#if !defined(NO_STD_NAMESPACE_BUG) && !defined(__DECCXX)
using namespace std;
#endif

#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif // MULTISET_IS_SEPARATE_FILE_BUG 

multiset< int , less< int > > m ;

