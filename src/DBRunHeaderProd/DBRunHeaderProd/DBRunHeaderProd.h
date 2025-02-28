// -*- C++ -*-
//
// Package:     <DBRunHeaderProd>
// Module:      DBRunHeaderProd
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Andreas Wolf
// Created:     Thu Jul 22 12:18:25 EDT 1999
// $Id: DBRunHeaderProd.h,v 1.1.1.1 1999/07/22 18:20:53 aw Exp $
//
// Revision history
//
// $Log: DBRunHeaderProd.h,v $
// Revision 1.1.1.1  1999/07/22 18:20:53  aw
// Imported initial DBRunHeaderProd sources
//
//
//
#ifndef DBRUNHEADERPROD_DBRUNHEADERPROD_H
#define DBRUNHEADERPROD_DBRUNHEADERPROD_H

// system include files

// user include files
#include "Processor/Producer.h"
#include "ToolBox/HistogramPackage.h"

// forward declarations

class DBRunHeaderProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      DBRunHeaderProd( void );                      // anal1 
      virtual ~DBRunHeaderProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( TBHistoManager& );                  

      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      DBRunHeaderProd( const DBRunHeaderProd& );

      // ------------ assignment operator(s) ----------------------
      const DBRunHeaderProd& operator=( const DBRunHeaderProd& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* DBRUNHEADERPROD_DBRUNHEADERPROD_H */
