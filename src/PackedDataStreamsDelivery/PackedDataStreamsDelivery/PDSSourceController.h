#if !defined(PACKEDDATASTREAMSDELIVERY_PDSSOURCECONTROLLER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSSOURCECONTROLLER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceController
// 
/**\class PDSSourceController PDSSourceController.h PackedDataStreamsDelivery/PDSSourceController.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sun Sep 24 15:50:22 EDT 2000
// $Id: PDSSourceController.h,v 1.4 2003/01/24 19:51:43 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceController.h,v $
// Revision 1.4  2003/01/24 19:51:43  cdj
// use UnixFileHandleStream when reading gzipped files
//
// Revision 1.3  2002/09/19 18:06:38  cdj
// can now read gzipped files with extension .pds.gz
//
// Revision 1.2  2001/05/31 16:57:20  cdj
// modifications necessary to allow chaining
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files
#include <string>
#include <fstream>

// user include files
#include "DataDelivery/DataSourceController.h"
#include "PackedDataStreamsDelivery/PDSRecordHeaderReader.h"
#include "PackedDataStreamsDelivery/PDSGunzipIFStreamHolder.h"

// forward declarations
class PDSProxyDeliverer;
template <class T> class ChainSourceController;
class PDSSourceBinder;

class PDSSourceController : public DataSourceController
{
      // ---------- friend classes and functions ---------------
      friend class ChainSourceController<PDSSourceBinder>;
      friend class PDSProxyDeliverer; //use to call setupProxyDeliverer
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSourceController(const std::string& iFileName,
			  const Stream::Set& iReadStreams,
			  PDSProxyDeliverer* iDeliverer = 0 );
      
      virtual ~PDSSourceController();

      // ---------- member functions ---------------------------
      virtual DataSourceController::SyncStatus 
           synchronizeSource( const SyncValue& iSyncTo );

      virtual DataSourceController::SearchStatus
               findNextRecord(SyncValue& oSyncValueOfNextRecord,
                              Stream::Type& oRecordTypeOfNextRecord );

      virtual DataSourceController::SearchStatus 
               gotoNextRecord();

      // ---------- const member functions ---------------------
      virtual DABoolean canRandomAccess( void ) const;

      virtual std::string dataSourceID( void ) const;
      virtual std::string parameters( void ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementSetForcedSequentialAccess( DABoolean iFlag );

      // ---------- protected const member functions -----------
      virtual ProxyDeliverer* createProxyDeliverer() const;

   private:
      // ---------- Constructors and destructor ----------------
      PDSSourceController( const PDSSourceController& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSourceController& operator=( const PDSSourceController& ); // stop default

      // ---------- private member functions -------------------
      PDSProxyDeliverer& pdsProxyDeliverer();
      std::istream& fileStream() { return m_fileHandler.stream(); }

      DataSourceController::SearchStatus movePeekToNextRecord();
      DataSourceController::SearchStatus ignoreRemainderOfUnwantedRecord();

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::string m_fileName ;                 // File name of the input file
      PDSGunzipIFStreamHolder m_fileHandler;
      Stream::Type m_peekAheadRecordType; // Record type of next record
      SyncValue m_peekAheadSyncValue;     // SyncValue of next record
      SearchStatus m_peekAheadStatus;     // I/O status of last read
      DABoolean m_havePeekedAhead;
      DABoolean m_reachedEOF;            // End-of-file reached on input
      PDSRecordHeaderReader m_nextRecordHeader;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSSourceController.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSSOURCECONTROLLER_H */
