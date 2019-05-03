/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Rozita&Alper
 *  
 *  
 * Diff Serv : A driver for user to drive different queue.
 * Diff Serv has the following public functions for handling
 * packets. 
 * 
 * bool Enqueue (Ptr<Packet> item);
 *
 *  Ptr<Packet> Dequeue ();
 *  Ptr<Packet> Remove ();
 *  Ptr<const Packet> Peek (void) const;
 * 
 * @author: Rozita Teymourzadeh <rteymourzadeh@usfca.edu>
 * @author: Alper Ozdamar <alper.ozdamar@gmail.com>
*/

#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "ns3/diff-serv.h"
#include "ns3/traffic-class.h"
#include <vector>
#include "stdio.h"
#include <iostream>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");
NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ, Packet);

template <typename Packet>
TypeId
DiffServ<Packet>::GetTypeId (void)
{
  static TypeId tid =
      TypeId (("ns3::DiffServ<" + GetTypeParamName<DiffServ<Packet>> () + ">").c_str ())
          .SetParent<Queue<Packet>> ()
          .SetGroupName ("trafficClass")
          .template AddConstructor<DiffServ<Packet>> ();
  return tid;
}

template <typename Packet>
DiffServ<Packet>::DiffServ () : Queue<Packet> (), NS_LOG_TEMPLATE_DEFINE ("DiffServ")
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
DiffServ<Packet>::~DiffServ ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Packet>
void
DiffServ<Packet>::SetMode (QueueMode mode)
{
  NS_LOG_FUNCTION (this << mode);
  this->m_mode = mode;
}

template <typename Packet>
QueueMode
DiffServ<Packet>::GetMode ()
{
  NS_LOG_FUNCTION (this);
  return m_mode;
}

template <typename Packet>
bool
DiffServ<Packet>::DoEnqueue (Ptr<ns3::Packet> p)
{
  NS_LOG_FUNCTION (this << p);

  auto iter = q_class.begin ();
  for (; iter != q_class.end (); iter++)
    {
      // std::cout<<*iter<<" ";
      if ((**iter).match (p))
        {
          return (**iter).Enqueue (p);
        }
      else
        {
        }
    }
  return false;
}


/**
 * To Dequeue the packet 
 **/
template <typename Packet>
Ptr<ns3::Packet>
DiffServ<Packet>::DoDequeue (void)
{
  NS_LOG_FUNCTION (this);
  for (TrafficClass *tc : q_class)
    {
      if (tc->Peek () != 0)
        {
          return tc-> Dequeue ();
        }
    }
  return 0;
}


/**
 * To peek the packet 
 **/
template <typename Packet>
Ptr<const ns3::Packet>
DiffServ<Packet>::DoPeek () const
{
  NS_LOG_FUNCTION (this);
  auto iter = q_class.begin ();
  for (; iter != q_class.end (); iter++)
    {      
      if ((**iter).Peek () != 0)
        { //NULL check!
          return (**iter).Peek ();
        }
    }
  return 0;
}

/**
 * To Remove the packet from queue.
 **/
template <typename Packet>
Ptr<ns3::Packet>
DiffServ<Packet>::DoRemove (void)
{
  NS_LOG_FUNCTION (this);

  for (TrafficClass *tc : q_class)
    {
      if (tc->Peek () != 0)
        {
          return tc->Remove ();
        }
    }
  return 0;
}

/**
 * The classify function utilizes filter aspect to sort the traffic packets into appropriate
 * traffic queues.
 **/
template <typename Packet>
uint32_t
DiffServ<Packet>::Classify (Ptr<ns3::Packet> p)
{
  std::cout<<"Test.DiffServ.Classify!"<<std::endl;
  NS_LOG_FUNCTION (this << p);

  uint32_t match_index = -1;

  return match_index;
}

/**
 * To schedule the packet and return it.
 *  
 **/
template <typename Packet>
Ptr<ns3::Packet>
DiffServ<Packet>::Schedule ()
{
  NS_LOG_FUNCTION (this);  
  std::cout<<"Test.DiffServ.Schedule!"<<std::endl;  
  return  0; 
}



/***
 * To Enqueue the packet
 * */
template <typename Packet>
bool
DiffServ<Packet>::Enqueue (Ptr<Packet> item)
{
  NS_LOG_FUNCTION (this << item);

  return DoEnqueue (Tail (), item);
}

/***
 * To Dequeue the packet
 * */
template <typename Packet>
Ptr<Packet>
DiffServ<Packet>::Dequeue (void)
{
  NS_LOG_FUNCTION (this);

  Ptr<Packet> item = DoDequeue (Head ());

  NS_LOG_LOGIC ("Popped " << item);

  return item;
}

/***
 * To Remove the packet
 * */
template <typename Packet>
Ptr<Packet>
DiffServ<Packet>::Remove (void)
{
  NS_LOG_FUNCTION (this);

  Ptr<Packet> item = DoRemove (Head ());

  NS_LOG_LOGIC ("Removed " << item);

  return item;
}


/***
 * To Peek the packet
 * */
template <typename Packet>
Ptr<const Packet>
DiffServ<Packet>::Peek (void) const
{
  NS_LOG_FUNCTION (this);

  return DoPeek (Head ());
}

} // namespace ns3
