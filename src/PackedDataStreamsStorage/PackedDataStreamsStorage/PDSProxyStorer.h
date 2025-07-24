#if !defined(PACKEDDATASTREAMSSTORAGE_PDSPROXYSTORER_H)
#define PACKEDDATASTREAMSSTORAGE_PDSPROXYSTORER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSProxyStorer
// 
/**\class PDSProxyStorer PDSProxyStorer.h PackedDataStreamsStorage/PDSProxyStorer.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Sep 13 09:39:13 EDT 2000
// $Id: PDSProxyStorer.h,v 1.2 2002/08/16 15:43:35 cleo3 Exp $
//
// Revision history
//
// $Log: PDSProxyStorer.h,v $
// Revision 1.2  2002/08/16 15:43:35  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files
#include <iostream>
#include <map>
#include <vector>

// user include files
#include "DataStorage/ProxyStorer.h"
#include "DataHandler/Stream.h"
#include "DataHandler/DataKey.h"
#include "PackedDataStreamsStorage/PDSDataToStore.h"

// forward declarations
class PDSPackerBase;
class SMProxyWriterBase;

class PDSProxyStorer : public ProxyStorer
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef std::map<TypeTag, std::vector<PDSPackerBase*> > PackersForTypeMap;
      typedef std::map< TypeTag, SMProxyWriterBase* > WriterMap;

      // ---------- Constructors and destructor ----------------
      PDSProxyStorer(ostream& iOStream, 
		     const Stream::Set& iStreams,
		     const PDSDataToStore& iDataToStore );
      virtual ~PDSProxyStorer();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
      virtual StoreStatus implementStore( const Record& iRecord ) const ;

   private:
      // ---------- Constructors and destructor ----------------
      PDSProxyStorer( const PDSProxyStorer& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSProxyStorer& operator=( const PDSProxyStorer& ); // stop default

      // ---------- private member functions -------------------
      void writeHeader( const PDSDataToStore& iDataToStore );
      void createStreamList( std::vector<UInt32>& iContainer );
      void createTypesInfo( std::vector<UInt32>& iContainer,
			    const PDSDataToStore& iDataToStore,
			    std::set<TypeTag>& oFactoryTypes );
      void probeSchema( const std::set<TypeTag>& iFactoryTypes,
			std::set<TypeTag>& oSubTypes );
      void fillPackingInfo( std::vector<UInt32>& ioContainer,
			    std::set<TypeTag>::const_iterator iBegin,
			    std::set<TypeTag>::const_iterator iEnd );
      void createProxiesInRecordsInfo( 
	 std::vector<UInt32>& ioContainer, 
	 const PDSDataToStore& iDataToStore,
	 const std::set<TypeTag>& iFactoryTypes );

      void createProxyWriters( const std::set<TypeTag>& iFactoryTypes );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
     std::ostream& m_ostream;
      PDSDataToStore m_dataToStore;

      std::map<unsigned int, unsigned int > m_streamToIndexMap;
      PackersForTypeMap m_packersForTypeMap;
      std::vector<UInt32> m_dataBuffer;
      WriterMap m_writers;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsStorage/Template/PDSProxyStorer.cc"
//#endif

#endif /* PACKEDDATASTREAMSSTORAGE_PDSPROXYSTORER_H */
