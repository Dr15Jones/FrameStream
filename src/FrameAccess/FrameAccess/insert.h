#if !defined(FRAMEACCESS_INSERTOR_H)
#define FRAMEACCESS_INSERTOR_H
// -*- C++ -*-
//
// Package:     <FrameAccess>
// Module:      insert
// 
// Description: Template for standard insert
//
// Usage: There are different ways of calling insert function:
//        1.) insert( record, value, useLabel, producerLabel );
//        2.) insert( record, value, useLabel, *this ); --> not implemented
//              // the *this pointer is the Producer in which you call insert
//
// Author:      Martin Lohner
// Created:     Wed Dec  3 10:52:26 EST 1997
// $Id: insert.h,v 1.6 1998/05/07 19:45:34 mkl Exp $
//
// Revision history
//
// $Log: insert.h,v $
// Revision 1.6  1998/05/07 19:45:34  mkl
// check for null labels
//
// Revision 1.5  1998/05/07 19:12:17  mkl
// support insertion without user and/or producer label
//
// Revision 1.4  1997/12/20 20:04:18  cleo3
// now use Producer label for insert/extract
//
// Revision 1.3  1997/12/16 22:32:34  mkl
// fixes to insert function
//
// Revision 1.2  1997/12/12 21:04:50  mkl
// changed const*const to const* for extract and insert labels -- why necessary to get working?
//
// Revision 1.1  1997/12/11 23:11:01  mkl
// new files insert and ValueProxy
//

// system include files

// user include files

// forward declarations
class Frame;
class Producer;

// There are two versions of the insert function below. All cases 
// pass the value "by value", making a copy of the object!

// The insert function forces you to specify:
// 1.) the use label
// 2.) the provider which produced this value
template < class DataType > 
DABoolean insert( Frame& aFrame,
		  const DataType* aValue,
		  const char* aUseLabel,
		  const char* aProducerLabel );

#if 0 /* not used at the moment because of dependencies due to Producer */
//
// The following insert function passes in the Producer and gets 
// access to the producer name as the label through that.
// People would call this in their code as:
// insert( record, value, *this ); 
// (have to find smarter way to avoid explicit passing of *this
template < class DataType > 
DABoolean insert( Frame& aFrame,
		  const DataType* aValue,
		  const char* aUseLabel, 
		  const Producer& producer ) ;
#endif /* not used */


#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// function definitions
# include "FrameAccess/Template/insert.cc"
#endif

#endif /* FRAMEACCESS_INSERTOR_H */
