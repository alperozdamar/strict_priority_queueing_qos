#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "diffServ.h"


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_ENSURE_REGISTERED (DiffServ);

// TypeId DiffServ::GetTypeId (void) 
// {
//     static TypeId tid = TypeId ("ns3::DiffServ");
//     SetParent<Queue> ()
//         .SetGroupName("Network")
//         .AddConstructor<DiffServ> ()
//         .AddAttribute ("Mode", 
//                        "Whether to use bytes (see MaxBytes) or packets (see MaxPackets) as the maximum queue size metric.", 
//                         EnumValue (QUEUE_MODE_PACKETS), 
//                         MakeEnumAccessor (&DiffServ::SetMode,&DiffServ::GetMode),
//                         MakeEnumChecker (QUEUE_MODE_BYTES, "QUEUE_MODE_BYTES", QUEUE_MODE_PACKETS, "QUEUE_MODE_PACKETS"))
//         .AddAttribute ("MaxPackets", "The maximum number of packets accepted by this DiffServe.",UintegerValue (100), 
//                         MakeUintegerAccessor (&DiffServ::m_maxPackets),MakeUintegerChecker<uint32_t> ())
//         .AddAttribute ("MaxBytes", "The maximum number of bytes accepted by this DiffServ.", UintegerValue (100 * 65535), 
//                         MakeUintegerAccessor (&DiffServ::m_maxBytes), MakeUintegerChecker<uint32_t> ())
//     ;

//     return tid;
// }

DiffServ::DiffServ () :
    Queue (),
    m_packets (),
    m_bytesInQueue (0)
{
    NS_LOG_FUNCTION (this);
}

DiffServ::~DiffServ ()
{
    NS_LOG_FUNCTION (this);
}

void
DiffServ::SetMode (DiffServ::QueueMode mode)
{
    NS_LOG_FUNCTION (this << mode);
    m_mode = mode;
}
 
DiffServ::QueueMode
DiffServ::GetMode (void) const
{
    NS_LOG_FUNCTION (this);
    return m_mode;
}

bool 
DiffServ::DoEnqueue (Ptr<ns3::Packet> p)
{
    NS_LOG_FUNCTION (this << p);

    if (m_mode == QUEUE_MODE_PACKETS && (m_packets.size () >= m_maxPackets))
    {
        NS_LOG_LOGIC ("Queue full (at max packets) -- droppping pkt");
        DropBeforeEnqueue (p);
        return false;
    }   

    if (m_mode == QUEUE_MODE_BYTES && (m_bytesInQueue + p->GetSize () >= m_maxBytes))
    {
        NS_LOG_LOGIC ("Queue full (packet would exceed max bytes) -- droppping pkt");
        DropBeforeEnqueue (p);
        return false;
    }

    m_bytesInQueue += p->GetSize ();
    m_packets.push (p);

    NS_LOG_LOGIC ("Number packets " << m_packets.size ());
    NS_LOG_LOGIC ("Number bytes " << m_bytesInQueue);

    return true;
}

Ptr<ns3::Packet>
DiffServ::DoDequeue (void)
{
    NS_LOG_FUNCTION (this);

    if (m_packets.empty ())
    {
        NS_LOG_LOGIC ("Queue empty");
        return 0;
    }

    Ptr<Packet> p = m_packets.front ();
    m_packets.pop ();
    m_bytesInQueue -= p->GetSize ();

    NS_LOG_LOGIC ("Popped " << p);

    NS_LOG_LOGIC ("Number packets " << m_packets.size ());
    NS_LOG_LOGIC ("Number bytes " << m_bytesInQueue);

    return p;
 }

Ptr<const ns3::Packet>
DiffServ::DoPeek (void) const
{
    NS_LOG_FUNCTION (this);

    if (m_packets.empty ())
    {
        NS_LOG_LOGIC ("Queue empty");
        return 0;
    }
    Ptr<Packet> p = m_packets.front ();

    NS_LOG_LOGIC ("Number packets " << m_packets.size ());
    NS_LOG_LOGIC ("Number bytes " << m_bytesInQueue);

    return p;
}

uint32_t
DiffServ::Classify (Ptr<ns3::Packet> p) 
{
    NS_LOG_FUNCTION (this);

    uint32_t flow;
    q_class.priority_level = 0;

    if (match(p))
    {
        q_class.priority_level = 1;
    } else{
        q_class.priority_level = 2;
    }

    return q_class.priority_level;
}

Ptr<ns3::Packet> 
DiffServ::Schedule (q_class) 
{
    NS_LOG_FUNCTION (this);

    //TODO
    return DoPeek();
}
} // namespace ns3
  
