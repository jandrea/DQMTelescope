// -*- C++ -*-
//
// Package:    DQMTelescope/PixelTelescope
// Class:      PixelTelescope
//
/**\class PixelTelescope PixelTelescope.cc DQMTelescope/PixelTelescope/plugins/PixelTelescope.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jeremy Andrea
//         Created:  Thu, 14 Jun 2018 14:43:12 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"



#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "TH2F.h"


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class PixelTelescope : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit PixelTelescope(const edm::ParameterSet&);
      ~PixelTelescope();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
      
      edm::Service<TFileService> fs;
      
      TH1F * DQM_ClusterCharge;
      TH1F * DQM_ClusterSize_X   ;  
      TH1F * DQM_ClusterSize_Y   ; 
      TH1F * DQM_ClusterSize_Tot ; 
      TH2F * DQM_ClusterPosition ;
      edm::EDGetTokenT<edmNew::DetSetVector<SiPixelCluster> > pixelclusterToken_;
       
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
PixelTelescope::PixelTelescope(const edm::ParameterSet& iConfig)
 :
  tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))

{
   //now do what ever initialization is needed
   
   
    /*TFileDirectory subDQMData   = fs->mkdir( "DQMData" );
    TFileDirectory subRunNum    = subDQMData.mkdir( "Run 1" );
    TFileDirectory subWorkSpace = subRunNum.mkdir( "PixelTelescope" );
    TFileDirectory subRunSumm   = subWorkSpace.mkdir( "Run summary" );*/
    
    
    TFileDirectory sub1 = fs->mkdir( "Run 100000" );
    TFileDirectory sub2 = sub1.mkdir( "PixelTelescope" );
    TFileDirectory sub3 = sub2.mkdir( "Run summary" );
    
    DQM_ClusterCharge     = sub3.make<TH1F>( "DQM_ClusterCharge"  ,     "DQM_ClusterCharge",     100,  0., 100000. );
    DQM_ClusterSize_X     = sub3.make<TH1F>( "DQM_ClusterSize_X"  ,     "DQM_ClusterSize_X",     100,  0., 20.     );
    DQM_ClusterSize_Y     = sub3.make<TH1F>( "DQM_ClusterSize_Y"  ,     "DQM_ClusterSize_Y",     100,  0., 20.     );
    DQM_ClusterSize_Tot   = sub3.make<TH1F>( "DQM_ClusterSize_Tot"  ,   "DQM_ClusterSize_Tot",   100,  0., 20.     );
    DQM_ClusterPosition   = sub3.make<TH2F>( "DQM_ClusterPosition"  ,   "DQM_ClusterPosition",   100,  0., 100., 100, 0, 100   );

   //TFileDirectory subDir = fs->mkdir( "mySubDirectory" );
   //TFileDirectory subSubDir = subDir.mkdir( "mySubSubDirectory" );
   //TH1F * h_pt = subDir.make<TH1F>( "pt"  , "p_{t}", 100,  0., 100. );

   
    pixelclusterToken_ = consumes<edmNew::DetSetVector<SiPixelCluster> >(iConfig.getParameter<edm::InputTag>("PixelClustersLabel"));
   
}


PixelTelescope::~PixelTelescope()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
PixelTelescope::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   /* Handle<TrackCollection> tracks;
    iEvent.getByToken(tracksToken_, tracks);
    for(TrackCollection::const_iterator itTrack = tracks->begin();
        itTrack != tracks->end();
        ++itTrack) {
      // do something with track parameters, e.g, plot the charge.
      // int charge = itTrack->charge();
    }
   
  */
  
  
  edm::Handle<edmNew::DetSetVector<SiPixelCluster> > pixelclusters;
  iEvent.getByToken(pixelclusterToken_,pixelclusters  );
 
  
  
  //edmNew::DetSetVector<SiPixelCluster>& input;
  //edmNew::DetSetVector<SiPixelCluster>::const_iterator isearch = input.find(id_); // search  clusters of detid
  
  
  unsigned int numberOfClusters = 0;
  //unsigned int numberOfFpixClusters = 0;
  
  //edmNew::DetSet<SiPixelCluster>::const_iterator  di;
  
  for( edmNew::DetSetVector<SiPixelCluster>::const_iterator DSViter=pixelclusters->begin(); DSViter!=pixelclusters->end();DSViter++   ) {
      numberOfClusters++;
      
      edmNew::DetSet<SiPixelCluster>::const_iterator begin=DSViter->begin();
      edmNew::DetSet<SiPixelCluster>::const_iterator end  =DSViter->end();
      
      
      
       DetId(id_);
      
      for(edmNew::DetSet<SiPixelCluster>::const_iterator iter=begin;iter!=end;++iter) {
       
        DQM_ClusterCharge->Fill(iter->charge());
        std::cout << "cluster charge " << iter->charge() << std::endl;
        std::cout << "cluster size " << iter->size() << std::endl;
	
        float x = iter->x();                   // barycenter x position
        float y = iter->y();                   // barycenter y position
        int size = iter->size();               // total size of cluster (in pixels)
        int sizeX = iter->sizeX();             // size of cluster in x-iterrection
        int sizeY = iter->sizeY();             // size of cluster in y-iterrection
        int minPixelRow = iter->minPixelRow(); // min x index
        int maxPixelRow = iter->maxPixelRow(); // max x index
        int minPixelCol = iter->minPixelCol(); // min y index
        int maxPixelCol = iter->maxPixelCol(); // max y index
	   
	DQM_ClusterSize_X->Fill(sizeX);   
	DQM_ClusterSize_Y->Fill(sizeY);     
	DQM_ClusterSize_Tot->Fill(size);   
	DQM_ClusterPosition->Fill(x, y);  
	
	
	
      }
    }
      //if(endcap) numberOfFpixClusters++;
      //float charge = 0.001*(di->charge()); // total charge of cluster
      

  if(numberOfClusters != 0 ) std::cout << "number of cluster " << numberOfClusters << std::endl;





}


// ------------ method called once each job just before starting event loop  ------------
void
PixelTelescope::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
PixelTelescope::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PixelTelescope::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PixelTelescope);
