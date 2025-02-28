#if !defined(BINARYDELIVERY_BINARYSOURCEFORMAT_H)
#define BINARYDELIVERY_BINARYSOURCEFORMAT_H
// -*- C++ -*-
//
// Package:     <BinaryDelivery>
// Module:      BinarySourceFormat
// 
// Description: Implementation of SourceFormat for Binary Files
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Nov 16 18:10:42 EDT 1998
// $Id: BinarySourceFormat.h,v 1.1 1998/11/16 16:51:01 mkl Exp $
//
// Revision history
//
// $Log: BinarySourceFormat.h,v $
// Revision 1.1  1998/11/16 16:51:01  mkl
// additions necessary to load BinarySourceFormat and chain binary files
//
//

// system include files

// user include files
#include "DataDelivery/SourceFormat.h"

// forward declarations

class BinarySourceFormat : public SourceFormat
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      BinarySourceFormat();
      virtual ~BinarySourceFormat();

      // ---------- member functions ---------------------------
      virtual BinderBase* createBinder( const string& iName,
					const Stream::Set& iBindStreams );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      BinarySourceFormat( const BinarySourceFormat& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const BinarySourceFormat& operator=( 
	 const BinarySourceFormat& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
};

// inline function definitions

#endif /* BINARYDELIVERY_BINARYSOURCEFORMAT_H */
