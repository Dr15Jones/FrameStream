// -*- C++ -*-
//
// Package:     Bug
// Module:      template_typedef_in_overloaded_member_function_of_template_bug
// 
// Description: Test for a compiler bug seen on Solaris CC v5.3
//
// Bug:
//     This compiler bug occurs when a templated class has an overloaded
//     member function, where one of the overloaded functions uses as an
//     argument a  typedef defined in another templated class AND at least one
//     of the implementations of the overloaded functions is not done
//     within the decleration of the class.
//
// Workaround:
//     Have all the overloaded functions declare their implementation within
//     the class decleration.  If the algorithms are too long to be in the
//     class decleration, define a new function with a unique name which actually
//     implements the algorithm.
//
// Author:      Chris D Jones
// Created:     Wed Aug 22 09:06:23 EDT 2001
// $Id: template_typedef_in_overloaded_member_function_of_template_bug.cc,v 1.1 2001/08/22 13:50:44 cdj Exp $
//
// Revision history
//
// $Log: template_typedef_in_overloaded_member_function_of_template_bug.cc,v $
// Revision 1.1  2001/08/22 13:50:44  cdj
// added new bug test
//

#include "Experiment/Experiment.h"

// system include files

// user include files

//templated class used as member function argument
template <class DummyT>
struct Dummy
{
      typedef DummyT* const_iterator;
};

//These defines make the class decleration more readable
#if !defined(TEMPLATE_TYPEDEF_IN_OVERLOADED_MEMBER_FUNCTION_OF_TEMPLATE_BUG)
#define REMOVE_ID(_variable_) ;
#define REMOVE_ITR(_variable_);
#else
#define REMOVE_ID(_variable_) { implementIdentifierRemove(_variable_); }
#define REMOVE_ITR(_variable_) { implementIdentifierRemove(*_variable_); }
#endif

//class that displays the problem
template <class FirstT>
class SimpleProblem
{
   public:
      void remove(typename FirstT::Identifier iID )
	 REMOVE_ID(iID)

      void remove(typename Dummy<typename FirstT::Identifier >::const_iterator iItr)
	 REMOVE_ITR(iItr)
   private:

#if defined(TEMPLATE_TYPEDEF_IN_OVERLOADED_MEMBER_FUNCTION_OF_TEMPLATE_BUG)
      //uniquely named function used as workaround for compiler bug
      void implementIdentifierRemove(typename FirstT::Identifier iID);
#endif

};

#if !defined(TEMPLATE_TYPEDEF_IN_OVERLOADED_MEMBER_FUNCTION_OF_TEMPLATE_BUG)
template<class FirstT>
void
SimpleProblem<FirstT>::remove(typename FirstT::Identifier )
{
}

template<class FirstT>
void 
SimpleProblem<FirstT>::remove(typename Dummy<typename FirstT::Identifier>::const_iterator)
{
}
#else
template<class FirstT>
void 
SimpleProblem<FirstT>::implementIdentifierRemove(typename FirstT::Identifier iID)
{
}
#endif

//Concrete classes used for template arguments
struct First
{
      typedef unsigned int Identifier;
};

//Instantiate the class
template class SimpleProblem<First>;


