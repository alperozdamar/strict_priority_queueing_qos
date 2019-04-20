
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "source-ip-address.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "ns3/simulator.h"
#include "ns3/mac48-address.h"
#include "ns3/llc-snap-header.h"
#include "ns3/error-model.h" 
#include "ns3/trace-source-accessor.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/lr-wpan-net-device.h" 
#include "ns3/point-to-point-net-device.h"
#include "ns3/point-to-point-channel.h"
#include "ns3/ppp-header.h" 
#include "ns3/udp-header.h"
#include "ns3/ipv4-header.h" 
#include "TrafficClass.h"
#include "stdio.h"
#include <iostream>
#include "ns3/drop-tail-queue.h"

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

    bool Filter::Match (Ptr<ns3::Packet> packet){
      auto iter = elements.begin();     
      for(;iter!=elements.end();iter++){
          std::cout<<*iter<<" "; 
          if ((**iter).Match(packet)==false){              
              return false;
          }                             
      }
      return true;      
    }
}// namespace ns3