#if !defined(PACKEDDATASTREAMSDELIVERY_PDSSOURCEFORMAT_H)
#define PACKEDDATASTREAMSDELIVERY_PDSSOURCEFORMAT_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSSourceFormat
// 
/**\class PDSSourceFormat PDSSourceFormat.h PackedDataStreamsDelivery/PDSSourceFormat.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Sep 25 15:38:37 EDT 2000
// $Id: PDSSourceFormat.h,v 1.2 2002/06/11 17:55:58 cdj Exp $
//
// Revision history
//
// $Log: PDSSourceFormat.h,v $
// Revision 1.2  2002/06/11 17:55:58  cdj
// added ability to set the default streams based on the contents of the source file
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
// imported
//

// system include files

// user include files
#include "DataDelivery/SourceFormat.h"

// forward declarations

class PDSSourceFormat : public SourceFormat
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSSourceFormat();
      virtual ~PDSSourceFormat();

      // ---------- member functions ---------------------------
      virtual BinderBase* createBinder( const string& iName,
                                        const Stream::Set& iBindStreams );

      // ---------- const member functions --------------------
      //determine the streams by looking at the file
      virtual const Stream::Set& defaultStreams( const string& iName);

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSSourceFormat( const PDSSourceFormat& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSSourceFormat& operator=( const PDSSourceFormat& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsDelivery/Template/PDSSourceFormat.cc"
//#endif

#endif /* PACKEDDATASTREAMSDELIVERY_PDSSOURCEFORMAT_H */
