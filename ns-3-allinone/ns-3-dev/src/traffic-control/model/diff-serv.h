/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
*
*
 */

#ifndef DIFFSERV_H
#define DIFFSERV_H

#include "ns3/log.h"
#include <queue>
#include "ns3/packet.h"
#include "ns3/queue.h"
#include "traffic-class.h"
#include <vector>

namespace ns3 {

class TraceContainer;
template<typename Packet>
class DiffServ : public Queue<ns3::Packet>{
public:  

enum QueueMode
  {
    QUEUE_MODE_PACKETS,
    QUEUE_MODE_BYTES,
  };


  DiffServ();
  virtual ~DiffServ();
  void SetMode (DiffServ<Packet>::QueueMode mode);
  DiffServ<Packet>::QueueMode GetMode (void);
  Ptr<ns3::Packet> Schedule (void);
  uint32_t Classify (Ptr<ns3::Packet> p);

  //TODO : Remove if not needed
  //static TypeId GetTypeId (void); 

private: 

  QueueMode m_mode; 
  std::vector<TrafficClass*> q_class;   

  bool DoEnqueue (Ptr<ns3::Packet> p);
  Ptr<ns3::Packet> DoDequeue (void);
  Ptr<ns3::Packet> DoRemove (void);
  Ptr<const ns3::Packet> DoPeek (void) const;
    
  //TODO : Remove if not needed
  //std::queue<Ptr<ns3::Packet>> m_packets; 
  //uint32_t m_maxPackets;              
  //uint32_t m_maxBytes;                
  //uint32_t m_bytesInQueue;  
  NS_LOG_TEMPLATE_DECLARE;

  

}; 

template <typename Packet>
DiffServ<Packet>::DiffServ()
//:Queue ()    
{
    //NS_LOG_FUNCTION (this);
}

template <typename Packet>
DiffServ<Packet>::~DiffServ ()
{
   // NS_LOG_FUNCTION (this);
}


//template <typename Packet>
void
DiffServ<Packet>::SetMode (typename DiffServ<Packet>::QueueMode mode)
{
    //NS_LOG_FUNCTION (this << mode);
    m_mode = mode;
}
 
template <typename Packet>
typename DiffServ<Packet>::QueueMode
DiffServ<Packet>::GetMode ()    
{
    //NS_LOG_FUNCTION (this);
    return m_mode;
}


//We should call TRaffic Class's Enqueu??? 
template <typename Packet>
bool
DiffServ<Packet>::DoEnqueue (Ptr<ns3::Packet> p)
{
    //NS_LOG_FUNCTION (this << p);

    auto iter = q_class.begin();
      for(;iter!=q_class.end();iter++){ 
         // std::cout<<*iter<<" ";    
            if((**iter).match(p)){
                return (**iter).Enqueue(p);
            }else{

            } 
    }       
    return false;
}
 
template <typename Packet>
Ptr<ns3::Packet>
DiffServ<Packet>::DoDequeue (void)
{
    //NS_LOG_FUNCTION (this);
    auto iter = q_class.begin();
    for(;iter!=q_class.end();iter++){                      
        //undefined reference to `ns3::TrafficClass::Dequeue()'         
        return (**iter).Dequeue();   
    }    
    return 0;     
 }

 
template <typename Packet>
Ptr<const ns3::Packet>
DiffServ<Packet>::DoPeek (void) const
{
   // NS_LOG_FUNCTION (this);  
    auto iter = q_class.begin();
      for(;iter!=q_class.end();iter++){ 
         // std::cout<<*iter<<" ";    
            if((**iter).Peek()!=0){ //NULL check!
                return (**iter).Peek();                   
            }
      }   
    return 0;
}

template <typename Packet>
Ptr<ns3::Packet> 
DiffServ<Packet>::DoRemove (void) 
{
    //NS_LOG_FUNCTION (this);
    auto iter = q_class.begin();
      for(;iter!=q_class.end();iter++){ 
         // std::cout<<*iter<<" ";    
            if((**iter).Peek()!=0){ //NULL check!
                return (**iter).Remove();                    
            }
      }        
    return 0;
}

template <typename Packet>
uint32_t
DiffServ<Packet>::Classify (Ptr<ns3::Packet> p) 
{

    //NS_LOG_FUNCTION (this)

   if(DoEnqueue(p)){
       return 1;
   }else{
       return 0;
   }
}

template <typename Packet>
Ptr<ns3::Packet> 
DiffServ<Packet>::Schedule () 
{
 //   NS_LOG_FUNCTION (this);
    return DoDequeue();
}
extern template class DiffServ<Packet>;
} // namespace ns3

#endif /* DIFFSERV_H */
