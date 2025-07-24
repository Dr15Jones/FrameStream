// -*- C++ -*-
//
// Package:     <Processor>
// Module:      Producer
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner, Simon Patton
// Created:     Mon Sep  1 22:37:28 EDT 1997
// $Id: Producer.cc,v 1.19 1999/11/04 00:58:56 cdj Exp $
//
// Revision history
//
// $Log: Producer.cc,v $
// Revision 1.19  1999/11/04 00:58:56  cdj
// fixed bug which caused Proxies not to be registered if you set production tag
//
// Revision 1.18  1999/10/09 21:57:44  cdj
// added production_tag command to Producer
//
// Revision 1.17  1999/09/06 22:21:31  mkl
// move to new histogramming interface
//
// Revision 1.16  1998/11/10 02:10:52  mkl
// fixed typo in factory symbol string
//
// Revision 1.15  1998/11/09 21:25:18  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.14  1998/11/06 21:20:26  mkl
// renamed 'proxies' command to 'proxy'
//
// Revision 1.13  1998/11/06 21:02:24  mkl
// add ProxiesCommand to Producers
//
// Revision 1.12  1998/11/03 19:10:19  mkl
// added 'forcereload proxies' flag
//
// Revision 1.11  1998/11/02 16:19:47  mkl
// moved ProxyFactory* stuff to DataHandler
//
// Revision 1.10  1998/11/01 20:14:44  mkl
// switched to new proxy factory registration scheme
//
// Revision 1.9  1998/09/08 19:02:39  mkl
// removed superfluous const qualifier
//
// Revision 1.8  1998/07/21 16:23:23  mkl
// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
//
// Revision 1.7  1998/03/11 19:01:21  mkl
// moved init/terminate into Module, since they are artifacts of the dynamic creation of Modules
//
// Revision 1.6  1997/12/20 20:13:27  cleo3
// added identifier to resolve Module::name and ProxyProvider::identifier
//
// Revision 1.5  1997/10/07 04:14:08  mkl
// replaced HbookManager by HIHistoManager
//
// Revision 1.4  1997/09/18 21:29:03  cdj
// changed Boolean to DABoolean
//
// Revision 1.3  1997/09/10 01:45:56  mkl
// rearranged timing of init and terminate calls
//
// Revision 1.2  1997/09/05 22:33:53  mkl
// moved init/terminate to Producer; implemented hist_book routine
//
// Revision 1.1  1997/09/03 02:43:11  mkl
// ProxyProvider-->Producer-->Processor
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Processor/Producer.h"
#include "DataHandler/ProxyFactoryBase.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "Processor.Producer" ;

typedef _producer_stream2factories_ Stream2Factories;

//
// static data member definitions
//

//
// inlined member functions
//

//
// constructors and destructor
//
Producer::Producer( const Name& iName, const Name& iModuleDescription )
   : ProxyProvider( iName ), Module( iName, iModuleDescription ),
     m_proxyCommand( "proxy", this ),
     m_productionTagCommand( "production_tag", this ),
     m_callHistBook       ( true ),
     m_callRegisterProxies( true ),
     m_stream2Factories( *new Stream2Factories ),
     m_productionTag("")
{
}

// Producer::Producer( const Producer& )
// {
// }

Producer::~Producer()
{
   // clean out all the proxy factories
   Stream2Factories::iterator itEnd = m_stream2Factories.end();
   for( Stream2Factories::iterator it = m_stream2Factories.begin();
	it != itEnd;
	++it ) {
      delete (*it).second.m_factory;
   }
   delete &m_stream2Factories;
}

//
// assignment operators
//
// const Producer& Producer::operator=( const Producer& )
// {
// }

//
// member functions
//
void
Producer::hist_book( HIHistoManager& ) 
{
}

void
Producer::align( const Stream::Type& aStream ,
		 const SyncValue& )
{
   invalidateProxies( aStream ) ;
}

void
Producer::setProductionTag( const std::string& iProductionTag )
{
   if( m_productionTag != iProductionTag ) {
      m_productionTag = iProductionTag;
   
      //need to get rid of all proxies we've made

      Stream::Set streams = supplies();
      Stream::Set::iterator itStreamEnd = streams.end();
      for( Stream::Set::iterator itStream = streams.begin();
	   itStream != itStreamEnd;
	   ++itStream ) {
	 eraseAll( *itStream );
	 expireProxies( *itStream );
	 
      }
      //remeber that we need to re-register the proxies
      m_callRegisterProxies= true ;


      //now change all the production tags used in the Factories list
      typedef Stream2Factories::iterator Iterator;
      Iterator itEnd = m_stream2Factories.end();
      for( Iterator it = m_stream2Factories.begin(); it != itEnd; ++it ) {
	 //keep the same type and usage Tag, only change production
	 (*it).second.m_key = DataKey( (*it).second.m_key.type(),
				       (*it).second.m_key.usage(),
				       productionTag() );
      }
      
   }
}

void
Producer::registerProxies( const Stream::Type& iStream,
			   KeyedProxies& iProxies )
{
   typedef Stream2Factories::iterator Iterator;
   std::pair< Iterator, Iterator > range = m_stream2Factories.equal_range( iStream );
   for( Iterator it = range.first; it != range.second; ++it ) {
      
      // only create proxy if "shouldUse"
      if( true == (*it).second.m_shouldUse ) {
	 ProxyBase* proxy = (*it).second.m_factory->makeProxy();
	 if( 0 != proxy ) {
	    iProxies.push_back( KeyedProxy( (*it).second.m_key,
					    proxy )
	       );
	 }
      }
   }
}

void
Producer::registerProxyFactory( const Stream::Type& iStream ,
				ProxyFactoryBase* iFactory,
				const UsageTag& iUsage )
{
   if( 0 == iFactory ) {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << std::endl;
      assert( false );
      ::exit( 1 );
   }

   registerStream( iStream );

   FactoryInfo info( iFactory->makeKey( iUsage, productionTag() ),
		     iFactory );

   m_stream2Factories.insert( Stream2Factories::value_type( iStream,
							    info ) 
      );
}

void
Producer::setCallHistBook( DABoolean iValue )
{
   m_callHistBook = iValue;
}

//
// const member functions
//
const char* 
Producer::identifier() const
{
   // need to use either Module::name or ProxyProvider::identifier
   return ProxyProvider::identifier().c_str();
}

const SyncValue&
Producer::latest( const Stream::Type& ,
		  SyncValue& aCurrentLatest ,
		  const SyncValue& ) const
{
   return ( aCurrentLatest ) ;
}

DABoolean
Producer::callHistBook() const
{
   return m_callHistBook;
}

DABoolean
Producer::callRegisterProxies( DABoolean forceReload ) const
{
   DABoolean returnValue = m_callRegisterProxies;

   if( true == forceReload ) {
      returnValue = true;
   }

   // registration should only happen once per "lifetime"
   (*(Producer*)this).m_callRegisterProxies = false;

   return returnValue;
}

std::vector< DataKey >
Producer::proxyKeys( const Stream::Type& iStream ) const
{
   std::vector< DataKey > dataKeys;

   typedef Stream2Factories::iterator Iterator;
   std::pair< Iterator, Iterator > range = m_stream2Factories.equal_range( iStream );
   for( Iterator it = range.first; it != range.second; ++it ) {
      dataKeys.push_back( (*it).second.m_key );
   }
  
   return dataKeys;
}

std::string
Producer::defaultProductionTag() const
{
   return std::string("");
}

//
// static member functions
//
std::string
Producer::factorySymbol()
{
   return "makeProducer:makeProcessor";
}
