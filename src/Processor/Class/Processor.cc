// -*- C++ -*-
//
// Package:     <package>
// Module:      Processor
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Thu Apr 17 17:31:01 EDT 1997
// $Id: Processor.cc,v 1.19 1999/03/15 19:15:35 mkl Exp $
//
// Revision history
//
// $Log: Processor.cc,v $
// Revision 1.19  1999/03/15 19:15:35  mkl
// make SunOS CC happy
//
// Revision 1.18  1999/03/15 18:44:25  mkl
// ActionCommand allows to list and en/disable actions at runtime
//
// Revision 1.17  1998/11/09 21:25:17  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.16  1998/03/27 15:26:56  mkl
// more naming fixups
//
// Revision 1.15  1998/02/03 21:29:51  mkl
// switch over to STLUtility library
//
// Revision 1.14  1998/02/03 02:16:32  mkl
// get rid of dependency code
//
// Revision 1.13  1997/11/24 18:34:30  mkl
// need to delete each action from actionmap
//
// Revision 1.12  1997/10/07 19:24:47  mkl
// cout --> report( INFO ) and kFacilityString update
//
// Revision 1.11  1997/10/07 04:15:01  mkl
// replace multimap by map for actions
//
// Revision 1.10  1997/09/05 22:33:53  mkl
// moved init/terminate to Producer; implemented hist_book routine
//
// Revision 1.9  1997/09/03 05:58:11  mkl
// moved from 'const string kFacilityString' to 'static const char* const'
//
// Revision 1.8  1997/09/03 02:43:36  mkl
// restructuring suez libraries
//
// Revision 1.7  1997/08/29 04:19:33  mkl
// bug flag name change
//
// Revision 1.6  1997/08/12 22:21:36  mkl
// better handling of out-of-memory errors
//
// Revision 1.5  1997/07/11 05:59:23  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.4  1997/06/17 20:30:20  mkl
// allow multiple actions per stream
//
// Revision 1.3  1997/06/14 03:52:51  mkl
// replaced static function calls with pointers to member functions
//
// Revision 1.2  1997/05/24 18:32:29  cdj
// Changed Stream::TypeLess to less< Stream::Type >
//
// Revision 1.1.1.1  1997/05/23 20:18:00  mkl
// imported processor sources
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif                         
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Processor/Processor.h"
#include "Processor/ActionBase.h"
#include "Experiment/report.h"

// STL classes
#include <vector>
#include <algorithm>
#include <map>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.Processor";

typedef _processor_stream2actions_ StreamActionMap;

//
// static data member definitions
//

//
// constructors and destructor
//
Processor::Processor( void )
   : Producer( "Processor", "Processor" ),
     m_streamActionMap( *new StreamActionMap ),
     m_actionCommand( "action", this )
{
   if(    0 == &m_streamActionMap
      )
   {
      report( EMERGENCY ,
              kFacilityString )
                 << "Unable to allocate memory"
                 << endl ;
      assert(false);
      ::exit( 1 );
   }
}

Processor::Processor( const Name& iName )
   : Producer( iName, "Processor" ),                     
     m_streamActionMap( *new StreamActionMap ),
     m_actionCommand( "action", this )
{
   if(    0 == &m_streamActionMap
      )
   {
      report( EMERGENCY ,
              kFacilityString )
                 << "Unable to allocate memory"
                 << endl ;
      assert(false);
      ::exit( 1 );
   }
}

// Processor::Processor( const Processor& )
// {
// }

Processor::~Processor()
{
   // delete action map (need to delete each action pointer!)
   StreamActionMap::iterator itEnd = m_streamActionMap.end();
   for( StreamActionMap::iterator it = m_streamActionMap.begin();
	it != itEnd;
	++it )
   {
      delete (*it).second.action();
   }
   m_streamActionMap.erase( m_streamActionMap.begin(), 
			    m_streamActionMap.end() );
   delete &m_streamActionMap;

}

//
// assignment operators
//
// const Processor& Processor::operator=( const Processor& )
// {
// }

//
// member functions
//
void
Processor::bindAction( const Stream::Type& iStream, ActionBase* iAction )
{
   StreamActionMap::iterator which = m_streamActionMap.find( iStream );
   if( m_streamActionMap.end() == which )
   {
      m_streamActionMap.insert(
	 pair< const Stream::Type, ActionInfo >( iStream, 
						 ActionInfo( iAction, true ) ) );
   }
   else
   {
      report( EMERGENCY, kFacilityString ) 
	 << "Trying to bind to already-bound stream \"" 
	 << iStream.value() << "\";\n exiting job ..." << endl;
      ::exit( 1 );
   }

   return;
}

ActionBase::ActionResult
Processor::execute( const Stream::Type& streamType, Frame& frame )
{
   ActionBase::ActionResult returnValue = ActionBase::kNoAction;

   StreamActionMap::iterator itAction = m_streamActionMap.find( streamType );
   if( m_streamActionMap.end() != itAction )
   {
      ActionInfo actionInfo = (*itAction).second;
      if( true == actionInfo.shouldUse() )
      {
	 returnValue = (*itAction).second.action()->operator()( frame );
      }
   }

   return returnValue;
}

StreamActionMap&
Processor::actions( void )
{
   return m_streamActionMap;
}

//
// const member functions
//
const StreamActionMap&
Processor::actions( void ) const
{
   return m_streamActionMap;
}

//
// static member functions
//
string
Processor::factorySymbol()
{
   return "makeProcessor";
}
