// -*- C++ -*-
//
// StorageManagement:     <StorageManagement>
// Module:      T_list_pair_pair_unsignedint_float_ptr_double
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Mar 11 19:15:06 EST 2002
// $Id: T_list_pair_pair_unsignedint_float_ptr_double.cc,v 1.1 2002/03/17 16:06:26 cdj Exp $
//
// Revision history
//
// $Log: T_list_pair_pair_unsignedint_float_ptr_double.cc,v $
// Revision 1.1  2002/03/17 16:06:26  cdj
// added optimized version of Fractional packing
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <list>
#include <algorithm>

// user include files


//
// constants, enums and typedefs
//
typedef pair< pair< unsigned int, float>, double*> _list_contents_;

#include "STLUtility/instantiate_list.h"
