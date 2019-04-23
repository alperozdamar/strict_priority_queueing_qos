
#include "ns3/log.h"
#include "traffic-class.h"

namespace ns3 {

    

    NS_LOG_COMPONENT_DEFINE ("TrafficClass");
    NS_OBJECT_ENSURE_REGISTERED (TrafficClass);

    TypeId 
    TrafficClass::GetTypeId (void)
    {
    static TypeId tid = TypeId ("ns3::TrafficClass")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl")
    ;
    return tid;
    }


    TrafficClass::TrafficClass ()
    {
      NS_LOG_FUNCTION (this);
    }

    TrafficClass::~TrafficClass()
    {
      NS_LOG_FUNCTION (this); 
    }

    //for each filter in vector of filter call match on each filter 
    // even if one match -- return true    
    bool TrafficClass::match(Ptr<Packet> packet)
    {
      NS_LOG_FUNCTION (this << packet);
      
      auto iter = filters.begin();

      for(;iter!=filters.end();iter++){
          std::cout<<*iter<<" "; 

          if ((**iter).match(packet)){

              return true; 
          }                   
      }
      return false;
    }

    //Enqueue func calls the head of the queue nd then calles enqueue of queue class
    bool TrafficClass::Enqueue (Ptr<Packet> item){            
      //m_queue -> Enqueue(packet);     //quue class's enqueue.
      return Enqueue (item);
      //return true;
    }
  
    Ptr<ns3::Packet> TrafficClass::Dequeue(){    
        Ptr<Packet> item = Dequeue ();
        return item ;
      //return m_queue -> Dequeue();            
    }


Ptr<ns3::Packet>
TrafficClass::Remove (void)
{  
  Ptr<ns3::Packet> item = Remove();
  return item;
}

Ptr<ns3::Packet>
TrafficClass::Peek (void) 
{

  return Peek ();
}

}// namespace ns3