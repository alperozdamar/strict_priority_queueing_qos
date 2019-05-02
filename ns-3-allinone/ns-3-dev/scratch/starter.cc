#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include <iostream>
#include <fstream>
#include <iomanip> 
#include <chrono> 
#include "ns3/udp-client.h"
#include "ns3/source-ip-address.h" 
#include "ns3/destination-port-number.h"
#include "ns3/source-port-number.h"  
#include "ns3/spq.h" 


using namespace ns3;
using namespace std::chrono;

NS_LOG_COMPONENT_DEFINE("Point to point connection"); 

static std::string CONFIG_FILE = "config.txt";
static uint32_t MTU_SIZE = 2000;
static uint32_t PACKET_SIZE = 1100; //This is for 0. Low enthropy. 
static Time interPacketInterval = Seconds(0.01);  
using namespace std::chrono;
uint16_t serverPort = 9; 
static int numberOfQueue=0;
static uint32_t dataRate = 1;
static uint32_t queue1priority = 1;
static uint32_t queue2priority = 3;

/**
 * 
 * Reading Configuration File......
 * 
 * */
bool readConfigurationFile(){  
  std::ifstream cFile (CONFIG_FILE);
      if (cFile.is_open())
      {
          std::string line;
          while(getline(cFile, line)){
              line.erase(std::remove_if(line.begin(), line.end(), isspace),
                                  line.end());
              if(line[0] == '#' || line.empty())
                  continue;
              auto delimiterPos = line.find("=");
              std::string name = line.substr(0, delimiterPos);
              std::string value = line.substr(delimiterPos + 1);            
              std::cout << name << " " << value << '\n';

              if(name.compare("numberOfQueue")==0 ){
                int intValue = atoi(value.c_str());
                numberOfQueue=intValue;                              
              }else if(name.compare("dataRate")==0 ){
                int intValue = atoi(value.c_str());
                dataRate=intValue;                              
              }else if(name.compare("queue1priority")==0 ){
                int intValue = atoi(value.c_str());
                queue1priority=intValue;                              
              }else if(name.compare("queue2priority")==0 ){
                int intValue = atoi(value.c_str());
                queue2priority=intValue;                              
              }
              else{
                NS_LOG_UNCOND("numberOfQueue is not equal to "<< name);
              }
          }        
      }
      else {
          std::cerr << "Couldn't open config file for reading.\n";
          return false;
      }

      return true;
}

int main (int argc, char *argv[])
{
  /* Read command line argument  */    
  uint32_t MAX_PACKET_COUNT=1;
  CommandLine cmd;
  cmd.AddValue("CompressionDataRate", "CompressionDataRate [Mbps]", dataRate);    
  cmd.AddValue("configFileName", "configFileName", CONFIG_FILE);    
  cmd.AddValue("MaxPacketCount", "MaxPacketCount", MAX_PACKET_COUNT); 
  cmd.Parse (argc, argv);
  NS_LOG_UNCOND("**********Command Line Configuration Parameters**************");  
  NS_LOG_UNCOND("*************************************************************");    

  /* READ CONFIGURATION FILE */
  bool configResult = readConfigurationFile();      

  if(configResult){
    NS_LOG_UNCOND("************Configuration File read, successfully************");  
    NS_LOG_UNCOND("numberOfQueue:"<<numberOfQueue);
    NS_LOG_UNCOND("dataRate:"<<dataRate);
    NS_LOG_UNCOND("queue1priority:"<<queue1priority);
    NS_LOG_UNCOND("queue2priority:"<<queue2priority);
  }else{
    NS_LOG_UNCOND("PROBLEM IN CONFIGURATION FILE!!!");
  }

  NodeContainer nodes;
  nodes.Create(3);    
  
  InternetStackHelper stack;
  stack.Install(nodes);  
  std::string dataRateString = std::to_string(dataRate);


/********************************SENDER TO ROUTER**************************************/

  /* Link btw Sender Router */
  PointToPointHelper P2PSenderToRouter;
  P2PSenderToRouter.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  P2PSenderToRouter.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (1)));
  P2PSenderToRouter.SetDeviceAttribute ("Mtu", UintegerValue (MTU_SIZE));   
  
    /* Connect node Sender & Router */
  NetDeviceContainer deviceSenderToRouter; 
  deviceSenderToRouter = P2PSenderToRouter.Install(nodes.Get(0),nodes.Get(1)); //TODO


  Ptr <PointToPointNetDevice> PpNdSenderToRouter = DynamicCast<PointToPointNetDevice> (deviceSenderToRouter.Get(1));
  PpNdSenderToRouter -> SetEnqueueQosFlag(true);  
 // PpNdSenderToRouter ->SetQueue(spq);
  //PpNdSenderToRouter -> SetQueue(spq.q_class[0]);
  



  Ipv4AddressHelper ipv4Address;
  /* Assign IP to SenderRouter */  
  ipv4Address.SetBase ("10.0.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaceSenderRouter1;
  interfaceSenderRouter1 = ipv4Address.Assign (deviceSenderToRouter);
/*******************************SENDER TO ROUTER (END)************************************/

/********************************ROUTER TO RECEIVER**************************************/

  /* Link btw Router Receiver */
  PointToPointHelper P2PRouterToReceiver;
  P2PRouterToReceiver.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  P2PRouterToReceiver.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (1)));
  P2PRouterToReceiver.SetDeviceAttribute ("Mtu", UintegerValue (MTU_SIZE));
           
  /* Connect node Router & Receiver */  
  NetDeviceContainer deviceRouterToReceiver; 
  deviceRouterToReceiver = P2PRouterToReceiver.Install(nodes.Get(1),nodes.Get(2));  
 
  //TODO:....Check!
  //Ptr <PointToPointNetDevice> PpNdRouterToServer = DynamicCast<PointToPointNetDevice> (deviceRouterToReceiver.Get(2)); 
  //PpNdRouterToServer -> SetDequeuQosFlag(true); 

  std::vector<TrafficClass*> vectorList;  
  Ptr<SPQ<Packet>> queue2 = new SPQ<Packet>(QueueMode::QUEUE_MODE_BYTES,vectorList);

  //PpNdRouterToServer -> SetQueue(spqInstance);

  /* Assign IP to Router2Receiver */
  ipv4Address.SetBase ("10.0.2.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaceRouterToReceiver;
  interfaceRouterToReceiver= ipv4Address.Assign(deviceRouterToReceiver);
  

  //Ptr<SPQ<Packet>> queue2= CreateObject<SPQ<Packet>>();  
  Ptr <PointToPointNetDevice> PpNdRouterToServer = DynamicCast<PointToPointNetDevice> (deviceRouterToReceiver.Get(2));         
 


  //uint32_t Q1maxPacket = 1000;
  //uint32_t Q2maxPacket = 500;

  //uint32_t Q1maxBytes = 1000;
  //uint32_t Q2maxBytes = 500; 

 // double_t Q1weight = 0;
 // double_t Q2weight = 0;

  //uint32_t Q1priority_level = 1;
  //uint32_t Q2priority_level = 3;

  //bool Q1isDefault = false;
  //bool Q2isDefault = true;

  std::vector<Filter*> filters;

  std::string filterSourceIpAddress="10.0.1.0";
  std::string filterDestinationIpAddress="10.0.2.0";
  uint32_t filterSourcePort=5060;
  uint32_t filterDestinationPort=6060;


  SourceIpAddress sourceIpAddressQ1 = SourceIpAddress(Ipv4Address("10.0.1.0"));
  SourceIpAddress sourceIpAddressQ2 = SourceIpAddress(Ipv4Address("10.0.8.8"));
  SourceIpAddress destinationIpAddressQ1 = SourceIpAddress(Ipv4Address("10.0.2.0"));
  SourceIpAddress destinationIpAddressQ2 = SourceIpAddress(Ipv4Address("10.0.9.9"));
  SourcePortNumber sourcePortNumberQ1 = SourcePortNumber(filterSourcePort);
  SourcePortNumber sourcePortNumberQ2= SourcePortNumber(filterSourcePort);
  DestinationPortNumber destinationPortNumberQ1= DestinationPortNumber(filterDestinationPort);
  DestinationPortNumber destinationPortNumberQ2= DestinationPortNumber(filterDestinationPort);

  static Filter filterForQ1;
  filterForQ1.elements.push_back(&sourceIpAddressQ1);
  filterForQ1.elements.push_back(&sourcePortNumberQ2);
  filterForQ1.elements.push_back(&destinationIpAddressQ1);
  filterForQ1.elements.push_back(&destinationPortNumberQ2);

  filters.push_back(&filterForQ1);

  static Filter filterForQ2;
  filterForQ2.elements.push_back(&sourceIpAddressQ1);
  filterForQ2.elements.push_back(&sourcePortNumberQ2);
  filterForQ2.elements.push_back(&destinationIpAddressQ1);
  filterForQ2.elements.push_back(&destinationPortNumberQ2);

 // filters.push_back(&filterForQ2);
  //We need to pass these queues to vectorList of the SPQ!  

  
  
  //TrafficClass *Q1 = new TrafficClass(Q1maxPacket,Q1maxBytes,Q1weight,Q1priority_level,Q1isDefault, filters); 
  //TrafficClass *Q2 = new TrafficClass(Q1maxPacket,Q1maxBytes,Q1weight,Q1priority_level,Q1isDefault, filters);    

  //queue2->AddTrafficClass(Q1);
  //queue2->AddTrafficClass(Q2);  

  PpNdRouterToServer->SetQueue(queue2); //This is correct.confirmed!

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  Address serverAddress;
  serverAddress = Address(interfaceRouterToReceiver.GetAddress(1));

  /* Create Server */  
  UdpServerHelper server (serverPort);
  ApplicationContainer serverApps = server.Install (nodes.Get(2));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (60.0));       

  UdpClientHelper clientHigh (serverAddress, serverPort);
  clientHigh.SetAttribute ("Interval", TimeValue (interPacketInterval));   
  clientHigh.SetAttribute ("MaxPackets", UintegerValue (MAX_PACKET_COUNT)); 
  clientHigh.SetAttribute ("PacketSize", UintegerValue (PACKET_SIZE));   
  ApplicationContainer clientAppsHigh = clientHigh.Install (nodes.Get(0));
  Ptr<UdpClient> UdpClientHigh = DynamicCast<UdpClient>(clientAppsHigh.Get(0));
  
     

 
  //Start client
  clientAppsHigh.Start(Seconds (20.0));
  clientAppsHigh.Stop(Seconds (40.0));   
 
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  #if 1
  AsciiTraceHelper ascii;  

  P2PRouterToReceiver.EnableAsciiAll(ascii.CreateFileStream("Sender.tr"));
  P2PRouterToReceiver.EnablePcap("Sender", deviceSenderToRouter.Get(0),false, false);

  P2PRouterToReceiver.EnableAsciiAll(ascii.CreateFileStream("Receiver.tr"));
  P2PRouterToReceiver.EnablePcap("Receiver", deviceRouterToReceiver.Get(1),false, false);

  #elif 0
  P2PSenderToRouter.EnablePcapAll ("P2PSenderToRouter");  
  P2PRouterToReceiver.EnablePcapAll ("P2PRouterToReceiver");
  #endif 

  AnimationInterface anim("p2p.xml");
  anim.SetConstantPosition(nodes.Get(0), 0.0, 0.0);
  anim.SetConstantPosition(nodes.Get(1), 10.0, 10.0);
  anim.SetConstantPosition(nodes.Get(2), 20.0, 20.0);  

  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}