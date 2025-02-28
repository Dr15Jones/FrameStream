// -*- C++ -*-
//
// Package:     DynamicLoader
// Module:      DLSharedObjectHandler
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implimentation>
//
// Author:      Martin Lohner
// Created:     Tue May 13 14:15:23 EDT 1997
// $Id: DLSharedObjectHandler.cc,v 1.5 2003/03/31 19:42:53 cdj Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#include "C++Std/iostream.h"
#include <stdio.h>
#if !defined(D_AIX)
#if !defined(Darwin)
#include <dlfcn.h>
#endif
#else
#if defined(D_AIX)
#include <sys/ldr.h>
#include <sys/errno.h>
#endif
#endif                   
#include <stdlib.h>
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif                         
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DynamicLoader/DLSharedObjectHandler.h"
#include "DynamicLoader/DLSharedObject.h"
#include "DynamicLoader/DLSymbolNotFoundException.h"
#include "DynamicLoader/DLMultiFactoryChooserBase.h"
#include "Utility/FileNameUtils.h"

// STL classes
#include <vector>
#if defined(MULTIMAP_IS_SEPARATE_FILE_BUG)
#  include <map>
#  include <multimap.h>
#else
#  include <map>
#endif                     
#include <algorithm>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "DynamicLoader.DLSharedObjectHandler";

typedef STL_MAP( string, DLSharedObject* ) DLSharedObjectMap;
typedef STL_MULTIMAP( string, string ) FilenamePathMMap;

//
// static data member definitions
//

//
// constructors and destructor
//
DLSharedObjectHandler::DLSharedObjectHandler( const string& environmentVar )
   : m_environmentVar( environmentVar ),
     m_loaded( *new DLSharedObjectMap ),
     m_available( *new FilenamePathMMap ),
     m_availablePaths  ( *new FilenamePathMMap )
{
   if(    0 == &m_loaded
       || 0 == &m_available
       || 0 == &m_availablePaths
      )
   {
      report( EMERGENCY ,
              kFacilityString )
                 << "Unable to allocate memory"
                 << endl ;
      assert(false);
      ::exit( 1 );
   }
}

// DLSharedObjectHandler::DLSharedObjectHandler( const DLSharedObjectHandler& )
// {
// }

DLSharedObjectHandler::~DLSharedObjectHandler( void )
{
   unloadAll();
   delete &m_loaded;
   delete &m_available;
   delete &m_availablePaths;
}

//
// assignment operators
//
// const DLSharedObjectHandler& DLSharedObjectHandler::operator=( const DLSharedObjectHandler& )
// {
// }

//
// member functions
//
DABoolean 
DLSharedObjectHandler::load( const string& iName, 
			     const string& iPatternString,
			     DLMultiFactoryChooserBase& iMultiFactoryChooser,
			     string& oLoadedAsName,
			     const int loadMode )
{
   DABoolean returnValue = true;

   // initialize properly
   oLoadedAsName = shortName( iName );

   // check that it hasn't been loaded yet
   if( 0 != fetch( oLoadedAsName ) )
   {
      report( ERROR, kFacilityString )
	 << "\"" << oLoadedAsName << "\" is already loaded" << endl;
      return returnValue = false;
   }

   // add .so if not present
   string extended_name = extendedName( iName );

   // remake "database"
   if( false == findAvailable( iPatternString ) ) return( returnValue = false );

   // 1.) first assume that user is only specifying the filename, 
   //     not the whole path
   // 2.) if that fails, then we assume he's specifying the whole thing
   string fullName;
   FilenamePathMMap::iterator which = m_available.find( extended_name );
   if( m_available.end() == which ) // didn't find it
   {                             
      // assume that user specified full path name
      fullName = extended_name;

      // but can check that pattern was satisfied
      if( iPatternString.size() != 0 && 
	  string::npos == fullName.find( iPatternString ) )
      {
	 report( ERROR, kFacilityString )
	    << "Specified shared-module doesn't fit pattern \"" 
	    << iPatternString << "\"" << endl;
	 return returnValue = false;
      }
   }
   else // found it in map
   {
      // have to make sure there aren't more than one possibility
      string path = (*which).second;
      string filename = (*which).first;
      fullName = path+filename;

      Count howManySuppliers = m_available.count( extended_name );

      if( howManySuppliers > 1 ) {

	 //create a list of the paths we can use
	 STL_VECTOR(string) suppliers;
	 suppliers.reserve(howManySuppliers);

	 FilenamePathMMap::iterator last
	    = m_available.upper_bound( extended_name ); 
	 for( FilenamePathMMap::iterator object
		 = m_available.lower_bound( extended_name ); 
	      object != last;
	      ++object )
	 {
	    suppliers.push_back( (*object).second ) ;
	 }
	 
	 STL_VECTOR(string)::iterator itChoice = 
	    iMultiFactoryChooser.choose( extended_name,
					 suppliers.begin(),
					 suppliers.end() );
	 
	 fullName = (*itChoice) + extended_name;

      }

   }


#if !defined(D_AIX ) && !defined(Darwin) /* -------------------------------------------- */

#if defined(OLD_CXX_STRING_CLASS_BUG)
   void* handle = dlopen( (char*)fullName, loadMode );
#else
   void* handle = dlopen( fullName.c_str(), loadMode );
#endif /* OLD_CXX_STRING_CLASS_BUG */
   if( NULL == handle ) // handle ok?
   {
      report( ERROR, kFacilityString )
	 << dlerror() << endl;
      returnValue = false;
   }

#else /* --------------------- AIX -------------------------------- */
#if defined(D_AIX)
   int (*handle)() = load( (char*)fullName.c_str(), 0, NULL );
   if( NULL == handle ) // loaded shared module?
   {
      char buffer[100];
      loadquery(L_GETMESSAGES, buffer, 100);
      report( ERROR, kFacilityString )
         << "Could not open " << fullName << "\n"
         << "errno = " << errno << "\n"
         << buffer << endl;
      returnValue = false;
   }
#endif
#if defined(Darwin)
   NSObjectFileImage imageHandle;
   NSObjectFileImageReturnCode status;
   if( NSObjectFileImageSuccess != (status = NSCreateObjectFileImageFromFile(fullName.c_str(), &imageHandle) ) ) {
     switch(status) {
     case NSObjectFileImageFailure:
       report( ERROR, kFacilityString ) <<"failure: "<<fullName<< endl;
       break;
     case NSObjectFileImageInappropriateFile:
       report( ERROR, kFacilityString ) <<"inappropriate file: "<<fullName<<endl;
       break;
     case NSObjectFileImageFormat:
       report( ERROR, kFacilityString ) <<"not an image format: "<<fullName<<endl;
       break;
     default:
       report( ERROR, kFacilityString ) <<"unknown error: "<<fullName<<endl;
     }
     returnValue=false;
   }
   NSModule handle;
   if( returnValue ) {
     handle = NSLinkModule(imageHandle, shortName(iName).c_str(),loadMode | NSLINKMODULE_OPTION_RETURN_ON_ERROR );
   }
   if( NULL==handle ) {
     NSLinkEditErrors errorCode;
     int errorNumber;
     const char* fileName;
     const char* errorString;
     NSLinkEditError(&errorCode, &errorNumber, &fileName, &errorString);
     report( ERROR, kFacilityString ) <<fileName <<" "<<errorString<<endl;
     returnValue = false;
   }
#endif
#endif /* --------------------------------------------------------- */
   else
   {
      DLSharedObject* soObject = new DLSharedObject(fullName, handle);

      // keep track with its short name
      oLoadedAsName = shortName( fullName );

      // insert in map
      m_loaded.insert( 
	 DLSharedObjectMap::value_type( oLoadedAsName, soObject ) );
   }

   return returnValue;
}

DABoolean 
DLSharedObjectHandler::unload( const string& iName )
{
   DABoolean returnValue = true;

   DLSharedObjectMap::iterator iter
      = m_loaded.find( iName );

   if( iter != m_loaded.end() )
   {
      assert( (*iter).second != 0 );
      assert( (*iter).second->handle() != 0 );

// -----------------------------------------------------------------
// quick fix for unload problems: don't unload shared libs anymore
// until we can unload in opposite order from load order
//#if !defined(D_AIX) /* -------------------------------------------- */
//
//      // close handle
//#if !defined(SUNCC) // for now since RTLD_NODELETE doesn't work right
//      dlclose( (*iter).second->handle );
//#endif
//
//#else /* --------------------- AIX -------------------------------- */
//
//      unload( (*iter).second->handle );
//
//#endif /* --------------------------------------------------------- */

      delete (*iter).second;
      m_loaded.erase( iter );
   } 
   else 
   {
      report( WARNING, kFacilityString )
         << "couldn't find DLSharedObject \"" << iName
         << "\" in loaded object list" << endl;
      returnValue = false;
   }

   return returnValue;
}

DABoolean 
DLSharedObjectHandler::unloadAll( void )
{
   DABoolean returnValue = true;

   while( !m_loaded.empty() )
   {
      DLSharedObjectMap::iterator itDelete = m_loaded.begin();
//      delete (*itDelete).second;
//      m_loaded.erase(itDelete);
      unload( (*itDelete).first );
   }
  
   return returnValue;
}

string
DLSharedObjectHandler::listAvailable( const string& iPatternString ) const
{
   string returnValue;

   if( false == findAvailable( iPatternString ) ) return returnValue;

   string previousPath = "";
   FilenamePathMMap::const_iterator endPath = m_availablePaths.end();
   for( FilenamePathMMap::const_iterator path = m_availablePaths.begin();
	path != endPath;
	++path )
   {
      // only print different keys!
      if( previousPath == (*path).first ) continue;
      previousPath = (*path).first;

      // first print path
      returnValue += string( "\n" ) + (*path).first;

      // second print all  for that path
      FilenamePathMMap::const_iterator lastSpecificEntry
	 = m_availablePaths.upper_bound( (*path).first );

      unsigned int i=0;
      for( FilenamePathMMap::const_iterator specificEntry
              = m_availablePaths.lower_bound( (*path).first );
           specificEntry != lastSpecificEntry;
           ++i, ++specificEntry )
      {
	 if( i > 0 ) 
	 {
	    string space = " ";
	    for( unsigned int j=0; j<(*path).first.size(); ++j )
	    {
	       space += " ";
	    }
	    returnValue += space;
	 }

	 // don't print .so if present
	 string name = (*specificEntry).second;
	 string extension = FileNameUtils::extension( (*specificEntry).second );
	 if( string( ".so" ) == extension )
	 {
	    name = FileNameUtils::basename( (*specificEntry).second );
	 }

	 // assemble result string
	 returnValue += name + string( "\n" );

      }
   }

   return returnValue;
}

DABoolean
DLSharedObjectHandler::findAvailable( const string& iPatternString ) const
{
   DABoolean returnValue = true;

   //remove this when 'mutable' available
   STL_MULTIMAP( string, string )& t_available = 
      const_cast<DLSharedObjectHandler*>(this)->m_available;
   STL_MULTIMAP( string, string )& t_availablePaths = 
      const_cast<DLSharedObjectHandler*>(this)->m_availablePaths;

   // reset t_available
   t_available.erase( t_available.begin(), 
			     t_available.end() );
   t_availablePaths  .erase( t_availablePaths.begin(), 
			     t_availablePaths.end() );

#if defined(OLD_CXX_STRING_CLASS_BUG)
   char* tempChar = getenv( (char*)m_environmentVar );
#else
   char* tempChar = getenv( m_environmentVar.c_str() );
#endif /* OLD_CXX_STRING_CLASS_BUG */

   if( 0 == tempChar )
   {
      // still return true, because user might have 
      // specified complete path without using environment variable!
      return returnValue = true;
   }
   // have valid environment variable

   vector<char> environmentVec;
   while( *tempChar != '\0' ) environmentVec.push_back( *tempChar++ );

   // the environment variable consists of "dir1":"dir2":etc
   vector<char>::iterator start = environmentVec.begin();
   if( *start == ':' ) ++start; // proceed beyond initial ':'
   vector<char>::iterator where = start;
   while( where != environmentVec.end() )
   {
      where = find( start, environmentVec.end(), ':' );
      if( where == start ) break;  // in case we're RIGHT ON the ':'

      vector<char> directoryVec( int( where - start ) );
      copy( start, where, directoryVec.begin() );

      directoryVec.push_back( '\0' ); // for char* termination
      
      //the size already includes the null 0
      char* newDirectory = new char[ directoryVec.size() ];
      copy( directoryVec.begin(), directoryVec.end(), newDirectory );

      string sNewDirectory(newDirectory);
      // delete char*
      delete [] newDirectory;


      //need to do 'cd' and then 'ls' to avoid the ARG list passed
      // to the shell is below the max length.  The ARG length
      // also includes the user's environment variables as well
      // as the length of the string returned by the ls.
      string command = 
	   string( "[ -d ") + sNewDirectory + string( " ] && ( cd " ) 
	 + sNewDirectory
	 + string( "; ls -1 *" ) + iPatternString + string( "*.so " ) 
	 + string( "2>/dev/null )" );

      if (!sNewDirectory.empty() && sNewDirectory[sNewDirectory.size()-1] !='/') {
	 sNewDirectory += string("/");
      }
      FILE* commandOutput;
#if defined(OLD_CXX_STRING_CLASS_BUG)
      if( ( commandOutput = popen( (char*)command, "r" ) ) == NULL )
      {
	 report( EMERGENCY, kFacilityString ) 
	    << "Can't run" << command << endl;
      }
#else
      if( ( commandOutput = popen( command.c_str(), "r" ) ) == NULL )
      {
	 report( EMERGENCY, kFacilityString ) 
	    << "Can't run" << command << endl;
      }
#endif /* OLD_CXX_STRING_CLASS_BUG */

      const Count BUFSIZE = 256;
      char buf[BUFSIZE];
      while( fgets( buf, sizeof( buf ), commandOutput ) != NULL )
      {
	 buf[strlen(buf)-1] = '\0';    // suppress \n

	 string fullThing( buf );
	 fullThing = sNewDirectory+fullThing;

	 // record output string (shared lib path+name)
	 string path     = FileNameUtils::path( fullThing );
	 string filename = FileNameUtils::filename( fullThing ); 
	 
	 t_available.insert( 
	    FilenamePathMMap::value_type( filename, path ) );
	 t_availablePaths.insert( 
	    FilenamePathMMap::value_type( path, filename ) );
      }

      pclose( commandOutput );

      // start directoryVec from scratch
      directoryVec.erase( directoryVec.begin(), directoryVec.end() );
      
      // update start
      start = where+1; // get beyond ':'
   }      

   return returnValue;
}


//
// const member functions
//
string
DLSharedObjectHandler::listLoaded() const
{
   string returnValue;

   DLSharedObjectMap::const_iterator begin( m_loaded.begin() );
   DLSharedObjectMap::const_iterator end  ( m_loaded.end()   );

   for( DLSharedObjectMap::const_iterator object = begin;
        object != end;
        ++object )
   {
      // assemble result string
      returnValue += string( " " ) + (*object).first + string( "\n" );
   }

   return returnValue;
}

const DLSharedObject* 
DLSharedObjectHandler::fetch( const string& iName ) const
{
   DLSharedObject* object = 0;

   DLSharedObjectMap::iterator iter = m_loaded.find( iName );

   if( iter != m_loaded.end() )
   {
      object = (*iter).second;

   } else {
//      report( WARNING, kFacilityString )
//         << "couldn't find DLSharedObject \""
//         << name << "\" in loaded DLSharedObjectMap" << endl;
      object = 0;
   }

   return object;            
}


DABoolean 
DLSharedObjectHandler::getSymbol( const string& iObjectName, 
				const string& symbolName, 
				const DABoolean& verbose,
				void*& symbol ) const
{
   DABoolean returnValue = true;

   const DLSharedObject* object = fetch( iObjectName );

   if( 0 != object )
   {
      try {
	 symbol = object->getSymbol( symbolName );

      } catch( DLSymbolNotFoundException& iException ) {
         if( true == verbose ) {
	    report( ERROR, kFacilityString ) << iException.what() << endl;
	 }
	 returnValue = false;
      }
   }
   else
   {
      report( EMERGENCY, kFacilityString ) 
	 << "No such DLSharedObject " << "\"" << iObjectName << "\"" << endl;
      returnValue = false;
   }

   return returnValue;
}

string
DLSharedObjectHandler::fullName( const string& iName ) const
{
   string returnValue;

   const DLSharedObject* shobject = fetch( iName );
   if( 0 != shobject )
   {
      returnValue = shobject->name();
   }
//   else
//   {
//      report( ERROR, kFacilityString )
//         << "no such shared object " << iName << endl;
//   }

   return returnValue;
}

string
DLSharedObjectHandler::shortName( const string& iName ) const
{
   return FileNameUtils::basename( iName );
}

string
DLSharedObjectHandler::extendedName( const string& iName ) const
{
   // add ".so" to name, if not present
   string extension = FileNameUtils::extension( iName, '.' );
   if( !( string( ".so" ) == extension ) )
   {
      return iName + string( ".so" );
   }
   else
   {
      return iName;
   }
}

//
// static member functions
//


// ------------------------------------------------------------
// Revision history
//
// $Log: DLSharedObjectHandler.cc,v $
// Revision 1.5  2003/03/31 19:42:53  cdj
// now works under OS X (Darwin)
//
// Revision 1.4  2002/08/16 14:54:20  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.3  2002/02/27 02:08:02  cdj
// changed command used to get list of shared objects to avoid problems with too long shell arguments
//
// Revision 1.2  2001/02/26 15:38:08  cleo3
// avoid C++ standard's ambiguity wrt string::find with empty string
//
// Revision 1.1.1.1  2000/11/30 20:51:31  cdj
// imported DynamicLoader source
//
// Revision 1.16  2000/05/15 15:33:58  mkl
// switch non-EMERGENCY suez messages to SYSTEM severity level
//
// Revision 1.15  2000/05/01 21:00:28  cdj
// SharedObjectHandler now properly lists loadables when a pattern is used
//
// Revision 1.14  2000/03/22 23:35:49  mkl
// turned cin-related couts into report(EMERGENCY) so that can check for errors in logfiles AND avoid too-high report level
//
// Revision 1.13  2000/02/03 17:08:29  mkl
// fix prompting response when several options present
//
// Revision 1.12  1999/11/07 18:22:49  mkl
// unresolved symbols: print on regular report stdout rather than sterr
//
// Revision 1.11  1999/10/26 17:41:52  mkl
// print 'memory' properly for memory-based modules
//
// Revision 1.10  1999/10/08 21:45:15  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.9  1999/09/14 18:38:53  mkl
// run_command wants to replace tcl_source; print better message when loading processor as producer
//
// Revision 1.8  1999/07/06 18:48:44  mkl
// dont unload shared objects at suez exit anymore (should avoid problems of unloading in improper order and speed things up)
//
// Revision 1.7  1999/02/26 00:36:57  mkl
// for now dont do dlclose on Solaris until RTLD_NODELETE problem is solved
//
// Revision 1.6  1999/02/22 23:40:44  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.5  1999/01/27 22:54:49  mkl
// rewrote StringUtil utility functions
//
// Revision 1.4  1998/12/02 06:02:52  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.3  1998/11/09 19:31:08  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/09/23 19:55:59  mkl
// undid mistakenly submitted C3String test changes
//
// Revision 1.1  1998/06/17 18:17:17  mkl
// allow dynamic loading of source and sink formats
//
