#if !defined(PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMTEMPLATE_CC)
#define PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMTEMPLATE_CC
// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSUnpackingSourceStreamTemplate
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Apr 14 15:09:52 EDT 2003
// $Id$
//
// Revision history
//
// $Log$

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSUnpackingSourceStreamTemplate.h"


//
// constants, enums and typedefs
//

//static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSUnpackingSourceStreamTemplate" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//PDSUnpackingSourceStreamTemplate::PDSUnpackingSourceStreamTemplate()
//{
//}

// PDSUnpackingSourceStreamTemplate::PDSUnpackingSourceStreamTemplate( const PDSUnpackingSourceStreamTemplate& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//PDSUnpackingSourceStreamTemplate::~PDSUnpackingSourceStreamTemplate()
//{
//}

//
// assignment operators
//
// const PDSUnpackingSourceStreamTemplate& PDSUnpackingSourceStreamTemplate::operator=( const PDSUnpackingSourceStreamTemplate& rhs )
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
template <class T, class U >
static
inline
DABoolean matchType(const T*, U&) {
   return false;
}

template <class T>
static
inline
DABoolean matchType(constT*, T& ) {
   return true;
}

#define UNPACK_DATA \
typename const T::value_type* dummy; \
if( matchType( dummy, oData ) ) { \
 oData = m_packer.unpack(*startWord(), *(startWord()+1), startBit()); \
} else { throw DAException("attempting to read back incorrect type"); } \
advanceStartWordIfNeeded(); 




template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( char& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( short& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( int& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( long& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( unsigned char& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( unsigned short& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( unsigned int& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( unsigned long& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( float& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( double& oData )
{
   UNPACK_DATA
   return gotoNext();
}

template<class T>
SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( string& oData )
{
   throw DAException("asked to read back a string instead of correct type");
   return gotoNext();
}

SMSourceStream& 
PDSUnpackingSourceStreamTemplate<T>::operator>>( const SMMakeContentsBase& iContents )
{
   throw DAException("asked to read back a container instead of a simple type");
   return gotoNext();
}

void 
PDSUnpackingSourceStreamTemplate<T>::beginObject( const TypeTag& iType )
{
//   m_unpackerHolder = UnpackerHolder( (*(m_typePackingMap->find( iType ))).second );
}

void 
PDSUnpackingSourceStreamTemplate<T>::endObject()
{
}

//
// const member functions
//

//
// static member functions
//
#endif /* PACKEDDATASTREAMSDELIVERY_PDSUNPACKINGSOURCESTREAMTEMPLATE_CC */

