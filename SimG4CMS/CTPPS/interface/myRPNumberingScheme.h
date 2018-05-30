#ifndef myRPNumberingScheme_h
#define myRPNumberingScheme_h

#include "SimG4CMS/CTPPS/interface/myTotemRPOrganization.h"

class myRPNumberingScheme : public myTotemRPOrganization {

public:
  myRPNumberingScheme(int i);
  ~myRPNumberingScheme();
	 
//  virtual unsigned int GetUnitID(const G4Step* aStep) const ;

};

#endif  //CTPPS_myRPNumberingScheme_h
