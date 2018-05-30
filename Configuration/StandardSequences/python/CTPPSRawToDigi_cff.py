import FWCore.ParameterSet.Config as cms

# This object is used to selectively make changes for different running
# scenarios. In this case it makes changes for Run 2.

from EventFilter.CTPPSRawToDigi.ctppsRawToDigi_cff import *

RawToDigi = cms.Sequence(ctppsPixelDigis
			)

ctppsPixelDigis.InputLabel = 'ctppsPixelRawData'
