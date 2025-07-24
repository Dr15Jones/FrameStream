#if !defined(STORAGEMANAGEMENT_SMPROXYWRITER_CC)
#define STORAGEMANAGEMENT_SMPROXYWRITER_CC
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMProxyWriter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon May 24 17:26:44 EDT 1999
// $Id: SMProxyWriter.cc,v 1.5 2003/04/28 14:07:27 vk Exp $
//
// Revision history
//
// $Log: SMProxyWriter.cc,v $
// Revision 1.5  2003/04/28 14:07:27  vk
// Remove thrown exception in try/catch block, setup return value.
//
// Revision 1.4  2003/04/25 15:36:07  vk
// Add entry to DAExceptionStack and throw DANoProxyException when proxy is not present
//
// Revision 1.3  2000/09/26 21:58:12  cdj
// SMProxyWriter now clears its cache before trying to read new data
//
// Revision 1.2  1999/12/10 14:45:57  cdj
// catches DANoDataException
//
// Revision 1.1.1.1  1999/09/13 21:21:43  cdj
// imported package
//

#include "Experiment/Experiment.h"
#include "Experiment/report.h"

// system include files

// user include files
#include "StorageManagement/SMProxyWriter.h"
#include "DataHandler/RecordMethods.h"
#include "DAException/DANoProxyException.h"
#include "DAException/DANoDataException.h"
#include "DAException/DAExceptionStack.h"
#include "DAException/DAExceptionStackEntry.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kSMFacilityString = "StorageManagement.SMProxyWriter" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMProxyWriter.cc,v 1.5 2003/04/28 14:07:27 vk Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SMProxyWriter::SMProxyWriter()
//{
//}

// SMProxyWriter::SMProxyWriter( const SMProxyWriter& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMProxyWriter::~SMProxyWriter()
//{
//}

//
// assignment operators
//
// const SMProxyWriter& SMProxyWriter::operator=( const SMProxyWriter& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
template <class T>
DABoolean 
SMProxyWriter<T>::extractData( const DataKey& iKey,
			       const Record&  iRecord,
			       SMSinkStream&  iOStream )
{
   DABoolean returnValue = false;

   try {

      //get the proxy
      const ProxyTemplate< T >* proxy = RecordMethods<T>::extractProxy( 
	 iRecord, 
	 iKey.usage(),
	 iKey.production() );
	 
      m_data = 0;
      if( 0 != proxy ) {
         // add data key to the stack
         DAExceptionStackEntry stackEntry(iKey);
	 m_data = proxy->get( iRecord, iKey );
	 returnValue = true;
      }

   } catch( DANoDataException< T >& ) {
   }
   return returnValue;
}

//
// const member functions
//
template <class T>
void 
SMProxyWriter<T>::writeData( SMSinkStream& iOStream ) const 
{
   m_helper->store( iOStream, *m_data );
}

//
// static member functions
//

#endif /* STORAGEMANAGEMENT_SMPROXYWRITER_CC */
