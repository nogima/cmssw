import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('CTPPSPixelAnalyzer'
     ,tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
)
