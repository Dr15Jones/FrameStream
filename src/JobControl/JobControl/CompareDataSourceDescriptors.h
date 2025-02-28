#if !defined(JOBCONTROL_COMPAREDATASOURCEDESCRIPTORS_H)
#define JOBCONTROL_COMPAREDATASOURCEDESCRIPTORS_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      CompareDataSourceDescriptors
// 
// Description: Function Object to compare DataSourceDescriptors 
//              (for use in set, map etc.)
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Sat Apr 24 11:10:37 EDT 1999
// $Id: CompareDataSourceDescriptors.h,v 1.2 1999/04/24 17:38:36 mkl Exp $
//
// Revision history
//
// $Log: CompareDataSourceDescriptors.h,v $
// Revision 1.2  1999/04/24 17:38:36  mkl
// avoid duplicate symbols (only OSF1)
//
// Revision 1.1  1999/04/24 16:22:57  mkl
// keep track of DataSourceDescriptors, not just names of files
//

// system include files

// user include files
#include "DataDelivery/DataSourceDescriptor.h"

// forward declarations

class CompareDataSourceDescriptors
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      //CompareDataSourceDescriptors();
      //~CompareDataSourceDescriptors();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      DABoolean operator()( const DataSourceDescriptor& iDSDa, 
			    const DataSourceDescriptor& iDSDb ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //CompareDataSourceDescriptors( 
      // const CompareDataSourceDescriptors& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const CompareDataSourceDescriptors& operator=( 
      // const CompareDataSourceDescriptors& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions
inline
DABoolean 
CompareDataSourceDescriptors::operator()( 
   const DataSourceDescriptor& iDSDa, 
   const DataSourceDescriptor& iDSDb ) const
{ 
   DABoolean returnValue(false);
   if( iDSDa.dataSourceID() < iDSDb.dataSourceID() ) {
      returnValue = true;
   } else
      if( iDSDa.dataSourceID() == iDSDb.dataSourceID() ) {
	 if( iDSDa.parameters() < iDSDb.parameters() ) {
	    returnValue = true;
	 }
      }
   return returnValue;
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/CompareDataSourceDescriptors.cc"
//#endif

#endif /* JOBCONTROL_COMPAREDATASOURCEDESCRIPTORS_H */
