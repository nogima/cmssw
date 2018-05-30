#ifndef DataFormats_CTPPSDigi_RP_DIG_CLUSTER
#define DataFormats_CTPPSDigi_RP_DIG_CLUSTER

#include "DataFormats/CTPPSDigi/interface/RPTypes.h"

class RPDigCluster
{
 public:
  RPDigCluster(RPDetId det_id, unsigned short str_beg, unsigned short str_end)
    : det_id_(det_id), str_beg_(str_beg), str_end_(str_end)
    {};
  RPDigCluster() : det_id_(0), str_beg_(0), str_end_(0) {}
  inline void DetId(RPDetId det_id) {det_id_ = det_id;}
  inline RPDetId DetId() const {return det_id_;}
  inline void StrBeg(unsigned short str_beg) {str_beg_ = str_beg;}
  inline unsigned short StrBeg() const {return str_beg_;}
  inline void StrEnd(unsigned short str_end) {str_end_ = str_end;}
  inline unsigned short StrEnd() const {return str_end_;}
  inline int GetNumberOfStrips() const {return (str_end_-str_beg_+1);}
  inline double CentreStripPos() const {return (str_beg_+str_end_)/2.0;}
 private:
  RPDetId det_id_;
  unsigned short str_beg_;
  unsigned short str_end_;
};

// Comparison operators
inline bool operator<( const RPDigCluster& one, const RPDigCluster& other) {
  if(one.DetId() < other.DetId())
    return true;
  else if(one.DetId() == other.DetId())
    return one.CentreStripPos() < other.CentreStripPos();
  else 
    return false;
}


#endif
