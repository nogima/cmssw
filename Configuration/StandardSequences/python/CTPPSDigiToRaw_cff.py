import FWCore.ParameterSet.Config as cms

# This object is used to make changes for different running scenarios. In
# this case for Run 2

from EventFilter.SiPixelRawToDigi.SiPixelDigiToRaw_cfi import *
from EventFilter.SiStripRawToDigi.SiStripDigiToRaw_cfi import *
from SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_cff import *
import EventFilter.EcalDigiToRaw.ecalDigiToRaw_cfi
ecalPacker = EventFilter.EcalDigiToRaw.ecalDigiToRaw_cfi.ecaldigitorawzerosup.clone()
from EventFilter.ESDigiToRaw.esDigiToRaw_cfi import *
from EventFilter.HcalRawToDigi.HcalDigiToRaw_cfi import *
from EventFilter.CSCRawToDigi.cscPacker_cfi import *
from EventFilter.DTRawToDigi.dtPacker_cfi import *
from EventFilter.RPCRawToDigi.rpcPacker_cfi import *
from EventFilter.CastorRawToDigi.CastorDigiToRaw_cfi import *
from EventFilter.CTPPSRawToDigi.CTPPSPixelDigiToRaw_cfi import *
from EventFilter.CTPPSRawToDigi.CTPPSTotemDigiToRaw_cfi import *
from EventFilter.RawDataCollector.rawDataCollector_cfi import *
from L1Trigger.Configuration.L1TDigiToRaw_cff import *
#DigiToRaw = cms.Sequence(L1TDigiToRaw*siPixelRawData*SiStripDigiToRaw*ecalPacker*esDigiToRaw*hcalRawData*cscpacker*dtpacker*rpcpacker*rawDataCollector)
#DigiToRaw = cms.Sequence(L1TDigiToRaw*siPixelRawData*SiStripDigiToRaw*ecalPacker*esDigiToRaw*hcalRawData*cscpacker*dtpacker*rpcpacker*castorRawData*ctppsPixelRawData*rawDataCollector)
DigiToRaw = cms.Sequence(ctppsPixelRawData*rawDataCollector)
#DigiToRaw = cms.Sequence(ctppsPixelRawData*ctppsTotemRawData*rawDataCollector)
