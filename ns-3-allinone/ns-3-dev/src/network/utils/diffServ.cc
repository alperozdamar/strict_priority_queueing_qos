#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "diffServ.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_ENSURE_REGISTERED (DiffServ);

TypeId DiffServ::GetTypeId (void) {
    static TypeId tid = TypeId ("ns3::DiffServ")
    SetParent<Queue> ()
    .SetGroupName("Network")
    .AddAttribute ("Mode", "Whether to use bytes (see MaxBytes) or packets (see MaxPackets) as the maximum queue size metric.", EnumValue (QUEUE_MODE_PACKETS),
        MakeEnumAccessor (&DropTailQueue::SetMode,&DropTailQueue::GetMode),
        MakeEnumChecker (QUEUE_MODE_BYTES, "QUEUE_MODE_BYTES", QUEUE_MODE_PACKETS, "QUEUE_MODE_PACKETS"))
    .AddAttribute ("MaxPackets", "The maximum number of packets accepted by this DropTailQueue.",UintegerValue (100), MakeUintegerAccessor (&DropTailQueue::m_maxPackets),MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("MaxBytes", "The maximum number of bytes accepted by this DropTailQueue.", UintegerValue (100 * 65535), MakeUintegerAccessor (&DropTailQueue::m_maxBytes), MakeUintegerChecker<uint32_t> ());

    return tid;
}

DropTailQueue::DropTailQueue () :
Queue (),
m_packets (),
m_bytesInQueue (0)
{
}

DropTailQueue::~DropTailQueue ()
{
NS_LOG_FUNCTION (this);
}

void
DropTailQueue::SetMode (DropTailQueue::QueueMode mode)
{
NS_LOG_FUNCTION (this << mode);
m_mode = mode;
}
 
DropTailQueue::QueueMode
DropTailQueue::GetMode (void) const
{
NS_LOG_FUNCTION (this);
return m_mode;
}

bool 
DropTailQueue::DoEnqueue (Ptr<Packet> p)
{
NS_LOG_FUNCTION (this << p);

if (m_mode == QUEUE_MODE_PACKETS && (m_packets.size () >= m_maxPackets))
{
NS_LOG_LOGIC ("Queue full (at max packets) -- droppping pkt");
Drop (p);
return false;
}

if (m_mode == QUEUE_MODE_BYTES && (m_bytesInQueue + p->GetSize () >= m_maxBytes))
{
 NS_LOG_LOGIC ("Queue full (packet would exceed max bytes) -- droppping pkt");
Drop (p);
return false;
}

    m_bytesInQueue += p->GetSize ();
    m_packets.push (p);

    NS_LOG_LOGIC ("Number packets " << m_packets.size ());
    NS_LOG_LOGIC ("Number bytes " << m_bytesInQueue);

    return true;
    }

    Ptr<Packet>
    DropTailQueue::DoDequeue (void)
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

  Ptr<const Packet>
  DropTailQueue::DoPeek (void) const
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
} // namespace ns3
  
