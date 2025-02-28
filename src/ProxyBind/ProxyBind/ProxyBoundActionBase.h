#if !defined(PROXYBIND_PROXYBOUNDACTIONBASE_H)
#define PROXYBIND_PROXYBOUNDACTIONBASE_H
// -*- C++ -*-
//
// Package:     ProxyBind
// Module:      ProxyBoundActionBase
// 
// Description: Base class for an Algorithm bound to a Proxy, where the 
//              Algorithm must be rerun after a certain Record changes
//              but before the Proxy's main algorithm is run.
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Sat Feb 27 10:13:58 EST 1999
// $Id: ProxyBoundActionBase.h,v 1.2 2003/05/31 23:49:24 cdj Exp $
//
// Revision history
//
// $Log: ProxyBoundActionBase.h,v $
// Revision 1.2  2003/05/31 23:49:24  cdj
// use new Record::cacheIdentifier() instead of Record::syncValue() to deterimine if the Record has changed since the last time a bound method was called.
//
// Revision 1.1.1.1  1999/03/04 19:11:56  cdj
// first submission
//

// system include files

// user include files
#include "DataHandler/Stream.h"
#include "DataHandler/SyncValue.h"

// forward declarations
class Frame;
class Record;

class ProxyBoundActionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ProxyBoundActionBase( const Stream::Type& iStream );
      virtual ~ProxyBoundActionBase();

      // ---------- member functions ---------------------------
      void execute( const Frame& iFrame );

      // ---------- const member functions ---------------------
      const Stream::Type& boundStream() const {
	 return m_stream; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementExecute( const Record& iRecord ) = 0;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ProxyBoundActionBase(); //stop default
      ProxyBoundActionBase( const ProxyBoundActionBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ProxyBoundActionBase& operator=( const ProxyBoundActionBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Stream::Type m_stream;
      unsigned long m_lastCacheIdentifier;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "ProxyBind/Template/ProxyBoundActionBase.cc"
//#endif

#endif /* PROXYBIND_PROXYBOUNDACTIONBASE_H */
