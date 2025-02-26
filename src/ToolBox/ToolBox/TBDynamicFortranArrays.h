// -*- C++ -*-
//
// File:    TBDynamicFortranArrays.h
// Package: ToolBox
// Module:  DynamicFortranArrays
// 
// Summary: Wrapped access to arrays, Fortran style, with DYNAMIC
//          allocation
//
// Description:
// Simply a slight modification of CDJ's TBFortranArrays.h to allow
//   dimensions/index-ranges to be specified at _construction_ time.
//   Basically change dimensions to member data and dynamically
//   allocate the internal array.
//
// Usage:
// The user-interface is essentially identical to the original,
//   except for the template instantiation and constructor:
//       TBDynamicFortranArray<double> anArray(0,numComponents);
//   and so on. A default argument of 1 for the starting index in
//   each dimension is supported, as in the original classes.
// Because the dimensions are specified in the ctor, there is no
//   longer a distinction between "Bounded" and normal arrays.
//
//
// ************** FROM TBFortranArrays.h *************
// Description: Templated classes to make it easier to access data in
//              Fortran arrays
//
// Usage:
//    These templated classes allow you to access a C array as if it were
//    a Fortran array.
//
//    Example
//       // the struct trakr1_ 'sits on top of' the Fortran common block
//       // TRAKR1 where the member data of trakr1_ are the arrays in the
//       // common block
//       // MXTRAK is an unsigned int constant
//
//       // Make it easy to read trakr1_.cucd which is a c array of size
//       //  MXTRAK of type FReal
//       TBFortranArray< FReal, MXTRAK >& cucd = 
//                      *( (TBFortranArray< FReal, MXTRAK>*) trakr1_.cucd);
//
//       //Get cucd of the 5th track
//       FReal cucdValue = cucd(5);
//
//       // Make it easy to read trakr1_.errmcd which is actually a 
//       //  2D fortran array of size ( MXTRAK,28 )
//       TBFortran2DArray<FReal, MXTRAK, 28>& errmcd =
//          *( (TBFortran2DArray<FReal, MXTRAK, 28>*) trakr1_.errmcd );
//
//       //Get errmcd for the 3rd element of the 5th track
//       FReal errmcdValue = errmcd( 5, 3 );
//
//   NOTE: Fortran2DArray uses the Fortran convention for its two indicies,
//         i.e. the first index changes faster than the second index.
// ************** End excerpt *************
//
// Implementation Notes:
// The array in each case is represented internally as a 1-D array,
//   and is allocated dynamically in the ctor.
//
// Author:  Thomas Meyer (tom)
// Created: 03/21/2001
// $Id: TBDynamicFortranArrays.h,v 1.1 2001/03/22 15:06:51 tom Exp $
//
// Revision history:
// $Log: TBDynamicFortranArrays.h,v $
// Revision 1.1  2001/03/22 15:06:51  tom
// New set of DYNAMICALLY-allocated FortranArrays
//
//
/* ******************************************************************** */
#if !defined(TOOLBOX_DYNAMIC_FORTRANARRAYS_H)
#define TOOLBOX_DYNAMIC_FORTRANARRAYS_H

// INCLUDED FILES

// DEFINITIONS

/* ======================================================================== */
template <class T>
class TBDynamicFortranArray
{
public:
  
  // Constructor(s)
  TBDynamicFortranArray(int firstIndex, int lastIndex) :
    m_minIndex(firstIndex),
    m_maxIndex(lastIndex),
    m_size(m_maxIndex - m_minIndex + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }

  TBDynamicFortranArray(int lastIndex) :
    m_minIndex(1),
    m_maxIndex(lastIndex),
    m_size(m_maxIndex - m_minIndex + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }
  
  // Destructor
  ~TBDynamicFortranArray() {
    delete [] m_array;
  }
  
  // Accessors
  T& operator()(int iIndex) { 
    return m_array[fortran2cIndex(iIndex )];
  }
  
  T* cArray() {
    return m_array;
  }
  
  // Accessors --- const
  T operator()( int iIndex ) const {
    return m_array[fortran2cIndex(iIndex)];
  }
  
  const T* cArray() const {
    return m_array;
  }
  
  int maxSize() const { return m_size; }
  int minFirstIndex() const { return m_minIndex; }
  int maxLastIndex()  const { return m_maxIndex; }
  
private:
  // Hide standard default ctors
  TBDynamicFortranArray();
  TBDynamicFortranArray(const TBDynamicFortranArray&);
  TBDynamicFortranArray& operator=(const TBDynamicFortranArray&);

  // Magic function to translate Fortran-style index to C-style
  int fortran2cIndex(int iIndex) const {
    return iIndex - minFirstIndex();
  }

  // Min and max index values
  int m_minIndex;
  int m_maxIndex;
  int m_size;
  
  // Internal representation of the array
  T* m_array;
};
/* ======================================================================== */

/* ======================================================================== */
template <class T>
class TBDynamicFortran1DArray : public TBDynamicFortranArray<T>
{
};
/* ======================================================================== */

/* ======================================================================== */
template <class T>
class TBDynamicFortran2DArray
{
public:
  
  // Constructor(s)
  TBDynamicFortran2DArray(int firstIndex1, int lastIndex1,
		   int firstIndex2, int lastIndex2) :
    m_minIndex1(firstIndex1),
    m_maxIndex1(lastIndex1),
    m_size1(m_maxIndex1 - m_minIndex1 + 1),
    m_minIndex2(firstIndex2),
    m_maxIndex2(lastIndex2),
    m_size2(m_maxIndex2 - m_minIndex2 + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }

  TBDynamicFortran2DArray(int lastIndex1,
		   int lastIndex2) :
    m_minIndex1(1),
    m_maxIndex1(lastIndex1),
    m_size1(m_maxIndex1 - m_minIndex1 + 1),
    m_minIndex2(1),
    m_maxIndex2(lastIndex2),
    m_size2(m_maxIndex2 - m_minIndex2 + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }

  // Destructor
  ~TBDynamicFortran2DArray() {
    delete [] m_array;
  }
  
  // Accessors
  T& operator()(int iIndex1, int iIndex2) {
    return m_array[fortran2cIndex(iIndex1, iIndex2)];
  }
  
  T* cArray() {
    return m_array;
  }
  
  // Accessors --- const
  T operator()(int iIndex1, int iIndex2) const {
    return m_array[fortran2cIndex(iIndex1, iIndex2)];
  }
  
  const T* cArray() const {
    return m_array;
  }
  
  int maxSize() const { return m_size1*m_size2; }
  int minFirstIndex1() const { return m_minIndex1; }
  int maxLastIndex1()  const { return m_maxIndex1; }
  int minFirstIndex2() const { return m_minIndex2; }
  int maxLastIndex2()  const { return m_maxIndex2; }
  
private:
  // Hide standard default ctors
  TBDynamicFortran2DArray();
  TBDynamicFortran2DArray(const TBDynamicFortran2DArray&);
  TBDynamicFortran2DArray& operator=(const TBDynamicFortran2DArray&);

  // Magic function to translate Fortran-style index to C-style
  int fortran2cIndex(int iIndex1,
		     int iIndex2) const {
    return (iIndex1 - minFirstIndex1()) +
           (iIndex2 - minFirstIndex2())*m_size1;
  }
  
  // Min and max index values
  int m_minIndex1;
  int m_maxIndex1;
  int m_size1;
  int m_minIndex2;
  int m_maxIndex2;
  int m_size2;
  
  // Internal representation of the array
  T* m_array;
};
/* ======================================================================== */

/* ======================================================================== */
template <class T>
class TBDynamicFortran3DArray
{
public:
  
  // Constructor(s)
  TBDynamicFortran3DArray(int firstIndex1, int lastIndex1,
		   int firstIndex2, int lastIndex2,
		   int firstIndex3, int lastIndex3) :
    m_minIndex1(firstIndex1),
    m_maxIndex1(lastIndex1),
    m_size1(m_maxIndex1 - m_minIndex1 + 1),
    m_minIndex2(firstIndex2),
    m_maxIndex2(lastIndex2),
    m_size2(m_maxIndex2 - m_minIndex2 + 1),
    m_minIndex3(firstIndex3),
    m_maxIndex3(lastIndex3),
    m_size3(m_maxIndex3 - m_minIndex3 + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }

  TBDynamicFortran3DArray(int lastIndex1,
		   int lastIndex2,
		   int lastIndex3) :
    m_minIndex1(1),
    m_maxIndex1(lastIndex1),
    m_size1(m_maxIndex1 - m_minIndex1 + 1),
    m_minIndex2(1),
    m_maxIndex2(lastIndex2),
    m_size2(m_maxIndex2 - m_minIndex2 + 1),
    m_minIndex3(1),
    m_maxIndex3(lastIndex3),
    m_size3(m_maxIndex3 - m_minIndex3 + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }
  
  // Destructor
  ~TBDynamicFortran3DArray() {
    delete [] m_array;
  }
  
  // Accessors
  T& operator()(int iIndex1, int iIndex2, int iIndex3) {
    return m_array[fortran2cIndex(iIndex1, iIndex2, iIndex3)];
  }
  
  T* cArray() {
    return m_array;
  }
  
  // Accessors --- const
  T operator()(int iIndex1, int iIndex2, int iIndex3) const {
    return m_array[fortran2cIndex(iIndex1, iIndex2, iIndex3)];
  }
  
  const T* cArray() const {
    return m_array;
  }
  
  int maxSize() const { return m_size1*m_size2*m_size3; }
  int minFirstIndex1() const { return m_minIndex1; }
  int maxLastIndex1()  const { return m_maxIndex1; }
  int minFirstIndex2() const { return m_minIndex2; }
  int maxLastIndex2()  const { return m_maxIndex2; }
  int minFirstIndex3() const { return m_minIndex3; }
  int maxLastIndex3()  const { return m_maxIndex3; }
  
private:
  // Hide standard default ctors
  TBDynamicFortran3DArray();
  TBDynamicFortran3DArray(const TBDynamicFortran3DArray&);
  TBDynamicFortran3DArray& operator=(const TBDynamicFortran3DArray&);

  // Magic function to translate Fortran-style index to C-style
  int fortran2cIndex(int iIndex1, 
		     int iIndex2,
		     int iIndex3 ) const {
    return (iIndex1 - minFirstIndex1()) +
           (iIndex2 - minFirstIndex2())*m_size1 +
           (iIndex3 - minFirstIndex3())*m_size1*m_size2;
  }
  
  // Min and max index values
  int m_minIndex1;
  int m_maxIndex1;
  int m_size1;
  int m_minIndex2;
  int m_maxIndex2;
  int m_size2;
  int m_minIndex3;
  int m_maxIndex3;
  int m_size3;
  
  // Internal representation of the array
  T* m_array;
};
/* ======================================================================== */

/* ======================================================================== */
template <class T>
class TBDynamicFortran4DArray
{
public:
  
  // Constructor(s)
  TBDynamicFortran4DArray(int firstIndex1, int lastIndex1,
		   int firstIndex2, int lastIndex2,
		   int firstIndex3, int lastIndex3,
		   int firstIndex4, int lastIndex4) :
    m_minIndex1(firstIndex1),
    m_maxIndex1(lastIndex1),
    m_size1(m_maxIndex1 - m_minIndex1 + 1),
    m_minIndex2(firstIndex2),
    m_maxIndex2(lastIndex2),
    m_size2(m_maxIndex2 - m_minIndex2 + 1),
    m_minIndex3(firstIndex3),
    m_maxIndex3(lastIndex3),
    m_size3(m_maxIndex3 - m_minIndex3 + 1),
    m_minIndex4(firstIndex4),
    m_maxIndex4(lastIndex4),
    m_size4(m_maxIndex4 - m_minIndex4 + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }

  TBDynamicFortran4DArray(int lastIndex1,
		   int lastIndex2,
		   int lastIndex3,
		   int lastIndex4) :
    m_minIndex1(1),
    m_maxIndex1(lastIndex1),
    m_size1(m_maxIndex1 - m_minIndex1 + 1),
    m_minIndex2(1),
    m_maxIndex2(lastIndex2),
    m_size2(m_maxIndex2 - m_minIndex2 + 1),
    m_minIndex3(1),
    m_maxIndex3(lastIndex3),
    m_size3(m_maxIndex3 - m_minIndex3 + 1),
    m_minIndex4(1),
    m_maxIndex4(lastIndex4),
    m_size4(m_maxIndex4 - m_minIndex4 + 1),
    m_array(0)
  {
    m_array = new T[maxSize()];
  }
  
  // Destructor
  ~TBDynamicFortran4DArray() {
    delete [] m_array;
  }
  
  // Accessors
  T& operator()(int iIndex1, int iIndex2, int iIndex3, int iIndex4) {
    return m_array[fortran2cIndex(iIndex1, iIndex2, iIndex3, iIndex4)];
  }
  
  T* cArray() {
    return m_array;
  }
  
  // Accessors --- const
  T operator()(int iIndex1, int iIndex2, int iIndex3, int iIndex4) const {
    return m_array[fortran2cIndex(iIndex1, iIndex2, iIndex3, iIndex4)];
  }
  
  const T* cArray() const {
    return m_array;
  }
  
  int maxSize() const { return m_size1*m_size2*m_size3*m_size4; }
  int minFirstIndex1() const { return m_minIndex1; }
  int maxLastIndex1()  const { return m_maxIndex1; }
  int minFirstIndex2() const { return m_minIndex2; }
  int maxLastIndex2()  const { return m_maxIndex2; }
  int minFirstIndex3() const { return m_minIndex3; }
  int maxLastIndex3()  const { return m_maxIndex3; }
  int minFirstIndex4() const { return m_minIndex4; }
  int maxLastIndex4()  const { return m_maxIndex4; }
  
private:
  // Hide standard default ctors
  TBDynamicFortran4DArray();
  TBDynamicFortran4DArray(const TBDynamicFortran4DArray&);
  TBDynamicFortran4DArray& operator=(const TBDynamicFortran4DArray&);

  // Magic function to translate Fortran-style index to C-style
  int fortran2cIndex(int iIndex1, 
		     int iIndex2,
		     int iIndex3,
		     int iIndex4 ) const {
    return (iIndex1 - minFirstIndex1()) + 
	   (iIndex2 - minFirstIndex2())*m_size1 +
	   (iIndex3 - minFirstIndex3())*m_size1*m_size2 +
	   (iIndex4 - minFirstIndex4())*m_size1*m_size2*m_size3 );
  }
  
  // Min and max index values
  int m_minIndex1;
  int m_maxIndex1;
  int m_size1;
  int m_minIndex2;
  int m_maxIndex2;
  int m_size2;
  int m_minIndex3;
  int m_maxIndex3;
  int m_size3;
  int m_minIndex4;
  int m_maxIndex4;
  int m_size4;
  
  // Internal representation of the array
  T* m_array;
};
/* ======================================================================== */

#endif  /* TOOLBOX_DYNAMIC_FORTRANARRAYS_H */
