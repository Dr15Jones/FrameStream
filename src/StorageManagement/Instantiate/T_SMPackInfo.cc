// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      T_SMPackInfo
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Jan  1 13:05:08 EST 2000
// $Id: T_SMPackInfo.cc,v 1.1 2000/01/05 16:29:52 cdj Exp $
//
// Revision history
//
// $Log: T_SMPackInfo.cc,v $
// Revision 1.1  2000/01/05 16:29:52  cdj
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
#include "StorageManagement/Template/SMPackInfo.cc"

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

INSTANTIATE_PACKINFO( char )
INSTANTIATE_PACKINFO( short )
INSTANTIATE_PACKINFO( int )
INSTANTIATE_PACKINFO( long )

INSTANTIATE_PACKINFO( unsigned char )
INSTANTIATE_PACKINFO( unsigned short )
INSTANTIATE_PACKINFO( unsigned int )
INSTANTIATE_PACKINFO( unsigned long )

INSTANTIATE_PACKINFO( float )
INSTANTIATE_PACKINFO( double )

