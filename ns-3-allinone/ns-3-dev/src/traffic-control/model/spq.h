
#ifndef SPQ_H
#define SPQ_H

#include "diff-serv.h"
#include "ns3/queue.h"
#include "ns3/log.h"

namespace ns3 {

template <typename Packet>
class SPQ : public DiffServ<Packet> 
{

public:
  SPQ ();

  SPQ (QueueMode mode, std::vector<TrafficClass *> trafficClassVector);

  static TypeId GetTypeId (void);

  virtual ~SPQ ();

  bool Enqueue (Ptr<Packet> item);

  Ptr<Packet> Dequeue ();

  Ptr<Packet> Remove ();

  Ptr<const Packet> Peek (void) const;

  u_int32_t Classify (Ptr<Packet> item);

  Ptr<Packet> Schedule ();

  bool AddTrafficClass (TrafficClass* trafficClass);

  QueueMode m_mode; 
  std::vector<TrafficClass*> q_class; 

private:

   //using Queue<Packet>::Head;
   //using Queue<Packet>::Tail;
   using DiffServ<Packet>::Enqueue;
   using DiffServ<Packet>::Dequeue;
   using DiffServ<Packet>::Remove;
   using DiffServ<Packet>::Peek;


   using DiffServ<Packet>::Schedule;
   using DiffServ<Packet>::Classify;

  NS_LOG_TEMPLATE_DECLARE;
};


extern template class SPQ<Packet>;
} // namespace ns3

#endif /* SPQ_H */
