#if !defined(PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMTEMPLATE_H)
#define PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMTEMPLATE_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSUnpackingSourceStreamTemplate
// 
/**\class PDSUnpackingSourceStreamTemplate PDSUnpackingSourceStreamTemplate.h PackedDataStreamsDelivery/PDSUnpackingSourceStreamTemplate.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Apr 14 11:51:13 EDT 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files
#include "PackedDataStreamsDelivery/PDSUnpackingSourceStreamBase.h"

// forward declarations

template< class TSMPacker >
class PDSUnpackingSourceStreamTemplate : class PDSUnpackingSourceStreamBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSUnpackingSourceStreamTemplate(const TSMPacker& iPacker) :
	 m_packer( iPacker ) {}
      //virtual ~PDSUnpackingSourceStreamTemplate();

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
      virtual SMSourceStream& operator>>( string& );

      virtual SMSourceStream& operator>>( const SMMakeContentsBase& );

      virtual void beginObject( const TypeTag& );
      virtual void endObject();

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSUnpackingSourceStreamTemplate( const PDSUnpackingSourceStreamTemplate& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSUnpackingSourceStreamTemplate& operator=( const PDSUnpackingSourceStreamTemplate& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      TSMPacker m_packer;

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMTEMPLATE_H */
