#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/spq.h"
#include <vector>
#include "ns3/netanim-module.h"
#include "ns3/config-store-module.h"


//#include "libxml/tree.h"
#include <libxml/tree.h>
#include <libxml/parser.h> 
#include "ns3/source-ip-address.h"
#include "ns3/source-mask.h"
#include "ns3/source-port-number.h"
#include "ns3/destination-ip-address.h"
//#include "ns3/destination-mask.h"
#include "ns3/destination-port-number.h"
#include "ns3/protocol-number.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

static Filter* 
create_filter(xmlNode * node){
  Filter* result = new Filter();

  xmlNode *cur_node = nullptr;

  for(cur_node=node->children; cur_node; cur_node=cur_node->next){
    if(cur_node->type==XML_ELEMENT_NODE){     
      if(strcmp((char*)cur_node->name,"source_address")==0){
        Ipv4Address address((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
        result->elements.push_back(new SourceIpAddress(address));
      }   
     // if(strcmp((char*)cur_node->name,"source_mask")==0){
     //   Ipv4Mask mask((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
     //   result->elements.push_back(new SourceMask(mask));
     // }
      if(strcmp((char*)cur_node->name,"source_port")==0){
        uint32_t port = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
        result->elements.push_back(new SourcePortNumber(port));
      }      
      if(strcmp((char*)cur_node->name,"destination_address")==0){
        Ipv4Address address((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
        result->elements.push_back(new DestinationIpAddress(address));
      }   
     // if(strcmp((char*)cur_node->name,"destination_mask")==0){
     //   Ipv4Mask mask((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
     //   result->elements.push_back(new DestinationMask(mask));
     // }
      if(strcmp((char*)cur_node->name,"destination_port")==0){
        uint32_t port = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
        result->elements.push_back(new DestinationPortNumber(port));
      }
      if(strcmp((char*)cur_node->name,"protocol")==0){
        uint32_t protocol = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
        result->elements.push_back(new ProtocolNumber(protocol));  
      }
    }
  }
  return result;
}

static TrafficClass* 
create_from_xml(xmlNode * node){
  xmlNode *cur_node = nullptr;
  uint32_t max_packets = 0;
  uint32_t max_bytes = 0;
  double_t weight = 0;
  uint32_t priority_level = 0;
  bool is_default = false;

  std::vector<Filter*> filters;

  for(cur_node=node; cur_node; cur_node=cur_node->next){
    if(cur_node->type==XML_ELEMENT_NODE){
      if(strcmp((char*)cur_node->name,"maxPackets")==0){
        max_packets = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
      }
      if(strcmp((char*)cur_node->name,"maxBytes")==0){
        max_bytes = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
      }
      if(strcmp((char*)cur_node->name,"weight")==0){
        weight = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
      }
      if(strcmp((char*)cur_node->name,"priority_level")==0){
        priority_level = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
      }
      if(strcmp((char*)cur_node->name,"isDefault")==0){
        is_default = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
      }
      if(strcmp((char*)cur_node->name,"filters")==0){
        xmlNode *cur_filter = nullptr;
        for(cur_filter=cur_node->children; cur_filter; cur_filter=cur_filter->next){
          Filter* filter = create_filter(cur_filter);
          
         //test.LOG... 
         for(uint32_t i=0;i<filter->elements.size();i++){
          std::cout<<"filter element[i]: "<<filter->elements[i]<<std::endl;
         }

          if(filter->elements.size()!=0){            
            std::cout<<"filter elements: "<<filter->elements.size()<<std::endl;
            filters.push_back(filter);
          }
        }
      }
    }
  }
  TrafficClass* tc = new TrafficClass(max_packets,max_bytes, weight, priority_level, is_default, filters);
  return tc;
}

static void
get_traffic_class(xmlNode * node, int level, std::vector<TrafficClass*> & result){
  xmlNode *cur_node = nullptr;
  for(cur_node=node; cur_node; cur_node=cur_node->next){//Loop through traffic
    if(cur_node->type==XML_ELEMENT_NODE){
      printf("HELLO\n");
      result.push_back(create_from_xml(cur_node->children));            
    }
  }
}

static void
readConfigurationFile(const std::string filename, std::vector<TrafficClass*> & result){
  char char_array[filename.length()+1];
  strcpy(char_array, filename.c_str());

  xmlDocPtr doc;
  doc = xmlReadFile(char_array,nullptr,0);
  if(doc==nullptr){
    fprintf(stderr, "Failed to parse %s\n", char_array);
    return;
  }

  xmlNode *root_ele = nullptr;
  root_ele = xmlDocGetRootElement(doc);

  get_traffic_class(root_ele->children,1, result);

  xmlFreeDoc(doc);

  xmlCleanupParser();
}

int
main (int argc, char *argv[])
{
  std::string file_name = "";
  //
  // Allow the user to override any of the defaults and the above Bind () at
  // run-time, viacommand-line arguments
  //
  CommandLine cmd;
  cmd.AddValue("filename","Name of the configuration file", file_name);
  cmd.Parse (argc, argv);


  NodeContainer nodes;
  nodes.Create (3);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
  NetDeviceContainer n_01 = p2p.Install (nodes.Get(0),nodes.Get(1));
  std::vector<TrafficClass*> tcs;
  readConfigurationFile(file_name, tcs);

  std::cout<< "tcs.size: " << tcs.size() <<std::endl;  
  

  p2p.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
  //p2p.SetDeviceAttribute ("DataRate", StringValue ("600bps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer n_12 = p2p.Install (nodes.Get(1),nodes.Get(2));

  Ptr<PointToPointNetDevice> router_send = DynamicCast<PointToPointNetDevice>(n_12.Get(0));

  //Ptr<CustomSPQ<Packet>> custom = new CustomSPQ<Packet>(QueueMode::Packets, tcs);
  //Ptr<SPQ<Packet>> custom = new SPQ<Packet>(QueueMode::Packets, tcs);
    
  Ptr<SPQ<Packet>> queue2 = new SPQ<Packet>(QueueMode::QUEUE_MODE_PACKETS,tcs);  
  router_send->SetQueue(queue2);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces1 = address.Assign (n_01);
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces2 = address.Assign (n_12);
  

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  UdpServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (2));
  serverApps.Start (Seconds (0.0));
  serverApps.Stop (Seconds (10000.0));

  UdpServerHelper echoServer2 (10);

  ApplicationContainer serverApps2 = echoServer2.Install (nodes.Get (2));
  serverApps2.Start (Seconds (0.0));
  serverApps2.Stop (Seconds (10000.0));

  UdpClientHelper echoClient (interfaces2.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1000));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (0.0));
  clientApps.Stop (Seconds (1000.0));

  UdpClientHelper echoClient2 (interfaces2.GetAddress (1), 10);
  echoClient2.SetAttribute ("MaxPackets", UintegerValue (1000));
  echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient2.SetAttribute ("PacketSize", UintegerValue (1000));

  ApplicationContainer clientApps2 = echoClient2.Install (nodes.Get (0));
  clientApps2.Start (Seconds (0.0));
  clientApps2.Stop (Seconds (1000.0));

  AnimationInterface anim ("spq_anim.xml");
	anim.SetConstantPosition (nodes.Get(0), 0, 0);
  anim.SetConstantPosition (nodes.Get(1), 10, 10);
  anim.SetConstantPosition (nodes.Get(2), 20, 20);

  p2p.EnablePcapAll("spq");

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
