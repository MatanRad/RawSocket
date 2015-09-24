#pragma once
#include <cstdint>
#include <cstdlib>
#include "IPHeader.hpp"
#include "UDPHeader.hpp"

class UDPPacket
{
	void Init(unsigned char TypeOfService, std::uint16_t identification, std::uint16_t flagOffset, unsigned char ttl, std::uint32_t srcAddr, std::uint32_t dstAddr, std::uint16_t srcPort, std::uint16_t dstPort, unsigned char* data, std::uint16_t dataLength);

public:

	IPHeader* ip = NULL;
	UDPHeader* udp = NULL;
	unsigned char* data = NULL;
	std::uint16_t dataLength;

	std::uint16_t GetPacketLength();
	UDPPacket(unsigned char TypeOfService, std::uint16_t identification, std::uint16_t flagOffset, unsigned char ttl, char* srcAddr, char* dstAddr, std::uint16_t srcPort, std::uint16_t dstPort, unsigned char* data, std::uint16_t dataLength);
	UDPPacket(unsigned char TypeOfService, std::uint16_t identification, std::uint16_t flagOffset, unsigned char ttl, std::uint32_t srcAddr, std::uint32_t dstAddr, std::uint16_t srcPort, std::uint16_t dstPort, unsigned char* data, std::uint16_t dataLength);
};