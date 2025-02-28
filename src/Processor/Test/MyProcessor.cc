// -*- C++ -*-
//
// Package:     <package>
// Module:      MyProcessor
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Thu Apr 17 18:04:32 EDT 1997
// $Id: MyProcessor.cc,v 1.3 2003/01/30 21:50:16 cdj Exp $
//
// Revision history
//
// $Log: MyProcessor.cc,v $
// Revision 1.3  2003/01/30 21:50:16  cdj
// get iostream header from C++Std package
//
// Revision 1.2  1998/03/27 15:27:05  mkl
// more naming fixups
//
// Revision 1.1.1.1  1997/05/23 20:18:01  mkl
// imported processor sources
//

// system include files
#include "C++Std/iostream.h"

// user include files
#if !defined(FILENAME_ONLY) /* relative path includes */
#include "Processor/Test/MyProcessor.h"

#else /* filename-only includes */
#include "MyProcessor.h"
#endif /* filename-only includes */

// STL classes

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyProcessor::MyProcessor( void ):
   m_data(0)
{
}

// MyProcessor::MyProcessor( const MyProcessor& )
// {
// }

MyProcessor::~MyProcessor()
{
}

//
// assignment operators
//
// const MyProcessor& MyProcessor::operator=( const MyProcessor& )
// {
// }

//
// member functions
//
void
MyProcessor::event( Frame& iFrame )
{
   cout <<"MyProcessor.Event:"<<m_data<<endl;
   return;
}

void
MyProcessor::beginRun( Frame& iFrame )
{
   cout <<"MyProcessor.BeginRun"<<endl;
   ++m_data;
   return;
}

//
// const member functions
//

//
// static member functions
//
