#ifndef DataFormats_CTPPSDigi_RP_STRIPDIGI_H
#define DataFormats_CTPPSDigi_RP_STRIPDIGI_H

#include "DataFormats/CTPPSDigi/interface/RPTypes.h"

class RPStripDigi {
 public:
  RPStripDigi(RPDetId det_id=0, unsigned short strip_no=0)
    {
      det_id_=det_id; 
      strip_no_=strip_no;
    };
  inline RPDetId GetDetId() const {return det_id_;}
  inline unsigned short GetStripNo() const {return strip_no_;}
  
 private:
  RPDetId det_id_;
  unsigned short strip_no_;
};

// Comparison operators
inline bool operator<( const RPStripDigi& one, const RPStripDigi& other) {
  if(one.GetDetId() < other.GetDetId())
    return true;
  else if(one.GetDetId() == other.GetDetId())
    return one.GetStripNo() < other.GetStripNo();
  else 
    return false;
}

#endif
