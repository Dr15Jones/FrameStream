#if !defined(PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSTRINGSOURCESTREAM_H)
#define PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSTRINGSOURCESTREAM_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSUnpackingStringSourceStream
// 
/**\class PDSUnpackingStringSourceStream PDSUnpackingStringSourceStream.h PackedDataStreamsDelivery/PDSUnpackingStringSourceStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Apr 15 10:28:01 EDT 2003
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files
#include "PackedDataStreamsDelivery/Sources/PDSUnpackingSourceStreamBase.h"

// forward declarations
class PDSUnpackingStringSameEndian
{
   public:
      void charToString(const char*& iArray, string& oString) {
	 oString = string(iArray);
      }
};

class PDSUnpackingStringDifferentEndian
{
   public:
      PDSUnpackingStringDifferentEndian() :
	 m_buffer(0),
	 m_bufferSize(0) {}
      ~PDSUnpackingStringDifferentEndian() {
	 delete [] m_buffer;
      }

      void charToString(const char*& iArray, string& oString);
   private:
      UInt32* m_buffer;
      unsigned int m_bufferSize;
};


#if defined(CANNOT_USE_ENUMS_AS_TEMPLATE_ARGS_BUG)
#define PDSSTRINGENDIAN int
#else
#define PDSSTRINGENDIAN PDSUnpackingStringEndian::Value
#endif

template <class T>
class PDSUnpackingStringSourceStream :  public PDSUnpackingSourceStreamBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSUnpackingStringSourceStream();
      virtual ~PDSUnpackingStringSourceStream();

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
      PDSUnpackingStringSourceStream( const PDSUnpackingStringSourceStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSUnpackingStringSourceStream& operator=( const PDSUnpackingStringSourceStream& ); // stop default

      // ---------- private member functions -------------------
      void fillStringFromBuffer(string& iData);

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      T m_endianHandler;

      // ---------- static data members ------------------------
      void throwException();
};


// inline function definitions

#endif /* PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSTRINGSOURCESTREAM_H */
