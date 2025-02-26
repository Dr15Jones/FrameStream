#if !defined(COMMANDPATTERN_LOADERBASE_H)
#define COMMANDPATTERN_LOADERBASE_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      LoaderBase
// 
// Description: Interface class for MasterPro[cessor,ducor] and others
//
// Usage:

// Author:      Martin  Lohner
// Created:     Thu Jan 15 15:48:09 EST 1997
// $Id: LoaderBase.h,v 1.3 2000/12/01 20:23:23 cdj Exp $
//
// Revision history (at end of file)
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

// forward declarations
#include "C++Std/fwd_string.h"
//class DLSharedObjectHandler;


class LoaderBase
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      LoaderBase( const string& environment );
      virtual ~LoaderBase();

      // member functions
      virtual DABoolean load( const string& iName ) = 0;
      virtual DABoolean unload( const string& iName ) = 0;
      virtual void unloadAll() = 0;

      // const member functions

      // listings
      virtual string listAvailable() const = 0;
      virtual string listLoaded   () const = 0;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      LoaderBase( const LoaderBase& ); // stop default
      
      // assignment operator(s)
      const LoaderBase& 
      operator=( const LoaderBase& ); // stop default

      // private member functions

      // data members

      // static data members

};

// inline function definitions


// ------------------------------------------------------
// Revision history
//
// $Log: LoaderBase.h,v $
// Revision 1.3  2000/12/01 20:23:23  cdj
// now uses DynamicLoader package
//
// Revision 1.2  1999/02/22 23:40:49  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.1  1998/11/09 19:31:34  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/06/23 23:01:12  mkl
// cleanup of LoaderBase
//
// Revision 1.1  1998/06/17 18:17:21  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.2  1998/04/01 17:58:00  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.1  1998/01/16 23:33:20  mkl
// added MasterProducer for selecting Producers at run time
//
#endif /* COMMANDPATTERN_LOADERBASE_H */
