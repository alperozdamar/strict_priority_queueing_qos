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

  // Came from project spec

    bool DoEnqueue (Ptr<ns3::Packet> p);

    Ptr<ns3::Packet> DoDequeue ();

    Ptr<ns3::Packet> DoRemove ();

    Ptr<const ns3::Packet> DoPeek (void) const;

    // wE MUST define these because inherrited from Queue
    bool Enqueue (Ptr<Packet> item);

    Ptr<Packet> Dequeue ();

    Ptr<Packet> Remove ();

    Ptr<const Packet> Peek (void) const;

   using Queue<Packet>::Head;
   using Queue<Packet>::Tail;
   using Queue<Packet>::DoEnqueue;
   using Queue<Packet>::DoDequeue;
   using Queue<Packet>::DoRemove;
   using Queue<Packet>::DoPeek;

  NS_LOG_TEMPLATE_DECLARE;
}; 

extern template class DiffServ<Packet>;
} // namespace ns3

#endif /* DIFFSERV_H */
