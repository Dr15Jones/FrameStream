#if !defined(PACKAGE_SMPTRHOLDER_H)
#define PACKAGE_SMPTRHOLDER_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      SMPtrHolder
// 
/**\class SMPtrHolder SMPtrHolder.h StorageManagement/SMPtrHolder.h

 Description: SMPtrHolder designed to store a pointer which
              can be zero. For StorageManagement it looks like
              a container. CDJ's idea.

 Usage:
    <usage>

*/
//
// Author:      Konstantin Bukin
// Created:     Mon Oct 23 19:00:01 EDT 2000
// $Id: SMPtrHolder.h,v 1.3 2000/11/03 21:39:25 cdj Exp $
//
// Revision history
//
// $Log: SMPtrHolder.h,v $
// Revision 1.3  2000/11/03 21:39:25  cdj
// simplified design of SMPtrHolder
//
// Revision 1.2  2000/11/01 07:09:42  kbukin
// fix missing declaration of operator>>( SMSourceStream& , SMPtrHolder<T,C>& )
//
// Revision 1.1  2000/11/01 02:21:06  kbukin
// added T_vector_UInt8_helper.cc and added SMPtrHolder with it's storage helper
//

// system include files
#define DO_EQUAL_INSTANTIATION

#include "ToolBox/TBDerefItr.h"
#include <vector>

// user include files

// forward declarations
#include "STLUtility/fwd_vector.h"

template<class T_Ptr, class T_valueType>
class SMPtrHolder
{
      // ---------- friend classes and functions ---------------
      typedef SMPtrHolder<T_Ptr, T_valueType> self;
     
   public:
      // ---------- constants, enums and typedefs --------------
      typedef T_valueType  value_type;
      typedef T_Ptr        pointer_type;
      typedef const T_valueType& const_reference;
      
      typedef TBDerefItr<T_valueType* const*,T_valueType,T_valueType> const_iterator;
      // ---------- Constructors and destructor ----------------
      
      SMPtrHolder(const pointer_type iPointer) : m_pointer(iPointer) {}
      SMPtrHolder() : m_pointer(0) {}
      //SMPtrHolder( const self& );
      
      //virtual ~SMPtrHolder();
      
      // ---------- member functions ---------------------------
      const self& operator=( const self& iRHS) {
	 m_pointer = iRHS.m_pointer; return *this; }
      
      void eraseAll() { m_pointer=0;}
      
      void setPointer( pointer_type iPointer ) { m_pointer = iPointer; }

      // ---------- const member functions ---------------------
      
      DABoolean operator==(const self& iRHS) const {
	 return (m_pointer == iRHS.m_pointer); }
      DABoolean operator!=(const self& iRHS ) const {
	 return (m_pointer != iRHS.m_pointer); }
      
      
      pointer_type pointer() const { return m_pointer; }
      
     DABoolean empty() const{ return ( 0 == m_pointer); }

      const_iterator begin() const { return &m_pointer; }
      const_iterator end() const { return 
				      (0 == m_pointer) ? 
				      &m_pointer : (&m_pointer)+1; }

     // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
     pointer_type m_pointer;

      // ---------- static data members ------------------------

};


#define INSTANTIATE_SMPTRHOLDER( _ptr_, _var_ ) \
typedef SMPtrHolder<_ptr_ , _var_> _one_element_; \
HCTYPETAGTEMPLATE_CLASSNAME_1_COMMA( SMPtrHolder<_ptr_,_var_>, DataKey )

//typedef SMPtrHolder<_ptr_ , _var_> _instantiate_one_type_ ; \

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/SMPtrHolder.cc"
//#endif

#endif /* PACKAGE_SMPTRHOLDER_H */
