
#ifndef FILTER_ELEMENT_H
#define FILTER_ELEMENT_H

 
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"

namespace ns3 {

class FilterElement: public Object {
public:

//static TypeId GetTypeId (void);

  FilterElement ();
  virtual ~FilterElement ();
  

  virtual bool Match (Ptr<Packet> packet) const = 0;


};

} // namespace ns3

#endif /* FilterElement */
