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
#ifndef SOURCE_IP_ADDRESS_H
#define SOURCE_IP_ADDRESS_H


#include "ns3/log.h"
#include "ns3/filter-element.h"
#include "ns3/ipv4-address.h" 

namespace ns3 {

class SourceIpAddress: public FilterElement {
public:

  static TypeId GetTypeId (void);
  
  SourceIpAddress ();
  SourceIpAddress (Ipv4Address ipv4Address);
  ~SourceIpAddress (); 



  bool match (Ptr<Packet> packet);


private:
  Ipv4Address value;  

};

} // namespace ns3

#endif /* SOURCE_IP_ADDRESS */
