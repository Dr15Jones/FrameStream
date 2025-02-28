#if !defined(PROCESSOR_RUNEVENTNUMBERPROC_H)
#define PROCESSOR_RUNEVENTNUMBERPROC_H
// -*- C++ -*-
//
// Package:     Processor
// Module:      RunEventNumberProc
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Sep 10 01:42:58 EDT 1997
// $Id: RunEventNumberProc.h,v 1.6 2001/10/26 16:11:14 ajm36 Exp $
//
// Revision history
//
// $Log: RunEventNumberProc.h,v $
// Revision 1.6  2001/10/26 16:11:14  ajm36
// make frequency parameter an unsigned int
//
// Revision 1.5  2001/07/08 14:40:04  cdj
// removed parameter for beginrun binding since can already do that on suez command line and it broke tests
//
// Revision 1.4  2001/07/06 21:36:14  ajm36
// provide parameter to keep from binding to beginrun
//
// Revision 1.3  2001/05/02 17:12:50  ajm36
// add a parameter to set frequency of printout
//
// Revision 1.2  1998/02/10 03:22:31  mkl
// got rid of obsolete HbookManager
//
// Revision 1.1.1.1  1998/01/13 18:18:10  mkl
// imported RunEventNumberProc sources
//
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "ToolBox/HistogramPackage.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class RunEventNumberProc : public Processor
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      RunEventNumberProc( void );                      // anal1 
      virtual ~RunEventNumberProc();                   // anal5 

      // member functions

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( TBHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);
      //virtual ActionBase::ActionResult geometry( Frame& iFrame);
      //virtual ActionBase::ActionResult hardware( Frame& iFrame);
      //virtual ActionBase::ActionResult user( Frame& iFrame);

      // const member functions

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      RunEventNumberProc( const RunEventNumberProc& );

      // assignment operator(s)
      const RunEventNumberProc& operator=( const RunEventNumberProc& );

      // private member functions
      void bind( 
         ActionBase::ActionResult (RunEventNumberProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // private const member functions

      // data members
      Parameter<unsigned int> m_frequency;

      // static data members

};

// inline function definitions

#endif /* PROCESSOR_RUNEVENTNUMBERPROC_H */
