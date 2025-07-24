// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSContainerSourceStream
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Apr 16 14:27:37 EDT 2003
// $Id$
//
// Revision history
//
// $Log$

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

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/Sources/PDSContainerSourceStream.h"
#include "PackedDataStreamsDelivery/Sources/PDSTypeSourceStream.h"
#include "StorageManagement/SMMakeContentsBase.h"
#include "StorageManagement/Compression/SMContainerSizePacker.h"

#include "DAException/DAException.h"
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSContainerSourceStream" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSContainerSourceStream::PDSContainerSourceStream()
{
}

// PDSContainerSourceStream::PDSContainerSourceStream( const PDSContainerSourceStream& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSContainerSourceStream::~PDSContainerSourceStream()
{
}

//
// assignment operators
//
// const PDSContainerSourceStream& PDSContainerSourceStream::operator=( const PDSContainerSourceStream& rhs )
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
static
inline
void
throwException()
{
   throw DAException("asked to unpack a type instead of a container");
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( char& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( short& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( int& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( long& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( unsigned char& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( unsigned short& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( unsigned int& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( unsigned long& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( float& iData )
{
   throwException();
   return *this;
}
SMSourceStream& 
PDSContainerSourceStream::operator>>( double& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( std::string& iData )
{
   throwException();
   return *this;
}

SMSourceStream& 
PDSContainerSourceStream::operator>>( const SMMakeContentsBase& iContents )
{
   static SMContainerSizePacker sizePacker;

   unsigned int iNumberOfEntries = sizePacker.unpack( *startWord(),
						      *(startWord()+1),
						      startBit() );
   advanceStartWordIfNeeded();


   if( 0 == m_typeSourceStream ) {
      m_typeSourceStream = (*(m_typePackingMap->find( iContents.typeTag() ))).second;
   }

   iContents.deliver( *m_typeSourceStream, iNumberOfEntries );

   setBufferInfo( m_typeSourceStream->startWord(), m_typeSourceStream->startBit() );
   return gotoNext();
}

void 
PDSContainerSourceStream::beginObject( const TypeTag& iType )
{
   DAException("beginObject called");
}

void 
PDSContainerSourceStream::endObject()
{
   DAException("endObject called");
}

//
// const member functions
//
unsigned int 
PDSContainerSourceStream::versionUsed( const TypeTag& iType ) const {
   return (*(m_typePackingMap->find(iType))).second->version();
}

//
// static member functions
//
