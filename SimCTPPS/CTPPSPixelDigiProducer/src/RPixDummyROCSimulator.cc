#include "SimCTPPS/CTPPSPixelDigiProducer/interface/RPixDummyROCSimulator.h"
#include "Geometry/VeryForwardGeometry/interface/CTPPSPixelTopology.h"
#include <vector>
#include "TRandom.h"
#include <iostream>


RPixDummyROCSimulator::RPixDummyROCSimulator(const edm::ParameterSet &params, uint32_t det_id)
  : params_(params), det_id_(det_id)
{

  threshold_ = params.getParameter<double>("RPixDummyROCThreshold");
  electron_per_adc_ = params.getParameter<double>("RPixDummyROCElectronPerADC");
  VcaltoElectronGain_ = params.getParameter<int>("VCaltoElectronGain");
  VcaltoElectronOffset_ = params.getParameter<int>("VCaltoElectronOffset");
  doSingleCalibration_ = params.getParameter<bool>("doSingleCalibration");
  dead_pixel_probability_ = params.getParameter<double>("RPixDeadPixelProbability");
  dead_pixels_simulation_on_ = params.getParameter<bool>("RPixDeadPixelSimulationOn");
  pixels_no_ = CTPPSPixelTopology().detPixelNo();
  verbosity_ = params.getParameter<int>("RPixVerbosity");
  links_persistence_ = params.getParameter<bool>("CTPPSPixelDigiSimHitRelationsPersistence");
  
  if(dead_pixels_simulation_on_)
    SetDeadPixels();

}

void RPixDummyROCSimulator::ConvertChargeToHits(const std::map<unsigned short, double, std::less<unsigned short> > &signals, 
						std::map<unsigned short, std::vector< std::pair<int, double> > > &theSignalProvenance, 
						std::vector<CTPPSPixelDigi> &output_digi, 
						std::vector<std::vector<std::pair<int, double> > >  &output_digi_links,
                                                const CTPPSPixelGainCalibrations *pcalibrations
						)
{

  for(std::map<unsigned short, double, std::less<unsigned short> >::const_iterator i=signals.begin(); 
      i!=signals.end(); ++i)
    {
    //one threshold per hybrid
      unsigned short pixel_no = i->first;   // questo dovrebbe essere il PixelIndex di CTPPSPixelSimTopology.h (col*160+row)
      //std::cout << " --------------------------------------- threshold " << threshold_ << std::endl;
      if(verbosity_)std::cout << "Dummy ROC adc and threshold : "<< i->second << ", " << threshold_ << std::endl; 
      if(i->second > threshold_ && (!dead_pixels_simulation_on_ 
				    || dead_pixels_.find(pixel_no)==dead_pixels_.end() ))
	{
          float gain=0;
          float pedestal=0;
          int adc = 0;
	  uint32_t col = pixel_no / 160;
	  uint32_t row = pixel_no % 160;

          const CTPPSPixelGainCalibration& DetCalibs = pcalibrations->getGainCalibration(det_id_);

          // Avoid exception due to col > 103 in case of 2x2 plane. To be removed
          if (col >= DetCalibs.getNCols()) {
		std::cout  << "arm: " << int((det_id_>>24)& 0X1) << " plane: " << int((det_id_>>16)&0X7) 
		<< " col: " << col << " row: " << row << std::endl;
		continue;
	  }
          if (col >= DetCalibs.getNCols()) throw cms::Exception("CorruptedData")
	   << "[RPixDummyROCSimulator::ConvertChargeToHits] Pixel out of range: col " << col << " row " << row;;

          if (doSingleCalibration_){
           adc = int(round(i->second / electron_per_adc_));
          } else {
           if(DetCalibs.getDetId() != 0){
             gain = DetCalibs.getGain(col,row)*1800./260.; // *highRangeCal/lowRangeCal
             pedestal = DetCalibs.getPed(col,row);
             adc = int(round((i->second - VcaltoElectronOffset_ )/(gain*VcaltoElectronGain_) + pedestal));
           } 
          } 
	  //std::cout << "------- RPixDummyROC -- charge, e_per_adc, adc " << i->second << ", "<< electron_per_adc_ << ", " << adc << std::endl;

/// set maximum for 8 bits adc
	  if (adc >=255) adc=255;
	  output_digi.push_back(CTPPSPixelDigi(row,col,adc) );//(det_id_, pixel_no)); /// ?????????????????????????????????????? devo metterci row, col e conteggi adc
	  if(links_persistence_)
	    {
	      output_digi_links.push_back(theSignalProvenance[pixel_no]);
	      if(verbosity_)
		{
		  std::cout<<"digi links size="<<theSignalProvenance[pixel_no].size()<<std::endl;
		  for(unsigned int u=0; u<theSignalProvenance[pixel_no].size(); ++u)
		    {
		      std::cout<<"   digi: particle="<<theSignalProvenance[pixel_no][u].first<<" energy [electrons]="<<theSignalProvenance[pixel_no][u].second<<std::endl;
		    }
		}
	    }
 
	}
    }

  if(verbosity_)
    {
      for(unsigned int i=0; i<output_digi.size(); ++i)
	{
	  std::cout<<"Dummy ROC Simulator "<<   det_id_ << "     row= " //output_digi[i].GetDetId()<<" "
		   <<output_digi[i].row() << "   col= " << output_digi[i].column() << "   adc= "<<  output_digi[i].adc() <<std::endl;
	}
    }
}

void RPixDummyROCSimulator::SetDeadPixels()
{
  dead_pixels_.clear();
  double dead_pixel_number = gRandom->Binomial(pixels_no_, dead_pixel_probability_);
  
  for(int i=0; i<dead_pixel_number; ++i)
    {
      dead_pixels_.insert(gRandom->Integer(pixels_no_));
    }
}

