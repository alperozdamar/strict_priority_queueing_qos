#ifndef DESTINATION_MASK_H
#define DESTINATION_MASK_H


#include "ns3/log.h"
#include "ns3/filter-element.h" 
#include "ns3/ipv4-address.h" 

namespace ns3 {


class DestinationMask: public FilterElement {
public:

  static TypeId GetTypeId (void);

  DestinationMask ();
  DestinationMask (Ipv4Mask ipv4Mask);  
  ~DestinationMask ();


  bool match (Ptr<Packet> packet);


private:
  Ipv4Mask value;   

};

} // namespace ns3

#endif /* DESTINATION_MASK_H */
