#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "DiffServ.h"
#include "TrafficClass.h"
#include <vector>
#include "stdio.h"
#include <iostream>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_ENSURE_REGISTERED (DiffServ);

DiffServ::DiffServ () :
    Queue ()    
{
    //NS_LOG_FUNCTION (this);
}

DiffServ::~DiffServ ()
{
   // NS_LOG_FUNCTION (this);
}

void
DiffServ::SetMode (DiffServ::QueueMode mode)
{
    //NS_LOG_FUNCTION (this << mode);
    m_mode = mode;
}
 
DiffServ::QueueMode
DiffServ::GetMode (void) const
{
    //NS_LOG_FUNCTION (this);
    return m_mode;
}


//We should call TRaffic Class's Enqueu???
bool 
DiffServ::DoEnqueue (Ptr<ns3::Packet> p)
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

Ptr<ns3::Packet>
DiffServ::DoDequeue (void)
{
    //NS_LOG_FUNCTION (this);
    auto iter = q_class.begin();
    for(;iter!=q_class.end();iter++){                      
        //undefined reference to `ns3::TrafficClass::Dequeue()'         
        return (**iter).Dequeue();   
    }    
    return 0;     
 }

Ptr<const ns3::Packet>
DiffServ::DoPeek (void) const
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

Ptr<ns3::Packet> DiffServ::DoRemove (void) 
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


uint32_t
DiffServ::Classify (Ptr<ns3::Packet> p) 
{

    //NS_LOG_FUNCTION (this)

   if(DoEnqueue(p)){
       return 1;
   }else{
       return 0;
   }
}

Ptr<ns3::Packet> 
DiffServ::Schedule () 
{
 //   NS_LOG_FUNCTION (this);
    return DoDequeue();
}
} // namespace ns3
  
