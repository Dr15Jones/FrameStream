#if !defined(PACKEDDATASTREAMSDELIVERY_PDSCONTAINERSOURCESTREAM_H)
#define PACKEDDATASTREAMSDELIVERY_PDSCONTAINERSOURCESTREAM_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSContainerSourceStream
// 
/**\class PDSContainerSourceStream PDSContainerSourceStream.h PackedDataStreamsDelivery/PDSContainerSourceStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Apr 16 14:17:18 EDT 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files
#include <map>

// user include files
#include "DataHandler/DataKey.h"
#include "PackedDataStreamsDelivery/PDSTypeUnpackingInfo.h"
#include "PackedDataStreamsDelivery/Sources/PDSUnpackingSourceStreamBase.h"

// forward declarations
#include <map>
class PDSTypeSourceStream;

class PDSContainerSourceStream :  public PDSUnpackingSourceStreamBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSContainerSourceStream();
      virtual ~PDSContainerSourceStream();

      // ---------- member functions ---------------------------
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
      virtual SMSourceStream& operator>>( std::string& );

      virtual SMSourceStream& operator>>( const SMMakeContentsBase& );

      virtual void beginObject( const TypeTag& );
      virtual void endObject();

      // ---------- const member functions ---------------------
      virtual unsigned int versionUsed( const TypeTag& iType ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSContainerSourceStream( const PDSContainerSourceStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSContainerSourceStream& operator=( const PDSContainerSourceStream& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      PDSTypeSourceStream* m_typeSourceStream;
      const std::map<TypeTag, PDSTypeSourceStream*>* m_typePackingMap;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSContainerSourceStream.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSCONTAINERSOURCESTREAM_H */
