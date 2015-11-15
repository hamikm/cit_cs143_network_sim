/**
 * @file
 * @author Jessica Li, Jingwen Wang, Hamik Mukelyan
 */

#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <cassert>
#include <string>
#include "nethost.h"
#include "netflow.h"
#include "netelement.h"

using namespace std;

/**
 * Describes a packet in the simulated network, which can be one of the types
 * in the enumerated type @c packetType.
 */
class packet : public netelement {

public:

	/** Types of packets in this simulation. */
	enum packetType {
		FLOW,
		ACK,
		ROUTING
	};

private:

	/**
	 * Type of packet: either payload transmission, acknowledgement, or
	 * routing.
	 */
	packetType t;

	/** Packet size in MB (to be consistent with flow) */
	float size;

	/** Sequence number of packet */
	int seq;

	/**
	 * IP address of source host, which is just the name of the source
	 * host in our simulation.
	 */
	string source_ip;

	/** IP address of destination host, which is similarly just a name. */
	string dest_ip;

	// TODO was told this is necessary but not sure why...
	/** Flow to which this packet belongs. */
	netflow *parent_flow;

public:

	packet(packetType type, float size, string source_ip,
			string dest_ip, int seq, netflow &parent_flow) :
				netelement (""), t(type), size(size), seq(seq),
				source_ip(source_ip), dest_ip(dest_ip),
				parent_flow(&parent_flow) { }

	string getSource() { return source_ip; }

	string getDestination() { return dest_ip; }

	int getSeq() { return seq; }

	netflow *getParentFlow() { return parent_flow; }

	bool isAckPacket() { return t == ACK; }

	bool isFlowPacket() { return t == FLOW; }

	bool isRoutingPacket() { return t == ROUTING; }

	/**
	 * Print helper function which partially overrides the one in @c netdevice.
	 * @param os The output stream to which to write.
	 */
	virtual void printHelper(ostream &os) const {
		netelement::printHelper(os);
		os << " ---> [packet. src: " << source_ip << ", dst: " << dest_ip <<
				", type: " << t << ", seq_num: " << seq << ", size: " <<
				size << "]";
	}
};

#endif // PACKET_H
