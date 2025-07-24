#if !defined(UTILITY_UTIDENTIFIER_H)
#define UTILITY_UTIDENTIFIER_H
// -*- C++ -*-
//
// Package:     Utility
// Module:      UTIdentifier
// 
// Description: A high speed general purpose identifier
//
// Usage:
//    This class maps a unique Identifier into an unsigned integer.
//    By using this class you have the convienience of your Identifier
//    (E.g. string) but the speed of an integer.
//
//    When you instantiate this class, you must also instantiate its two
//    static data members
//    Code Example
//
//      //Instantiating static member data
//      map< string, Count, less< string > >*
//      UTIdentifier< string, Stream>::m_idToIndexMap(0);
//
//      vector< string >*
//      UTIdentifier< string, Stream>::m_idList(0);
//
//      ...
//
//      UTIdentifier< string, Stream> event("event");
//      UTIdentifier< string, Stream> beginRun( "beginrun");
//
//      if( event != beginRun ){
//        cout <<event.value()<<"!="<<beginRun.value()<<std::endl;
//      } else {
//        cout <<"Error"<<event.value()<<"["<<event.index()<<"]"
//                      <<"=="
//                      <<beginRun.value()<<"["<<beginRun.index()<<"]"<<std::endl;
//      }
//
// Author:      Chris D. Jones
// Created:     Sun Apr 27 09:32:12 EDT 1997
// $Id: UTIdentifier.h,v 1.15 1998/04/01 15:56:37 mkl Exp $
//
// Revision history
//
// $Log: UTIdentifier.h,v $
// Revision 1.15  1998/04/01 15:56:37  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.14  1998/02/06 20:36:19  mkl
// left-over edits for switch to STLUtility
//
// Revision 1.13  1997/09/18 21:35:46  cdj
// changed Boolean to DABoolean
//
// Revision 1.12  1997/09/03 20:05:32  sjp
// Uses CPP macros for STL containers
//
// Revision 1.11  1997/09/01 23:02:09  sjp
// Fixed error in CPP macro naming
//
// Revision 1.10  1997/09/01 16:23:10  sjp
// Moved TBIdentifier to UTIdentifier
//
// Revision 1.9  1997/08/30 18:57:22  cdj
// Bug fixes: 1) #define vector looks for NO_ALLOCATOR_IN_STL_DECLARATION_BUG
//            2) methods taking UTIdentifier's use TBIdentifer<ID, T>
//
// Revision 1.8  1997/08/14 11:42:32  sjp
// Mods to run under CW Pro 1
//
// Revision 1.7  1997/07/17 18:42:31  sjp
// Cleaned up problem with static data in template class
//
// Revision 1.6  1997/07/11 16:44:36  sjp
// Added INCLUDE_TEMPLATE_DEFINITIONS flag
//
// Revision 1.5  1997/07/08 14:34:49  sjp
// Put in correct forward declaration for STL
//
// Revision 1.4  1997/07/07 16:15:49  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/05/07 19:54:47  sjp
// Added "read from stream" function
//
// Revision 1.2  1997/05/01 13:51:09  sjp
// Fixed DECCXX bug flags
//
// Revision 1.1  1997/04/30 13:43:22  sjp
// New file to speed up matching identifiers
//


// system include files

// user include files

// forward declarations
#include <iosfwd>
#include <vector>
#include <map>

#if !defined(_utidentifier_counts_)
#define _utidentifier_counts_ std::map< ID , Count >
#define _utidentifier_ids_ std::vector< ID >
#endif /* _uTIdentifier_counts_ */

template< class ID, class T >
class UTIdentifier
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      UTIdentifier( void );

      UTIdentifier( const ID& iID );
      UTIdentifier( const UTIdentifier<ID, T> & iIdentifier);

      virtual ~UTIdentifier();

      // assignment operator(s)
      const UTIdentifier& operator=( const UTIdentifier& iIdentifier);

      // member functions

      // const member functions
      DABoolean operator==( const UTIdentifier<ID, T>& iRHS ) const;
      DABoolean operator!=( const UTIdentifier<ID, T>& iRHS ) const;

      Count index( void ) const;
      const ID& value( void ) const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor

      // private member functions

      // private const member functions
      
      // private static member functions 
      static _utidentifier_counts_& idToIndexMap( void ) ;
      static _utidentifier_ids_& idList( void ) ;
      static Count findIndex( const ID& iID );

      // data members
      Count m_index;

      // static data members

};

// inline function definitions

// utility functions
template< class ID, class T>
std::ostream& 
operator<<(std::ostream& iOStream, const UTIdentifier< ID, T>& iIdentifier );

template< class ID, class T>
std::istream&
operator>>( std::istream& iIStream , UTIdentifier< ID, T>& iIdentifier ) ;

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "Utility/Template/UTIdentifier.cc"
#endif

#endif /* UTILITY_UTIDENTIFIER_H */
