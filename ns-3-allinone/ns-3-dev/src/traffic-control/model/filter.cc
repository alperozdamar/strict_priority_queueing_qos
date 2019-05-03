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
#include "source-ip-address.h"
#include "traffic-class.h"
#include "filter.h"


namespace ns3 {
    NS_LOG_COMPONENT_DEFINE ("Filter");
    NS_OBJECT_ENSURE_REGISTERED (Filter);

    Filter::Filter ()
    {
      NS_LOG_FUNCTION (this);
    }
    
    Filter::~Filter()
    {
      NS_LOG_FUNCTION (this); 
    }

    /**
     * To match the packet according to filters.
     * 
     * */    
    bool Filter::match (Ptr<ns3::Packet> packet){
      auto iter = elements.begin();     
      for(;iter!=elements.end();iter++){
          std::cout<<*iter<<" "; 
          if ((**iter).match(packet)==false){              
              return false;
          }                             
      }
      return true;      
    }
}// namespace ns3