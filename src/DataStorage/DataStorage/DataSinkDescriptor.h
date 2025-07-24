#if !defined(DATASTORAGE_DATASINKDESCRIPTOR_H)
#define DATASTORAGE_DATASINKDESCRIPTOR_H
// -*- C++ -*-
//
// Package:     DataStorage
// Module:      DataSinkDescriptor
// 
// Description: Contains all the information necessary to distinguish
//              one DataSink from another.
//
// Usage:
//    DataSinkDescriptors are used by FrameStorer to
//       1) remove data sinks
//       2) identify a sink when returning a list of the status of all sinks
//
// Author:      Chris D. Jones
// Created:     Sun May 25 15:03:23 EDT 1997
// $Id: DataSinkDescriptor.h,v 1.3 1997/09/18 21:13:17 cdj Exp $
//
// Revision history
//
// $Log: DataSinkDescriptor.h,v $
// Revision 1.3  1997/09/18 21:13:17  cdj
// Changed Boolean to DABoolean
//
// Revision 1.2  1997/07/11 06:20:15  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/30 15:41:38  cdj
// First submission
//


// system include files

// user include files
#include "DataHandler/Stream.h"


// forward declarations
class DataSinkController;

class DataSinkDescriptor
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      DataSinkDescriptor( const std::string& iDataSinkID = std::string(""),
			  const std::string& iParameters = std::string(""),
			  const Stream::Type& iBindStream= Stream::kNone);

      DataSinkDescriptor( const std::string& iDataSinkID,
			    const std::string& iParameters,
			    const Stream::Set& iBindStreams );

      DataSinkDescriptor( const DataSinkController& iController );

      DataSinkDescriptor( const DataSinkDescriptor& iDescriptor);

      virtual ~DataSinkDescriptor();

      // assignment operator(s)
      const DataSinkDescriptor& operator=( const DataSinkDescriptor& );

      // member functions
      void bindStreams( const Stream::Set& iBindStreams );
      void clearStreams( void );

      // const member functions
      const Stream::Set& boundStreams( void ) const;

      const std::string& dataSinkID( void ) const;
      const std::string& parameters( void ) const;

      DABoolean operator==( const DataSinkController& iController ) const;
      DABoolean operator==( const DataSinkDescriptor& iDescriptor ) const;

      // static member functions

   protected:
      // protected member functions
      void setDataSinkID( std::string iDataSinkID );
      void setParameters( std::string iParameters ) ;

      // protected const member functions

   private:
      // Constructors and destructor

      // private member functions

      // private const member functions

      // data members

      // static data members
      Stream::Set& m_boundStreamList;
      std::string m_dataSinkID;
      std::string m_parameters;
};

// inline function definitions

#endif /* DATASTORAGE_DATASINKDESCRIPTOR_H */
