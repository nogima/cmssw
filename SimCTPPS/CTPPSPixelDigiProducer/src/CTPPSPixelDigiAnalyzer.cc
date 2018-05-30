
#include <FWCore/Framework/interface/Event.h>

#include "SimCTPPS/CTPPSPixelDigiProducer/interface/CTPPSPixelDigiAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/GeometryVector/interface/LocalPoint.h"



#include <iostream>
#include <string>

#include "TFile.h"


#define SELECTED_PIXEL_ROW 89
#define SELECTED_PIXEL_COLUMN 23
#define SELECTED_UNITID 2014314496
#define TG184 0.332655724

#define USE_MIDDLE_OF_PIXEL_2
#define CENTERX 1.05
#define CENTERY -8.475 

using namespace edm;
using namespace std;

CTPPSPixelDigiAnalyzer:: CTPPSPixelDigiAnalyzer(const ParameterSet& pset) : theRPixDetTopology_()
{

  label = pset.getUntrackedParameter<string>("label");  
  verbosity_ = pset.getParameter<int> ("Verbosity");
#ifdef USE_MIDDLE_OF_PIXEL
  file = new TFile("CTPPSPixelDigiPlots2.root","RECREATE");

  hOneHitperEvent = new TH2D("OneHitperEvent","One Hit per Event",30,-8.511,-8.361,20,1,1.1);
  hOneHitperEvent2 = new TH2D("OneHitperEvent2","One Hit per Event 2",30,-8.511,-8.361,20,1,1.1);
#else
  file = new TFile("CTPPSPixelDigiPlots.root","RECREATE");
// hOneHitperEvent = new TH2D("OneHitperEvent","One Hit per Event",10,1,1.1,10,-8.55,-8.4);
// hOneHitperEvent2 = new TH2D("OneHitperEvent2","One Hit per Event 2",10,1,1.1,10,-8.55,-8.4);
  hOneHitperEvent = new TH2D("OneHitperEvent","One Hit per Event",30,-8.55,-8.4,20,1,1.1);
  hOneHitperEvent2 = new TH2D("OneHitperEvent2","One Hit per Event 2",30,-8.55,-8.4,20,1,1.1);
  hOneHitperEventCenter = new TH2D("OneHitperEventCenter","One Hit per Event Center",30,-0.075,0.075,20,-0.05,0.05);
  hOneHitperEvent2Center = new TH2D("OneHitperEvent2Center","Cluster Size 2",30,-0.075,0.075,20,-0.05,0.05);
#endif
  file->cd();
  hAllHits = new TH2D("AllHits","All Hits",10,1,1.1,10,-8.55,-8.4);

//  hAllHits = new TH2D("AllHits","All Hits",100,-5,5,100,-11,11);
  if(file->IsOpen()) cout<<"file open!"<<endl;
  else cout<<"*** Error in opening file ***"<<endl;

  psim_token = consumes<PSimHitContainer>( edm::InputTag("g4SimHits","CTPPSPixelHits") );
// psim_token = consumes<CrossingFrame<PSimHit>>(edm::InputTag("mix"));
  pixel_token = consumes<edm::DetSetVector<CTPPSPixelDigi>>( edm::InputTag(label,"") ); //label=RPixDetDigitizer???

 
}

CTPPSPixelDigiAnalyzer::~CTPPSPixelDigiAnalyzer(){
}


void CTPPSPixelDigiAnalyzer::beginJob(){
  found_corresponding_digi_count=0;
  for(int a=0; a<3; a++)  cumulative_cluster_size[a]=0;
}
void CTPPSPixelDigiAnalyzer::endJob(){
//cout<<"Number of analyzed event: "<<nevts<<endl;
//HitsAnalysis->Report();
  file->cd();
/*
  DigiTimeBox->Write();
  hDigis_global.Write();
  hDigis_W0.Write();
  hDigis_W1.Write();
  hDigis_W2.Write();
  hAllHits.Write();
*/
  hAllHits->Write();
  hOneHitperEvent->Write();
  hOneHitperEvent2->Write();
  hOneHitperEventCenter->Write();
  hOneHitperEvent2Center->Write();
  file->Close();

  cout << "found_corresponding_digi_count: " << found_corresponding_digi_count << endl;
  cout << "Cumulative cluster size (1,2,>2) = " << cumulative_cluster_size[0] << ", " << cumulative_cluster_size[1] << ", " << cumulative_cluster_size[2] << endl;

  delete file;
  delete hAllHits;
  delete hOneHitperEvent;
  delete hOneHitperEvent2;
  delete hOneHitperEventCenter;
  delete hOneHitperEvent2Center;

}

void  CTPPSPixelDigiAnalyzer::analyze(const Event & event, const EventSetup& eventSetup){
  if(verbosity_>0)cout << "--- Run: " << event.id().run()
		       << " Event: " << event.id().event() << endl;
  
  cout << "                                                            I do love Pixels     " << endl;  
  Handle<PSimHitContainer> simHits; 
  event.getByToken(psim_token,simHits);    

/*
  edm::Handle<CrossingFrame<PSimHit> > cf;
  event.getByToken(psim_token, cf);
*/
//	event.getByLabel("g4SimHits", "CTPPSPixelHits", simHits);


  edm::Handle< edm::DetSetVector<CTPPSPixelDigi> > CTPPSPixelDigis;
  event.getByToken(pixel_token, CTPPSPixelDigis);



//  ESHandle<DTGeometry> muonGeom;
//  eventSetup.get<MuonGeometryRecord>().get(muonGeom);


       
  if(verbosity_>0)
    std::cout << "\n=================== RPDA Starting SimHit access" << "  ===================" << std::endl;

  if(verbosity_>1)
    std::cout << simHits->size() << std::endl;

  double selected_pixel_lower_x;
  double selected_pixel_lower_y;
  double selected_pixel_upper_x;
  double selected_pixel_upper_y;
  double myX=0;
  double myY=0;

  theRPixDetTopology_.pixelRange(SELECTED_PIXEL_ROW,SELECTED_PIXEL_COLUMN,selected_pixel_lower_x,selected_pixel_upper_x,selected_pixel_lower_y,selected_pixel_upper_y);


//cout << selected_pixel_lower_x << " " << selected_pixel_upper_x << " " << selected_pixel_lower_y << " " << selected_pixel_upper_y << endl;
// 1  1.1 -8.55 -8.4


  double hit_inside_selected_pixel[2];
  bool found_hit_inside_selected_pixel = false;

  for(vector<PSimHit>::const_iterator hit = simHits->begin();
      hit != simHits->end(); hit++){    
 

    LocalPoint entryP = hit->entryPoint();
    LocalPoint exitP = hit->exitPoint();
//    int partType = hit->particleType();
    LocalPoint midP ((entryP.x()+exitP.x())/2.,(entryP.y()+exitP.y())/2.);
//    float path = (exitP-entryP).mag();
//    float path_x = fabs((exitP-entryP).x());
    

//-------------
//store simhit information if it hits selected pixel in selected unitId 
  //   cout << hit->detUnitId() << " "<< entryP << endl;
//    if(hit->detUnitId() ==  SELECTED_UNITID)hAllHits->Fill(entryP.x(),entryP.y());
#ifdef USE_MIDDLE_OF_PIXEL
    if(entryP.x() > selected_pixel_lower_x && entryP.x() < selected_pixel_upper_x && entryP.y() > (selected_pixel_lower_y+0.115*TG184) && entryP.y() < (selected_pixel_upper_y+0.115*TG184) 
#else
#ifdef USE_MIDDLE_OF_PIXEL_2
       if(midP.x() > selected_pixel_lower_x && midP.x() < selected_pixel_upper_x && midP.y() > selected_pixel_lower_y && midP.y() < selected_pixel_upper_y 
#else
	  if(entryP.x() > selected_pixel_lower_x && entryP.x() < selected_pixel_upper_x && entryP.y() > selected_pixel_lower_y && entryP.y() < selected_pixel_upper_y 
#endif
#endif

	     && hit->detUnitId() ==  SELECTED_UNITID){
	    hit_inside_selected_pixel[0]=entryP.x();
	    hit_inside_selected_pixel[1]=entryP.y();
	    found_hit_inside_selected_pixel = true;
#ifdef USE_MIDDLE_OF_PIXEL_2
	    hAllHits->Fill(midP.x(),midP.y());
	    myX=midP.x();
	    myY=midP.y();
#else
	    hAllHits->Fill(entryP.x(),entryP.y());
	    myX=entryP.x();
	    myY=entryP.y();
#endif
	    if(verbosity_>2)   
	      cout << hit_inside_selected_pixel[0] << " " << hit_inside_selected_pixel[1] << endl;
	  }

//--------------

	  if(verbosity_>1)
	    if( hit->timeOfFlight() > 0){
	      cout << "DetId: " << hit->detUnitId()
		   <<"PID: "<<hit->particleType()
		   <<" TOF: "<<hit->timeOfFlight()
		   <<" Proc Type: "<<hit->processType() 
		   <<" p: " << hit->pabs()
		   <<" x = " << entryP.x() << "   y = " <<entryP.y() <<  "  z = " << entryP.z() <<endl;
	    //     hAllHits.FillTOF(hit->timeOfFlight());


	    }
	  }


       if(verbosity_>0)
	 std::cout << "\n=================== RPDA Starting Digi access" << "  ===================" << std::endl;
       int numberOfDetUnits = 0;
    
// Iterate on detector units
       edm::DetSetVector<CTPPSPixelDigi>::const_iterator DSViter = CTPPSPixelDigis->begin();

       for( ; DSViter != CTPPSPixelDigis->end(); DSViter++) {
	 ++numberOfDetUnits;
 
	 DetId detIdObject(DSViter->detId());
	 if(verbosity_>1)       std::cout << "DetId: " << DSViter->detId()<< std::endl;

	 bool found_corresponding_digi = false;
	 unsigned int corresponding_digi_cluster_size = 0;

// looping over digis in a unit id
	 edm::DetSet<CTPPSPixelDigi>::const_iterator begin = (*DSViter).begin();
	 edm::DetSet<CTPPSPixelDigi>::const_iterator end = (*DSViter).end();

	 if(verbosity_>2){
	   std::cout << "FF  "<< DSViter->detId() << std::endl;
           for( edm::DetSet<CTPPSPixelDigi>::const_iterator di = begin; di != end; di++){
	     std::cout << "           Digi row  " << di->row() << ", col "<<di->column() <<std::endl ;

	   // reconvert the digi to local coordinates
	     double lx;
	     double ly;
	     double ux;
	     double uy;
	     unsigned int rr = di->row();
	     unsigned int cc = di->column();
// theRPixDetTopology_.pixelRange(SELECTED_PIXEL_ROW,SELECTED_PIXEL_COLUMN,selected_pixel_lower_x,selected_pixel_upper_x,selected_pixel_lower_y,selected_pixel_upper_y);
	     theRPixDetTopology_.pixelRange(rr,cc,lx,ux,ly,uy);

	     cout << " pixel boundaries x low up, y low up " << lx << " "<< ux << " "<< ly << " "<< uy << endl;

	   }
	 }

       //   if(DSViter->detId()/1e6 >2198.8 && DSViter->detId()/1e6 <2198.9) {    // looping only on one plane
	 if(DSViter->detId() == SELECTED_UNITID && found_hit_inside_selected_pixel
	    ){
	   for( edm::DetSet<CTPPSPixelDigi>::const_iterator di = begin; di != end; di++){

	     if(verbosity_>1)  	
	       std::cout << "           Digi row  " << di->row() << ", col "<<di->column() <<std::endl ;
	
	     if( di->row() == SELECTED_PIXEL_ROW && di->column() == SELECTED_PIXEL_COLUMN ){
	       found_corresponding_digi_count++;
	       found_corresponding_digi = true;
	       corresponding_digi_cluster_size = 1;
	  
	     }


	   }
//if coresponding digi found, re-loop to look for adjacent pixels
	   if( found_corresponding_digi){
	     for( edm::DetSet<CTPPSPixelDigi>::const_iterator di = begin; di != end; di++){
	  
	       if(verbosity_>1)  	
		 std::cout << "           Digi row  " << di->row() << ", col "<<di->column() <<std::endl ;
	  
	       if( 
		  (di->row() == SELECTED_PIXEL_ROW+1 && di->column() == SELECTED_PIXEL_COLUMN)
		  || 	     (di->row() == SELECTED_PIXEL_ROW-1 && di->column() == SELECTED_PIXEL_COLUMN)
		  || 	     (di->row() == SELECTED_PIXEL_ROW && di->column() == SELECTED_PIXEL_COLUMN+1)
		  || 	     (di->row() == SELECTED_PIXEL_ROW && di->column() == SELECTED_PIXEL_COLUMN-1)
		   ){
		 corresponding_digi_cluster_size++;	  
		 std::cout << "           Digi row  " << di->row() << ", col "<<di->column() <<std::endl ;
	       }
	     }
	   }
       


	 }
	 if( corresponding_digi_cluster_size >0){
	   std::cout << "corresponding_digi_cluster_size in the event: " << corresponding_digi_cluster_size << std::endl;
	 //     hOneHitperEvent->Fill(myX,myY);
	   hOneHitperEvent->Fill(myY,myX);
	   hOneHitperEventCenter->Fill(myY-CENTERY,myX-CENTERX);

	   if(corresponding_digi_cluster_size<3){
	     cumulative_cluster_size[corresponding_digi_cluster_size-1]++;
//	if(corresponding_digi_cluster_size>1)hOneHitperEvent2->Fill(myX,myY);
	     if(corresponding_digi_cluster_size>1){

	       hOneHitperEvent2->Fill(myY,myX);
	       hOneHitperEvent2Center->Fill(myY-CENTERY,myX-CENTERX);
	     }
	   }
	   else{
	     cumulative_cluster_size[2]++;
//	hOneHitperEvent2->Fill(myX,myY);
	     hOneHitperEvent2->Fill(myY,myX);
	     hOneHitperEvent2Center->Fill(myY-CENTERY,myX-CENTERX);
	   }
	 }
       }
     
       if(verbosity_>1)       std::cout << "numberOfDetUnits in the event: " << numberOfDetUnits << std::endl;


       }


#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

    DEFINE_FWK_MODULE(CTPPSPixelDigiAnalyzer);
