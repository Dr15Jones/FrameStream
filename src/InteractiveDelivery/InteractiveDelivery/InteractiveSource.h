#if !defined(INTERACTIVEDELIVERY_INTERACTIVESOURCE_H)
#define INTERACTIVEDELIVERY_INTERACTIVESOURCE_H
// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveSource
// 
// Description: An Event Source inwhich the user sets SyncValue to produce
//
// Usage:
//    The developers of job control frameworks use this class in conjuction
//    with InteractiveSourceBinder to create "goto run event" commands.
//
//    Code example
//    //Create the Interactive Source and pass it to the binder
//    InteractiveSource intSource;
//
//    InteractiveSourceBinder intBinder( &intSource);
//    //NOTE: Binder only binds to Event stream
//
//    //Give binder to FrameDeliverer, check for errors etc.
//    ...
//
//    //Do loop until user gives appropriate run event
//    //  The only time the users request can fail is if
//    //  FrameDeliverer is in sequential access mode and
//    //  the user gave a (run, event) number that goes back in time.
//    do{
//      //Now prompt user where to go to
//      cout <<"goto run event";
//      unsigned long run, event;
//      cin >> run >> event;
//
//    //Tell the source to go there
//    }while( ! intSource.setRunEvent( run, event ));
//
//    //Now you must
//    // 1) save which sources are active
//    // 2) set InteractiveSource to be the only active source
//    // 3) ask FrameDeliverer for nextStop().  This will be where you
//    //    told it to goto
//    // 4) reset the active sources to what they were in 1)
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 12:27:23 EDT 1997
// $Id: InteractiveSource.h,v 1.6 2003/11/22 20:22:29 cdj Exp $
//
// Revision history
//
// $Log: InteractiveSource.h,v $
// Revision 1.6  2003/11/22 20:22:29  cdj
// can now specify what stream should be used
//
// Revision 1.5  1997/09/18 21:25:25  cdj
// changed Boolean to DABoolean
//
// Revision 1.4  1997/07/09 19:22:11  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/05/06 20:26:12  mkl
// got rid of runNumber(), eventNumber() methods
//
// Revision 1.2  1997/05/06 18:34:01  mkl
// replaced run, event with SyncValue
//
// Revision 1.1.1.1  1997/04/21 19:30:10  cdj
// First submission
//


// system include files

// user include files
#include "DataHandler/SyncValue.h"
#include "DataHandler/StreamType.h"

// forward declarations

class InteractiveSource
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      InteractiveSource( void );
      virtual ~InteractiveSource();

      // member functions
      void resetSyncValue( const SyncValue& syncValue );
      DABoolean setSyncValue( const SyncValue& syncValue );
      //Returns false if SyncValue not allowed (in serial access mode)

      void setStream(const StreamType& iStream );

      void setSequentialAccess( DABoolean iSetValue ); 

      // const member functions
      SyncValue syncValue( void ) const;
      const StreamType& stream() const {return m_streamType;}

      DABoolean isSequentiallyAccessing( void ) const;
      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      InteractiveSource( const InteractiveSource& );

      // assignment operator(s)
      const InteractiveSource& operator=( const InteractiveSource& );

      // private member functions

      // private const member functions

      // data members
      SyncValue m_syncValue;
      DABoolean m_isSequentiallyAccessing;
      StreamType m_streamType;

      // static data members

};

// inline function definitions

#endif /* INTERACTIVEDELIVERY_INTERACTIVESOURCE_H */
