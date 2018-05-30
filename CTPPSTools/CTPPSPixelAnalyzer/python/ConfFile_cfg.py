import FWCore.ParameterSet.Config as cms

process = cms.Process("Pixel")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        'file:myfile.root'
#'file:/afs/cern.ch/work/p/polme/public/FullSimPPS/test19/CMSSW_10_1_0_pre1/src/step3_RAW2DIGI_RECO.root'
#'file:/afs/cern.ch/work/p/polme/public/FullSimPPS/test20/CMSSW_10_1_0/src/step3_RAW2DIGI_RECO2017_100K_0305.root'
#'file:/afs/cern.ch/work/p/polme/public/FullSimPPS/test20/CMSSW_10_1_0/src/step3_RAW2DIGI_RECO2016_100K_0405.root'
#'file:/afs/cern.ch/work/p/polme/public/FullSimPPS/test20/CMSSW_10_1_0/src/step3_RAW2DIGI_RECO2018_100K_0305.root'
#'file:/eos/user/f/ferro/fabferro/_304292/CTPPSPixelReco_304292_zb_6.root'
#'file:simevent_CTPPS_CLU__REC_TRA_DB_mem_ALL_300k.root'
#'file:simevent_CTPPS_CLU__REC_TRA_DB_mem_ALL.root'
#'file:step3_RAW2DIGI_RECO2018.root'
#'file:step3_RAW2DIGI_RECO2017_300k.root'
#'file:step3_RAW2DIGI_RECO2017_300k_new.root'
#'file:step3_RAW2DIGI_RECO2017_50k_Coup1.root'
#'file:simevent_CTPPS_CLU__REC_TRA_DB_mem_ALL.root'
'file:step23_RAW2DIGI_RECO2017.root'
    )
)

process.pixel = cms.EDAnalyzer('CTPPSPixelAnalyzer',
      digitoken = cms.untracked.InputTag("ctppsPixelDigis"),
      dgtstoken = cms.InputTag("RPixDetDigitizer"),
   clustertoken = cms.InputTag("ctppsPixelClusters"),
    rechittoken = cms.InputTag("ctppsPixelRecHits"), 
     psimHitTag = cms.untracked.InputTag('g4SimHits',"CTPPSPixelHits")
)

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

process.TFileService = cms.Service("TFileService",
                fileName = cms.string('outPixelAnalysis.root')
)

process.p = cms.Path(process.pixel)
