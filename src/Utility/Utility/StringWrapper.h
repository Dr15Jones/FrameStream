#if !defined(UTILITY_STRINGWRAPPER_H)
#define UTILITY_STRINGWRAPPER_H
// -*- C++ -*-
//
// Package:     <Utility>
// Module:      StringWrapper
// 
// Description: Wrapper for standard string class: only needed
//              because g++.2.7.2 can't handle "map< string, string >"
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon Nov 24 13:10:31 EST 1997
// $Id: StringWrapper.h,v 1.3 1998/07/03 19:51:00 mkl Exp $
//
// Revision history
//
// $Log: StringWrapper.h,v $
// Revision 1.3  1998/07/03 19:51:00  mkl
// move fwd_string include before OLD_*_STRING* bug flag
//
// Revision 1.2  1998/04/01 15:56:36  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.1  1997/11/24 18:31:26  mkl
// new StringWrapper class to get around g++ proboem with map<string, string>
//

// system include files

// user include files

// STL include
#include <string>

// forward declarations

class StringWrapper
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      StringWrapper( std::string& iString );
      StringWrapper();
      // default copy constructor is fine!
      ~StringWrapper();

      // member functions
      std::string& operator()();

      // const member functions
      const std::string& operator()() const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      //StringWrapper( const StringWrapper& );

      // assignment operator(s)
      //const StringWrapper& operator=( const StringWrapper& );

      // private member functions

      // private const member functions

      // data members
      std::string m_string;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "Utility/Template/StringWrapper.cc"
//#endif

#endif /* UTILITY_STRINGWRAPPER_H */
