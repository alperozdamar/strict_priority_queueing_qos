/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Rozita&Alper
 *  
 *  
 * Filter: To Filter different packets
 *
 * 
 * @author: Rozita Teymourzadeh <rteymourzadeh@usfca.edu>
 * @author: Alper Ozdamar <alper.ozdamar@gmail.com>
*/
#ifndef DESTINATION_PORT_NUMBER_H
#define DESTINATION_PORT_NUMBER_H

#include "ns3/filter-element.h"
#include "ns3/log.h"



namespace ns3 {


    class DestinationPortNumber: public FilterElement {
    public:
        
        static TypeId GetTypeId (void);

        DestinationPortNumber (uint32_t);
        ~DestinationPortNumber ();


        bool match(Ptr<ns3::Packet> packet);


    private:

        uint32_t value;

    };
} // namespace ns3
#endif /*DESTINATION_PORT_NUMBER_H */
