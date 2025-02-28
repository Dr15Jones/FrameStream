#if !defined(STORAGEMANAGEMENT_SMPACKINFO_H)
#define STORAGEMANAGEMENT_SMPACKINFO_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMPackInfo
// 
/**\class SMPackInfo SMPackInfo.h StorageManagement/SMPackInfo.h

 Description: Holds the packing information provided by the user in her 
              StorageHelper store method.

 Usage:
    The user would not create an instance of this class, but would instead
    normally create on of its child classes, where the child specifies
    what type of packing strategy to use and what type is being compressed

*/
//
// Author:      Chris D Jones
// Created:     Wed Oct 27 10:50:22 EDT 1999
// $Id: SMPackInfo.h,v 1.7 2002/08/08 20:54:16 cdj Exp $
//
// Revision history
//
// $Log: SMPackInfo.h,v $
// Revision 1.7  2002/08/08 20:54:16  cdj
// replaced inappropriate use of reinterpret_cast with static_cast
//
// Revision 1.6  2000/09/24 16:12:37  cdj
// added ContainerSize strategy
//
// Revision 1.5  2000/05/16 15:22:38  mkl
// new StorageManagement builtin container vs other flag
//
// Revision 1.4  2000/01/24 22:35:21  cdj
// exposed run time type info
//
// Revision 1.3  2000/01/05 16:29:56  cdj
// worked around a bug on Solaris that has to do with static variables in a template class's static function
//
// Revision 1.2  1999/11/24 12:06:19  cdj
// fixed typo in code example in SMPackInfo.h
//
// Revision 1.1  1999/11/03 17:53:47  cdj
// added compression hints code
//

// system include files
#include <assert.h>

// user include files
#include "StorageManagement/SMSinkStream.h"

// forward declarations
class SMFieldBase;

class SMPackInfo
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum Strategy { kNoPacking, 
		      kFixed,
		      kFractional,
		      kContainerSize
      };
      enum DataType { kUnknown=0 };

      // ---------- Constructors and destructor ----------------
      SMPackInfo() : m_field(0), m_type(kUnknown), m_strategy(kNoPacking) {}

      //virtual ~SMPackInfo();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void setupPack( SMSinkStream& iSink ) const {
	 iSink.setPackInfo( *this );
	 iSink << *m_field;
	 iSink.unsetPackInfo();
      }

      Strategy strategy() const { return m_strategy; }

      const char* strategyName() const {
	 return (strategyNames())[ m_strategy ]; }

      unsigned int fieldType() const { return m_type; }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      SMPackInfo( const SMFieldBase& iField,
		  unsigned int iType,
		  Strategy iStrategy ) 
	 : m_field( &iField ),
	   m_type( iType ),
	   m_strategy(iStrategy ) {}

      // ---------- protected const member functions -----------
      const SMFieldBase* field() const {return m_field;}

      static unsigned int nextType() {
	 static unsigned int typeValue = kUnknown;
	 return ++typeValue; }

   private:
      // ---------- Constructors and destructor ----------------
      //SMPackInfo( const SMPackInfo& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMPackInfo& operator=( const SMPackInfo& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static const char** strategyNames() {
	 const char* names[] = { "no packing",
				 "fixed",
				 "fractional",
				 "container size"
	 };
	 return names;
      }

      // ---------- data members -------------------------------
      const SMFieldBase* m_field;
      unsigned int m_type;
      Strategy m_strategy;

      // ---------- static data members ------------------------

};

// inheriting classes
/**\class SMPackInfoFixedTemplate SMPackInfo.h StorageManagement/SMPackInfo.h

 Description: Holds the packing information necessary to pack a type using
              fixed precision packing

 Usage:
    Normally, one would not create a SMPackInfoFixedTemplate directly, instead
    one would use the templated helper function sm_pack.
    \code
        //want to pack data for object iData which as two fields 
	//  'int_value' which has min value 10, max value 382 and 
        //              precision of 2
        // 'float_value' which has min -0.45, max 129.0, precision 0.02
	iSinkStream << sm_pack( SM_VAR( iData, int_value ), 10, 382, 2)
	            << sm_pack( SM_VAR( iData, float_value ), -0.45, 129, 0.02);
    \endcode
    The three parameters needed to pack the data are
      min : the minimum value that the field can hold
      max : the maximum value that the field can hold
      precision : the precision of the value that should be kept.  This
                  translates into the smallest allowed difference between
                  two measurably different values of the field.

*/
template <class T >
class SMPackInfoFixedTemplate : public SMPackInfo
{
   public:
      SMPackInfoFixedTemplate( const SMFieldBase& iField,
				  T iMin, T iMax, T iPrec ) :
	 SMPackInfo(iField, classFieldType(), SMPackInfo::kFixed ),
	 m_min(iMin),
	 m_max(iMax),
	 m_precision( iPrec ) {}

      ///checks to make sure that iInfo is the correct type
      SMPackInfoFixedTemplate( const SMPackInfo& iInfo ) :
	 SMPackInfo( iInfo ) {
	    assert( strategy() == SMPackInfo::kFixed );
	    assert( fieldType() == classFieldType() );
	    const SMPackInfoFixedTemplate<T>* temp = 
	       static_cast<const SMPackInfoFixedTemplate<T>*>(&iInfo);
	    m_min = temp->min();
	    m_max = temp->max();
	    m_precision = temp->precision();
      }

      T min() const { return m_min; }
      T max() const { return m_max; }
      T precision() const { return m_precision; }

      static unsigned int classFieldType() ;

   private:

      T m_min;
      T m_max;
      T m_precision;
};

/**\class SMPackInfoFractionalTemplate SMPackInfo.h StorageManagement/SMPackInfo.h

 Description: Holds the packing information necessary to pack a type using
              fractional precision packing

 Usage:
    Normally, one would not create a SMPackInfoFractionalTemplate directly, 
    instead one would use the templated helper function sm_pack_fraction.
    \code
        //want to pack data for object iData which as a field 
        // 'float_value' which has smallest absolute value 1.0*10^-5, 
	//                         max value 2.3*10^12,
	//                         and accuracy as a fraction of the value of
	//                             0.003
	iSinkStream << sm_pack_fraction( SM_VAR( iData, float_value ), 
	                                 1.0e-5, 2.3e12, 0.003);
    \endcode
    The three parameters needed to pack the data are
      min : the smallest absolute value that the field can hold
      max : the maximum value that the field can hold
      fraction : the accuracy of the measurement which is measured as a 
                 fraction of the value of the measurement.

*/
template <class T >
class SMPackInfoFractionalTemplate : public SMPackInfo
{
   public:
      SMPackInfoFractionalTemplate( const SMFieldBase& iField,
				    T iMin, T iMax, float iFraction ) :
	 SMPackInfo(iField, classFieldType(), SMPackInfo::kFractional ),
	 m_min(iMin),
	 m_max(iMax),
	 m_fraction( iFraction ) {}
      
      ///checks to make sure that iInfo is the correct type
      SMPackInfoFractionalTemplate( const SMPackInfo& iInfo ) :
	 SMPackInfo( iInfo ) {
	    assert( strategy() == SMPackInfo::kFractional );
	    assert( fieldType() == classFieldType() );
	    const SMPackInfoFractionalTemplate<T>* temp = 
	       static_cast<const SMPackInfoFractionalTemplate<T>*>(&iInfo);
	    m_min = temp->min();
	    m_max = temp->max();
	    m_fraction = temp->fraction();
      }

      T min() const { return m_min; }
      T max() const { return m_max; }
      float fraction() const { return m_fraction; }

      static unsigned int classFieldType() ;

   private:

      T m_min;
      T m_max;
      float m_fraction;
};

// inline function definitions

inline
SMSinkStream&
operator<<( SMSinkStream& iSink, const SMPackInfo& iPackInfo ) {
   iPackInfo.setupPack( iSink );
   return iSink;
}

# if defined(TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG)
//This class is needed for compilers that do not properly handle
// typedefs from Template arguments used in return values
template<class T>
class SMPackInfoFixedTemplateFix : 
   public SMPackInfoFixedTemplate< typename T::field_type >
{
   public:
      SMPackInfoFixedTemplateFix( 
	 const SMPackInfoFixedTemplate< typename T::field_type >& iInfo )
	 :
	 SMPackInfoFixedTemplate< typename T::field_type >( iInfo ) {}
};

template<class T>
class SMPackInfoFractionalTemplateFix : 
   public SMPackInfoFractionalTemplate< typename T::field_type >
{
   public:
      SMPackInfoFractionalTemplateFix(
	 const SMPackInfoFractionalTemplate<typename T::field_type>& iInfo ):
	 SMPackInfoFractionalTemplate< typename T::field_type >( iInfo ) {}
};
#endif

/**Note need template arguments T1-T3 because the number 1 is an int not
   an unsigned int so we can only figure out the type from SMField<T>
 */
template<class FieldT, class T1, class T2, class T3>
inline
# if !defined(TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG)
SMPackInfoFixedTemplate<typename FieldT::field_type > 
#else
SMPackInfoFixedTemplateFix<FieldT> 
#endif
sm_pack( const FieldT& iField, 
	 T1 iMin, T2 iMax, T3 iStep ) {
   typedef typename FieldT::field_type T ;
   return SMPackInfoFixedTemplate<T>
      (iField, T(iMin), T(iMax), T(iStep) );
}

template<class FieldT, class T1, class T2 >
inline
# if !defined(TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG)
SMPackInfoFractionalTemplate< typename FieldT::field_type > 
#else
SMPackInfoFractionalTemplateFix< FieldT > 
#endif
sm_pack_fraction( const FieldT& iField,
		  T1 iMin, T2 iMax, float iFraction ) {
   typedef typename FieldT::field_type T;
   return SMPackInfoFractionalTemplate<T>(iField,
					  T(iMin), T(iMax), iFraction );
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMPackInfo.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPACKINFO_H */
