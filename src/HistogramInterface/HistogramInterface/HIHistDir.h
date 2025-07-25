#if !defined(HISTOGRAMINTERFACE_HIHISTDIR_H)
#define HISTOGRAMINTERFACE_HIHISTDIR_H
// -*- C++ -*-
//
// Package:     HistogramInterface
// Module:      HIHistDir
// 
// Description: Abstract interface for directories containing histograms
//
// Usage:
//    <usage>
//
// Author:      Marc Soussa
// Created:     Tue Dec  1 15:34:52 EST 1998
// $Id: HIHistDir.h,v 1.8 2003/01/17 20:34:31 cdj Exp $
//
// Revision history
//
// $Log: HIHistDir.h,v $
// Revision 1.8  2003/01/17 20:34:31  cdj
// use namespace to avoid using template math operations with non-histogram code
//
// Revision 1.7  2002/12/05 21:46:41  cleo3
// dealt with fact that g++ vector iterators are not pointers
//
// Revision 1.6  2001/07/21 15:43:48  cdj
// can now iterate through HIHistDir's contents
//
// Revision 1.5  1999/10/07 18:05:05  hufnagel
// Numbers now use float instead of double
//
// Revision 1.4  1999/09/29 17:52:03  cdj
// added histogram directories
//// Revision 1.3  1999/09/07 21:20:46  mkl
// make cxx happy
//
// Revision 1.2  1999/09/07 18:53:29  mkl
// new histogram interface
//
// Revision 1.1.1.1  1999/02/16 22:07:03  cdj
// first submission
//

// system include files
#include <string>
#include <vector>
#include "HistogramInterface/HIHistProf.h"
// user include files

#if !defined(NO_KOENIG_LOOKUP_RULE_BUG)
#define HISTOGRAMINTERFACE_NS HistogramInterface::
namespace HistogramInterface {
#else
#define HISTOGRAMINTERFACE_NS
#endif
class HIHist1D;
class HIHist2D;
#if !defined(NO_KOENIG_LOOKUP_RULE_BUG)
};
#endif

class HINtuple;
class HIHistProf;
class HINumber;
class HINumberWithErrors;

// forward declarations
#define HIDIR_FUNCS(_type_, _prefix_) \
public:\
const_ ## _prefix_ ## _iterator _prefix_ ## _begin() const { \
   std::vector<void*>::const_iterator t = m_ ## _prefix_ ## List.begin(); \
   return *reinterpret_cast<const_ ## _prefix_ ## _iterator *>(&t); } \
const_ ## _prefix_ ## _iterator _prefix_ ## _end() const { \
   std::vector<void*>::const_iterator t = m_ ## _prefix_ ## List.end(); \
   return *reinterpret_cast<const_ ## _prefix_ ## _iterator *> (&t); } \
protected: \
_prefix_ ## _iterator _prefix_ ## _begin() { \
   std::vector<void*>::iterator t = m_ ## _prefix_ ## List.begin(); \
   return *reinterpret_cast< _prefix_ ## _iterator *>(&t); } \
_prefix_ ## _iterator _prefix_ ## _end() { \
   std::vector<void*>::iterator t = m_ ## _prefix_ ## List.end(); \
   return *reinterpret_cast< _prefix_ ## _iterator *> (&t); } \
void _prefix_ ## Empty(); \
private: \
_type_* insert( _type_ * iEntry ) { m_ ## _prefix_ ## List.push_back(iEntry); return iEntry; }\
std::vector<void*> m_ ## _prefix_ ##List; \
public:


class HIHistDir 
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef std::vector<HISTOGRAMINTERFACE_NS HIHist1D*>::const_iterator const_h1d_iterator;
      typedef std::vector<HISTOGRAMINTERFACE_NS HIHist2D*>::const_iterator const_h2d_iterator;
      typedef std::vector<HINtuple*>::const_iterator const_nt_iterator;
      typedef std::vector<HIHistProf*>::const_iterator const_prof_iterator;
      typedef std::vector<HINumber*>::const_iterator const_n_iterator;
      typedef std::vector<HINumberWithErrors*>::const_iterator const_ne_iterator;
      typedef std::vector<HIHistDir*>::const_iterator const_dir_iterator;

      typedef std::vector<HISTOGRAMINTERFACE_NS HIHist1D*>::iterator h1d_iterator;
      typedef std::vector<HISTOGRAMINTERFACE_NS HIHist2D*>::iterator h2d_iterator;
      typedef std::vector<HINtuple*>::iterator nt_iterator;
      typedef std::vector<HIHistProf*>::iterator prof_iterator;
      typedef std::vector<HINumber*>::iterator n_iterator;
      typedef std::vector<HINumberWithErrors*>::iterator ne_iterator;
      typedef std::vector<HIHistDir*>::iterator dir_iterator;
      // ---------- Constructors and destructor ----------------     
      HIHistDir( const std::string& iName ) : m_name( iName ) {}
      virtual ~HIHistDir();

      // ---------- member functions ---------------------------

      /// Make a  sub directory with name iName
      virtual HIHistDir* mkdir( const std::string& iName) {
	 return insert(makeDir(iName) ); }

      // create generic histograms and ntuples
      /// 1D histogram
      HISTOGRAMINTERFACE_NS HIHist1D*
      histogram( Count          iId, 
		 const std::string&  iTitle,
		 unsigned int   iNChannels, 
		 float          iLowEdge,
		 float          iHighEdge,
		 float          iBitsPerChannel=0){ 
	 return insert(makeHistogram(iId, iTitle, iNChannels, iLowEdge, iHighEdge, iBitsPerChannel)); }
      
      /// 1D histogram with automatic id assignment
      HISTOGRAMINTERFACE_NS HIHist1D* 
      histogram( const std::string&  iTitle,
		 unsigned int   iNChannels, 
		 float          iLowEdge,
		 float          iHighEdge,
		 float          iBitsPerChannel=0) { 
	 return insert(makeHistogram(nextId(),iTitle, iNChannels, iLowEdge, iHighEdge, iBitsPerChannel)); }

      /// 2D histogram
      HISTOGRAMINTERFACE_NS HIHist2D* 
      histogram( Count          iId,
		 const std::string&  iTitle,
		 unsigned int   iNChannelsX, 
		 float          iLowEdgeX, 
		 float          iHighEdgeX,
		 unsigned int   iNChannelsY, 
		 float          iLowEdgeY, 
		 float          iHighEdgeY,
		 float          iBitsPerChannel=0) { 
	 return insert(makeHistogram(iId, iTitle, iNChannelsX, iLowEdgeX, iHighEdgeX, iNChannelsY, iLowEdgeY, iHighEdgeY, iBitsPerChannel)); }
      
      /// 2D histogram with automatic id assignment
      HISTOGRAMINTERFACE_NS HIHist2D* 
      histogram( const std::string&  iTitle,
		 unsigned int   iNChannelsX, 
		 float          iLowEdgeX, 
		 float          iHighEdgeX,
		 unsigned int   iNChannelsY, 
		 float          iLowEdgeY, 
		 float          iHighEdgeY,
		 float          iBitsPerChannel=0) { 
	 return insert(makeHistogram(nextId(),iTitle, iNChannelsX, iLowEdgeX, iHighEdgeX, iNChannelsY, iLowEdgeY, iHighEdgeY, iBitsPerChannel)); }
      
      /// profile histogram
      HIHistProf* profile( Count          iId,
			   const std::string&  iTitle,
			   unsigned int   iNChannels, 
			   float iLowEdgeX, 
			   float iHighEdgeX,
			   float iLowEdgeY, 
			   float iHighEdgeY,
			   HIHistProf::DisplayErrorsAs iDisplayErrorsAs ) { 
	 return insert(makeProfile(iId, iTitle, iNChannels, iLowEdgeX, iHighEdgeX, iLowEdgeY, iHighEdgeY, iDisplayErrorsAs)); }

      /// profile histogram with automatic id assignment
      virtual HIHistProf* profile( const std::string&  iTitle,
				   unsigned int   iNChannels, 
				   float iLowEdgeX, 
				   float iHighEdgeX,
				   float iLowEdgeY, 
				   float iHighEdgeY,
				   HIHistProf::DisplayErrorsAs iDisplayErrorsAs ) { 
	 return insert(makeProfile(nextId(),iTitle, iNChannels, iLowEdgeX, iHighEdgeX, iLowEdgeY, iHighEdgeY, iDisplayErrorsAs)); }

      /// ntuple
      HINtuple* ntuple(    Count          iId,
			   const std::string&  iTitle,
			   unsigned int   iSizeOfEntry,
			   unsigned int   iChunkSize,
			   const char* const* iLabels) { 
	 return insert(makeNtuple(iId, iTitle, iSizeOfEntry, iChunkSize, iLabels)); }
 
      /// ntuple histogram with automatic id assignment
      HINtuple* ntuple(    const std::string&  iTitle,
			   unsigned int   iSizeOfEntry,
			   unsigned int   iChunkSize,
			   const char* const* iLabels) { 
	 return insert(makeNtuple(nextId(),iTitle, iSizeOfEntry, iChunkSize, iLabels)); }

      /// create an updatable number (needed for Online)
      HINumber* number( const std::string& iName,
			float        iValue ) { 
	 return insert(makeNumber(iName, iValue)); }

      /// create an updatable number with errors (needed for Online)
      HINumberWithErrors* numberWithErrors( 
	 const std::string& iName,
	 float        iValue,
	 float        iPositiveError,
	 float        iNegativeError ) { 
	 return insert(makeNumberWithErrors(iName, iValue, iPositiveError, iNegativeError)); }
      
      // ---------- const member functions ---------------------
      const std::string& name() const { return m_name; }

      HIDIR_FUNCS(HISTOGRAMINTERFACE_NS HIHist1D, h1d)
      HIDIR_FUNCS(HISTOGRAMINTERFACE_NS HIHist2D, h2d)
      HIDIR_FUNCS(HINtuple, nt)
      HIDIR_FUNCS(HIHistProf, prof)
      HIDIR_FUNCS(HINumber, n)
      HIDIR_FUNCS(HINumberWithErrors, ne)
      HIDIR_FUNCS(HIHistDir, dir)

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // Make a  sub directory with name iName
      virtual HIHistDir* makeDir( const std::string& iName) = 0;

      // create generic histograms and ntuples
      virtual HISTOGRAMINTERFACE_NS HIHist1D* 
      makeHistogram( Count          iId, 
		     const std::string&  iTitle,
		     unsigned int   iNChannels, 
		     float          iLowEdge,
		     float          iHighEdge,
		     float          iBitsPerChannel=0) =0;
            
      virtual HISTOGRAMINTERFACE_NS HIHist2D* 
      makeHistogram( Count          iId,
		     const std::string&  iTitle,
		     unsigned int   iNChannelsX, 
		     float          iLowEdgeX, 
		     float          iHighEdgeX,
		     unsigned int   iNChannelsY, 
		     float          iLowEdgeY, 
		     float          iHighEdgeY,
		     float          BitsPerChannel=0) =0;
      
      virtual HIHistProf* makeProfile( Count          iId,
				       const std::string&  iTitle,
				       unsigned int   iNChannels, 
				       float iLowEdgeX, 
				       float iHighEdgeX,
				       float iLowEdgeY, 
				       float iHighEdgeY,
				       HIHistProf::DisplayErrorsAs iDisplayErrorsAs ) =0;
      
      virtual HINtuple* makeNtuple(    Count          iId,
				       const std::string&  iTitle,
				       unsigned int   iSizeOfEntry,
				       unsigned int   iChunkSize,
				       const char* const* iLabels) =0; 
            
      virtual HINumber* makeNumber( const std::string& iName,
				    float        iValue ) =0;
      
      virtual HINumberWithErrors* makeNumberWithErrors( 
	 const std::string& iName,
	 float        iValue,
	 float        iPositiveError,
	 float        iNegativeError ) =0;

      virtual Count nextId() = 0;
      // ---------- protected const member functions -----------
      
   private:
      // ---------- Constructors and destructor ----------------
      HIHistDir( const HIHistDir& ); // stop default
      
      // ---------- assignment operator(s) ---------------------
      const HIHistDir& operator=( const HIHistDir& ); // stop default
      
      // ---------- private member functions -------------------
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------
      std::string m_name;
      
      // ---------- static data members ------------------------
      
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "HISTOGRAMINTERFACE/Template/HIHistDir.cc"
//#endif

#endif /* HISTOGRAMINTERFACE_HIHistDIR_H */
