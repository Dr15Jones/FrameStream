#if !defined(STORAGEMANAGEMENT_SMMAKECONTENTSBASE_H)
#define STORAGEMANAGEMENT_SMMAKECONTENTSBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMMakeContentsBase
// 
// Description: Base class for classes used to retrieve from a SourceStream
//               a series of objects
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Thu May 20 17:02:13 EDT 1999
// $Id: SMMakeContentsBase.h,v 1.4 2002/12/09 16:14:45 cleo3 Exp $
//
// Revision history
//
// $Log: SMMakeContentsBase.h,v $
// Revision 1.4  2002/12/09 16:14:45  cleo3
// allow compiler to make copy constructor
//
// Revision 1.3  2000/05/16 15:22:38  mkl
// new StorageManagement builtin container vs other flag
//
// Revision 1.2  2000/04/27 21:07:27  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.1.1.1  1999/09/13 21:21:41  cdj
// imported package
//

// system include files

// user include files
#include "DataHandler/DataKeyTags.h"

// forward declarations
class SMSourceStream;

class SMMakeContentsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef unsigned long size_type;
      enum Strategy { kDefault, kBuiltin };

      // ---------- Constructors and destructor ----------------
      SMMakeContentsBase() : m_strategy( kDefault ) {}
      virtual ~SMMakeContentsBase() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void deliver( SMSourceStream& iSource,
			    size_type iSizeOfContainer ) const = 0;
      virtual const TypeTag& typeTag() const = 0;
 
      Strategy strategy() const { return m_strategy; }
      
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      SMMakeContentsBase( Strategy iStrategy ) : m_strategy( iStrategy ) {}

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMMakeContentsBase( const SMMakeContentsBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMMakeContentsBase& operator=( const SMMakeContentsBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Strategy m_strategy;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMMakeContentsBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMMAKECONTENTSBASE_H */
