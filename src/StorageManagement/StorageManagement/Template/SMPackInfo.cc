#if !defined(STORAGEMANAGEMENT_SMPACKINFO_CC)
#define STORAGEMANAGEMENT_SMPACKINFO_CC
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMPackInfo
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Jan  1 12:59:22 EST 2000
// $Id: SMPackInfo.cc,v 1.1 2000/01/05 16:29:59 cdj Exp $
//
// Revision history
//
// $Log: SMPackInfo.cc,v $
// Revision 1.1  2000/01/05 16:29:59  cdj
// worked around a bug on Solaris that has to do with static variables in a template class's static function
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMPackInfo.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
template <class T >
unsigned int
SMPackInfoFixedTemplate<T>::classFieldType() 
{
   static unsigned int temp = nextType();
   return temp;
}

template <class T >
unsigned int
SMPackInfoFractionalTemplate<T>::classFieldType() 
{
   static unsigned int temp = nextType();
   return temp;
}

#define INSTANTIATE_PACKINFO( type_ ) \
template class SMPackInfoFixedTemplate< type_ > ;\
template class SMPackInfoFractionalTemplate< type_ >;

#endif /* STORAGEMANAGEMENT_SMPACKINFO_CC */
