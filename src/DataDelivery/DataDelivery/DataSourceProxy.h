#if !defined(DATADELIVERY_DATASOURCEPROXY_H)
#define DATADELIVERY_DATASOURCEPROXY_H
// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      DataSourceProxy
// 
/**\class DataSourceProxy DataSourceProxy.h DataDelivery/DataSourceProxy.h

 Description: A Proxy base class for that should be used by Sources

 Usage:
    A Proxy for a Source should inherit from this class so that the
    correct type of exception will be thrown if no data is found in
    the source for that particular record

*/
//
// Author:      Chris D Jones
// Created:     Wed Dec  8 08:23:48 EST 1999
// $Id: DataSourceProxy.h,v 1.1 1999/12/10 14:24:48 cdj Exp $
//
// Revision history
//
// $Log: DataSourceProxy.h,v $
// Revision 1.1  1999/12/10 14:24:48  cdj
// added DataSourceProxy
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "DataHandler/Record.h"
#include "DAException/DANoDataException.h"

// forward declarations

template< class T>
class DataSourceProxy : public ProxyTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:

      // ---------- Constructors and destructor ----------------
      DataSourceProxy() {}
      //virtual ~DataSourceProxy();


   protected:

      virtual void throwFaultHandlerException( const Record& iRecord,
					       const DataKey& iKey ) const {
	 throw DANoDataException<T>(iRecord.stream(), iKey ); }
	 
   private:
      // ---------- Constructors and destructor ----------------
      //DataSourceProxy( const DataSourceProxy& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const DataSourceProxy& operator=( const DataSourceProxy& ); // stop default

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DataDelivery/Template/DataSourceProxy.cc"
//#endif

#endif /* DATADELIVERY_DATASOURCEPROXY_H */
