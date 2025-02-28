#if !defined(JOBCONTROL_BINDER_H)
#define JOBCONTROL_BINDER_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      Binder
// 
// Description: Since ChainSourceBinder is template, need type-safe wrapper.
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Aug  4 17:31:59 EDT 1997
// $Id: Binder.h,v 1.5 1998/09/11 16:15:38 mkl Exp $
//
// Revision history
//
// $Log: Binder.h,v $
// Revision 1.5  1998/09/11 16:15:38  mkl
// g++ wants 'typename' hint
//
// Revision 1.4  1998/06/17 18:18:17  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.3  1998/03/31 20:58:22  cdj
// add BlankRecord as a source type
//
// Revision 1.2  1997/08/13 07:11:09  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.1  1997/08/08 05:21:16  mkl
// first attempt at chains-of-files
//

// system include files

// user include files
#include "JobControl/BinderBase.h"
#include "DataDelivery/Chainability.h"

// forward declarations

template< class DataBinder >
class Binder : public BinderBase
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef BinderType Type;
      typedef typename DataBinder::Chainability Chainability;

      // Constructors and destructor
      Binder( DataBinder* dsb=0, Type type=kNone );
      virtual ~Binder();

      // assignment operator(s)

      // member functions
      virtual DABoolean addBinder( BinderBase* iBinder );

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor

      // private member functions
      Binder( const Binder& );                  // stop default
      const Binder& operator=( const Binder& ); // stop default

      // front ends to externally-defined versions
      DataSourceBinder* makeChain( const string& iName,
				   const Stream::Set& iBindStreams );
      
      void addSourceToChain( DataSourceBinder& ioChainBinder,
			     DataSourceBinder& iDataBinder );
      
      // private const member functions

      // data members

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "JobControl/Template/Binder.cc"
#endif

#endif /* JOBCONTROL_BINDER_H */

