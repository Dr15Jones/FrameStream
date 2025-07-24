// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceController
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sun Sep 24 16:25:45 EDT 2000
// $Id: PDSSourceController.cc,v 1.8 2003/08/12 20:40:08 tom Exp $
//
// Revision history
//
// $Log: PDSSourceController.cc,v $
// Revision 1.8  2003/08/12 20:40:08  tom
// Modifications to allow synchronization on out-of-order records
//
// Revision 1.7  2002/09/19 18:06:31  cdj
// can now read gzipped files with extension .pds.gz
//
// Revision 1.6  2001/05/31 16:57:14  cdj
// modifications necessary to allow chaining
//
// Revision 1.5  2000/10/07 18:24:24  cdj
// can now read files that were written from a different endian machine
//
// Revision 1.4  2000/10/06 17:41:27  cdj
// fixed bug when skipping over unwanted records
//
// Revision 1.3  2000/10/04 18:52:17  cdj
// PDSProxyDeliverer.cc
//
// Revision 1.2  2000/10/02 20:42:17  cdj
// now compiles and links using cxx
//
// Revision 1.1.1.1  2000/09/29 17:48:06  cdj
// imported
//

#include "Experiment/Experiment.h"

// system include files
#include <iostream>
#include <iomanip>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSSourceController.h"
#include "PackedDataStreamsDelivery/PDSProxyDeliverer.h"
#include "PackedDataStreamsDelivery/PDSRecordReadBuffer.h"
#include "PackedDataStreamsDelivery/PDSIstreamWordReader.h"

#include "PackedDataStreamsDelivery/PDSDExceptionBase.h"


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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSSourceController" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSourceController.cc,v 1.8 2003/08/12 20:40:08 tom Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
static const unsigned char kBytesPerWord = sizeof(UInt32)/sizeof(char);

//
// constructors and destructor
//
PDSSourceController::PDSSourceController(const std::string& iFileName,
					 const Stream::Set& iReadStreams,
					 PDSProxyDeliverer* iDeliverer ):
   DataSourceController( iDeliverer ),
   m_fileName(iFileName),
   m_fileHandler(iFileName.c_str()),
   m_havePeekedAhead(false),
   m_reachedEOF(false)
{
   try {
      if (
/*
#if defined(NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG)
	 ! (*m_fileStream.rdbuf()).is_open()
#else
	 ! m_fileStream.is_open()
#endif
*/
	 m_fileHandler.errorOccurred()
	 ) {
	 report( ERROR ,
		 kFacilityString )
		    << "\n\tUnable to open pds data file "
		    << m_fileName
		    << std::endl ;
	 setInitializationStatus( kInitSourceInaccessible ) ;
	 m_reachedEOF = true ;
	 return ;
      }
      // Verify that the specified record types are actually here
      else {

	 DABoolean isOK( setRecordsToRetrieve( iReadStreams ) );
	 if( ! isOK ){
	    setInitializationStatus( 
	       DataSourceController::kInitInvalidStopsForSource );
	    // Compose an error message listing invalid stream names
	    report( ERROR, kFacilityString ) << "File " << m_fileName
	       <<  " Invalid stops requested at:" ;
	    Stream::Set legalRecords (
	       DataSourceController::potentialRecordsToRetrieve() );
	    Stream::Set::const_iterator streamListEnd( iReadStreams.end() ) ;
	    for ( Stream::Set::const_iterator streamName = 
		     iReadStreams.begin() ;
		  streamName != streamListEnd ;
		  ++streamName )
	    {
	       if ( !(legalRecords.contains( *streamName )) )
	       {
		  report( ERROR, kFacilityString )
		     << " " << *streamName ;
	       }
	    }
	    report( ERROR, kFacilityString ) <<"\n   Valid stops are:";
       {
	    for ( Stream::Set::const_iterator streamName = 
		     legalRecords.begin() ;
		  streamName != legalRecords.end() ;
		  ++streamName )
	    {
		  report( ERROR, kFacilityString )
		     << " " << *streamName ;
	    }
       }
	    report( ERROR, kFacilityString ) << std::endl ;
	    return;
	 }
      }

      //force proxy deliverer to create the Proxies for the records we want to
      // read
      //if( iDeliverer == 0 ) {
         for( Stream::Set::const_iterator itStream = iReadStreams.begin();
	         itStream != iReadStreams.end();
	         ++itStream ) {
	         proxyDeliverer()->keyedProxies( *itStream );
         }
      //}
//  Set the input stream reference and flag success
      setIsSequentiallyAccessing( true );
      setInitializationStatus( kInitNoError );

   } catch( PDSDExceptionBase& iException ) {
      setInitializationStatus( kInitUnknownError );

      report(ERROR, kFacilityString ) <<"While initializing "<<iFileName
				      <<"\n"
				      << iException.what() << std::endl;
   }
}

// PDSSourceController::PDSSourceController( const PDSSourceController& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSSourceController::~PDSSourceController()
{
}

//
// assignment operators
//
// const PDSSourceController& PDSSourceController::operator=( const PDSSourceController& rhs )
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

DataSourceController::SyncStatus
PDSSourceController::synchronizeSource( const SyncValue& iSyncTo )
{
  SyncStatus returnValue(kSyncNoError);
  
  DABoolean exactMatchRequired = false;

//  report( DEBUG, kFacilityString )
//    << "Requested sync value (" << iSyncTo << "); "
//    << "Current sync value (" << currentSyncValue() << ")"
//    << std::endl;
  
  if ( currentSyncValue() != iSyncTo )
  {
    // Warn if we're supposed to sync (forward) to a record it looks
    //   like we have already passed
    if ( currentSyncValue() > iSyncTo )
    {
      report( WARNING, kFacilityString )
        << "Current sync value (" << currentSyncValue() << ") "
        << "suggests source is already past "
        << "requested sync value (" << iSyncTo << ")\n"
        << " . . . But will seek *forward* to look for requested event anyway"
        << std::endl;
      
      // In this case, we'll require an exact match as we step forward
      exactMatchRequired = true;
    }
    
    //  Loop forward, reading and discarding records with SyncValue < iSyncTo
     
    DABoolean continueLoop(true);
    
    SyncValue syncValueOfNextRecord;
    Stream::Type tempStreamType;
    SearchStatus searchStatus;

    do
    {
      // If we're currently at the record we want, exit loop
      if ( currentSyncValue() == iSyncTo )
      {
        continueLoop = false;
        break;
      }
        
      searchStatus = findNextRecord( syncValueOfNextRecord, tempStreamType );

      report(DEBUG, kFacilityString) 
        << "Next Record SyncValue: " << syncValueOfNextRecord << " "
        << "Search status: " << searchStatus << " "
        << "Current: " << currentSyncValue()
        << std::endl;

      //  Encountered an error while reading records
      //  Drop out of the continueLoop if end of file reached:  still returns a
      //    valid record to the user
      //  A read error is fatal, causing an immediate return, settingCurrentStop
      //    to no record current
      
      if ( kSearchNoError != searchStatus )
      {
        // EOF of source
        if ( kSearchEndOfSource == searchStatus ) 
        {
          returnValue = kSyncWarningAtEndOfSource;
          continueLoop = false;

          // If we're looking for an out-of-order record, we allow search
          //   to continue to next file in the chain (if there is one)
          // But at least warn the poor user
          if ( exactMatchRequired )
          {
            report( WARNING, kFacilityString )
              << "Reached end of current source looking for sync value ("
              << iSyncTo << ")\n"
              << " . . . Continuing search *forward* to find it in next file\n"
              << " . . . MAKE SURE THIS RECORD IS ACTUALLY IN THE PDS SOURCE!!"
              << std::endl;
          }
          else
          {
            setCurrentStop( Stream::kNone );
            return convertSearchStatusToSyncStatus( searchStatus );
          }          
        }

        // Any other read error
        else
        {
          setCurrentStop( Stream::kNone );
          return convertSearchStatusToSyncStatus( searchStatus );
        }
      }
      
      // We successfully read another record!
      else
      {
        // If the next record is the one we want, advance to it
        // If the next record is before what we're looking for, advance one
        if ( syncValueOfNextRecord <= iSyncTo )
        {
          // Goto that record, i.e. make nextRecord current
          if ( kSearchNoError != ( searchStatus = gotoNextRecord() ) ) {
            // Error occurred while reading event record
            setCurrentStop( Stream::kNone );
            return convertSearchStatusToSyncStatus( searchStatus );
          }
        }
        
        // Even if the next record looks out-of-order, if we need an
        //   exact match, keep on truckin'
        else if ( exactMatchRequired )
        {
          // Goto next record, i.e. make nextRecord current
          if ( kSearchNoError != ( searchStatus = gotoNextRecord() ) ) {
            // Error occurred while reading event record
            setCurrentStop( Stream::kNone );
            return convertSearchStatusToSyncStatus( searchStatus );
          }
        }

        // Read beyond desired record
        else
        {
          // Exit loop now and return previous record
          continueLoop = false;
        }
      }
      
    } while( continueLoop );
  }
  
  return returnValue;
}

DataSourceController::SearchStatus
PDSSourceController::findNextRecord(SyncValue& oSyncValueOfNextRecord,
                                     Stream::Type& oRecordTypeOfNextRecord )
{
   if( ! m_havePeekedAhead){
      const Stream::Set& tempRecordsToRetrieve(recordsToRetrieve() );
      DABoolean isGood( true ) ;
      DABoolean isRecordToRetrieve( true ) ;

//    Read record headers until we find one which was requested

      do { 
         
         isGood = (kSearchNoError == movePeekToNextRecord());
	 report(DEBUG, kFacilityString) << "next Record " << m_peekAheadRecordType.value() << std::endl;

         if ( isGood ) {
            isRecordToRetrieve = tempRecordsToRetrieve.contains( 
                                                   m_peekAheadRecordType ) ;
            if ( ! isRecordToRetrieve ) {
               isGood = (kSearchNoError ==
                         ignoreRemainderOfUnwantedRecord() ) ;
            }
         }

      } while( isGood && ! isRecordToRetrieve ) ;

      if( isGood ){
         //Get the SyncValue for this record
	 m_peekAheadSyncValue = m_nextRecordHeader.syncValue();
      } else {
         //Bad stuff happened
         m_peekAheadRecordType = Stream::kNone;
         m_peekAheadSyncValue = SyncValue();
      }
      
      m_havePeekedAhead = true;
   }

   oRecordTypeOfNextRecord = m_peekAheadRecordType;
   oSyncValueOfNextRecord = m_peekAheadSyncValue;

   // m_peekAheadStatus was set by movePeekToNextRecord()
   return m_peekAheadStatus;
}

DataSourceController::SearchStatus
PDSSourceController::gotoNextRecord( void )
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

   //read the Record's body
   if ( m_reachedEOF )
   {
      report(ERROR,kFacilityString) <<"trying to read past end of file"<<std::endl;
      m_peekAheadStatus = kSearchProblemWithSource ;
      setCurrentStop( Stream::kNone );
      return m_peekAheadStatus ;

   }
   else
   {
      try {
	 pdsProxyDeliverer().readBody( streamTypeOfRecord,
				       fileStream(), 
				       m_nextRecordHeader.bodyLength() ) ;
      } catch (PDSDExceptionBase& iException) {
         m_peekAheadStatus = kSearchProblemWithSource ;
         report ( ERROR, kFacilityString )
            <<"Read error in event record at run "
            << m_nextRecordHeader.syncValue().runNumber()
            << ", event "
            << m_nextRecordHeader.syncValue().eventNumber()
            << "\n"
	    << iException.what() << std::endl;
	 setCurrentStop( Stream::kNone );
	 return m_peekAheadStatus ;
      }
   }

   m_havePeekedAhead = false;  // This marks both that the peekAhead is
   // invalid and that m_fileStream is positioned before the header of next rec

   //Tell the ProxyDeliverer that we have a new Record
   pdsProxyDeliverer().reset( streamTypeOfRecord,
                               syncValueOfRecord );

   setCurrentStop( streamTypeOfRecord );
   setSyncValue( syncValueOfRecord );

   return searchStatus;
}

void
PDSSourceController::implementSetForcedSequentialAccess( DABoolean )
{
   //Do nothing
}

PDSProxyDeliverer&
PDSSourceController::pdsProxyDeliverer()
//  This simply recasts proxyDeliverer to PDSProxyDeliverer so it
//    can be recognized as a local symbol for convenience and clarity
{
   return static_cast<PDSProxyDeliverer&>( *(proxyDeliverer()) );
}

DataSourceController::SearchStatus
PDSSourceController::movePeekToNextRecord()
// movePeekToNextRecord reads the next record's 6 header words into
// the peekAheadBuffer

{
   DABoolean isGood(true);
   m_peekAheadStatus = kSearchUnknownError;

// Is the input stream at end of file?  Return error

   if ( m_reachedEOF )
   {
      m_peekAheadRecordType = Stream::kNone ;
      m_peekAheadStatus = kSearchEndOfSource ;
      isGood = false ;
   }

// Read the record header for the next record
   try {
      if ( isGood ) {
	 if( ! m_nextRecordHeader.read( 
	    *(pdsProxyDeliverer().wordReader()) ) ) {
	    //reached end of file
	    m_peekAheadRecordType = Stream::kNone ;
            m_peekAheadStatus = kSearchEndOfSource ;
            m_reachedEOF = true ;
         } else {	 
	    // Convert record type to stream type
	    m_peekAheadRecordType = 
	       pdsProxyDeliverer().recordIndexToStreamType( 
		  m_nextRecordHeader.recordType() );
	    m_peekAheadStatus = kSearchNoError;
	 }
      }
   } catch ( PDSDExceptionBase& iException ) {
      m_peekAheadRecordType = Stream::kNone ;
      m_peekAheadStatus = kSearchProblemWithSource ;
      
      report(ERROR, kFacilityString ) << iException.what() << std::endl;
   }

   return m_peekAheadStatus;
}

DataSourceController::SearchStatus
PDSSourceController::ignoreRemainderOfUnwantedRecord()
{
// Read and verify event length
   m_peekAheadStatus  = kSearchNoError ;

   try {
      // Trash all remaining words but the last
      pdsProxyDeliverer().wordReader()->skipWords(
	 m_nextRecordHeader.bodyLength() - 1);
      
      // Check the final word against the event length
      UInt32 lengthCheck ;
      UInt32* wordToRead( &lengthCheck ) ;

      if( ! pdsProxyDeliverer().wordReader()->readWords( 
	 wordToRead, 
	 1,
	 "reading Record length check") ) {
	 m_reachedEOF = true ;
	 m_peekAheadStatus = kSearchEndOfSource ;
      }
      
      if ( lengthCheck != m_nextRecordHeader.bodyLength() )
      {
	 report ( ERROR, kFacilityString )
	    << "Length = "
	    << m_nextRecordHeader.bodyLength()
	    << " in event record header is inconsistent with lengthcheck = "
	    << lengthCheck
	    << " at end of record "
	    << m_nextRecordHeader.syncValue()
	    << std::endl ;
	 m_peekAheadStatus = kSearchProblemWithSource ;
      }
   } catch (PDSDExceptionBase& iException ) {
      m_peekAheadStatus = kSearchProblemWithSource ;

      report( ERROR, kFacilityString ) << iException.what() << std::endl;
   }
   return m_peekAheadStatus ;
}



// const member functions
//
DABoolean
PDSSourceController::canRandomAccess( void ) const
{
   return false;
}

string
PDSSourceController::dataSourceID( void ) const
{
   return m_fileName;
}
string
PDSSourceController::parameters( void ) const
{
   return std::string("");
}

ProxyDeliverer*
PDSSourceController::createProxyDeliverer( void ) const
{
   //reset the file back to the beginning
   //const_cast<PDSSourceController*>(this)->m_fileStream.detach();
   const_cast<PDSSourceController*>(this)->m_fileHandler.resetToBeginning();
   // Create the requested proxy deliverer
   ProxyDeliverer* returnedProxyDeliverer = 
      new PDSProxyDeliverer(
	 const_cast<PDSSourceController*>(this)->fileStream()) ;

   return returnedProxyDeliverer ;
}

//
// static member functions
//






