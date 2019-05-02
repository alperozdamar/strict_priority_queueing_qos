
#ifndef SOURCE_PORT_NUMBER_H
#define SOURCE_PORT_NUMBER_H

#include "filter-element.h"
#include "ns3/log.h"



namespace ns3 {
    class SourcePortNumber: public FilterElement {
    public:
        
        static TypeId GetTypeId (void);

        SourcePortNumber (uint32_t);
        ~SourcePortNumber ();


        bool match(Ptr<ns3::Packet> packet);


    private:

        uint32_t value;

    };
} // namespace ns3
#endif /*SOURCE_PORT_NUMBER_H */
