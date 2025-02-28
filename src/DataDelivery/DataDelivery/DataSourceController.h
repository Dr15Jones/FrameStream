#if !defined(DATADELIVERY_DATASOURCECONTROLLER_H)
#define DATADELIVERY_DATASOURCECONTROLLER_H
// -*- C++ -*-
//
// Package:     DataDelivery
// Module:      DataSourceController
// 
// Description: Abstract base class for classes used to read
//              from different data sources
//
// Usage:
//    Used by FrameDeliverer to synchronize across data streams and
//     owns the ProxyDeliverer which is used to read DataFields
//     from the data source.
//
//    A DataSourceController finds and loads certain data records for one type
//     of data source.  The DataSourceController knows what types of records 
//     can be in the source (referred to as "potentialRecordsToRetrieve"). 
//     The user tells the DataSourceController which data source it should
//     use as well as any additional parameters and also tells it which of 
//     the potential record types the DataSourceController should actually 
//     find and load (these are referred to as "recordsToRetrieve").
//     The user also tells the DataSourceController which of its Streams are
//     Active. 
//
//    Users do not communicate directly with DataSourceControllers.  Instead
//     they use DataSourceBinders to Bind Streams to a Data Source.  The
//     DataSourceBinder is given to FrameDeliverer and FrameDeliverer asks
//     the DataSourceBinder to create the necessary DataSourceController.
//
//    Since users never directly use DataSourceControllers, we will not discuss
//     how to use a DataSourceController.  Instead we will discuss how to
//     write a DataSourceController.
//
//    A DataSourceController must perform the following tasks
//      1) Initialize the data source
//      2) Be able to describe its data source
//      3) create the necessary ProxyDeliverer
//      4) control reading Records from the source
//
//    Initializing the Data Source
//      Data sources are initialized in the constructor.  E.g. if the
//       data source is a file, that file is opened in the constructor.
//       In addition you must call
//       a) 'setRecordsToRetrieve(...)' with the set of Streams the user 
//          wants read from this source (E.g. Events from a roar file).  
//       b) 'setIsSequentiallyAccessing(DABoolean )' with true if the 
//          DataSourceController will read Records in sequential (time) order 
//          and false if it may read them out of order.
//       c) 'setInitializationStatus(...)' with the appropriate value if
//          there was a problem. (If you do not call it, it will default to
//          no problem).
//
//    Describing the Data Source
//      FrameDeliverer needs to be able to tell the differences between
//      Data Sources.  The methods dataSourceID() and parameters() are used to 
//      identify Data sources. dataSourceID() returns a string that identifies 
//      the data source, E.g a DataSourceController that reads a file would 
//      return the files name. parameters() returns a string that describes 
//      any additional information that is needed to distinguish a data source. 
//      E.g. if the data source is a data base, the dataSourceID() may be the 
//      name of the database, "CLEO data", and parameters() may be a selection 
//      criteria, "On 4S".
//
//      FrameDeliverer also need to know whether a source can be random accessed.
//      This is done through the method 'DABoolean canRandomAccess( void ) const'.
//      If the DataSourceController can randomly access the source this method
//      returns true, else it returns false.
//       
//
//    Create the necessary ProxyDeliverer
//      FrameDeliverer asks the DataSourceController for the ProxyDeliverer
//      associated with that Controller through the method 
//      'proxyDeliverer()'.  The first time that method is called, it calls
//      'createProxyDeliverer()' to create the correct ProxyDeliverer
//      which is then managed by the base class.
//      NOTE: the created ProxyDeliverer is also used to determine the
//            "potentialRecordsToRetrieve" by calling the ProxyDeliverer 
//            method 'Stream::Set supplies( void )'.
//
//
//    Control Reading Records from the Source
//     FrameDeliverer uses the DataSourceController to read Records from the
//     source.  To do this, the FrameDeliverer needs to tell the 
//     DataSourceController to
//       a) read its records in sequential order if necessary
//       b) find the next Record in the source
//       c) advance the source to a new 'time'
//
//     Read in Sequential Order
//       There are times when FrameDeliverer must force a DataSourceController
//       to read its Records in sequential (time) order.  To do this,
//       FrameDeliverer calls setForcedSequentialAccess( true ).  This then calls
//       the virtual method implementSetForcedSequentialAccess( true ).
//       If sequential access is not required, FrameDeliverer calls
//       setForcedSequentialAccess( false ) which in turn calls 
//       implementSetForcedSequentialAccess( false ).  Therefore if a 
//       DataSourceController needs to do something special to read sequentially
//       that code should be called from implementSetForcedSequentialAccess(...).
//       NOTE: In the case where FrameDeliverer is not forcing the controller
//       to read in sequential order does NOT mean that the controller can't
//       read them in sequential order.  If a DataSourceController is NOT
//       reading in sequential order then it must call setIsSequentiallyAccessing
//       with false.
//
//     Find Next Record
//        FrameDeliverer needs to know the next Record that will be retrieved
//        from an Active source when FrameDeliverer is synchronizing the
//        sources and there are several Active sources.  To do this it calls
//        'DataSourceController::SearchStatus 
//            findNextRecord(SyncValue& oSyncValueOfNextRecord,
//                           Stream::Type& oRecordTypeOfNextRecord)'
//         The return value is
//           A status flag that explains what (if anything) went wrong
//         The arguments are
//           SyncValue& sync value of the next Record
//           Stream::Type& the Stream from which the next Record comes
//
//        NOTE: Subsequent calls to findNextRecord MUST return the same values
//        (See Special Case for further requirements on findNextRecord.)
// 
//        The meaning of 'next' is different for random and serial access sources
//           a) For a random access data source findNextRecord will always be 
//              able to find the next Record in an Active Stream immediately.  
//           b) For a serial access data source findNextRecord should
//              only return the SyncValue and Stream::Type of the next record 
//              in the source that is of type recordsToRetrieve and NOT of 
//              the next Record from an Active Stream (unless they are the 
//              same Record). This is necessary to avoid the problem when a 
//              serial access source 
//              i)  is supplying multiple streams
//              ii) some but not all of the streams are Active
//              iii)is not the only source with active streams
//              having findNextRecord read through the data source until
//              it found an Active Stream record to Stop at could cause the
//              source to have read to far
//              Ex : two sources 
//                  1) Roar file (my.rp) 
//                       RecordsToRetrieve: BeginRun Event
//                       RecordsToStopOn :  BeginRun
//                  2) User data
//                       RecordsToRetrieve: Event
//                       RecordsToStopOn :  Event
//                  The Records have the following time order
//                  my.rp : BeginRun   1     6
//                        : Event        2345
//                  user  : Event          4
//                  After initially stopping at BeginRun(1) the next
//                  stop should be at Event(4).  If findNextRecord caused
//                  my.rp to jump directly to its next requested Record
//                  it would find BeginRun(6) and since it is serially
//                  accessing, it would have loaded Event(5) into its buffer
//                  and subsequently be unable to get Event(4) which is what
//                  it should have. 
//
//     Advancing a Source
//        A data source can be advanced in two ways
//        1) by going to the next Record
//        2) synchronizing the source to a SyncValue
//
//        Goto Next Record
//           Ex: say we want the DataSourceController driverSource to advance
//               to its next record
//           Code:
//                DataSourceController::SearchStatus searchStatus;
//                searchStatus = driverSource.gotoNextRecord();
//
//           This moves the data source to the record that would have been
//           found if findNextRecord( ... ) had been called. The return value is
//           identical to the hypothesized findNextRecord( ... ) call. 
//           The value of currentSyncValue() must match the SyncValue 
//           of that Record.
//           The value of currentStop() must be the record type of the
//           Record which we have gone to.
//
//        Synchronize the Source
//           To synchronize a source the internal pointer to the location 
//           being read must be advanced to a new SyncValue.
//           Once at a new SyncValue it is possible to read the Records of 
//           a type that match recordsToRetrieve which have SyncValues closest 
//           to but not greater than the data sources SyncValue.
//
//        2) Ex: (Continuing the example) say we want to synchronize user info
//             (that is being read by a user made DataSourceController named
//              userDataSynch ) with the current record in driverSource.
//           Code:
//             DataSourceController::SyncStatus syncStatus
//             if( DataSourceController::kSyncNoError != 
//                  userDataSynch.synchronizeSource( 
//                              driverSource.currentSyncValue() ) ){
//                //Things were able to synchronize
//             } else {
//                //Something went wrong
//                // checking syncStatus
//             }
//        Once synchronizeSource() is finished, the value of 
//        currentSyncValue() must be the same as the syncValue
//        given to synchronizeSource().  The value of currentStop()
//        must be the record type of the recordsToRetrieve whose 
//        synchronization value lies closest to the value given to 
//        synchronizeSource(). 
//
//     Changing Active Streams
//        Since knowing what active streams are being read by a 
//        DataSourceController is important when determining the "next"
//        Record, we provide a call back function for when the Active
//        Streams being read by a DataSourceController is changed.  
//        This allows a DataSourceController to do any optimizations that
//        might be necessary. The method is 
//                 'void callWhenActiveStreamsChange( void )'.  
//        The default implementation of this method does nothing.
//
//    Special Case: Source containing different Record types where several
//                  Records can have the same SyncValue
//
//     Example: All of the calibration and alignment Records are stored in 
//              the same database.  Also, some of these Records may change
//              at the SyncValue of a BeginRun Record (i.e. the Records 
//              may change at a Run boundary).  
//
//     Problem: Since all of these Records occur at the same SyncValue, 
//              what is the order the Records should be in when
//              find/gotoNextRecord is called and what should the current
//              Record be when asked to Synchronize at that SyncValue?
//
//     Answer:
//       Handling find/gotoNextRecord
//        If the next Record is at a new SyncValue and at that new SyncValue
//        there are several Record of different Types then find/gotoNextRecord
//        must at least find/goto the Record at that SyncValue with the 
//        highest priority.  Use the class StreamPriorityGreater to order the
//        Streams.  If possible, find/gotoNextRecord should return the
//        Record from the Active Stream with the highest priority, but this
//        is not a requirement.
//        Example: Say we have a Source that serves the following Records
//                 GeomRecord    (Perfectly aligned detector geometry)
//                 DCAlignRecord (Drift chamber alignment info)
//                 DCCalRecord   (Drift chamber calibration info)
//
//          Where the Streams are listed in the order of priorty (i.e.
//          GeomRecord has highest priority and DCCalRecord the lowest).
//          If the source is asked to find/gotoNextRecord and this will
//          goto a new SyncValue in which all three of these Records occur,
//          then the Source should find/goto GeomRecord.
//
//        If the Source has already Stopped/Synchronized on a Record at a
//        SyncValue where there are several Records, then find/gotoNextRecord
//        should find/goto the Record with the next highest priority
//        (compared to the Record the Source is already at).
//        Example: Continuing the previous example, say that after having
//          the source goto the GeomRecord, the Controller is asked to
//          find the next Record.  It should return DCAlignRecord.
//
//       Handling synchronizeSource
//        If the synchronizeSource call will move the Source to a new
//        SyncValue where there are several Records of different Type then
//        the Source must make the Record from the highest priority Stream 
//        the current Record for that source.  Additionally, the Source
//        must be able to read in all data associated with ALL Records 
//        at that SyncValue.  This has special meaning for a serial source,
//        since you must read in ALL Records that have the SyncValue you are
//        synchronizing to but the last Record you read in may not be the
//        Record the controller uses as it's current Record.
//        Example: (Continuing the above example) Say the source is to goto
//          a new SyncValue where all three Records exist, then the Controller
//          should set currentStop to GeomRecord but if requested, it must
//          be able to read data from the DCAlignRecord and DCCalRecord
//          which are at that SyncValue.
//
//        If the synchronizeSource call ask the source to synchronize to
//        a SyncValue that the source is already at, then the Controller
//        should do nothing.
//        Example: (Continuing the above example) Say that after
//          synchronizing the Controller is asked to gotoNextRecord and
//          this moves the Source to DCAlignRecord.  Now say the Controller
//          is told to synchronizeSource to that exact same SyncValue then
//          the Controller should do nothing.  In particular the currentStop
//          must remain at DCAlignRecord. 
//
// Invariants:
//    A random access data source must be able to access data sequentially
//     if setForcedSequentialAccess( true ).
//    When implementSetForcedSequentialAccess is called the data source
//     must inform DataSourceController whether the records will be retrieved
//     sequentially even if sequential access is not required
//    A call to findNextRecord() and then to gotoNextRecord() MUST cause 
//     the record found by findNextRecord to be set up to be able to read.
//
// Author:      Chris D Jones
// Created:     Wed Mar 12 12:28:59 EST 1997
// $Id: DataSourceController.h,v 1.9 1997/09/18 21:07:13 cdj Exp $
//
// Revision history
//
// $Log: DataSourceController.h,v $
// Revision 1.9  1997/09/18 21:07:13  cdj
// changed Boolean to DABoolean
//
// Revision 1.8  1997/08/06 16:17:40  sjp
// Changed to use ProxyDeliverer
//
// Revision 1.7  1997/07/25 23:24:31  cdj
// Modified to work with ChainSourceController
//
// Revision 1.6  1997/07/09 18:00:55  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.5  1997/06/29 20:06:21  cdj
// Updated documentation to explain how to handle the case where a source can
// have multiple Records at the same SyncValue.
//
// Revision 1.4  1997/05/02 19:56:09  cdj
// 1) now knows about Active Streams
// 2) now base class manages ProxyDeliverer
// 3) simplified some method interfaces
// 4) moved some implementations into the base class
// 5) improved documentation
//
// Revision 1.3  1997/03/20 22:21:03  cdj
// Extensive change to interface
// 1) Added better error reporting on findNextRecord, gotoNextRecord and
//    synchronizeSource
// 2) Replaced isSourceFine() with initializationStatus()
// 3) Added methods needed for sequential access control
//
// Revision 1.2  1997/03/19 22:52:06  sjp
// Added required forward declaration
//
// Revision 1.1  1997/03/13 21:51:43  cdj
// First submission.
// NOTE: No compilation has been attempted on this file so syntax errors are
// possible/likely.
//


// system include files

// user include files
#include "DataHandler/SyncValue.h"
#include "DataHandler/Stream.h"


// forward declarations
class ProxyDeliverer ;

// class definition
class DataSourceController
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      enum InitializationStatus { kInitNoError = 0,
				  kInitInvalidStopsForSource,
				  kInitSourceInaccessible,
				  kInitBadParameters,
				  kInitUnknownError 
      };

      enum SearchStatus { kSearchNoError = 0,
			  kSearchEndOfSource,
			  kSearchProblemWithSource,
			  kSearchUnknownError
      };
      enum SyncStatus { kSyncNoError = 0,
			kSyncWarningAtEndOfSource,
			kSyncFailedToSync,
			kSyncProblemWithSource,
			kSyncUnknownError
      };

      // Constructors and destructor
      DataSourceController( void );
      //The instance does not own the Deliverer, this construct is
      // used when chaining source controllers
      DataSourceController( ProxyDeliverer* iDeliverer );
      virtual ~DataSourceController();

      // member functions
      virtual DataSourceController::SyncStatus 
           synchronizeSource( const SyncValue& iSyncTo )= 0;

      virtual DataSourceController::SearchStatus
               findNextRecord(SyncValue& oSyncValueOfNextRecord,
			      Stream::Type& oRecordTypeOfNextRecord ) =0;

      virtual DataSourceController::SearchStatus 
               gotoNextRecord( void ) = 0;

      DABoolean setRecordsToRetrieve( 
	         const Stream::Set& iRetrieve );
      void clearRecordsToRetrieve( void );

      DABoolean setActiveStreams( const Stream::Set& iActive );
      void clearActiveStreams( void );

      void setForcedSequentialAccess( DABoolean iFlag );

      // const member functions
      const Stream::Set
              potentialRecordsToRetrieve( void ) const;
      const Stream::Set& recordsToRetrieve( void ) const;

      const Stream::Set& activeStreams( void ) const;

      virtual DABoolean canRandomAccess( void ) const = 0;
      DABoolean isSequentiallyAccessing( void ) const;
      DABoolean forcedSequentialAccess( void ) const;

      const SyncValue& currentSyncValue( void ) const;

      const Stream::Type& currentStop( void ) const;

      InitializationStatus initializationStatus( void ) const;

      ProxyDeliverer*  proxyDeliverer( void ) const;

      virtual string dataSourceID( void ) const = 0;
      virtual string parameters( void ) const = 0;

      // static member functions

   protected:
      // protected member functions
      void setSyncValue( const SyncValue& iSynch) ;
      void setCurrentStop( const Stream::Type& iStop );
      void setInitializationStatus( 
	              DataSourceController::InitializationStatus iStatus );
      void setIsSequentiallyAccessing( DABoolean iFlag );

      virtual void implementSetForcedSequentialAccess( DABoolean iFlag ) = 0;
      virtual void callWhenActiveStreamsChange( void );

      // protected const member functions
      virtual ProxyDeliverer* createProxyDeliverer( void ) const = 0;

   private:
      // Constructors and destructor
      DataSourceController( const DataSourceController& );

      // assignment operator(s)
      const DataSourceController& operator=( const DataSourceController& );

      // private member functions

      // private const member functions

      // data members
      SyncValue m_syncValue;
      Stream::Type m_currentStop;
      Stream::Set& m_readStreams;
      Stream::Set& m_activeStreams;

      InitializationStatus m_initializationStatus;
      DABoolean m_forcedSequentialAccess;
      DABoolean m_isSequentiallyAccessing;
      
      ProxyDeliverer* m_proxyDeliverer;
      DABoolean m_ownsDeliverer;
      // static data members

};

// inline function definitions

#endif /* DATADELIVERY_DATASOURCECONTROLLER_H */
