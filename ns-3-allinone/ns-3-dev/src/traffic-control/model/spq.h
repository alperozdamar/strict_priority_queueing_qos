// /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
// /*
//  * Copyright (c) 2016 Universita' degli Studi di Napoli Federico II
//  *
//  * This program is free software; you can redistribute it and/or modify
//  * it under the terms of the GNU General Public License version 2 as
//  * published by the Free Software Foundation;
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU General Public License for more details.
//  *
//  * You should have received a copy of the GNU General Public License
//  * along with this program; if not, write to the Free Software
//  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//  */

// #ifndef SPQ_H
// #define SPQ_H

// #include "ns3/object.h"
// #include "diff-serv.h" 

// namespace ns3 {

// class SPQ: public DiffServ {
// public:

//   static TypeId GetTypeId (void);

//   SPQ ();
//   ~SPQ (); 

//   int32_t Classify (Ptr<QueueDiscItem> item) const;

// private:
    
//   int32_t DoClassify (Ptr<QueueDiscItem> item);



// };

//} // namespace ns3

//#endif /* PACKET_FILTER */


#ifndef SPQ_H
#define SPQ_H

#include "diff-serv.h" 
#include "ns3/queue.h"
#include "ns3/log.h"

namespace ns3 {

template<typename Packet>
class SPQ: public DiffServ<Packet> {

public:

  enum QueueMode
  {
    QUEUE_MODE_PACKETS,
    QUEUE_MODE_BYTES,
  };
    
  //QueueMode mode;
  //std::vector<TrafficClass*>) trafficClassVector;
  
  static TypeId GetTypeId (void);

  SPQ (QueueMode mode, std::vector<TrafficClass*> trafficClassVector); 
  //  this->m_mode = mode;
  //  this->q_class = trafficClassVector;
  

  virtual ~SPQ (); 
  bool Enqueue(Ptr<Packet> item);


//  int32_t Classify (Ptr<QueueDiscItem> item2) const;

private:
    
//  int32_t DoClassify (Ptr<QueueDiscItem> item);

NS_LOG_TEMPLATE_DECLARE;

};


// Class here

    template <typename Packet>
    TypeId  
    SPQ<Packet>::GetTypeId (void)
    {
    static TypeId tid = TypeId (("ns3::SPQ<" + GetTypeParamName<SPQ<Packet> > () + ">").c_str ())
      .SetParent<DiffServ<Packet>()
      .SetGroupName ("trafficClass")
      .template AddConstructor<SPQ<Packet> > () //)//TODO: I may need to remove 2 parameters 
    ;
    return tid;
    }


    template <typename Packet> //TODO May need parameter here 
    SPQ<Packet> :: SPQ (QueueMode mode, std::vector<TrafficClass*> trafficClassVector):
    NS_LOG_TEMPLATE_DEFINE("SPQ")   
    {
        this -> m_mode = mode;
        this -> q_class = trafficClassVector;
        NS_LOG_FUNCTION (this);
    }


    template <typename Packet>
    bool
    SPQ<Packet> :: Enqueue(Ptr<Packet> item){
        NS_LOG_FUNCTION (this << item);
        return DoEnqueue(Tail(), item)
    }
   


    template<typename Packet>
    SPQ<Packet>::~SPQ()
    {
        // NS_LOG_FUNCTION (this); 
    }
    extern template class SPQ<Packet>;
} // namespace ns3

#endif /* SPQ_H */
