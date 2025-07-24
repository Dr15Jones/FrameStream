// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSTypeSourceStream
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Thu Apr 17 10:01:34 EDT 2003
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
#include "PackedDataStreamsDelivery/Sources/PDSTypeSourceStream.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSTypeSourceStream" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSTypeSourceStream::PDSTypeSourceStream() :
   m_lastSource(0)
{
}

// PDSTypeSourceStream::PDSTypeSourceStream( const PDSTypeSourceStream& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSTypeSourceStream::~PDSTypeSourceStream()
{
}

//
// assignment operators
//
// const PDSTypeSourceStream& PDSTypeSourceStream::operator=( const PDSTypeSourceStream& rhs )
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

//NOTE: would use templated member function instead if we had it
#define DO_WORK setupNextSource(); return nextSource()->operator>>(iData)

SMSourceStream& 
PDSTypeSourceStream::operator>>( char& iData )
{
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( short& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( int& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( long& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( unsigned char& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( unsigned short& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( unsigned int& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( unsigned long& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( float& iData )
{  
   DO_WORK;
}
SMSourceStream& 
PDSTypeSourceStream::operator>>( double& iData )
{  
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( std::string& iData )
{
   DO_WORK;
}

SMSourceStream& 
PDSTypeSourceStream::operator>>( const SMMakeContentsBase& iData )
{
   DO_WORK;
}

void 
PDSTypeSourceStream::beginObject( const TypeTag& iType )
{
}

void 
PDSTypeSourceStream::endObject()
{
   //get the buffer info from the last source
   setBufferInfo( m_lastSource->startWord(), m_lastSource->startBit() );
}

//
// const member functions
//
unsigned int 
PDSTypeSourceStream::versionUsed( const TypeTag& iType ) const
{
   return m_version;
}

//
// static member functions
//

#include "PackedDataStreamsDelivery/PDSSourceStreamFactory.h"
#include "StorageManagement/Compression/SMContainerSizePacker.h"

void 
PDSTypeSourceStream::readPackingInfo( const UInt32*& ioHeader,
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

   PDSUnpackingSourceStreamBase* presentStream = this;

   //retrieve each field's info
   unsigned int fieldIndex = 0;
   while( fieldIndex < numberOfFields ) {
      ++fieldIndex;

      static PDSSourceStreamFactory s_factory;
      PDSUnpackingSourceStreamBase* stream = 
	 s_factory.createStream( ioHeader, 
				 startBit,
				 iSwappedBytes );
      presentStream->setNextSource( stream );
      presentStream = stream;
      /*
      cout <<"  field type: " << m_packers.back()->type() 
	   <<" strategy: " << m_packers.back()->strategy() << std::endl;
	   */
   }
   //all type info begins on 32bit boundary
   if( startBit != 0 ) {
      ++ioHeader;
   }
   m_lastSource = presentStream;
   m_lastSource->setNextSource( endSource() );
}
