#if !defined(JOBCONTROL_PROCESSINGPATHS_H)
#define JOBCONTROL_PROCESSINGPATHS_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      ProcessingPaths
// 
/**\class ProcessingPaths ProcessingPaths.h JobControl/ProcessingPaths.h

 Description: Handles processing of the list of Paths

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Tue Jul  8 14:10:53 EDT 2003
// $Id: ProcessingPaths.h,v 1.1 2003/09/19 21:26:58 cdj Exp $
//
// Revision history
//
// $Log: ProcessingPaths.h,v $
// Revision 1.1  2003/09/19 21:26:58  cdj
// first submission of Path code
//

// system include files
#include <vector>
#include <string>

// user include files
#include "SignalsSlots/SSSlotted.h"

#include "DataStorage/FrameStorer.h"

#include "STLUtility/fwd_vector.h"

#include "JobControl/FilterBase.h"

// forward declarations
class SinkManager;
class MasterProcessor;
class FrameDeliverer;
class Processor;
class Frame;
namespace JobControlNS {
class Path;
class FilterBase;
class FilterProc;
class FilterAnd;
}

class ProcessingPaths : public SSSlotted
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      ProcessingPaths(SinkManager& iSM,
		      MasterProcessor& iMP);
      virtual ~ProcessingPaths();

      // ---------- member functions ---------------------------
      virtual DABoolean initialize(FrameDeliverer&);

      virtual DABoolean processStop(Frame&, DABoolean iContinueIfException);

      ///Takes ownership of object and returns false if problem with object
      DABoolean add( JobControlNS::Path* );
      ///Takes ownership of object and returns false if problem with object
      DABoolean add( JobControlNS::FilterBase* );

      DABoolean remove(JobControlNS::Path* );
      DABoolean remove(JobControlNS::FilterBase* );
      
      ///assumes all Paths are specified in the list
      void reorder(const STL_VECTOR(JobControlNS::Path*)& iOrder);
      
      //slots
      void addSink(const string&);
      void removeSink(const string&);

      void addProcessor(const string&);
      void removeProcessor(const string&);

      void processorNotBeingUsed(const string&, DABoolean&);
      
      // ---------- const member functions ---------------------
      const STL_VECTOR(JobControlNS::Path*)& paths() const { return m_paths; }
      const STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterBase> )& filters() const {return m_definedFilters;}
      const STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterProc> )& filterProcs() const {return m_filterProcs;}

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ProcessingPaths( const ProcessingPaths& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ProcessingPaths& operator=( const ProcessingPaths& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      SinkManager* m_sinkManager;
      MasterProcessor* m_masterProcessor;

      STL_VECTOR(JobControlNS::Path*) m_paths;

      STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterBase> ) m_definedFilters;
      
      STL_VECTOR(JobControlNS::Holder<JobControlNS::FilterProc> ) m_filterProcs;
      
      JobControlNS::FilterAnd* m_defaultFilter;
      
      DABoolean m_usingDefault;
      DABoolean m_procsChanged;
      DABoolean m_sinksChanged;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/ProcessingPaths.cc"
//#endif

#endif /* JOBCONTROL_PROCESSINGPATHS_H */
