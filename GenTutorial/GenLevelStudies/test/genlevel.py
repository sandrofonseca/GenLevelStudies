
import FWCore.ParameterSet.Config as cms
process = cms.Process("GENLevelDump")

## 2017 geometry 
#from Configuration.Eras.Era_Run2_2017_cff import Run2_2017
## Phase 2
from Configuration.Eras.Era_Phase2C8_timing_layer_bar_cff import Phase2C8_timing_layer_bar
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

## Global tag for 10_6 phase2 mc
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_upgrade2023_realistic_v2', '')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
     '/store/mc/PhaseIITDRSpring19DR/DYToMuMuorEleEle_M-20_14TeV_pythia8/GEN-SIM-DIGI-RAW/NoPU_106X_upgrade2023_realistic_v3-v1/40000/E2C88213-1B8C-F740-BF2A-496508BF6F43.root'
    #'file:step1.root' 
 )
)

process.genlevel = cms.EDAnalyzer('GenLevelStudies')

process.TFileService = cms.Service("TFileService",
	fileName = cms.string("mcgen.root"),
	closeFileFast = cms.untracked.bool(True))


process.p = cms.Path(process.genlevel)
