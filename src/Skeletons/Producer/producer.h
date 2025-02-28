// -*- C++ -*-
#if !defined(PRODNAME_PRODNAME_H)
#define PRODNAME_PRODNAME_H
//
// Package:     <prodname>
// Module:      prodname
//
/**\class prodname prodname.h prodname/prodname.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "HistogramInterface/HistogramPackage.h"

// forward declarations

class prodname : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      prodname( void );                      // anal1 
      virtual ~prodname();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      prodname( const prodname& );

      // ------------ assignment operator(s) ----------------------
      const prodname& operator=( const prodname& );

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* PRODNAME_PRODNAME_H */
