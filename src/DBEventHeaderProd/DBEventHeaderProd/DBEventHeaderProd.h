#if !defined(DBEVENTHEADERPROD_DBEVENTHEADERPROD_H)
#define DBEVENTHEADERPROD_DBEVENTHEADERPROD_H
// -*- C++ -*-
//
// Package:     <DBEventHeaderProd>
// Module:      DBEventHeaderProd
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Jun  1 14:15:24 EDT 1999
// $Id: DBEventHeaderProd.h,v 1.1.1.1 1999/06/01 18:58:32 mkl Exp $
//
// Revision history
//
// $Log: DBEventHeaderProd.h,v $
// Revision 1.1.1.1  1999/06/01 18:58:32  mkl
// imported sources
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "ToolBox/HistogramPackage.h"

// forward declarations

class DBEventHeaderProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      DBEventHeaderProd( void );                      // anal1 
      virtual ~DBEventHeaderProd();                   // anal5 

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
      DBEventHeaderProd( const DBEventHeaderProd& );

      // ------------ assignment operator(s) ----------------------
      const DBEventHeaderProd& operator=( const DBEventHeaderProd& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* DBEVENTHEADERPROD_DBEVENTHEADERPROD_H */
