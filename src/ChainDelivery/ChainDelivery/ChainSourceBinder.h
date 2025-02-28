#if !defined(CHAINDELIVERY_CHAINSOURCEBINDER_H)
#define CHAINDELIVERY_CHAINSOURCEBINDER_H
// -*- C++ -*-
//
// Package:     ChainDelivery
// Module:      ChainSourceBinder
// 
// Description: Binder for ChainSourceController
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Fri Jul 25 13:35:17 EDT 1997
// $Id: ChainSourceBinder.h,v 1.8 1998/06/17 18:25:41 mkl Exp $
//
// Revision history
//
// $Log: ChainSourceBinder.h,v $
// Revision 1.8  1998/06/17 18:25:41  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.7  1998/02/06 20:38:16  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.6  1997/09/18 20:50:53  cdj
// Changed Boolean to DABoolean
//
// Revision 1.5  1997/09/03 20:06:46  sjp
// Uses CPP macros for STL containers
//
// Revision 1.4  1997/08/14 11:43:59  sjp
// Mods to run under CW Pro 1
//
// Revision 1.3  1997/08/08 05:12:41  mkl
// added ChainSourceBinderBase.h
//
// Revision 1.2  1997/07/26 16:43:19  cdj
// Now holds vector of binders
//
// Revision 1.1.1.1  1997/07/25 23:35:24  cdj
// First submission. Compiles but untested
//

// system include files

// user include files
#include "ChainDelivery/ChainSourceBinderBase.h"

// forward declarations
#include "STLUtility/fwd_vector.h"
class DataSourceDescriptor;

#if !defined(_chainsourcebinder_binders_)
// the following CPP macro is used to avoid having a typedef
// from a template in the constructor arguments
#define _chainsourcebinder_binders_ STL_VECTOR( Binder )
#endif /* _chainsourcebinder_binders_ */

template< class Binder> 
class ChainSourceBinder : public ChainSourceBinderBase
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef _chainsourcebinder_binders_ Binders ;

      // Constructors and destructor
      ChainSourceBinder( const string& iName,
			 const Binders& iBinders,
			 const Stream::Set& iBindStreams );
      ChainSourceBinder( const string& iName,
			 const Stream::Set& iBindStreams );
      virtual ~ChainSourceBinder();

      // member functions
      void addSource( const Binder& iBinder );
      DABoolean removeSource( const DataSourceDescriptor& iDescriptor );

      // const member functions
      virtual DataSourceController* createDataSourceController() const ;

      virtual const Descriptors sources( void ) const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      ChainSourceBinder( const ChainSourceBinder& );

      // assignment operator(s)
      const ChainSourceBinder& operator=( const ChainSourceBinder& );

      // private member functions

      // private const member functions

      // data members
      Binders& m_binders;

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "ChainDelivery/Template/ChainSourceBinder.cc"
#endif

#endif /* CHAINDELIVERY_CHAINSOURCEBINDER_H */
