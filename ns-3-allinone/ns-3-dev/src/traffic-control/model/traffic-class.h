
#ifndef TRAFFIC_CLASS_H
#define TRAFFIC_CLASS_H

#include "ns3/log.h"
#include "filter.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/queue.h"


namespace ns3 {


class TrafficClass: public Object {
public:

  static TypeId GetTypeId (void);

  TrafficClass ();
  ~TrafficClass ();

  std::vector<Filter*> filters;  
  bool Enqueue (Ptr<ns3::Packet> packet);
  Ptr<ns3::Packet> Dequeue();
  bool match (Ptr<ns3::Packet> packet); 
  Ptr<ns3::Packet>Remove(void);
  Ptr<ns3::Packet>Peek(void);

private:
  uint32_t bytes;
  uint32_t packets;       //related SPQ
  uint32_t maxPackets;    //related SPQ
  uint32_t maxBytes;      //related DDR
  double_t weight;        //related DDR
  uint32_t priority_level;  
  bool isDefault;        //only one traffic class should have isDefault value=1
  Ptr<ns3::Queue<ns3::Packet>> m_queue;  
};
  //PacketFilter
} // namespace ns3

#endif /* TRAFFICCLASS_H */
