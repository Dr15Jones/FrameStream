#if !defined(BINARYDELIVERY_BDRECORDBUFFER_H)
#define BINARYDELIVERY_BDRECORDBUFFER_H
// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BDRecordBuffer
// 
// Description: Manages memory buffer for one record (e.g. event record)
//
// Usage:
//    <usage>
//
// Author:      David L. Kreinick
// Created:     Mon Oct 19 12:46:42 EDT 1998
// $Id: BDRecordBuffer.h,v 1.4 1999/06/09 17:57:07 dlk Exp $
//
// Revision history
//
// $Log: BDRecordBuffer.h,v $
// Revision 1.4  1999/06/09 17:57:07  dlk
// DLK: Changes forced by need to accomodate to large file bug on Solaris
//      BDRecordBuffer.h and BDRecordHeader.h:
// 	Changed istream to ifstream
// 	Return int rather than DABoolean from read functions
//      BinarySourceController.h
// 	New member data m_reachedEOF and m_bufferToTrash
//
// Revision 1.3  1999/04/15 19:11:24  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.2  1998/11/18 19:48:28  dlk
// DLK: Intermediate update of BinaryDelivery code
//      The code has now been debugged to the point that it compiles,
//      and runs properly under Martin Lohner's test driver program.
//
//      There are still substantial problems:
//      1) BinaryRawEventProxy not yet written
//      2) Record types have not yet been defined
//      3) We haven't decided on BeginRun and EndRun record formats yet
//      and no doubt there are other problems I haven't discovered yet.
//
// Revision 1.1.1.1  1998/11/03 20:46:42  dlk
// importing new BinaryDelivery sources
//

// system include files

// user include files
#include "DataHandler/Stream.h"
#include "BinaryDelivery/BDRecordHeader.h"

// forward declarations

class BDRecordBuffer
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BDRecordBuffer(const Stream::Type& iStream,
		     UInt32 iBufferLengthInWords );
      virtual ~BDRecordBuffer();

      // member functions

      int read( ifstream& iIFStream, BDRecordHeader& iRecordHeader );
      DABoolean consistent( BDRecordHeader& iRecordHeader );

      // const member functions
      UInt32* beginOfBuffer() const ; // points to beginning of buffer
      UInt32  numberOfWords() const ; // Length of record in buffer
      UInt32  identifier() const ;    // Record's ASCII identifier
      UInt32  recordType() const ;    // Record's type
      const Stream::Type& streamType() const;
      UInt32 bufferLengthInWords() const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      BDRecordBuffer( const BDRecordBuffer& );

      // assignment operator(s)
      const BDRecordBuffer& operator=( const BDRecordBuffer& );

      // private member functions

      // private const member functions
      const UInt32* begin( void ) const;
      const UInt32* end( void ) const;

      // data members
      UInt32 m_bufferLengthInWords;
      UInt32* m_buffer;
      Stream::Type m_streamType;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "BinaryDelivery/Template/BDRecordBuffer.cc"
//#endif

#endif /* BINARYDELIVERY_BDRECORDBUFFER_H */
