#if !defined(PACKEDDATASTREAMSDELIVERY_PDSSOURCESTREAM_H)
#define PACKEDDATASTREAMSDELIVERY_PDSSOURCESTREAM_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceStream
// 
/**\class PDSSourceStream PDSSourceStream.h PackedDataStreamsDelivery/PDSSourceStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Sep 27 13:56:47 EDT 2000
// $Id: PDSSourceStream.h,v 1.5 2002/04/06 19:03:18 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceStream.h,v $
// Revision 1.5  2002/04/06 19:03:18  cdj
// added a specialized SourceStream to handle containers of builtin types
//
// Revision 1.2  2001/05/31 16:57:20  cdj
// modifications necessary to allow chaining
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files
#include <map>

// user include files
#include "DataHandler/DataKey.h"
#include "PackedDataStreamsDelivery/PDSProxyBuffer.h"
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"
#include "StorageManagement/SMSourceStream.h"

// forward declarations
#include "STLUtility/fwd_map.h"
class PDSTypeUnpackingInfo;

class PDSSourceStream : public SMSourceStream
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSourceStream(const STL_MAP(TypeTag, PDSTypeUnpackingInfo* )* iTypeInfo,
		      UInt32 iIndex ) : 
	 m_typePackingMap(iTypeInfo),
	 m_index(iIndex), m_isValid(false), m_buffer(0) {}

      virtual ~PDSSourceStream();

      // ---------- member functions ---------------------------
      void invalidate() { m_isValid = false; }
      void setBuffer( const PDSProxyBuffer& iBuffer ) {
	 m_buffer = iBuffer;
	 m_isValid = true;
	 m_startBit = 0;
	 m_startWord = m_buffer.buffer() + 2;
      }

      //needed for chaining files
      void setUnpackingInfoMap( 
            const STL_MAP(TypeTag, PDSTypeUnpackingInfo*)* iTypeInfo ) {
         m_typePackingMap = iTypeInfo ;
      }
      void setIndex( UInt32 iIndex ) { m_index = iIndex; }

      virtual SMSourceStream& operator>>( char  &);
      virtual SMSourceStream& operator>>( short &);
      virtual SMSourceStream& operator>>( int   &);
      virtual SMSourceStream& operator>>( long  &);

      virtual SMSourceStream& operator>>( unsigned char  &);
      virtual SMSourceStream& operator>>( unsigned short &);
      virtual SMSourceStream& operator>>( unsigned int   &);
      virtual SMSourceStream& operator>>( unsigned long  &);

      virtual SMSourceStream& operator>>( float  &);
      virtual SMSourceStream& operator>>( double &);
      virtual SMSourceStream& operator>>( string& );

      virtual SMSourceStream& operator>>( const SMMakeContentsBase& );

      virtual void beginObject( const TypeTag& );
      virtual void endObject();

      // ---------- const member functions ---------------------
      virtual unsigned int versionUsed( const TypeTag& iType ) const;
      virtual DABoolean valid() const { return m_isValid; }

      UInt32 index() const { return m_index; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      class UnpackerHolder {
	 public:
	    UnpackerHolder():
	       m_iterator(0) {}
	    UnpackerHolder(PDSTypeUnpackingInfo* iUnpackingInfo):
	       m_iterator(iUnpackingInfo->begin()) {}

	    PDSTypeUnpackingInfo::TypePacker& unpacker(){
	       return ( *(m_iterator++) ); }
	 private:
	    PDSTypeUnpackingInfo::TypePacker* m_iterator;
      };

      // ---------- Constructors and destructor ----------------
      PDSSourceStream( const PDSSourceStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSourceStream& operator=( const PDSSourceStream& ); // stop default

      // ---------- private member functions -------------------
      void advanceStartWordIfNeeded() {
	 if( m_startBit >= 32) { m_startBit -=32; ++m_startWord; } }

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const STL_MAP(TypeTag, PDSTypeUnpackingInfo* )* m_typePackingMap;
      UInt32 m_index;
      DABoolean m_isValid;
      PDSProxyBuffer m_buffer;

      UnpackerHolder m_unpackerHolder;

      const UInt32* m_startWord;
      unsigned char m_startBit;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSSourceStream.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSSOURCESTREAM_H */
