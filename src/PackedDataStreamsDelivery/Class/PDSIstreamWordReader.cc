// -*- C++ -*-
//
// Package:     <PackedDataStreamsDelivery>
// Module:      PDSIstreamWordReader
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Oct  6 14:33:54 EDT 2000
// $Id: PDSIstreamWordReader.cc,v 1.2 2001/01/15 21:07:55 cdj Exp $
//
// Revision history
//
// $Log: PDSIstreamWordReader.cc,v $
// Revision 1.2  2001/01/15 21:07:55  cdj
// Now properly reads Tags when doing byteSwapping
//
// Revision 1.1  2000/10/07 18:24:22  cdj
// can now read files that were written from a different endian machine
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <string>

// user include files
#include "Experiment/report.h"
#include "PackedDataStreamsDelivery/PDSIstreamWordReader.h"
#include "PackedDataStreamsDelivery/PDSDReadFailedException.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "PackedDataStreamsDelivery.PDSIstreamWordReader" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PDSIstreamWordReader.cc,v 1.2 2001/01/15 21:07:55 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//PDSIstreamWordReader::PDSIstreamWordReader()
//{
//}

// PDSIstreamWordReader::PDSIstreamWordReader( const PDSIstreamWordReader& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

PDSIstreamWordReader::~PDSIstreamWordReader()
{
}

//
// assignment operators
//
// const PDSIstreamWordReader& PDSIstreamWordReader::operator=( const PDSIstreamWordReader& rhs )
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
#undef FSTREAM_CANNOT_READ_LARGE_FILES_BUG

DABoolean
PDSIstreamWordReader::readWords( UInt32* iBuffer, 
				 unsigned int iNumberOfWords,
				 const char* iActivity )
{


// We can't proceed if the stream is already at the eof
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   if( m_stream.eof() ) { 
      report( ERROR, kFacilityString )
         << "Unable to open input file."  << std::endl ;
      return false ; 
   }
#endif

#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
// Obtain the file descriptor corresponding to input file stream
   int fileDescriptor = m_stream.rdbuf()->fd() ;
   if ( EOF == fileDescriptor ) {
      report( ERROR, kFacilityString )
         << "Unable to open input file."  << std::endl ;
      return false;
   }
#endif

// Read the record body

#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   m_stream.read( reinterpret_cast<char*>(iBuffer), 
		  sizeof(UInt32)*iNumberOfWords/sizeof(char) ) ;
   if ( m_stream.fail() ) {
      if( m_stream.eof() ) {
	 return false;
      } else {
	 //A problem occured
	 throw PDSDReadFailedException(iActivity);
      }
   }
#else
   int n_read = ::read( fileDescriptor,
			reinterpret_cast<char*>(iBuffer), 
			sizeof(UInt32)*iNumberOfWords/sizeof(char)) ;	
   if ( 0 > n_read )
   {
      std::string errorReport = std::string(iActivity) + std::string("/n system error: ")
	 + std::string( strerror( errno ) );
      throw PDSReadFailedException( iActivity );
   }
   else if ( 0 == n_read ) {
      //end of file
      return false;
   }
#endif
   
   return true;
}

void
PDSIstreamWordReader::unswapString( UInt32* iBegin, UInt32 iNumberOfStrings ) 
{
   //don't need to do anything since array was never swapped to begin with
}

void
PDSIstreamWordReader::unswapStringArray( UInt32* iBegin, 
					 UInt32* iEnd ) 
{
   //don't need to do anything since array was never swapped to begin with
}

void 
PDSIstreamWordReader::skipWords( unsigned int iNumberOfWordsToSkip )
{
#if defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
   int fileDescriptor = m_stream.rdbuf()->fd() ;
#endif

   unsigned int bytesToSkip = iNumberOfWordsToSkip*sizeof(UInt32)/sizeof(char);
   if( 0 < iNumberOfWordsToSkip ) {
// Ignore all the remaining words but the last
#if !defined(FSTREAM_CANNOT_READ_LARGE_FILES_BUG)
      m_stream.ignore( bytesToSkip ) ;
#else
      char* bufferToTrash = new char[bytesToSkip];
      
      int n_read = ::read( fileDescriptor,
			   bufferToTrash,
			   bytesToSkip ) ;
      delete [] bufferToTrash;
#endif
   }

}

//
// static member functions
//
