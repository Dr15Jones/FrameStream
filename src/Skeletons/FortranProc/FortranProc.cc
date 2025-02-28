// -*- C++ -*-
//
// Package:     Processor
// Module:      procname
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implimentation>
//
// Author:      John Doe
// Created:     day-mon-xx
// $Id: FortranProc.cc,v 1.6 1999/09/07 14:17:07 mkl Exp $
//
// Revision history
//
// $Log: FortranProc.cc,v $
// Revision 1.6  1999/09/07 14:17:07  mkl
// switch to new Histogram Interface
//
// Revision 1.5  1998/03/26 21:10:54  mkl
// naming fixups: package etc
//
// Revision 1.4  1998/03/05 18:17:42  mkl
// added sample implementations (commented out) of copyctor and assignment op
//
// Revision 1.3  1998/02/10 20:08:23  mkl
// needed AMBIGUOUS_STRING construct for g++
//
// Revision 1.2  1998/02/10 18:07:07  mkl
// return from fortran 'actions' handled
//
// Revision 1.1  1998/02/10 03:41:37  mkl
// first version of FortranProcessor skeletons
//

#include "Experiment/Experiment.h"
#include "Experiment/fortran_types.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif             
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "procname/procname.h"
#include "Experiment/report.h"

// extern fortran functions called from implementation methods
extern "C" {
lowcap   void procname_initialize_( void );
lowcap   void procname_terminate_( void );
lowcap   void procname_hist_book_( void );
FInteger 
lowcap   procname_event_( void );
FInteger 
lowcap   procname_beginRun_( void );
FInteger 
lowcap   procname_endRun_( void );
}

// STL classes

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.procname" ;

//
// static data member definitions
//

//
// constructors and destructor
//
procname::procname( void )               // anal1
{
}

// procname::procname( const procname& iprocname )
// {
//    *this = iprocname;
// }

procname::~procname()                    // anal5
{
}

//
// assignment operators
//
// const procname& procname::operator=( const procname& iprocname )
// {
//   if( this != &iprocname ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iprocname );
//   }
//
//   return *this;
// }

//
// member functions
//
void 
procname::implementInitialize( void )
{
lowcap   procname_initialize_();
}

void 
procname::implementTerminate( void )
{
lowcap   procname_terminate_();
}
 
void 
procname::implementHistBook( HIHistoManager& )
{
lowcap   procname_hist_book_();
}

ActionBase::ActionResult 
procname::implementEvent( Frame& )
{
   return ActionBase::ActionResult(
lowcap      procname_event_()
      );
}

ActionBase::ActionResult 
procname::implementBeginRun( Frame& )
{
   return ActionBase::ActionResult(
lowcap      procname_beginRun_()
      );
}

ActionBase::ActionResult 
procname::implementEndRun( Frame& )
{
   return ActionBase::ActionResult(
lowcap      procname_endRun_()
      );
}

//
// const member functions
//

//
// static member functions
//
