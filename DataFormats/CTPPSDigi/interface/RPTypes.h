#ifndef DataFormatsCTPPSDigiRPTypes_H
#define DataFormatsCTPPSDigiRPTypes_H

#include <boost/cstdint.hpp>

typedef unsigned int RPStationId;
typedef unsigned int RPId;
typedef uint32_t RPDetId;

class MADXBeamType
{
  public:
    enum BeamType {DEFAULT, BEAM1, BEAM2, BEAM4};
};

#endif //DataFormatsCTPPSDigiRPTypes_H
