#if !defined(STORAGEMANAGEMENT_SMTESTRETURNTYPEMATCHESVARIABLE_H)
#define STORAGEMANAGEMENT_SMTESTRETURNTYPEMATCHESVARIABLE_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      smTestReturnTypeMatchesVariable
// 
/**\class smTestReturnTypeMatchesVariable smTestReturnTypeMatchesVariable.h StorageManagement/smTestReturnTypeMatchesVariable.h

 Description: compile time check that variable matches return type of member function

 Usage:
    Call this function to do a compile time check that the type of the 
    pointer to the variable matches the return type of the member function.

    If the types do not match you will get a compile time error stating that
    the proper function could not be found.

    If the types do match, no run time penalty happens because the function
    is inlined and will be optimized away.

*/
//
// Author:      Chris D Jones
// Created:     Fri Apr  4 15:48:28 EST 2003
// $Id: smTestReturnTypeMatchesVariable.h,v 1.2 2003/04/07 15:31:27 cdj Exp $
//
// Revision history
//
// $Log: smTestReturnTypeMatchesVariable.h,v $
// Revision 1.2  2003/04/07 15:31:27  cdj
// worked around a compiler bug on Solaris 8 that caused the new type tests to always fail
//
// Revision 1.1  2003/04/04 21:34:48  cdj
// added compile time checking of data in deliver function matches type stored
//

// system include files

// user include files

// forward declarations

#if !defined(INHERITED_MEMBER_FUNCTION_ARG_IN_TEMPLATED_FUNCTION_BUG)
template<class V, class T>
inline
void smTestReturnTypeMatchesVariable( V*, V (T::*iPFunc)() const ) {}


template<class V, class T>
inline
void smTestReturnTypeMatchesVariable( V*, const V& (T::*iPFunc)() const ) {}

template<class V, class T>
inline
void smTestReturnTypeMatchesVariable( V*, const V (T::*iPFunc)() const ) {}

#else
//Make the test always pass and hope another compiler catches any problem
template<class V, class T>
inline
void smTestReturnTypeMatchesVariable( V*, T ) {}
#endif


/*
//Could use non-templated functions if all else fails
#define SM_TEST_FUNCS(_V_, _T_)  \
inline void smTestReturnTypeMatchesVariable( _V_* , _V_(_T_::*iPFunc)() const ) {} \
inline void smTestReturnTypeMatchesVariable( _V_* , const _V_&(_T_::*iPFunc)() const ) {} \
inline void smTestReturnTypeMatchesVariable( _V_* , const _V_(_T_::*iPFunc)() const ) {}
#define MAKE_SM_TEST_FUNCS(_T_) \
SM_TEST_FUNCS(char, _T_) \
SM_TEST_FUNCS(unsigned char, _T_) \
SM_TEST_FUNCS(short, _T_) \
SM_TEST_FUNCS(unsigned short, _T_) \
SM_TEST_FUNCS(int, _T_) \
SM_TEST_FUNCS(unsigned int, _T_) \
SM_TEST_FUNCS(long, _T_) \
SM_TEST_FUNCS(unsigned long, _T_) \
SM_TEST_FUNCS(float, _T_) \
SM_TEST_FUNCS(double, _T_) \
SM_TEST_FUNCS(string, _T_) 
*/

#define TEST_RETURN_TYPE(_class_, _name_) smTestReturnTypeMatchesVariable(&_name_, &_class_::_name_);

#endif /* STORAGEMANAGEMENT_SMTESTRETURNTYPEMATCHESVARIABLE_H */


