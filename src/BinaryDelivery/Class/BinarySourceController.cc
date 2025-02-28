// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BinarySourceController
// 
// Description: <one line class summary>
//
// Implementation:
//     BinarySourceController owns the istream and does the reads
//     It also owns the 6-word peakAheadBuffer
//     But it fills a buffer supplied by the binaryProxyDeliverer
//
//     Binary format on disk is quite straightforward.  The raw
//     event is preceded by a 6-word header containing
//        event length in words (including the 6 word header)
//        event type code
//        run number
//        event number
//        time stamp high order word
//        time stamp low order word
//     The strategy here is to hold this header in a separate
//     6-word buffer called the nextRecordHeader.  The proxy requests
//     records of a particular type and SyncValue.  The BinarySourceCtlr
//     uses the nextRecordHeader to decide whether to discard the record
//     or to read it into the buffer supplied by the proxy
//
// Author:      David L. Kreinick
// Created:     Tue Aug 18 16:37:00 EDT 1998
// $Id: BinarySourceController.cc,v 1.17 2003/11/18 22:17:43 dlk Exp $
//
// Revision history
//
// $Log: BinarySourceController.cc,v $
// Revision 1.17  2003/11/18 22:17:43  dlk
// Repair reading files >2GB on Solaris
//
// Revision 1.16  2003/10/17 12:42:48  vk
// Fix reading back time stamp from record header.
//
// Revision 1.15  2002/11/21 21:03:19  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.14  2002/08/16 13:55:31  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.13  2001/11/13 20:57:03  dlk
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
// Revision 1.12  2001/05/22 21:08:03  bkh
// Fix event time decoding
// Add event time to instantiation of SyncValue.
//
// Revision 1.11  1999/12/17 13:17:50  dlk
// Improve error messages
//
// Revision 1.10  1999/06/17 19:16:57  dlk
// DLK: Further adventures in 64-bit file handling
// 	If FSTREAM_CANNOT_READ_LARGE_FILES_BUG, do a C open,
// 	so that files over 2GB can be handled.  Previous bug
// 	workaround dealt with the reads only, and that didn't suffice.
//      Provide more detailed error messages when file errors encountered
//
// Revision 1.9  1999/06/09 18:00:07  dlk
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
// Revision 1.8  1999/06/04 18:40:12  dlk
// DLK: If the file open fails, BinarySourceController is supposed to return
//      kInitSourceInaccessible.  I was sloppily overwriting this with a
//      success message.  This is repaired by returning immediately after
//      the error condition is noticed and flagged.
//
// Revision 1.7  1999/05/20 17:51:46  dlk
// Make a smooth landing when EOF reached
//
// Revision 1.6  1999/05/19 21:04:29  dlk
// DLK: BinaryProxyDeliverer.cc
// 	Add startRun and pauseRun, but kluge out pauseRun, which won't
// 	function properly because of a conceptual flaw in the system
// 	for assigning stream priorities.  Since almost no one will
// 	want to stop on pauseRun records, this shouldn't matter for now.
// DLK: BinarySourceController.cc
// 	Add startRun and pauseRun streams
// 	Add informative error message if user requests an unimplemented
// 	stream (like pauserun, for example)
//
// Revision 1.5  1999/04/23 19:10:59  dlk
// DLK: Conditional code added to byte swap words appropriately on little
//      endian machines.
//
// Revision 1.4  1999/04/15 19:11:41  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.3  1998/11/18 19:48:58  dlk
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
// Revision 1.2  1998/11/04 16:13:48  mkl
// got rid of gzip handling; changed istream to ifstream
//
// Revision 1.1.1.1  1998/11/03 20:46:41  dlk
// importing new BinaryDelivery sources
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include "C++Std/iostream.h"
#include "C++Std/fstream.h"
#include <stdlib.h>
#include <assert.h>
#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
#include <unistd.h>  // Must do standard C read on SUN
#include <fcntl.h>   // Parameter O_RDONLY for SUN open statement
#include <errno.h>
#include <string.h>
#endif
// user include files
#include "Experiment/report.h"
#include "BinaryDelivery/BinaryProxyDeliverer.h"
#include "BinaryDelivery/BinarySourceController.h"
#include "BinaryDelivery/BDRecordHeader.h"
#include "BinaryDelivery/BDRecordBuffer.h"
#include "EventDefs/EventTypes.h"
#include "BinaryDelivery/ByteSwapping.h"  // Inline function to swap bytes

// STL classes
#include <string>
#include <map>

//
// constants, enums and typedefs
//
static const char* const kFacilityString 
= "BinaryDelivery.BinarySourceController" ;
static const int kBytesPerWord = 4  ;   // Number of bytes in a word
static const int kTrashBufferSize = 50000 ; // Size of buffer for ignore

//
// local functions
//
static
DataSourceController::SyncStatus
convertSearchStatusToSyncStatus( const DataSourceController::SearchStatus&
				 iSearchStatus)
// Trivial translation of Search Status codes to Sync Status codes
{
   DataSourceController::SyncStatus oStatus;
   switch( iSearchStatus ){
      case DataSourceController::kSearchNoError:
        oStatus = DataSourceController::kSyncNoError;
	break;
      case DataSourceController::kSearchEndOfSource:
        oStatus = DataSourceController::kSyncWarningAtEndOfSource;
	break;
      case DataSourceController::kSearchProblemWithSource:
        oStatus = DataSourceController::kSyncProblemWithSource;
	break;
      case DataSourceController::kSearchUnknownError:
        oStatus = DataSourceController::kSyncUnknownError;
	break;
      default:
        oStatus = DataSourceController::kSyncUnknownError;
	break;
   }
   return oStatus;
}

//
// static data member definitions
//

//
// constructors and destructor
//
BinarySourceController::BinarySourceController( const string& iFileName,
						const Stream::Set& iReadStreams,
						BinaryProxyDeliverer* iDeliverer):
   DataSourceController( iDeliverer ),
   m_fileName( iFileName ),
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   m_file( iFileName.c_str() ),  // Use C++ open normally
#else                            // For Solaris6, use a C open
   m_fileDescriptor(0),
   m_file( m_fileDescriptor = open( iFileName.c_str(), O_RDONLY ) ),
#endif
   m_nextRecordHeader(),
   m_nextRecordType( Stream::kNone ),
   m_havePeekedAhead( false ),
   m_reachedEOF( false ),
   m_bufferToTrash( 0 )
{
// Were we able to actually open the file?

#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)   // C++ open
   if (
#if defined(NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG)
      ! (*m_file.rdbuf()).is_open()
#else
      ! m_file.is_open()
#endif  // NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG
      ) {
      report( ERROR , kFacilityString ) <<
	 "\n  Unable to open binary data file " <<
	 m_fileName << endl ;
#else                                              // C open
   if ( 0 > m_fileDescriptor )
   {
      report( ERROR, kFacilityString ) <<
	 "\n  Open failed for " << iFileName <<
	 ": "  << strerror(errno) << endl ;
#endif  // FSTREAM_CANNOT_READ_LARGE_FILES_BUG

// Open failed; set flags and quit
      setInitializationStatus( kInitSourceInaccessible ) ;
      m_reachedEOF = true ;
      return ;
   }  // This closes either the C++ if ( ! m_file.is_open() )
   //      or the C if ( 0 > m_fileDescriptor )

   // Verify that the specified record types are actually here
   DABoolean isOK( setRecordsToRetrieve( iReadStreams ) );
   if( ! isOK ){
      setInitializationStatus( 
	 DataSourceController::kInitInvalidStopsForSource );
      // Compose an error message listing invalid stream names
      report( ERROR, kFacilityString )
	 << 	"Invalid stops requested at:" ;
      Stream::Set legalRecords (
	 DataSourceController::potentialRecordsToRetrieve() );
      Stream::Set::const_iterator streamListEnd( iReadStreams.end() ) ;
      for ( Stream::Set::const_iterator streamName = iReadStreams.begin() ;
	    streamName != streamListEnd ;
	    ++streamName )
      {
	 if ( !(legalRecords.contains( *streamName )) )
	 {
	    report( ERROR, kFacilityString )
	       << " " << *streamName ;
	 }
      }
      report( ERROR, kFacilityString ) << endl ;
      return;
   }
#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   m_bufferToTrash = new char[ kTrashBufferSize ] ;
#endif
//  Set the input stream reference and flag success
   setIsSequentiallyAccessing( true );
   setInitializationStatus( kInitNoError );
}

// BinarySourceController::BinarySourceController( const BinarySourceController& )
// {
// }

BinarySourceController::~BinarySourceController()
{
   //Close the input stream
   m_file.close();
#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   delete [] m_bufferToTrash ;
#endif
}

//
// assignment operators
//
// const BinarySourceController& BinarySourceController::operator=( const BinarySourceController& )
// {
// }

//
// member functions
//
DataSourceController::SyncStatus
BinarySourceController::synchronizeSource( const SyncValue& iSyncTo )
{
   SyncStatus returnValue(kSyncNoError);

   if( currentSyncValue() != iSyncTo ){
      if( currentSyncValue() > iSyncTo ){
	 setCurrentStop( Stream::kNone ); // Have already read past iSyncTo
	 return kSyncFailedToSync;
      }

//  Loop for reading and discarding records with SyncValue < iSyncTo

      DABoolean continueLoop(true);

      SyncValue syncValueOfNextRecord;
      Stream::Type tempStreamType;
      SearchStatus searchStatus;
      
      do{ searchStatus = findNextRecord( syncValueOfNextRecord,
					 tempStreamType );

//  Encountered an error while reading records
//  Drop out of the continueLoop if end of file reached:  still returns a
//    valid record to the user
//  A read error is fatal, causing an immediate return, settingCurrentStop
//    to no record current

	 if(kSearchNoError != searchStatus ){
	    if( kSearchEndOfSource == searchStatus ) {
	       returnValue = kSyncWarningAtEndOfSource;
	       continueLoop = false;
	    } else {
	       setCurrentStop( Stream::kNone );
	       return convertSearchStatusToSyncStatus( searchStatus );
	    }

//  Read another record successfully

	 } else {
	    if( syncValueOfNextRecord <= iSyncTo ){
	       //Goto that record, i.e. make nextRecord current
	       if( kSearchNoError != ( searchStatus =
				       gotoNextRecord() )) {
                  // Error occurred while reading event record
		  setCurrentStop( Stream::kNone );
		  return convertSearchStatusToSyncStatus( searchStatus );
	       }

//  Read beyond desired iSyncTo.  Exit loop now and return previous record

	    } else {
	       continueLoop = false;
	    }
	 }
      }while(continueLoop );
   }
   return returnValue;
}

DataSourceController::SearchStatus
BinarySourceController::findNextRecord(SyncValue& oSyncValueOfNextRecord,
				     Stream::Type& oRecordTypeOfNextRecord )
{
   if( ! m_havePeekedAhead){
      const Stream::Set& tempRecordsToRetrieve(recordsToRetrieve() );
      DABoolean isGood( true ) ;
      DABoolean isRecordToRetrieve( true ) ;

//    Read record headers until we find one which was requested

      do { 
	 
	 isGood = (kSearchNoError == movePeekToNextRecord());
	 if ( isGood ) {
	    isRecordToRetrieve = tempRecordsToRetrieve.contains( 
	                                           m_nextRecordType ) ;
	    if ( ! isRecordToRetrieve ) {
	       isGood = (kSearchNoError ==
			 ignoreRemainderOfUnwantedRecord() ) ;
	    }
	 }

      } while( isGood && ! isRecordToRetrieve ) ;

      // read 64 bit time stamp out of two 32-bit words
      UInt64 timeStamp=m_nextRecordHeader.timeMost();
      timeStamp=(timeStamp << 32) | m_nextRecordHeader.timeLeast();

      if( isGood ){
	 //Get the SyncValue for this record
	 if ( Stream::kEndRun != m_nextRecordType )
	 {  // SyncValue comes from run number and most recent event number
	    m_peekAheadSyncValue = SyncValue(
	       m_nextRecordHeader.runNumber(),
	       m_nextRecordHeader.eventNumber(),timeStamp);
	 }
	 else
	 {
            // The endRun record gets a syncValue corresponding to an
            // impossibly huge event number
	    m_peekAheadSyncValue = SyncValue( m_nextRecordHeader.runNumber(),
					      SyncValue::kMaxRunEventValue,
					      timeStamp);
	 }
      } else {
	 //Bad stuff happened
	 m_nextRecordType = Stream::kNone;
	 m_peekAheadSyncValue = SyncValue();
      }
      
      m_havePeekedAhead = true;
   }

   oRecordTypeOfNextRecord = m_nextRecordType;
   oSyncValueOfNextRecord = m_peekAheadSyncValue;

   // m_peekAheadStatus was set by movePeekToNextRecord()
   return m_peekAheadStatus;
}

DataSourceController::SearchStatus
BinarySourceController::gotoNextRecord( void )
{

   SyncValue syncValueOfRecord;
   Stream::Type streamTypeOfRecord = Stream::kNone ;

   SearchStatus searchStatus(kSearchNoError);

// Make sure that the record header has been read and that the
// input file is still readable

   if( kSearchNoError != ( searchStatus = 
			   findNextRecord( syncValueOfRecord, 
					   streamTypeOfRecord ) ) ){
      setCurrentStop( Stream::kNone );
      return searchStatus;
   }

//now get the Logical Record buffer object for this stream
   BDRecordBuffer* buffer = binaryProxyDeliverer().buffer( 
                                                        streamTypeOfRecord);
   
   if( 0 == buffer ) {
      //No buffer for this Stream
      setCurrentStop( Stream::kNone );
      report( ERROR , kFacilityString )
                 << "No buffer available from binaryProxyDeliverer "
                 << endl ;
      return kSearchProblemWithSource;
   }

// Copy the peek-ahead buffer contents into the event buffer
//  ProxyDeliv just gave us, and read the rest of the record into
//  that buffer

   int readStatus( 0 ) ;
   if ( m_reachedEOF )
   {
      readStatus = 0 ;  // Flag EOF without even trying to read
   }
   else
   {
      readStatus = buffer->read( m_file, m_nextRecordHeader ) ;
   }
// Error condition if readStatus less than or equal to zero
   if ( 0 >= readStatus )
   {
      // readStatus = 0 indicates EOF was reached
      if ( 0 == readStatus )
      {
	 m_peekAheadStatus = kSearchEndOfSource ;
	 m_reachedEOF = true ;
      }
      // readStatus < 0 flags a read error
      if ( 0 > readStatus )
      {
	 m_peekAheadStatus = kSearchProblemWithSource ;
	 report ( ERROR, kFacilityString )
	    <<"Read error in event record at run "
	    << m_nextRecordHeader.runNumber()
	    << ", event "
	    << m_nextRecordHeader.eventNumber()
	    << endl ;
      }
      setCurrentStop( Stream::kNone );
      return m_peekAheadStatus ;
   }

// Perform record validity checks: length, record type, ...
   if ( !(buffer->consistent ( m_nextRecordHeader )))
   {
      m_peekAheadStatus = kSearchUnknownError ;
      return m_peekAheadStatus ;
   }

   m_havePeekedAhead = false;  // This marks both that the peekAhead is
   // invalid and that m_file is positioned before the header of next rec

   //Tell BinaryProxyDeliverer to read the buffer we just filled
   if( !binaryProxyDeliverer().finishedWritingToBuffer( streamTypeOfRecord ) ){
      setCurrentStop( Stream::kNone );
      report( ERROR , kFacilityString )
                 << "Unable to mark finishedWritingToBuffer to "
		 << "binaryProxyDeliverer"
                 << endl ;
      return kSearchProblemWithSource;
   }

   //Tell the ProxyDeliverer that we have a new Record
   binaryProxyDeliverer().reset( streamTypeOfRecord,
			       syncValueOfRecord );

   setCurrentStop( streamTypeOfRecord );
   setSyncValue( syncValueOfRecord );

   return searchStatus;
}

void
BinarySourceController::implementSetForcedSequentialAccess( DABoolean )
{
   //Do nothing
}

BinaryProxyDeliverer&
BinarySourceController::binaryProxyDeliverer( void )
//  This simply recasts proxyDeliverer to BinaryProxyDeliverer so it
//    can be recognized as a local symbol for convenience and clarity
{
   return (BinaryProxyDeliverer& ) ( *(proxyDeliverer()) );
}


DataSourceController::SearchStatus
BinarySourceController::movePeekToNextRecord( void )
// movePeekToNextRecord reads the next record's 6 header words into
// the peekAheadBuffer

{
   DABoolean isGood(true);
   m_peekAheadStatus = kSearchUnknownError;

// Is the input stream at end of file?  Return error

   if ( m_reachedEOF )
   {
      m_nextRecordType = Stream::kNone ;
      m_peekAheadStatus = kSearchEndOfSource ;
      isGood = false ;
   }

// Read the record header for the next record
   if ( isGood )
   {
      int readStatus( m_nextRecordHeader.read( m_file ) ) ;
      if ( 0 >= readStatus )
      {
	 m_nextRecordType = Stream::kNone ;
	 m_peekAheadStatus = kSearchProblemWithSource ;
	 if ( 0 == readStatus )
	 {
	    m_peekAheadStatus = kSearchEndOfSource ;
	    m_reachedEOF = true ;
	 }
	 else
	 {
	    report( ERROR , kFacilityString )
		       << "Unable to read nextRecordHeader on "
		       << m_fileName
               << ", readStatus = " << readStatus
		       << endl ;
	 }
	 isGood = false ;
      }
   }

// Apparently CW10 reads blank inputs instead of flagging EOF
//   if ( isGood )
//   {
//#if defined(TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG)
//   const Uint32 tmp( (char*) (m_peekAheadBuffer.length()) ) ;
//  aStream = tmp ;
//const Stream::Type blank( "" ) ;
//if ( blank == aStream ) {
//#else
//aStream = Stream::Type( (char*) (header.length) ) ;
//if ( Stream::Type("") == aStream ) {
//#endif /* TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG */   
//      m_peekAheadRecord = Stream::kNone ;
//      m_peekAheadStatus = kSearchEndOfSource ;
//      isGood = false ;
//}

// Convert record type to stream type
   if( isGood )
   {
      m_nextRecordType = 
	 logicalRecordIDToStreamType( 
	    m_nextRecordHeader.recordType() );
      m_peekAheadStatus = kSearchNoError;
   }

   return m_peekAheadStatus;
}

DataSourceController::SearchStatus
BinarySourceController::ignoreRemainderOfUnwantedRecord( void )
{
// Read and verify event length
   m_peekAheadStatus  = kSearchNoError ;

// Trash all remaining words but the last
// Reminder: kMinRecordSize (=12) words were already read in
   int bytesToIgnore ( kBytesPerWord*
		       ( m_nextRecordHeader.recordLength() -
			 BDRecordHeader::kMinRecordSize - 1 ) ) ;
// If there were exactly 12 words in the record, we are done already.
   if ( 0 <= bytesToIgnore )
   {
#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
      int fileDescriptor = m_file.rdbuf()->fd() ;
#endif
// Ignore all the remaining words but the last
      if ( 0 < bytesToIgnore )
      {
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
	 m_file.ignore( bytesToIgnore ) ;
#else
	 int incrementalBytesToIgnore ( kTrashBufferSize ) ;
	 do
	 {
	    if ( incrementalBytesToIgnore > bytesToIgnore )
	    { incrementalBytesToIgnore = bytesToIgnore ; }
	    int n_read = ::read( fileDescriptor,
				 m_bufferToTrash,
				 incrementalBytesToIgnore ) ;
	    bytesToIgnore -= incrementalBytesToIgnore ;
	 } while ( 0 < bytesToIgnore ) ;
#endif
      }
// Check the final word against the event length
      UInt32 lengthCheck ;
      UInt32* wordToRead( &lengthCheck ) ;
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
      m_file.read( (char*)wordToRead, kBytesPerWord ) ;
      if ( m_file.eof() )
      {
	 m_reachedEOF = true ;
	 m_peekAheadStatus = kSearchEndOfSource ;
      }
#else
      int n_read = ::read( fileDescriptor,
			   (char*)wordToRead,  kBytesPerWord) ;
      if ( 0 >  n_read )
      {
	 m_peekAheadStatus = kSearchProblemWithSource ;
	 report( ERROR , kFacilityString )
                 << "Read error reading length of next record in "
                 << m_fileName
                 << endl ;
      }
      if ( 0 == n_read )
      {
	 m_reachedEOF = true ;
	 m_peekAheadStatus = kSearchEndOfSource ;
      }
#endif

#if ( AC_BIGENDIAN == 0 )
// On little endian machines, must byte swap lengthCheck -- file is bigendian
      lengthCheck = swapBytesInUInt32( lengthCheck ) ;
#endif
      if ( lengthCheck != m_nextRecordHeader.recordLength() )
      {
	 report ( ERROR, kFacilityString )
	    << "Length = "
	    << m_nextRecordHeader.recordLength()
	    << " in event record header is inconsistent with lengthcheck = "
	    << lengthCheck
	    << " at end of record "
	    << m_nextRecordHeader.eventNumber()
	    << endl ;
	 m_peekAheadStatus = kSearchProblemWithSource ;
      }
   }
   return m_peekAheadStatus ;
}
//
// const member functions
//
DABoolean
BinarySourceController::canRandomAccess( void ) const
{
   return false;
}

string
BinarySourceController::dataSourceID( void ) const
{
   return m_fileName;
}

string
BinarySourceController::parameters( void ) const
{
   return string("");
}

ProxyDeliverer*
BinarySourceController::createProxyDeliverer( void ) const
{
   // Create the requested proxy deliverer
   ProxyDeliverer* returnedProxyDeliverer( new BinaryProxyDeliverer );

   // (quick kludge by cdj to initialize ProxyDeliverer proxies correctly)
   const Stream::Set& streams = returnedProxyDeliverer->supplies();
   Stream::Set::const_iterator itEnd = streams.end();
   for( Stream::Set::const_iterator it = streams.begin();
        it != itEnd;
        ++it ) {
      returnedProxyDeliverer->keyedProxies( *it );
   }
   return returnedProxyDeliverer ;
}
//
// static member functions
//
const Stream::Type&
BinarySourceController::logicalRecordIDToStreamType( int iRecordID )
{
   typedef STL_MAP(int, Stream::Type) IDToTypeMap;

   static DABoolean isFirstTime(true);
   static IDToTypeMap idToTypeMap;

   if(isFirstTime){
      isFirstTime = false;
      idToTypeMap[ET_DATAEVENT]      = Stream::kEvent;
      idToTypeMap[ET_CALIBEVENT]     = Stream::kEvent;
      idToTypeMap[ET_MCEVENT]        = Stream::kEvent;
      idToTypeMap[ET_BEGINNORMALRUN] = Stream::kBeginRun;
      idToTypeMap[ET_BEGINCALIBRUN]  = Stream::kBeginRun;
      idToTypeMap[ET_BEGINMCRUN]     = Stream::kBeginRun;
      idToTypeMap[ET_BEGINRANDOMRUN] = Stream::kBeginRun;
      idToTypeMap[ET_ENDRUN]         = Stream::kEndRun;
      idToTypeMap[ET_STARTRUN]         = Stream::kStartRun;
      idToTypeMap[ET_PAUSERUN]         = Stream::kPauseRun;
   }

   IDToTypeMap::const_iterator itFind = idToTypeMap.find( iRecordID );

   if( itFind == idToTypeMap.end() ){
      return Stream::kNone;
   }

   return (*itFind).second;
}
