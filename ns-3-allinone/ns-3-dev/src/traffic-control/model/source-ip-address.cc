
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
#include "source-ip-address.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("SourceIpAddress");


    NS_OBJECT_ENSURE_REGISTERED (SourceIpAddress);

    TypeId 
    SourceIpAddress::GetTypeId (void)
    {
    static TypeId tid = TypeId ("ns3::SourceIpAddress")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl")
    ;
    return tid;
    }


    SourceIpAddress::SourceIpAddress ()
    {
    NS_LOG_FUNCTION (this);
    }

    SourceIpAddress::~SourceIpAddress()
    {
    NS_LOG_FUNCTION (this); 
    }

    
    bool
    SourceIpAddress::Match (Ptr<Packet> packet) 
    {
    NS_LOG_FUNCTION (this << packet);
    

    Ipv4Header ipv4Header;
    packet->PeekHeader(ipv4Header);

    
    Ipv4Address Ipv4Address =ipv4Header.GetSource();

    
    if(Ipv4Address.IsEqual(value)){
        std::cout<<" Matched Ipv4Address:" << Ipv4Address <<std::endl;
        return true;
    }  else{
        std::cout<<" Not Matched Ipv4Address:" << Ipv4Address <<std::endl;
        return false;

    } 

    }


}// namespace ns3