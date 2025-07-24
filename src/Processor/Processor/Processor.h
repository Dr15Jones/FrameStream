#if !defined(PACKAGE_PROCESSOR_H)
#define PACKAGE_PROCESSOR_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      Processor
// 
// Description: Base class for Processors
//
// Usage:
//    Processors are objects which hold related Actions.
//
//    Note: Any ActionBase* handed to Processor through bindActions
//          is owned by the Processor
//
// Author:      Chris D. Jones, Martin Lohner
// Created:     Thu Apr 17 17:15:47 EDT 1997
// $Id: Processor.h,v 1.16 1999/03/15 18:44:29 mkl Exp $
//
// Revision history
//
// $Log: Processor.h,v $
// Revision 1.16  1999/03/15 18:44:29  mkl
// ActionCommand allows to list and en/disable actions at runtime
//
// Revision 1.15  1998/11/10 23:21:07  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
// Revision 1.14  1998/11/09 21:25:22  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.13  1998/04/20 19:25:30  mkl
// fix static linking of producers
//
// Revision 1.12  1998/02/03 21:30:00  mkl
// switch over to STLUtility library
//
// Revision 1.11  1998/02/03 02:16:23  mkl
// get rid of dependency code
//
// Revision 1.10  1997/10/07 04:15:10  mkl
// replace multimap by map for actions
//
// Revision 1.9  1997/09/05 22:33:56  mkl
// moved init/terminate to Producer; implemented hist_book routine
//
// Revision 1.8  1997/09/03 02:43:38  mkl
// restructuring suez libraries
//
// Revision 1.7  1997/08/29 04:19:37  mkl
// bug flag name change
//
// Revision 1.6  1997/07/11 05:59:27  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.5  1997/07/01 03:16:56  mkl
// moved typedef map statements to .cc files
//
// Revision 1.4  1997/06/17 20:31:17  mkl
// allow multiple actions per stream
//
// Revision 1.3  1997/06/14 03:52:55  mkl
// replaced static function calls with pointers to member functions
//
// Revision 1.2  1997/05/24 18:32:31  cdj
// Changed Stream::TypeLess to less< Stream::Type >
//
// Revision 1.1.1.1  1997/05/23 20:18:00  mkl
// imported processor sources
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */                               

// user include files
#include "Processor/Producer.h"
#include "DataHandler/Stream.h"
#include "Processor/ActionBase.h"
#include "Processor/ActionCommand.h"

// forward declarations
#include <vector>
#include <map>

#if !defined(_producer_stream2actions_)
#define _processor_stream2actions_ std::map< Stream::Type , Processor::ActionInfo >
#endif


class Processor : public Producer
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef Producer::Name Name;
      class ActionInfo {
	 public:
            ActionInfo() {}
            ActionInfo( ActionBase* iAction, 
			DABoolean iShouldUse = true )
               : m_action( iAction ), 
                 m_shouldUse( iShouldUse ) {}
	    DABoolean& shouldUse() { return m_shouldUse; }
	    ActionBase* action() { return m_action; }
	    DABoolean shouldUse() const { return m_shouldUse; }
	    const ActionBase* action() const { return m_action; }
	 private:
            ActionBase* m_action;
            DABoolean m_shouldUse;
      };

      // Constructors and destructor
      virtual ~Processor();

      // member functions

      ActionBase::ActionResult execute( const Stream::Type& streamType, 
					Frame& frame );

      _processor_stream2actions_& actions( void );

      // const member functions
      const _processor_stream2actions_& actions( void ) const;

      // static member functions
      static std::string factorySymbol();

   protected:
      // protected member functions
      Processor( void );
      Processor( const Name& iName );

      void bindAction( const Stream::Type& iStream, ActionBase* iAction );

      // protected const member functions

   private:
      // Constructors and destructor
      Processor( const Processor& );

      // assignment operator(s)
      const Processor& operator=( const Processor& );

      // private member functions

      // private const member functions

      // data members
      // bindings of actions to streams
      _processor_stream2actions_& m_streamActionMap;    

      // commands
      ActionCommand m_actionCommand;

      // static data members

};

// inline function definitions

#endif /* PACKAGE_PROCESSOR_H */
