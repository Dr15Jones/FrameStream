#if !defined(DYNAMICLOADER_SHAREDOBJECTHANDLER_H)
#define DYNAMICLOADER_SHAREDOBJECTHANDLER_H
// -*- C++ -*-
//
// Package:     DynamicLoader
// Module:      SharedObjectHandler
// 
// Description: Abstraction of Dynamic Loading of Objects
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue May 13 14:15:39 EDT 1997
// $Id: DLSharedObjectHandler.h,v 1.3 2003/03/31 19:42:55 cdj Exp $
//
// Revision history (at end of file )
//

// system include files

#if !defined(D_AIX)
#if !defined(Darwin)
#include <dlfcn.h> // for RTLD_NOW
#endif
#endif

#if defined(Darwin)
#include <mach-o/dyld.h>
#endif

// user include files
//#include "Utility/StringWrapper.h"

// STL include
#include <string>

// forward declarations
#include <map>

class DLSharedObject;
class DLMultiFactoryChooserBase;

class DLSharedObjectHandler
{
      // friend classses and functions
   public:
      // constants, enums and typedefs

      // Constructors and destructor
      DLSharedObjectHandler( const std::string& environmentVar );
      virtual ~DLSharedObjectHandler();

      // member functions
      DABoolean load( const std::string& iName, 
		      const std::string& iPatternString,
		      DLMultiFactoryChooserBase& iMultiFactoryChooser,
	              std::string& ioLoadedAsName,
#if defined(D_AIX) /* -------------AIX ---------------------------- */
		      const int = 0 );
#elif defined(SUNCC) /* --------- Solaris ------------------------ */
                      const int = RTLD_NOW|RTLD_GLOBAL );
#elif defined(Linux) /* --------- Linux -------------------------- */
                      const int = RTLD_NOW|RTLD_GLOBAL );
// bad with new OS patch:   const int = RTLD_NOW|RTLD_GLOBAL|RTLD_NODELETE );
#elif defined(Darwin) /* -------- OS X ---------------------------- */
const int = NSLINKMODULE_OPTION_BINDNOW );
#else /* ----------- the default for everybody else --------------- */
		      const int = RTLD_NOW );
#endif /* --------------------------------------------------------- */
      DABoolean unload( const std::string& iName );
      DABoolean unloadAll( void );

      // const member functions
      std::string listAvailable( const std::string& iPatternString ) const;
      std::string listLoaded() const;

      const DLSharedObject* fetch( const std::string& iName ) const;
      std::string fullName( const std::string& iName ) const;
      std::string shortName( const std::string& iName ) const;

      DABoolean getSymbol( const std::string& objectName, 
			   const std::string& symbolName, 
			   const DABoolean& verbose,
			   void*& symbol ) const;
			   
      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      DLSharedObjectHandler( const DLSharedObjectHandler& );

      // assignment operator(s)
      const DLSharedObjectHandler& operator=( const DLSharedObjectHandler& );

      // private member function

      // private const member functions
      DABoolean findAvailable( const std::string& iPatternString ) const;
      std::string extendedName( const std::string& iName ) const;

      // data members
      const std::string m_environmentVar;
      std::map< std::string, DLSharedObject* >& m_loaded;

      // here we have two ways to store full path+names:
      // 1.) key = procname, values = different paths for it
      // 2.) key = path,     values = different procnames
      std::multimap< std::string, std::string >& m_available;
      std::multimap< std::string, std::string >& m_availablePaths;

      // static data members

};

// inline function definitions

// -----------------------------------------------
// Revision history
//
// $Log: DLSharedObjectHandler.h,v $
// Revision 1.3  2003/03/31 19:42:55  cdj
// now works under OS X (Darwin)
//
// Revision 1.2  2001/02/26 15:38:43  cleo3
// modifications for Linux
//
// Revision 1.1.1.1  2000/11/30 20:51:30  cdj
// imported DynamicLoader source
//
// Revision 1.11  1999/10/08 21:45:19  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.10  1999/09/14 18:39:00  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.9  1999/02/24 19:27:07  mkl
// RTLD_NODELETE bad with new OS patch; for now disable
//
// Revision 1.8  1999/02/22 23:40:51  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.7  1999/02/09 19:29:10  mkl
// no unload of shared libs to avoid dependency effects
//
// Revision 1.6  1999/01/27 22:54:51  mkl
// rewrote StringUtil utility functions
//
// Revision 1.5  1998/11/09 19:31:44  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.4  1998/09/23 19:56:01  mkl
// undid mistakenly submitted C3String test changes
//
// Revision 1.3  1998/09/23 19:04:51  mkl
// typename; protect against multiple inclusion. All the make egcs happy
//
// Revision 1.2  1998/08/21 17:48:32  mkl
// special flag requierd for symbol resolution under solaris
//
// Revision 1.1  1998/06/17 18:17:23  mkl
// allow dynamic loading of source and sink formats
//
#endif /* DYNAMICLOADER_SHAREDOBJECTHANDLER_H */
