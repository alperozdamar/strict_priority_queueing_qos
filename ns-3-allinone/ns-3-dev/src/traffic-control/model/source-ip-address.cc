
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


    int32_t
    SourceIpAddress::Classify (Ptr<QueueDiscItem> item) const
    {
    NS_LOG_FUNCTION (this << item);

    if (!CheckProtocol (item))
    {
        NS_LOG_LOGIC ("Unable to classify packets of this protocol");
        return PF_NO_MATCH;
    }

    return DoClassify (item);
    }

    bool
    SourceIpAddress::Match (Ptr<Packet> packet) const
    {
    NS_LOG_FUNCTION (this << packet);

    if (!CheckProtocol (packet))
    {
        NS_LOG_LOGIC ("Unable to classify packets of this protocol");
        return PF_NO_MATCH;
    }


    /**
    *
    * TODO:
    * 
    * 
    **/


    return DoClassify (packet);
    }


}// namespace ns3