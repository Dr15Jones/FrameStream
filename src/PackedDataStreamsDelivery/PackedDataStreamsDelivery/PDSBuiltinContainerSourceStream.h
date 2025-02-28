#if !defined(PACKEDDATASTREAMSDELIVERY_PDSBUILTINCONTAINERSOURCESTREAM_H)
#define PACKEDDATASTREAMSDELIVERY_PDSBUILTINCONTAINERSOURCESTREAM_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSBuiltinContainerSourceStream
// 
/**\class PDSBuiltinContainerSourceStream PDSBuiltinContainerSourceStream.h PackedDataStreamsDelivery/PDSBuiltinContainerSourceStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Apr  5 20:55:08 EST 2002
// $Id: PDSBuiltinContainerSourceStream.h,v 1.1 2002/04/06 19:03:18 cdj Exp $
//
// Revision history
//
// $Log: PDSBuiltinContainerSourceStream.h,v $
// Revision 1.1  2002/04/06 19:03:18  cdj
// added a specialized SourceStream to handle containers of builtin types
//

// system include files

// user include files
#include "StorageManagement/SMSourceStream.h"

// forward declarations
class SMPackerBase;

class PDSBuiltinContainerSourceStream : public SMSourceStream 
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSBuiltinContainerSourceStream():
         m_startWord(0), m_startBit(0), m_packer(0) {}
      //virtual ~PDSBuiltinContainerSourceStream();

      // ---------- member functions ---------------------------
      void reset( const UInt32* iStartWord, 
                  unsigned char iStartBit,
                  SMPackerBase* iPacker) {
         m_startWord = iStartWord;
         m_startBit = iStartBit;
         m_packer = iPacker;
      }

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
      const UInt32* startWord() const { return m_startWord;}
      unsigned char startBit() const { return m_startBit;}

      virtual unsigned int versionUsed( const TypeTag& iType ) const {
         return 0; }
      virtual DABoolean valid() const { return true; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSBuiltinContainerSourceStream( const PDSBuiltinContainerSourceStream& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSBuiltinContainerSourceStream& operator=( const PDSBuiltinContainerSourceStream& ); // stop default

      // ---------- private member functions -------------------
      void advanceStartWordIfNeeded() {
	 if( m_startBit >= 32) { m_startBit -=32; ++m_startWord; } }

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const UInt32* m_startWord;
      unsigned char m_startBit;
      SMPackerBase* m_packer;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSBuiltinContainerSourceStream.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSBUILTINCONTAINERSOURCESTREAM_H */
