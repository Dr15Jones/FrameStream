#if !defined(STORAGEMANAGEMENT_SMMAKECONTENTS_H)
#define STORAGEMANAGEMENT_SMMAKECONTENTS_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMMakeContents
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Thu May 20 17:02:17 EDT 1999
// $Id: SMMakeContents.h,v 1.3 2000/04/27 21:07:27 mkl Exp $
//
// Revision history
//
// $Log: SMMakeContents.h,v $
// Revision 1.3  2000/04/27 21:07:27  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.2  2000/04/06 14:58:10  cdj
// allow compiler to write copy constructor and assignment operator
//
// Revision 1.1.1.1  1999/09/13 21:21:41  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMMakeContentsBase.h"

// forward declarations

template <class Iterator>
class SMMakeContents : public SMMakeContentsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMMakeContents( const Iterator& itInserter ) :
	 m_inserter( itInserter ) {}
      //virtual ~SMMakeContents();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void deliver( SMSourceStream& iSource,
			    size_type iSizeOfContainer ) const;
      virtual const TypeTag& typeTag() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMMakeContents( const SMMakeContents& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMMakeContents& operator=( const SMMakeContents& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static const TypeTag& getTypeTag();
      static SMStorageHelperBase& storageHelper();

      // ---------- data members -------------------------------
      Iterator m_inserter;

      // ---------- static data members ------------------------

};

// inline function definitions
template< class Iterator >
inline
SMMakeContents< Iterator >
sm_make_contents( const Iterator& itInserter ) {
   return SMMakeContents<Iterator>( itInserter ); 
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMMakeContents.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMMAKECONTENTS_H */
