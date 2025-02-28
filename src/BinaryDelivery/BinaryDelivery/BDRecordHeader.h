#if !defined(PACKAGE_BDRECORDHEADER_H)
#define PACKAGE_BDRECORDHEADER_H
// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BDRecordHeader
// 
// Description: Holds the first 12 words = header of an event record
//
// Usage:
//   The first 11 words of an event are
//     0 Length
//     1 "RAWD"
//     2 Event Type / Version
//     3 Header field length
//     4 "HEAD"
//     5 Time, most significant bits
//     6 Time, least significant bits
//     7 Run Number
//     8 Event Number
//     9 Level3 Tag Word
//    10 Header field length (repeated)
//     ... and every record must have at least one more word, the
//         repeated record length.
//     Binary delivery wants the length, record type, run number,
//       event number, and both time stamp words.
//       
// Author:      David L. Kreinick
// Created:     Tue Oct 27 16:46:40 EST 1998
// $Id: BDRecordHeader.h,v 1.7 2002/11/21 21:03:16 cleo3 Exp $
//
// Revision history
//
// $Log: BDRecordHeader.h,v $
// Revision 1.7  2002/11/21 21:03:16  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.6  2001/05/22 21:07:37  bkh
// Fix event time decoding
//
// Revision 1.5  1999/06/23 17:52:50  dlk
// Dump record header if fatal formatting error detected
//
// Revision 1.4  1999/06/09 17:57:07  dlk
// DLK: Changes forced by need to accomodate to large file bug on Solaris
//      BDRecordBuffer.h and BDRecordHeader.h:
// 	Changed istream to ifstream
// 	Return int rather than DABoolean from read functions
//      BinarySourceController.h
// 	New member data m_reachedEOF and m_bufferToTrash
//
// Revision 1.3  1999/04/15 19:11:25  dlk
// DLK Major revision
// 	The EventHeader must be the first raw data unit inside the event
// 	The 6-word binary header is no longer made -- I use EventHeader
// 	The code supports all record types
// 		BeginRun, StartData, Event, Pause, EndRun ...
// 	Currently, the code currently works for bigendian machines only
//
// Revision 1.2  1998/11/18 19:48:29  dlk
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
#include "C++Std/fstream.h"

// user include files

// forward declarations

class BDRecordHeader
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum {
	 kMinRecordSize = 12  // Read in 12 words at a time
      } ;

      // ---------- Constructors and destructor ----------------
      BDRecordHeader();
      virtual ~BDRecordHeader();
//     const BDRecordHeader& operator=( const BDRecordHeader& );
//    The default copy constructor should work just fine

      // ---------- member functions ---------------------------
// Read the next 12 words from the input stream into the RecordHeader
      int read( ifstream& iIFStream ) ;

      // ---------- const member functions ---------------------
      const UInt32* recordHeaderBuffer() const ;

      UInt32 recordLength()  const ;
      UInt32 recordVersion() const ;
      UInt32 recordType()    const ;
      UInt32 runNumber()     const ;
      UInt32 eventNumber()   const ;
      UInt32 timeMost()      const ;
      UInt32 timeLeast()     const ;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      BDRecordHeader( const BDRecordHeader& ); // stop default

      // ---------- assignment operator(s) ---------------------

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      void dumpHeaderBufferContents() const ;

      // ---------- data members -------------------------------
      UInt32* m_headerBuffer ;
      UInt32  m_recordType ;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/BDRecordHeader.cc"
//#endif

#endif /* PACKAGE_BDRECORDHEADER_H */





