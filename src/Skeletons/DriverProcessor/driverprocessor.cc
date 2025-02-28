nocap// -*- C++ -*-
nocap//
nocap// Package:     Processor
nocap// Module:      procname
nocap// 
nocap// Description: <one line class summary>
nocap//
nocap// Implementation:
nocap//     <Notes on implimentation>
nocap//
nocap// Author:      John Doe
nocap// Created:     day-mon-xx
nocap// RCS(Id)
nocap//
nocap// Revision history
nocap//
nocap// RCS(Log)
nocap
nocap#include "Experiment/Experiment.h"
nocap
nocap// system include files
nocap#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
nocap#include <string>
nocap#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            
nocap
nocap// user include files
nocap#include "procname.h"
nocap#include "Experiment/report.h"
nocap#include "anal.h"
nocap
nocap// STL classes
nocap
nocap//
nocap// constants, enums and typedefs
nocap//
nocapstatic const char* const kFacilityString = "procname: " ;
nocap
nocap//
nocap// static data member definitions
nocap//
nocap
nocap//
nocap// constructors and destructor
nocap//
nocapprocname::procname( void )
nocap   : Processor( "procname" )
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;
nocap
nocap// ---- bind a method to a stream -----
nocap   bind( &procname::event,    Stream::kEvent );
nocap   bind( &procname::beginRun, Stream::kBeginRun);
nocap   bind( &procname::endRun,   Stream::kEndRun);
nocap
nocap   // call user routine
nocap   anal1_();
nocap}
nocap
nocap// procname::procname( const procname& )
nocap// {
nocap//    *this = iskelname;
nocap// }
nocap
nocapprocname::~procname()
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
nocap
nocap   // call user routine
nocap   anal5_();
nocap}
nocap
nocap//
nocap// assignment operators
nocap//
nocap// const procname& procname::operator=( const procname& iprocname )
nocap// {
nocap//   if( this != &iprocname ) {
nocap//      // do actual copying here, plus:
nocap//      // "SuperClass"::operator=( iprocname );
nocap//   }
nocap//
nocap//   return *this;
nocap// }
nocap
nocap//
nocap// member functions
nocap//
nocap
nocap// -------------------------- methods bound to streams -------------
nocapActionBase::ActionResult
nocapprocname::event( Frame& )
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in event()" << endl;
nocap
nocap   // call user routine
nocap   anal3_();
nocap
nocap   return ActionBase::kPassed;
nocap}
nocap
nocapActionBase::ActionResult
nocapprocname::beginRun( Frame& )
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;
nocap
nocap   // call user routine
nocap   anal2_();
nocap
nocap   return ActionBase::kPassed;
nocap}
nocap
nocap
nocapActionBase::ActionResult
nocapprocname::endRun( Frame& )
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;
nocap
nocap   // call user routine
nocap   anal4_();
nocap
nocap   return ActionBase::kPassed;
nocap}
nocap
nocap
nocap/*
nocapActionBase::ActionResult
nocapprocname::geometry( Frame& )
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in geometry()" << endl;
nocap
nocap   return ActionBase::kPassed;
nocap}
nocap*/
nocap
nocap/*
nocapActionBase::ActionResult
nocapprocname::hardware( Frame& )
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in hardware()" << endl;
nocap
nocap   return ActionBase::kPassed;
nocap}
nocap*/
nocap
nocap/*
nocapActionBase::ActionResult
nocapprocname::user( Frame& )
nocap{
nocap   report( DEBUG, kFacilityString ) << "here in user()" << endl;
nocap
nocap   return ActionBase::kPassed;
nocap}
nocap*/
nocap
nocap//
nocap// const member functions
nocap//
nocap
nocap//
nocap// static member functions
nocap//
