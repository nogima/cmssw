#ifndef SimCTPPS_RPDigiProducer_RP_DISPLACEMENT_GENERATOR_H
#define SimCTPPS_RPDigiProducer_RP_DISPLACEMENT_GENERATOR_H

#include "DataFormats/CTPPSDigi/interface/RPTypes.h"
#include "DetectorDescription/Core/interface/DDRotationMatrix.h"
#include "DetectorDescription/Core/interface/DDTranslation.h"
#include <Math/Rotation3D.h>
#include <map>

namespace edm {
  class ParameterSet;
  class EventSetup;
}

class PSimHit;


/**
 * \ingroup TotemDigiProduction
 * \brief This class introduces displacements of RP.
 * It actually shifts and rotates PSimHit positions. It doesn't test whether the displaced
 * hit is still on the detector's surface. This check takes place later in the process. It
 * is done via edge effectivity.
 *
 * PSimHit points are given in the "local Det frame" (PSimHit.h)
 */

class RPDisplacementGenerator
{
  public:
    typedef ROOT::Math::Rotation3D RotationMatrix;

    RPDisplacementGenerator(const edm::ParameterSet &, RPDetId, const edm::EventSetup &);
  
    /// returns displaced PSimHit
    PSimHit Displace(const PSimHit &);
    
  private:
    /// ID of the detector
    RPDetId detId;

    /// displacement
	DDTranslation shift;
	DDRotationMatrix rotation;

    /// set to false to bypass displacements
    bool isOn;

    /// displaces a point
    Local3DPoint DisplacePoint(const Local3DPoint &);
};

#endif

