#if !defined(HETEROCONTAINER_HCTYPETAG_H)
#define HETEROCONTAINER_HCTYPETAG_H
// -*- C++ -*-
//
// Package:     HeteroContainer
// Module:      HCTypeTag
// 
// Description: Base class for Tags that can specify a class Type.
//
// Usage:
//    This class is used in conjunction with KCTypeTagTemplate to specify
//    the class Type of another class.
//    To build a TypeTag you must initialize the correct KCTypeTagTemplate
//
//    Example
//       //Make a TypeTag for class Foo
//       HCTypeTag< MyGroup > fooTag = HCTypeTagTemplate< Foo, MyGroup >(); 
//
// Author:      Chris D. Jones
// Created:     Sun Sep 20 15:05:10 EDT 1998
// $Id: HCTypeTag.h,v 1.2 2000/07/25 13:42:34 cdj Exp $
//
// Revision history
//
// $Log: HCTypeTag.h,v $
// Revision 1.2  2000/07/25 13:42:34  cdj
// HCTypeTag can now find a TypeTag from the name of a type
//
// Revision 1.1.1.1  1998/09/23 14:13:12  cdj
// first submission
//

// system include files
#include <string>

// user include files

// forward declarations

template< class Group >
class HCTypeTag
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum { kDefaultValue = 0 };

      // ---------- Constructors and destructor ----------------
      HCTypeTag() : m_value( kDefaultValue ), m_name(0) {}
      //virtual ~HCTypeTag();  

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      unsigned int value() const { return m_value; }
      const char*  name() const { return m_name; }

      DABoolean operator==( const HCTypeTag< Group >& iRHS ) const {
	 return m_value == iRHS.m_value; }
      DABoolean operator!=( const HCTypeTag< Group >& iRHS ) const {
	 return m_value != iRHS.m_value; }
      DABoolean operator<( const HCTypeTag< Group >& iRHS ) const {
	 return m_value < iRHS.m_value; }
      DABoolean operator<=( const HCTypeTag< Group >& iRHS ) const {
	 return m_value <= iRHS.m_value; }
      DABoolean operator>( const HCTypeTag< Group >& iRHS ) const {
	 return m_value > iRHS.m_value; }
      DABoolean operator>=( const HCTypeTag< Group >& iRHS ) const {
	 return m_value >= iRHS.m_value; }

      ///find a type based on the types name, if not found will return default HCTypeTag
      static HCTypeTag<Group> findType( const std::string& iTypeName );
   protected:
      // ---------- protected member functions -----------------
      HCTypeTag( unsigned int iValue, const char* iName ) :
	 m_value( iValue ), m_name( iName ) {}

      // ---------- protected const member functions -----------

      // ---------- protected static member functions ----------
      static unsigned int nextValue(const char* iTypeName);

   private:
      // ---------- Constructors and destructor ----------------
      //HCTypeTag( const HCTypeTag& ); // use default

      // ---------- assignment operator(s) ---------------------
      //const HCTypeTag& operator=( const HCTypeTag& ); // use default


      // ---------- data members -------------------------------
      unsigned int m_value;
      const char*  m_name;


};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "HeteroContainer/Template/HCTypeTag.cc"
//#endif

#endif /* HETEROCONTAINER_HCTYPETAG_H */
