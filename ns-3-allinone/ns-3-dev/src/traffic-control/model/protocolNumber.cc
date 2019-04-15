
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
#include "protocolNumber.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("ProtocolNumber");


    NS_OBJECT_ENSURE_REGISTERED (ProtocolNumber);

    TypeId 
    ProtocolNumber::GetTypeId (void)
    {
    static TypeId tid = TypeId ("ns3::ProtocolNumber")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl")
    ;
    return tid;
    }


    ProtocolNumber::ProtocolNumber ()
    {
    NS_LOG_FUNCTION (this);
    }

    ProtocolNumber::~ProtocolNumber()
    {
    NS_LOG_FUNCTION (this); 
    }

    
    bool
    ProtocolNumber::Match (Ptr<Packet> packet) const
    {
    NS_LOG_FUNCTION (this << packet);
    

    Ipv4Header ipv4Header;
    packet->PeekHeader(ipv4Header);

    
    uint8_t protocolNumber = ipv4Header.GetProtocol();
    
    if(protocolNumber==value ){
        std::cout<<" Matched protocolNumber:" << protocolNumber <<std::endl;
        return true;
    }  else{
        std::cout<<" Not Matched protocolNumber:" << protocolNumber <<std::endl;
        return false;

    } 

    }


}// namespace ns3