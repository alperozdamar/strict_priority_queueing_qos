
#ifndef FILTER_H
#define FILTER_H

 
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "filterElement.h"

namespace ns3 {

class Filter: public Object {
public:

std::vector<FilterElement> elements; 

//static TypeId GetTypeId (void);

  Filter ();
  ~Filter ();
  

  bool Match (Ptr<Packet> packet);  

};

} // namespace ns3

#endif /* FilterElement */
