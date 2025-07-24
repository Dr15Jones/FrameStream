// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      PathModule
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Jul  7 11:18:22 EDT 2003
// $Id: PathModule.cc,v 1.1 2003/09/19 21:26:44 cdj Exp $
//
// Revision history
//
// $Log: PathModule.cc,v $
// Revision 1.1  2003/09/19 21:26:44  cdj
// first submission of Path code
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "JobControl/PathModule.h"
#include "CommandPattern/Keyword/NoArgReturnResult.h"
#include "CommandPattern/Keyword/OneArgNoReturn.h"
#include "CommandPattern/Keyword/Composite.h"
#include "CommandPattern/Keyword/StringParser.h"
#include "CommandPattern/Keyword/VectorStringParser.h"
#include "JobControl/SinkManager.h"
#include "JobControl/Path.h"
#include "JobControl/FilterBase.h"
#include "JobControl/FilterAnd.h"
#include "JobControl/FilterOr.h"
#include "JobControl/FilterXOr.h"
#include "JobControl/FilterNot.h"
#include "JobControl/FilterProc.h"
#include "Processor/Processor.h"
#include "Processor/MasterProcessor.h"
#include "CommandPattern/Keyword/keyword_exceptions.h"

#include "DataStorage/DataSinkDescriptor.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "JobControl.PathModule" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PathModule.cc,v 1.1 2003/09/19 21:26:44 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
using CommandPattern::Keyword::NoArgReturnResult;
using CommandPattern::Keyword::OneArgNoReturn;
using CommandPattern::Keyword::Composite;
using JobControlNS::FilterBase;

static const std::string kPathHelp
(
 "Description: path\n"
 "\n"
 "Valid subcommands are:\n"
 "\n"
 " path help                           see this help page\n"
 " path list                           list paths\n"
 " path ls\n"
 " path remove <path>                  removes <path>\n"
 " path rm <path>\n"
 " path create <name> [<filter spec>] >> [<proc>][<sink>][...]\n"
 "    creates a path named <name> using the optionally defined filter\n"
 "    <filter spec> (see filter create for syntax) and if the records\n"
 "    pass the filter, the record\n is passed to the optional list of\n"
 "    Processors and sinks\n"
 "\n"
 " path filter ls                      list filters\n"
 " path filter list\n"
 " path filter remove <filter>         removes <filter> if not in use\n"
 " path filter create <name> [not] <proc>|<filter>\n"
 "                           [ and|or|xor [not] <proc>|<filter> ] [...]\n"
 "    creates a filter named <name> which is a list of Processors and/or\n"
 "    other Filters which optionally can be modified using 'not'.  The\n"
 "    list of Processors/Filters are joined together using any combination of\n"
 "    the logical operations 'and' 'or' and 'xor'.\n"
 ""
 " Example:\n"
 "     path filter create Good Cut1Proc and Cut2Proc\n"
 "     path filter create Bad not Good\n"
 "     path filter create Everything Good or Bad\n"
 "     path create Good Good >> good.pds\n"
 "     path create Bad Bad >> bad.pds\n"
 "     path create All Everything >> RunEventNumberProc\n"
 );

//
// constructors and destructor
//
namespace PathModuleNS {
   class CreateFilter : public CommandPattern::Keyword::Base {
     public:
      CreateFilter(const std::string& iName, PathModule* iModule ) :
      Base(iName), m_module(iModule) {}
      unsigned int minArgs() const { return 2;}
      unsigned int maxArgs() const {return 1000;}
     protected:
      int implementExecute( int argc, char** argv );
     private:
      PathModule* m_module;
   };
   
   int CreateFilter::implementExecute(int argc, char** argv) {
      return m_module->createFilter(argc, argv);
   }
   class CreatePath : public CommandPattern::Keyword::Base {
public:
      CreatePath(const std::string& iName, PathModule* iModule ) :
      Base(iName), m_module(iModule) {}
      unsigned int minArgs() const { return 2;}
      unsigned int maxArgs() const {return 1000;}
protected:
      int implementExecute( int argc, char** argv );
private:
      PathModule* m_module;
   };
   
   int CreatePath::implementExecute(int argc, char** argv) {
      return m_module->createPath(argc, argv);
   }
   
}

PathModule::PathModule(SinkManager& iSM,
		       MasterProcessor& iMP ) :
   Module("PathModule","controller for execution paths"),
   m_paths(iSM,iMP),
   m_command("path",this,false,kPathHelp),
   m_sinkM(&iSM),
   m_procM(&iMP)
{
   m_command.add(new NoArgReturnResult<PathModule,std::string>("ls", this,&PathModule::listPaths, &m_command) );
      m_command.add(new NoArgReturnResult<PathModule,std::string>("list", this,&PathModule::listPaths, &m_command) );
   m_command.add( new PathModuleNS::CreatePath("create",this) );
   m_command.add(new OneArgNoReturn<PathModule,const std::string&, 
                 CommandPattern::Keyword::StringParser>("remove", this,&PathModule::removePath));
   m_command.add(new OneArgNoReturn<PathModule,const std::string&, 
                 CommandPattern::Keyword::StringParser>("rm", this,&PathModule::removePath));
   m_command.add(new OneArgNoReturn<PathModule,const std::vector<std::string>&, 
                 CommandPattern::Keyword::VectorStringParser>("reorder", this,&PathModule::reorder));

   Composite* filterCommand = new Composite("filter");
   filterCommand->add( new NoArgReturnResult<PathModule,std::string>("ls",this, &PathModule::listFilters,&m_command) );
   filterCommand->add( new NoArgReturnResult<PathModule,std::string>("list",this, &PathModule::listFilters,&m_command) );
   filterCommand->add( new PathModuleNS::CreateFilter("create",this) );
   filterCommand->add(new OneArgNoReturn<PathModule,const std::string&, 
                 CommandPattern::Keyword::StringParser>("remove", this,&PathModule::removeFilter));
   m_command.add(filterCommand);
}

// PathModule::PathModule( const PathModule& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PathModule::~PathModule()
{
}

//
// assignment operators
//
// const PathModule& PathModule::operator=( const PathModule& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

//
// const member functions
//
std::string
PathModule::listPaths()
{
   std::string returnValue;
   for(std::vector<JobControlNS::Path*>::const_iterator itPath = m_paths.paths().begin();
       itPath != m_paths.paths().end();
       ++itPath) {
      assert(0 != *itPath);
      returnValue += "Path "+(*itPath)->name() + "\n";
      returnValue += " filter: ";
      if( 0 != (*itPath)->filter() ) {
         returnValue += (*itPath)->filter()->name();
      } else {
         returnValue += "none";
      }
      returnValue +="\n";
      
      returnValue +=" ops: ";
      if( 0 == (*itPath)->operations().size() ) {
         returnValue += "none\n";
      } else {
         returnValue += (*itPath)->operations().front()->name() +"\n";
         for( std::vector<Processor*>::const_iterator itProc = (*itPath)->operations().begin()+1;
              itProc != (*itPath)->operations().end();
              ++itProc ) {
            returnValue +="      "+(*itProc)->name() + "\n";
         }
      }

      returnValue +=" sinks: ";
      _framestorer_sinkdescriptors_ sinks = (*itPath)->sinks();
      if( 0 == sinks.size() ) {
         returnValue += "none\n";
      } else {
         returnValue += sinks.front().dataSinkID() +"\n";
         for(_framestorer_sinkdescriptors_::iterator itSink = sinks.begin()+1;
             itSink != sinks.end();
             ++itSink ) {
            returnValue += "        "+(*itSink).dataSinkID()+"\n";
         }
      }
   }
   return returnValue;
}

std::string
PathModule::listFilters()
{
   std::string returnValue;
   for(std::vector<JobControlNS::Holder<JobControlNS::FilterBase> >::const_iterator itFilter = m_paths.filters().begin();
       itFilter != m_paths.filters().end();
       ++itFilter) {
      returnValue += (*itFilter)->name() + ": "+(*itFilter)->description()+"\n";
   }
   return returnValue;
}   

namespace PathModuleNS {
enum Ops {kAnd, kOr, kXOr};
}
using PathModuleNS::Ops;

static
JobControlNS::FilterComposite*
makeFilter(const std::string& iName, PathModuleNS::Ops iOp)
{
   switch(iOp) {
      case PathModuleNS::kAnd:
         return new JobControlNS::FilterAnd(iName);
      case PathModuleNS::kOr:
         return new JobControlNS::FilterOr(iName);
      case PathModuleNS::kXOr:
         return new JobControlNS::FilterXOr(iName);
   }
   return 0;
}

int 
PathModule::createFilter( int argc, char** argv )
{

   JobControlNS::Holder<JobControlNS::FilterBase> pFilter (
      implementCreateFilter(argv[0], argc-1, argv+1) );
   
   m_paths.add( pFilter.get() );
   
   return Command::COMMAND_OK;
}

JobControlNS::Holder<JobControlNS::FilterBase> 
PathModule::implementCreateFilter( const std::string& iName, int argc, char** argv )
{
   
   
   std::map<std::string, FilterBase*> nameToFilter;

   const std::string kName(iName);
   //does a filter with this name already exist?
   for(std::vector<JobControlNS::Holder<JobControlNS::FilterBase> >::const_iterator itFilter = m_paths.filters().begin();
       itFilter != m_paths.filters().end();
       ++itFilter) {
      if( (*itFilter)->name() == kName) {
         std::string info("A Filter named ");
         info += kName;
         info += " already exists";
         throw CommandPattern::Keyword::UserException(info);
      }
      nameToFilter.insert( make_pair((*itFilter)->name(), (*itFilter).get() ) );
   }

   //does a processor with this name already exist?
   for(std::vector<JobControlNS::Holder<JobControlNS::FilterProc> >::const_iterator itFilter = m_paths.filterProcs().begin();
       itFilter != m_paths.filterProcs().end();
       ++itFilter) {
      if( (*itFilter)->name() == kName) {
         std::string info("A Processor named ");
         info += kName;
         info += " already exists";
         throw CommandPattern::Keyword::UserException(info);
      }
      nameToFilter.insert( std::pair<std::string,JobControlNS::FilterBase*>((*itFilter)->name(), (*itFilter).get() ) );
   }
   
   //parse filter
   typedef std::vector< JobControlNS::Holder<FilterBase> > FilterInfoStack;
   FilterInfoStack infoStack;
   infoStack.reserve(argc);
   typedef std::vector<Ops> OpsStack;
   OpsStack opsStack;
   opsStack.reserve(argc);
   std::map<std::string, Ops> nameToOp;
   nameToOp.insert(std::map<std::string,Ops>::value_type("and",PathModuleNS::kAnd) );
   nameToOp.insert(std::map<std::string,Ops>::value_type("or",PathModuleNS::kOr) );
   nameToOp.insert(std::map<std::string,Ops>::value_type("xor",PathModuleNS::kXOr) );
   
   DABoolean shouldBeFilter = true;
   for(int itArg=0; itArg < argc; ++itArg) {
      std::string args(argv[itArg] );

      if(shouldBeFilter) {
         DABoolean usingNot = false;
         if( args == "not") {
            usingNot = true;
            ++itArg;
            if( itArg ==argc ) {
               throw CommandPattern::Keyword::UserException("Filter or Processor name must follow 'not'");
            }
            args = std::string(argv[itArg]);
         }
         std::map<std::string,FilterBase*>::iterator itFound = nameToFilter.find(args);
         if( itFound == nameToFilter.end() ) {
            std::string info(args+" is not the name of a Filter or Processor");
            throw CommandPattern::Keyword::UserException(info);
         }
         if( usingNot ) {
            infoStack.push_back( new JobControlNS::FilterNot( "", (*itFound).second) );
         } else {
            infoStack.push_back( (*itFound).second );
         }
      } else {
         //is it one of our operation keywords?
         std::map<std::string, Ops>::iterator itOp = nameToOp.find(args);
         if( itOp == nameToOp.end() ) {
            throw CommandPattern::Keyword::UserException(args+" is not one of the keywords 'or', 'and' or 'xor'");
         }
         opsStack.push_back((*itOp).second);
      }
      shouldBeFilter = ! shouldBeFilter;
   }
   if( shouldBeFilter ) {
      throw CommandPattern::Keyword::UserException("Filter creation should end with the name of a Filter or Processor");
   }
   
   //parsing has shown that everything is correct, so now build the filter
   JobControlNS::Holder<JobControlNS::FilterComposite> pFilter;
   
   if( 0 == opsStack.size() ) {
      pFilter = new JobControlNS::FilterAnd(kName);
      pFilter->add(infoStack.front().get());
   } else {
      //if the same operation is used in series, we can use the same filter
      pFilter = makeFilter("", opsStack.front());
      Ops prevOp = opsStack.front();
      pFilter->add(infoStack.front().get());

      FilterInfoStack::iterator itFilter = infoStack.begin()+1;
      OpsStack::iterator itOp = opsStack.begin();

      JobControlNS::Holder<JobControlNS::FilterComposite> pPrevFilter = pFilter;

      while(itFilter != infoStack.end() ) {
         if( prevOp != *itOp ) {
            JobControlNS::FilterComposite* newFilter = makeFilter("", *itOp);
            newFilter->add( pPrevFilter.get() );
            pPrevFilter = newFilter;
            prevOp = *itOp;
         }
         pPrevFilter->add( (*itFilter).get() );
         ++itOp;
         ++itFilter;
      }
      pFilter = pPrevFilter;
   }
   pFilter->setName(kName);
   
   return pFilter.get();
}

int 
PathModule::createPath( int argc, char** argv )
{
   const std::string kName(argv[0]);

   //does this path name already exist?
   for(std::vector<JobControlNS::Path*>::const_iterator itPath = m_paths.paths().begin();
       itPath != m_paths.paths().end();
       ++itPath) {
      if( (*itPath)->name() == kName ) {
         throw CommandPattern::Keyword::UserException(std::string("A Path named "+kName+" already exists.") );
      }
   }
   
   //do we have a Filter?
   JobControlNS::Holder<JobControlNS::FilterBase> pFilter;
   int argIndex = 1;

   const std::string kSeperator(">>");
   while(argIndex < argc && 
	 kSeperator != argv[argIndex] ) { 
      ++argIndex;
   }

   if( argIndex != 1 ) {
      //should have a filter

      if( 2 == argIndex ) {
	 //only one thing specified, is this the name of an existing filter?
	 const std::string kName( argv[1] );
	 //is this the name of a filter?
	 for(std::vector<JobControlNS::Holder<JobControlNS::FilterBase> >::const_iterator itFilter = m_paths.filters().begin();
	     itFilter != m_paths.filters().end();
	     ++itFilter) {
	    if( (*itFilter)->name() == kName) {
	       pFilter = *itFilter;
	       break;
	    }
	 }
      }
      if( pFilter.get() == 0 ) {
	 pFilter = implementCreateFilter("",argIndex-1,argv+1);
      }
   }
   //is the next argument a ">>" or the end?
   if( argc != argIndex ) {
      if(kSeperator != argv[argIndex]) {
	 throw CommandPattern::Keyword::UserException(std::string("Filter specification must be followed by ")+kSeperator);
      }
      ++argIndex;
   }

   if( pFilter.get() == 0 ) {
      //need a default filter
      pFilter = JobControlNS::Holder<JobControlNS::FilterBase>(new JobControlNS::FilterAnd(""));
   }
   
   //Now see if we have any Processor or sinks to add to the Path
   std::vector<Processor*> procs;
   std::vector<DataSinkBinder*> binders;
   std::string args;

   for(; argIndex != argc; ++argIndex ) {
      args = std::string(argv[argIndex]);
      //is this a Processor?
      if(m_procM->alreadyLoaded(args)  ) {
         //is it already being used?
         //in a filter?
         DABoolean notUsed = true;
         m_paths.processorNotBeingUsed(args, notUsed);
         if( ! notUsed ) {
            throw CommandPattern::Keyword::UserException(std::string("The processor ")+args+" is being used in a filter so can not be an operation.");
         }
         //in another path?
         for(std::vector<JobControlNS::Path*>::const_iterator itPath = m_paths.paths().begin();
             itPath != m_paths.paths().end();
             ++itPath) {
            for(std::vector<Processor*>::const_iterator itProc = (*itPath)->operations().begin();
                itProc != (*itPath)->operations().end();
                ++itProc) {
               if( (*itProc)->name() == args ) {
                  throw CommandPattern::Keyword::UserException(std::string("The processor ")+args+" is already in the path "+(*itPath)->name() + " as an operation so can not be used again.");
               }
            }
         }
         procs.push_back(m_procM->fetch(args) );
      } else if( m_sinkM->hasSink(args) ) {
         //is this a sink?
         if( m_sinkM->isUnused(args) ) {
            binders.push_back(m_sinkM->binderFor(args));
         } else {
            throw CommandPattern::Keyword::UserException(std::string("The sink ")+args+"is already in use.");
         }
      } else {
         throw CommandPattern::Keyword::UserException(args+" is not the name of a Processor nor a Sink");
      }
   }
   try {
      m_paths.add( new JobControlNS::Path(kName, pFilter.get(), procs, binders) );

      //now that sinks are in the path, remove them from use
      for( std::vector<DataSinkBinder*>::iterator itBinder = binders.begin();
           itBinder != binders.end();
           ++itBinder ) {
         m_sinkM->useSink( *itBinder );
      }
   } catch(const DAExceptionBase& iException ) {
      throw CommandPattern::Keyword::UserException(iException.what());
   }
   return Command::COMMAND_OK;
}

void
PathModule::removePath(const std::string& iPath)
{
   for(std::vector<JobControlNS::Path*>::const_iterator itPath = m_paths.paths().begin();
       itPath != m_paths.paths().end();
       ++itPath) {
      if( (*itPath)->name() == iPath ) {
         m_paths.remove( (*itPath) );
         return;
      }
   }
   throw CommandPattern::Keyword::UserException(std::string("No path named ")+iPath+" exists");
}

void
PathModule::removeFilter(const std::string& iFilter)
{
   for(std::vector<JobControlNS::Holder<JobControlNS::FilterBase> >::const_iterator itFilter = m_paths.filters().begin();
       itFilter != m_paths.filters().end();
       ++itFilter) {
      if( (*itFilter)->name() == iFilter) {
         if( m_paths.remove((*itFilter).get()) ) {
            return;
         } else {
            throw CommandPattern::Keyword::UserException(std::string("The filter named ")+iFilter+" is in use by a path or another filter so can not be removed");
         }
      }
   }
   throw CommandPattern::Keyword::UserException(std::string("No filter named ")+iFilter+" exists");
}

void
PathModule::reorder(const std::vector<std::string>& iNames )
{
   
   if( iNames.size() < m_paths.paths().size() ) {
      throw CommandPattern::Keyword::UserException(std::string("Not all paths are specified in reorder list") );
   }
   std::vector<JobControlNS::Path*> pathOrder;
   pathOrder.reserve(iNames.size() );
   for( std::vector<std::string>::const_iterator itName = iNames.begin();
        itName != iNames.end();
        ++itName) {
      std::vector<JobControlNS::Path*>::const_iterator itPath = m_paths.paths().begin();
      for(;
          itPath != m_paths.paths().end();
          ++itPath) {
         if( (*itPath)->name() == *itName ) {
            //is it already in the list?
            for(std::vector<JobControlNS::Path*>::iterator itPath2 = pathOrder.begin();
                itPath2 != pathOrder.end();
                ++itPath2) {
               if( (*itPath2) == (*itPath) ) {
                  throw CommandPattern::Keyword::UserException(std::string("The path ")+*itName+" appears multiple times in the list");
               }
            }
            pathOrder.push_back(*itPath);
            break;
         }
      }
      if( itPath == m_paths.paths().end() ) {
         throw CommandPattern::Keyword::UserException(std::string("No path named ")+*itName);
      }
   }
   m_paths.reorder(pathOrder);
}
//
// static member functions
//
