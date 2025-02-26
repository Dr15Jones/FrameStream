#if !defined(CPPSTD_IOMANIP_H)
#define CPPSTD_IOMANIP_H
// -*- C++ -*-
//
// Package:     <C++Std>
// Module:      iomanip
// 
/**\class iomanip iomanip.h C++Std/iomanip.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      CLEO DAQ testing
// Created:     Fri Aug 24 09:03:20 EDT 2001
// $Id: iomanip.h,v 1.1 2001/09/07 16:49:43 cleo3 Exp $
//
// Revision history
//
// $Log: iomanip.h,v $
// Revision 1.1  2001/09/07 16:49:43  cleo3
// first submission
//

// system include files

// user include files

// forward declarations
#include <iomanip.h>

#if !defined(IOMANIP_IS_CPP_MACRO_BUG)
template<class T>
class OManip
{
   public:
    OManip(ostream& (*pf)(ostream&, T), T manarg)
      : m_pf(pf)
      , m_manarg(manarg)
    { ; }
      
    ostream&  (*m_pf)(ostream&, T);
    T         m_manarg;

};

template<class T>
inline ostream& operator<<(ostream& os, const OManip<T>& a)
{
   (*a.m_pf)(os, a.m_manarg);
   
   return os;
}

#endif

#endif /* C++STD_IOMANIP_H */
