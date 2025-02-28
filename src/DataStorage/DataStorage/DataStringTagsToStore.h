#if !defined(DATASTORAGE_DATASTRINGTAGSTOSTORE_H)
#define DATASTORAGE_DATASTRINGTAGSTOSTORE_H
// -*- C++ -*-
//
// Package:     <DataStorage>
// Module:      DataNamesToStore
// 
/**\class DataNamesToStore DataNamesToStore.h DataStorage/DataNamesToStore.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Thu Sep 14 12:59:49 EDT 2000
// $Id: DataStringTagsToStore.h,v 1.1 2001/06/15 21:05:14 cdj Exp $
//
// Revision history
//
// $Log: DataStringTagsToStore.h,v $
// Revision 1.1  2001/06/15 21:05:14  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.1.1.1  2000/09/29 17:49:40  cdj
// imported
//

// system include files
#include <set>
#include <map>
#include <string>

// user include file
#include "DataHandler/Stream.h"

// forward declarations
#include "STLUtility/fwd_map.h"
#include "STLUtility/fwd_set.h"


class DataStringTagsToStore { // introduce utility class to 
   public:
      // ease map-of-set instantiation
      class DatumStringTags {
	 public:
	    DatumStringTags( string iType, 
		              string iUsage, 
		              string iProduction) :
	       m_type(iType),
	       m_usage(iUsage),
	       m_production(iProduction ) {}
	    const string& type() const {
	       return m_type; }
	    const string& usage() const {
	       return m_usage; }
	    const string& production() const {
	       return m_production; }
	    DABoolean operator<( const DatumStringTags& iRHS ) const {
	       if( m_type != iRHS.m_type ) {
		  return m_type < iRHS.m_type;
	       } else if( m_usage != iRHS.m_usage ) {
		  return m_usage < iRHS.m_usage;
	       }
	       return m_production < iRHS.m_production;
	    }

	 private:
	    string m_type;
	    string m_usage;
	    string m_production;
      };

   public:
      typedef STL_SET( DatumStringTags ) Tags;
      typedef Tags::const_iterator const_iterator;
      typedef Tags::iterator iterator;
      DataStringTagsToStore( const Tags& iTags, DABoolean iStoreThese = true ):
         m_tags( iTags ), m_storeThese(iStoreThese) {}
      DataStringTagsToStore() {}

      Tags& operator()() { return m_tags; }
      const Tags& operator()() const { return m_tags; }
      
      DABoolean storeThese() const {return m_storeThese; }
   private:
      Tags m_tags;
      DABoolean m_storeThese;
};


// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DataStorage/Template/DataNamesToStore.cc"
//#endif

#endif /* DATASTORAGE_DATASTRINGTAGSTOSTORE_H */
