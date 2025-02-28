#if !defined(JOBCONTROL_PATH_H)
#define JOBCONTROL_PATH_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      Path
// 
/**\class Path Path.h JobControl/Path.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Jul 21 15:03:04 EDT 2003
// $Id: Path.h,v 1.2 2004/01/09 18:48:42 cdj Exp $
//
// Revision history
//
// $Log: Path.h,v $
// Revision 1.2  2004/01/09 18:48:42  cdj
// fix to path: needed to delay initialization of sinks until all sources and producers have been registered
//
// Revision 1.1  2003/09/19 21:26:57  cdj
// first submission of Path code
//

// system include files
#include <string>

#include "STLUtility/fwd_vector.h"

// user include files
#include "DataStorage/FrameStorer.h"
#include "SignalsSlots/SSSlotted.h"
#include "JobControl/FilterBase.h"

// forward declarations
class Processor;
class Frame;
class DataSinkBinder;

namespace JobControlNS {
class FilterBase;

class Path : public SSSlotted
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Path( const string& iName,
            FilterBase* iFilter,
	   const STL_VECTOR(Processor*)& iOpProcs,
	   const STL_VECTOR(DataSinkBinder*)& iSinks);
      virtual ~Path();

      // ---------- member functions ---------------------------

      ///returns false if a Processor wants the job to stop
      DABoolean execute(Frame& , DABoolean iContinueOnException);

      DABoolean removeSink(const DataSinkDescriptor& iSink);
      void addSink(const DataSinkBinder& iSink);
      
      void setFilter(FilterBase* iFilter) {
         m_filter = iFilter;
      }
      
      void initializeSinks();

      void isNotInOperations(const string& iName, DABoolean&);
      void notUsingSink(const string& iName, DABoolean&);
      
      // ---------- const member functions ---------------------
      DABoolean mustBeSequential() const;

      _framestorer_sinkdescriptors_ sinks() const; 

      const string& name() const { return m_name;}
      FilterBase* filter() const {return m_filter.get();}
      const STL_VECTOR(Processor*)& operations() const {return m_procOperations;}
      
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Path( const Path& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Path& operator=( const Path& ); // stop default

      // ---------- private member functions -------------------
      DABoolean removeSinkFromStorer(const DataSinkDescriptor& iSink);
      void addSinkToStorer(const DataSinkBinder& iSink);

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      Holder<FilterBase> m_filter;
      STL_VECTOR(Processor* ) m_procOperations;
      FrameStorer m_storer;
      string m_name;
 
      STL_VECTOR(DataSinkBinder*) m_uninitializedSinks;     
      // ---------- static data members ------------------------

};
// inline function definitions

}  //namespace JobControlNS

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/Path.cc"
//#endif

#endif /* JOBCONTROL_PATH_H */
