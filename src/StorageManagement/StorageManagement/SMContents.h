#if !defined(STORAGEMANAGEMENT_SMCONTENTS_H)
#define STORAGEMANAGEMENT_SMCONTENTS_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMContents
// 
// Description: informs SinkStream about a container that holds elements
//              of type T
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed May 19 14:02:27 EDT 1999
// $Id: SMContents.h,v 1.2 2000/04/27 21:07:26 mkl Exp $
//
// Revision history
//
// $Log: SMContents.h,v $
// Revision 1.2  2000/04/27 21:07:26  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.1.1.1  1999/09/13 21:21:41  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMContentsBase.h"

// forward declarations
class SMStorageHelperBase;

template < class Iterator >
class SMContents : public SMContentsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMContents( const Iterator& itBegin,
		  const Iterator& itEnd ) :
	 m_begin( itBegin ),
	 m_end( itEnd ) {}

      //virtual ~SMContents();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual size_type size() const;
      virtual void store( SMSinkStream& iSink ) const;
      const TypeTag& typeTag() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMContents(); // stop default
      //SMContents( const SMContents& ); // allow default

      // ---------- assignment operator(s) ---------------------
      const SMContents& operator=( const SMContents& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static const TypeTag& getTypeTag();
      static SMStorageHelperBase& storageHelper();

      // ---------- data members -------------------------------
      Iterator m_begin;
      Iterator m_end;

      // ---------- static data members ------------------------

};

// inline function definitions

template< class Iterator >
inline
SMContents< Iterator >
sm_contents( const Iterator& itBegin, const Iterator& itEnd ) {
   return SMContents<Iterator>( itBegin, itEnd ); 
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMContents.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMCONTENTS_H */
