#ifndef SimCTPPS_RPDigiProducer_RP_HIT_CHARGE_CONVERTER_H
#define SimCTPPS_RPDigiProducer_RP_HIT_CHARGE_CONVERTER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include <map>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimCTPPS/RPDigiProducer/interface/RPLinearChargeCollectionDrifter.h"
#include "SimCTPPS/RPDigiProducer/interface/RPLinearChargeDivider.h"
#include "SimCTPPS/RPDigiProducer/interface/RPLinearInduceChargeOnStrips.h"
#include "SimCTPPS/RPDigiProducer/interface/RPSimTypes.h"

class RPHitChargeConverter
{
  public:
    RPHitChargeConverter(const edm::ParameterSet &params_, CLHEP::HepRandomEngine& eng, RPDetId det_id);
    ~RPHitChargeConverter();
    
    SimRP::strip_charge_map processHit(const PSimHit &hit);
  private:
    const edm::ParameterSet &params_;
    const RPDetId det_id_;
    
    RPLinearChargeDivider* theRPChargeDivider;
    RPLinearChargeCollectionDrifter* theRPChargeCollectionDrifter;
    RPLinearInduceChargeOnStrips* theRPInduceChargeOnStrips;
    int verbosity_;
};

#endif  //SimCTPPS_RPDigiProducer_RP_HIT_CHARGE_CONVERTER_H
