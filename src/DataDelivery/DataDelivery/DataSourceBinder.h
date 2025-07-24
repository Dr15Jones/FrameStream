#if !defined(PACKAGE_DATASOURCEBINDER_H)
#define PACKAGE_DATASOURCEBINDER_H
// -*- C++ -*-
//
// Package:     DataHandler
// Module:      DataSourceBinder
// 
// Description: 
//     Binds one or more DataStreams to one DataSource
//
//      - There should be at least one DataSourceBinder for each type of 
//        DataSource.
//
//      -  DataBinder is an Abstract Class!
//        (The idea is to have concrete subclasses (eg. RoarSourceBinder)
//         inherit from DataSourceBinder)
//
//      - The main function of DataBinder is to:
//          - create a DataSourceController for the correct format
//          - provide the necessary initialization data to that 
//            DataSourceController
//
// Usage:
//    Method createDataSourceManager only returns properly initialized
//    DataSourceControllers.  If the DataSourceControllers can not be 
//    initialized properly, 0 is returned.
//
// Invariants:
//    Only method createDataSourceController knows if the requested bound 
//     streams can be read from the requested source.
//
// Author:      Chris D Jones
// Created:     Wed Mar 12 12:28:14 EST 1997
// $Id: DataSourceBinder.h,v 1.8 1998/06/17 18:19:56 mkl Exp $
//
// Revision history
//
// $Log: DataSourceBinder.h,v $
// Revision 1.8  1998/06/17 18:19:56  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.7  1997/08/14 11:43:12  sjp
// Mods to run under CW Pro 1
//
// Revision 1.6  1997/07/09 18:00:50  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.5  1997/04/21 19:17:19  cdj
// Now inherits from DataSourceDescriptor
//
// Revision 1.4  1997/03/20 22:25:42  cdj
// Added operator==( const DataSourceController& ) needed by FrameDeliverer
//
// Revision 1.3  1997/03/19 22:52:38  sjp
// Removed string include file, which crashes cxx
//
// Revision 1.2  1997/03/18 16:14:49  cdj
// Minor changes: 1) includes types.h which is needed for Boolean
//                2) bindStreams no longer returns a Boolean
//
// Revision 1.1  1997/03/13 21:51:42  cdj
// First submission.
// NOTE: No compilation has been attempted on this file so syntax errors are
// possible/likely.
//


// system include files

// user include files
#include "DataDelivery/DataSourceDescriptor.h"
#include "DataDelivery/Chainability.h"

// stl include files

// forward declarations
class DataSourceController;

class DataSourceBinder : public DataSourceDescriptor
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef NotChainable Chainability;

      // Constructors and destructor
      DataSourceBinder( const Stream::Set& iBindStreams );
      DataSourceBinder( const Stream::Type& iBindStream =  Stream::kNone ) ;

      DataSourceBinder( const std::string& iDataSourceID,
			const std::string& iParameters,
			const Stream::Set& iBindStreams );

      DataSourceBinder( const std::string& iDataSourceID,
			const std::string& iParameters,
			const Stream::Type& iBindStream );

      virtual ~DataSourceBinder();

      // member functions

      // const member functions

      virtual DataSourceController*
        createDataSourceController( void ) const = 0;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      DataSourceBinder( const DataSourceBinder& );

      // assignment operator(s)
      const DataSourceBinder& operator=( const DataSourceBinder& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* PACKAGE_DATASOURCEBINDER_H */

