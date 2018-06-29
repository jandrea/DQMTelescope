import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")


process.TFileService = cms.Service("TFileService", 
      fileName = cms.string("DQM_V0001_PixelTelescope_R000100000.root"),
      closeFileFast = cms.untracked.bool(True)
)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:../../../../../PixelTelescope_Pion120GeV_RECO.root'
    )
)

process.DQMData = cms.EDAnalyzer('PixelTelescope', 
 	tracks = cms.untracked.InputTag('ctfWithMaterialTracks'),
	PixelClustersLabel = cms.InputTag("siPixelClusters")
)


process.p = cms.Path(process.DQMData)
