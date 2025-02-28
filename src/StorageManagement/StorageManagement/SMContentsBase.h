#if !defined(STORAGEMANAGEMENT_SMCONTENTSBASE_H)
#define STORAGEMANAGEMENT_SMCONTENTSBASE_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMContentsBase
// 
// Description: Base class for classes used to inform a SinkStream
//               what types of objects another object contains
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed May 19 13:44:52 EDT 1999
// $Id: SMContentsBase.h,v 1.3 2000/05/16 15:22:36 mkl Exp $
//
// Revision history
//
// $Log: SMContentsBase.h,v $
// Revision 1.3  2000/05/16 15:22:36  mkl
// new StorageManagement builtin container vs other flag
//
// Revision 1.2  2000/04/27 21:07:26  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files
#include "DataHandler/DataKeyTags.h"

// forward declarations
class SMSinkStream;

class SMContentsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef unsigned long size_type;
      enum Strategy { kDefault, kBuiltin };

      // ---------- Constructors and destructor ----------------
      SMContentsBase() : m_strategy(kDefault) {}
      virtual ~SMContentsBase() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual size_type size() const = 0;
      virtual void store( SMSinkStream& iSink ) const = 0;
      virtual const TypeTag& typeTag() const = 0;

      Strategy strategy() const { return m_strategy; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      SMContentsBase( Strategy iStrategy ) : m_strategy( iStrategy ) {}

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMContentsBase( const SMContentsBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMContentsBase& operator=( const SMContentsBase& ); // stop default

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
//# include "StorageManagement/Template/SMContentsBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMCONTENTSBASE_H */
