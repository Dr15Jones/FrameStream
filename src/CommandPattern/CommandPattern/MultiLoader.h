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
#include <string>
#include <vector>
#include <map>

template< class T >
class MultiLoader : public LoaderBase<T>
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef std::vector< std::string > _loader_loaded_;

      // Constructors and destructor
      MultiLoader( const std::string& environment );
      virtual ~MultiLoader();

      // member functions
      
      virtual DABoolean load( const std::string& iName );
      virtual DABoolean load( const std::string& iName, const std::string& iTag );
      virtual DABoolean unload( const std::string& iName );
      virtual void unloadAll();

      virtual DABoolean reorder( const std::string& iListString );
      
      virtual std::pair<std::string,std::string> disassembleName(const std::string& iName) const;

      // static factory

      // static member functions

   protected:
      // protected member functions
      _loader_loaded_&     loaded()    { return m_loaded; } 

      // warning/error messages
      virtual std::string makeErrorMesg( const std::string& iName ) const;
      // give derived class a change to perform specific actions
      virtual void initializeTag( const std::string& iTag, T& )  {}

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
