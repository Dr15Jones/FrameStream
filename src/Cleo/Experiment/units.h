#if !defined(EXPERIMENT_UNITS_H)
#define EXPERIMENT_UNITS_H
// -*- C++ -*-
//
// Package:     Cleo
// Module:      units.h
// 
// Description: These are just a few definitions for specifying units and
//              keeping things consistent.
//
// Usage:
//    It's just like writing up homework!  Specify your units, and it'll all
//    work just dandy.  If a length is 3.5 cm, it becomes 3.5*k_cm.  If it's
//    1.2 in, it becomes 1.2*k_in.
//
//    If, on the other hand, something passes a number back to you in, say,
//    grams per cubic centimeter, you would *divide* by k_g_per_cm3 to get it
//    in the correct CLEO III units.  Think of the CLEO III units as
//    dimensionless, and this makes sense.
//
//    Simple, isn't it?
//
//    One final note:  "k_degrees" refers to angles, not temperature.  Since
//    there are no multiplicative conversions between the common temperature
//    units, this shouldn't cause much confusion.
//
// Author:      Michael Marsh
// Created:     Tue Jan 20 12:06:31 EST 1998
// $Id: units.h,v 1.6 2001/12/18 20:48:20 lkg Exp $
//
// Revision history
//
// $Log: units.h,v $
// Revision 1.6  2001/12/18 20:48:20  lkg
// added time units
//
// Revision 1.5  1998/11/24 19:35:49  mkl
// turned float into double for standard types and units
//
// Revision 1.4  1998/07/03 17:29:48  marsh
// Changed units of energy to GeV.  Added units for magnetic field (kG).
// Added more units, such as keV and radians, and more constants to convert
// from CLEO units to all units with constants.
//
// Revision 1.3  1998/05/14 19:58:05  marsh
// Added millimeters, microns, and mils.
//
// Revision 1.2  1998/05/07 22:26:06  marsh
// Renamed the constants to be more readable.  This was in response to input
// that people didn't like the old names, such as kM, which looked like it
// might be kilometers, but was in fact meters.
//
// Revision 1.1  1998/04/09 19:48:50  marsh
// New in repository.
//

// system include files
#if defined(EXCEPTION_CLASH_WITH_MATH_H_BUG)
#define exception _math_bug_
#include <math.h>  // required for trigonometry and fabs
#undef exception
#else
#include <math.h>  // required for trigonometry and fabs
#endif

// user include files

const double k_in_to_cm = 2.54;

const double k_m  = 1.0;
const double k_cm = 0.01;  // lengths are in meters
const double k_mm = 1.0E-3;
const double k_um = 1.0E-6; // microns
const double k_in = k_in_to_cm * k_cm;
const double k_mil = k_in * 1.0E-3;
const double k_to_m = 1/k_m;
const double k_to_cm = 1/k_cm;
const double k_to_mm = 1/k_mm;
const double k_to_um = 1/k_um;
const double k_to_in = 1/k_in;
const double k_to_mil = 1/k_mil;

const double k_kg = 1.0;
const double k_g  = 0.001;
const double k_u  = 1.6605402E-27;
const double k_to_kg = 1/k_kg;
const double k_to_g = 1/k_g;
const double k_to_u = 1/k_u;

const double k_kg_per_m3 = 1;
const double k_g_per_cm3 = 1000;  // density is in kg/m^3
const double k_to_kg_per_m3 = 1/k_kg_per_m3;
const double k_to_g_per_cm3 = 1/k_g_per_cm3;

const double k_Pa  = 1; // pressure is in pascals
const double k_atm = 101325;
const double k_to_Pa = 1/k_Pa;
const double k_to_atm = 1/k_atm;

const double k_GeV = 1; // energy is in GeV
const double k_MeV = 1.0E-3;
const double k_keV = 1.0E-6;
const double k_eV = 1.0E-9;
const double k_to_GeV = 1/k_GeV;
const double k_to_MeV = 1/k_MeV;
const double k_to_keV = 1/k_keV;
const double k_to_eV = 1/k_eV;
const double k_to_J = 1.60217733E-10;
const double k_J = 1/k_to_J;

const double k_kGauss = 1;
const double k_Gauss = 1.0E-3;
const double k_Tesla = 10;
const double k_to_kGauss = 1/k_kGauss;
const double k_to_Gauss = 1/k_Gauss;
const double k_to_Tesla = 1/k_Tesla;

const double k_radians = 1; // pretty much everything uses radians
const double k_degrees = M_PI / 180;
const double k_to_radians = 1/k_radians;
const double k_to_degrees = 1/k_degrees;

const double k_psec = 1; // Cleo has typically used picoseconds
const double k_nsec = 1.0E3;
const double k_usec = 1.0E6;
const double k_msec = 1.0E9;
const double k_sec  = 1.0E12;
const double k_to_psec = 1/k_psec;
const double k_to_nsec = 1/k_nsec;
const double k_to_usec = 1/k_usec;
const double k_to_msec = 1/k_msec;
const double k_to_sec  = 1/k_sec;

#endif /* EXPERIMENT_UNITS_H */
