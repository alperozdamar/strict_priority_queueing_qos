#ifndef SOURCE_IP_ADDRESS_H
#define SOURCE_IP_ADDRESS_H

#include "ns3/object.h"
#include "ipv4-address.h"

namespace ns3 {

class QueueDiscItem;

/**
 * \ingroup traffic-control
 *
 * PacketFilter is the abstract base class for filters used by queue discs
 * to classify packets.
 */
class SourceIpAddress: public Object {
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  //static TypeId GetTypeId (void);

  SourceIpAddress ();
  virtual ~SourceIpAddress ();

  /**
   * Standard value used by packet filters to indicate that no match was possible.
   */
  //static const int PF_NO_MATCH = -1;

  virtual bool Match (Ptr<Packet> packet) const = 0;

  /**
   * \brief Classify a packet.
   *
   * \param item the packet to classify.
   *
   * \return -1 if this filter is not able to classify packets of the same protocol
   * as item or the item does not match the filter conditions, the configured return
   * value otherwise.
   */
  //int32_t Classify (Ptr<QueueDiscItem> item) const;


private:
  Ipv4Address value;  

};

} // namespace ns3

#endif /* SOURCE_IP_ADDRESS */
