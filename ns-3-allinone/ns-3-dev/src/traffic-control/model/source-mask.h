
#ifndef SOURCE_MASK_H
#define SOURCE_MASK_H


#include "ns3/log.h"
#include "ns3/filter-element.h"
#include "ns3/ipv4-address.h" 

namespace ns3 {


class SourceMask: public FilterElement {
public:

  static TypeId GetTypeId (void);

  SourceMask ();
  SourceMask (Ipv4Mask ipv4Mask);  
  ~SourceMask ();

  
  bool match (Ptr<Packet> packet);


private:
  Ipv4Mask value;   

};

} // namespace ns3

#endif /* SOURCE_MASK_H */