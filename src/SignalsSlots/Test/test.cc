// -*- C++ -*-
//
// Package:     <package>
// Module:      test
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 16:11:41 EDT 2003
// $Id: test.cc,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: test.cc,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
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
#include <iostream>

// user include files
//#include "Experiment/report.h"
#include "SignalsSlots/SSSlotted.h"
#include "SignalsSlots/SSSignal_0.h"
#include "SignalsSlots/SSSignal_1.h"

class Bar : public SSSlotted
{
   public:
      
      void callThis() {cout <<"called"<<std::endl;}
      
      void callThisArg(int iValue) { cout <<"called with "<<iValue <<std::endl;}
      
      void callFloatArg(float iValue) {
	 cout <<"called with float "<<iValue <<std::endl; }
 
#if defined(TEST_BAD_ARGUMENT_TYPE)
      void callBad(const Bar& ) {
	 cout <<"called bad"<<std::endl;
      }
#endif
};

class Foo
{
   public:
      SSSignal_0 mySignal;
      SSSignal_1<int> myArgSignal;
};

int
main()
{
   Foo foo;
   Bar bar;
   
   foo.mySignal.attach(&bar, &Bar::callThis );
   foo.mySignal.emit();
   cout <<"-----------"<<std::endl;
   {
      //test use of temporary slotted
      Bar bar2;
      foo.mySignal.attach(&bar2, &Bar::callThis );
      
      foo.mySignal.emit();
      cout <<"-----------"<<std::endl;
   }
   foo.mySignal.emit();
   cout <<"-----------"<<std::endl;

   {
      //test use of temporary signal
      Foo foo2;
      
      foo2.mySignal.attach(&bar, &Bar::callThis );
      foo2.mySignal.emit();
      cout <<"-----------"<<std::endl;
   }

   //test signals with arguments
   foo.myArgSignal.attach(&bar, &Bar::callThisArg);
   foo.myArgSignal.attach(&bar, &Bar::callFloatArg);
   foo.myArgSignal.emit(1);
   cout <<"-----------"<<std::endl;
   foo.myArgSignal.emit(2);
   cout <<"-----------"<<std::endl;

#if defined(TEST_BAD_ARGUMENT_TYPE)
   foo.myArgSignal.attach(&bar, &Bar::callBad);
#endif
   
   return 0;
}
