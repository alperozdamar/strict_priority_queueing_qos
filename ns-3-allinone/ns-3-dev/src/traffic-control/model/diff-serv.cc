#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "ns3/diff-serv.h"
#include "ns3/traffic-class.h"
#include <vector>
#include "stdio.h"
#include <iostream>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ, Packet);

template <typename Packet>
TypeId
DiffServ<Packet>::GetTypeId (void)
{
  static TypeId tid =
      TypeId (("ns3::DiffServ<" + GetTypeParamName<DiffServ<Packet>> () + ">").c_str ())
          .SetParent<Queue<Packet>> ()
          .SetGroupName ("trafficClass")
          .template AddConstructor<DiffServ<Packet>> ();
  return tid;
}

template <typename Packet>
DiffServ<Packet>::DiffServ () : Queue<Packet> (), NS_LOG_TEMPLATE_DEFINE ("DiffServ")
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
DiffServ<Packet>::~DiffServ ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
void
DiffServ<Packet>::SetMode (QueueMode mode)
{
  NS_LOG_FUNCTION (this << mode);
  this->m_mode = mode;
}

template <typename Packet>
QueueMode
DiffServ<Packet>::GetMode ()
{
  NS_LOG_FUNCTION (this);
  return m_mode;
}

template <typename Packet>
bool
DiffServ<Packet>::DoEnqueue (Ptr<ns3::Packet> p)
{
  NS_LOG_FUNCTION (this << p);

  auto iter = q_class.begin ();
  for (; iter != q_class.end (); iter++)
    {
      // std::cout<<*iter<<" ";
      if ((**iter).match (p))
        {
          return (**iter).Enqueue (p);
        }
      else
        {
        }
    }
  return false;
}

template <typename Packet>
Ptr<ns3::Packet>
DiffServ<Packet>::DoDequeue (void)
{
  NS_LOG_FUNCTION (this);
  auto iter = q_class.begin ();
  for (; iter != q_class.end (); iter++)
    {
      return (**iter).Dequeue ();
    }
  return 0;
}

template <typename Packet>
Ptr<const ns3::Packet>
DiffServ<Packet>::DoPeek () const
{
  NS_LOG_FUNCTION (this);
  auto iter = q_class.begin ();
  for (; iter != q_class.end (); iter++)
    {
      // std::cout<<*iter<<" ";
      if ((**iter).Peek () != 0)
        { //NULL check!
          return (**iter).Peek ();
        }
    }
  return 0;
}

template <typename Packet>
Ptr<ns3::Packet>
DiffServ<Packet>::DoRemove (void)
{
  NS_LOG_FUNCTION (this);
  // auto iter = q_class.begin();
  //   for(;iter!=q_class.end();iter++){
  //      // std::cout<<*iter<<" ";
  //         if((**iter).Peek()!=0){ //NULL check!
  //             return (**iter).Remove();
  //         }
  //   }
  // return 0;

  for (TrafficClass *tc : q_class)
    {
      if (tc->Peek () != 0)
        {
          return tc->Remove ();
        }
    }
  return 0;
}

template <typename Packet>
uint32_t
DiffServ<Packet>::Classify (Ptr<ns3::Packet> p)
{
  std::cout<<"Test.DiffServ.Classify!"<<std::endl;
  NS_LOG_FUNCTION (this << p);

  uint32_t match_index = -1;


  // std::cout<<"Diff-Serv.q_class.size():"<< q_class.size() <<std::endl;

  // for (uint32_t i=0; i< q_class.size();i++)
  // {
  //   if ((q_class[i]-> match (p)))
  //   {
  //      std::cout<<"Matched!"<<std::endl;
  //     return match_index = i;
  //   } 
  //   //TODO Alper to check
  //   else{      
  //     std::cout<<"Not Matched!"<<std::endl;
  //     std::cout<<"q_class[i]->isDefault:"<< q_class[i]->isDefault <<std::endl;
  //     if (q_class[i]->isDefault){
  //       match_index = i ; // Check
  //     }
  //   }
  // }
  return match_index;
}

template <typename Packet>
Ptr<ns3::Packet>
DiffServ<Packet>::Schedule ()
{
  NS_LOG_FUNCTION (this);  
  std::cout<<"Test.DiffServ.Schedule!"<<std::endl;

  // // TrafficClass *tc;
  // // if (tc ->priority_level ==1 && tc->IfEmpty()!= false)
  // // {
  // //   NS_LOG_LOGIC ("Queue with high priority is find - start dequeueing ...!!");
  // //   Ptr<Packet> p = tc -> Peek();
  // //   return p; 
  // // }

  // Ptr<Packet> p;
  // for(uint32_t priority= 0; priority < 100 ; priority++){   

  //   std::cout<<"DiffServ.q_class.size():"<<  q_class.size()<<std::endl;

  //   for (uint32_t i=0; i< q_class.size();i++)
  //   {   
  //       std::cout<<"DiffServ.priority_level:"<<  priority <<std::endl;
  //       std::cout<<"DiffServ.q_class[i]->m_queue.size():"<<  q_class[i]->m_queue.size() <<std::endl;
  //       if  (q_class[i]-> priority_level == priority  && q_class[i]->IfEmpty() != true)//HIGH PRIORITY 
  //       {          
  //         std::cout<<"DiffServ.priority_level MATCHED!QUEUE is NOT EMPTY!priority:"<<  priority <<std::endl;
  //         Ptr<Packet> p = q_class[i] -> Dequeue(); // Peek()
  //         return p;
  //       }
  //   }
  // }

  //   std::cout<< "PROBLEM!! Should not be here!" <<std::endl;

  return  0; 
}

template <typename Packet>
bool
DiffServ<Packet>::Enqueue (Ptr<Packet> item)
{
  NS_LOG_FUNCTION (this << item);

  return DoEnqueue (Tail (), item);
}

template <typename Packet>
Ptr<Packet>
DiffServ<Packet>::Dequeue (void)
{
  NS_LOG_FUNCTION (this);

  Ptr<Packet> item = DoDequeue (Head ());

  NS_LOG_LOGIC ("Popped " << item);

  return item;
}

template <typename Packet>
Ptr<Packet>
DiffServ<Packet>::Remove (void)
{
  NS_LOG_FUNCTION (this);

  Ptr<Packet> item = DoRemove (Head ());

  NS_LOG_LOGIC ("Removed " << item);

  return item;
}

template <typename Packet>
Ptr<const Packet>
DiffServ<Packet>::Peek (void) const
{
  NS_LOG_FUNCTION (this);

  return DoPeek (Head ());
}

} // namespace ns3
