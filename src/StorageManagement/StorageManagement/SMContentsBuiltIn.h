#if !defined(STORAGEMANAGEMENT_SMCONTENTSBUILTIN_H)
#define STORAGEMANAGEMENT_SMCONTENTSBUILTIN_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMContentsBuiltIn
// 
// Description: A SMContentsBase specifically designed to handle types
//               that SMSinkStreams already know about, e.g. float.
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Thu Sep 30 21:12:06 EDT 1999
// $Id: SMContentsBuiltIn.h,v 1.3 2000/05/16 15:22:37 mkl Exp $
//
// Revision history
//
// $Log: SMContentsBuiltIn.h,v $
// Revision 1.3  2000/05/16 15:22:37  mkl
// new StorageManagement builtin container vs other flag
//
// Revision 1.2  2000/04/27 21:07:27  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.1  1999/10/11 22:00:40  cdj
// added Lattice storage code
//

// system include files

// user include files
#include "StorageManagement/SMContentsBase.h"

// forward declarations

template < class Iterator >
class SMContentsBuiltIn : public SMContentsBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMContentsBuiltIn( const Iterator& itBegin,
			 const Iterator& itEnd ) :
	 SMContentsBase( SMContentsBase::kBuiltin ),
	 m_begin( itBegin ),
	 m_end( itEnd ) {}
      //virtual ~SMContentsBuiltIn();

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
      SMContentsBuiltIn(); // stop default
      //SMContentsBuiltIn( const SMContentsBuiltIn& ); // allow default

      // ---------- assignment operator(s) ---------------------
      const SMContentsBuiltIn& operator=( const SMContentsBuiltIn& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static const TypeTag& getTypeTag();

      // ---------- data members -------------------------------
      Iterator m_begin;
      Iterator m_end;

      // ---------- static data members ------------------------

};

// inline function definitions
template< class Iterator >
inline
SMContentsBuiltIn< Iterator >
sm_contents_builtin( const Iterator& itBegin, const Iterator& itEnd ) {
   return SMContentsBuiltIn< Iterator >( itBegin, itEnd ); 
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "StorageManagement/Template/SMContentsBuiltIn.cc"
#endif

#endif /* STORAGEMANAGEMENT_SMCONTENTSBUILTIN_H */
