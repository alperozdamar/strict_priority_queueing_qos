
#include "ns3/log.h"
#include "traffic-class.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TrafficClass");
NS_OBJECT_ENSURE_REGISTERED (TrafficClass);

TypeId
TrafficClass::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::TrafficClass")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl");
  return tid;
}

TrafficClass::TrafficClass ()
{
  NS_LOG_FUNCTION (this);
}

TrafficClass::TrafficClass (uint32_t maxPackets, uint32_t maxBytes, double_t weight, uint32_t priority_level, bool isDefault, std::vector<Filter *> filters)
{
  this->maxPackets = maxPackets;
  this->maxBytes = maxBytes;
  this->weight = weight;
  this->priority_level = priority_level;
  this->isDefault = isDefault;
  this->filters = filters;
  NS_LOG_FUNCTION (this);
}

TrafficClass::~TrafficClass ()
{
  NS_LOG_FUNCTION (this);
}

//for each filter in vector of filter call match on each filter
// even if one match -- return true
bool
TrafficClass::match (Ptr<Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);

  for (Filter *filter : filters)
    {
      if (filter->match (packet))
        {
          return true;
        }
    }
  return false;
}

bool
TrafficClass::IsEmpty ()
{
  return m_queue.empty ();
}

bool
TrafficClass::Enqueue (Ptr<Packet> packet)
{
  //std::cout<<"Test.TrafficClass.Enqueue.m_queue.size:"<<m_queue.size()<<std::endl;
  
  bytes+=packet->GetSize();
  m_queue.push (packet);
  //std::cout<<"Test.TrafficClass.Enqueue.packet:"<<packet<<std::endl;
  std::cout<<"Test.TrafficClass.Enqueue.m_queue.size.AFTER.PUSH:"<<m_queue.size()<<std::endl;  

  return true;
}

Ptr<ns3::Packet>
TrafficClass::Dequeue ()
{
  // Ptr<Packet> p = m_queue.front();
  // if(!m_queue.empty){
  //   m_queue.pop();
  // }
  // if(p){
  //   return p;
  // }
  // return 0;
  NS_LOG_FUNCTION (this);

  if (m_queue.empty ())
    {
      NS_LOG_LOGIC ("Queue empty");
      std::cout<<"Queue empty" <<std::endl;
      return 0;
    }

  Ptr<Packet> p = m_queue.front ();
  m_queue.pop ();
  bytes -= p-> GetSize ();
  NS_LOG_LOGIC ("Popped " << p);
  std::cout<< "Queue Size " << m_queue.size () << ",priority:"<< priority_level;
  NS_LOG_LOGIC ("Number bytes " << bytes);

  return p;
}

Ptr<ns3::Packet>
TrafficClass::Remove ()
{
    if(!m_queue.empty()){
       m_queue.pop();
  }
  return 0;
}

Ptr<ns3::Packet>
TrafficClass::Peek ()
{
  NS_LOG_FUNCTION (this);

  if (m_queue.empty ())
    {
      NS_LOG_LOGIC ("Queue empty");
      std::cout<<"Queue empty" <<std::endl;
    
      return 0;
    }

  Ptr<Packet> p = m_queue.front ();
  packets = m_queue.size ();
  bytes = bytes;

  return p;
}

} // namespace ns3