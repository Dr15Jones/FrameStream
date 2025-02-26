#if !defined(DATADELIVERY_CHAINABILITY_H)
#define DATADELIVERY_CHAINABILITY_H
// -*- C++ -*-
//
// Package:     <DataDelivery>
// Module:      Chainability
// 
// Description: Signals if a Source can be chained or not
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue May 12 18:33:16 EDT 1998
// $Id: Chainability.h,v 1.3 1998/11/24 22:06:23 mkl Exp $
//
// Revision history
//
// $Log: Chainability.h,v $
// Revision 1.3  1998/11/24 22:06:23  mkl
// introduce int-receiving ctor to allow for fake initialization to avoid compiler warnings
//
// Revision 1.2  1998/07/18 20:01:21  mkl
// typedef-not-in-class-namespace bug --> workaround
//
// Revision 1.1  1998/06/17 18:19:55  mkl
// allow dynamic loading of source and sink formats
//

// system include files

// user include files

// forward declarations

class NotChainable 
{
   public:
      // int-receiving ctor to allo fake initialization 
      // to 0 to avoid compiler warnings of uninitialized variables
      NotChainable( int = 0 ) {} 
};

template< class DataBinder >
class Chainable
{
   public:
      // int-receiving ctor to allo fake initialization 
      // to 0 to avoid compiler warnings of uninitialized variables
      Chainable( int = 0 ) {}

      typedef DataBinder DataBinderType;
};

// inline function definitions

#endif /* DATADELIVERY_CHAINABILITY_H */
