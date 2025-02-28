#if !defined(STORAGEMANAGEMENT_SMFILLCONTENTS_H)
#define STORAGEMANAGEMENT_SMFILLCONTENTS_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMFillContents
// 
// Description: Fills a container using an operator>> for the contents
//               of the container
//
// Usage:
//    This class is used when writing a 'deliver' method of a StorageHelper
//     where the container you are filling actually holds instances of the
//     class instead of holding pointers to instances of the class.
//
//    Requirements of Iterator::value_type
//     1) default constructor
//     2) copy constructor
//     3) operator>>( SMSourceStream& , Iterator::value_type& ) 
//
// Author:      Chris D Jones
// Created:     Tue Jun  8 09:00:30 EDT 1999
// $Id: SMFillContents.h,v 1.4 2000/05/16 15:22:37 mkl Exp $
//
// Revision history
//
// $Log: SMFillContents.h,v $
// Revision 1.4  2000/05/16 15:22:37  mkl
// new StorageManagement builtin container vs other flag
//
// Revision 1.3  2000/04/27 21:07:27  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.2  2000/04/06 14:58:10  cdj
// allow compiler to write copy constructor and assignment operator
//
// Revision 1.1.1.1  1999/09/13 21:21:42  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMMakeContentsBase.h"

// forward declarations

template <class Iterator>
class SMFillContents : public SMMakeContentsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMFillContents( const Iterator& itInserter ) :
	 SMMakeContentsBase( SMMakeContentsBase::kBuiltin ),
	 m_inserter( itInserter ) {}
      //virtual ~SMFillContents();

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
      //SMFillContents( const SMFillContents& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMFillContents& operator=( const SMFillContents& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static const TypeTag& getTypeTag();

      // ---------- data members -------------------------------
      Iterator m_inserter;

      // ---------- static data members ------------------------

};

// inline function definitions
template< class Iterator >
inline
SMFillContents< Iterator >
sm_fill_contents( const Iterator& itInserter ) {
   return SMFillContents<Iterator>( itInserter ); 
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
#include "StorageManagement/Template/SMFillContents.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMFILLCONTENTS_H */
