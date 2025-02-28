#if !defined(PACKAGE_UNIXFILEHANDLESTREAM_H)
#define PACKAGE_UNIXFILEHANDLESTREAM_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      UnixFileHandleStream
// 
/**\class UnixFileHandleStream UnixFileHandleStream.h package/UnixFileHandleStream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Thu Jan 23 15:36:12 EST 2003
// $Id: UnixFileHandleStream.h,v 1.1 2003/01/24 19:49:59 cdj Exp $
//
// Revision history
//
// $Log: UnixFileHandleStream.h,v $
// Revision 1.1  2003/01/24 19:49:59  cdj
// added UnixFileHandleStream to deal with case where ifstream was not extended to use filehandles
//

// system include files

// user include files

// forward declarations

#if defined(__GNUG__)
#include <iostream>
#include <ext/stdio_filebuf.h>
//This code is mostly copied from gcc 3.2 basic_ifstream definition
class UnixFileHandleStream : public basic_istream<char>
{
   public:
      // Types:
      typedef char                                      char_type;
      typedef char_traits<char_type>                    traits_type;
      typedef traits_type::int_type            int_type;
      typedef traits_type::pos_type            pos_type;
      typedef traits_type::off_type            off_type;
      
      // Non-standard types:
      typedef __gnu_cxx::stdio_filebuf<char_type, traits_type>     __filebuf_type;
      typedef basic_istream<char_type, traits_type>     __istream_type;
      
   private:
      __filebuf_type    _M_filebuf;
      
   public:
      // Constructors/Destructors:
      /** Default constructor.  Create an input file stream.  */
      //UnixFileHandleStream()
      //: __istream_type(NULL), _M_filebuf() { this->init(&_M_filebuf); }
      
      /**
       *  @brief Create an input file stream.
       *  @param  s  Null terminated string specifying filename.
       *  @param  mode  Open file in specified mode (see std::ios_base).
       *
       *  Tip:  When using std::string to hold the filename, you must use
       *  .c_str() before passing it to this constructor.
       */
      explicit UnixFileHandleStream(int iFileHandle, ios_base::openmode __mode = ios_base::in)
	 : __istream_type(NULL), _M_filebuf(iFileHandle, __mode,false, static_cast<int_type>(BUFSIZ)){
	    this->init(&_M_filebuf);
      }
      
      ~UnixFileHandleStream() { }
      
      // Members:
      /**
       *  @brief  Get a pointer to the file stream's buffer.
       *  @return Pointer to basic_filebuf.
       */
      __filebuf_type*
      rdbuf() const { return const_cast<__filebuf_type*>(&_M_filebuf); }

};
#else
#include "C++Std/fstream.h"
//ifstream already takes file handle as a constructor argument
typedef ifstream UnixFileHandleStream;

#endif
// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/UnixFileHandleStream.cc"
//#endif

#endif /* PACKAGE_UNIXFILEHANDLESTREAM_H */
