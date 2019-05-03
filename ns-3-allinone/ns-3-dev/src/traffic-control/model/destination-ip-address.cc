/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Rozita&Alper
 *  
 *  
 * Filter: To Filter different packets
 *
 * 
 * @author: Rozita Teymourzadeh <rteymourzadeh@usfca.edu>
 * @author: Alper Ozdamar <alper.ozdamar@gmail.com>
*/
#include "ns3/log.h"
#include "ns3/ipv4-header.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/destination-ip-address.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DestinationIpAddress");

NS_OBJECT_ENSURE_REGISTERED (DestinationIpAddress);

TypeId
DestinationIpAddress::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DestinationIpAddress")
    .SetParent<FilterElement> ()
    .SetGroupName ("trafficControl");
  return tid;
}

DestinationIpAddress::DestinationIpAddress ()
{
  NS_LOG_FUNCTION (this);
}

DestinationIpAddress::DestinationIpAddress (Ipv4Address ipV4Address)
{
  NS_LOG_FUNCTION (this);
  this->value = ipV4Address;
}

DestinationIpAddress::~DestinationIpAddress ()
{
  NS_LOG_FUNCTION (this);
}

bool
DestinationIpAddress::match (Ptr<Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);

  Ipv4Header ipv4Header;
  packet->PeekHeader (ipv4Header);

  Ipv4Address Ipv4Address = ipv4Header.GetDestination();

  if (Ipv4Address.IsEqual (value))
    {
      std::cout << " Matched Ipv4Address:" << Ipv4Address << std::endl;
      return true;
    }
  else
    {
      std::cout << " Not Matched Ipv4Address:" << Ipv4Address << std::endl;
      return false;
    }
}

} // namespace ns3
