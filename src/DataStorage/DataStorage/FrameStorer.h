#if !defined(DATASTORAGE_FRAMESTORER_H)
#define DATASTORAGE_FRAMESTORER_H
// -*- C++ -*-
//
// Package:     DataStorage
// Module:      FrameStorer
// 
// Description: Handles the storing of data to multiple sinks.
//
// Usage:
//
// SETUP THE STORAGE SYSTEM
//
//    FrameStorer FS;
//
//    //Tell FrameStorer what data sinks to use.
//    // FrameStorer uses the DataSinkBinder to create the appropriate
//    //  DataSinkController to use with the data sink you specify.
//    // You also specify what Records you want to write to the DataSink
//
//    Stream::Set writeStreams;
//    writeStreams.insert( Stream::kEvent );
//    My1SinkBinder my1Binder( writeStreams );
//
//    writeStreams.insert( Stream::kBeginRun );
//    AsciiSinkBinder asciiBinder("myskim.asc", writeStreams );
//
//    FrameStorer::AddSinkStatus status;
//    // addSink returns FrameStorer::kAddSinkNoError if the data sink
//    // was openned sucessfully.
//    // To determine what caused a failure, look at status.
//
//    //Write to the user's sink
//    if( FrameStorer::kAddSinkNoError !=
//           (status = FS.addSink(my1Binder ) ) ){
//       exit(1);
//    }
//
//    //Write to the ascii file
//    if( FrameStorer::kAddSinkNoError !=
//           (status = FS.addSink(asciiBinder ) ) ){
//       exit(1);
//    } 
//
//
// SAVING A FRAME
//
//    //The Storage system is designed to save all Proxies in the Stopped
//    // Stream's Record that have been "touched".  Proxys can be touched
//    // either explicitly or they are automatically touched when the  
//    // contents of a Proxy are calculated by an algorithmic provider.
//
//    Frame& frame = frameDeliverer.currentFrame();
//
//    //store() returns FrameStorer::kStoreFrameNoError if the Frame was
//    // stored correctly
//
//    FrameStorer::StoreFrameStatus storeStatus = FS.store( frame );
//
// SEQUENTIAL STORERS
//    Some DataSinks can only store Records in series.  Therefore to 
//    guarantee that these DataSinks will be written in sequential order
//    Job Control should check the mustSequentiallyStore() method after
//    setting up all the DataSinks.  If this method is 'true' than 
//    Job Control should call FrameDeliverer::setForcedSequentiallAccess()
//    with 'true'.  Failure to do this may cause the DataSink to write
//    records which are out of sequence which can cause problems when that
//    DataSink is later used as a DataSource.
//
//
// Author:      Chris D. Jones
// Created:     Sun May 25 14:28:52 EDT 1997
// $Id: FrameStorer.h,v 1.9 1999/12/06 21:46:48 mkl Exp $
//
// Revision history
//
// $Log: FrameStorer.h,v $
// Revision 1.9  1999/12/06 21:46:48  mkl
// added 'contains( StreamType )' method
//
// Revision 1.8  1998/07/18 20:14:09  mkl
// move to STL macros
//
// Revision 1.7  1998/02/03 21:28:47  mkl
// switch over to STLUtility library
//
// Revision 1.6  1997/09/18 21:13:18  cdj
// Changed Boolean to DABoolean
//
// Revision 1.5  1997/08/18 18:00:11  mkl
// changed vector to list, because of problems with return type 'list<>::iterator' of function
//
// Revision 1.4  1997/08/16 17:45:39  cdj
// Modified to work with Proxies
//
// Revision 1.3  1997/07/11 06:20:16  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.2  1997/05/31 20:47:22  cdj
// 1) storeFrame now gets status from RecordStorer
// 2) can now get the actual status of a sink
//
// Revision 1.1.1.1  1997/05/30 15:41:37  cdj
// First submission
//


// system include files
#if defined(TEMPLATE_DEFAULT_ARGS_FIRST_BUG)
#include <vector>
#endif /* TEMPLATE_DEFAULT_ARGS_FIRST_BUG */
  
// user include files
#include "DataHandler/Frame.h"
#include "DataHandler/Stream.h"
#include "DataHandler/StreamSet.h"

#include "DataStorage/DataSinkDescriptor.h"

// forward declarations
class DataSinkBinder;
class DataSinkController;
class RecordStorer;
class DataSinkDescriptor;

#include "STLUtility/fwd_multimap.h"
#include "STLUtility/fwd_vector.h"
#include <vector>

#if !defined(_framestorer_statusofsinks_)
#  define _framestorer_statusofsinks_ STL_MULTIMAP( FrameStorer::SinkStatus, DataSinkDescriptor )
#  define _framestorer_sinkdescriptors_ STL_VECTOR( DataSinkDescriptor )
#  define _framestorer_sinkcontrollers_ STL_VECTOR( DataSinkController* )
#  define _framestorer_recordstorers_ STL_MAP( Stream::Type , RecordStorer* )
#endif /* _framestorer_sinkdescriptors_ */

class FrameStorer
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      enum AddSinkStatus  { kAddSinkNoError = 0,
			    kAddSinkBinderFailedToMakeController,
			    kAddSinkInvalidStopsForSink ,
			    kAddSinkSinkInaccessible,
			    kAddSinkBadParameters,
			    kAddSinkUnknownError
      };
      enum RemoveSinkStatus { kRemoveSinkNoError = 0,
			      kRemoveSinkNoMatchingSink
      };

      enum SinkStatus { kSinkNoError = 0,
			kSinkProblemWithSink,
			kSinkUnknownSinkError,
			kSinkUnknownError
      };

      enum StoreFrameStatus { kStoreFrameNoError=0,
			      kStoreFrameWarningNoSinkForRecord,
			      kStoreFrameProblemWithASink,
			      kStoreFrameUnknownSinkError,
			      kStoreFrameUnknownRecordError,
			      kStoreFrameUnknownError
      };

      // Constructors and destructor
      FrameStorer( void );
      virtual ~FrameStorer();

      // member functions
      FrameStorer::AddSinkStatus
        addSink( const DataSinkBinder& iAddSinkBinder); 
      FrameStorer::RemoveSinkStatus
        removeSink( const DataSinkDescriptor& iCloseSinkBinder);
      void removeAllSinks( void );

      StoreFrameStatus storeFrame( const Frame& iFrame);
      
      // const member functions
      _framestorer_statusofsinks_ statusOfSinks( void ) const;
      _framestorer_sinkdescriptors_ sinks( void ) const;
      DABoolean mustSequentiallyStore( void ) const;

      DABoolean contains( const Stream::Type& aStream ) const ;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      FrameStorer( const FrameStorer& );

      // assignment operator(s)
      const FrameStorer& operator=( const FrameStorer& );

      // private member functions
      void updateMustSequentiallyStore( void );
      _framestorer_sinkcontrollers_::iterator 
      findDataSinkController( const DataSinkDescriptor& iBinder );

      // private const member functions

      // data members
      _framestorer_recordstorers_& m_streamToRecordStorerMap;
      _framestorer_sinkcontrollers_& m_dataSinkControllers;

      DABoolean m_mustSequentiallyStore;
      // static data members

};

// inline function definitions

#endif /* DATASTORAGE_FRAMESTORER_H */
