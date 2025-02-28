nocap// -*- C++ -*-
nocap#if !defined(PROCESSOR_PROCNAME_H)
nocap#define PROCESSOR_PROCNAME_H
nocap//
nocap// Package:     Processor
nocap// Module:      procname
nocap// 
nocap// Description: <one line class summary>
nocap//
nocap// Usage:
nocap//    <usage>
nocap//
nocap// Author:      John Doe
nocap// Created:     day-mon-xx
nocap// RCS(Id)
nocap//
nocap// Revision history
nocap//
nocap// RCS(Log)
nocap
nocap
nocap// system include files
nocap
nocap// user include files
nocap#include "Processor/Processor.h"
nocap
nocap// forward declarations
nocap
nocapclass procname : public Processor
nocap{
nocap      // friend classses and functions
nocap
nocap   public:
nocap      // constants, enums and typedefs
nocap
nocap      // Constructors and destructor
nocap      procname( void );               // anal1_
nocap      virtual ~procname();            // anal5_
nocap
nocap      // member functions
nocap
nocap      // methods for binding to streams (anal3_, anal2_, anal4_)
nocap      virtual ActionBase::ActionResult event( Frame& iFrame );
nocap      virtual ActionBase::ActionResult beginRun( Frame& iFrame);
nocap      virtual ActionBase::ActionResult endRun( Frame& iFrame);
nocap
nocap      // const member functions
nocap
nocap      // static member functions
nocap
nocap   protected:
nocap      // protected member functions
nocap
nocap      // protected const member functions
nocap
nocap   private:
nocap      // Constructors and destructor
nocap      procname( const procname& );
nocap
nocap      // assignment operator(s)
nocap      const procname& operator=( const procname& );
nocap
nocap      // private member functions
nocap      void bind( 
nocap         ActionBase::ActionResult (procname::*iMethod)( Frame& ),
nocap	      const Stream::Type& iStream );
nocap
nocap      // private const member functions
nocap
nocap      // data members
nocap
nocap      // static data members
nocap
nocap};
nocap
nocap// inline function definitions
nocap
nocap#endif /* PROCESSOR_PROCNAME_H */
