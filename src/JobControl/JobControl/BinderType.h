#if !defined(JOBCONTROL_BINDERTYPE_H)
#define JOBCONTROL_BINDERTYPE_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      BinderType
// 
// Description: Class to encapsulate the concept of a Stream type.
//              
//
// Usage:
//    Used by Stream.
//
//    When declaring a new BinderType instance, we strongly suggest that
//     you declare it as a globally accessable const (either as a global
//     variable or as a static const member data to a class) and then only
//     refer to that Stream using the const value.
//
//     Code example
//     // Somewhere in your .cc file
//     //   Make a "myBinderType"
//     const BinderType kMyBinderType( "myBinderType" );
//     
//     ...
// 
//     //Somewhere in your code
//     if( kMyBinderType == aBinder ) {...}
//
//    Efficiency demands you to make your Stream a globally accessible const:
//      every time you instantiate a new BinderType the system
//      does a number of string comparisons.  This can be 
//      computationally expensive
//
// Author:      Martin Lohner
// Created:     Mon Mar 30 11:47:04 EDT 1998
// $Id: BinderType.h,v 1.3 2002/12/06 16:25:28 cleo3 Exp $
//
// Revision history
//
// $Log: BinderType.h,v $
// Revision 1.3  2002/12/06 16:25:28  cleo3
// put in std namespace when specializing less
//
// Revision 1.2  2001/09/07 17:00:21  cleo3
// modernized includes
//
// Revision 1.1  1998/06/17 18:18:18  mkl
// allow dynamic loading of source and sink formats
//
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Utility/UTIdentifier.h"

// STL classes
#include <string>

// forward declarations
#include "C++Std/fwd_ostream.h"
#include "STLUtility/fwd_vector.h"
class BinderBase;

#if !defined(_bindertype_arestandard_)
#define _bindertype_arestandard_ STL_VECTOR( DABoolean )
#endif /* _streamtype_priorities_ */


class BinderType : public UTIdentifier< string, BinderBase >
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BinderType( void );
      BinderType( const string& iString,
                  DABoolean iIsStandard=false );
      virtual ~BinderType();

      // member functions

      // const member functions
      DABoolean isStandard( void ) const;

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      //BinderType( const BinderType& );

      // assignment operator(s)
      //const BinderType& operator=( const BinderType& );

      // private member functions
      void setIsStandard( const DABoolean iIsStandard );

      // private const member functions
      DABoolean findIsStandard( void ) const;

      // static member functions
      static _bindertype_arestandard_& standards( void ) ;

      // data members

      // static data members

};

// inline function definitions

ostream& operator<<( ostream& iOStream, const BinderType& iBinderType );
istream& operator>>( istream& iIStream, BinderType& iBinderType ) ;
      
// needed so forward decleration in Stream.h can be done

// system include files
#include <functional>

// user include files
#include "Utility/UTIdentifierLess.h"

#if !defined( NO_STD_NAMESPACE_BUG)
namespace std {
#endif
template<>
class less< BinderType > : public UTIdentifierLess< string, BinderBase >
{
};
#if !defined( NO_STD_NAMESPACE_BUG)
}
#endif

#endif /* JOBCONTROL_BINDERTYPE_H */
