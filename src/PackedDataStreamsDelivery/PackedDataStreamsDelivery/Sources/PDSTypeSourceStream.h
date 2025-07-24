#if !defined(PACKEDDATASTREAMSDELIVERY_PDSTYPESOURCESTREAM_H)
#define PACKEDDATASTREAMSDELIVERY_PDSTYPESOURCESTREAM_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSTypeSourceStream
// 
/**\class PDSTypeSourceStream PDSTypeSourceStream.h PackedDataStreamsDelivery/PDSTypeSourceStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Apr 16 14:16:40 EDT 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files
#include "PackedDataStreamsDelivery/Sources/PDSUnpackingSourceStreamBase.h"

// forward declarations

class PDSTypeSourceStream : public PDSUnpackingSourceStreamBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSTypeSourceStream();
      virtual ~PDSTypeSourceStream();

      //initialize object from file info
      void readPackingInfo( const UInt32*& ioHeader,
			    DABoolean iSwappedBytes );

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
      unsigned int version() const {
	 return m_version;
      }

      virtual unsigned int versionUsed( const TypeTag& iType ) const;
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSTypeSourceStream( const PDSTypeSourceStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSTypeSourceStream& operator=( const PDSTypeSourceStream& ); // stop default

      // ---------- private member functions -------------------
      void setupNextSource() {
	 nextSource()->setBufferInfo(startWord(), startBit() ) ; }

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      PDSUnpackingSourceStreamBase* m_lastSource;
      unsigned int m_version;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSTypeSourceStream.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSTYPESOURCESTREAM_H */
