#if !defined(FRAMEACCESS_VALUEPROXY_H)
#define FRAMEACCESS_VALUEPROXY_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      ValueProxy
// 
// Description: Templated implementation of Proxy for holding a value.
//
// Usage:
//     ValueProxy is a concrete implementation of DataProxys that are 
//     designed to hold a value with which they get initizlied.
//     The ProxyTemplate requires implementation of two abstract 
//     functions, `invalidateCache' and `faultHandler'. The implementation 
//     of these functions is "trivial", just supplying back the initial value.
//
// Author:      Martin Lohner
// Created:     Thu Dec 11 15:49:42 EDT 1997
// $Id: ValueProxy.h,v 1.2 1998/09/25 19:57:55 cdj Exp $
//
// Revision history
//
// $Log
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h" // superclass

// forward declarations
class Record ;
class DataKey ;

template < class T >
class ValueProxy : public ProxyTemplate< T >
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      ValueProxy( const T* value );
      virtual ~ValueProxy() ;

      // member functions

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const T* faultHandler( const Record& aDict ,
				     const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      ValueProxy() ; // stop default
      ValueProxy( const ValueProxy< T >& ) ; // stop default

      // assignment operator(s)
      const ValueProxy& operator=( const ValueProxy< T >& ) ; // stop default

      // private member functions

      // private const member functions

      // data members
      const T* m_ptr ;

      // static data members

};

// inline function definitions

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "FrameAccess/Template/ValueProxy.cc"
#endif

#endif /* FRAMEACCESS_VALUEPROXY_H */
