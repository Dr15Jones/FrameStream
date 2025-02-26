#if !defined(CHAINDELIVERY_CHAINSOURCEBINDERBASE_H)
#define CHAINDELIVERY_CHAINSOURCEBINDERBASE_H
// -*- C++ -*-
//
// Package:     ChainDelivery
// Module:      ChainSourceBinderBase
// 
// Description: Base for templated ChainSourceBinder<Binder>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Aug 7 17:05:17 EDT 1997
// $Id: ChainSourceBinderBase.h,v 1.5 1998/02/06 20:38:17 mkl Exp $
//
// Revision history
//
// $Log: ChainSourceBinderBase.h,v $
// Revision 1.5  1998/02/06 20:38:17  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.4  1997/09/18 20:50:55  cdj
// Changed Boolean to DABoolean
//
// Revision 1.3  1997/09/03 20:06:49  sjp
// Uses CPP macros for STL containers
//
// Revision 1.2  1997/08/14 11:44:00  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1  1997/08/08 05:12:29  mkl
// added ChainSourceBinderBase.h
//
//

// system include files

// user include files
#include "DataDelivery/DataSourceDescriptor.h"
#include "DataDelivery/DataSourceBinder.h"

#if !defined(_chainsourcebinderbase_descriptors_)
// the following CPP macro is used to avoid having a typedef
// from a template in the constructor arguments
#define _chainsourcebinderbase_descriptors_ STL_VECTOR( DataSourceDescriptor )
#endif /* _chainsourcebinder_descriptors_ */

class ChainSourceBinderBase : public DataSourceBinder
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef _chainsourcebinderbase_descriptors_ Descriptors ;

      // Constructors and destructor
      ChainSourceBinderBase( const string& iName,
			     const string& iParameters,
			     const Stream::Set& iBindStreams )
	 : DataSourceBinder( iName, iParameters, iBindStreams ) {}
      virtual ~ChainSourceBinderBase() {}

      // member functions
      virtual DABoolean removeSource( 
	 const DataSourceDescriptor& iDescriptor ) = 0;

      // const member functions
      virtual DataSourceController* 
        createDataSourceController( void ) const = 0;

      virtual const Descriptors sources( void ) const = 0;

      const string& name() const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      ChainSourceBinderBase( const ChainSourceBinderBase& );

      // assignment operator(s)
      const ChainSourceBinderBase& operator=( const ChainSourceBinderBase& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions
inline
const string& 
ChainSourceBinderBase::name() const 
{ 
   return dataSourceID(); 
}

#endif /* CHAINDELIVERY_CHAINSOURCEBINDERBASE_H */
