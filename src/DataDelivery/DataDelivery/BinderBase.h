#if !defined(JOBCONTROL_BINDERBASE_H)
#define JOBCONTROL_BINDERBASE_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      BinderBase
// 
// Description: base class for type-safe binder wrappers
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Mar 31 17:31:59 EDT 1998
// $Id: BinderBase.h,v 1.6 1999/04/30 18:15:24 mkl Exp $
//
// Revision history
//
// $Log: BinderBase.h,v $
// Revision 1.6  1999/04/30 18:15:24  mkl
// first version of source act command handling
//
// Revision 1.5  1999/04/24 16:22:55  mkl
// keep track of DataSourceDescriptors, not just names of files
//
// Revision 1.4  1998/11/16 21:57:25  mkl
// added official kConstants binder type
//
// Revision 1.3  1998/11/16 17:31:14  mkl
// added kBinary to official source formats
//
// Revision 1.2  1998/10/01 14:41:01  mkl
// delayed stream activation until after calling init on Proc/ducers
//
// Revision 1.1  1998/06/17 18:18:18  mkl
// allow dynamic loading of source and sink formats
//
//

// system include files

// user include files
#include "DataDelivery/BinderType.h"
#include "DataDelivery/DataSourceBinder.h"

// forward declarations
class DataSourceBinder;

class DummySourceBinder : public DataSourceBinder {
   public:
      virtual DataSourceController*
      createDataSourceController( void ) const { return 0; }
};

class BinderBase
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef BinderType Type;
      typedef std::string Token;

      // BinderType Constants
      static const Type kNone;
      static const Type kRoar;
      static const Type kZFiles;
      static const Type kAscii;
      static const Type kBinary;
      static const Type kKarp;
      static const Type kDB;
      static const Type kConstants;
      static const Type kBlank;

      // Constructors and destructor
      BinderBase( DataSourceBinder* dsb, Type type=kNone );

      virtual ~BinderBase();

      // assignment operator(s)

      // member functions
      virtual DABoolean addBinder( BinderBase* iBinder ) = 0;
      
      // access routines
      DataSourceBinder& dsBinder()  { return *m_dsBinder; }
      DataSourceBinder* dsBinderP() { return m_dsBinder;  }
      DataSourceBinder* operator->() { 
	 return m_dsBinder; 
      }
      DataSourceBinder& operator*() { 
	 return *m_dsBinder; 
      }

      void setToken( const Token& iToken );
      const Token& token() const { return m_token; }

      const DataSourceBinder& dsBinder()  const { return *m_dsBinder; }
      const DataSourceBinder* dsBinderP() const { return m_dsBinder;  }
      const DataSourceBinder* operator->() const { 
	 return m_dsBinder; 
      }
      const DataSourceBinder& operator*() const { 
	 return *m_dsBinder; 
      }

      Type type() const { return m_type; }
      DABoolean isDummy() const { return( m_type == kNone ) ? true : false; }
      DABoolean isChain() const { return m_isChain; }

      // duplicate DataSourceDescriptor functionality
      void bindStreams( const Stream::Set& iBindStreams );
      const Stream::Set& boundStreams( void ) const;
      const std::string& dataSourceID( void ) const;
      const std::string& parameters( void ) const;
      
      // keep track of streams to-be-active
      void setToBeActiveStreams( const Stream::Set& iStreams );
      void clearToBeActiveStreams( void );
      DABoolean isToBeActiveStream( const Stream::Type& iStream ) const;

      // static member functions
   protected:
      // protected member functions
      void setDSBinder( DataSourceBinder* binder ) { m_dsBinder = binder; }
      void setChainFlag( DABoolean flag ) { m_isChain = flag; }

      // protected const member functions

      // data members
      Token m_token;

      // holding the real thing
      DataSourceBinder* m_dsBinder;
      // keep track of "types" and "properties"
      Type m_type;
      DABoolean m_isChain;

      // keep track of streams to-be-active
      Stream::Set& m_toBeActiveStreams;

   private:
      // Constructors and destructor
      BinderBase( const BinderBase& );                   // stop default
      const BinderBase& operator=( const BinderBase& );  // stop default

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions


#endif /* JOBCONTROL_BINDER_H */

