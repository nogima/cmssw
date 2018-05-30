import FWCore.ParameterSet.Config as cms

from SimTransport.CTPPSProtonTransport.TotemBeamConditions_cff import BeamConditionsGlobal
LHCTransport = cms.EDProducer('CTPPSSimTrackProducer',
    TransportMethod = cms.string('Totem'),
    HepMCProductLabel = cms.string('generatorSmeared'),
    Verbosity = cms.bool(False),
    sqrtS = cms.double(13.0e3),

    # crossing angle
    checkApertures = cms.bool(True),

    BeamProtTransportSetup=BeamConditionsGlobal
)
