#if !defined(DATASTORAGE_SINKFORMAT_H)
#define DATASTORAGE_SINKFORMAT_H
// -*- C++ -*-
//
// Package:     <DataStorage>
// Module:      SinkFormat
// 
// Description: Base Class for all <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 25 18:10:42 EDT 1998
// $Id: SinkFormat.h,v 1.6 2001/06/15 21:05:15 cdj Exp $
//
// Revision history
//
// $Log: SinkFormat.h,v $
// Revision 1.6  2001/06/15 21:05:15  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.5  1998/11/10 23:13:08  mkl
// dont need 'type' anymore, since using generic (but less safe) factory
//
// Revision 1.4  1998/11/09 21:25:45  mkl
// loadable classes know their own factorySymbol string
//
// Revision 1.3  1998/07/29 02:15:49  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.2  1998/07/25 16:21:00  mkl
// allow static linking of source/sink formats
//
// Revision 1.1  1998/06/17 18:20:13  mkl
// allow dynamic loading of source and sink formats
//

// system include files

// user include files
#include "DataHandler/Stream.h"
#include "DataStorage/StreamToDataStringTagsToStoreMap.h"

// forward declarations
class DataSinkBinder;
#include "STLUtility/fwd_set.h"
#include <set>
#if !defined(_sinkformat_extensions_)
#define _sinkformat_extensions_ STL_SET( string )
#endif

class SinkFormat
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef _sinkformat_extensions_ Extensions;

      // ---------- Constructors and destructor ----------------
      SinkFormat();
      virtual ~SinkFormat();

      // ---------- member functions ---------------------------
      virtual DataSinkBinder* 
      createBinder( const string& iName,
		    const Stream::Set& iBindStreams ) = 0;

      virtual DataSinkBinder*
      createBinder( const string& iName,
		    const Stream::Set& iBindStreams,
                    const StreamToDataStringTagsToStoreMap& iStreamTagsMap);
                    
      // ---------- const member functions ---------------------
      const Extensions& extensions() const;

      virtual DABoolean canSpecifyDataToStore() const ;
      
      // ---------- static member functions --------------------
      static string factorySymbol();

   protected:
      // ---------- protected member functions -----------------
      void addExtension( const string& iExtension );

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SinkFormat( const SinkFormat& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SinkFormat& operator=( const SinkFormat& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Extensions& m_extensions;

      // ---------- static data members ------------------------
};

// inline function definitions

#endif /* DATASTORAGE_SINKFORMAT_H */
