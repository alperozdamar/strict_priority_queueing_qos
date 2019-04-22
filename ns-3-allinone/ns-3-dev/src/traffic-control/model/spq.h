
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

private:

//Do Not Delete 
 
 // Initialize_Q_class_Test ();


   using Queue<Packet>::Head;
   using Queue<Packet>::Tail;
   using Queue<Packet>::DoEnqueue;
   using Queue<Packet>::DoDequeue;
   using Queue<Packet>::DoRemove;
   using Queue<Packet>::DoPeek;


   using DiffServ<Packet>::Schedule;
   using DiffServ<Packet>::Classify;

  NS_LOG_TEMPLATE_DECLARE;
};


extern template class SPQ<Packet>;
} // namespace ns3

#endif /* SPQ_H */
