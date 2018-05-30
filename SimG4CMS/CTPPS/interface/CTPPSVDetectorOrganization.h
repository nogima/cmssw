///////////////////////////////////////////////////////////////////////////////
// File: CTPPSVDetectorOrganization.h
// Description: Base class for numbering scheme of CTPPS
///////////////////////////////////////////////////////////////////////////////
#ifndef _CTPPS_VDetectorOrganization_h
#define _CTPPS_VDetectorOrganization_h

#include "G4Step.hh"
#include <boost/cstdint.hpp>

class CTPPSVDetectorOrganization {

public:
  CTPPSVDetectorOrganization(){};
  virtual ~CTPPSVDetectorOrganization(){};   
  virtual uint32_t GetUnitID(const  G4Step* aStep) const =0;
};      


#endif


