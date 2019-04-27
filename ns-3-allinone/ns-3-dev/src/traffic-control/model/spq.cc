
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
  NS_LOG_FUNCTION (this);
}


template <typename Packet>
SPQ<Packet>::~SPQ ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
bool
SPQ<Packet>::Enqueue (Ptr<Packet> item)
{
  NS_LOG_FUNCTION (this << item);
  //return DiffServ<Packet>::DoEnqueue (Queue<Packet>::Tail (), item)
  //return Classify(item);
 for (TrafficClass * tc : q_class)
  {
   // if (tc-> Peek ()!= 0 && Classify(item)== 1)
   if (Classify(item)== 1)
    {
      tc -> Enqueue (item);
      return true;
    }
  }
  return false;
}

template <typename Packet>
Ptr<Packet>
SPQ<Packet>::Dequeue (void)
{
  NS_LOG_FUNCTION (this);
  //Ptr<Packet> item = DiffServ<Packet>::DoDequeue (Queue<Packet>::Head());

  Ptr<Packet> item = Schedule ();
  NS_LOG_LOGIC("Popped " << item);
  return item;
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
    //for (TrafficClass tc : *q_class)
    //{
      //TODP  Check with Alper 
     TrafficClass tc;
      if (!tc.match(p))
        {
          NS_LOG_LOGIC ("Unable to classify packets of this match!");
          return -1;
        }
      return 1;
    //} 

  //return DiffServ<Packet>::Classify(item);
}

template <typename Packet>
Ptr<Packet> 
SPQ<Packet>::Schedule ()
{
  NS_LOG_FUNCTION (this);

  return DiffServ<Packet>::Schedule();
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