#if !defined(PROCESSOR_ACTIONRESULT_INC)
#define PROCESSOR_ACTIONRESULT_INC
#if defined( THIS_WILL_NEVER_BE_TRUE )
C// -*- C++ -*-
C//
C// Package:     Processor
C// Module:      ActionResult
C// 
C// Description: hardwired return types to be the same for c++ and fortran
C//
C// Usage:
C//
C// Author:      Martin Lohner
C// Created:     Tue Feb 10 11:32:47 EDT 1998
C// $Id: ActionResult.inc,v 1.2 1998/07/21 16:23:25 mkl Exp $
C//
C// Revision history
C//
C// $Log: ActionResult.inc,v $
C// Revision 1.2  1998/07/21 16:23:25  mkl
C// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
C//
C// Revision 1.1  1998/02/10 18:07:04  mkl
C// return from fortran 'actions' handled
C//
C//
#endif
#define kActionPassed          0
#define kActionFailed          1
#define kActionError           2
#define kActionNoAction        3
#define kActionStopProcessLoop 4
#endif 



