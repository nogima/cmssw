#include "DataFormats/CTPPSDigi/interface/RPStripDigiCollection.h"

//trig_mode: 0=no trigger, 1=one sector per chip, 2=4 sectors, 3=8 sectors, 4=gem mode (not implemented)
RPStripDigiCollection::RPStripDigiCollection(RPDetId det_id, unsigned int trig_mode)
  : chips_per_hyb_(4)
{
  det_id_ = det_id;
  trig_mode_ = trig_mode;
  switch(trig_mode_)
    {
    case 0: 
      strips_per_section_ = 0;
      break;
    case 1:
      strips_per_section_ = 128; //since we have 4 chips
      break;
    case 2:
      strips_per_section_ = 128/4; //since we have 4 chips
      break;
    case 3:
      strips_per_section_ = 128/8; //since we have 4 chips
      break;
    default:
      strips_per_section_ = 0;
    }
}

void RPStripDigiCollection::AddHit(int strip_no)
{
  hitsCont_.insert(strip_no);
  if(strips_per_section_)
    {
      trigCont_.insert(strip_no/strips_per_section_);
    }
}
