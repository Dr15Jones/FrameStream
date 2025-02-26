#if !defined(HETEROCONTAINER_HCTYPETAG_CC)
#define HETEROCONTAINER_HCTYPETAG_CC
// -*- C++ -*-
//
// Package:     HeteroContainer
// Module:      HCTypeTag
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D. Jones
// Created:     Sun Sep 20 15:27:25 EDT 1998
// $Id: HCTypeTag.cc,v 1.2 2000/07/25 13:42:37 cdj Exp $
//
// Revision history
//
// $Log: HCTypeTag.cc,v $
// Revision 1.2  2000/07/25 13:42:37  cdj
// HCTypeTag can now find a TypeTag from the name of a type
//
// Revision 1.1.1.1  1998/09/23 14:13:12  cdj
// first submission
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "HeteroContainer/HCTypeTag.h"

#include "STLUtility/fwd_map.h"

// STL classes
#include <map>
#include <string>

//
// constants, enums and typedefs
//

//static const char* const kFacilityString = "HeteroContainer.HCTypeTag" ;

//
// static data member definitions
//

//This class hides the use of map from all classes that use HCTypeTag
template<class Group>
class HCTypeTagNameHolder {
   public:
      static STL_MAP(string, unsigned int)& typeNameToValueMap() {
	 static STL_MAP(string, unsigned int) s_map;
	 return s_map;
      }
};

//
// constructors and destructor
//
//HCTypeTag::HCTypeTag()
//{
//}

// HCTypeTag::HCTypeTag( const HCTypeTag& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//HCTypeTag::~HCTypeTag()
//{
//}

//
// assignment operators
//
// const HCTypeTag& HCTypeTag::operator=( const HCTypeTag& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

//
// const member functions
//

//
// static member functions
//
template<class Group >
HCTypeTag< Group >
HCTypeTag< Group >::findType( const string& iTypeName )
{
   STL_MAP(string, unsigned int)::iterator itFind = HCTypeTagNameHolder<Group>::typeNameToValueMap().find(
      iTypeName );
   
   if( itFind == HCTypeTagNameHolder<Group>::typeNameToValueMap().end() ) {
      return HCTypeTag< Group >();
   }
   
   return HCTypeTag< Group >( (*itFind).second, (*itFind).first.c_str() );
}

template< class Group >
unsigned int
HCTypeTag< Group >::nextValue(const char* iTypeName )
{
   static unsigned int presentValue = kDefaultValue;
   unsigned int newValue = ++presentValue;

   HCTypeTagNameHolder<Group>::typeNameToValueMap().insert( 
      pair<string, unsigned int>( iTypeName,
				  newValue ) );
   return newValue;
}


#endif /* HETEROCONTAINER_HCTYPETAG_CC */
