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
#ifndef PROTOCOL_NUMBER_H
#define PROTOCOL_NUMBER_H


#include "ns3/log.h"
#include "filter-element.h"
#include "ns3/ipv4-address.h" 
#include "ns3/ipv4-header.h"
#include "ns3/point-to-point-net-device.h"

namespace ns3 {

class ProtocolNumber: public FilterElement {
  
public:

  static TypeId GetTypeId (void);

  ProtocolNumber ();
  ProtocolNumber(uint32_t val);  
  ~ProtocolNumber ();  

  bool match (Ptr<ns3::Packet> packet);


private:
  uint32_t value;  

};

} // namespace ns3

#endif /* PROTOCOL_NUMBER_H */
