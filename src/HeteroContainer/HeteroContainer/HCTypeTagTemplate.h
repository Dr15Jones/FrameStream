#if !defined(HETEROCONTAINER_HCTYPETAGTEMPLATE_H)
#define HETEROCONTAINER_HCTYPETAGTEMPLATE_H
// -*- C++ -*-
//
// Package:     HeteroContainer
// Module:      HCTypeTagTemplate
// 
// Description: initializer class for HCTypeTag
//
// Usage:
//    See HCTypeTag.h for usage.
//
//    This templated class does NOT have a definition of the method
//    className().  Instead className() is supposed to be specialized
//    for each parameter T.  We have included a cpp macro to make it 
//    easier to do this specialization.  To use the macro simple do
//
//    #include "HeteroContainer/HCTypeTagTemplate.h"
//    HCTYPETAGTEMPLATE_CLASS( Foo, MyGroup )
//     
// Author:      Chris D. Jones
// Created:     Sun Sep 20 15:31:56 EDT 1998
// $Id: HCTypeTagTemplate.h,v 1.6 2002/06/04 18:22:45 cleo3 Exp $
//
// Revision history
//
// $Log: HCTypeTagTemplate.h,v $
// Revision 1.6  2002/06/04 18:22:45  cleo3
// use new explicit template specialization syntax
//
// Revision 1.5  2000/07/25 13:42:35  cdj
// HCTypeTag can now find a TypeTag from the name of a type
//
// Revision 1.4  1998/10/20 18:06:22  cdj
// modified so .cc file can not be multiply included
//
// Revision 1.3  1998/09/30 15:42:42  cdj
// removed inlined version of className(), now get from HCTypeTagTemplate.cc
//
// Revision 1.2  1998/09/29 18:57:01  cdj
// fixed cpp macro
//
// Revision 1.1.1.1  1998/09/23 14:13:12  cdj
// first submission
//

// system include files

// user include files
#include "HeteroContainer/HCTypeTag.h"

// forward declarations

template < class T, class Group >
class HCTypeTagTemplate : public HCTypeTag< Group >
{
   public:

      // ---------- Constructors and destructor ---------------- 
      HCTypeTagTemplate() : 
	 HCTypeTag<Group>( classValue(), className() ) {}
      //virtual ~HCTypeTagTemplate(); //not needed

      // ---------- static member functions --------------------
      static unsigned int classValue() {
	 static unsigned int theValue = nextValue( className() );
	 return theValue; }

      static const char* className();

   protected:

   private:
      // ---------- Constructors and destructor ----------------
      //HCTypeTagTemplate( const HCTypeTagTemplate& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const HCTypeTagTemplate& operator=( const HCTypeTagTemplate& ); // stop default

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "HeteroContainer/Template/HCTypeTagTemplate.cc"
//#endif

// c preprocessor macros

// easy way to custom build the className method
#define HCTYPETAGTEMPLATE_CLASSNAME( Tname, group ) \
template <> \
const char* \
HCTypeTagTemplate< Tname, group >::className() \
{ return #Tname ; }

#define HCTYPETAGTEMPLATE_CLASSNAME_1_COMMA( Tname1, Tname2, group ) \
template <> \
const char* \
HCTypeTagTemplate< Tname1,Tname2 , group >::className() \
{ return #Tname1 "," #Tname2 ; }

#endif /* HETEROCONTAINER_HCTYPETAGTEMPLATE_H */
