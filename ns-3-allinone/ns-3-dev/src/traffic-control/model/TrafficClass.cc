
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "source-ip-address.h"
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "ns3/log.h"
#include "ns3/queue.h"
#include "ns3/simulator.h"
#include "ns3/mac48-address.h"
#include "ns3/llc-snap-header.h"
#include "ns3/error-model.h" 
#include "ns3/trace-source-accessor.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/lr-wpan-net-device.h" 
#include "point-to-point-net-device.h"
#include "point-to-point-channel.h"
#include "ppp-header.h" 
#include "ns3/udp-header.h"
#include "ns3/ipv4-header.h" 
#include "TrafficClass.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("TrafficClass");
    NS_OBJECT_ENSURE_REGISTERED (TrafficClass);

    TypeId 
    TrafficClass::GetTypeId (void)
    {
    static TypeId tid = TypeId ("ns3::TrafficClass")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl")
    ;
    return tid;
    }


    TrafficClass::TrafficClass ()
    {
      NS_LOG_FUNCTION (this);
    }

    TrafficClass::~TrafficClass()
    {
      NS_LOG_FUNCTION (this); 
    }

    
    bool TrafficClass::Match(Ptr<Packet> packet) 
    {
      NS_LOG_FUNCTION (this << packet);

      //TODO
  
      return true;
    }


    bool TrafficClass::Enqueue (Ptr<Packet> packet){
      m_queue -> Enqueue(packet);
      return true;
    }
  
    Ptr<ns3::Packet> Dequeue(){
      //TODO
    }

}// namespace ns3