/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Rozita&Alper
 *  
 *  
 * Starter: Topology for Project-2
 *
 * 
 * @author: Rozita Teymourzadeh <rteymourzadeh@usfca.edu>
 * @author: Alper Ozdamar <alper.ozdamar@gmail.com>
*/


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
#include <libxml/tree.h>
#include <libxml/parser.h> 
#include "ns3/source-ip-address.h"
#include "ns3/source-mask.h"
#include "ns3/source-port-number.h"
#include "ns3/destination-ip-address.h"
#include "ns3/destination-mask.h"
#include "ns3/destination-port-number.h"
#include "ns3/protocol-number.h" 

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Quality of Service");

static Filter* 
createFilter(xmlNode * node){
  Filter* filterWithElement = new Filter();

  xmlNode *point = nullptr;

  for(point=node->children; point; point=point->next){
    if(point->type==XML_ELEMENT_NODE){     
      if(strcmp((char*)point->name,"source_address")==0){
        Ipv4Address address((char*)xmlGetProp(point,(xmlChar *)"value"));
        filterWithElement->elements.push_back(new SourceIpAddress(address));
      }   
      if(strcmp((char*)point->name,"source_mask")==0){
        Ipv4Mask mask((char*)xmlGetProp(point,(xmlChar *)"value"));
        filterWithElement->elements.push_back(new SourceMask(mask));
      }
      if(strcmp((char*)point->name,"source_port")==0){
        uint32_t port = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
        filterWithElement->elements.push_back(new SourcePortNumber(port));
      }      
      if(strcmp((char*)point->name,"destination_address")==0){
        Ipv4Address address((char*)xmlGetProp(point,(xmlChar *)"value"));
        filterWithElement->elements.push_back(new DestinationIpAddress(address));
      }   
      if(strcmp((char*)point->name,"destination_mask")==0){
        Ipv4Mask mask((char*)xmlGetProp(point,(xmlChar *)"value"));
        filterWithElement->elements.push_back(new DestinationMask(mask));
      }
      if(strcmp((char*)point->name,"destination_port")==0){
        uint32_t port = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
        filterWithElement->elements.push_back(new DestinationPortNumber(port));
      }
      if(strcmp((char*)point->name,"protocol")==0){
        uint32_t protocol = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
        filterWithElement->elements.push_back(new ProtocolNumber(protocol));  
      }
    }
  }
  return filterWithElement;
}

static TrafficClass* 
generateFromXml(xmlNode * node){
  xmlNode *point = nullptr;
  uint32_t maxPackets = 0;
  uint32_t maxBytes = 0;
  double_t weight = 0;
  uint32_t priorityLevel = 0;
  bool isDefault = false;

  std::vector<Filter*> filters;

  for(point=node; point; point=point->next){
    if(point->type==XML_ELEMENT_NODE){
      if(strcmp((char*)point->name,"maxPackets")==0){
        maxPackets = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
      }
      if(strcmp((char*)point->name,"maxBytes")==0){
        maxBytes = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
      }
      if(strcmp((char*)point->name,"weight")==0){
        weight = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
      }
      if(strcmp((char*)point->name,"priority_level")==0){
        priorityLevel = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
      }
      if(strcmp((char*)point->name,"isDefault")==0){
        isDefault = atoi((char*)xmlGetProp(point,(xmlChar *)"value"));
      }
      if(strcmp((char*)point->name,"filters")==0){
        xmlNode *currentFilter = nullptr;
        for(currentFilter=point->children; currentFilter; currentFilter=currentFilter->next){
          Filter* filter = createFilter(currentFilter);
          if(filter->elements.size()!=0){            
            std::cout<<"filter elements: "<<filter->elements.size()<<std::endl;
            filters.push_back(filter);
          }
        }
      }
    }
  }
  TrafficClass* tc = new TrafficClass(maxPackets,maxBytes, weight, priorityLevel, isDefault, filters);
  return tc;
}

static void
getTrafficClass(xmlNode * node, int level, std::vector<TrafficClass*> & result){
  xmlNode *point = nullptr;
  for(point=node; point; point=point->next){
    if(point->type==XML_ELEMENT_NODE){
      result.push_back(generateFromXml(point->children));            
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

  xmlNode *rootElement = nullptr;
  rootElement = xmlDocGetRootElement(doc);

  getTrafficClass(rootElement->children,1, result);

  xmlFreeDoc(doc);

  xmlCleanupParser();
}

int
main (int argc, char *argv[])
{
  std::string fileName = "";
  CommandLine cmd;
  cmd.AddValue("filename","Name of the configuration file", fileName);
  cmd.Parse (argc, argv);


  NodeContainer nodes;
  nodes.Create (3);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("4Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
  NetDeviceContainer n_01 = p2p.Install (nodes.Get(0),nodes.Get(1));
  std::vector<TrafficClass*> tcs;
  readConfigurationFile(fileName, tcs);
 // std::cout<< "tcs.size: " << tcs.size() <<std::endl;  
  

 // p2p.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
  p2p.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer n_12 = p2p.Install (nodes.Get(1),nodes.Get(2));

  Ptr<PointToPointNetDevice> router_send = DynamicCast<PointToPointNetDevice>(n_12.Get(0));
    
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
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10000.0));

  UdpServerHelper echoServer2 (10);
  ApplicationContainer serverApps2 = echoServer2.Install (nodes.Get (2));
  serverApps2.Start (Seconds (1.0));
  serverApps2.Stop (Seconds (10000.0));


  //1st sender wıll have source port 49153
  //2nd sender wıll have source port 49154
  UdpClientHelper echoClient (interfaces2.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1000));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.001)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer client1 = echoClient.Install (nodes.Get (0));
  client1.Start (Seconds (3.000));
  client1.Stop (Seconds (10000.0));

  UdpClientHelper echoClient2 (interfaces2.GetAddress (1), 10);
  echoClient2.SetAttribute ("MaxPackets", UintegerValue (1000));
  echoClient2.SetAttribute ("Interval", TimeValue (Seconds (0.001)));
  echoClient2.SetAttribute ("PacketSize", UintegerValue (1000));

  ApplicationContainer client2 = echoClient2.Install (nodes.Get (0));
  client2.Start (Seconds (3.101)); //5.101
  client2.Stop (Seconds (10000.0));

  AnimationInterface anim ("spq_topology.xml");
	anim.SetConstantPosition (nodes.Get(0), 0, 0);
  anim.SetConstantPosition (nodes.Get(1), 10, 10);
  anim.SetConstantPosition (nodes.Get(2), 20, 20);

  p2p.EnablePcapAll("spq");

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}