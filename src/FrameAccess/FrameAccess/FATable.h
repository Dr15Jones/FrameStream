#if !defined(FRAMEACCESS_FATABLE_H)
#define FRAMEACCESS_FATABLE_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FATable
// 
/**\class FATable FATable.h FrameAccess/FATable.h

 Description: Container of multiple repeating data objects

 Usage:
     A FATable<T> is a container of multiple repeating CLEO data
     objects of type T.  It is used to return data from an extract call.  
     Only extract needs to know how to use a FATable with respect to Proxies.

     To access the data pointer contained in a FATable the user gets
     either a FATableItr<T> or FAItem<T> from the FATable by using one of
     the following access functions:
     - begin() ; returns FATableItr<T> that points to the first
       data object in the Table;
     - end() ; returns FATableItr<T> that points to the `past-end'
       data object in the Table;
     - find( const T::Identifier& ) ; returns a FAItem<T>
       that points to the data element with the supplied
       identifier.  If no element has the supplied Identifier
       then the returned FAItem<T> is not valid (See FAItem.h).

     Note: ALL multiply occurs objects must have a class typedef 
     T::Identifier.

     To access the data pointed to by a FATableItr or FAItem the user
     de-references it (See FATableItr.h or FAItem.h for more details).

     \code
     FATable<DBTrack> trackTable ;
     extract( frame.record(Stream::kEvent) , trackTable ) ;
     FATable<DBTrack>::const_iterator finished = trackTable.end();
     for ( FATable<DBTrack>::const_iterator track = trackTable.begin();
           track != finished ;
	   ++track ) {
	report( INFO ) << "Track " << (*track).identifier()
	               << " has charge " ,, (*track).charge() ;
     }
     \endcode

     For those unfamilar with de-referencing, this simply means
     adding a `*' before the identifier to indicate that you require
     the contents of the object.

     If the data requested does not exist then an error is generated
     when any of the three access functions are calls and the
     program exits.  If the user wishes to avoid this behaviour
     then they need to check the state of the Table, by using the
     `valid' function, before accessing the it.

     \code
     ...
     #include "DAException/DANoDataException.h"
     ...
     FATable<DBTrack> trackTable ;
     try {
       extract( frame.record(Stream::kEvent) , trackTable ) ;
     } catch( NO_TABLE_EXCEPTION(DBTrack)& iException ) {
       //print a nice diagnostic message
       report(WARNING, kFacilityString ) << iException.what() << std::endl;
     }
     
     //want to know if the extract call worked
     if ( trackTable.valid() ) {
        //use trackTable access functions here
     }
     \endcode

     The user need only check the validity of the data if they caught the
     exception and then later want to make sure the extract call succeeded.

     A FATable<T> is similar to a FAItem, in that it "points" to a
     single object.  The set of elements of the object can not be
     changed using the FATable access.  This means there is no need
     for any "edit" functions, such as `insert' and `erase'.
*/
//
//
// Author:      Simon Patton
// Created:     Mon Mar 17 14:42:17 EST 1997
// $Id: FATable.h,v 1.12 2001/09/07 17:47:20 cleo3 Exp $
//
// Revision history
//
// $Log: FATable.h,v $
// Revision 1.12  2001/09/07 17:47:20  cleo3
// added typename
//
// Revision 1.11  2000/12/27 19:05:12  cdj
// removed unnecessary includes
//
// Revision 1.10  1999/12/10 14:20:58  cdj
// added exception macro
//
// Revision 1.9  1999/11/07 02:19:05  cdj
// fixed outdated documentation
//
// Revision 1.8  1999/10/31 15:39:24  cdj
// doxygenated the comments
//
// Revision 1.7  1999/04/13 13:53:26  bkh
// Make FATable<>::find() a const_iterator
//
// Revision 1.6  1998/09/28 18:34:11  cdj
// added getContents() to allow access to FAPtrTable
//
// Revision 1.5  1998/05/07 21:27:40  mkl
// elevate FATable/Itr to stl container/iterator status
//
// Revision 1.4  1998/05/07 19:45:33  mkl
// check for null labels
//
// Revision 1.3  1998/04/09 23:19:35  cleo3
// port to egcs
//
// Revision 1.2  1998/02/06 20:39:03  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.1  1997/12/05 03:04:02  mkl
// moved sources from DataHandler
//
// Revision 1.15  1997/09/18 21:10:26  cdj
// changed Boolean to DABoolean
//
// Revision 1.14  1997/09/10 14:14:47  sjp
// Changed FAItr to be FATableItr
//
// Revision 1.13  1997/08/27 03:16:09  sjp
// Updated to new name for bug flag
//
// Revision 1.12  1997/08/22 15:38:20  sjp
// Updated old bug flag
//
// Revision 1.11  1997/08/06 15:27:36  sjp
// Updated documentation to deal with Proxies
//
// Revision 1.10  1997/08/06 14:57:43  sjp
// Added new typedef used by Extractor
//
// Revision 1.9  1997/07/11 16:44:48  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.8  1997/07/09 17:59:40  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.7  1997/06/03 17:26:40  sjp
// fixed copy constructor error
//
// Revision 1.6  1997/05/09 18:16:49  sjp
// Added operator[] function
//
// Revision 1.5  1997/04/20 18:37:32  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.4  1997/04/19 20:43:23  sjp
// activated begin and end functions
//
// Revision 1.3  1997/04/10 01:06:38  sjp
// Added value_type typedef for new DataField system
//
// Revision 1.2  1997/03/29 16:28:30  sjp
// Added size function
//
// Revision 1.1  1997/03/19 22:18:16  sjp
// New header file for class
//

#define NO_TABLE_EXCEPTION(_type_) DANoDataException<FATable<_type_>::contents>

// system include files

// user include files
#include "FrameAccess/FATableItr.h"
#include "FrameAccess/FAItem.h"


// forward declarations
#if ! ( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#  endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

template < class T >
class FATable
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef T value_type ;
      typedef const value_type& const_reference;
      typedef FAPtrTable< T > contents ;
      typedef FATableItr< T > const_iterator ;

      // Constructors and destructor
      FATable() ;
      FATable( const FATable<T>& aOther ) ;
      FATable( const FAPtrTable< T >* pTable ) ;
      virtual ~FATable() ;

      // assignment operator(s)
      const FATable& operator=( const FATable< T >& aTable ) ;

      // member functions
      void setContents( const FAPtrTable< T >* pTable ) ;

      // const member functions
      DABoolean valid() const ;
      Count size() const ;
      DABoolean empty() const;
      ///returns FATableItr<T> that points to the first data object in the Table
      const_iterator begin() const ;
      ///returns FATableItr<T> that points to the `past-end' data object in the Table
      const_iterator end() const ;
      const_reference front() const;
      const_reference back() const;
      /** returns a FAItem<T> that points to the data element with the 
          supplied identifier.  If no element has the supplied Identifier
          then the returned FAItem<T> is not valid (See FAItem.h). 
	  */
#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
// Note: g++ has a deficiecy in that is can only parse some arguments
//   that contain class::typedef constructs. This is a works around.
      const_iterator find( const typename T::Identifier aIdentifier ) const {
	 (*(FATable< T >*)this).m_fixGnuIdentifier = aIdentifier ;
	 return ( find_fixGnu() ) ;
      }
      const_reference 
      operator[]( const typename T::Identifier& aIdentifier ) const {
	 (*(FATable< T >*)this).m_fixGnuIdentifier = aIdentifier ;
	 return ( *find_fixGnu() ) ;
      }
#else
      const_iterator find( const typename T::Identifier& aIdentifier ) const ;
      const_reference 
      operator[]( const typename T::Identifier& aIdentifier ) const ;
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */

      const FAPtrTable< T >* getContents() const { return m_ptrTable; }
      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
// Note: g++ has a deficiecy in that is can only parse some arguments
//   that contain class::typedef constructs. This is a works around.
      const_iterator find_fixGnu() const ;
      typename T::Identifier m_fixGnuIdentifier ;
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */
      // Constructors and destructor

      // private member functions

      // private const member functions

      // data members
      const FAPtrTable< T >* m_ptrTable ;

      // static data members

};

// inline function definitions

template < class T >
inline DABoolean
FATable< T >::valid() const
{
   return ( 0 != m_ptrTable ) ;
}

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "FrameAccess/Template/FATable.cc"
#endif

#endif /* FRAMEACCESS_FATABLE_H */
