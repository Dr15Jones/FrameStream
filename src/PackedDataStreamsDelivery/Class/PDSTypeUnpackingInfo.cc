// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSTypeUnpackingInfo
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Tue Sep 19 13:52:36 EDT 2000
// $Id: PDSTypeUnpackingInfo.cc,v 1.4 2002/08/16 15:42:40 cleo3 Exp $
//
// Revision history
//
// $Log: PDSTypeUnpackingInfo.cc,v $
// Revision 1.4  2002/08/16 15:42:40  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.3  2002/04/04 19:13:32  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
//
// Revision 1.2  2001/04/10 19:48:10  cdj
// can now store strings
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
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
//#include "C++Std/iostream.h"

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"
#include "PackedDataStreamsDelivery/PDSPackerFactory.h"
#include "PackedDataStreamsFormat/PDSPackerBase.h"

#include "StorageManagement/Compression/SMContainerSizePacker.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSTypeUnpackingInfo" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSTypeUnpackingInfo.cc,v 1.4 2002/08/16 15:42:40 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSTypeUnpackingInfo::PDSTypeUnpackingInfo()
{
}

// PDSTypeUnpackingInfo::PDSTypeUnpackingInfo( const PDSTypeUnpackingInfo& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSTypeUnpackingInfo::~PDSTypeUnpackingInfo()
{
   for( STL_VECTOR(PDSPackerBase*)::iterator itPacker = m_packers.begin();
	itPacker != m_packers.end();
	++itPacker ) {
      delete (*itPacker);
   }
}

//
// assignment operators
//
// const PDSTypeUnpackingInfo& PDSTypeUnpackingInfo::operator=( const PDSTypeUnpackingInfo& rhs )
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
void 
PDSTypeUnpackingInfo::readPackingInfo( const UInt32*& ioHeader,
				       DABoolean iSwappedBytes )
{
   SMContainerSizePacker sizePacker;

   //The first value is the version info
   unsigned char startBit = 0;
   //m_version  = *ioHeader;
   //++ioHeader;

   m_version = sizePacker.unpack(*ioHeader,
				 *(ioHeader+1),
				 startBit);
   if( startBit >= 32 ) {
      startBit -= 32;
      ++ioHeader;
   }

   //the second value is the number of fields
   const unsigned int numberOfFields = sizePacker.unpack(*ioHeader,
							 *(ioHeader+1),
							 startBit);
   if( startBit >= 32 ) {
      startBit -= 32;
      ++ioHeader;
   }
   m_packers.reserve(numberOfFields);
   m_typePackers.reserve(numberOfFields);
   //retrieve each field's info
   unsigned int fieldIndex = 0;
   while( fieldIndex < numberOfFields ) {
      ++fieldIndex;

      PDSPackerBase* packer = packerFactory().createPacker( ioHeader, 
							 startBit,
							 iSwappedBytes );
      m_packers.push_back( packer );
      m_typePackers.push_back( TypePacker( packer->type(),
                                           packer->smPacker() ) );
      /*
      cout <<"  field type: " << m_packers.back()->type() 
	   <<" strategy: " << m_packers.back()->strategy() << endl;
	   */
   }
   //all type info begins on 32bit boundary
   if( startBit != 0 ) {
      ++ioHeader;
   }
}

PDSPackerFactory&
PDSTypeUnpackingInfo::packerFactory() {
   static PDSPackerFactory s_factory;
   return s_factory;
}

//
// const member functions
//

//
// static member functions
//
