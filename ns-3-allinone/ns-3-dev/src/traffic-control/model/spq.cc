
#include "ns3/log.h"
#include "ns3/spq.h"


namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("SPQ");
NS_OBJECT_TEMPLATE_CLASS_DEFINE (SPQ, Packet);

template <typename Packet>
TypeId
SPQ<Packet>::GetTypeId (void)
{
  static TypeId tid = TypeId (("ns3::SPQ<" + GetTypeParamName<SPQ<Packet>> () + ">").c_str ())
    .SetParent <DiffServ<Packet>> ()
    .SetGroupName ("trafficControl")
    .template AddConstructor<SPQ<Packet>> () //)//TODO: I may need to add 2 parameters
;
  return tid;
}

template <typename Packet>
SPQ<Packet>::SPQ ():
DiffServ<Packet>(),
NS_LOG_TEMPLATE_DEFINE("SPQ")
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet> 
SPQ<Packet>::SPQ (QueueMode mode, std::vector<TrafficClass *> trafficClassList)
    : NS_LOG_TEMPLATE_DEFINE ("SPQ")
{
  this-> m_mode = mode;
  this-> q_class = trafficClassList;

  std::cout<< "SPQ.q_class.size: " << q_class.size() <<std::endl;

  NS_LOG_FUNCTION (this);
}


template <typename Packet>
SPQ<Packet>::~SPQ ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
bool
SPQ<Packet>::Enqueue (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  
  printf("Test.SPQ.Enqueue\n");
  //return 1 in case of not matched!
  u_int32_t index = Classify(p); //return the index of match!!
      
  std::cout<<"Test.SPQ.Enqueue.index.matched: "<<index << ",priority:" <<q_class[index]->priority_level  <<std::endl;
  q_class[index] -> Enqueue (p);
  return true;
}

template <typename Packet>
Ptr<Packet>
SPQ<Packet>::Dequeue (void)
{
  NS_LOG_FUNCTION (this);
  printf("Test.SPQ.Dequeue\n");
  Ptr<Packet> p; 

  if(!(q_class[0]->IfEmpty())){
    p = Schedule();
    q_class[0]->Dequeue();   
  }else{
    if(q_class[0]->IfEmpty()){
      q_class[1]->Dequeue();
      //DiffServ<Packet>::Dequeue();
    }

  }


  DiffServ<Packet>::Dequeue();

  return  p;
}

template <typename Packet>
Ptr<Packet>
SPQ<Packet>::Remove (void)
{
  NS_LOG_FUNCTION (this);
  Ptr<Packet> item = DiffServ<Packet>::Remove();
  NS_LOG_LOGIC("Removed " << item);
  return item;
}

template <typename Packet>
Ptr<const Packet>
SPQ<Packet>::Peek (void) const
{
  NS_LOG_FUNCTION (this);

  return DiffServ<Packet>::Peek();
}

template <typename Packet>
uint32_t
SPQ<Packet>::Classify (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this << p);
  std::cout<<"Test.SPQ.Classify!"<<std::endl;
  
  uint32_t index = -1;

  std::cout<<"SPQ.q_class.size():"<< q_class.size() <<std::endl;

  // We iterate here, 2 times. Because we have 2 Traffic Classes!
  for (uint32_t i=0; i< q_class.size();i++)
  {
    if ((q_class[i]-> match (p)))
    {
      std::cout<<"SPQ.Matched!, for priority:"<< q_class[i]->priority_level <<std::endl;
      return index = i;
    } 
    //NOT MATCHED case, we need to put this packet to default queue.
    else{      
      //std::cout<<"SPQ.Not Matched!"<<std::endl;
      //std::cout<<"SPQ.q_class[i]->isDefault:"<< q_class[i]->isDefault <<std::endl;
      if (q_class[i]->isDefault){ //low i=1 or 0
        std::cout<<"SPQ.Not Matched! Putting to Default Queue. Index value is "<< i << ", for priority:"<< q_class[i]->priority_level <<std::endl;
        index = i ; // Check
      }
    }
  }
  return index;

  //return DiffServ<Packet>::Classify(p);
}

template <typename Packet>
Ptr<Packet> 
SPQ<Packet>::Schedule ()
{
  NS_LOG_FUNCTION (this);   
  std::cout<<"Test.SPQ.Schedule!"<<std::endl;
  Ptr<Packet> p;
  // for(uint32_t priority= 0; priority < 100 ; priority++){   
  //   //std::cout<<"SPQ.q_class.size():"<<  q_class.size()<<std::endl;
  //   for (uint32_t i=0; i< q_class.size();i++)
  //   {   
  //      // std::cout<<"SPQ.priority_level:"<<  priority <<std::endl;
  //      // std::cout<<"SPQ.q_class[i]->m_queue.size():"<<  q_class[i]->m_queue.size() <<std::endl;
  //       if  (q_class[i]-> priority_level == priority  && q_class[i]->IfEmpty() != true)//HIGH PRIORITY 
  //       {          
  //         std::cout<<"SPQ.priority_level is SAME!QUEUE is NOT EMPTY!priority:"<<  priority <<std::endl;          
  //         //Peek()==> Killing our system.          
  //         Ptr<Packet> p = q_class[i] -> Peek(); // Dequeue()          
  //         q_class[i] -> Dequeue();
  //         return p; 
  //       }
  //   }
  // }

   

        if  (q_class[0]-> priority_level == 77  && q_class[0]->IfEmpty() != true)//HIGH PRIORITY 
        { 
            //std::cout<<"SPQ.priority_level is SAME!QUEUE is NOT EMPTY!priority:"<<  priority <<std::endl;          
            //Peek()==> Killing our system.          
              Ptr<Packet> p = q_class[0] -> Dequeue(); // Dequeue()          
              //q_class[0] -> Dequeue();
            return p; 
        }
        // else {
        //    Ptr<Packet> p = q_class[1]->Dequeue();
        //    return p;
        // }

    std::cout<< "PROBLEM!! Should not be here!" <<std::endl;

  return 0;
}


template <typename Packet>
//std::vector<TrafficClass*>
bool
SPQ<Packet>::AddTrafficClass (TrafficClass* trafficClass)
{
  //std::vector<Filter*> filterList;
  //TrafficClass* trafficClass = new TrafficClass(5, 0, true,filterList); //TODO Check for this input
  std::vector<TrafficClass*>  trafficClassList;
  trafficClassList.push_back(trafficClass);
  this -> q_class = trafficClassList;
  NS_LOG_FUNCTION (this);
  return true;
}












} // namespace ns3