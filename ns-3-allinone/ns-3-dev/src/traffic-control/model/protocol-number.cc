
#include "ns3/log.h"
#include "protocol-number.h"

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

    ProtocolNumber::ProtocolNumber (uint32_t val)
    {
        value = val;
    }

    
    bool
    ProtocolNumber::match (Ptr<Packet> packet)
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