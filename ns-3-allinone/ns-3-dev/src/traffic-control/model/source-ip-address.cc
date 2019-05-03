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

bool SourceIpAddress::match (Ptr<Packet> packet){
    NS_LOG_FUNCTION (this << packet);
    Ptr<Packet> copy = packet->Copy ();
    PppHeader ppph;
		Ipv4Header iph;
		copy->RemoveHeader(ppph);
		copy->RemoveHeader(iph);

    std::cout<<" value:" << value <<std::endl;

		Ipv4Address Ipv4Address = iph.GetSource();
		if(Ipv4Address.IsEqual(this->value)){
			std::cout<<" Matched Ipv4Address:" << Ipv4Address <<std::endl;
			return true;
		}  else{
			std::cout<<" Not Matched Ipv4Address:" << Ipv4Address <<std::endl;
			return false;
		}
    }

} // namespace ns3