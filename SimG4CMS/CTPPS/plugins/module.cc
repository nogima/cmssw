#include "SimG4CMS/CTPPS/interface/Totem_RP_SD.h"
#include "SimG4CMS/CTPPS/interface/CTPPSSD.h"
#include "SimG4CMS/CTPPS/interface/CTPPS_Diamond_SD.h"


#include "SimG4Core/SensitiveDetector/interface/SensitiveDetectorPluginFactory.h"
#include "SimG4Core/Watcher/interface/SimWatcherFactory.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
  
typedef Totem_RP_SD RomanPotSensitiveDetector;
DEFINE_SENSITIVEDETECTOR(RomanPotSensitiveDetector);

typedef CTPPSSD CTPPSSensitiveDetector;
DEFINE_SENSITIVEDETECTOR(CTPPSSensitiveDetector);

typedef CTPPS_Diamond_SD CTPPSDiamondSensitiveDetector;
DEFINE_SENSITIVEDETECTOR(CTPPSDiamondSensitiveDetector);






