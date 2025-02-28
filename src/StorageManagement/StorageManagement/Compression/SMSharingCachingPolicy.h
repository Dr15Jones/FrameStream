#if !defined(STORAGEMANAGEMENT_SMSHARINGCACHINGPOLICY_H)
#define STORAGEMANAGEMENT_SMSHARINGCACHINGPOLICY_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMSharingCachingPolicy
// 
/**\class SMSharingCachingPolicy SMSharingCachingPolicy.h StorageManagement/SMSharingCachingPolicy.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Mar 11 14:07:13 EST 2002
// $Id: SMSharingCachingPolicy.h,v 1.2 2003/03/08 20:56:01 cdj Exp $
//
// Revision history
//
// $Log: SMSharingCachingPolicy.h,v $
// Revision 1.2  2003/03/08 20:56:01  cdj
// made sure that recompressing using fractional packing returns the same result as the first compression
//
// Revision 1.1  2002/03/17 16:06:30  cdj
// added optimized version of Fractional packing
//

// system include files
#include <list>
#include <assert.h>

// user include files

// forward declarations


template< class T, int ILevel>
class SMHalveValue
{
   public:
      static void calculate(T iValue, T* oIterator){
	 *oIterator = iValue;
	 SMHalveValue<T,ILevel-1>::calculate(iValue/2.0, --oIterator);
      }
};

template<>
class SMHalveValue<double,0>
{
   public:
      static void calculate(double iValue, double* oIterator){
	 *oIterator = iValue;
      }
};
template<>
class SMHalveValue<float,0>
{
   public:
      static void calculate(float iValue, float* oIterator){
	 *oIterator = iValue;
      }
};


template< class T, int IMax, int IMin>
class SMInitializeHalveValueArray
{
   public:
      static void calculate(T * oBeginIterator) {
	 if (IMax > 0 ) {
	    SMHalveValue<T,IMax-IMin>::calculate( T(1<<IMax), oBeginIterator+IMax-IMin);
	 } else {
	    SMHalveValue<T,IMax-IMin>::calculate( 1.0/T(1<<IMax), oBeginIterator+IMax-IMin);	 }
      }
};


template< class T, int IMaxPower2, int IMinPower2>
class SMSharingCachingPolicy
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      //SMSharingCachingPolicy();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static const T* powerArray(unsigned int iNumberOfExponentBits,
				 int iExponentOffset ) {
	 static T s_powerArray[IMaxPower2-IMinPower2+1];
	 static int firstTime = 0;
	 if( 0 == firstTime ) {
	    firstTime = 1;
	    SMInitializeHalveValueArray<T,IMaxPower2,IMinPower2>::calculate(s_powerArray);
	 }
	 assert(0 < iExponentOffset - IMinPower2);
	 return s_powerArray+iExponentOffset - IMinPower2;
      }

      static const T* fractionArray( unsigned int iNumberOfMantissaBits,
				     float iFraction ) {
	 //first see if we already have this value pre-computed
	 typedef list<pair< pair<unsigned int, float>, T*> > List;
	 List& tArrayList = fractionArrayList();
	 for( typename List::iterator itInfo = tArrayList.begin();
	      itInfo != tArrayList.end();
	      ++itInfo ) {
	    pair<unsigned int, float> values = (*itInfo).first;
	    if( values.first == iNumberOfMantissaBits &&
		values.second == iFraction ) {
	       return (*itInfo).second;
	    }
	 }
	 //need to create a new array
	 const unsigned int kSize = 1.0/iFraction+1.5;
	 T* newArray = new T[kSize];
	 tArrayList.push_back( make_pair(make_pair(iNumberOfMantissaBits,iFraction), newArray ) );
	 //fill the array
	 unsigned int index = 0;
	 for( T* itValue = newArray; itValue != newArray + kSize; ++itValue, ++index ) {
	    *itValue = (index+0.5)*iFraction+0.5;
	 }
	 
	 return newArray;
      }

      static list<pair< pair<unsigned int, float>, T*> >&
      fractionArrayList() {
	 static list<pair< pair<unsigned int, float>, T*> > s_list;
	 return s_list;
      }
   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMSharingCachingPolicy( const SMSharingCachingPolicy& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMSharingCachingPolicy& operator=( const SMSharingCachingPolicy& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMSharingCachingPolicy.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMSHARINGCACHINGPOLICY_H */
