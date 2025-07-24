#if !defined(DATASTORAGE_DATASINKCONTROLLER_H)
#define DATASTORAGE_DATASINKCONTROLLER_H
// -*- C++ -*-
//
// Package:     DataStorage
// Module:      DataSinkController
// 
// Description: Abstract base class for classes used to write to
//              different data sinks
//
// Usage:
//    Used by FrameStorer to open a connection to a data sink.
//    Owns the ProxyStorer which is used to write Proxys to
//    the data sink.
//
//    A DataSinkController writes certain data records to one type
//     of data sink.  The DataSinkController knows what types of records 
//     can be in the sink (referred to as "potentialRecordsToStore"). 
//     The user tells the DataSinkController which data sink it should
//     use as well as any additional parameters and also tells it which of 
//     the potential record types the DataSinkController should actually 
//     write (these are referred to as "recordsToRetrieve").
//
//    Users do not communicate directly with DataSinkControllers.  Instead
//     they use DataSinkBinders to Bind Streams to a Data Sink.  The
//     DataSinkBinder is given to FrameStorer and FrameStorer asks
//     the DataSinkBinder to create the necessary DataSinkController.
//
//    Since users never directly use DataSinkControllers, we will not discuss
//     how to use a DataSinkController.  Instead we will discuss how to
//     write a DataSinkController.
//
//    A DataSinkController must perform the following tasks
//      1) Initialize the data sink
//      2) Be able to describe its data sink
//      3) create the necessary ProxyStorer
//
//    Initializing the Data Sink
//      Data sinks are initialized in the constructor.  E.g. if the
//       data sink is a file, that file is opened in the constructor.
//       In addition you must call
//       a) 'setRecordsToStore(...)' with the set of Streams the user 
//          wants read from this sink (E.g. Events from a roar file).  
//       d) 'setInitializationStatus(...)' with the appropriate value if
//          there was a problem. (If you do not call it, it will default to
//          no problem).
//
//    Describing the Data Sink
//      FrameStorer needs to be able to tell the differences between
//      Data Sinks.  The methods dataSinkID() and parameters() are used to 
//      identify Data sinks. dataSinkID() returns a std::string that identifies 
//      the data sink, E.g a DataSinkController that writes to a file would 
//      return the files name. parameters() returns a std::string that describes 
//      any additional information that is needed to distinguish a data sink. 
//      E.g. if the data sink is a data base, the dataSinkID() may be the 
//      name of the database, "CLEO data", and parameters() may be a selection 
//      criteria, "On 4S".
//
//      FrameStorer also need to know whether a sink stores Records serially.
//       The method 'DABoolean mustSequentiallyStore( )' must
//       return true if the DataSinkController must write Records in 
//       sequential (time) order and false if it may write them out of order.
//       
//
//    Create the necessary ProxyStorer
//      FrameStorer asks the DataSinkController for the ProxyStorer
//      associated with that Controller through the method 
//      'proxyStorer()'.  The first time that method is called, it calls
//      'createProxyStorer()' to create the correct ProxyStorer
//      which is then managed by the base class.
//      NOTE: the created ProxyStorer is also used to determine the
//            "potentialRecordsToStore" by calling the ProxyStorer 
//            method 'Stream::Set stores( void )'.
//
// Author:      Chris D. Jones
// Created:     Sun May 25 15:02:58 EDT 1997
// $Id: DataSinkController.h,v 1.4 1997/09/18 21:13:16 cdj Exp $
//
// Revision history
//
// $Log: DataSinkController.h,v $
// Revision 1.4  1997/09/18 21:13:16  cdj
// Changed Boolean to DABoolean
//
// Revision 1.3  1997/08/16 17:45:38  cdj
// Modified to work with Proxies
//
// Revision 1.2  1997/07/11 06:20:14  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/05/30 15:41:37  cdj
// First submission
//


// system include files

// user include files
#include "DataHandler/Stream.h"


// forward declarations
class ProxyStorer;

class DataSinkController
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      enum InitializationStatus { kInitNoError = 0,
				  kInitInvalidStopsForSink,
				  kInitSinkInaccessible,
				  kInitBadParameters,
				  kInitUnknownError 
      };

      // Constructors and destructor
      DataSinkController( void );
      virtual ~DataSinkController();

      // member functions
      DABoolean setRecordsToStore( const Stream::Set& iStore );
      void clearRecordsToStore( void );

      // const member functions
      DataSinkController::InitializationStatus
        initializationStatus( void ) const;

      const Stream::Set
              potentialRecordsToStore( void ) const;
      const Stream::Set& recordsToStore( void ) const;

      virtual DABoolean mustSequentiallyStore( void ) const = 0;

      ProxyStorer*  proxyStorer( void ) const;

      virtual std::string dataSinkID( void ) const = 0;
      virtual std::string parameters( void ) const = 0;

      // static member functions

   protected:
      // protected member functions
      void setInitializationStatus(
	 DataSinkController::InitializationStatus iStatus );

      // protected const member functions

      virtual ProxyStorer* createProxyStorer( void ) const = 0;

   private:
      // Constructors and destructor
      DataSinkController( const DataSinkController& );

      // assignment operator(s)
      const DataSinkController& operator=( const DataSinkController& );

      // private member functions

      // private const member functions

      // data members
      Stream::Set& m_storeStreams;
      InitializationStatus m_initializationStatus;

      ProxyStorer* m_proxyStorer;
      // static data members

};

// inline function definitions

#endif /* DATASTORAGE_DATASINKCONTROLLER_H */
