# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
process = cms.Process('DIGI2RAW',eras.Run2_2017)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('SimGeneral.MixingModule.MYmixNoPU_cfi')
process.load('Configuration.StandardSequences.cmsCTPPSDigi_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('CondFormats.CTPPSReadoutObjects.CTPPSPixelDAQMappingESSourceXML_cfi')
############### using only CTPPS geometry 
process.load("Geometry.VeryForwardGeometry.geometryCTPPSFromDD_2017_cfi")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.load("IOMC.RandomEngine.IOMC_cff")
process.RandomNumberGeneratorService.generator.initialSeed = 456789
process.RandomNumberGeneratorService.g4SimHits.initialSeed = 9876
process.RandomNumberGeneratorService.VtxSmeared.initialSeed = 123456789
process.RandomNumberGeneratorService.RPixDetDigitizer = cms.PSet(initialSeed =cms.untracked.uint32(137137))
process.RandomNumberGeneratorService.RPSiDetDigitizer = cms.PSet(initialSeed =cms.untracked.uint32(137137))

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
#    fileNames = cms.untracked.vstring('file:step1_SIM2017.root'),
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/n/nogima/FullSim/CMSSW_10_1_0_pre1/src/step1_SIM.root'),
    inputCommands = cms.untracked.vstring('keep *', 
        'drop *_genParticles_*_*', 
        'drop *_genParticlesForJets_*_*', 
        'drop *_kt4GenJets_*_*', 
        'drop *_kt6GenJets_*_*', 
        'drop *_iterativeCone5GenJets_*_*', 
        'drop *_ak4GenJets_*_*', 
        'drop *_ak7GenJets_*_*', 
        'drop *_ak8GenJets_*_*', 
        'drop *_ak4GenJetsNoNu_*_*', 
        'drop *_ak8GenJetsNoNu_*_*', 
        'drop *_genCandidatesForMET_*_*', 
        'drop *_genParticlesForMETAllVisible_*_*', 
        'drop *_genMetCalo_*_*', 
        'drop *_genMetCaloAndNonPrompt_*_*', 
        'drop *_genMetTrue_*_*', 
        'drop *_genMetIC5GenJs_*_*'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('step23_RAW2DIGI_RECO2017.root'),
    outputCommands = cms.untracked.vstring("drop *","keep PSimHits*_*_*_*","keep CTPPS*_*_*_*","keep *_*RP*_*_*",'keep *_LHCTransport_*_*')
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')

process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(
        record = cms.string('CTPPSPixelGainCalibrationsRcd'),
        tag = cms.string("CTPPSPixelGainCalibNew_v4"),
        connect = cms.string('sqlite_file:CTPPSPixel_Mapping_Mask_Gain_Jan23rd2018.db')
        ),
    cms.PSet(
        record = cms.string('CTPPSPixelAnalysisMaskRcd'),
        tag = cms.string("PixelAnalysisMask"),
        label = cms.untracked.string(""),
        connect = cms.string('sqlite_file:CTPPSPixel_Mapping_Mask_Gain_Jan23rd2018.db')
        ),
    cms.PSet(
        record = cms.string('CTPPSPixelDAQMappingRcd'),
        tag = cms.string("PixelDAQMapping"),
        connect = cms.string('sqlite_file:CTPPSPixel_Mapping_Mask_Gain_Jan23rd2018.db')
        )
)

# modify Totem 2017 mapping
process.load('CondFormats.CTPPSReadoutObjects.totemDAQMappingESSourceXML_cfi')
process.totemDAQMappingESSourceXML.configuration = cms.VPSet(
    cms.PSet(
      validityRange = cms.EventRange("1:min - 999999999:max"),
      mappingFileNames = cms.vstring("CondFormats/CTPPSReadoutObjects/xml/mapping_tracking_strip_2017.xml"),
      maskFileNames = cms.vstring()
    )   
)

process.load("EventFilter.CTPPSRawToDigi.pgctppsDigiToRaw_cfi")
process.load("EventFilter.CTPPSRawToDigi.pgctppsRawToDigi_cfi")

from RecoCTPPS.Configuration.recoCTPPS_DD_2017_cff import *
process.load("RecoCTPPS.Configuration.recoCTPPS_DD_2017_cff")

# Path and EndPath definitions
process.mixedigi_step = cms.Path(process.mix*process.RPixDetDigitizer*process.RPSiDetDigitizer)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.ctppsRawToDigi)
process.reco_step = cms.Path(process.recoCTPPS)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.output_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.mixedigi_step,process.digi2raw_step,process.raw2digi_step,process.reco_step,process.endjob_step,process.output_step)

from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
