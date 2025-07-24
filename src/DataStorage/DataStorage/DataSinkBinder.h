#if !defined(DATASTORAGE_DATASINKBINDER_H)
#define DATASTORAGE_DATASINKBINDER_H
// -*- C++ -*-
//
// Package:     DataStorage
// Module:      DataSinkBinder
// 
// Description: Binds one or more Streams to one DataSink
//
// Usage:
//      - There should be at least one DataSinkBinder for each type of 
//        DataSink.
//
//      -  DataBinder is an Abstract Class!
//        (The idea is to have concrete subclasses (eg. RoarSinkBinder)
//         inherit from DataSinkBinder)
//
//      - The main function of DataBinder is to:
//          - create a DataSinkController for the correct format
//          - provide the necessary initialization data to that 
//            DataSinkController
//
//    Method createDataSinkController only returns properly initialized
//    DataSinkControllers.  If the DataSinkControllers can not be 
//    initialized properly, 0 is returned.
//
// Invariants:
//    Only the DataSinkController created by the method 
//     createDataSinkController knows if the requested bound 
//     streams can be read from the requested sink.
//
// Author:      Chris D. Jones
// Created:     Sun May 25 15:03:11 EDT 1997
// $Id: DataSinkBinder.h,v 1.3 1998/06/17 18:20:11 mkl Exp $
//
// Revision history
//
// $Log: DataSinkBinder.h,v $
// Revision 1.3  1998/06/17 18:20:11  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.2  1997/07/11 06:20:13  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/30 15:41:37  cdj
// First submission
//


// system include files

// user include files
#include "DataStorage/DataSinkDescriptor.h"

// forward declarations

class DataSinkBinder : public DataSinkDescriptor
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      DataSinkBinder( const Stream::Set& iBindStreams );
      DataSinkBinder( const Stream::Type& iBindStream =  Stream::kNone ) ;

      DataSinkBinder( const std::string& iDataSinkID,
			const std::string& iParameters,
			const Stream::Set& iBindStreams );

      DataSinkBinder( const std::string& iDataSinkID,
			const std::string& iParameters,
			const Stream::Type& iBindStream );

      virtual ~DataSinkBinder();

      // member functions

      // const member functions
      virtual DataSinkController*
        createDataSinkController( void ) const = 0;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      DataSinkBinder( const DataSinkBinder& );

      // assignment operator(s)
      const DataSinkBinder& operator=( const DataSinkBinder& );

      // private member functions

      // private const member functions

      // data members

      // static data members

};

// inline function definitions

#endif /* DATASTORAGE_DATASINKBINDER_H */
