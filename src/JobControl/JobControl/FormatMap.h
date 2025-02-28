#if !defined(JOBCONTROL_FORMATMAP_H)
#define JOBCONTROL_FORMATMAP_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      FormatMap
// 
// Description: abstract class: look-up table for formats
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:41:54 EDT 1998
// $Id: FormatMap.h,v 1.7 1998/11/09 19:33:26 mkl Exp $
//
// Revision history
//
// $Log: FormatMap.h,v $
// Revision 1.7  1998/11/09 19:33:26  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.6  1998/07/29 02:16:01  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.5  1998/07/28 15:37:39  mkl
// use .cc file for implementations
//
// Revision 1.4  1998/06/23 23:00:49  mkl
// cleanup of LoadableInterface
//
// Revision 1.3  1998/06/23 20:15:43  mkl
// minor bug fixes
//
// Revision 1.2  1998/06/17 20:20:57  mkl
// clean-out
//
// Revision 1.1  1998/06/17 18:19:29  mkl
// allow dynamic loading of source and sink formats
//

// system include files

// user include files
#include "CommandPattern/Loader.h"
#include "CommandPattern/Module.h"

// forward declarations
#include "C++Std/fwd_string.h"

template< class T >
class FormatMap : public Loader< T >, public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FormatMap( const string& moduleName, const string& environment )
	    : Loader< T >( environment ),
	      Module( moduleName, moduleName ) {}
      virtual ~FormatMap() {}

      // ---------- member functions ---------------------------
      // clear all formats
      virtual DABoolean clearAll() = 0;

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      // utility function to find name extensions
      static 
      string& findExtension( const string& iName, string& iExtension );

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FormatMap( const FormatMap& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FormatMap& operator=( const FormatMap& ); // stop default

      // ---------- private member functions -------------------
      // bind extensions to formats
      virtual DABoolean bind( const string& iFormatName,
			      const string& iExtension ) = 0;
      virtual DABoolean unbind( const string& iExtension ) = 0;
      virtual DABoolean unbindAll() = 0;

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions
template< class T >
inline
string&
FormatMap< T >::findExtension( const string& iName, string& iExtension )
{
   // figure out extension
   string::size_type i = iName.find_last_of( '/' );
   string basename( iName.substr( i+1, string::npos ) );
   string::size_type j = basename.find_last_of( '.' );
   //cout << "first . found or not; j = " << j << endl;
   if( j != string::npos ) {
      iExtension = basename.substr( j, string::npos );
      // if extension is .gz, need to look one '.' further back
      if( iExtension == ".gz" ) {
         string::size_type k = basename.rfind( '.', j-1 );
         if( k == j || k == string::npos ) {
            ; //cout << "no other '.', k=" << k << ", j" << endl;
         }
         else {
            iExtension = basename.substr( k, string::npos );
         }
      }
      //cout << "extension=" << extension << endl;
   }

   return iExtension;
}                      

#endif /* JOBCONTROL_FORMATMAP_H */
