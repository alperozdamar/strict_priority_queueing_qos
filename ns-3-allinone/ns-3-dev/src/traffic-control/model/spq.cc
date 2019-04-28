
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

  //return DiffServ<Packet>::DoEnqueue (Queue<Packet>::Tail (), item)
  //return Classify(item);
  //if (tc-> Peek ()!= 0 && Classify(item)== 1)
   //if (Classify(p) != -1)
   // {

      //return 1 in case of not matched!
      u_int32_t index = Classify(p); //return the index of match!!
      
      std::cout<<"Test.SPQ.Enqueue.index.matched: "<<index<<std::endl;
      q_class[index] -> Enqueue (p);
      return true;
   // } 
 // return false;
}

template <typename Packet>
Ptr<Packet>
SPQ<Packet>::Dequeue (void)
{
  NS_LOG_FUNCTION (this);
  printf("Test.SPQ.Dequeue\n");

  return  Schedule();

  //for (int32_t i = 0; i < q_class[i]; i++){

    // // method 1
    //   if  ((q_class[i]-> priority_level == 1  && q_class[i]->IfEmpty() != true)){
    //     queue_index_with_high_priority = i;
    //     p = q_class -> Schedule();
    //   } else if (Schedule()== 0) { 
    //      p = q_class[i] -> Dequeue();
    //   } else {
    //     return 0;
    //   }

    // // method 2

    //   while ((q_class[i]-> priority_level == 1  && q_class[i]->IfEmpty() != true)){
    //     queue_index_with_high_priority = i;
    //     return p = Schedule();
    //   } 
    //   if (q_class[queue_index_with_high_priority] ->IfEmpty == true) {
         
    //      p = q_class[i] -> Dequeue();
    //   } else {
    //     return 0;
    //   
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
       std::cout<<"SPQ.Matched!"<<std::endl;
      return index = i;
    } 
    //NOT MATCHED case, we need to put this packet to default queue.
    else{      
      std::cout<<"SPQ.Not Matched!"<<std::endl;
      std::cout<<"SPQ.q_class[i]->isDefault:"<< q_class[i]->isDefault <<std::endl;
      if (q_class[i]->isDefault){ //low i=1 or 0
        std::cout<<"SPQ.Not Matched! Default Queue's index value is "<< i <<std::endl;
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
  for(uint32_t priority= 0; priority < 100 ; priority++){   
    //std::cout<<"SPQ.q_class.size():"<<  q_class.size()<<std::endl;
    for (uint32_t i=0; i< q_class.size();i++)
    {   
       // std::cout<<"SPQ.priority_level:"<<  priority <<std::endl;
       // std::cout<<"SPQ.q_class[i]->m_queue.size():"<<  q_class[i]->m_queue.size() <<std::endl;
        if  (q_class[i]-> priority_level == priority  && q_class[i]->IfEmpty() != true)//HIGH PRIORITY 
        {          
          std::cout<<"SPQ.priority_level MATCHED!QUEUE is NOT EMPTY!priority:"<<  priority <<std::endl;
          Ptr<Packet> p = q_class[i] -> Dequeue(); // Peek()
          return p;
        }
    }
  }

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