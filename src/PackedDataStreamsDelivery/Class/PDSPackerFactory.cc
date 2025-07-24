// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSPackerFactory
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Tue Sep 19 14:21:47 EDT 2000
// $Id: PDSPackerFactory.cc,v 1.4 2002/08/09 18:03:55 cdj Exp $
//
// Revision history
//
// $Log: PDSPackerFactory.cc,v $
// Revision 1.4  2002/08/09 18:03:55  cdj
// removed inappropriate use of reinterpret_cast
//
// Revision 1.3  2002/03/17 16:08:15  cdj
// use optimized version of fractional packing
//
// Revision 1.2  2001/04/10 19:48:09  cdj
// can now store strings
//
// Revision 1.1.1.1  2000/09/29 17:48:05  cdj
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
#include <string.h>

// user include files
//#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSPackerFactory.h"
#include "PackedDataStreamsFormat/PDSIntNoPackPacker.h"
#include "PackedDataStreamsFormat/PDSFloatNoPackPacker.h"
#include "PackedDataStreamsFormat/PDSFixedPacker.h"
#include "PackedDataStreamsFormat/PDSFixedTrueZeroPacker.h"
#include "PackedDataStreamsFormat/PDSFractionalPacker.h"

#include "PackedDataStreamsFormat/PDSContainerNoPackPacker.h"
#include "PackedDataStreamsFormat/PDSContainerPackedPacker.h"
#include "PackedDataStreamsFormat/PDSStringPacker.h"

#include "PackedDataStreamsFormat/pds_packing_enums.h"

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

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSPackerFactory" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSPackerFactory.cc,v 1.4 2002/08/09 18:03:55 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
class PDSPackerSubFactoryBase
{
   public:
      virtual PDSPackerBase* create( const UInt32*& ioBuffer, 
				     unsigned char& ioStartBit,
				     DABoolean iSwappedBytes ) = 0;
};

template <class T>
class PDSPackerSubFactoryTemplate : public PDSPackerSubFactoryBase
{
   public:
      PDSPackerBase* create( const UInt32*& ioBuffer, 
			     unsigned char& ioStartBit,
			     DABoolean ) {
	 return new T( ioBuffer, ioStartBit );
      }
};

static
PDSPackerSubFactoryBase*
g_subFactories[PDSPacking::kNumberOfTypes][PDSPacking::kNumberOfStrategies];

#define SEPARATOR ::
#define CREATE_SUBFACTORY( _pack_strategy_, _pack_type_, _strategy_, _type_ ) \
g_subFactories[_pack_type_ ][ _pack_strategy_ ] = \
new PDSPackerSubFactoryTemplate< PDS ## _strategy_ ## Packer<_type_ > >;

#define CREATE_SUBFACTORY_SPECIAL( _pack_strategy_, _pack_type_, _strategy_) \
g_subFactories[_pack_type_ ][_pack_strategy_ ] = \
new PDSPackerSubFactoryTemplate< PDS ## _strategy_ ## Packer >;

#define CREATE_SUBFACTORY_OPTIMIZING_FRACTIONAL( _pack_type_, _type_ ) \
g_subFactories[_pack_type_ ][PDSPacking::kFractionalPacking ] = \
new PDSFractionalPackerSubFactory<_type_>;


#define CREATE_SUBFACTORY_PACKEDCONTAINER( _pack_strategy_ ) \
g_subFactories[PDSPacking::kContainerType ][_pack_strategy_ ] = \
new PDSContainerPackedPackerSubFactory;


//precompute exponential part of FractionalPacker for 2^-22 (2e-7) to 2^22 (4e6)
enum {kMinExponent = -22, kMaxExponent = 22};
//how big of an array to we use when precomputing values
static const float kMaxCacheSize = 25000.;


#include "StorageManagement/Compression/SMCachingFractionalPacker.h"
#include "StorageManagement/Compression/SMSharingCachingPolicy.h"
template< class T>
class PDSCachingFractionalPacker : public PDSPackerTemplate<T>
{
   public:
      PDSCachingFractionalPacker(unsigned int iTotalNumberOfBits,
                                 unsigned int iNumberOfExponentBits,
                                 float iFraction,
                                 int iExponentOffset ):
      m_packer(iTotalNumberOfBits, iNumberOfExponentBits, iFraction, iExponentOffset)
      { }

      SMPackerTemplate<T>& packer() { return m_packer;}

      void storeStrategyInfo( UInt32& ioPackedWord,
                             unsigned char& ioStartBit,
                             std::vector<UInt32>& ioContainer ) const
      {
         //This class is not meant for storage
                                 assert(false);
      }
      PDSPacking::Strategies strategy() const { 
         return PDSPacking::kFractionalPacking; }

   private:
      SMCachingFractionalPacker<T,SMSharingCachingPolicy<T,kMaxExponent,kMinExponent> > m_packer;
};
template <class T>
class PDSFractionalPackerSubFactory : public PDSPackerSubFactoryBase
{
   public:
      PDSPackerBase* create( const UInt32*& ioBuffer, 
			     unsigned char& ioStartBit,
			     DABoolean iBytesSwapped) {
	 PDSPackerFactory factory;
	 const UInt32* tempIOBuffer = ioBuffer;
	 unsigned char tempIOStartBit = ioStartBit;
         PDSFractionalPacker<T> tempPacker(ioBuffer, ioStartBit);
         SMFractionalPacker<T>& packer = static_cast<SMFractionalPacker<T>&>(tempPacker.packer());
         int exponentOffset = packer.exponentOffset();
         unsigned int totalNumberOfBits = packer.numberOfBits();
         unsigned int numberOfExponentBits = packer.numberOfExponentBits();
         float fraction = packer.fraction();
         //decide which optimization to use
         if( (exponentOffset >= kMinExponent) &&
             (numberOfExponentBits <= kMaxExponent -kMinExponent +1) &&
             (fraction > 1.0/kMaxCacheSize) ) {
               //cout <<" made caching" <<std::endl;
               return new PDSCachingFractionalPacker<T>(totalNumberOfBits,
                                                        numberOfExponentBits,
                                                        fraction,
                                                        exponentOffset );
         }                                   
         //cout <<" made normal" <<std::endl;                         
	 return new PDSFractionalPacker<T>( tempIOBuffer, tempIOStartBit);
      }  
};

class PDSContainerPackedPackerSubFactory : public PDSPackerSubFactoryBase
{
   public:
      PDSPackerBase* create( const UInt32*& ioBuffer, 
			     unsigned char& ioStartBit,
			     DABoolean iBytesSwapped) {
	 PDSPackerFactory factory;
	 return new PDSContainerPackedPacker( factory.createPacker( ioBuffer, ioStartBit, iBytesSwapped) );
      }
};

class PDSStringPackerSubFactory : public PDSPackerSubFactoryBase
{
   public:
      PDSPackerBase* create( const UInt32*& ioBuffer, 
			     unsigned char& ioStartBit,
			     DABoolean iSwappedBytes ) {
	 return new PDSStringPacker( iSwappedBytes );
      }
};

static
void
initSubFactories()
{
   static DABoolean firstTime = true;
   if( firstTime) {
      firstTime = false;

      memset( reinterpret_cast<char*>(&g_subFactories), 0, 
	      sizeof(g_subFactories));

      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kCharType, IntNoPack, char );
      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kShortType, IntNoPack, short );
      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kIntType, IntNoPack, int );
      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kLongType, IntNoPack, long );

      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kUCharType, IntNoPack, unsigned char );
      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kUShortType, IntNoPack, unsigned short );
      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kUIntType, IntNoPack, unsigned int );
      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kULongType, IntNoPack, unsigned long );

      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kFloatType, FloatNoPack, float );
      CREATE_SUBFACTORY( PDSPacking::kNoPacking, PDSPacking::kDoubleType, FloatNoPack, double );


      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kCharType, Fixed, char );
      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kShortType, Fixed, short );
      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kIntType, Fixed, int );
      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kLongType, Fixed, long );

      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kUCharType, Fixed, unsigned char );
      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kUShortType, Fixed, unsigned short );
      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kUIntType, Fixed, unsigned int );
      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kULongType, Fixed, unsigned long );

      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kFloatType, Fixed, float );
      CREATE_SUBFACTORY( PDSPacking::kFixedPacking, PDSPacking::kDoubleType, Fixed, double );


      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kCharType, FixedTrueZero, char );
      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kShortType, FixedTrueZero, short );
      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kIntType, FixedTrueZero, int );
      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kLongType, FixedTrueZero, long );

      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kUCharType, FixedTrueZero, unsigned char );
      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kUShortType, FixedTrueZero, unsigned short );
      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kUIntType, FixedTrueZero, unsigned int );
      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kULongType, FixedTrueZero, unsigned long );

      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kFloatType, FixedTrueZero, float );
      CREATE_SUBFACTORY( PDSPacking::kFixedTrueZeroPacking, PDSPacking::kDoubleType, FixedTrueZero, double );


      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kCharType, Fractional, char );
      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kShortType, Fractional, short );
      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kIntType, Fractional, int );
      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kLongType, Fractional, long );

      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kUCharType, Fractional, unsigned char );
      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kUShortType, Fractional, unsigned short );
      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kUIntType, Fractional, unsigned int );
      CREATE_SUBFACTORY( PDSPacking::kFractionalPacking, PDSPacking::kULongType, Fractional, unsigned long );

      CREATE_SUBFACTORY_OPTIMIZING_FRACTIONAL(PDSPacking::kFloatType, float);
      CREATE_SUBFACTORY_OPTIMIZING_FRACTIONAL(PDSPacking::kDoubleType, double);
//      _CREATE_SUBFACTORY( kFractionalPacking, kFloatType, Fractional, float );
//      _CREATE_SUBFACTORY( kFractionalPacking, kDoubleType, Fractional, double );

      CREATE_SUBFACTORY_SPECIAL( PDSPacking::kNoPacking, PDSPacking::kClassContainerType, ContainerNoPack );
      CREATE_SUBFACTORY_PACKEDCONTAINER( PDSPacking::kNoPacking );
      CREATE_SUBFACTORY_PACKEDCONTAINER( PDSPacking::kFractionalPacking );
      CREATE_SUBFACTORY_PACKEDCONTAINER( PDSPacking::kFixedPacking );
      CREATE_SUBFACTORY_PACKEDCONTAINER( PDSPacking::kFixedTrueZeroPacking );

      g_subFactories[ PDSPacking::kStringType ][PDSPacking::kNoPacking ] = 
	 new PDSStringPackerSubFactory;
   }
}


static
PDSPackerSubFactoryBase&
subFactory( PDSPacking::Types iType, PDSPacking::Strategies iStrategy)
{
   //cout <<" type "<<iType<<"  strategy "<<iStrategy<<std::endl;
   assert( 0 != g_subFactories[iType][iStrategy]);
   return *(g_subFactories[iType][iStrategy]);
}

//
// constructors and destructor
//
PDSPackerFactory::PDSPackerFactory()
{
   initSubFactories();
}

// PDSPackerFactory::PDSPackerFactory( const PDSPackerFactory& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//PDSPackerFactory::~PDSPackerFactory()
//{
//}

//
// assignment operators
//
// const PDSPackerFactory& PDSPackerFactory::operator=( const PDSPackerFactory& rhs )
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

//
// const member functions
//
PDSPackerBase* 
PDSPackerFactory::createPacker( const UInt32*& ioBuffer,
				unsigned char& ioStartBit,
				DABoolean iSwappedBytes ) const
{
   PDSPacking::Types type;
   PDSPacking::Strategies strategy;
   PDSPackerBase::readTypeAndStrategy( ioBuffer, ioStartBit, type, strategy );

   //report(DEBUG,kFacilityString) <<"Factory type: " <<type << " strategy: " <<strategy << std::endl;
   return subFactory(type,strategy).create(ioBuffer, 
					   ioStartBit, 
					   iSwappedBytes);
}


//
// static member functions
//
