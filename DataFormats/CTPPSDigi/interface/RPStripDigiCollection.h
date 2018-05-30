#ifndef DataFormats_CTPPSDigi_RP_STRIPDIGI_COLLECTION_H
#define DataFormats_CTPPSDigi_RP_STRIPDIGI_COLLECTION_H

#include <set>
#include "DataFormats/CTPPSDigi/interface/RPTypes.h"

class RPStripDigiCollection {
 public:
  //trig_mode: 0=no trigger, 1=one sector per chip, 2=4 sectors, 3=8 sectors, 4=gem mode (not implemented)
  typedef std::set<short, std::less<short> > HitsContainer;
  typedef std::set<short, std::less<short> > TriggerContainer;
  
  RPStripDigiCollection(RPDetId det_id, unsigned int trig_mode);  
  void AddHit(int strip_no);
  
  inline const HitsContainer& GetHits() const {return hitsCont_;}
  inline const TriggerContainer& GetTriggers() const {return trigCont_;}
  inline unsigned int GetTriggerMode() const {return trig_mode_;}
  inline RPDetId GetDetId() const {return det_id_;}
  inline short GetStripsPerSection() {return strips_per_section_;}
  inline short GetChipsPerHybrid() {return chips_per_hyb_;}

 private:
  short chips_per_hyb_, strips_per_section_;
  RPDetId det_id_;
  unsigned int trig_mode_;
  HitsContainer hitsCont_;
  TriggerContainer trigCont_;
};

// Comparison operators
inline bool operator<( const RPStripDigiCollection& one, const RPStripDigiCollection& other) {
  return one.GetDetId() < other.GetDetId();
}

#endif
