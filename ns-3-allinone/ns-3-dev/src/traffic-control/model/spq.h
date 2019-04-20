/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 Universita' degli Studi di Napoli Federico II
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SPQ_H
#define SPQ_H

#include "ns3/object.h"
#include "diff-serv.h" 

namespace ns3 {

class SPQ: public DiffServ {
public:

  static TypeId GetTypeId (void);

  SPQ ();
  ~SPQ (); 

  int32_t Classify (Ptr<QueueDiscItem> item) const;

private:
    
  int32_t DoClassify (Ptr<QueueDiscItem> item);



};

} // namespace ns3

#endif /* PACKET_FILTER */
