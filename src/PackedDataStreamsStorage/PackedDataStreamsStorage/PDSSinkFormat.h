#if !defined(PACKEDDATASTREAMSSTORAGE_PDSSINKFORMAT_H)
#define PACKEDDATASTREAMSSTORAGE_PDSSINKFORMAT_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSinkFormat
// 
/**\class PDSSinkFormat PDSSinkFormat.h PackedDataStreamsStorage/PDSSinkFormat.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 22 15:32:53 EDT 2000
// $Id: PDSSinkFormat.h,v 1.2 2001/06/15 21:07:21 cdj Exp $
//
// Revision history
//
// $Log: PDSSinkFormat.h,v $
// Revision 1.2  2001/06/15 21:07:21  cdj
// can now specify data (not) to store
//
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files

// user include files
#include "DataStorage/SinkFormat.h"

// forward declarations

class PDSSinkFormat : public SinkFormat
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSinkFormat();
      virtual ~PDSSinkFormat();

      // ---------- member functions ---------------------------
      virtual DataSinkBinder* createBinder( const string& iName,
                                            const Stream::Set& iBindStreams );

      virtual DataSinkBinder*
      createBinder( const string& iName,
		              const Stream::Set& iBindStreams,
                    const StreamToDataStringTagsToStoreMap& iStreamTagsMap);
       // ---------- const member functions ---------------------
      virtual DABoolean canSpecifyDataToStore() const ;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSSinkFormat( const PDSSinkFormat& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSinkFormat& operator=( const PDSSinkFormat& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsStorage/Template/PDSSinkFormat.cc"
//#endif

#endif /* PACKEDDATASTREAMSSTORAGE_PDSSINKFORMAT_H */
