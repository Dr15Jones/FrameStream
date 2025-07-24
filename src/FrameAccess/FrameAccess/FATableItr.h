#if !defined(FRAMEACCESS_FATABLEITR_H)
#define FRAMEACCESS_FATABLEITR_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FATable
// 
/**\class FATableItr FATableItr.h FrameAccess/FATableItr.h

 Description: A forward-iterator to access the contents of a FATable

 Usage:
     A FATableItr<T> is a smart pointer to multiple repeating CLEO data
     objects that are stored in a FATable<T> ( see FATable.h).  It
     is the implementation of the FATable::const_iterator.   To
     access the data pointed to by a FATableItr the user de-references
     it.

     \code
     FATable<DBTrack> trackTable ;
     extract( frame.record(Stream::kEvent) , trackTable ) ;
     FATable<DBTrack>::const_iterator finished = trackTable.end();
     for ( FATable<DBTrack>::const_iterator track = trackTable.begin() ;
           track != finished ;
           ++track ) {
        report( INFO ) << "Track " << (*track).identifier()
                       << " has charge " ,, (*track).charge() ;
     }
     \endcode

     For those unfamilar with de-referencing, this simply means
     adding a `*' before the identifier to indicate that you require
     the contents of the object.

     If the user needs to hold onto an object pointer to by the
     iterator, they should store the objects as FAItem<T>, not as a
     FATableItr<T> (nor as a FATable<T>::const_Iterator).

     \code
     FATable<DBTrack> trackTable ;
     extract( frame.record(Stream::kEvent) , trackTable ) ;
     FAItem<DBTrack> hardestTrack ;
     GeV momentum( 0.0 ) ;
     GeV currentMomentum ;
     FATable<DBTrack>::const_iterator finished = trackTable.end();
     for ( FATable<DBTrack>::const_iterator track = trackTable.begin() ;
           track != finished ;
           ++track ) {
        if ( momentum < ( currentMomentum = (*track).momentum.mag() ) ) {
           momentum = currentMomentum ;
           hardestTrack = track ;
        }
     }
     \endcode
*/
//
// Author:      Simon Patton
// Created:     Mon Mar 17 14:42:40 EST 1997
// $Id: FATableItr.h,v 1.16 2001/09/07 17:47:20 cleo3 Exp $
//
// Revision history
//
// $Log: FATableItr.h,v $
// Revision 1.16  2001/09/07 17:47:20  cleo3
// added typename
//
// Revision 1.15  2000/12/27 19:05:13  cdj
// removed unnecessary includes
//
// Revision 1.14  2000/12/26 21:10:18  cdj
// FAPtrTable now uses a vector when then Identifier is an integral type
//
// Revision 1.13  2000/04/21 17:50:13  cdj
// FAPtrTable now holds a map<Identifer,void*> to reduce number of map instantiations
//
// Revision 1.12  1999/12/10 14:16:14  cdj
// inlined operator++ because it was showing up in profier
//
// Revision 1.11  1999/11/07 02:19:06  cdj
// fixed outdated documentation
//
// Revision 1.10  1999/10/31 15:39:24  cdj
// doxygenated the comments
//
// Revision 1.9  1999/09/22 15:20:52  cdj
// added standard STL typedefs
//
// Revision 1.8  1999/04/13 13:53:28  bkh
// Make FATable<>::find() a const_iterator
//
// Revision 1.7  1998/07/18 19:47:48  mkl
// solaris comp. has trouble parsing typedefs in templates; workaround
//
// Revision 1.6  1998/05/07 21:52:47  mkl
// make g++ happy too...
//
// Revision 1.5  1998/05/07 19:45:33  mkl
// check for null labels
//
// Revision 1.4  1998/04/09 23:19:36  cleo3
// port to egcs
//
// Revision 1.3  1998/02/06 20:39:04  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.2  1998/01/30 18:14:31  mkl
// added --operators
//
// Revision 1.1  1997/12/05 03:04:06  mkl
// moved sources from DataHandler
//
// Revision 1.12  1997/09/18 21:10:27  cdj
// changed Boolean to DABoolean
//
// Revision 1.11  1997/09/10 14:20:38  sjp
// Finished name changes for FAItr to FATableItr
//
// Revision 1.10  1997/09/10 14:14:44  sjp
// Changed FAItr to be FATableItr
//
// Revision 1.9  1997/09/03 20:06:19  sjp
// Uses CPP macros for STL containers
//
// Revision 1.8  1997/08/27 03:16:06  sjp
// Updated to new name for bug flag
//
// Revision 1.7  1997/08/14 11:42:48  sjp
// Mods to run under CW Pro 1
//
// Revision 1.6  1997/07/11 16:44:44  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.5  1997/07/09 17:59:37  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.4  1997/05/09 18:15:40  sjp
// Changed function name setPointer to setContents
//
// Revision 1.3  1997/04/20 18:37:27  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.2  1997/04/19 20:44:35  sjp
// First working version of iterator
//
// Revision 1.1  1997/03/19 22:18:10  sjp
// New header file for class
//

// system include files

// user include files
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FAVoidPtrContainer.h"


// forward declarations

#if !defined(_fatableitr_map_)
#  define _fatableitr_map_ FAVoidPtrContainer< typename T::Identifier >
#endif /* _fatableitr_map_ */

typedef long FATableItr_Distance;

template < class T >
class FATableItr : public FAItem< T >
{
      // private constants, enums and typedefs
      typedef FATableItr< T > self;

      // friend classes and functions

   public:
      // constants, enums and typedefs
      //standard STL iterator typedefs 
      typedef FATableItr_Distance difference_type;
      typedef T* pointer;
      typedef T& reference;
      typedef std::random_access_iterator_tag iterator_category;

      // Constructors and destructor
      FATableItr() ;
      FATableItr( const self& aPtr ) ;
#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
      typedef typename _fatableitr_map_::const_iterator _fatableitr_map_const_iterator_;
      FATableItr( const _fatableitr_map_const_iterator_ & aElement) :
      //FATableItr( const _fatableitr_map_::const_iterator& aElement) :
	 m_element( aElement ) {
	    setContents( static_cast<T*>((*m_element).second) ) ;
      }
      FATableItr( const _fatableitr_map_const_iterator_ & aElement, int  ) :
	 m_element( aElement ) {} // this one used to use default FAItem c'tor
#else
      FATableItr( const typename _fatableitr_map_::const_iterator& aElement) ;
      FATableItr( const typename _fatableitr_map_::const_iterator& aElement, int ) ;
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */
      //virtual ~FATableItr() ;

      // assignment operator(s)
      const FATableItr& operator=( const self& aPtr ) ;

      // member functions
      //inline this function since it is showing up in profiler
      self& operator++() { ++m_element; 
      setContents( static_cast<T*>((*m_element).second ) );
      return (*this); }
      self  operator++(int) ;

      self& operator--() ;
      self  operator--(int) ;

      self operator+( FATableItr_Distance n );
      self& operator+=( FATableItr_Distance n );
      self operator-( FATableItr_Distance n );
      self& operator-=( FATableItr_Distance n );
      FATableItr_Distance operator-( const self& aPtr );

      // const member functions
      DABoolean operator==( const self& aPtr ) const ;
      DABoolean operator!=( const self& aPtr ) const ;
#if 0 /* not currently implemented */
#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
// Note: g++ has a deficiecy in that is can only parse some arguments
//   that contain class::typedef constructs. This is a works around.
      const_reference operator[]( FATableItr_Distance n ) const {
      }
#else
      const_reference operator[]( FATableItr_Distance n ) const;
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */
#endif
      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor

      // private member functions

      // private const member functions

      // data members
      typename _fatableitr_map_::const_iterator m_element ;
      // static data members

};

// inline function definitions

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "FrameAccess/Template/FATableItr.cc"
#endif

#endif /* FRAMEACCESS_FATABLEITR_H */
