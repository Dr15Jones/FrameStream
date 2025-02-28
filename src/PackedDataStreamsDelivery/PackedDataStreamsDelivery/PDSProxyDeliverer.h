#if !defined(PACKEDDATASTREAMSDELIVERY_PDSPROXYDELIVERER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSPROXYDELIVERER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSProxyDeliverer
// 
/**\class PDSProxyDeliverer PDSProxyDeliverer.h PackedDataStreamsDelivery/PDSProxyDeliverer.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Sep 18 16:29:33 EDT 2000
// $Id: PDSProxyDeliverer.h,v 1.8 2003/12/15 16:58:40 cdj Exp $
//
// Revision history
//
// $Log: PDSProxyDeliverer.h,v $
// Revision 1.8  2003/12/15 16:58:40  cdj
// moved file header reading and data caching to new object to be shared with event store
//
// Revision 1.7  2003/12/11 21:38:24  cdj
// added changeIStream method needed for EventStore
//
// Revision 1.6  2003/01/24 19:51:43  cdj
// use UnixFileHandleStream when reading gzipped files
//
// Revision 1.5  2002/11/21 21:17:00  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.4  2002/08/16 15:42:43  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.3  2001/05/31 16:57:20  cdj
// modifications necessary to allow chaining
//
// Revision 1.2  2000/10/07 18:24:28  cdj
// can now read files that were written from a different endian machine
//
// Revision 1.1.1.1  2000/09/29 17:48:04  cdj
// imported
//

// system include files
#include "C++Std/iostream.h"
#include "C++Std/fstream.h"
#include <vector>
#include <map>
#include <string>

// user include files
#include "DataDelivery/ProxyDeliverer.h"
#include "DataHandler/DurableDataKey.h"

#include "PackedDataStreamsDelivery/PDSFileHeaderInfo.h"

// forward declarations
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
class PDSTypeUnpackingInfo;
class PDSRecordReadBuffer;

class PDSSourceStream;
class PDSIstreamWordReader;
class PDSSourceController;
class PDSTypeToUnpackingInfoMap;

class PDSProxyDeliverer : public ProxyDeliverer
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef STL_VECTOR( PDSSourceStream* ) SourceStreams;
      typedef STL_MAP( Stream::Type, SourceStreams ) StreamToSourcesMap;
      typedef PDSTypeToUnpackingInfoMap TypeToUnpackingInfoMap;

      // ---------- Constructors and destructor ----------------
      PDSProxyDeliverer(istream& iIStream );
      virtual ~PDSProxyDeliverer();

      // ---------- member functions ---------------------------
      virtual void disable( const Stream::Type& aStream ) ;
      virtual void enable( const Stream::Type& aStream ) ;

      ///throws PDSDExceptionBase if problem encountered
      void readBody( const Stream::Type& iStream,
		     istream& iIFStream,
		     UInt32 iWordsToRead );

      PDSIstreamWordReader* wordReader() { return m_headerInfo.wordReader(); }
      
      //needed for chaining
      void changeSourceController( PDSSourceController& );
      //used by the EventStore
      void changeIStream( istream& iStream);

      // ---------- const member functions ---------------------
      const StreamType& recordIndexToStreamType( UInt32 iRecordIndex ) const {
	 return m_headerInfo.recordIndexToStreamType(iRecordIndex); }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void resetCache( const Stream::Type& aStream ) ;
      virtual void registerProxies( const Stream::Type& aStream ,
                                    KeyedProxies& aProxyList ) ;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSProxyDeliverer( const PDSProxyDeliverer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSProxyDeliverer& operator=( const PDSProxyDeliverer& ); // stop default

      // ---------- private member functions -------------------
      void initializeStreams();

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      PDSFileHeaderInfo m_headerInfo;
      STL_MAP(StreamType, PDSRecordReadBuffer*) m_streamToBufferMap;

      StreamToSourcesMap m_streamToSourcesMap;

      //needed for chaining
      DABoolean m_haveRecordsFromPreviousFiles;
      STL_MAP(StreamType, TypeToUnpackingInfoMap*) m_presentPackingInfo;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSProxyDeliverer.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSPROXYDELIVERER_H */
