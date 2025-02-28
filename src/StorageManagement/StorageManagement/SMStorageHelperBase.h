#if !defined(STORAGEMANAGEMENT_SMSTORAGEHELPERBASE_H)
#define STORAGEMANAGEMENT_SMSTORAGEHELPERBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageHelperBase
// 
/**\class SMStorageHelperBase SMStorageHelperBase.h StorageManagement/SMStorageHelperBase.h

 Description: Base class used to communicate with storage system how to 
               store and retrieve a particular class type

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri May 14 10:43:09 EDT 1999
// $Id: SMStorageHelperBase.h,v 1.3 2000/04/24 20:21:10 mkl Exp $
//
// Revision history
//
// $Log: SMStorageHelperBase.h,v $
// Revision 1.3  2000/04/24 20:21:10  mkl
// SMStorageHelperBase::versionToStore() now virtual.
//
// Revision 1.2  1999/10/18 18:25:24  cdj
// no longer creates proxies
//
// Revision 1.1.1.1  1999/09/13 21:21:40  cdj
// imported package
//

// system include files

// user include files
#include "DataHandler/DataKeyTags.h"

// forward declarations
class SMSinkStream;
class SMSourceStream;

class SMStorageHelperBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum { kNoVersionsDefined = 0,
	     kFirstVersionNumber = 1 };

      // ---------- Constructors and destructor ----------------
      SMStorageHelperBase( const TypeTag& iTypeTag ) ;

      virtual ~SMStorageHelperBase();

      // ---------- member functions ---------------------------      

      // ---------- const member functions ---------------------
      const TypeTag& typeTag() const { return m_typeTag; }

      virtual DABoolean checkConsistance(SMSinkStream&iSink, 
					 SMSourceStream& iSource ) = 0;

      virtual void useDefault( SMSinkStream& iSink ) = 0;
      virtual unsigned int versionToStore() const = 0;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMStorageHelperBase() ; //stop default
      SMStorageHelperBase( const SMStorageHelperBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMStorageHelperBase& operator=( const SMStorageHelperBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      TypeTag m_typeTag;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMStorageHelperBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMSTORAGEHELPERBASE_H */
