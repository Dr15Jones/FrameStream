#if !defined(PACKEDDATASTREAMSDELIVERY_PDSPACKERFACTORY_H)
#define PACKEDDATASTREAMSDELIVERY_PDSPACKERFACTORY_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSPackerFactory
// 
/**\class PDSPackerFactory PDSPackerFactory.h PackedDataStreamsDelivery/PDSPackerFactory.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Sep 19 14:17:43 EDT 2000
// $Id: PDSPackerFactory.h,v 1.2 2001/04/10 19:48:14 cdj Exp $
//
// Revision history
//
// $Log: PDSPackerFactory.h,v $
// Revision 1.2  2001/04/10 19:48:14  cdj
// can now store strings
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/pds_packing_enums.h"

// forward declarations
class PDSPackerBase;

class PDSPackerFactory
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSPackerFactory();
      //virtual ~PDSPackerFactory();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      PDSPackerBase* createPacker( const UInt32*& ioBuffer,
				   unsigned char& ioStartBit,
				   DABoolean iSwappedBytes ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSPackerFactory( const PDSPackerFactory& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSPackerFactory& operator=( const PDSPackerFactory& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSPackerFactory.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSPACKERFACTORY_H */
