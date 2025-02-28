// -*- C++ -*-
//
// Package:     <PackedDataStreamsStorage>
// Module:      PDSSchemaProbeSinkStream
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 15:58:55 EDT 2000
// $Id: PDSSchemaProbeSinkStream.cc,v 1.6 2002/04/03 19:14:36 cleo3 Exp $
//
// Revision history
//
// $Log: PDSSchemaProbeSinkStream.cc,v $
// Revision 1.6  2002/04/03 19:14:36  cleo3
// worked around a bug in CC 6.02
//
// Revision 1.5  2001/06/08 13:53:23  cdj
// can now handle storing containers of strings
//
// Revision 1.4  2001/04/10 19:49:29  cdj
// can now store strings
//
// Revision 1.3  2000/11/28 02:19:05  cdj
// added unsigned char to list of types that can be 'non-packed'
//
// Revision 1.2  2000/10/02 20:46:49  cdj
// now compiles and links using cxx
//
// Revision 1.1.1.1  2000/09/29 17:49:41  cdj
// imported
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsStorage/PDSSchemaProbeSinkStream.h"

#include "PackedDataStreamsFormat/PDSIntNoPackPacker.h"
#include "PackedDataStreamsFormat/PDSFloatNoPackPacker.h"
#include "PackedDataStreamsFormat/PDSFixedPacker.h"
#include "PackedDataStreamsFormat/PDSFixedTrueZeroPacker.h"
#include "PackedDataStreamsFormat/PDSFractionalPacker.h"
#include "PackedDataStreamsFormat/PDSStringPacker.h"

#include "PackedDataStreamsFormat/PDSContainerNoPackPacker.h"
#include "PackedDataStreamsFormat/PDSContainerPackedPacker.h"

#include "StorageManagement/SMContentsBase.h"
#include "DataHandler/RecordMethods.h"
// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "PackedDataStreamsStorage.PDSSchemaProbeSinkStream" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSSchemaProbeSinkStream.cc,v 1.6 2002/04/03 19:14:36 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
PDSSchemaProbeSinkStream::PDSSchemaProbeSinkStream() :
   m_packers( 0 )
{
}

// PDSSchemaProbeSinkStream::PDSSchemaProbeSinkStream( const PDSSchemaProbeSinkStream& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSSchemaProbeSinkStream::~PDSSchemaProbeSinkStream()
{
}

//
// assignment operators
//
// const PDSSchemaProbeSinkStream& PDSSchemaProbeSinkStream::operator=( const PDSSchemaProbeSinkStream& rhs )
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
static
PDSPackerBase*
createNoPacker( const SMPackInfo& iPackInfo, float* iData )
{
   return new PDSFloatNoPackPacker<float>(iPackInfo);
}

static
PDSPackerBase*
createNoPacker( const SMPackInfo& iPackInfo, double* iData )
{
   return new PDSFloatNoPackPacker<double>(iPackInfo);
}

static
PDSPackerBase*
createNoPacker( const SMPackInfo& iPackInfo, string* iData ) 
{
   //We do not support compression for strings
   return new PDSStringPacker(false);
}

template <class T>
static
inline
PDSPackerBase*
createNoPacker( const SMPackInfo& iPackInfo, T* iData)
{
   return new PDSIntNoPackPacker<T>(iPackInfo);
}

template <class T>
static
inline
PDSPackerBase*
createFixedPacker( const SMPackInfo& iPackInfo, T* iData)
{
   PDSPackerBase* pReturnValue;

   SMPackInfoFixedTemplate<T> packInfo( iPackInfo );

   if( packInfo.min() < 0 && packInfo.max() > 0 ) {
      pReturnValue = new PDSFixedTrueZeroPacker<T>(packInfo);
   } else {
      pReturnValue = new PDSFixedPacker<T>(packInfo);
   }
   return pReturnValue;
}

template <class T>
static
inline
PDSPackerBase*
createFractionalPacker( const SMPackInfo& iPackInfo, T* iData)
{
   return new PDSFractionalPacker<T>( SMPackInfoFractionalTemplate<T>(iPackInfo) );
}

static
PDSPackerBase*
createPackInfo( const SMPackInfo& iPackInfo, const string* iData ) 
{
   //We do not support compression for strings
   return new PDSStringPacker(false);
}

//Bug under Solaris CC v6.02 requires specialization
static
inline
PDSPackerBase*
createPackInfo( const SMPackInfo& iPackInfo, double* iData)
{
   PDSPackerBase* pReturnType;

   switch( iPackInfo.strategy() )
   {
      case SMPackInfo::kNoPacking:
        pReturnType = createNoPacker( iPackInfo, iData );
	break;
      case SMPackInfo::kFixed:
        pReturnType = createFixedPacker( iPackInfo, iData );
	break;
      case SMPackInfo::kFractional:
        pReturnType = createFractionalPacker( iPackInfo, iData );
	break;
   }
   return pReturnType;
}

static
inline
PDSPackerBase*
createPackInfo( const SMPackInfo& iPackInfo, float* iData)
{
   PDSPackerBase* pReturnType;

   switch( iPackInfo.strategy() )
   {
      case SMPackInfo::kNoPacking:
        pReturnType = createNoPacker( iPackInfo, iData );
	break;
      case SMPackInfo::kFixed:
        pReturnType = createFixedPacker( iPackInfo, iData );
	break;
      case SMPackInfo::kFractional:
        pReturnType = createFractionalPacker( iPackInfo, iData );
	break;
   }
   return pReturnType;
}

template <class T>
static
inline
PDSPackerBase*
createPackInfo( const SMPackInfo& iPackInfo, T* iData)
{
   PDSPackerBase* pReturnType;

   switch( iPackInfo.strategy() )
   {
      case SMPackInfo::kNoPacking:
        pReturnType = createNoPacker( iPackInfo, iData );
	break;
      case SMPackInfo::kFixed:
        pReturnType = createFixedPacker( iPackInfo, iData );
	break;
      case SMPackInfo::kFractional:
        pReturnType = createFractionalPacker( iPackInfo, iData );
	break;
   }
   return pReturnType;
}


#define CREATE_IF_TYPE(_compression_, _type_) \
if( iPackInfo.fieldType() == SMPackInfo ## _compression_ ## Template< _type_ >::classFieldType() ) { _type_* temp = 0; return create ## _compression_ ## Packer( iPackInfo, temp ); }

static
PDSPackerBase*
createContainedFixedPacker( const SMPackInfo& iPackInfo )
{
   CREATE_IF_TYPE(Fixed, char);
   CREATE_IF_TYPE(Fixed, short);
   CREATE_IF_TYPE(Fixed, int);
   CREATE_IF_TYPE(Fixed, long);

   CREATE_IF_TYPE(Fixed, unsigned char);
   CREATE_IF_TYPE(Fixed, unsigned short);
   CREATE_IF_TYPE(Fixed, unsigned int);
   CREATE_IF_TYPE(Fixed, unsigned long);

   CREATE_IF_TYPE(Fixed, float);
   CREATE_IF_TYPE(Fixed, double);

   assert(false);
   return 0;
}

static
PDSPackerBase*
createContainedFractionalPacker( const SMPackInfo& iPackInfo )
{
   CREATE_IF_TYPE(Fractional, char);
   CREATE_IF_TYPE(Fractional, short);
   CREATE_IF_TYPE(Fractional, int);
   CREATE_IF_TYPE(Fractional, long);

   CREATE_IF_TYPE(Fractional, unsigned char);
   CREATE_IF_TYPE(Fractional, unsigned short);
   CREATE_IF_TYPE(Fractional, unsigned int);
   CREATE_IF_TYPE(Fractional, unsigned long);

   CREATE_IF_TYPE(Fractional, float);
   CREATE_IF_TYPE(Fractional, double);

   assert(false);
   return 0;
}

#define CREATE_NOPACK_IF_TYPE(_type_)\
if( iData.typeTag() == RecordMethods< _type_ >::makeKey("","").type() ) { _type_* temp = 0; return createNoPacker( iPackInfo, temp ); }
static
PDSPackerBase*
createContainedNoPackPacker( const SMPackInfo& iPackInfo, const SMContentsBase& iData )
{
   //CREATE_NOPACK_IF_TYPE( char);
   //CREATE_NOPACK_IF_TYPE( short);
   CREATE_NOPACK_IF_TYPE( int);
   //CREATE_NOPACK_IF_TYPE( long);

   CREATE_NOPACK_IF_TYPE( unsigned char);
   CREATE_NOPACK_IF_TYPE( unsigned short);
   CREATE_NOPACK_IF_TYPE( unsigned int);
   //CREATE_NOPACK_IF_TYPE( unsigned long);

   CREATE_NOPACK_IF_TYPE( float);
   CREATE_NOPACK_IF_TYPE( double);

   CREATE_NOPACK_IF_TYPE( string);

   assert(false);
   return 0;
}


static
PDSPackerBase*
createContainerPackInfo( const SMPackInfo& iPackInfo, const SMContentsBase& iData)
{
   PDSPackerBase* pReturnType;

   switch( iPackInfo.strategy() )
   {
      case SMPackInfo::kNoPacking:
        if( iData.strategy() == SMContentsBase::kBuiltin ) {
	   pReturnType = new PDSContainerPackedPacker(
	      createContainedNoPackPacker(iPackInfo, iData) );
	} else {
	   pReturnType = new PDSContainerNoPackPacker;
	}
	break;
      case SMPackInfo::kFixed:
        pReturnType = new PDSContainerPackedPacker( 
	   createContainedFixedPacker( iPackInfo ) );
	break;
      case SMPackInfo::kFractional:
        pReturnType = new PDSContainerPackedPacker( 
	   createContainedFractionalPacker( iPackInfo ) );
	break;
   }

   return pReturnType;

}


void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, char iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, short iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, int iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, long iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}

void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, unsigned char iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, unsigned short iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, unsigned int iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, unsigned long iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, float iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, double iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}
void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, const string& iData )
{
   m_packers->push_back(createPackInfo(packInfo(), &iData ) );
}

void 
PDSSchemaProbeSinkStream::put( const char * iFieldName, 
			      const SMContentsBase& iData )
{
   m_packers->push_back( createContainerPackInfo(packInfo(), iData ) );

   if( iData.strategy() != SMContentsBase::kBuiltin ) {
      m_subtypes.insert( iData.typeTag() );
   }
}

void 
PDSSchemaProbeSinkStream::beginObject( const TypeTag& )
{
}

void 
PDSSchemaProbeSinkStream::endObject()
{
}

void 
PDSSchemaProbeSinkStream::clearSubtypes()
{
   m_subtypes.erase(m_subtypes.begin(), m_subtypes.end() );
}
//
// const member functions
//

//
// static member functions
//
