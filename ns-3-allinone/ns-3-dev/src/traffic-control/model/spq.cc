/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Rozita&Alper
 *  
 *  
 * Strict Priority Queueing(SPQ) the queue: to give priority
 * for sening the packet.
 * 
 * @author: Rozita Teymourzadeh <rteymourzadeh@usfca.edu>
 * @author: Alper Ozdamar <alper.ozdamar@gmail.com>
*/
#include "ns3/log.h"
#include "ns3/spq.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("SPQ");
NS_OBJECT_TEMPLATE_CLASS_DEFINE (SPQ, Packet);

template <typename Packet>
TypeId
SPQ<Packet>::GetTypeId (void)
{
  static TypeId tid =
      TypeId (("ns3::SPQ<" + GetTypeParamName<SPQ<Packet>> () + ">").c_str ())
          .SetParent<DiffServ<Packet>> ()
          .SetGroupName ("trafficControl")
          .template AddConstructor<SPQ<Packet>> () 
      ;
  return tid;
}

template <typename Packet>
SPQ<Packet>::SPQ () : DiffServ<Packet> (), NS_LOG_TEMPLATE_DEFINE ("SPQ")
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
SPQ<Packet>::SPQ (QueueMode mode, std::vector<TrafficClass *> trafficClassList)
    : NS_LOG_TEMPLATE_DEFINE ("SPQ")
{
  this->m_mode = mode;
  this->q_class = trafficClassList;
  std::cout << "SPQ.q_class.size: " << q_class.size () << std::endl;
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
SPQ<Packet>::~SPQ ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
bool
SPQ<Packet>::Enqueue (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);

  printf ("Test.SPQ.Enqueue\n");
  u_int32_t index = Classify (p);
//  std::cout << "Test.SPQ.Enqueue.index.matched: " << index
//            << ",priority:" << q_class[index]->priority_level << std::endl;
  q_class[index]->Enqueue (p);
//  std::cout << "Test.SPQ.Enqueue.index.matched: " << index
//            << ",priority:" << q_class[index]->priority_level << std::endl;
  DiffServ<Packet>::Enqueue(p);

  return true;
}

template <typename Packet>
Ptr<Packet>
SPQ<Packet>::Dequeue (void)
{
  NS_LOG_FUNCTION (this);
  printf ("Test.SPQ.Dequeue\n");
  Ptr<Packet> p;
  p = Schedule ();
  std::cout << "Schedule p in final Dequeue" << &p << std::endl;
  DiffServ<Packet>::Dequeue();
  return p;
}

template <typename Packet>
Ptr<Packet>
SPQ<Packet>::Remove (void)
{
  NS_LOG_FUNCTION (this);
  Ptr<Packet> item = DiffServ<Packet>::Remove ();
  NS_LOG_LOGIC ("Removed " << item);
  return item;
}

template <typename Packet>
Ptr<const Packet>
SPQ<Packet>::Peek (void) const
{
  NS_LOG_FUNCTION (this);

  return DiffServ<Packet>::Peek ();
}

template <typename Packet>
uint32_t
SPQ<Packet>::Classify (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  std::cout << "Test.SPQ.Classify!" << std::endl;

  uint32_t index = -1;

  for (uint32_t i = 0; i < q_class.size (); i++)
    {
      if ((q_class[i]->match (p)))
        {
          //std::cout << "SPQ.Matched!, for priority:" << q_class[i]->priority_level << std::endl;
          return index = i;
        }
      else
        {
          //std::cout<<"SPQ.Not Matched!"<<std::endl;
          //std::cout<<"SPQ.q_class[i]->isDefault:"<< q_class[i]->isDefault <<std::endl;
          if (q_class[i]->isDefault)
            { 
            //  std::cout << "SPQ.Not Matched! Putting to Default Queue. Index value is " << i
            //            << ", for priority:" << q_class[i]->priority_level << std::endl;
              index = i; 
            }
        }
    }

  

  return index;
}

template <typename Packet>
Ptr<Packet>
SPQ<Packet>::Schedule ()
{
  NS_LOG_FUNCTION (this);
  Ptr<Packet> p;
  for (uint32_t priority = 0; priority < 100; priority++)
    {
      //std::cout<<"SPQ.q_class.size():"<<  q_class.size()<<std::endl;
      for (uint32_t i = 0; i < q_class.size (); i++)
        {
          // std::cout<<"SPQ.priority_level:"<<  priority <<std::endl;
          // std::cout<<"SPQ.q_class[i]->m_queue.size():"<<  q_class[i]->m_queue.size() <<std::endl;
          if (q_class[i]->priority_level == priority &&
              q_class[i]->IsEmpty () != true) //HIGH PRIORITY
            {
              std::cout << "SPQ.priority_level is SAME!QUEUE is NOT EMPTY!priority:" << priority
                        << std::endl;
              p = q_class[i]->Dequeue ();
              return p;
            }
        }
    }
    return 0;
}

template <typename Packet>
bool
SPQ<Packet>::AddTrafficClass (TrafficClass *trafficClass)
{
  std::vector<TrafficClass *> trafficClassList;
  trafficClassList.push_back (trafficClass);
  this->q_class = trafficClassList;
  NS_LOG_FUNCTION (this);
  return true;
}

} // namespace ns3