#if !defined(TOOLBOX_TBREFERENCECOUNT_H)
#define TOOLBOX_TBREFERENCECOUNT_H
// -*- C++ -*-
//
// Package:     ToolBox
// Module:      TBReferenceCount
// 
// Description: Base class for classes that need reference counting
//
// Usage:
//   TBReferenceCount()  - default constructor
//   ~TBReferenceCount() - destructor
//   addLink()  - record that another object points to this object
//   dropLink() - record that an object no longer points to this object
//
// Author:      Simon Patton
// Created:     Fri May 17 08:01:51 EDT 1996
// $Id: TBReferenceCount.h,v 1.5 1997/07/07 16:15:57 sjp Exp $
//
// Revision history
//
// $Log: TBReferenceCount.h,v $
// Revision 1.5  1997/07/07 16:15:57  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.4  1996/12/20 20:44:05  sjp
// Made initial count 1, so never call delete just dropLink()
//
// Revision 1.3  1996/11/04 16:14:26  sjp
// Allowed for 'filename-only' include, for use with MWERKS.
// Changed add and drop link functions to be `const'.
// Changed virtual destuctor to no longer be inlined.
//
// Revision 1.2  1996/07/16 19:04:57  sjp
// Restructed Libraries
// Put relative pathnames into all includes
//
// Revision 1.1.1.1  1996/06/04 14:46:25  sjp
// New library files containing DS Objects
//


// system include files

// user include files


// forward declarations

class TBReferenceCount
{
   public:
      // Constructors and destructor
      TBReferenceCount();
      virtual ~TBReferenceCount();

      // const member functions
      void addLink() const ;
      void dropLink() const ;

   private:
      // Constructors and destructor
      TBReferenceCount( const TBReferenceCount& ) ; // stop default

      // assignment operator(s)
      const TBReferenceCount& operator=( const TBReferenceCount& ) ; // stop default

      // data members
      SmallCount _linkCount ;

};

// inline function definitions

//
// constructors and destructor
//

inline TBReferenceCount::TBReferenceCount() :
   _linkCount( 1 )
{
}

//
// member functions
//

inline void TBReferenceCount::addLink() const
{
// The following is a work around until 'mutable' is implemented
   ++(*(TBReferenceCount*)this)._linkCount ;
}

inline void TBReferenceCount::dropLink() const
{
// The following is a work around until 'mutable' is implemented
   --(*(TBReferenceCount*)this)._linkCount ;
   if ( 0 == _linkCount ) {
// It is necessary to throw away the 'const' so that the object
//   can be deleted
      delete (TBReferenceCount*)this ;
   }
}

#endif /* TOOLBOX_TBREFERENCECOUNT_H */
