
#ifndef SOURCE_IP_ADDRESS_H
#define SOURCE_IP_ADDRESS_H


#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "FilterElement.h" 
#include "ns3/ipv4-address.h"

namespace ns3 {

/**
 * \ingroup traffic-control
 *
 * PacketFilter is the abstract base class for filters used by queue discs
 * to classify packets.
 */
class SourceIpAddress: public FilterElement {
public:

  static TypeId GetTypeId (void);

  SourceIpAddress ();
  ~SourceIpAddress ();

  /**
   * Standard value used by packet filters to indicate that no match was possible.
   */
  //static const int PF_NO_MATCH = -1;

  bool Match (Ptr<Packet> packet);


private:
  Ipv4Address value;  

};

} // namespace ns3

#endif /* SOURCE_IP_ADDRESS */
