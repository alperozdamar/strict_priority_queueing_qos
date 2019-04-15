
#include "ns3/log.h"
#include "ns3/integer.h"
#include "queue-disc.h"
#include "source-ip-address.h"


namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("SourceIpAddress");


    NS_OBJECT_ENSURE_REGISTERED (PacketFilter);

    SourceIpAddress::SourceIpAddress ()
    {
    NS_LOG_FUNCTION (this);
    }

    SourceIpAddress::~SourceIpAddress()
    {
    NS_LOG_FUNCTION (this); 
    }

    
    bool
    SourceIpAddress::Match (Ptr<Packet> packet) const
    {
    NS_LOG_FUNCTION (this << packet);
        
    /**
    *
    * TODO:    
    **/

    return true;
    }


}// namespace ns3