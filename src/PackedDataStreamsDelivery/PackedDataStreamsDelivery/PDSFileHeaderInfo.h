#if !defined(PACKEDDATASTREAMSDELIVERY_PDSFILEHEADERINFO_H)
#define PACKEDDATASTREAMSDELIVERY_PDSFILEHEADERINFO_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSFileHeaderInfo
// 
/**\class PDSFileHeaderInfo PDSFileHeaderInfo.h PackedDataStreamsDelivery/PDSFileHeaderInfo.h

 Description: Reads and manages the data from a PDS file's header

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Dec 12 18:52:27 EST 2003
// $Id: PDSFileHeaderInfo.h,v 1.1 2003/12/15 17:04:17 cdj Exp $
//
// Revision history
//
// $Log: PDSFileHeaderInfo.h,v $
// Revision 1.1  2003/12/15 17:04:17  cdj
// first submission
//

// system include files
#include <iostream>
#include <string>
#include <vector>
#include <map>

// user include files
#include "DataHandler/StreamType.h"
#include "DataHandler/DurableDataKey.h"

// forward declarations
class PDSTypeToUnpackingInfoMap;
class PDSIstreamWordReader;

class PDSFileHeaderInfo
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum {kFirstProxyIndex =0 };
      typedef PDSTypeToUnpackingInfoMap TypeToUnpackingInfoMap;
      typedef std::map<StreamType, std::vector<DurableDataKey> > StreamTypesMap;

      // ---------- Constructors and destructor ----------------
      PDSFileHeaderInfo(istream& iIStream );
      virtual ~PDSFileHeaderInfo();

      // ---------- member functions ---------------------------
      PDSIstreamWordReader* wordReader() { return m_wordReader; }
      void changeFile( std::istream& iStream);

      TypeToUnpackingInfoMap* dropOwnershipOfTypeToUnpackingInfoMap();

      TypeToUnpackingInfoMap* typeToUnpackingInfoMap() {
	 return m_typeToUnpackingInfoMap; }

      StreamTypesMap& streamProxyFactoryInfoMap() {
	 return m_streamProxyFactoryInfoMap;
      }
      // ---------- const member functions ---------------------
      const TypeToUnpackingInfoMap* typeToUnpackingInfoMap() const {
	 return m_typeToUnpackingInfoMap; }
      
      const StreamType& recordIndexToStreamType( UInt32 iRecordIndex ) const {
	 return m_indexToStreamType[iRecordIndex]; }

      const std::vector<StreamType>& indexToStreamType() const {
	 return m_indexToStreamType; }

      const StreamTypesMap& streamProxyFactoryInfoMap() const {
	 return m_streamProxyFactoryInfoMap;
      }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSFileHeaderInfo( const PDSFileHeaderInfo& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSFileHeaderInfo& operator=( const PDSFileHeaderInfo& ); // stop default

      // ---------- private member functions -------------------
      void readHeader( std::istream& );
      void readStreams( const UInt32* &iHeader );

      void readNameList( const UInt32* & ioHeader, 
			 std::vector<string>& oNames );

      void readTypeNames(const UInt32*& ioHeader, 
			 std::vector<string>& oNames );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      std::vector<StreamType> m_indexToStreamType;
      TypeToUnpackingInfoMap* m_typeToUnpackingInfoMap;

      StreamTypesMap m_streamProxyFactoryInfoMap;

      PDSIstreamWordReader* m_wordReader;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSFileHeaderInfo.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSFILEHEADERINFO_H */
