// -*- C++ -*-
#if !defined(PROCNAME_PROCNAME_H)
#define PROCNAME_PROCNAME_H
//
// Package:     <procname>
// Module:      procname
//
/**\class procname procname.h procname/procname.h
 
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
example_tuplevector #include <vector>

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
example_tuple_tuplevector #include "FrameAccess/FAInserter.h"

example_tuple_tuplevector #include "procname/example=.h"
// forward declarations

class procname : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      procname( void );                      // anal1 
      virtual ~procname();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      procname( const procname& );

      // ------------ assignment operator(s) ---------------------
      const procname& operator=( const procname& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (procname::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
example_histogram       HIHist1D*  m_histo1;
example_dchain       HINtuple* m_dStarNtuple;
example_tuple       FAInserter<example=> m_example=Inserter;
example_tuplevector       FAInserter< vector<example=> > m_example=Inserter;
example_tuplevector       vector<example=> m_example=List;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PROCNAME_PROCNAME_H */
