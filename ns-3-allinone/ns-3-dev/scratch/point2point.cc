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
  //CommandLine cmd;
  //cmd.Parse (args, argh);

  Time::SetResolution (Time::NS);
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

  // Create Node
  NodeContainer nodes;
  nodes.Create(2);

  // Create link between nodes and set attribute
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

  // connect nodes using DeviceContainer
  NetDeviceContainer devices;
  devices = pointToPoint.Install(nodes);


  InternetStackHelper stack;
  stack.Install(nodes);

  // assign IP to nodes and generate interface from node and IP
  Ipv4AddressHelper address;
  address.SetBase("10.1.1.0", "225.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  // set server
  UdpEchoServerHelper echoServer(9);

  // create application on top of server
  ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
  serverApps.Start(Seconds(1.0));
  serverApps.Stop(Seconds(10.0));

  // create interface btw client and server, set attribute
  UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
  echoClient.SetAttribute("MaxPackets", UintegerValue(1));
  echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
  echoClient.SetAttribute("PacketSize", UintegerValue(1024));

  // create application on top of client
  ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
  clientApps.Start(Seconds(2.0));
  clientApps.Stop(Seconds(10.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}











 

 
