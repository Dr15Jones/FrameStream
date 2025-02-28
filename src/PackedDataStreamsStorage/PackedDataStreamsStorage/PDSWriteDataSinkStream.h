#if !defined(PACKEDDATASTREAMSSTORAGE_PDSWRITEDATASINKSTREAM_H)
#define PACKEDDATASTREAMSSTORAGE_PDSWRITEDATASINKSTREAM_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSWriteDataSinkStream
// 
/**\class PDSWriteDataSinkStream PDSWriteDataSinkStream.h PackedDataStreamsStorage/PDSWriteDataSinkStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 16:50:21 EDT 2000
// $Id: PDSWriteDataSinkStream.h,v 1.1.1.1 2000/09/29 17:49:40 cdj Exp $
//
// Revision history
//
// $Log: PDSWriteDataSinkStream.h,v $
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files
#include <vector>
#include <map>

// user include files
#include "StorageManagement/SMSinkStream.h"
#include "DataHandler/DataKey.h"

// forward declarations
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
class PDSPackerBase;

class PDSWriteDataSinkStream : public SMSinkStream
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      class PackerHolder {
	 public:
	    PackerHolder( const STL_VECTOR(PDSPackerBase*)* iPackers,
			  DABoolean iShouldIncrement = true ) :
	       m_packers(iPackers),
	       m_index(0),
               m_shouldIncrement(iShouldIncrement){}
	    
	    PackerHolder() : m_packers(0), m_index(0) {}

	    PDSPackerBase* packer() {
	       return (*m_packers)[ m_shouldIncrement? m_index++ : m_index ];
	    }
	 private:
	    const STL_VECTOR(PDSPackerBase*)* m_packers;
	    UInt32 m_index;
	    DABoolean m_shouldIncrement;
      };

      // ---------- Constructors and destructor ----------------
      PDSWriteDataSinkStream();
      virtual ~PDSWriteDataSinkStream();

      // ---------- member functions ---------------------------
      virtual void put( const char * iFieldName, char );
      virtual void put( const char * iFieldName, short );
      virtual void put( const char * iFieldName, int );
      virtual void put( const char * iFieldName, long );

      virtual void put( const char * iFieldName, unsigned char );
      virtual void put( const char * iFieldName, unsigned short );
      virtual void put( const char * iFieldName, unsigned int );
      virtual void put( const char * iFieldName, unsigned long );

      virtual void put( const char * iFieldName, float );
      virtual void put( const char * iFieldName, double );
      virtual void put( const char * iFieldName, const string& );

      virtual void put( const char * iFieldName, const SMContentsBase& );

      virtual void beginObject( const TypeTag& );
      virtual void endObject();

      void setContainer( STL_VECTOR(UInt32)& iContainer ) {
	 m_container = & iContainer;
      }
      
      void setPackers( const STL_MAP(TypeTag, STL_VECTOR(PDSPackerBase*) )&
      iPackers ) { m_typeToPackersMap = & iPackers; }

      void setTypeIndex( UInt32 iTypeIndex ) {
	 m_typeIndex = iTypeIndex;
      }
      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSWriteDataSinkStream( const PDSWriteDataSinkStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSWriteDataSinkStream& operator=( const PDSWriteDataSinkStream& ); // stop default

      // ---------- private member functions -------------------
      void addToContainerIfPackWordFull( UInt32& ioOverflowWord ) {
	    if( m_startBit >= 32 ) {
	       m_startBit -=32;
	       (*m_container).push_back(m_packWord);
	       m_packWord = ioOverflowWord;
	       ioOverflowWord = 0;
	    }
      }


      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      STL_VECTOR(UInt32)* m_container;
      const STL_MAP(TypeTag, STL_VECTOR(PDSPackerBase*) )* m_typeToPackersMap;
      STL_VECTOR(PackerHolder) m_packerStack;
      PackerHolder m_presentPacker;
      UInt32 m_typeIndex;
      UInt32 m_startSizeOfContainer;

      UInt32 m_packWord;
      unsigned char m_startBit;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsStorage/Template/PDSWriteDataSinkStream.cc"
//#endif

#endif /* PACKEDDATASTREAMSSTORAGE_PDSWRITEDATASINKSTREAM_H */
