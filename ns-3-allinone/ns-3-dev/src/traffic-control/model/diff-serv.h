/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
*
*
 */

#ifndef DIFFSERV_H
#define DIFFSERV_H

#include "ns3/log.h"
#include <queue>
#include "ns3/packet.h"
#include "ns3/queue.h"
#include "traffic-class.h"
#include <vector>

namespace ns3 {

enum QueueMode
  {
    QUEUE_MODE_PACKETS,
    QUEUE_MODE_BYTES,
  };

class TraceContainer;
template<typename Packet>
class DiffServ : public Queue<ns3::Packet>{
public: 

  static TypeId GetTypeId (void);  
  DiffServ();
  virtual ~DiffServ();
  void SetMode (QueueMode mode);
  QueueMode GetMode (void);
  Ptr<ns3::Packet> Schedule (void);
  uint32_t Classify (Ptr<ns3::Packet> p);



private: 

  QueueMode m_mode; 
  std::vector<TrafficClass*> q_class;   

  bool DoEnqueue (Ptr<ns3::Packet> p);
  Ptr<ns3::Packet> DoDequeue (void);
  Ptr<ns3::Packet> DoRemove (void);
  Ptr<const ns3::Packet> DoPeek (void) const;
    

  NS_LOG_TEMPLATE_DECLARE;
}; 

extern template class DiffServ<Packet>;
} // namespace ns3

#endif /* DIFFSERV_H */
