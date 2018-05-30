#ifndef SimCTPPS_CTPPSPixelDigiProducer_RPix_DET_DIGITIZER_H
#define SimCTPPS_CTPPSPixelDigiProducer_RPix_DET_DIGITIZER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include <vector>
#include <string>

#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimGeneral/NoiseGenerators/interface/GaussianTailNoiseGenerator.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
//#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"

#include "FWCore/Framework/interface/EventSetup.h"

#include "SimCTPPS/CTPPSPixelDigiProducer/interface/RPixHitChargeConverter.h"
#include "SimCTPPS/CTPPSPixelDigiProducer/interface/RPixDummyROCSimulator.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigi.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigiCollection.h"

#include "SimCTPPS/CTPPSPixelDigiProducer/interface/RPixPileUpSignals.h"

#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSPixelGainCalibrations.h"
#include "RecoCTPPS/PixelLocal/interface/CTPPSPixelGainCalibrationDBService.h"

#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSPixelAnalysisMask.h"

namespace CLHEP{
  class HepRandomEngine;
}

class RPixDetDigitizer
{

public:
  RPixDetDigitizer(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, uint32_t det_id, const edm::EventSetup& iSetup);
  void run(const std::vector<PSimHit> &input, const std::vector<int> &input_links, 
	   std::vector<CTPPSPixelDigi> &output_digi,
	   std::vector<std::vector<std::pair<int, double> > >  &output_digi_links,
           const CTPPSPixelGainCalibrations * pcalibration
    );

  ~RPixDetDigitizer();
//  static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);
      
private:
//    RPGaussianTailNoiseAdder *theRPGaussianTailNoiseAdder;
  RPixPileUpSignals *theRPixPileUpSignals;
  RPixHitChargeConverter *theRPixHitChargeConverter;
  RPixDummyROCSimulator *theRPixDummyROCSimulator;
//    RPDisplacementGenerator *theRPDisplacementGenerator;

private:
  const edm::ParameterSet &params_;

  int numPixels;
  double theNoiseInElectrons;   // Noise (RMS) in units of electrons.
  double thePixelThresholdInE;  // Pixel noise treshold in electorns.
  bool noNoise;                 //if the nos is included
  uint32_t det_id_;
  bool misalignment_simulation_on_;
  int verbosity_;
  bool  _links_persistence;
};

#endif
