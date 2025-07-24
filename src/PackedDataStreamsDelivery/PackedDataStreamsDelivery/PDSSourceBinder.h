#if !defined(PACKEDDATASTREAMSDELIVERY_PDSSOURCEBINDER_H)
#define PACKEDDATASTREAMSDELIVERY_PDSSOURCEBINDER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceBinder
// 
/**\class PDSSourceBinder PDSSourceBinder.h PackedDataStreamsDelivery/PDSSourceBinder.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 15:38:30 EDT 2000
// $Id: PDSSourceBinder.h,v 1.2 2001/05/31 16:57:20 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceBinder.h,v $
// Revision 1.2  2001/05/31 16:57:20  cdj
// modifications necessary to allow chaining
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files

// user include files
#include "DataDelivery/DataSourceBinder.h"
#include "DataDelivery/Chainability.h"

// forward declarations
class PDSSourceController;
class PDSProxyDeliverer;

class PDSSourceBinder : public DataSourceBinder
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef Chainable< PDSSourceBinder > Chainability;
      typedef PDSSourceController Controller;
      typedef PDSProxyDeliverer Deliverer;
      
      // ---------- Constructors and destructor ----------------
      PDSSourceBinder( const std::string& iFileName,
		       const Stream::Set& iBindStreams );
      PDSSourceBinder() {}
      PDSSourceBinder( const PDSSourceBinder& ); 
      virtual ~PDSSourceBinder();

      // ---------- member functions ---------------------------
      const PDSSourceBinder& operator=( const PDSSourceBinder& ); // stop default

      // ---------- const member functions ---------------------
      virtual DataSourceController* createDataSourceController() const;
      const std::string& fileName() const;

      PDSSourceController* createSourceController(PDSProxyDeliverer* ) const;
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      
      // ---------- assignment operator(s) ---------------------
      //const PDSSourceBinder& operator=( const PDSSourceBinder& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSSourceBinder.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSSOURCEBINDER_H */
