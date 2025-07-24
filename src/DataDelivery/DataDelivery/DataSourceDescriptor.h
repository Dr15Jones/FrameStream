#if !defined(DATADELIVERY_DATASOURCEDESCRIPTOR_H)
#define DATADELIVERY_DATASOURCEDESCRIPTOR_H
// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      DataSourceDescriptor
// 
// Description: Contains all the information necessary to distinguish
//              one DataSource from another.
//
// Usage:
//    DataSourceDescriptors are use be FrameDeliverer to
//      1) Set the active streams
//      2) remove data sources
//      3) identify a source when returning a list of active sources
//      4) identify a source when returning a list of the status of all sources
//
// Author:      Chris D. Jones
// Created:     Mon Apr 21 11:47:07 EDT 1997
// $Id: DataSourceDescriptor.h,v 1.5 1999/10/08 21:42:25 mkl Exp $
//
// Revision history
//
// $Log: DataSourceDescriptor.h,v $
// Revision 1.5  1999/10/08 21:42:25  mkl
// make DataSourceDescriptor::setDataSourceID() public
//
// Revision 1.4  1998/04/01 18:09:15  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.3  1997/09/18 21:07:15  cdj
// changed Boolean to DABoolean
//
// Revision 1.2  1997/07/09 18:00:57  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1  1997/04/21 19:16:11  cdj
// First submission
//


// system include files

// user include files
#include "DataHandler/Stream.h"

#if defined(OLD_CXX_STRING_CLASS_BUG)
#include <string>
#include <String.h>
#else
#include <string>
#endif /* OLD_CXX_STRING_CLASS_BUG */

// forward declarations
class DataSourceController;

class DataSourceDescriptor
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      DataSourceDescriptor( const std::string& iDataSourceID = std::string(""),
			    const std::string& iParameters = std::string(""),
			    const Stream::Type& iBindStream= Stream::kNone);

      DataSourceDescriptor( const std::string& iDataSourceID,
			    const std::string& iParameters,
			    const Stream::Set& iBindStreams );

      DataSourceDescriptor( const DataSourceController& iController );

      DataSourceDescriptor( const DataSourceDescriptor& iDescriptor);

      virtual ~DataSourceDescriptor();

      // assignment operator(s)
      const DataSourceDescriptor& operator=( const DataSourceDescriptor& 
	                                     iDescriptor );

      // member functions
      void bindStreams( const Stream::Set& iBindStreams );
      void clearStreams( void );

      void setDataSourceID( std::string iDataSourceID );
      void setParameters( std::string iParameters ) ;

      // const member functions
      const Stream::Set& boundStreams( void ) const;

      const std::string& dataSourceID( void ) const;
      const std::string& parameters( void ) const;

      DABoolean operator==( const DataSourceController& iController ) const;
      DABoolean operator==( const DataSourceDescriptor& iDescriptor ) const;

      // static member functions

   protected:
      // protected member functions

      //void setDataSourceID( string iDataSourceID );
      //void setParameters( string iParameters ) ;

      // protected const member functions

   private:
      // Constructors and destructor

      // private member functions

      // private const member functions

      // data members

      // static data members
      Stream::Set& m_boundStreamList;
      std::string m_dataSourceID;
      std::string m_parameters;
};

// inline function definitions

#endif /* DATADELIVERY_DATASOURCEDESCRIPTOR_H */
