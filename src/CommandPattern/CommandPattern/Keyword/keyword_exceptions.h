#if !defined(COMMANDPATTERN_KEYWORD_EXCEPTIONS_H)
#define COMMANDPATTERN_KEYWORD_EXCEPTIONS_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      keyword_exceptions
// 
/**\class keyword_exceptions keyword_exceptions.h CommandPattern/keyword_exceptions.h

 Description: Standard exceptions thrown when using Keywords

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Jul 18 18:10:11 EDT 2003
// $Id: keyword_exceptions.h,v 1.1 2003/09/19 20:45:44 cdj Exp $
//
// Revision history
//
// $Log: keyword_exceptions.h,v $
// Revision 1.1  2003/09/19 20:45:44  cdj
// first submission
//

// system include files
#include <string>

// user include files
#include "CommandPattern/Keyword/ExceptionBase.h"

// forward declarations

namespace CommandPattern
{
namespace Keyword
{

class TooFewArgsException : public ExceptionBase
{
   public:
      TooFewArgsException(const string& iKeyword,
				    unsigned int iNeed,
				    unsigned int iGot ) :
	 m_keyword(iKeyword),
	 m_need(iNeed),
	 m_got(iGot) {}

      const char* what() const;

   private:
      string m_keyword;
      unsigned int m_need;
      unsigned int m_got;
      
      mutable string m_result;
};

class TooManyArgsException : public ExceptionBase
{
   public:
      TooManyArgsException(const string& iKeyword,
				    unsigned int iNeed,
				    unsigned int iGot ) :
	 m_keyword(iKeyword),
	 m_need(iNeed),
	 m_got(iGot) {}

      const char* what() const;

   private:
      string m_keyword;
      unsigned int m_need;
      unsigned int m_got;
      
      mutable string m_result;
};

class WrongNumberArgsException : public ExceptionBase
{
   public:
      WrongNumberArgsException(const string& iKeyword,
				    unsigned int iGot ) :
	 m_keyword(iKeyword),
	 m_got(iGot) {}

      const char* what() const;

   private:
      string m_keyword;
      unsigned int m_got;
      
      mutable string m_result;
};

class UnknownArgException : public ExceptionBase
{
   public:
      UnknownArgException(const string& iKeyword,
				    const string& iArg ) :
	 m_keyword(iKeyword),
	 m_arg(iArg) {}

      const char* what() const;

   private:
      string m_keyword;
      string m_arg;

      mutable string m_result;
};

class UserException : public ExceptionBase
{
   public:
     UserException(const string& iInfo) :
       m_info(iInfo) {}
     const char* what() const { return m_info.c_str();}
   private:
     string m_info;
};
} //namespace Keyword
} //namespace CommandPattern

#endif /* COMMANDPATTERN_KEYWORD_EXCEPTIONS_H */
