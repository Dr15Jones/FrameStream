#if !defined(DATAHANDLER_STREAMCONSTANTS_DECL_H)
#define DATAHANDLER_STREAMCONSTANTS_DECL_H
// -*- C++ -*-
//
// Package:     DataHandler
// Module:      Stream
// 
// Description: Experiement dependent declarations of Stream Constants
//
// Usage:
//
// Author:      Simon Patton
// Created:     Wed Nov 19 10:09:56 EST 1997
// $Id: StreamConstants_decl.h,v 1.10 2003/10/10 23:10:44 cdj Exp $
//
// Revision history
//
// $Log: StreamConstants_decl.h,v $
// Revision 1.10  2003/10/10 23:10:44  cdj
// added Stream::kMaterial
//
// Revision 1.9  2003/02/04 14:39:16  huanggs
// Stream::kZDSimulation added
//
// Revision 1.8  2002/11/07 20:39:35  huanggs
// Stream::kZDAlignment added
//
// Revision 1.8  2002/11/04 huanggs
// added Stream::kZDAlignment as needed by StreamConstants_defn.h
//
// Revision 1.7  1999/06/22 19:21:08  cdj
// added Physics stream
//
// Revision 1.6  1999/05/13 18:42:10  dlk
// DLK: In StreamConstants_decl.h
// 	Set stream priorities kStartRunPriority and kPauseRunPriority
// DLK: In StreamConstants_defn.h
// 	Define StartRun and PauseRun streams
//
// Revision 1.5  1998/11/21 20:16:49  cdj
// made endrun priority less than event priority to avoid trying to serve
// endruns at the beginning of a run
//
// Revision 1.4  1998/11/04 21:57:30  mkl
// added new *Calibration and *Simulation streams
//
// Revision 1.3  1998/03/31 20:20:53  cdj
// added preliminary geometry streams
//
// Revision 1.2  1997/11/28 19:49:16  mkl
// added Stream::kDRAlignment as needed by StreamConstants_defn.h
//
// Revision 1.1  1997/11/19 15:17:42  sjp
// New file for Experiment dependent Stream declarations
//

// Stream Priorities
      //These priorities of the various standard streams need to be
      // accessible to users during global initialization.  This is
      // not possible using E.g. Stream::kEvent.priority() since 
      // the order inwhich global (and static) data is initialized is
      // not guaranteed.
      enum { kBeginRunPriority        = Type::kDefaultPriority-100,
	     kStartRunPriority        = kBeginRunPriority-10,
	     kEventPriority           = kBeginRunPriority-100,
	     kPauseRunPriority        = kBeginRunPriority-20,
	     kEndRunPriority          = kEventPriority - 100,
	     kHardwarePriority        = Type::kDefaultPriority,
	     kBaseGeometryPriority    = Type::kDefaultPriority+100,
	     kAlignmentPriority       = Type::kDefaultPriority,
	     kAlignedGeometryPriority = kAlignmentPriority-50,
	     kCalibrationPriority     = Type::kDefaultPriority,
	     kSimulationPriority      = Type::kDefaultPriority,
	     kMaterialPriority        = kBaseGeometryPriority+50,
	     kPhysicsPriority         = kBaseGeometryPriority+100
      };

// Stream Constants
      static const Type kNone;

      static const Type kPhysics;

      static const Type kBeginRun;
      static const Type kEndRun;
      static const Type kEvent;
      static const Type kStartRun;
      static const Type kPauseRun;

      static const Type kHardware;

      static const Type kMaterial;
      static const Type kBaseGeometry;
      static const Type kAlignedGeometry;

      static const Type kDRAlignment;
      static const Type kZDAlignment;
      static const Type kSVAlignment;
      static const Type kRICHAlignment;
      static const Type kCCAlignment;
      static const Type kMUAlignment;

      static const Type kCalibration;
      static const Type kDRCalibration;
      static const Type kSVCalibration;
      static const Type kRICHCalibration;
      static const Type kCCCalibration;
      static const Type kMUCalibration;

      static const Type kDRSimulation;
      static const Type kZDSimulation;
      static const Type kSVSimulation;
      static const Type kRICHSimulation;
      static const Type kCCSimulation;
      static const Type kMUSimulation;

#endif /* DATAHANDLER_STREAMCONSTANTS_DECL_H */

