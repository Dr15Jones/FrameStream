#if !defined(INTERACTIVEDELIVERY_INTERACTIVESOURCEBINDER_H)
#define INTERACTIVEDELIVERY_INTERACTIVESOURCEBINDER_H
// -*- C++ -*-
//
// Package:     InteractiveDelivery
// Module:      InteractiveSourceBinder
// 
// Description: Binds an InteractiveSource to an IteractiveSourceController
//
// Usage:
//    This is used by framework developers, in conjunction with 
//    InteractiveSource, to implement 'goto run event' commands.
//    See InteractiveSource.h for more details
//
// Author:      Chris D. Jones
// Created:     Sat Apr 19 12:27:39 EDT 1997
// $Id: InteractiveSourceBinder.h,v 1.2 1997/07/09 19:22:13 sjp Exp $
//
// Revision history
//
// $Log: InteractiveSourceBinder.h,v $
// Revision 1.2  1997/07/09 19:22:13  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.1.1.1  1997/04/21 19:30:11  cdj
// First submission
//


// system include files

// user include files
#include "DataDelivery/DataSourceBinder.h"

// forward declarations
class InteractiveSource;

class InteractiveSourceBinder : public DataSourceBinder
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      InteractiveSourceBinder( InteractiveSource* iSource );

      virtual ~InteractiveSourceBinder();

      // member functions

      // const member functions
      virtual DataSourceController*
        createDataSourceController( void ) const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      InteractiveSourceBinder( const InteractiveSourceBinder& );

      // assignment operator(s)
      const InteractiveSourceBinder& operator=( const InteractiveSourceBinder& );

      // private member functions

      // private const member functions

      // data members
      InteractiveSource* m_source;

      // static data members

};

// inline function definitions

#endif /* INTERACTIVEDELIVERY_INTERACTIVESOURCEBINDER_H */
