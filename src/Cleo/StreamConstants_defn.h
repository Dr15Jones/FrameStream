#if !defined(DATAHANDLER_STREAMCONSTANTS_DEFN_H)
#define DATAHANDLER_STREAMCONSTANTS_DEFN_H
// -*- C++ -*-
//
// Package:     DataHandler
// Module:      Stream
// 
// Description: Experiement dependent defenition of Stream Constants
//
// Implimentation:
//
// Author:      Simon Patton
// Created:     Wed Nov 19 10:09:56 EST 1997
// $Id: StreamConstants_defn.h,v 1.9 2003/10/10 23:10:44 cdj Exp $
//
// Revision history
//
// $Log: StreamConstants_defn.h,v $
// Revision 1.9  2003/10/10 23:10:44  cdj
// added Stream::kMaterial
//
// Revision 1.8  2003/02/04 14:39:05  huanggs
// Stream::kZDSimulation added
//
// Revision 1.7  2002/11/07 20:39:35  huanggs
// Stream::kZDAlignment added
//
// Revision 1.7  2002/11/04 huanggs
// added Stream::kZDAlignment
//
// Revision 1.6  1999/06/22 19:21:09  cdj
// added Physics stream
//
// Revision 1.5  1999/05/13 18:42:10  dlk
// DLK: In StreamConstants_decl.h
// 	Set stream priorities kStartRunPriority and kPauseRunPriority
// DLK: In StreamConstants_defn.h
// 	Define StartRun and PauseRun streams
//
// Revision 1.4  1998/11/04 21:57:34  mkl
// added new *Calibration and *Simulation streams
//
// Revision 1.3  1998/03/31 20:20:56  cdj
// added preliminary geometry streams
//
// Revision 1.2  1997/12/08 17:20:11  mkl
// change of label for dralignment stream
//
// Revision 1.1  1997/11/19 15:18:01  sjp
// New file for Experiment dependent Stream definitions
//

//
// Stream Constants
//
const Stream::Type
Stream::kPhysics("physics", 
		  Stream::kPhysicsPriority, 
		  true);
const Stream::Type
Stream::kBeginRun("beginrun", 
		  Stream::kBeginRunPriority, 
		  true);
const Stream::Type
Stream::kEndRun("endrun", 
		Stream::kEndRunPriority, 
		true );
const Stream::Type
Stream::kEvent("event", 
	       Stream::kEventPriority, 
	       true);
const Stream::Type
Stream::kStartRun("startrun", 
		  Stream::kStartRunPriority, 
		  true);
const Stream::Type
Stream::kPauseRun("pauserun", 
		  Stream::kPauseRunPriority, 
		  true);

const Stream::Type
Stream::kHardware("hardware", 
		  Stream::kHardwarePriority, 
		  true);

const Stream::Type
Stream::kMaterial("material", 
		  Stream::kMaterialPriority, 
		  true );

const Stream::Type
Stream::kBaseGeometry("basegeometry", 
		  Stream::kBaseGeometryPriority, 
		  true );
const Stream::Type
Stream::kAlignedGeometry("alignedgeometry", 
		  Stream::kAlignedGeometryPriority, 
		  true );

const Stream::Type
Stream::kDRAlignment("dralignment", 
		     Stream::kAlignmentPriority, 
		     true);
const Stream::Type
Stream::kZDAlignment("zdalignment", 
		     Stream::kAlignmentPriority, 
		     true);
const Stream::Type
Stream::kSVAlignment("svalignment", 
		     Stream::kAlignmentPriority, 
		     true);
const Stream::Type
Stream::kRICHAlignment("richalignment", 
		     Stream::kAlignmentPriority, 
		     true);
const Stream::Type
Stream::kCCAlignment("ccalignment", 
		     Stream::kAlignmentPriority, 
		     true);
const Stream::Type
Stream::kMUAlignment("mualignment", 
		     Stream::kAlignmentPriority, 
		     true);

const Stream::Type
Stream::kCalibration("calibration", 
		     Stream::kCalibrationPriority, 
		     true);
const Stream::Type
Stream::kDRCalibration( "drcalibration", 
			Stream::kCalibrationPriority, 
			true);
const Stream::Type
Stream::kSVCalibration( "svcalibration", 
			Stream::kCalibrationPriority, 
			true);
const Stream::Type
Stream::kRICHCalibration( "richcalibration", 
			  Stream::kCalibrationPriority, 
			  true);
const Stream::Type
Stream::kCCCalibration( "cccalibration", 
			Stream::kCalibrationPriority, 
			true);
const Stream::Type
Stream::kMUCalibration( "mucalibration", 
			Stream::kCalibrationPriority, 
			true);

const Stream::Type
Stream::kDRSimulation( "drsimulation", 
		       Stream::kSimulationPriority, 
		       true);
const Stream::Type
Stream::kZDSimulation( "zdsimulation", 
		       Stream::kSimulationPriority, 
		       true);
const Stream::Type
Stream::kSVSimulation( "svsimulation", 
		       Stream::kSimulationPriority, 
		       true);
const Stream::Type
Stream::kRICHSimulation( "richsimulation", 
			 Stream::kSimulationPriority, 
			 true);
const Stream::Type
Stream::kCCSimulation( "ccsimulation", 
		       Stream::kSimulationPriority, 
		       true);
const Stream::Type
Stream::kMUSimulation( "musimulation", 
		       Stream::kSimulationPriority, 
		       true);

#endif /* DATAHANDLER_STREAMCONSTANTS_DEFN_H */
