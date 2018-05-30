#ifndef _CTPPSSD_h
#define _CTPPSSD_h
// -*- C++ -*-
//
// Package:     Forward
// Class  :     CTPPSSD
//
/**\class CTPPSSD CTPPSSD.h SimG4CMS/CTPPS/interface/CTPPSSD.h
 
 Description: Stores hits of CTPPS in appropriate  container
 
 Usage:
    Used in sensitive detector builder 
 
*/
//
// Original Author: 
//         Created:  Tue May 16 10:14:34 CEST 2006
//
 
// system include files

// user include files

#include "SimG4Core/Notification/interface/Observer.h"
#include "SimG4Core/SensitiveDetector/interface/SensitiveTkDetector.h"
#include "SimG4Core/Notification/interface/BeginOfEvent.h"
#include "SimG4Core/Notification/interface/EndOfEvent.h"

#include "SimG4CMS/CTPPS/interface/CTPPSG4Hit.h"
#include "SimG4CMS/CTPPS/interface/CTPPSG4HitCollection.h"
#include "SimG4CMS/CTPPS/interface/CTPPSVDetectorOrganization.h"
#include "SimG4Core/Application/interface/SimTrackManager.h"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
 
#include <string>

class TrackingSlaveSD;
class SimTrackManager;

class CTPPSSD : public SensitiveTkDetector,
		public Observer<const BeginOfEvent*>,
		public Observer<const EndOfEvent*> {

public:

  /*
   * std::string,
   * DDCompactView const&,
   * SensitiveDetectorCatalog&,
   * edm::ParameterSet const&,
   * SimTrackManager const*
   */
  CTPPSSD(const std::string &,
        const DDCompactView &,
        const SensitiveDetectorCatalog &,
        edm::ParameterSet const &,
        SimTrackManager const *);
  ~CTPPSSD() override;
  
  bool   ProcessHits(G4Step *,G4TouchableHistory *) override;
  uint32_t setDetUnitId(const G4Step *);

  void   Initialize(G4HCofThisEvent * HCE) override;
  void   EndOfEvent(G4HCofThisEvent * eventHC) override;
  void   clear() override;
  void   DrawAll() override;
  void   PrintAll() override;

  void fillHits(edm::PSimHitContainer&, const std::string &) override;

private:

  void           update(const BeginOfEvent *) override;
  void           update(const ::EndOfEvent *) override;
  void   clearHits() override;

private:

  G4ThreeVector  SetToLocal(const G4ThreeVector& globalPoint);
  void           GetStepInfo(G4Step* aStep);
  bool           HitExists();
  void           CreateNewHit();
  void           CreateNewHitEvo();
  G4ThreeVector  PosizioEvo(const G4ThreeVector&,double ,double ,double, double,int&);
  void           UpdateHit();
  void           StoreHit(CTPPSG4Hit*);
  void           ResetForNewPrimary();
  void           Summarize();

private:

  TrackingSlaveSD*            slave;
  CTPPSVDetectorOrganization* numberingScheme;

  // Data relative to primary particle (the one which triggers a shower)
  // These data are common to all Hits of a given shower.
  // One shower is made of several hits which differ by the
  // unit ID (cristal/fiber/scintillator) and the Time slice ID.

  G4ThreeVector               entrancePoint;
  float                       incidentEnergy;
  G4int                       primID  ; //@@ ID of the primary particle.

  std::string                 name;
  G4int                       hcID;
  CTPPSG4HitCollection*       theHC; 
  const SimTrackManager*      theManager;

  int                         tsID; 
  CTPPSG4Hit*                 currentHit;
  G4Track*                    theTrack;
  G4VPhysicalVolume*          currentPV;
  uint32_t                    unitID, previousUnitID;
  int                         primaryID, tSliceID;  
  double                      tSlice;

  G4StepPoint*                preStepPoint; 
  G4StepPoint*                postStepPoint; 
  float                       edeposit;
  G4ThreeVector               hitPoint;

  G4ThreeVector               Posizio;
  G4ThreeVector               theEntryPoint;
  G4ThreeVector               theExitPoint;
  float                       Pabs;
  float                       Tof;
  float                       Eloss;	
  short                       ParticleType; 

  float                       ThetaAtEntry;
  float                       PhiAtEntry;

  int                         ParentId;
  float                       Vx,Vy,Vz;

  int                         eventno;
};

#endif


