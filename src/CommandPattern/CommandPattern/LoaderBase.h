#if !defined(COMMANDPATTERN_LOADERBASE_H)
#define COMMANDPATTERN_LOADERBASE_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      LoaderBase
// 
// Description: LoaderBase
//              Base Loader class
//
// Usage:

// Author:      Martin  Lohner
// Created:     Mon Oct 26 15:48:09 EST 1998
// $Id: LoaderBase.h,v 1.6 2003/09/19 20:37:48 cdj Exp $
//
// Revision history (at end of file)
//

// system include files
#include <utility>

// user include files
#include "DynamicLoader/DLFactoryManager.h"

// forward declarations
#include <string>
#include <vector>
#include <map>

template< class T >
class LoaderBase 
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef std::map< std::string, T* > _loader_loaded_map_;

      // Constructors and destructor
      LoaderBase( const std::string& environment );
      virtual ~LoaderBase();

      // member functions
      virtual DABoolean alreadyLoaded(const std::string& iName);
      DABoolean alreadyLoadedFactory(const std::string& iName);
      
      // static factory
      DABoolean add( const std::string& iName, DLFactoryBase* iFactory );

      virtual DABoolean load( const std::string& iName );
      virtual DABoolean unload( const std::string& iName );
      virtual void unloadAll();

      ///retrieves already loaded item
      virtual T* fetch( const std::string& iName );

      // const member functions
      virtual const T* fetch( const std::string& iName ) const;

      // listings
      virtual std::string listAvailable() const;
      virtual std::string listAvailablePatternString() const { 
	 return std::string( "" ); 
      }
      virtual std::string listLoaded   () const;
      virtual std::string shortName(const std::string& iName) const;
      virtual std::string localPath(const std::string& iName) const;

      // allow child classes to overide this method
      virtual std::pair<std::string,std::string> disassembleName(const std::string& iName) const = 0;

      // static member functions

   protected:
      // protected member functions
      
      _loader_loaded_map_& loadedMap() { return m_loadedMap; }
      DLFactoryManagerPtr<T>& factoryManagerPtr() { return m_factoryManagerPtr; }

      // give derived class a change to perform specific actions
      virtual void initialize( const std::string& iName, T& )  {}
      virtual void finalize  ( const std::string& iName, T& )  {}
      virtual DABoolean canUnload(const std::string& iName, T&) {return true;}
      
      // protected const member functions

      const _loader_loaded_map_& loadedMap() const { return m_loadedMap; }
      const DLFactoryManagerPtr<T>& factoryManagerPtr() const { return m_factoryManagerPtr; }

      std::string factorySymbol() const ;

      // warning/error messages
      virtual std::string makeErrorMesg( const std::string& iName ) const;

   private:
      // Constructors and destructor
      LoaderBase( const LoaderBase& );    // stop default
      
      // assignment operator(s)
      const LoaderBase& operator=( const LoaderBase& ); // stop default

      // private member functions

      // private const member functions

      // data members

      //FactoryManager holds static Factories and does the dynamic loading 
      //   of the other Factories
      DLFactoryManagerPtr<T> m_factoryManagerPtr;

      // all selected "objects"
      // because maps don't preserve the order of entered items, need
      //  also vector to preserve order for execution
      _loader_loaded_map_ m_loadedMap; 

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/LoaderBase.cc"
#endif                                


// ---------------------------------------------------------------
// Revision history
//
// $Log: LoaderBase.h,v $
// Revision 1.6  2003/09/19 20:37:48  cdj
// added alreadyLoadedFactory and canUnload methods
//
// Revision 1.5  2003/03/19 19:50:56  vk
// Fix local path problem
//
// Revision 1.4  2003/03/12 21:34:02  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
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

#endif /* COMMANDPATTERN_LOADERBASE_H */
