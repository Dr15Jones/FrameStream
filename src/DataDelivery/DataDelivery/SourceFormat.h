#if !defined(DATADELIVERY_SOURCEFORMAT_H)
#define DATADELIVERY_SOURCEFORMAT_H
// -*- C++ -*-
//
// Package:     <DataDelivery>
// Module:      SourceFormat
// 
// Description: Base Class for all <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 25 18:10:42 EDT 1998
// $Id: SourceFormat.h,v 1.7 2002/06/11 17:53:50 cdj Exp $
//
// Revision history
//
// $Log: SourceFormat.h,v $
// Revision 1.7  2002/06/11 17:53:50  cdj
// added ability to set the default streams differently for each source name
//
// Revision 1.6  1999/06/12 00:03:30  mkl
// allow to specify default streams per source format
//
// Revision 1.5  1998/11/10 23:12:39  mkl
// dont need 'type' anymore, since using generic (but less safe) factory
//
// Revision 1.4  1998/11/09 21:25:36  mkl
// loadable classes know their own factorySymbol string
//
// Revision 1.3  1998/07/29 02:15:42  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.2  1998/07/25 16:20:51  mkl
// allow static linking of source/sink formats
//
// Revision 1.1  1998/06/17 18:19:56  mkl
// allow dynamic loading of source and sink formats
//

// system include files

// user include files
#include "DataHandler/Stream.h"
#include "DataDelivery/BinderType.h"

// forward declarations
#include <set>
#include <string>

class SourceFormat
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef std::set<std::string> Extensions;

      // ---------- Constructors and destructor ----------------
      SourceFormat( BinderType iType );
      virtual ~SourceFormat();

      // ---------- member functions ---------------------------
      virtual BinderBase* createBinder( const std::string& iName,
					const Stream::Set& iBindStreams ) = 0;

      // ---------- const member functions ---------------------
      const Extensions& extensions() const;
      const Stream::Set& defaultStreams() const;
      const BinderType& type() const;

      //override this if the source can choose its default streams
      // be looking at the file
      virtual const Stream::Set& defaultStreams( const std::string& iName);

      // ---------- static member functions --------------------
      static std::string factorySymbol();

   protected:
      // ---------- protected member functions -----------------
      void addExtension( const std::string& iExtension );
      void setDefaultStreams( const Stream::Set& iStreamSet );

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SourceFormat( const SourceFormat& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SourceFormat& operator=( const SourceFormat& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      BinderType m_type;
      Extensions& m_extensions;
      Stream::Set& m_defaultStreams;

      // ---------- static data members ------------------------
};

// inline function definitions
inline
const BinderType& 
SourceFormat::type() const
{
   return m_type;
}

#endif /* DATADELIVERY_SOURCEFORMAT_H */
