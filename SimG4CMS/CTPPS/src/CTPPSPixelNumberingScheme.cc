// -*- C++ -*-
//
// Package:     CTPPS
// Class  :     CTPPSPixelNumberingScheme
//
// Implementation:
//     <Notes on implementation>
//
// Original Author: 
//         Created:  Tue May 16 10:14:34 CEST 2006
//

// system include files

// user include files
#include "SimG4CMS/CTPPS/interface/CTPPSPixelNumberingScheme.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

//
// constructors and destructor
//
CTPPSPixelNumberingScheme::CTPPSPixelNumberingScheme() {

  edm::LogInfo("CTPPSSim") << " Creating CTPPSPixelNumberingScheme";
//  SetCurrentDetectorPosition();
}

CTPPSPixelNumberingScheme::~CTPPSPixelNumberingScheme() {
  edm::LogInfo("CTPPSSim") << " Deleting CTPPSPixelNumberingScheme";
}


