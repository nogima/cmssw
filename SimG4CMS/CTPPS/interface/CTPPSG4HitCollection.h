#ifndef _CTPPS_G4HitCollection_h
#define _CTPPS_G4HitCollection_h 1
// -*- C++ -*-
//
// Package:     CTPPS
// Class  :     CTPPSG4HitCollection
//
/**\class CTPPSG4HitCollection CTPPSG4HitCollection.h SimG4CMS/CTPPS/interface/CTPPSG4HitCollection.h
 
 Description: Hit collection class for CTPPS transient hits
 
 Usage: 
 
*/
//
// Original Author:
//         Created:  Tue May 16 10:14:34 CEST 2006
//
 
// system include files

// user include files
#include "SimG4CMS/CTPPS/interface/CTPPSG4Hit.h"
#include "G4THitsCollection.hh"

typedef G4THitsCollection<CTPPSG4Hit> CTPPSG4HitCollection;

#endif
