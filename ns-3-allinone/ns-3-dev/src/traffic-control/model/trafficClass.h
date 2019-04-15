
#ifndef TRAFFIC_CLASS_H
#define TRAFFIC_CLASS_H

#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "ns3/queue.h" 
#include "filter.h"

namespace ns3 {


class TrafficClass: public Object {
public:

  static TypeId GetTypeId (void);

  TrafficClass ();
  ~TrafficClass ();

  std::vector<Filter> filters;  

  bool Enqueue (Ptr<Packet> packet);
  
  Ptr<Packet> Dequeue();

  bool Match (Ptr<Packet> packet); 


private:
  uint32_t bytes;
  uint32_t packets;
  uint32_t maxPackets;
  uint32_t maxBytes;
  double_t weight;
  uint32_t priorityLevel;
  bool isDefault;
  Ptr<Queue<Packet>> m_queue;   


};

} // namespace ns3

#endif /* TrafficClass */
