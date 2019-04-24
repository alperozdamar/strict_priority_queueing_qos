
#include "ns3/log.h"
#include "traffic-class.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TrafficClass");
NS_OBJECT_ENSURE_REGISTERED (TrafficClass);

TypeId
TrafficClass::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::TrafficClass").SetParent<Object> ().SetGroupName ("TrafficControl");
  return tid;
}

TrafficClass::TrafficClass ()
{
  NS_LOG_FUNCTION (this);
}

TrafficClass::TrafficClass (uint32_t maxPackets, uint32_t packets, bool isDefault,
                            std::vector<Filter *> filters)
{
  this->maxPackets = maxPackets;
  this->packets = packets;
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

  // auto iter = filters.begin ();

  // for (; iter != filters.end (); iter++)
  //   {
  //     std::cout << *iter << " ";

  //     if ((**iter).match (packet))
  //       {

  //         return true;
  //       }
  //   }
  // return false;
  // NS_LOG_FUNCTION(this<<packet);
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
TrafficClass::IfEmpty ()
{
  return m_queue.empty ();
}

bool
TrafficClass::Enqueue (Ptr<Packet> packet)
{
  m_queue.push (packet);

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
      return 0;
    }

  Ptr<Packet> p = m_queue.front ();
  m_queue.pop ();
  bytes -= p-> GetSize ();
  NS_LOG_LOGIC ("Popped " << p);
  NS_LOG_LOGIC ("Number packets " << m_queue.size ());
  NS_LOG_LOGIC ("Number bytes " << bytes);

  return p;
}

Ptr<ns3::Packet>
TrafficClass::Remove (void)
{
  Ptr<ns3::Packet> item;
  return item;
}

Ptr<ns3::Packet>
TrafficClass::Peek (void)
{
  NS_LOG_FUNCTION (this);

  if (m_queue.empty ())
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_queue.front ();
  packets = m_queue.size ();
  bytes = bytes;

  return p;
}

} // namespace ns3