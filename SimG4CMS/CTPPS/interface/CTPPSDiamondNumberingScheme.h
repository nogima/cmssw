//  //////////////////////
// Author 
// Seyed Mohsen Etesami setesami@cern.ch
// ////////////////////////

#ifndef CTPPS_CTPPSDiamondNumberingScheme_h
#define CTPPS_CTPPSDiamondNumberingScheme_h

#include "SimG4CMS/CTPPS/interface/CTPPSDiamondOrganization.h"

class CTPPSDiamondNumberingScheme : public CTPPSDiamondOrganization 
{
  public:
    CTPPSDiamondNumberingScheme();
    ~CTPPSDiamondNumberingScheme();
	 
    //  virtual unsigned int GetUnitID(const G4Step* aStep) const ;

};

#endif //CTPPS_CTPPSDiamondNumberingScheme_h
