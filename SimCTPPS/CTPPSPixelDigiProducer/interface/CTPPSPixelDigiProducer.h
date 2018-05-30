
#ifndef SimCTPPS_CTPPSDigiProducer_CTPPSPixelDigiProducer_h
#define SimCTPPS_CTPPSDigiProducer_CTPPSPixelDigiProducer_h

// -*- C++ -*-
//
// Package:    CTPPSPixelDigiProducer
// Class:      CTPPSPixelDigiProducer
// 
/**\class CTPPSPixelDigiProducer CTPPSPixelDigiProducer.cc SimCTPPS/CTPPSPixelDigiProducer/src/CTPPSPixelDigiProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  F.Ferro

//

#include "boost/shared_ptr.hpp"

// system include files
#include <memory>
#include <vector>
#include <map>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"

//  ****  CTPPS
#include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigi.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigiCollection.h"

#include "SimCTPPS/CTPPSPixelDigiProducer/interface/RPixDetDigitizer.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"

#include "DataFormats/Common/interface/DetSet.h"

// DB
#include "CondFormats/DataRecord/interface/CTPPSPixelDAQMappingRcd.h"
#include "CondFormats/DataRecord/interface/CTPPSPixelAnalysisMaskRcd.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSPixelDAQMapping.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSPixelAnalysisMask.h"
#include "CondFormats/CTPPSReadoutObjects/interface/CTPPSPixelGainCalibrations.h"
#include "RecoCTPPS/PixelLocal/interface/CTPPSPixelGainCalibrationDBService.h"


namespace CLHEP {
  class HepRandomEngine;
}

class CTPPSPixelDigiProducer : public edm::EDProducer {
   public:
      explicit CTPPSPixelDigiProducer(const edm::ParameterSet&);
      ~CTPPSPixelDigiProducer();
      static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);
   private:
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      std::vector<std::string> RPix_hit_containers_;
      typedef std::map<unsigned int, std::vector<PSimHit> > simhit_map;
      typedef simhit_map::iterator simhit_map_iterator;
      simhit_map SimHitMap;
      
      edm::ParameterSet conf_;


      std::map<uint32_t, boost::shared_ptr<RPixDetDigitizer> > theAlgoMap;  //DetId = uint32_t 



      std::vector<edm::DetSet<CTPPSPixelDigi> > theDigiVector;


      CLHEP::HepRandomEngine* rndEngine = nullptr;
      int verbosity_;

      CTPPSPixelGainCalibrationDBService theGainCalibrationDB;

      /**
       * this variable answers the question whether given channel is dead or not
       */
//      DeadChannelsManager deadChannelsManager;
      /**
       * this variable indicates whether we take into account dead channels or simulate as if all
       * channels work ok (by default we do not simulate dead channels)
       */
      //    bool simulateDeadChannels;

      edm::EDGetTokenT<CrossingFrame<PSimHit>> tokenCrossingFrameCTPPSPixel;
};


#endif
