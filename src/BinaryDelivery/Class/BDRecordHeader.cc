// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BDRecordHeader
// 
// Description: Holds the first 12 words = header of an event record
//
// Implementation:
//     
//
// Author:      David L. Kreinick
// Created:     Wed Oct 14 13:30:05 EDT 1998
// $Id: BDRecordHeader.cc,v 1.18 2003/02/25 16:29:27 dlk Exp $
//
// Revision history
//
// $Log: BDRecordHeader.cc,v $
// Revision 1.18  2003/02/25 16:29:27  dlk
// DLK: When BinaryDelivery was run on the Linux platform it screwed up.
//      Turns out this was because I defined the ASCII comparison string
//      for 'RAWD' with 'RAWD'.  Evidently the Linux g++ compiler and
//      Alpha's cxx treat this differently.  The fix was to replace
//      'RAWD' with 0x52415744, its hexadecimal equivalent.
// 	This obviated some contortions with endian-dependent
//      comparisons and actually simplified the code.
// 	I have verified that the new code works properly on Solaris6
//      OSF1, and Lintel g++, and deliberately screwed up the code to
//      prove that it responds to mistakes the same on all 3 platforms.
//
// Revision 1.17  2003/01/27 19:49:44  cdj
// get iomanip.h from C++Std package
//
// Revision 1.16  2002/11/21 21:03:18  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.15  2002/08/16 13:55:30  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.14  2001/11/13 20:57:03  dlk
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
// Revision 1.13  2001/05/22 21:08:03  bkh
// Fix event time decoding
// Add event time to instantiation of SyncValue.
//
// Revision 1.12  2000/01/04 13:24:31  dlk
// Improve error message for missing input file
//
// Revision 1.11  1999/12/17 13:17:49  dlk
// Improve error messages
//
// Revision 1.10  1999/06/23 17:52:53  dlk
// Dump record header if fatal formatting error detected
//
// Revision 1.9  1999/06/09 18:00:06  dlk
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
// Revision 1.8  1999/05/20 17:51:45  dlk
// Make a smooth landing when EOF reached
//
// Revision 1.7  1999/05/13 18:47:21  dlk
// DLK: 	Redefine decimal stream output after outputting hex
// 	Commented out diagnostic print statements
//
// Revision 1.6  1999/04/23 19:10:59  dlk
// DLK: Conditional code added to byte swap words appropriately on little
//      endian machines.
//
// Revision 1.5  1999/04/15 19:11:39  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.4  1998/11/18 19:48:56  dlk
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
// Revision 1.3  1998/11/16 16:51:11  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
// Revision 1.2  1998/11/04 16:14:11  mkl
// minor change
//
// Revision 1.1.1.1  1998/11/03 20:46:41  dlk
// importing new BinaryDelivery sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include "C++Std/iostream.h"
#include "C++Std/iomanip.h"
#include "C++Std/fstream.h"
#include <unistd.h>  // Must do standard C read on SUN
#include <errno.h>
#include <string.h>

// user include files
#include "Experiment/report.h"
#include "BinaryDelivery/BDRecordHeader.h"
#include <assert.h>
#include "BinaryDelivery/ByteSwapping.h"  // Inline function to swap bytes
// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BinaryDelivery.BDRecordHeader" ;
static const int kBytesPerWord = 4 ;     // Number of bytes in a word
// Cross checks for endian compatibility; keywords forward and backward
static const UInt32 kRAWD = 0x52415744 ; // Hex code for ASCII 'RAWD'
static const UInt32 kDWAR = 0x44574152 ; // Hex code for ASCII 'DWAR'
static const UInt32 kHEAD = 0x48454144 ; // Hex code for ASCII 'HEAD'

//
// static data member definitions
//

//
// constructors and destructor
//
BDRecordHeader::BDRecordHeader():
   m_headerBuffer( 0 )
{
  m_headerBuffer = new UInt32[ kMinRecordSize ];
   if( 0 == m_headerBuffer ){
      report( ERROR, kFacilityString )
         << "Unable to create buffer for event header; out of memory" << endl ;
      assert( 0 != m_headerBuffer );
      ::exit(1);
   }
   return ;
}
 
// BDRecordHeader::BDRecordHeader( const BDRecordHeader& )
// {
// }

BDRecordHeader::~BDRecordHeader()
{
   delete [] m_headerBuffer ;
}

//
// assignment operators
//
// const BDRecordHeader& BDRecordHeader::operator=( const BDRecordHeader& )
// {
// }

//
// member functions
//
int
BDRecordHeader::read( ifstream& iIFStream )
{
// Return value patterned after C read status convention:
// 0        = EOF reached
// negative = error
// positive = OK
   int returnFlag( 1 ) ;  // return value

// We can't proceed if the stream is already at the eof
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   if( iIFStream.eof() ) { returnFlag = 0 ; }
#endif

#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
// Obtain the file descriptor corresponding to input file stream
   int fileDescriptor = iIFStream.rdbuf()->fd() ;
   if ( 0 > fileDescriptor )
   {
      report( ERROR, kFacilityString )
         << "Unable to open input file."  << endl ;
      returnFlag = -1 ;  // Flag the failure to open
   }
#endif

// Don't try to read if system says we're at EOF
   if ( 0 == returnFlag )
   {
      report ( INFO, kFacilityString )
	 << "Detected EOF of binary source; will not attempt read" << endl ;
   }
// Read twelve words into the recordHeader
   if ( 0 < returnFlag )
   {
// First read and check the record length
// Because ifstream.read insists on storing to a char*, and I want
//  UInt32s, there is some ugly typecasting here.

#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
      iIFStream.read( (char*)m_headerBuffer, kBytesPerWord ) ;
      if ( iIFStream.fail() )
      {
	 if ( iIFStream.eof() )
	 {
	    returnFlag = 0 ;  // Flag EOF
	    report ( INFO, kFacilityString )
	       << "Reached EOF of binary source" << endl ;
	 }
	 else
	 {
	    returnFlag = -1 ; // Flag read error
	    report ( INFO, kFacilityString )
	       << "Error " << iIFStream.rdstate()
	       << " reading next event header" << endl ;
	 }
      }
#else
      int n_read = ::read( fileDescriptor,
			   (char*)m_headerBuffer, kBytesPerWord) ;	
      if ( 0 > n_read )
      {
         report( ERROR, kFacilityString )
            << "C read fails for next event header\n"
            << "    System error message is: "
            << strerror( errno ) << endl ;
         returnFlag = n_read ;    // Flag read error to calling routine
      }
      else if ( 0 == n_read )
      {
	 returnFlag = 0 ;
	 report ( INFO, kFacilityString )
	    << "Reached EOF of binary source" << endl ;
      }
#endif
      else                 //  Successful read
      {
#if ( AC_BIGENDIAN == 0 )
// On little endian machines, must byte swap words, because file is bigendian
	 m_headerBuffer[0] = swapBytesInUInt32( m_headerBuffer[0] ) ;
#endif
	 if ( kMinRecordSize > m_headerBuffer[0] )
	 {
	    returnFlag = -1 ;
	    report( ERROR, kFacilityString )
	       << m_headerBuffer[0]
	       << " is too few words to hold a valid event record.  Aborting"
	       << endl ;
	    assert( kMinRecordSize <= m_headerBuffer[0] );
	    ::exit(1) ;
	 }
      }
   }

// Read the remaining header words

   if ( 0 < returnFlag )
   {
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
      iIFStream.read( (char*)m_headerBuffer + kBytesPerWord,
		     (kMinRecordSize-1)*kBytesPerWord ) ;
      if ( iIFStream.fail() )
#else
      int n_read = ::read( fileDescriptor,
			   (char*)m_headerBuffer + kBytesPerWord,
			   (kMinRecordSize-1)*kBytesPerWord ) ;
      if (0 >= n_read )
#endif
      {
	 returnFlag = -1 ;
	 report ( ERROR, kFacilityString )
	    << "Have reached EOF of binary source" << endl ; // This
//              is an error because we shouldn't hit EOF in mid-event
      }
#if ( AC_BIGENDIAN == 0 )
// On little endian machines, must byte swap words, because file is bigendian
      for ( UInt32 index = 1 ;  // Yes, I really mean 1; 0's already done
	    index < kMinRecordSize ;
	    index++ )
      {
	 m_headerBuffer[index] = swapBytesInUInt32( m_headerBuffer[index] ) ;
      }
#endif

// Check that the ASCII tags RAWD and HEAD are right
// This checks for data corruption and phase slippage

      if ( kRAWD != m_headerBuffer[1] )
      {
	 returnFlag = -1 ;
	 report( ERROR, kFacilityString )
	    << "Read "
	    << hex << m_headerBuffer[1]
	    << ", should be "  << kRAWD
	    << " (RAWD) for raw data events" << dec
	    << endl ;
	 dumpHeaderBufferContents() ;

// If RAWD comes out DWAR, then byteswapping code is defective

	 if ( kDWAR == m_headerBuffer[1] )
	 {
	    // Someone (me) has screwed up the little endian flag
	    // and we got the wrong byte ordering
	    // This is a coding error, so make an assertion
	    int ac_bigendian = AC_BIGENDIAN ;
	    report( ERROR, kFacilityString )
	       << "Coding error:  CPU has AC_BIGENDIAN = "
	       << ac_bigendian << "\n"
	       << "However ASCII tag is byte-swapped" 
	       << " RAWD dataID flag has come out DWAR" << endl ;
	    assert( kDWAR != m_headerBuffer[1] ) ;
	    // (There will not be an assertion for corrupt data)
	 }
      }
      
// Check ASCII tag HEAD just as we tested RAWD for add'l safety

      if ( kHEAD != m_headerBuffer[4] )
      {
	 returnFlag = -1 ;
	 report( ERROR, kFacilityString )
	    << "Read "
	    << hex << m_headerBuffer[4]
	    << ", should be " << kHEAD << dec
	    << " (HEAD) for record header information"
	    << endl ;
	 dumpHeaderBufferContents() ;
      }

// Extract record type from the version/type word by shifting and masking
      m_recordType =  0xFFFF & ( m_headerBuffer[2] >> 16 ) ;
//      dumpHeaderBufferContents() ;
   }
      return returnFlag ;
}

//
// const member functions
//
const UInt32*
BDRecordHeader::recordHeaderBuffer() const
{
   return m_headerBuffer ;
}

UInt32
BDRecordHeader::recordLength() const
{
   return m_headerBuffer[0] ;
}

UInt32
BDRecordHeader::recordVersion() const
{
   return ( m_headerBuffer[2] && 0xFFFF ) ;
}

UInt32
BDRecordHeader::recordType() const
{
   return m_recordType ;
}

UInt32
BDRecordHeader::runNumber() const
{
   return m_headerBuffer[7] ;
}

UInt32
BDRecordHeader::eventNumber() const
{
   return m_headerBuffer[8] ;
}

UInt32
BDRecordHeader::timeMost() const
{
   return m_headerBuffer[5] ;
}

UInt32
BDRecordHeader::timeLeast() const
{
   return m_headerBuffer[6] ;
}

void
BDRecordHeader::dumpHeaderBufferContents() const
{
      report( INFO, kFacilityString )
	 << "Dumping 12-word header buffer" << endl
	 << " 0: " << setw(8) << hex << m_headerBuffer[0] << 
	 " record length    " << dec << m_headerBuffer[0] << endl;

      char asciiID[5] ;
#if ( AC_BIGENDIAN != 0 )
      memcpy( asciiID, (char*)(m_headerBuffer+1), 4) ;
#else
      UInt32 intAsciiID ;
      UInt32* ptr ( &intAsciiID ) ;
      intAsciiID = swapBytesInUInt32( m_headerBuffer[1] ) ;
      memcpy( asciiID, (char*)ptr, 4) ;
#endif
      asciiID[4] = '\0' ;
      report( INFO, kFacilityString )
	 << " 1: " << setw(8) << hex << m_headerBuffer[1] << 
	 " ASCII identifier " << asciiID << endl ;

      report( INFO, kFacilityString )
	 << " 2: " << setw(8) << hex << m_headerBuffer[2] << 
	 " Type and version " << ( 0xffff & ( m_headerBuffer[2] >> 16 ))
	 << "  "  << (0xffff & m_headerBuffer[2]) << endl ;

      report( INFO, kFacilityString )
	 << " 3: " << setw(8) << hex << m_headerBuffer[3] << 
	 " HEAD length      " << dec << m_headerBuffer[3] << endl ;

#if ( AC_BIGENDIAN != 0 )
      memcpy( asciiID, (char*)(m_headerBuffer+4), 4) ;
#else
      intAsciiID = swapBytesInUInt32( m_headerBuffer[4] ) ;
      memcpy( asciiID, (char*)ptr, 4 ) ;
#endif
      report( INFO, kFacilityString )
	 << " 4: " << setw(8) << hex << m_headerBuffer[4] << 
	 " ASCII identifier " << asciiID << endl ;

      report( INFO, kFacilityString )
	 << " 5: " << setw(8) << hex << m_headerBuffer[5] << 
	 " Time seconds     " << dec << m_headerBuffer[5] << endl ;

      report( INFO, kFacilityString )
	 << " 6: " << setw(8) << hex << m_headerBuffer[6] << 
	 " Time usecs       " << dec << m_headerBuffer[6] << endl ;

      report( INFO, kFacilityString )
	 << " 7: " << setw(8) << hex << m_headerBuffer[7] << 
	 " Run number       " << dec << m_headerBuffer[7] << endl ;

      report( INFO, kFacilityString )
	 << " 8: " << setw(8) << hex << m_headerBuffer[8] << 
	 " Event number     " << m_headerBuffer[8] << endl ;

      report( INFO, kFacilityString )
	 << " 9: " << setw(8) << hex << m_headerBuffer[9] << 
	 " Level3 tag       " << endl ;

      report( INFO, kFacilityString )
	 << "10: " << setw(8) << hex << m_headerBuffer[10] << 
	 " HEAD length      " << m_headerBuffer[10] << endl ;

      report( INFO, kFacilityString )
	 << "11: " << setw(8) << hex << m_headerBuffer[11] << 
	 " Length           " << dec << m_headerBuffer[11] <<
	 "\n" << endl ;
	 return ;
}
//
// static member functions
//
