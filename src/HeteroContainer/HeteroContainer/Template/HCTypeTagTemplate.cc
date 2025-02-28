#if !defined(HETEROCONTAINER_HCTYPETAGTEMPLATE_CC)
#define HETEROCONTAINER_HCTYPETAGTEMPLATE_CC
// -*- C++ -*-
//
// Package:     HeteroContainer
// Module:      HCTypeTagTemplate
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Sep 30 11:09:00 EDT 1998
// $Id: HCTypeTagTemplate.cc,v 1.2 1999/10/08 13:42:47 urner Exp $
//
// Revision history
//
// $Log: HCTypeTagTemplate.cc,v $
// Revision 1.2  1999/10/08 13:42:47  urner
// avoid multiple inclusion of HCTypeTagTemplate.cc
//
// Revision 1.1  1998/09/30 15:41:52  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "HeteroContainer/HCTypeTagTemplate.h"

// STL classes

//
// constants, enums and typedefs
//

//static const char* const kFacilityString = "HeteroContainer.HCTypeTagTemplate" ;

//
// static member functions
//
template < class T, class Group >
const char*
HCTypeTagTemplate<T,Group>::className()
{
   return "";
}
#endif /* HETEROCONTAINER_HCTYPETAGTEMPLATE_CC */
