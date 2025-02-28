#if !defined(COMMANDPATTERN_MULTILOADER_H)
#define COMMANDPATTERN_MULTILOADER_H
// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      MultiLoader
// 
// Description: MultiLoader based on LoaderBase class and adds multi
//              load functionality.
//
// Usage:
//
// Author:      Valentine Kouznetsov
// Created:     Tue Mar  4 15:36:40 EST 2003
// $Id: MultiLoader.h,v 1.2 2003/11/20 18:34:26 vk Exp $
//
// $Log: MultiLoader.h,v $
// Revision 1.2  2003/11/20 18:34:26  vk
// Get rid of define statement, use typedef instead.
//
// Revision 1.1  2003/03/12 21:34:03  vk
// Redesign loader class into LoaderBase, Loader (single loader) and MultiLoader
//
//

// system include files
#include <utility>

// user include files
#include "CommandPattern/LoaderBase.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"

template< class T >
class MultiLoader : public LoaderBase<T>
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef STL_VECTOR( string ) _loader_loaded_;

      // Constructors and destructor
      MultiLoader( const string& environment );
      virtual ~MultiLoader();

      // member functions
      
      virtual DABoolean load( const string& iName );
      virtual DABoolean load( const string& iName, const string& iTag );
      virtual DABoolean unload( const string& iName );
      virtual void unloadAll();

      virtual DABoolean reorder( const string& iListString );
      
      virtual pair<string,string> disassembleName(const string& iName) const;

      // static factory

      // static member functions

   protected:
      // protected member functions
      _loader_loaded_&     loaded()    { return m_loaded; } 

      // warning/error messages
      virtual string makeErrorMesg( const string& iName ) const;
      // give derived class a change to perform specific actions
      virtual void initializeTag( const string& iTag, T& )  {}

      // protected const member functions
      const _loader_loaded_&     loaded()    const { return m_loaded; } 


   private:
      // Constructors and destructor
      MultiLoader( const MultiLoader& );    // stop default      
      const MultiLoader& operator=( const MultiLoader&); // stop default

      // private member functions

      // private const member functions

      // data members
      _loader_loaded_&     m_loaded;

      // static data members

};

// inline function definitions

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/MultiLoader.cc"
#endif                                


#endif /* COMMANDPATTERN_MULTILOADER_H */
