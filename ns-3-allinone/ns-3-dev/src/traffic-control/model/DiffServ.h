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
#include "TrafficClass.h"
#include <vector>

namespace ns3 {

class TraceContainer;
class DiffServ : public Queue<ns3::Packet>{
public:

  enum QueueMode
  {
    QUEUE_MODE_PACKETS,
    QUEUE_MODE_BYTES,
  };
  DiffServ();
  virtual ~DiffServ();
  void SetMode (DiffServ::QueueMode mode);
  DiffServ::QueueMode GetMode (void) const;
  Ptr<ns3::Packet> Schedule ();
  uint32_t Classify (Ptr<ns3::Packet> p);

  //TODO : Remove if not needed
  static TypeId GetTypeId (void); 

private: 

  QueueMode m_mode; 
  std::vector<TrafficClass> q_class;   

  virtual bool DoEnqueue (Ptr<ns3::Packet> p);
  virtual Ptr<ns3::Packet> DoDequeue (void);
  //virtual Ptr<ns3::Packet> DoRemove (void);
  virtual Ptr<const ns3::Packet> DoPeek (void) const;
  
  
  //TODO : Remove if not needed
  std::queue<Ptr<ns3::Packet>> m_packets; 
  uint32_t m_maxPackets;              
  uint32_t m_maxBytes;                
  uint32_t m_bytesInQueue;  

}; 
} // namespace ns3

#endif /* DIFFSERV_H */
