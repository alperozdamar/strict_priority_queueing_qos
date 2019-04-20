#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
//#include "diff-serv.h"
#include "spq.h"


namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("SPQ");


    NS_OBJECT_ENSURE_REGISTERED (SPQ);

    TypeId 
    SPQ::GetTypeId (void)
    {
    static TypeId tid = TypeId ("ns3::SPQ")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl")
    ;
    return tid;
    }

//TrafficClass p1 = new TrafficClass();
//TrafficClass p2 = new TrafficClass();

    SPQ::SPQ ()
    {
    // NS_LOG_FUNCTION (this);
    }

    SPQ::~SPQ()
    {
   // NS_LOG_FUNCTION (this); 
    }

    // int32_t
    // SPQ::Classify (Ptr<QueueDiscItem> item) 
    // {        
    //  return DoClassify (item);
    // }
} // namespace ns3
  
