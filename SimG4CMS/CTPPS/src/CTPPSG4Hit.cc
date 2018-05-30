// -*- C++ -*-
//
// Package:     CTPPS
// Class  :     CTPPSG4Hit
//
// Implementation:
//     <Notes on implementation>
//
// Original Author: 
//         Created:  Tue May 16 10:14:34 CEST 2006
//

// system include files

// user include files
#include "SimG4CMS/CTPPS/interface/CTPPSG4Hit.h"
#include <iostream>

//
// constructors and destructor
//

CTPPSG4Hit::CTPPSG4Hit(): MeanPosition(0), theEntryPoint(0), theExitPoint(0) {

  elem              = 0.;
  hadr              = 0.;
  theIncidentEnergy = 0.;
  theTrackID        = -1;
  theUnitID         =  0;
  theTimeSlice      = 0.;

  theX              = 0.;
  theY              = 0.;
  theZ              = 0.;
  thePabs           = 0.;
  theTof            = 0.;
  theEnergyLoss     = 0.;
  theParticleType   = 0;
  theThetaAtEntry   = 0.;
  thePhiAtEntry     = 0.;
  theParentId       = 0;
  theVx             = 0.;
  theVy             = 0.;
  theVz             = 0.;
  thePx =0;
  thePy =0;
  thePz =0;
  theVPx =0;
  theVPy =0;
  theVPz =0;


}

CTPPSG4Hit::~CTPPSG4Hit() {}

CTPPSG4Hit::CTPPSG4Hit(const CTPPSG4Hit &right) {

  MeanPosition            = right.MeanPosition;

  elem              = right.elem;
  hadr              = right.hadr;
  theIncidentEnergy = right.theIncidentEnergy;
  theTrackID        = right.theTrackID;
  theUnitID         = right.theUnitID;
  theTimeSlice      = right.theTimeSlice;

  theX              = right.theX;
  theY              = right.theY;
  theZ              = right.theZ;
  thePabs           = right.thePabs;
  theTof            = right.theTof;
  theEnergyLoss     = right.theEnergyLoss;
  theParticleType   = right.theParticleType;

  theThetaAtEntry   = right.theThetaAtEntry;
  thePhiAtEntry     = right.thePhiAtEntry;
  theEntryPoint     = right.theEntryPoint;
  theExitPoint      = right.theExitPoint;
  theParentId       = right.theParentId;
  theVx             = right.theVx;
  theVy             = right.theVy;
  theVz             = right.theVz;
  thePx =right.thePx;
  thePy =right.thePy;
  thePz =right.thePz;
  theVPx =right.theVPx;
  theVPy =right.theVPy;
  theVPz =right.theVPz;

}


const CTPPSG4Hit& CTPPSG4Hit::operator=(const CTPPSG4Hit &right) {

  MeanPosition            = right.MeanPosition;
  elem              = right.elem;
  hadr              = right.hadr;
  theIncidentEnergy = right.theIncidentEnergy;
  theTrackID        = right.theTrackID;
  theUnitID         = right.theUnitID;
  theTimeSlice      = right.theTimeSlice;
 
  theX              = right.theX;
  theY              = right.theY;
  theZ              = right.theZ;
  thePabs           = right.thePabs;
  theTof            = right.theTof ;
  theEnergyLoss     = right.theEnergyLoss   ;
  theParticleType   = right.theParticleType ;

  theThetaAtEntry   = right.theThetaAtEntry;
  thePhiAtEntry     = right.thePhiAtEntry;
  theEntryPoint     = right.theEntryPoint;
  theExitPoint      = right.theExitPoint;
  theParentId       = right.theParentId;
  theVx             = right.theVx;
  theVy             = right.theVy;
  theVz             = right.theVz;
  thePx =right.thePx;
  thePy =right.thePy;
  thePz =right.thePz;
  theVPx =right.theVPx;
  theVPy =right.theVPy;
  theVPz =right.theVPz;



  return *this;
}

void CTPPSG4Hit::addEnergyDeposit(const CTPPSG4Hit& aHit) {

  elem += aHit.getEM();
  hadr += aHit.getHadr();
}


void CTPPSG4Hit::Print() {
  std::cout << (*this);
}

Hep3Vector CTPPSG4Hit::getEntryPoint() const           {return theEntryPoint;}
void       CTPPSG4Hit::setEntryPoint(Hep3Vector xyz)   { theEntryPoint    = xyz; }
Hep3Vector CTPPSG4Hit::getExitPoint() const           {return theExitPoint;}
void       CTPPSG4Hit::setExitPoint(Hep3Vector xyz)   { theExitPoint    = xyz; }

double     CTPPSG4Hit::getEM() const              {return elem; }
void       CTPPSG4Hit::setEM (double e)           { elem     = e; }
      
double     CTPPSG4Hit::getHadr() const            {return hadr; }
void       CTPPSG4Hit::setHadr (double e)         { hadr     = e; }
      
double     CTPPSG4Hit::getIncidentEnergy() const  {return theIncidentEnergy; }
void       CTPPSG4Hit::setIncidentEnergy(double e) {theIncidentEnergy  = e; }

int        CTPPSG4Hit::getTrackID() const         {return theTrackID; }
void       CTPPSG4Hit::setTrackID (int i)         { theTrackID = i; }

uint32_t   CTPPSG4Hit::getUnitID() const          {return theUnitID; }
void       CTPPSG4Hit::setUnitID (uint32_t i)     { theUnitID = i; }

double     CTPPSG4Hit::getTimeSlice() const       {return theTimeSlice; }
void       CTPPSG4Hit::setTimeSlice (double d)    { theTimeSlice = d; }
int        CTPPSG4Hit::getTimeSliceID() const     {return (int)theTimeSlice;}

void       CTPPSG4Hit::addEnergyDeposit(double em, double hd) {elem += em;  hadr += hd;}

double     CTPPSG4Hit::getEnergyDeposit() const   {return elem+hadr;}

float      CTPPSG4Hit::getPabs() const            {return thePabs;}
float      CTPPSG4Hit::getTof() const             {return theTof;}
float      CTPPSG4Hit::getEnergyLoss() const      {return theEnergyLoss;}
int        CTPPSG4Hit::getParticleType() const    {return theParticleType;}
float CTPPSG4Hit::getPx() const {return thePx;}
float CTPPSG4Hit::getPy() const {return thePy;}
float CTPPSG4Hit::getPz() const {return thePz;}
float CTPPSG4Hit::getVPx() const {return theVPx;}
float CTPPSG4Hit::getVPy() const {return theVPy;}
float CTPPSG4Hit::getVPz() const {return theVPz;}


void       CTPPSG4Hit::setPabs(float e)           {thePabs = e;}
void CTPPSG4Hit::setPx(float e) {thePx = e;}
void CTPPSG4Hit::setPy(float e) {thePy = e;}
void CTPPSG4Hit::setPz(float e) {thePz = e;}
void CTPPSG4Hit::setVPx(float e) {theVPx = e;}
void CTPPSG4Hit::setVPy(float e) {theVPy = e;}
void CTPPSG4Hit::setVPz(float e) {theVPz = e;}
void       CTPPSG4Hit::setTof(float e)            {theTof = e;}
void       CTPPSG4Hit::setEnergyLoss(float e)     {theEnergyLoss = e;}
void       CTPPSG4Hit::setParticleType(short i)   {theParticleType = i;}

float      CTPPSG4Hit::getThetaAtEntry() const    {return theThetaAtEntry;}   
float      CTPPSG4Hit::getPhiAtEntry() const      {return thePhiAtEntry;}

void       CTPPSG4Hit::setThetaAtEntry(float t)   {theThetaAtEntry = t;}
void       CTPPSG4Hit::setPhiAtEntry(float f)     {thePhiAtEntry = f ;}

float      CTPPSG4Hit::getX() const               {return theX;}
void       CTPPSG4Hit::setX(float t)              {theX = t;}

float      CTPPSG4Hit::getY() const               {return theY;}
void       CTPPSG4Hit::setY(float t)              {theY = t;}

float      CTPPSG4Hit::getZ() const               {return theZ;}
void       CTPPSG4Hit::setZ(float t)              {theZ = t;}

int        CTPPSG4Hit::getParentId() const        {return theParentId;}
void       CTPPSG4Hit::setParentId(int p)         {theParentId = p;}

float      CTPPSG4Hit::getVx() const              {return theVx;}
void       CTPPSG4Hit::setVx(float t)             {theVx = t;}

float      CTPPSG4Hit::getVy() const              {return theVy;}
void       CTPPSG4Hit::setVy(float t)             {theVy = t;}

float      CTPPSG4Hit::getVz() const              {return theVz;}
void       CTPPSG4Hit::setVz(float t)             {theVz = t;}

std::ostream& operator<<(std::ostream& os, const CTPPSG4Hit& hit) {
  os << " Data of this CTPPSG4Hit are:\n" 
     << " Time slice ID: " << hit.getTimeSliceID() << "\n"
     << " EnergyDeposit = " << hit.getEnergyLoss() << "\n"
     << " Energy of primary particle (ID = " << hit.getTrackID()
     << ") = " << hit.getIncidentEnergy() << " (MeV)" << "\n"
     << " Local entry and exit points in CTPPS unit number " << hit.getUnitID()
     << " are: " << hit.getEntryPoint() << " (mm)" << hit.getExitPoint() << " (mm)" <<"\n"
     << " Global posizion in CTPPS unit number " << hit.getUnitID()
     << " are: " << hit.getMeanPosition() << " (mm)" <<"\n"
     << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  return os;
}


