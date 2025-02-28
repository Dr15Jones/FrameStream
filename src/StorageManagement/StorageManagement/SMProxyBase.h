#if !defined(STORAGEMANAGEMENT_SMPROXYBASE_H)
#define STORAGEMANAGEMENT_SMPROXYBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMProxyBase
// 
// Description: Interface for adding storage methods to a proxy
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed Jun  2 13:45:09 EDT 1999
// $Id: SMProxyBase.h,v 1.1.1.1 1999/09/13 21:21:42 cdj Exp $
//
// Revision history
//
// $Log: SMProxyBase.h,v $
// Revision 1.1.1.1  1999/09/13 21:21:42  cdj
// imported package
//

// system include files

// user include files

// forward declarations
class ProxyBase;
class SMSourceStream;

class SMProxyBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMProxyBase() : m_source(0) {}
      virtual ~SMProxyBase();

      // ---------- member functions ---------------------------
      virtual ProxyBase* proxyBase() = 0;

      //does not own the memory
      void setSourceStream( SMSourceStream* iSource ) {
	 m_source = iSource ; }

      // ---------- const member functions ---------------------
      SMSourceStream* sourceStream() const {
	 return m_source; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMProxyBase( const SMProxyBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMProxyBase& operator=( const SMProxyBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      //does not own this data, just refers to it.
      SMSourceStream* m_source;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMProxyBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPROXYBASE_H */
