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
static uint32_t queue2priority = 1;

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
  deviceSenderToRouter = P2PSenderToRouter.Install(nodes.Get(0),nodes.Get(1));

  /***
   * 
   * DEFINE SPQ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   *    
   * */
  //SPQ spq = new SPQ(); 
     
  //for(size_t i = 1; i <= numberOfQueue; i++)
  //{       
  // spq.q_class[i]=new TrafficClass();    
  //}  

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
  Ptr <PointToPointNetDevice> PpNdRouterToServer = DynamicCast<PointToPointNetDevice> (deviceRouterToReceiver.Get(2)); 
  PpNdRouterToServer -> SetDequeuQosFlag(true); 
  //PpNdRouterToServer ->SetQueue(spq);

  /* Assign IP to Router2Receiver */
  ipv4Address.SetBase ("10.0.2.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaceRouterToReceiver;
  interfaceRouterToReceiver= ipv4Address.Assign(deviceRouterToReceiver);
  
  
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