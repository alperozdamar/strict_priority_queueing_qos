#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Point to point conection");

int 
main (int argc, char *argv[])
{
 

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}











 

 
