#if !defined(STORAGEMANAGEMENT_SMLATTICESTORAGEHELPER_CC)
#define STORAGEMANAGEMENT_SMLATTICESTORAGEHELPER_CC
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMLatticeStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Tue Jun  8 09:39:48 EDT 1999
// $Id: SMLatticeStorageHelper.cc,v 1.6 2002/12/09 16:16:05 cleo3 Exp $
//
// Revision history
//
// $Log: SMLatticeStorageHelper.cc,v $
// Revision 1.6  2002/12/09 16:16:05  cleo3
// added typename
//
// Revision 1.5  2002/03/25 19:14:19  cdj
// now reuse Lattice during readback
//
// Revision 1.4  2000/04/06 14:58:45  cdj
// insert iterator now has correct value_type
//
// Revision 1.3  2000/03/08 19:01:47  cdj
// fixed mismatch between reading and writing schema use for Lattices
//
// Revision 1.2  2000/01/08 19:18:13  cdj
// updated Lattice code to work with new cxx compiler
//
// Revision 1.1  1999/10/11 22:00:49  cdj
// added Lattice storage code
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMLatticeStorageHelper.h"
#include "StorageManagement/SMLatticeLinkInfoIn.h"
#include "StorageManagement/SMLatticeLinkInfoOut.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMFillContents.h"
#include "StorageManagement/SMMakeContents.h"
#include "StorageManagement/SMDeliverer.h"

#include "StorageManagement/SMLatticeProxy.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "StorageManagement.SMLatticeStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SMLatticeStorageHelper.cc,v 1.6 2002/12/09 16:16:05 cleo3 Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//


template< class T>
SMLatticeStorageHelper<T>::SMLatticeStorageHelper():
   m_lattice(0)
{
   registerDeliverVersion( 
      new SMDeliverer<T, SMLatticeStorageHelper<T> >( 
	 &SMLatticeStorageHelper<T>::deliverV1, this ) );
}

// SMLatticeStorageHelper<T>::SMLatticeStorageHelper( const SMLatticeStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

template< class T>
SMLatticeStorageHelper<T>::~SMLatticeStorageHelper()
{
}

//
// assignment operators
//
// const SMLatticeStorageHelper& SMLatticeStorageHelper<T>::operator=( const SMLatticeStorageHelper& rhs )
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
template< class T>
SMProxyBase* 
SMLatticeStorageHelper<T>::makeProxy() const
{
   return new SMLatticeProxy<T>( const_cast< SMLatticeStorageHelper<T>* >(this) );
}


template< class Lattice >
class LatticeOutputItr : 
#if defined(OLD_ITERATOR_CLASSES_BUG)
   public forward_iterator< const SMLatticeLinkInfoBase<Lattice >,
   ptrdiff_t >
#else
   public iterator< forward_iterator_tag, const SMLatticeLinkInfoBase<Lattice> >
#endif
{
   public:
      typedef typename Lattice::LinkItr Itr;
      typedef SMLatticeLinkInfoBase<Lattice> value_type;

      typedef SMLatticeLinkInfoOut<Lattice> real_value_type;

      LatticeOutputItr( const Itr& iIterator ) :
	 m_iterator( iIterator ), m_value(0) {}
      LatticeOutputItr() : m_iterator(), m_value(0) {}


      const value_type& operator*() {
	 m_value = *m_iterator;
	 return m_value; }

      const LatticeOutputItr<Lattice>& operator++() {
	 ++m_iterator;
	 return *this; }

      LatticeOutputItr<Lattice> operator++(int ) {
	 LatticeOutputItr<Lattice> temp = *this;
	 ++m_iterator;
	 return temp; }


      DABoolean operator==( const LatticeOutputItr<Lattice>& iRHS ) {
	 return (m_iterator == iRHS.m_iterator) ; }

      DABoolean operator!=( const LatticeOutputItr<Lattice>& iRHS ) {
	 return (m_iterator != iRHS.m_iterator) ; }

   private:
      real_value_type m_value;
      Itr m_iterator;
};

//use a symbolic name to denote the type which is used to store an enum
typedef int EnumType;

template< class T>
void 
SMLatticeStorageHelper<T>::implementStore( 
   SMSinkStream& iSink,
   const T& iData ) 
{
   typedef LatticeOutputItr< T > Itr;
   //output the topology info
   iSink << sm_field( "LNode", static_cast<EnumType>( iData.isLNodeMulti() ? 
						      T::LNodeMulti :
						      T::Default ) )
	 << sm_field( "RNode", static_cast<EnumType>( iData.isRNodeMulti() ? 
						      T::RNodeMulti :
						      T::Default ) )
	 << sm_field( "LLink", static_cast<EnumType>( iData.isLLinkMulti() ? 
						      T::LLinkMulti :
						      T::Default ) )
	 << sm_field( "RLink", static_cast<EnumType>( iData.isRLinkMulti() ? 
						      T::RLinkMulti :
						      T::Default ) );
   
   //store the lattice info
   iSink << sm_field( "links", sm_contents( Itr(iData.links().begin()), 
					    Itr(iData.links().end()) ) );
}



template< class Lattice >
class LatticeInsertItr : 
#if defined(OLD_ITERATOR_CLASSES_BUG)
   public output_iterator 
#else
   public iterator<output_iterator_tag, SMLatticeLinkInfoBase<Lattice>* >
#endif
{
   public:
      // ---------- constants, enums and typedefs --------------
      typedef Lattice container_type;
      typedef SMLatticeLinkInfoBase<Lattice>* value_type;

      LatticeInsertItr (container_type& x) : m_container(x) {}

      const LatticeInsertItr<Lattice>& operator= (value_type value) {
	 typename Lattice::Link* link = m_container.connect(
	    value->vLeftID().front(),
	    value->vRightID().front(),
	    value->linkData() );

	 //now fill all remaining left nodes
	 typedef typename Lattice::VectorLeftID VLeftID;
	 typedef typename Lattice::VectorRightID VRightID;
	 const typename VLeftID::const_iterator itLEnd =
	    value->vLeftID().end();
	 typename VLeftID::const_iterator itLBegin = 
	    value->vLeftID().begin();
	 ++itLBegin;
	 for( typename VLeftID::const_iterator itLeft = itLBegin; 
	      itLeft != itLEnd; 
	      ++itLeft ) {
	    m_container.connect( *itLeft, *link );
	 }

	 //now fill all remaining right nodes
	 const typename VRightID::const_iterator itREnd =
	    value->vRightID().end();
	 typename VRightID::const_iterator itRBegin = 
	    value->vRightID().begin();
	 ++itRBegin;
	 for( typename VRightID::const_iterator itRight = itRBegin;
	      itRight != itREnd; 
	      ++itRight ) {
	    m_container.connect( *link, *itRight );
	 }

	 //since we own the memory, we need to delete it
	 delete value;

	 return *this;
      }
      LatticeInsertItr<Lattice>& operator*  ()    { return *this; }
      LatticeInsertItr<Lattice>& operator++ ()    { return *this; }
      LatticeInsertItr<Lattice> operator++ (int) { return *this; }

   private:
      LatticeInsertItr(); // stop default

      Lattice& m_container;
};

template< class T>
T* 
SMLatticeStorageHelper<T>::deliverV1( SMSourceStream& iSource )
{
   EnumType lNodeMulti;
   EnumType rNodeMulti;
   EnumType lLinkMulti;
   EnumType rLinkMulti;

   iSource >> lNodeMulti >> rNodeMulti >> lLinkMulti >> rLinkMulti;

   T* temp = m_lattice;
   if( 0 == temp ) {
      temp = new T(
      static_cast<typename T::LatticeTopology>(lNodeMulti),
      static_cast<typename T::LatticeTopology>(rNodeMulti),
      static_cast<typename T::LatticeTopology>(lLinkMulti),
      static_cast<typename T::LatticeTopology>(rLinkMulti) );
   }

   LatticeInsertItr<T> insertIterator( *temp);

   iSource >> sm_make_contents( insertIterator );
   
   return temp;
}

//
// const member functions
//
template< class T>
const T& 
SMLatticeStorageHelper<T>::getDefault() const
{
   static const T temp;
   return temp;
}

template< class T>
DABoolean 
SMLatticeStorageHelper<T>::compare( 
   const T* iNewData, 
   const T& iOldData ) const
{
   //need to compare contents
   return false;
}


//
// static member functions
//



#endif /* STORAGEMANAGEMENT_SMLATTICESTORAGEHELPER_CC */
