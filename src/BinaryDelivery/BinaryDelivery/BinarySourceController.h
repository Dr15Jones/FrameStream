#if !defined(BINARYDELIVERY_BINARYSOURCECONTROLLER_H)
#define BINARYDELIVERY_BINARYSOURCECONTROLLER_H
// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BinarySourceController
// 
// Description: Contols reading Records from a binary file
//
// Usage:
//    <usage>
//
// Author:      David L. Kreinick
// Created:     Tue Aug 18 16:37:00 EDT 1998
// $Id: BinarySourceController.h,v 1.8 2003/11/18 22:17:39 dlk Exp $
//
// Revision history
//
// $Log: BinarySourceController.h,v $
// Revision 1.8  2003/11/18 22:17:39  dlk
// Repair reading files >2GB on Solaris
//
// Revision 1.7  2002/11/21 21:03:16  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.6  1999/06/09 17:57:08  dlk
// DLK: Changes forced by need to accomodate to large file bug on Solaris
//      BDRecordBuffer.h and BDRecordHeader.h:
// 	Changed istream to ifstream
// 	Return int rather than DABoolean from read functions
//      BinarySourceController.h
// 	New member data m_reachedEOF and m_bufferToTrash
//
// Revision 1.5  1999/04/15 19:11:26  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.4  1998/11/18 19:48:30  dlk
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
// Revision 1.3  1998/11/16 16:50:58  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
// Revision 1.2  1998/11/04 16:13:20  mkl
// got rid of gzip handling; changed istream to ifstream
//
// Revision 1.1.1.1  1998/11/03 20:46:42  dlk
// importing new BinaryDelivery sources
//
//

// system include files
#include "C++Std/fstream.h"

// user include files
#include "DataDelivery/DataSourceController.h"
#include "BinaryDelivery/BDRecordHeader.h"

// forward declarations
#include "STLUtility/fwd_set.h"
class BinaryProxyDeliverer;
class BinarySourceBinder;
template< class Binder > class ChainSourceController;

class BinarySourceController : public DataSourceController
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      friend class ChainSourceController< BinarySourceBinder >;

      // Constructors and destructor
      BinarySourceController( const string& iFileName,
			      const Stream::Set& iReadStreams,
			      BinaryProxyDeliverer* iDeliverer = 0);
      virtual ~BinarySourceController();

      // member functions
      virtual DataSourceController::SyncStatus 
           synchronizeSource( const SyncValue& iSyncTo );

      virtual DataSourceController::SearchStatus
               findNextRecord(SyncValue& oSyncValueOfNextRecord,
			      Stream::Type& oRecordTypeOfNextRecord );
      // Reads the input stream until it finds the next record which
      // the user marked as a recordToRetrieve.  Returns the SyncValue
      // and RecordType of that record.

      virtual DataSourceController::SearchStatus 
               gotoNextRecord( void );
      // Makes the next record of a type marked as a recordToRetrieve
      // into the current record

      // const member functions
      virtual DABoolean canRandomAccess( void ) const;

      virtual string dataSourceID( void ) const;
      virtual string parameters( void ) const;
      // static member functions

   protected:
      // protected member functions
      virtual void implementSetForcedSequentialAccess( DABoolean iFlag );

      // protected const member functions
      virtual ProxyDeliverer* createProxyDeliverer( void ) const;

   private:
      // Constructors and destructor
      BinarySourceController( void );
      BinarySourceController( const BinarySourceController& );

      // assignment operator(s)
      const BinarySourceController& operator=( const BinarySourceController& );

      // private member functions
      BinaryProxyDeliverer& binaryProxyDeliverer( void );
      SearchStatus movePeekToNextRecord( void );
      SearchStatus ignoreRemainderOfUnwantedRecord( void );

      // private const member functions

      // private static member functions
      static const Stream::Type& logicalRecordIDToStreamType( int iRecordID);  

      // data members
      string m_fileName ;                // File name of the input file
#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
      int m_fileDescriptor ;             // File descriptor from C read
#endif
      ifstream m_file ;                  // Input file stream
      BDRecordHeader m_nextRecordHeader; // 12-word buffer of header info
      Stream::Type m_nextRecordType;     // Record type of next record
      SyncValue m_peekAheadSyncValue;    // SyncValue of next record
      SearchStatus m_peekAheadStatus;    // I/O status of last read
// If m_havePeekedAhead is true, we have successfully read the header
// info for the next record, and are positioned in the file to read in
// the rawEvent from m_file.  If we don't want the next rawEvent, we
// have to advance m_file to the end of the event record.
      DABoolean m_havePeekedAhead;
      DABoolean m_reachedEOF;            // End-of-file reached on input
      char* m_bufferToTrash ;            // Pointer to buffer of data to ignore
      // static data members

};

// inline function definitions

#endif /* BINARYDELIVERY_BINARYSOURCECONTROLLER_H */
