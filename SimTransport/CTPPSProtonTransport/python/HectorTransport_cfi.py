import FWCore.ParameterSet.Config as cms

from SimG4Core.Application.hectorParameter_cfi import *

from SimTransport.CTPPSProtonTransport.HectorOpticsParameters_cfi import *

LHCTransport = cms.EDProducer("CTPPSSimTrackProducer",
    HepMCProductLabel = cms.string('generatorSmeared'),  ## HepMC source to be processed
    Verbosity = cms.bool(False),
    TransportMethod = cms.string('Hector'),
    #VtxMeanX        = cms.double(0.),
    #VtxMeanY        = cms.double(0.),
    #VtxMeanZ        = cms.double(0.),
    CTPPSHector = cms.PSet(
        HectorEtaCut,
        Validated_PreTS2_2016,
        BeamLineLengthCTPPS = cms.double(250.0),
        CTPPSf = cms.double(212.55),    ##in meters
        CTPPSb = cms.double(212.55),    ##in meters
        MomentumMin = cms.double(3.000)
    )
)
