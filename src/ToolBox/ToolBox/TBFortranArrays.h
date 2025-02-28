#if !defined(TOOLBOX_FORTRANARRAYS_H)
#define TOOLBOX_FORTRANARRAYS_H
// -*- C++ -*-
//
// Package:     ToolBox
// Module:      FortranArrays
// 
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
//
// Author:      Chris D. Jones
// Created:     Fri Jun 26 16:33:10 EDT 1998
// $Id: TBFortranArrays.h,v 1.4 1998/07/29 16:39:06 cdj Exp $
//
// Revision history
//
// $Log: TBFortranArrays.h,v $
// Revision 1.4  1998/07/29 16:39:06  cdj
// implemented work around for bug in g++ 2.7.2
//
// Revision 1.3  1998/07/16 13:36:46  cdj
// fixed typo
//
// Revision 1.2  1998/06/29 22:41:15  cdj
// added classes to handle Fortran Arrays with a first index other than 1
//
// Revision 1.1  1998/06/26 21:28:53  cdj
// templated classes to make it easy to access Fortran arrays
//

// system include files

// user include files

// forward declarations
template< class T, int FirstIndex, int LastIndex >
class TBFortranArrayBounded
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      enum { 
#if !defined(__GNUG__) /* g++ 2.7.2 crashes if FirstIndex is negative */
	 kFirstIndex = FirstIndex, 
	 kLastIndex  = LastIndex,
#endif
	 kSize       = LastIndex - FirstIndex + 1 };

      // Constructors and destructor

      // member functions
      T& operator()( int iIndex ) { 
	 return m_array[ fortran2cIndex( iIndex ) ] ; }

      T* cArray() { return m_array; };

      // const member functions
      T operator()( int iIndex ) const {
	 return m_array[ fortran2cIndex( iIndex ) ] ; }

      const T* cArray() const { return m_array; }

      // static member functions
      static int maxSize() { return kSize; } 
      static int minFirstIndex() { return FirstIndex; }
      static int maxLastIndex() { return LastIndex; }

   private:
      // Constructors and destructor
      //FortranArrays( const FortranArrays& );

      // assignment operator(s)
      //const FortranArrays& operator=( const FortranArrays& );

      // private member functions

      // private const member functions
      int fortran2cIndex( int iIndex ) const {
	 return iIndex -  minFirstIndex() ; }

      // data members
      T m_array[ kSize ];

      // static data members

};


template< class T, int LastIndex >
class TBFortranArray : public TBFortranArrayBounded< T, 1, LastIndex >
{
} ;


template< class T, int FirstIndex1, int LastIndex1,
                   int FirstIndex2, int LastIndex2 >
class TBFortran2DArrayBounded
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      enum { kFirstIndex1 = FirstIndex1,
             kLastIndex1  = LastIndex1,
	     kSize1       = LastIndex1 - FirstIndex1 + 1,
             kFirstIndex2 = FirstIndex2,
             kLastIndex2  = LastIndex2,
             kSize2       = LastIndex2 - FirstIndex2 + 1,
	     kMaxSize     = kSize1 * kSize2
      };

      // Constructors and destructor
      
      // member functions
      T& operator()( int iIndex1, int iIndex2 ) {
	 return m_array[  fortran2cIndex( iIndex1, iIndex2 ) ] ; }

      T* cArray() { return m_array; };

      // const member functions
      T operator()( int iIndex1, int iIndex2 ) const {
	 return m_array[  fortran2cIndex( iIndex1, iIndex2 ) ]; }
      
      const T* cArray() const { return m_array; }
      
      // static member functions
      static int maxSize() { return kMaxSize; } 
      static int minFirstIndex1() { return kFirstIndex1; }
      static int maxLastIndex1() { return kLastIndex1; }
      static int minFirstIndex2() { return kFirstIndex2; }
      static int maxLastIndex2() { return kLastIndex2; }
      
   private:
      // Constructors and destructor
      //FortranArrays( const FortranArrays& );

      // assignment operator(s)
      //const FortranArrays& operator=( const FortranArrays& );

      // private member functions
      int fortran2cIndex( int iIndex1, int iIndex2 ) const {
	 return (        (iIndex1 - FirstIndex1) + 
		  kSize1*(iIndex2 - FirstIndex2) ); }

      // private const member functions

      // data members
      T m_array[ kMaxSize ];

      // static data members
      
};

template< class T, int Size1, int Size2 >
class TBFortran2DArray : 
   public TBFortran2DArrayBounded< T, 1, Size1, 1, Size2 >
{
};


template< class T, int FirstIndex1, int LastIndex1,
                   int FirstIndex2, int LastIndex2,
                   int FirstIndex3, int LastIndex3 >
class TBFortran3DArrayBounded
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      enum { kFirstIndex1 = FirstIndex1,
             kLastIndex1  = LastIndex1,
	     kSize1       = LastIndex1 - FirstIndex1 + 1,
             kFirstIndex2 = FirstIndex2,
             kLastIndex2  = LastIndex2,
             kSize2       = LastIndex2 - FirstIndex2 + 1,
             kFirstIndex3 = FirstIndex3,
             kLastIndex3  = LastIndex3,
             kSize3       = LastIndex3 - FirstIndex3 + 1,
	     kMaxSize     = kSize1*kSize2*kSize3
      };

      // Constructors and destructor

      // member functions
      T& operator()( int iIndex1, int iIndex2, int iIndex3 ) {
	 return m_array[  fortran2cIndex( iIndex1, 
					  iIndex2,
					  iIndex3 ) ] ; }

      T* cArray() { return m_array; };

      // const member functions
      T operator()( int iIndex1, int iIndex2, int iIndex3 ) const {
	 return m_array[  fortran2cIndex( iIndex1, 
					  iIndex2,
					  iIndex3 ) ]; }

      const T* cArray() const { return m_array; }

      // static member functions
      static int maxSize()        { return kMaxSize; } 
      static int minFirstIndex1() { return FirstIndex1; }
      static int maxLastIndex1()  { return LastIndex1; }
      static int minFirstIndex2() { return FirstIndex2; }
      static int maxLastIndex2()  { return LastIndex2; }
      static int minFirstIndex3() { return FirstIndex3; }
      static int maxLastIndex3()  { return LastIndex3; }
      
   private:
      // Constructors and destructor
      //FortranArrays( const FortranArrays& );

      // assignment operator(s)
      //const FortranArrays& operator=( const FortranArrays& );

      // private member functions
      int fortran2cIndex( int iIndex1, 
			  int iIndex2,
			  int iIndex3 ) const {
	 return ( (iIndex1 - FirstIndex1) + 
		  (iIndex2 - FirstIndex2)*kSize1 +
	          (iIndex3 - FirstIndex3)*kSize1*kSize2 ); }

      // private const member functions

      // data members
      T m_array[ kMaxSize ];

      // static data members

};

template< class T, int Size1, int Size2, int Size3 >
class TBFortran3DArray : public TBFortran3DArrayBounded< T, 1, Size1, 
			                                    1, Size2,
			                                    1, Size3 >
{
};


template< class T, int FirstIndex1, int LastIndex1,
                   int FirstIndex2, int LastIndex2,
                   int FirstIndex3, int LastIndex3,
                   int FirstIndex4, int LastIndex4 >
class TBFortran4DArrayBounded
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      enum { kFirstIndex1 = FirstIndex1,
             kLastIndex1  = LastIndex1,
	     kSize1       = LastIndex1 - FirstIndex1 + 1,
             kFirstIndex2 = FirstIndex2,
             kLastIndex2  = LastIndex2,
             kSize2       = LastIndex2 - FirstIndex2 + 1,
             kFirstIndex3 = FirstIndex3,
             kLastIndex3  = LastIndex3,
             kSize3       = LastIndex3 - FirstIndex3 + 1,
             kFirstIndex4 = FirstIndex4,
             kLastIndex4  = LastIndex4,
             kSize4       = LastIndex4 - FirstIndex4 + 1,
	     kMaxSize     = kSize1*kSize2*kSize3*kSize4
      };

      // Constructors and destructor

      // member functions
      T& operator()( int iIndex1, 
		     int iIndex2, 
		     int iIndex3,
		     int iIndex4 ) {
	 return m_array[  fortran2cIndex( iIndex1, 
					  iIndex2,
					  iIndex3,
					  iIndex4 ) ] ; }

      T* cArray() { return m_array; };

      // const member functions
      T operator()( int iIndex1, 
		    int iIndex2, 
		    int iIndex3,
		    int iIndex4 ) const {
	 return m_array[  fortran2cIndex( iIndex1, 
					  iIndex2,
					  iIndex3,
					  iIndex4 ) ]; }

      const T* cArray() const { return m_array; }

      // static member functions
      static int maxSize()        { return kMaxSize; } 
      static int minFirstIndex1() { return FirstIndex1; }
      static int maxLastIndex1()  { return LastIndex1; }
      static int minFirstIndex2() { return FirstIndex2; }
      static int maxLastIndex2()  { return LastIndex2; }
      static int minFirstIndex3() { return FirstIndex3; }
      static int maxLastIndex3()  { return LastIndex3; }
      static int minFirstIndex4() { return FirstIndex4; }
      static int maxLastIndex4()  { return LastIndex4; }
      
   private:
      // Constructors and destructor
      //FortranArrays( const FortranArrays& );

      // assignment operator(s)
      //const FortranArrays& operator=( const FortranArrays& );

      // private member functions
      int fortran2cIndex( int iIndex1, 
			  int iIndex2,
			  int iIndex3,
			  int iIndex4 ) const {
	 return ( (iIndex1 - FirstIndex1) + 
		  (iIndex2 - FirstIndex2)*kSize1 +
	          (iIndex3 - FirstIndex3)*kSize1*kSize2 +
	          (iIndex4 - FirstIndex4)*kSize1*kSize2*kSize3 ); }

      // private const member functions

      // data members
      T m_array[ kMaxSize ];

      // static data members

};

template< class T, int Size1, int Size2, int Size3, int Size4 >
class TBFortran4DArray : public TBFortran4DArrayBounded< T, 1, Size1, 
			                                    1, Size2,
			                                    1, Size3,
			                                    1, Size4 >
{
};
#endif /* TOOLBOX_FORTRANARRAYS_H */
