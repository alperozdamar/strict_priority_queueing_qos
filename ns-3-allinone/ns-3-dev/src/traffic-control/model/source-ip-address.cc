
#include "ns3/log.h"
#include "ns3/ipv4-header.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/source-ip-address.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SourceIpAddress");

NS_OBJECT_ENSURE_REGISTERED (SourceIpAddress);

TypeId
SourceIpAddress::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::SourceIpAddress").SetParent<FilterElement> ().SetGroupName ("trafficControl");
  return tid;
}

SourceIpAddress::SourceIpAddress ()
{
  NS_LOG_FUNCTION (this);
}

SourceIpAddress::SourceIpAddress (Ipv4Address ipV4Address)
{
  NS_LOG_FUNCTION (this);
  this->value = ipV4Address;
}

SourceIpAddress::~SourceIpAddress ()
{
  NS_LOG_FUNCTION (this);
}

bool
SourceIpAddress::match (Ptr<Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);

  

  Ipv4Header ipv4Header;
  packet->PeekHeader (ipv4Header);

  Ipv4Address ipv4Address = ipv4Header.GetSource ();

  std::cout << " SourceIpAddress::match.Ipv4Address:" << ipv4Address << std::endl;
  //49153
  std::cout << " SourceIpAddress.value:" << value << std::endl;

  if (ipv4Address==value)
    {
      std::cout << " Matched Ipv4Address:" << ipv4Address << std::endl;
      return true;
    }
  else
    {
      std::cout << " Not Matched Ipv4Address:" << ipv4Address << std::endl;
      return false;
    }
}

} // namespace ns3