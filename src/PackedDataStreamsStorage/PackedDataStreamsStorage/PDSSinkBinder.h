#if !defined(PACKEDDATASTREAMSSTORAGE_PDSSINKBINDER_H)
#define PACKEDDATASTREAMSSTORAGE_PDSSINKBINDER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSinkBinder
// 
/**\class PDSSinkBinder PDSSinkBinder.h PackedDataStreamsStorage/PDSSinkBinder.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 22 14:42:27 EDT 2000
// $Id: PDSSinkBinder.h,v 1.2 2001/06/15 21:07:21 cdj Exp $
//
// Revision history
//
// $Log: PDSSinkBinder.h,v $
// Revision 1.2  2001/06/15 21:07:21  cdj
// can now specify data (not) to store
//
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files

// user include files
#include "DataStorage/DataSinkBinder.h"
#include "DataStorage/StreamToDataStringTagsToStoreMap.h"

// forward declarations

class PDSSinkBinder : public DataSinkBinder
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSinkBinder( const string& iFileName,
		     const Stream::Set& iBindStreams );
      PDSSinkBinder( const string& iFileName,
		     const Stream::Set& iBindStreams,
		     const StreamToDataStringTagsToStoreMap& iStreamsDataMap );
      virtual ~PDSSinkBinder();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual DataSinkController*
        createDataSinkController( void ) const;

      string fileName( void ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSSinkBinder( const PDSSinkBinder& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSinkBinder& operator=( const PDSSinkBinder& ); // stop default

      // ---------- private member functions -------------------
      DataSinkController* createUsingAll() const;
      DataSinkController* createSpecifyingData() const;

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      StreamToDataStringTagsToStoreMap* m_streamsDataMap;
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsStorage/Template/PDSSinkBinder.cc"
//#endif

#endif /* PACKEDDATASTREAMSSTORAGE_PDSSINKBINDER_H */
