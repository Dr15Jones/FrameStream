#if !defined(PROCESSOR_PRODUCER_H)
#define PROCESSOR_PRODUCER_H
// -*- C++ -*-
//
// Package:     <Processor>
// Module:      Producer
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner, Simon Patton
// Created:     Mon Sep  1 22:37:50 EDT 1997
// $Id: Producer.h,v 1.19 1999/10/09 21:57:47 cdj Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "DataHandler/ProxyProvider.h"
#include "CommandPattern/Module.h"                    
#include "HistogramInterface/HistogramPackage.h"
#include "DataHandler/DataKey.h"
#include "Processor/ProxiesCommand.h"
#include "Processor/ProductionTagCommand.h"

// forward declarations
class ProxyFactoryBase;
#include <vector>
#include <map>
#if !defined(_producer_stream2factories_)
#define _producer_stream2factories_ std::multimap< Stream::Type, Producer::FactoryInfo >
#endif

class Producer : public ProxyProvider, public Module 
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef std::string Name;
      struct FactoryInfo {
	    FactoryInfo() {}
	    FactoryInfo( const DataKey& iKey, 
			 ProxyFactoryBase* iFactory,
			 DABoolean iShouldUse = true )
	       : m_key( iKey ), 
		 m_factory( iFactory ), 
		 m_shouldUse( iShouldUse ) {}
	    DataKey m_key;
	    ProxyFactoryBase* m_factory;
	    DABoolean m_shouldUse;
      };

      // Constructors and destructor
      Producer( const Name& iName, const Name& iModuleDescription="Producer" );
      virtual ~Producer();

      // ------------ member functions --------------------
      
      /// required by ProxyProvider
      virtual void align( const Stream::Type& aStream ,
			  const SyncValue& aSyncValue ) ;

      /// standard place to book histograms
      virtual void hist_book( HIHistoManager& );

      /// calls for proper sequence of events
      void setCallHistBook( DABoolean iValue );

      void setProductionTag( const std::string& iProductionTag  );

      // -------------- const member functions -------------------

      /// need to reconcile Module and ProxyProvider name/identifier
      const char* identifier() const;

      /// required by ProxyProvider
      virtual const SyncValue& latest( const Stream::Type& aStream ,
				       SyncValue& aCurrentLatest ,
				       const SyncValue& aLimit ) const ;
      /// calls for proper sequence of events
      DABoolean callHistBook() const;
      DABoolean callRegisterProxies( DABoolean forceReload = false ) const;

      std::vector< DataKey > proxyKeys( const Stream::Type& iStream ) const;

      ProductionTag productionTag() const {
	 return ProductionTag( m_productionTag.c_str() ); }

      std::string defaultProductionTag() const;

      // static member functions
      static std::string factorySymbol();

   protected:
      // protected member functions

      // register proxies
      virtual void registerProxies( const Stream::Type& iStream ,
				    KeyedProxies& aProxyList ) ;

      virtual void registerProxyFactory( const Stream::Type& iStream ,
					 ProxyFactoryBase* iFactory,
					 const UsageTag& iUsage );

// the "future":					 
//      virtual void registerProxyFactory( const Stream::Type& iStream ,
//					 ProxyFactoryBase* iFactory,
//					 const UsageTag& iUsage,
//                                       const ProductionTag& iProduction );
					 
      // protected const member functions

   private:
      // Constructors and destructor
      Producer( const Producer& );

      // assignment operator(s)
      const Producer& operator=( const Producer& );

      // private member functions

      // private const member functions

      // data members

      ProxiesCommand m_proxyCommand;
      ProductionTagCommand m_productionTagCommand;

      // for proper sequence of events
      DABoolean m_callHistBook;
      DABoolean m_callRegisterProxies;

      _producer_stream2factories_& m_stream2Factories;

      // Have to use a string instead of a ProductionTag because
      //  ProductionTags do not own the 'const char *' that they
      //  hold.
      std::string m_productionTag;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "Processor/Template/Producer.cc"
//#endif

// -----------------------------------------------------------------------
// Revision history
//
// $Log: Producer.h,v $
// Revision 1.19  1999/10/09 21:57:47  cdj
// added production_tag command to Producer
//
// Revision 1.18  1999/09/06 22:21:35  mkl
// move to new histogramming interface
//
// Revision 1.17  1998/11/10 23:21:11  mkl
// static linking of proc/ducers/source-/sink-formats/modules whatever; and cleanup
//
// Revision 1.16  1998/11/09 21:25:22  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.15  1998/11/06 21:02:38  mkl
// add ProxiesCommand to Producers
//
// Revision 1.14  1998/11/03 19:10:22  mkl
// added 'forcereload proxies' flag
//
// Revision 1.13  1998/11/01 20:14:47  mkl
// switched to new proxy factory registration scheme
//
// Revision 1.12  1998/09/08 19:02:37  mkl
// removed superfluous const qualifier
//
// Revision 1.11  1998/07/21 16:23:27  mkl
// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
//
// Revision 1.10  1998/04/20 19:25:30  mkl
// fix static linking of producers
//
// Revision 1.9  1998/03/11 19:01:18  mkl
// moved init/terminate into Module, since they are artifacts of the dynamic creation of Modules
//
// Revision 1.8  1998/01/26 23:56:05  mkl
// moved registerProxies method to protected
//
// Revision 1.7  1998/01/16 23:32:23  mkl
// added MasterProducer for selecting Producers at run time
//
// Revision 1.6  1997/12/20 20:13:28  cleo3
// added identifier to resolve Module::name and ProxyProvider::identifier
//
// Revision 1.5  1997/10/07 04:13:59  mkl
// replaced HbookManager by HIHistoManager
//
// Revision 1.4  1997/09/18 21:29:07  cdj
// changed Boolean to DABoolean
//
// Revision 1.3  1997/09/10 01:45:47  mkl
// rearranged timing of init and terminate calls
//
// Revision 1.2  1997/09/05 22:33:57  mkl
// moved init/terminate to Producer; implemented hist_book routine
//
// Revision 1.1  1997/09/03 02:43:02  mkl
// ProxyProvider-->Producer-->Processor
#endif /* PROCESSOR_PRODUCER_H */
