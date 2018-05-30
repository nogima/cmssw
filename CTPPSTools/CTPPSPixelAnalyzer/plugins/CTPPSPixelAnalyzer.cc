// -*- C++ -*-
//
// Package:    CTPPSTools/CTPPSPixelAnalyzer
// Class:      CTPPSPixelAnalyzer
//
/**\class CTPPSPixelAnalyzer CTPPSPixelAnalyzer.cc CTPPSTools/CTPPSPixelAnalyzer/plugins/CTPPSPixelAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Helio Nogima
//         Created:  Fri, 04 May 2018 20:06:34 GMT
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

#include <DataFormats/Common/interface/Handle.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/CTPPSReco/interface/CTPPSPixelLocalTrack.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "RecoCTPPS/PixelLocal/interface/CTPPSPixelRecHitProducer.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSPixelDetId.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSPixelDigi.h"
#include "DataFormats/CTPPSReco/interface/CTPPSPixelCluster.h"
#include "EventFilter/CTPPSRawToDigi/interface/CTPPSPixelDataFormatter.h"

#include <TROOT.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLorentzVector.h>
#include <TObjString.h>
#include <TMath.h>
#include <TStyle.h>
#include "DataFormats/Math/interface/Vector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include <cmath>
#include <vector>

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


//using reco::TrackCollection;

class CTPPSPixelAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit CTPPSPixelAnalyzer(const edm::ParameterSet&);
      ~CTPPSPixelAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

      typedef std::vector<CTPPSPixelDigi> DetDigis;
      typedef std::map<cms_uint32_t,DetDigis> Digis;

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
//      edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
      edm::EDGetTokenT<edm::DetSetVector<CTPPSPixelDigi>> digiToken_;
      edm::Handle<edm::DetSetVector<CTPPSPixelDigi>> digiCollection;
      edm::EDGetTokenT<edm::DetSetVector<CTPPSPixelDigi>> dgtsToken_;
      edm::Handle<edm::DetSetVector<CTPPSPixelDigi>> dgtsCollection;
      edm::EDGetTokenT<edm::DetSetVector<CTPPSPixelCluster>> clusterToken_;
      edm::Handle<edm::DetSetVector<CTPPSPixelCluster>> clusterCollection;
      edm::EDGetTokenT<edm::DetSetVector<CTPPSPixelRecHit>> rechitToken_;
      edm::Handle<edm::DetSetVector<CTPPSPixelRecHit>> rechitCollection;
    edm::EDGetTokenT<edm::PSimHitContainer> psimHitToken;
    edm::Handle<edm::PSimHitContainer> PSimHit;

      edm::Service<TFileService> fs;

      TH2F *h_DetXY[2][6];
      TH2F *h_DgtXY[2][6];
      TH2F *h_RecHitXY[2][6];
      TH2F *h_PSimHitXY[2][6];
      TH1F *h_RecHitX[2][6];
      TH1F *h_RecHitY[2][6];
      TH1F *h_PSimHitX[2][6];
      TH1F *h_PSimHitY[2][6];
      TH1F *h_DetADC[2][6];
      TH1F *h_DgtADC[2][6];
      TH1F *h_ClusterCharge[2][6];
      TH1F *h_ClusterCharge1[2][6];
      TH1F *h_ClusterCharge2[2][6];
      TH1F *h_ClusterCharge3[2][6];
      TH1F *h_NumberOfPixels[2][6];
      TH1F *h_NumberOfDgtPixels[2][6];
      TH1F *h_NumberOfClusters[2][6];
      TH1F *h_ClusterSize[2][6];
      TH1F *h_ClusterSize1[2][6];
      TH1F *h_ClusterSizeRow[2][6];
      TH1F *h_ClusterSizeCol[2][6];
      TH1F *h_ClusterSizeRow1[2][6];
      TH1F *h_ClusterSizeCol1[2][6];
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
CTPPSPixelAnalyzer::CTPPSPixelAnalyzer(const edm::ParameterSet& iConfig)
// :
//  tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))
//  digiToken_(consumes<edm::DetSetVector<CTPPSPixelDigi>>(iConfig.getUntrackedParameter<edm::InputTag>("digitoken")))
//  clusterToken_(consumes<edm::DetSetVector<CTPPSPixelCluster>>(iConfig.getUntrackedParameter<edm::InputTag>("clustertoken")))
{
   //now do what ever initialization is needed
 digiToken_=consumes<edm::DetSetVector<CTPPSPixelDigi>>(iConfig.getUntrackedParameter<edm::InputTag>("digitoken"));
 dgtsToken_=consumes<edm::DetSetVector<CTPPSPixelDigi>>(iConfig.getParameter<edm::InputTag>("dgtstoken"));
 clusterToken_=consumes<edm::DetSetVector<CTPPSPixelCluster>>(iConfig.getParameter<edm::InputTag>("clustertoken"));
 rechitToken_=consumes<edm::DetSetVector<CTPPSPixelRecHit>>(iConfig.getParameter<edm::InputTag>("rechittoken"));

//Comment for real data
 psimHitToken = mayConsume<edm::PSimHitContainer>(iConfig.getUntrackedParameter<edm::InputTag>("psimHitTag"));

}


CTPPSPixelAnalyzer::~CTPPSPixelAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CTPPSPixelAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

//    Handle<TrackCollection> tracks;
//    iEvent.getByToken(tracksToken_, tracks);
    iEvent.getByToken(digiToken_, digiCollection);
/*    for(TrackCollection::const_iterator itTrack = tracks->begin();
        itTrack != tracks->end();
        ++itTrack) {
      // do something with track parameters, e.g, plot the charge.
      // int charge = itTrack->charge();
    }*/

    int arm = 999;
    int plane = 999;

    for(std::vector< edm::DetSet<CTPPSPixelDigi> >::const_iterator di=digiCollection->begin(); di != digiCollection->end(); di++) {
//      std::cout << "di->detId(): " << di->detId() << "  size: " << di->size() << "  empty: " << di->empty() << std::endl;
      arm = int((di->detId()>>24)& 0X1);
      plane = int((di->detId()>>16)&0X7);
      h_NumberOfPixels[arm][plane]->Fill(di->size());
      for (edm::DetSet<CTPPSPixelDigi>::const_iterator dui = (*di).begin(); dui!=(*di).end() ; dui++ ){
//          std::cout << "row: " << dui->row() << "  col: " << dui->column() << "  adc: " << dui->adc() << std::endl;
          h_DetXY[arm][plane]->Fill(dui->row(),dui->column());
          h_DetADC[arm][plane]->Fill(dui->adc());
      }
    }


    iEvent.getByToken(dgtsToken_, dgtsCollection);
    arm = 999;
    plane = 999;
    for(std::vector< edm::DetSet<CTPPSPixelDigi> >::const_iterator di=dgtsCollection->begin(); di != dgtsCollection->end(); di++) {
      arm = int((di->detId()>>24)& 0X1);
      plane = int((di->detId()>>16)&0X7);
      h_NumberOfDgtPixels[arm][plane]->Fill(di->size());
      for (edm::DetSet<CTPPSPixelDigi>::const_iterator dui = (*di).begin(); dui!=(*di).end() ; dui++ ){
          h_DgtXY[arm][plane]->Fill(dui->row(),dui->column());
          h_DgtADC[arm][plane]->Fill(dui->adc());
      }
    }

    iEvent.getByToken(clusterToken_, clusterCollection);
    for(std::vector< edm::DetSet<CTPPSPixelCluster> >::const_iterator cl=clusterCollection->begin(); cl != clusterCollection->end(); cl++) {
//      std::cout << "cl->detId(): " << cl->detId() << "  size: " << cl->size() << "  empty: " << cl->empty() << std::endl;
      arm = int((cl->detId()>>24)& 0X1);
      plane = int((cl->detId()>>16)&0X7);
      h_NumberOfClusters[arm][plane]->Fill(cl->size()); 
          for(edm::DetSet<CTPPSPixelCluster>::const_iterator cli = (*cl).begin(); cli!=(*cl).end() ; cli++){
//           std::cout << "cli->charge(): " << cli->charge() << "  cli->size(): " << cli->size() << std::endl;
           h_ClusterCharge[arm][plane]->Fill(cli->charge());
           h_ClusterSize[arm][plane]->Fill(cli->size());
           h_ClusterSizeRow[arm][plane]->Fill(cli->sizeRow());
           h_ClusterSizeCol[arm][plane]->Fill(cli->sizeCol());
           if (cl->size()==1) h_ClusterSize1[arm][plane]->Fill(cli->size());
           if (cl->size()==1) h_ClusterSizeRow1[arm][plane]->Fill(cli->sizeRow());
           if (cl->size()==1) h_ClusterSizeCol1[arm][plane]->Fill(cli->sizeCol());
           if(cli->size()==1) h_ClusterCharge1[arm][plane]->Fill(cli->charge());
           if(cli->size()==2) h_ClusterCharge2[arm][plane]->Fill(cli->charge());
           if(cli->size() >2) h_ClusterCharge3[arm][plane]->Fill(cli->charge());
          }
    }

    iEvent.getByToken(rechitToken_, rechitCollection);
    for(std::vector< edm::DetSet<CTPPSPixelRecHit> >::const_iterator rh=rechitCollection->begin(); rh != rechitCollection->end(); rh++) {
      arm = int((rh->detId()>>24)& 0X1);
      plane = int((rh->detId()>>16)&0X7);
          for(edm::DetSet<CTPPSPixelRecHit>::const_iterator rhi = (*rh).begin(); rhi!=(*rh).end() ; rhi++){
            h_RecHitXY[arm][plane]->Fill(rhi->getPoint().x(),rhi->getPoint().y());
            h_RecHitX[arm][plane]->Fill(rhi->getPoint().x());    
            h_RecHitY[arm][plane]->Fill(rhi->getPoint().y());    
          }
    }

// Comment for real data
    iEvent.getByToken( psimHitToken, PSimHit);
    if(PSimHit.isValid()) {
     for(edm::PSimHitContainer::const_iterator ps =  PSimHit->begin(); ps!= PSimHit->end(); ++ps){
      arm = int((ps->detUnitId()>>24)& 0X1);
      plane = int((ps->detUnitId()>>16)&0X7);
      h_PSimHitXY[arm][plane]->Fill(ps->entryPoint().x(),ps->entryPoint().y());
      h_PSimHitX[arm][plane]->Fill(ps->entryPoint().x());    
      h_PSimHitY[arm][plane]->Fill(ps->entryPoint().y());
     }
    }

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
CTPPSPixelAnalyzer::beginJob()
{
   for (int i = 0; i<2; i++){
    for (int j = 0; j<6; j++){
     char hname1[20], title1[50];
     char hname2[20], title2[50];
     char hname3[20], title3[50];
     char hname4[20], title4[50];
     char hname5[20], title5[50];
     char hname6[20], title6[50];
     char hname7[20], title7[50];
     char hname8[20], title8[50];
     char hname9[20], title9[50];
     char hname10[20], title10[50];
     char hname11[20], title11[50];
     char hname12[20], title12[50];
     char hname13[20], title13[50];
     char hname14[20], title14[50];
     char hname15[20], title15[50];
     char hname16[20], title16[50];
     char hname17[20], title17[50];
     char hname18[20], title18[50];
     char hname19[20], title19[50];
     char hname20[20], title20[50];
     char hname21[20], title21[50];
     char hname22[20], title22[50];
     char hname23[20], title23[50];
     sprintf(hname1,"detXY_%d%d",i,j);
     sprintf(title1,"Arm: %d  Plane: %d",i,j);
     h_DetXY[i][j] = fs->make<TH2F>(hname1,title1,165,0,165,165,0,165);
     sprintf(hname2,"detADC_%d%d",i,j);
     sprintf(title2,"Arm: %d  Plane: %d",i,j);
     h_DetADC[i][j] = fs->make<TH1F>(hname2,title2,150,0,300);
     sprintf(hname3,"detCharge_%d%d",i,j);
     sprintf(title3,"Arm: %d  Plane: %d - Charge",i,j);
     h_ClusterCharge[i][j] = fs->make<TH1F>(hname3,title3,100,0,500000);
     sprintf(hname4,"detCharge1_%d%d",i,j);
     sprintf(title4,"Arm: %d  Plane: %d - Charge (cluster = 1)",i,j);
     h_ClusterCharge1[i][j] = fs->make<TH1F>(hname4,title4,100,0,150000);
     sprintf(hname5,"detCharge2_%d%d",i,j);
     sprintf(title5,"Arm: %d  Plane: %d - Charge (cluster = 2)",i,j);
     h_ClusterCharge2[i][j] = fs->make<TH1F>(hname5,title5,100,0,150000);
     sprintf(hname6,"detCharge3_%d%d",i,j);
     sprintf(title6,"Arm: %d  Plane: %d - Charge (cluster > 2)",i,j);
     h_ClusterCharge3[i][j] = fs->make<TH1F>(hname6,title6,100,0,500000);
     sprintf(hname7,"NbPixels_%d%d",i,j);
     sprintf(title7,"Arm: %d  Plane: %d - Number of Pixels",i,j);
     h_NumberOfPixels[i][j] = fs->make<TH1F>(hname7,title7,80,0,80);     
     sprintf(hname8,"NbClusters_%d%d",i,j);
     sprintf(title8,"Arm: %d  Plane: %d - Number of Clusters",i,j);
     h_NumberOfClusters[i][j] = fs->make<TH1F>(hname8,title8,50,0,50);
     sprintf(hname9,"ClusterSize_%d%d",i,j);
     sprintf(title9,"Arm: %d  Plane: %d - Cluster Size",i,j);
     h_ClusterSize[i][j] = fs->make<TH1F>(hname9,title9,30,0,30);
     sprintf(hname10,"ClusterSize1_%d%d",i,j);
     sprintf(title10,"Arm: %d  Plane: %d - Cluster Size (Nb = 1)",i,j);
     h_ClusterSize1[i][j] = fs->make<TH1F>(hname10,title10,30,0,30);
     sprintf(hname11,"RecHitXY_%d%d",i,j);
     sprintf(title11,"Arm: %d  Plane: %d - RecHit Map",i,j);
     h_RecHitXY[i][j] = fs->make<TH2F>(hname11,title11,160,-10,10,160,-14,14);
     sprintf(hname12,"RecHitX_%d%d",i,j);
     sprintf(title12,"Arm: %d  Plane: %d - RecHit X",i,j);
     h_RecHitX[i][j] = fs->make<TH1F>(hname12,title12,100,-10,10);
     sprintf(hname13,"RecHitY_%d%d",i,j);
     sprintf(title13,"Arm: %d  Plane: %d - RecHit Y",i,j);
     h_RecHitY[i][j] = fs->make<TH1F>(hname13,title13,100,-14,14);
     sprintf(hname14,"PSimHitXY_%d%d",i,j);
     sprintf(title14,"Arm: %d  Plane: %d - PSimHit Map",i,j);
     h_PSimHitXY[i][j] = fs->make<TH2F>(hname14,title14,160,-10,10,160,-14,14);
     sprintf(hname15,"PSimHitX_%d%d",i,j);
     sprintf(title15,"Arm: %d  Plane: %d - PSimHit X",i,j);
     h_PSimHitX[i][j] = fs->make<TH1F>(hname15,title15,100,-10,10);
     sprintf(hname16,"PSimHitY_%d%d",i,j);
     sprintf(title16,"Arm: %d  Plane: %d - PSimHit Y",i,j);
     h_PSimHitY[i][j] = fs->make<TH1F>(hname16,title16,100,-14,14);
     sprintf(hname17,"ClusterSizeRow_%d%d",i,j);
     sprintf(title17,"Arm: %d  Plane: %d - Cluster Row Size",i,j);
     h_ClusterSizeRow[i][j] = fs->make<TH1F>(hname17,title17,30,0,30);
     sprintf(hname18,"ClusterSizeCol_%d%d",i,j);
     sprintf(title18,"Arm: %d  Plane: %d - Cluster Column Size",i,j);
     h_ClusterSizeCol[i][j] = fs->make<TH1F>(hname18,title18,30,0,30);
     sprintf(hname19,"ClusterSizeRow1_%d%d",i,j);
     sprintf(title19,"Arm: %d  Plane: %d - Cluster Row Size (Nb = 1)",i,j);
     h_ClusterSizeRow1[i][j] = fs->make<TH1F>(hname19,title19,30,0,30);
     sprintf(hname20,"ClusterSizeCol1_%d%d",i,j);
     sprintf(title20,"Arm: %d  Plane: %d - Cluster Column Size (Nb = 1)",i,j);
     h_ClusterSizeCol1[i][j] = fs->make<TH1F>(hname20,title20,30,0,30);
     sprintf(hname21,"dgtXY_%d%d",i,j);
     sprintf(title21,"Arm: %d  Plane: %d",i,j);
     h_DgtXY[i][j] = fs->make<TH2F>(hname21,title21,165,0,165,165,0,165);
     sprintf(hname22,"dgtADC_%d%d",i,j);
     sprintf(title22,"Arm: %d  Plane: %d",i,j);
     h_DgtADC[i][j] = fs->make<TH1F>(hname22,title22,150,0,300);
     sprintf(hname23,"NbDgtPixels_%d%d",i,j);
     sprintf(title23,"Arm: %d  Plane: %d - Number of Pixels",i,j);
     h_NumberOfDgtPixels[i][j] = fs->make<TH1F>(hname23,title23,80,0,80);
    }
   }
}

// ------------ method called once each job just after ending the event loop  ------------
void
CTPPSPixelAnalyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CTPPSPixelAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(CTPPSPixelAnalyzer);
