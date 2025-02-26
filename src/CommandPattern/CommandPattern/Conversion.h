#if !defined(COMMANDPATTERN_CONVERSION_H)
#define COMMANDPATTERN_CONVERSION_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Conversion
// 
// Description: package of conversion routines
//              If I could, I would use templated member functions...
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Sep  4 15:35:25 EDT 1997
// $Id: Conversion.h,v 1.3 1999/10/25 18:50:04 mkl Exp $
//
// Revision history
//
// $Log: Conversion.h,v $
// Revision 1.3  1999/10/25 18:50:04  mkl
// fixed wrong logic for Parameter< bool > instantiation
//
// Revision 1.2  1999/09/10 02:42:53  mkl
// location of Conversion class has moved
//
// Revision 1.1  1999/09/10 01:04:54  mkl
// 1) new smarter history command.
// 2) new "uppercase" function, since our compilers don't support it yet.
// 3) moved "Conversion" class to CommandPattern (needed by HistoryCommand).
//
// Revision 1.2  1997/09/18 21:27:00  cdj
// changed Boolean to DABoolean
//
// Revision 1.1  1997/09/05 02:37:22  mkl
// wrap asynchronous interrupt handling in wrapper class
//

// system include files

// user include files

// forward declarations

class Conversion
{
      // friend classes and functions
      friend class Dummy; // to get rid of g++ warnings

   public:

      // constants, enums and typedefs

      // Constructors and destructor

      // member functions

      // const member functions

      // static member functions
      static long          stringToDigit( const char* c, DABoolean& isNumber );
      static int           stringToInt  ( const char* c, DABoolean& isNumber );
      static unsigned int  stringToUInt ( const char* c, DABoolean& isNumber );
      static long          stringToLong ( const char* c, DABoolean& isNumber );
      static unsigned long stringToULong( const char* c, DABoolean& isNumber );

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      Conversion();
      virtual ~Conversion();

      Conversion( const Conversion& );

      // assignment operator(s)
      const Conversion& operator=( const Conversion& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "CommandPattern/Template/Conversion.cc"
//#endif

#endif /* COMMANDPATTERN_CONVERSION_H */
