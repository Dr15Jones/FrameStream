// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BDRecordBuffer
// 
// Description: Manages memory buffer for one record (e.g. event record)
//
// Implementation:
//n
//
// Author:      David L. Kreinick
// Created:     Wed Oct 28 12:35:51 EST 1998
// $Id: BDRecordBuffer.cc,v 1.9 2002/11/21 21:03:18 cleo3 Exp $
//
// Revision history
//
// $Log: BDRecordBuffer.cc,v $
// Revision 1.9  2002/11/21 21:03:18  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.8  2001/11/13 20:57:03  dlk
// DLK: BinarySourceController -
// 	Revised C open to print more informative error message when
// 	file open fails.  Also, trap the failure at constructor time,
// 	rather than at first read attempt.
//      BDRecordHeader -
// 	Distinguish between EOF and read errors when trying to read header
// 	The former gives a warning, the latter is fatal
//      BDRecordBuffer -
// 	Scream bloody murder if an EOF is encountered during the reading
// 	of an event's data (for fstream reading).
//
// Revision 1.7  1999/11/16 19:31:24  dlk
// Suppress debug messages
//
// Revision 1.6  1999/09/13 18:51:27  dlk
// DLK: Tomasz Skwarnicki reported problems when working with events
//      as large as 750 kBytes.  Duh!  I forgot to expand the buffer
//      if it was too small to hold the incoming event.  I also improved
//      the error message to make clearer what is failing.
//
//      BinaryProxyDeliverer has only a couple cosmetic changes.
//
// Revision 1.5  1999/06/09 18:00:05  dlk
// DLK: Changes forced by need to accomodate to large file bug on Solaris
// 	Include unistd.h for unix read
// 	Return int rather than DABoolean from read function
// 	Changed istream to ifstream
// 	Program around the large file bug by doing a C read
//      Additionally in  BDRecordBuffer.cc
// 	Improve confusing error message
//      Additionally in BinarySourceController.cc
// 	Use EventDefs/EventType.h from Common/include
// 	Keep track of reaching EOF locally instead of relying on fstream
// 	Create a buffer for reading and discarding unwanted input data
// 	Improve confusing error message
//
// Revision 1.4  1999/04/23 19:10:58  dlk
// DLK: Conditional code added to byte swap words appropriately on little
//      endian machines.
//
// Revision 1.3  1999/04/15 19:11:39  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.2  1998/11/18 19:48:54  dlk
// DLK: Intermediate update of BinaryDelivery code
//      The code has now been debugged to the point that it compiles,
//      and runs properly under Martin Lohner's test driver program.
//
//      There are still substantial problems:
//      1) BinaryRawEventProxy not yet written
//      2) Record types have not yet been defined
//      3) We haven't decided on BeginRun and EndRun record formats yet
//      and no doubt there are other problems I haven't discovered yet.
//
// Revision 1.1.1.1  1998/11/03 20:46:41  dlk
// importing new BinaryDelivery sources
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include <fstream>
#include <errno.h>
#include <string.h>
#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
#include <unistd.h>  // Must do standard C read on SUN
#endif
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "BinaryDelivery/BDRecordBuffer.h"
#include "BinaryDelivery/BDRecordHeader.h"
#include "BinaryDelivery/ByteSwapping.h"  // Inline function to swap bytes

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BinaryDelivery.BDRecordBuffer" ;
static const int kBytesPerWord = 4 ;      // Number of bytes in a word

//
// static data member definitions
//

//
// constructors and destructor
//
BDRecordBuffer::BDRecordBuffer(const Stream::Type& iStream,
			       UInt32 iBufferLengthInWords ):
   m_bufferLengthInWords(iBufferLengthInWords),
   m_buffer(0),
   m_streamType( iStream )
{
   m_buffer = new UInt32[iBufferLengthInWords];
   if( 0 == m_buffer ){
      report( ERROR, kFacilityString )
	 << "Unable to create record buffer; out of memory" << std::endl ;
      assert( 0 != m_buffer );
      exit(1);
   }
   return ;
}

// BDRecordBuffer::BDRecordBuffer( const BDRecordBuffer& )
// {
// }

BDRecordBuffer::~BDRecordBuffer()
{
   delete [] m_buffer;
}

//
// assignment operators
//
// const BDRecordBuffer& BDRecordBuffer::operator=( const BDRecordBuffer& )
// {
// }

//
// member functions
//
UInt32
BDRecordBuffer::numberOfWords() const
{
// First word of buffer is the number of words
   return ( begin() )[0];
}

UInt32
BDRecordBuffer::identifier() const 
{
// Second word of buffer is the ASCII identifier
   return ( begin() )[1];
}

UInt32
BDRecordBuffer::recordType() const 
{
// Third word of buffer is the record type
   return ( begin() )[2];
}

int
BDRecordBuffer::read( ifstream& iIFStream, BDRecordHeader& iRecordHeader )
{
// Return value patterned after C read status convention:
// 0        = EOF reached
// negative = error
// positive = OK
   int returnFlag( 1 ) ;
   const int bytesInMinimalRecord
      ( BDRecordHeader::kMinRecordSize*kBytesPerWord ) ;

// Is our current buffer big enough to hold the incoming record?

   if ( iRecordHeader.recordLength() > m_bufferLengthInWords )
   {
// Get rid of the old buffer and carve out a new one with adequate size
// Round up to the next multiple of a kilobyte
      delete [] m_buffer;
      m_bufferLengthInWords =
	 256 * (( iRecordHeader.recordLength() + 256 ) / 256 ) ;
      m_buffer = new UInt32[m_bufferLengthInWords] ;
      if( 0 == m_buffer )
      {
	 report( ERROR, kFacilityString )
	    << "Unable to increase record buffer size; out of memory" << std::endl ;
	 assert( 0 != m_buffer ) ;
	 exit(1);
      }
   }

// The first 12 (kMinRecordSize) words have already been read into the
//   peek-ahead buffer.  Copy them into the event buffer
   memcpy( m_buffer,
	   (char*) iRecordHeader.recordHeaderBuffer(),
	   bytesInMinimalRecord ) ;

// Remaining number of bytes in the record
   int remainingBytesToRead ( kBytesPerWord*(iRecordHeader.recordLength())
			      - bytesInMinimalRecord ) ;
// If there were only kMinRecordSize words in record, we're done
   if ( 0 >= remainingBytesToRead ) { return returnFlag ; }

//Read remainder from input stream into the buffer
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   iIFStream.read( (char*)m_buffer + bytesInMinimalRecord,  
		 remainingBytesToRead) ;
   // We must never get a read error or an end-of-file marker in
   //  the middle of reading an event!  Sending -1 screams ERROR!
   returnFlag = 1 ;
   if ( iIFStream.fail() )
   {
      returnFlag = -1 ;
      report( ERROR, kFacilityString )
	 << "Have read " << iIFStream.gcount() << " bytes, but expected "
	 << remainingBytesToRead << std::endl ;
   }
#else
   int fileDescriptor = iIFStream.rdbuf()->fd() ;
#ifdef CLEO_DEBUG
   report( DEBUG, kFacilityString )
      << " Executing C reads using fileDescriptor "
      << fileDescriptor << std::endl ;
#endif
   int n_read = ::read( fileDescriptor,
			(char*)m_buffer + bytesInMinimalRecord,  
			remainingBytesToRead ) ;
   returnFlag = n_read ;
// n_read = -1 flags system error on read
   if ( -1 == n_read )
   {
      report( ERROR, kFacilityString )
	 << " Read failed, error code " << errno << ":  "
	 << (( strerror( errno ) == NULL) ? "unknown error": strerror( errno) )
	 << std::endl ;
      assert ( 0 < n_read ) ;
      ::exit( 1 ) ;
   }
   if ( n_read != remainingBytesToRead )
   {
      returnFlag = -1 ;  // serious error if wrong number of bytes read
      report( ERROR, kFacilityString )
	 << " Have read " << n_read << " bytes, was expecting " 
	 << remainingBytesToRead << std::endl ;
   }
#endif //FSTREAM_CANNOT_READ_LARGE_FILES_BUG
#if ( AC_BIGENDIAN == 0 )
// On little endian machines, must byte swap words, because file is bigendian
   if ( 0 < returnFlag )
   {
      for ( UInt32 index = BDRecordHeader::kMinRecordSize ;
	    index < iRecordHeader.recordLength() ;
	    index++ )
      {
	 m_buffer[ index ] = swapBytesInUInt32( m_buffer[ index ] ) ;
      }
   }
#endif

   return returnFlag ; 
}

DABoolean
BDRecordBuffer::consistent( BDRecordHeader& iRecordHeader )
{
// Check the final word against length as reported in first word
   UInt32 lengthFromHeader ;
   lengthFromHeader = iRecordHeader.recordLength() ;

   if ( lengthFromHeader != m_buffer[ lengthFromHeader - 1 ] )
   {
      report ( ERROR, kFacilityString )
	 << "Length = "
	 << lengthFromHeader
	 << " in event record header is inconsistent with lengthcheck = "
	 << m_buffer[ lengthFromHeader - 1 ]
	 << " at end of record "
	 << iRecordHeader.eventNumber()
	 << std::endl ;
      return false ;
   }
   return true; 
}

//
// const member functions
//
UInt32*
BDRecordBuffer::beginOfBuffer() const
{
   return m_buffer;
}

const Stream::Type&
BDRecordBuffer::streamType() const
{
   return m_streamType ;
}

UInt32 
BDRecordBuffer::bufferLengthInWords() const
{
   return m_bufferLengthInWords ;
}

const UInt32*
BDRecordBuffer::begin() const
{
   return  m_buffer ;
}

const UInt32*
BDRecordBuffer::end() const
{
   return begin() + numberOfWords() ;
}

//
// static member functions
//
