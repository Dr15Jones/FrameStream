#if !defined(JOBCONTROL_PATHMODULE_H)
#define JOBCONTROL_PATHMODULE_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      PathModule
// 
/**\class PathModule PathModule.h JobControl/PathModule.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul  7 11:03:46 EDT 2003
// $Id: PathModule.h,v 1.1 2003/09/19 21:26:57 cdj Exp $
//
// Revision history
//
// $Log: PathModule.h,v $
// Revision 1.1  2003/09/19 21:26:57  cdj
// first submission of Path code
//

// system include files
#include <string>
#include <vector>

// user include files
#include "CommandPattern/Module.h"
#include "JobControl/ProcessingPaths.h"
#include "CommandPattern/CPCommandWithKeywords.h"

// forward declarations
class MasterProcessor;
class SinkManager;


class PathModule : public Module
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      //holds onto these references
      PathModule(SinkManager&,
		 MasterProcessor&);

      virtual ~PathModule();

      // ---------- member functions ---------------------------
      ProcessingPaths& processingPaths() {
	 return m_paths; }

      int createFilter( int argc, char** argv );
      int createPath( int argc, char** argv );
      
      ///Throws CommandPattern::Keyword::UserException if error
      void removePath(const std::string& iName);
      ///Throws CommandPattern::Keyword::UserException if error
      void removeFilter( const std::string& iName);

      void reorder(const std::vector<std::string>& iNames);
      // ---------- const member functions ---------------------
      std::string listPaths() ;
      std::string listFilters();

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PathModule( const PathModule& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PathModule& operator=( const PathModule& ); // stop default

      // ---------- private member functions -------------------
      JobControlNS::Holder<JobControlNS::FilterBase> implementCreateFilter(
	 const std::string& iName,
	 int argc, 
	 char** argv);

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      ProcessingPaths m_paths;
      CPCommandWithKeywords m_command;
      
      SinkManager* m_sinkM;
      MasterProcessor* m_procM;
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/PathModule.cc"
//#endif

#endif /* JOBCONTROL_PATHMODULE_H */
