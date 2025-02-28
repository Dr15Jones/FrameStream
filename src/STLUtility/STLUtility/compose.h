#if !defined(STLUTILITY_COMPOSE_H)
#define STLUTILITY_COMPOSE_H
// -*- C++ -*-
//
// Package:     <STLUtility>
// Module:      compose
// 
/**\class compose compose.h STLUtility/compose.h

 Description: The STL has two function object adaptors, unary_compose and
 binary_compose that are not part of the C++ standard, and hence
 neither the OSF nor the SUN STL implementations have them. Because
 they are useful, they are implimented here.

 unary_compose<Function1, Function2> is a function object adaptor. If
 f and g are adaptable unary functions, then unary_compose is used to
 pass g's result into f's argument (so long as g's result type is
 convertable to f's argument type). Effectively, this creates a new
 adaptable unary function h(x) where h(x) = f(g(x)).  Use the helper
 function, compose1 to string functions together.

 I'll add binary_compose when it's needed.

 

 Usage:

   You want to determine how many response objects each monte carlo
   particle in an event has produced. A convenient way to do this is
   to make a map, with the key as the mc track ID and the value as the
   number of responses it made. To make things as generic as possible,
   we need a function object that takes a MCDRResponse object and
   returns the associated mc track id (ParticleIdExtractor()).
   Another object takes the mc track id and increments the appropriate
   counter in its map (that it holds) (CountItems). We use the STL
   for_each function to easily loop over the FATable. for_each takes
   one function object, but we want to run two! The output of
   ParticleIdExtractor must be passed to the argument of
   CountItems. This is where unary_compose comes in. The call to
   for_each would be...

   // Construct the CountItems object
   CountItems countResponses( map_to_hold_counts );

   // Loop over the FATable, making counts
   for_each( mcDRResponses.begin(), mcDRResponses.end(),
             compose1( countResponses, ParticleIdExtractor() ) );

   Note the use of compose1 to easily make the composition of the two
   function objects. compose1 actually returns the composition object
   unary_compose<CountItems, ParticleIdExtractor>. Therefore when you
   manually instantiate for_each, you must instantiate it with
   unary_compose<Function1, Function2>, not compose1. 


 Glossary:
   unary function: A function that takes only one argument -
   f(x). In the case of a function object, its operator() takes only
   one argument.

   adaptable function: A function object that exposes its return and argument 
   types via public typdefs. See the "Generic Programming and the STL" 
   book by Austern. 

   unary_compose is an example of an adaptable unary function
   object. It's operator() takes one argument and it exposes its
   return and argument types.
 

*/
//
// Author:      Adam Lyon
// Created:     Fri Jun 29 11:59:08 EDT 2001
// $Id: compose.h,v 1.1 2001/07/02 14:54:29 lyon Exp $
//
// Revision history
//
// $Log: compose.h,v $
// Revision 1.1  2001/07/02 14:54:29  lyon
// Implement the unary_compose STL function
//

// system include files
#include <functional>

// user include files

// forward declarations


// unary_compose: Join Function1 and Function2, passing Function2's
// result to Function1's argument, creating a new unary adaptable
// function object. Both Function1 and Function2 must be adaptable unary
// function objects.
template<class Function1, class Function2>
class unary_compose : public unary_function< typename Function2::argument_type, 
                                             typename Function1::result_type >
{
  protected:

    Function1 m_f;
    Function2 m_g;

  public:

  // unary_compose is an adaptable unary function object, expose argument
  // and return types
  typedef typename unary_function< typename Function2::argument_type, 
                                   typename Function1::result_type>::argument_type argument_type;
  
  typedef typename unary_function< typename Function2::argument_type, 
                                   typename Function1::result_type>::result_type result_type;
  
  unary_compose( const Function1& f, const Function2& g) :
    m_f(f),  // makes a copy of the f function object
    m_g(g)   // makes a copy of the g function object
  {};

  // operator() -- pass g's result to f's argument and return f's result.
  result_type operator()( argument_type x )
  {
    return m_f( m_g(x) );
  };

};

// Helper function to make unary_compose easy
template <class Function1, class Function2>
inline unary_compose<Function1, Function2>
compose1(const Function1& f, const Function2& g)
{
  return unary_compose<Function1, Function2>(f, g);
}



#endif /* STLUTILITY_COMPOSE_H */
