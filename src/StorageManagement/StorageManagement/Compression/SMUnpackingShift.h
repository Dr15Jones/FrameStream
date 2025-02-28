#if !defined(STORAGEMANAGEMENT_SMUNPACKINGSHIFT_H)
#define STORAGEMANAGEMENT_SMUNPACKINGSHIFT_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMUnpackingShift
// 
/**\class SMUnpackingShift SMUnpackingShift.h StorageManagement/SMUnpackingShift.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sat Mar  8 19:09:02 EST 2003
// $Id: SMUnpackingShift.h,v 1.2 2003/03/10 16:32:08 cdj Exp $
//
// Revision history
//
// $Log: SMUnpackingShift.h,v $
// Revision 1.2  2003/03/10 16:32:08  cdj
// if the floating point packing precision is exactly a power of 2, do not shift to center of bin since it is impossible to get rounding problems on recompression (also returns correct value if only storing integral values with precision 1.0)
//
// Revision 1.1  2003/03/09 00:50:38  cdj
// made sure that recompressing using fixed packing returns the same result as the first compression
//

// system include files

// user include files
#include "Experiment/cleo_math.h"

// forward declarations
class DummyFriend;

template <class T>
class SMUnpackingShift
{
      // ---------- friend classes and functions ---------------
      class DummyFriend;

   public:
      // ---------- static member functions --------------------
      static T shift(T iPrecision) ;

   private:
      // ---------- Constructors and destructor ----------------
      SMUnpackingShift();
      SMUnpackingShift( const SMUnpackingShift& ); // stop default

      const SMUnpackingShift& operator=( const SMUnpackingShift& ); // stop default
};

// inline function definitions
template<class T>
inline
T
SMUnpackingShift<T>::shift(T iPrecision)
{
   return T(0);
}

template<>
inline
float
SMUnpackingShift<float>::shift(float iPrecision)
{
   int exponent;
   return ( (0.5== frexp(iPrecision, &exponent) ) ? 0.: 0.5);
}

template<>
inline
double
SMUnpackingShift<double>::shift(double iPrecision)
{
   int exponent;
   return ( (0.5== frexp(iPrecision, &exponent) ) ? 0.: 0.5);
}

#endif /* STORAGEMANAGEMENT_SMUNPACKINGSHIFT_H */
