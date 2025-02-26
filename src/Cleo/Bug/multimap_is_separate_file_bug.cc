// -*- C++ -*-
//
// Bug Name:    MULTIMAP_IS_SEPARATE_FILE_BUG
// 
// Description: 
//     The g++ compiler did not include the declaration of multimap in
// the standard <map> header file.
//
// Existance:
//   g++: v2.7.2
//
// Author:      Simon Patton
// Created:     Thu May  17 13:06:83 EDT 1996
// $Id: multimap_is_separate_file_bug.cc,v 1.2 2001/01/16 22:25:17 cdj Exp $
//
// Revision history
//
// $Log: multimap_is_separate_file_bug.cc,v $
// Revision 1.2  2001/01/16 22:25:17  cdj
// now closer to C++ standard
//
// Revision 1.1  1998/03/16 22:59:54  mkl
// Simon's bug code snipplets for bug/feature flags
//
//
#include "Experiment/Experiment.h"

#if !defined(NO_STD_NAMESPACE_BUG) && !defined(__DECCXX)
using namespace std;
#endif

#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#include <multimap.h>
#else
#include <map>
#endif // MULTIMAP_IS_SEPARATE_FILE_BUG 

multimap< int , int , less< int > > m ;



