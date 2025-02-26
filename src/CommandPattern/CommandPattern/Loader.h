#if !defined(COMMANDPATTERN_LOADER_H)
#define COMMANDPATTERN_LOADER_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      Loader
// 
// Description: Loader
//             
//              All T items must have a static string T::factorySymbol() 
//              function.
//
// Usage:

// Author:      Martin  Lohner
// Created:     Mon Oct 26 15:48:09 EST 1998
// $Id: Loader.h,v 1.10 2000/12/01 20:23:22 cdj Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "DynamicLoader/DLFactoryManager.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
#if !defined(_loader_loaded_map_)
#define _loader_loaded_map_  STL_MAP( string, T* )
#define _loader_loaded_      STL_VECTOR( string )
#endif

template< class T >
class Loader 
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      Loader( const string& environment );
      virtual ~Loader();

      // member functions

      // static factory
      DABoolean add( const string& iName, DLFactoryBase* iFactory );

      virtual DABoolean load( const string& iName );
      virtual DABoolean unload( const string& iName );
      virtual void unloadAll();

      ///retrieves already loaded item
      virtual T* fetch( const string& iName );

      virtual DABoolean reorder( const string& iListString );

      // const member functions
      virtual const T* fetch( const string& iName ) const;

      // listings
      virtual string listAvailable() const;
      virtual string listAvailablePatternString() const { 
	 return string( "" ); 
      }
      virtual string listLoaded   () const;

      // static member functions

   protected:
      // protected member functions

      _loader_loaded_map_& loadedMap() { return m_loadedMap; }
      _loader_loaded_&     loaded()    { return m_loaded; } 

      // give derived class a change to perform specific actions
      virtual void initialize( const string& iName, T& )  {}
      virtual void finalize  ( const string& iName, T& )  {}

      // protected const member functions

      const _loader_loaded_map_& loadedMap() const { return m_loadedMap; }
      const _loader_loaded_&     loaded()    const { return m_loaded; } 

      string factorySymbol() const ;

      // warning/error messages
      virtual string makeErrorMesg( const string& iName ) const;

   private:
      // Constructors and destructor
      Loader( const Loader& );    // stop default
      
      // assignment operator(s)
      const Loader& operator=( const Loader& ); // stop default

      // private member functions

      // private const member functions

      // data members

      //FactoryManager holds static Factories and does the dynamic loading 
      //   of the other Factories
      DLFactoryManagerPtr<T> m_factoryManagerPtr;

      // all selected "objects"
      // because maps don't preserve the order of entered items, need
      //  also vector to preserve order for execution
      _loader_loaded_map_& m_loadedMap; 
      _loader_loaded_&     m_loaded; 

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/Loader.cc"
#endif                                


// ---------------------------------------------------------------
// Revision history
//
// $Log: Loader.h,v $
// Revision 1.10  2000/12/01 20:23:22  cdj
// now uses DynamicLoader package
//
// Revision 1.9  1999/10/08 21:45:18  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.8  1999/09/14 22:33:14  mkl
// fix 'proc reorder' command to not unload processors first
//
// Revision 1.7  1999/09/14 18:38:58  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.6  1999/02/22 23:40:48  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.5  1998/11/12 02:23:50  mkl
// minor cleanup
//
// Revision 1.4  1998/11/10 23:21:58  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
// Revision 1.3  1998/11/10 03:53:03  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.2  1998/11/09 21:24:42  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.1  1998/11/09 19:31:32  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#endif /* COMMANDPATTERN_LOADER_H */
