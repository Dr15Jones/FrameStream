// -*- C++ -*-
#if !defined(PACKAGE_PROXYNAMEPROXY_H)
#define PACKAGE_PROXYNAMEPROXY_H
//
// Package:     <package>
// Module:      proxynameProxy
//
/**\class proxynameProxy proxynameProxy.h package/proxynameProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "package/YourItemHere.h"

// forward declarations

class proxynameProxy : public ProxyBindableTemplate< YourItemHere >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef YourItemHere value_type;

      // Constructors and destructor
      proxynameProxy();
      virtual ~proxynameProxy();

      // member functions

      // use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      proxynameProxy( const proxynameProxy& );

      // assignment operator(s)
      const proxynameProxy& operator=( const proxynameProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (proxynameProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_proxyname ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "package/Template/proxynameProxy.cc"
//#endif

#endif /* PACKAGE_PROXYNAMEPROXY_H */
