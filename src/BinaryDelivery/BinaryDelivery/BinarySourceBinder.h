#if !defined(BINARYDELIVERY_BINARYSOURCEBINDER_H)
#define BINARYDELIVERY_BINARYSOURCEBINDER_H
// -*- C++ -*-
//
// Package:     BinaryDelivery
// Module:      BinarySourceBinder
// 
// Description: Binds event, beginRun, or endRun stream to a binary file
//
// Usage:
//    Cribbed from CDJ's RoarSourceBinder
//
// Author:      David L. Kreinick
// Created:     Tue Nov  3 12:48:33 EST 1998
// $Id: BinarySourceBinder.h,v 1.3 1998/11/16 16:50:54 mkl Exp $
//
// Revision history
//
// $Log: BinarySourceBinder.h,v $
// Revision 1.3  1998/11/16 16:50:54  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
// Revision 1.2  1998/11/03 21:14:30  dlk
// DLK: Ooops!  Lost one line in the import
//
// Revision 1.1.1.1  1998/11/03 20:46:42  dlk
// importing new BinaryDelivery sources
//

// system include files

// user include files
#include "DataDelivery/DataSourceBinder.h"

// forward declarations
class BinarySourceController;
class BinaryProxyDeliverer;

class BinarySourceBinder : public DataSourceBinder
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef Chainable< BinarySourceBinder > Chainability;
      typedef BinaryProxyDeliverer Deliverer;
      typedef BinarySourceController Controller;

      // ---------- Constructors and destructor ----------------
      BinarySourceBinder( const std::string& iFileName,
			  const Stream::Set& iBindStreams );

      //Needed by STL, no one else should call this
      BinarySourceBinder();
      BinarySourceBinder( const BinarySourceBinder& ) ;

      virtual ~BinarySourceBinder();

      // assignment operator(s)
      const BinarySourceBinder& operator=( const BinarySourceBinder& iBinder );

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual DataSourceController* createDataSourceController() const;

      //Needed to be able to chain files
      BinarySourceController* createSourceController( 
	 BinaryProxyDeliverer* iDeliverer ) const;

      const std::string& fileName() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------
 
      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "BinaryDelivery/Template/BinarySourceBinder.cc"
//#endif

#endif /* BINARYDELIVERY_BINARYSOURCEBINDER_H */
