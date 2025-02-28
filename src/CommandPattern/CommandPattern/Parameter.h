#if !defined(COMMANDPATTERN_PARAMETER_H)
#define COMMANDPATTERN_PARAMETER_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Parameter
// 
// Description: templated Parameter class
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Jan 28 15:55:03 EST 1998
// $Id: Parameter.h,v 1.10 2003/02/13 21:03:28 ajm36 Exp $
//
// Revision history at end of file
//

// system include files
#include <assert.h>

// user include files
#include "CommandPattern/ParameterBase.h"

// forward declarations

template< class T >
class Parameter : public ParameterBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      class ParameterChangeCallBack : public ParameterChangeCallBackBase {
	 public:
	    ParameterChangeCallBack() : m_parmP( 0 ) {}

	    // to be overwritten
	    virtual DABoolean operator()() = 0; 

	    // built in
	    void setParameter( Parameter< T >* iParameter ) { 
	       m_parmP = iParameter; 
	    }
	    const T& value() const { 
	       assert( m_parmP!=0 ); return m_parmP->value(); 
	    }
	 private:
	    Parameter< T >* m_parmP;
      };

      // ---------- Constructors and destructor ----------------
      // ctor with default value
      Parameter( const Name& iName,
		 Module* iTarget,
		 const T& defaultValue );
      // and without default value
      Parameter( const Name& iName,
		 Module* iTarget );
      virtual ~Parameter();
      
      // ---------- member functions ---------------------------
      void setDefault( const T& iDefault );

      // install call back for parameter changes
      void setParameterChangeCallBack( ParameterChangeCallBack* iCallBack );

      // ---------- const member functions ---------------------
      virtual const T& value() const;

      // ---------- static member functions --------------------
      virtual const char* typeName();

   protected:
      // ---------- protected member functions -----------------
      virtual int implementSetHandler(); // called by ParameterBase::setHandler
      virtual int implementSetDefaultHandler(); // "
      virtual int listHandler();         // used by template execute method

      virtual void setValue( T& value );    // formatting routine

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Parameter( const Parameter& );  // stop default

      // ---------- assignment operator(s) ---------------------
      const Parameter& operator=( const Parameter& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      T& m_value;
      T& m_defaultValue;

      // ---------- static data members ------------------------

};

// c preprocessor macros

// easy way to custom build the typeName method
#define PARAMETER_TYPENAME( Tname ) \
template <> \
const char* \
Parameter< Tname >::typeName() \
{ return #Tname ; }

// define macro for convenience
#define INSTANTIATE_PARAMETER( T ) \
PARAMETER_TYPENAME( T ) \
template class Parameter< T >;

// inline function definitions

#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
# include "CommandPattern/Template/Parameter.cc"
#endif

// ----------------------------------------------------------------------
// Revision history
//
// $Log: Parameter.h,v $
// Revision 1.10  2003/02/13 21:03:28  ajm36
// parameters now return their value to tcl when they are changed or checked
//
// Revision 1.9  2000/08/04 15:15:09  mkl
// call-back function now returns DABoolean (if false, value gets reset to default)
//
// Revision 1.8  2000/08/03 22:05:26  mkl
// parameters now have optional call-back mechanism
//
// Revision 1.7  2000/05/12 15:44:12  mkl
// reorder instantiation directives for Parameter of vector of T to have className directive first
//
// Revision 1.6  2000/01/04 20:53:30  mkl
// now print type with parameter value
//
// Revision 1.5  1998/11/09 19:31:42  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.4  1998/03/31 22:48:04  cdj
// includes Parameter.cc if INCLUDE_TEMPLATE_DEFINITIONS is set
//
// Revision 1.3  1998/03/15 00:08:13  mkl
// Parameter< vector< T > >
//
// Revision 1.2  1998/03/14 01:52:58  mkl
// added default value
//
// Revision 1.1  1998/03/11 19:10:39  mkl
// new Parameter sources
//

#endif /* COMMANDPATTERN_PARAMETER_H */
