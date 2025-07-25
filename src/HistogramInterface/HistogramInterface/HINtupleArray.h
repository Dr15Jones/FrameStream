#if !defined(PACKAGE_HINTUPLEARRAY_H)
#define PACKAGE_HINTUPLEARRAY_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      HINtupleArray
// 
/**\class HINtupleArray HINtupleArray.h package/HINtupleArray.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Aug 27 14:36:40 EDT 2001
// $Id: HINtupleArray.h,v 1.5 2003/03/04 00:16:38 cleo3 Exp $
//
// Revision history
//
// $Log: HINtupleArray.h,v $
// Revision 1.5  2003/03/04 00:16:38  cleo3
// only instantiate bitset if using no implicit instantiation
//
// Revision 1.4  2002/06/04 19:42:34  cleo3
// added typename needed for CC 5.3
//
// Revision 1.3  2001/12/17 19:33:41  ajm36
// add another ctor to HINtupleArray, allow default copy ctor
//
// Revision 1.2  2001/09/15 11:52:43  tom
// Fixed typo in 2nd ctor: itValues --> itValue now.
//
// Revision 1.1  2001/08/28 15:18:01  cdj
// first submission
//

// system include files
#include <assert.h>
#include <string.h>
#include <bitset>

// user include files
#include "HistogramInterface/HINtuple.h"
#include "Experiment/report.h"

// forward declarations

template< unsigned int ISize>
class HINtupleArray
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      HINtupleArray() {}
      HINtupleArray( float iInitialValue)
      {
         for( float* itValue = m_values;
              itValue != m_values + ISize;
              ++itValue ) 
         {
            *itValue = iInitialValue;
         }
         m_setValues.set();
      }

      HINtupleArray( const float* iBegin, const float* iEnd){
         assert(ISize == (iEnd - iBegin));
         memcpy(m_values, iBegin, ISize*sizeof(float)/sizeof(char));
         m_setValues.set();
      }
      //virtual ~HINtupleArray();

      // ---------- member functions ---------------------------
      class reference {
            typename bitset<ISize>::reference m_setValue;
            float& m_value;
         public:
            reference(float& iValue, 
                      typename bitset<ISize>::reference iSetValue ) :
               m_setValue(iSetValue), m_value(iValue) {}
               
            float& operator=( float iValue ) {
               m_value = iValue;
               m_setValue = true;
               return m_value;
            }
            float& operator+=( float iValue ) {
               return m_value += iValue;
            }
            float& operator-=( float iValue ) {
               return m_value -= iValue;
            }
            float& operator*=( float iValue ) {
               return m_value *= iValue;
            }
            float& operator/=( float iValue ) {
               return m_value /= iValue;
            }

            operator float&() const { return m_value; }
      };

      reference operator[](unsigned int iIndex) {
            assert(iIndex < ISize);
            return reference(m_values[iIndex], m_setValues[iIndex] ); 
      }
      
      float* begin() { return m_values;}
      float* end() { return m_values+ISize; }

      // ---------- const member functions ---------------------
      float operator[](unsigned int iIndex) const
      { assert(iIndex <ISize); return m_values[iIndex]; }

      void fill( HINtuple* iNtuple ) {
         bool allValuesHaveBeenSet = (m_setValues.count() == m_setValues.size());
         if ( ! allValuesHaveBeenSet ) {
           std::ostream& myReport = report(EMERGENCY, "HistogramInterface.HINtupleArray");
             myReport <<
               "not all values have been set before trying to fill Ntuple\n  "
               <<iNtuple->title()
               <<" unset indicies are\n";
               for( unsigned int index = 0; index != ISize; ++index) {
                  if(!m_setValues.test(index) ) {
                     myReport << iNtuple->labels()[index];
                  }
               }
               myReport<<std::endl;
            assert(allValuesHaveBeenSet );
         }
         iNtuple->fill(m_values);
      }

      const float* begin() const { return m_values;}
      const float* end() const { return m_values+ISize; }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //HINtupleArray( const HINtupleArray& ); // allow default

      // ---------- assignment operator(s) ---------------------
      const HINtupleArray& operator=( const HINtupleArray& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      float m_values[ISize];
      bitset<ISize> m_setValues;
};

#if defined(NO_IMPLICIT_INSTANTIATION)
#define CREATE_HINTUPLEARRAY(_array_size_) template class bitset<_array_size_>;
#else 
#define CREATE_HINTUPLEARRAY(_array_size_)
#endif

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/HINtupleArray.cc"
//#endif

#endif /* PACKAGE_HINTUPLEARRAY_H */
