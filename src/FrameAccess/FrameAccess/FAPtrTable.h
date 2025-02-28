#if !defined(FRAMEACCESS_FAPTRTABLE_H)
#define FRAMEACCESS_FAPTRTABLE_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FAPtrTable
// 
/** \class FAPtrTable FAPtrTable.h FrameAccess/FAPtrTable.h 

 Description: Table to hold a set of pointer as a single unit

 Usage:
     A FATable<T> is a container of multiple repeating CLEO data
     objects of type T.  It is used to provide an efficient
     implementation of  the FATable<T> class.  Only Proxy
     writers need to know how to use, i.e. fill, a FAPtrTables.

     After creating a FAPtrTable<T> for a Proxy, pointers to
     each objects in the Proxy should be placed in it with the
     `insert' function.  Once all the pointers have been
     inserted into the FAPtrTable<T> it can be used in the
     constructor of a FATable<T>

     \code
     LargeCount finished = numberMUHits ;
     for ( LargeCount hitIndex = 0 ;
          hitIndex != finished ;
          ++hitIndex ) {
       DBRawMUHit* tmp = new DBRawMUHit( hitIndex ,
                                         hardwareAddress[ hitIndex ] ,
                                         adc1[ hitIndex ] ,
                                         adc1[ hitIndex ] ) ;
       if ( 0 == tmp ) {
          exit( 1 ) ;
       }
       dbRawMUHitTable.insert( tmp ) ;
     }
     \endcode

     When the pointers are inserted into the FAPtrTable<T> they,
     along with the objects they point to, become the property of
     the FAPtrTable<T>.  The `eraseAll' function removes the
     pointers from the FAPtrTable<T> and deletes the objects they
     point to.

     \code
     dbRawMUHitsTable.eraseAll() ;
     \endcode

     If you do now wish the FAPtrTable<T> to delete its contents, then
     call eraseWithoutDeleteAll() before the FAPtrTable<T> is deleted.
*/
// Author:      Simon Patton
// Created:     Tue Mar 18 17:05:43 EST 1997
// $Id: FAPtrTable.h,v 1.14 2003/01/29 21:41:22 cleo3 Exp $
//
// Revision history
//
// $Log: FAPtrTable.h,v $
// Revision 1.14  2003/01/29 21:41:22  cleo3
// minor changes to allow compilation by g++
//
// Revision 1.13  2001/01/03 22:50:16  cdj
// bug fix: fix seg fault when calling begin() for an empty FAPtrTable
//
// Revision 1.12  2001/01/02 22:20:30  cdj
// insert now returns an iterator
//
// Revision 1.11  2000/12/27 19:05:12  cdj
// removed unnecessary includes
//
// Revision 1.10  2000/12/26 21:10:17  cdj
// FAPtrTable now uses a vector when then Identifier is an integral type
//
// Revision 1.9  2000/06/17 20:12:52  cdj
// returns end() iterator (which is an invalid FAItem) when find fails
//
// Revision 1.8  2000/04/21 17:50:12  cdj
// FAPtrTable now holds a map<Identifer,void*> to reduce number of map instantiations
//
// Revision 1.7  1999/12/03 15:01:25  bkh
// Make new class which handles const ptr tables which do not delete member ptrs
// Modify base ptr table class to have virtual eraseAll for protection
//
// Revision 1.6  1999/11/07 02:18:36  cdj
// doxygenated the comments
//
// Revision 1.5  1999/04/13 13:53:24  bkh
// Make FATable<>::find() a const_iterator
//
// Revision 1.4  1998/07/07 19:26:01  mkl
// FAPtrTable::dtor deletes its internal table of pointers; added 'eraseWithoutDeleteAll' which deletes table entries, but pointed-to memory
//
// Revision 1.3  1998/04/09 23:19:34  cleo3
// port to egcs
//
// Revision 1.2  1998/02/06 20:39:03  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.1  1997/12/05 03:04:00  mkl
// moved sources from DataHandler
//
// Revision 1.19  1997/09/10 14:22:30  sjp
// Finished name changes for FAItr to FATableItr
//
// Revision 1.18  1997/09/10 14:14:46  sjp
// Changed FAItr to be FATableItr
//
// Revision 1.17  1997/08/27 03:16:08  sjp
// Updated to new name for bug flag
//
// Revision 1.16  1997/08/22 15:38:51  sjp
// Reordered to standard bug flag ordering
//
// Revision 1.15  1997/08/14 11:42:49  sjp
// Mods to run under CW Pro 1
//
// Revision 1.14  1997/08/06 15:27:34  sjp
// Updated documentation to deal with Proxies
//
// Revision 1.13  1997/08/06 14:57:41  sjp
// Added new typedef used by Extractor
//
// Revision 1.12  1997/07/11 16:44:46  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.11  1997/07/09 17:59:38  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.10  1997/07/01 18:46:14  sjp
// Added required include file
//
// Revision 1.9  1997/06/03 17:12:05  sjp
// Added forward declaration of map
//
// Revision 1.8  1997/06/03 17:09:55  sjp
// Modified to contain map rather than inherit from
//
// Revision 1.7  1997/04/20 18:37:30  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.6  1997/04/19 20:43:55  sjp
// activated begin and end functions
//
// Revision 1.5  1997/04/14 19:50:34  sjp
// Move code out to .cc file
//
// Revision 1.4  1997/04/01 16:09:32  sjp
// used new names for functions
//
// Revision 1.3  1997/03/29 16:27:31  sjp
// Renamed functions
//
// Revision 1.2  1997/03/19 22:51:22  sjp
// Added missing include file
//
// Revision 1.1  1997/03/19 22:18:14  sjp
// New header file for class
//

// system include files

// user include files
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATableItr.h"

// forward declarations

template < class T >
class FAPtrTable
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef T value_type ;
      typedef FATableItr< T > const_iterator ;

      // Constructors and destructor
      FAPtrTable() ;
      virtual ~FAPtrTable() ;

      // member functions
      ///takes ownership of aEntry's memory unless you use eraseWithoutDeleteAll 
      FATableItr<T> insert( T* aEntry ) ;
      ///empties the container and calls delete for each entry
      virtual void eraseAll() ;
      ///empties the container without calling delete for each entry
      void eraseWithoutDeleteAll() ;
      
      ///allows you to reserve space in the FAPtrTable
      void reserve( unsigned long iSize ) { m_map.reserve( iSize ); }

      // const member functions
      //since a FATableItr dereferences the m_map iterator, need to 
      // return end() if container is empty 
      FATableItr< T > begin() const {    
	 return ( empty() ? end() : FATableItr< T >( m_map.begin() ) ) ; }

      ///end iterator is also an invalid FAItem
      FATableItr< T > end() const {
	 return ( FATableItr< T >( m_map.end(), 0 ) ) ; // set with null ptr
      }

      ///find returns end() if no item found
      const_iterator find( const typename T::Identifier& aIdentifier ) const {
	 typename _fatableitr_map_::const_iterator foundItr = m_map.find(aIdentifier);
	 if ( foundItr == m_map.end() ) {
	    return end();
	 }
	 return foundItr; }

      LargeCount size() const { return m_map.size(); }
      DABoolean  empty() const { return ( 0 == size() ); }

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:

      // Constructors and destructor
      FAPtrTable( const FAPtrTable< T >& ) ; // stop default

      // assignment operator(s)
      const FAPtrTable& operator=( const FAPtrTable< T >& ) ; // stop default

      // private member functions

      // private const member functions

      // data members
      _fatableitr_map_& m_map ;

      // static data members

};

// inline function definitions

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "FrameAccess/Template/FAPtrTable.cc"
#endif

#endif /* FRAMEACCESS_FAPTRTABLE_H */
