import FWCore.ParameterSet.Config as cms

# CTPPS Digitization
from SimCTPPS.CTPPSPixelDigiProducer.RPixDetConf_cfi import *
from SimCTPPS.RPDigiProducer.RPSiDetConf_cfi import *

ctppsDigi = cms.Sequence(RPixDetDigitizer+RPSiDetDigitizer)



