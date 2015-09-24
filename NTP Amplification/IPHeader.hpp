#pragma once

#include <random>
#include <climits>
#include <WinSock2.h>

class IPHeader
{
public:

	unsigned char IHL : 4;
	unsigned char version : 4;
	unsigned char typeOfService;
	std::uint16_t totalLength;
	std::uint16_t identification;
	std::uint16_t flagOffset;
	unsigned char ttl;
	unsigned char protocol;
	std::uint16_t header_checksum;
	std::uint32_t src_addr;
	std::uint32_t dst_addr;
	

	enum Protocol
	{
		ICMP = 1,
		TCP = 6,
		UDP = 17
	};

	int GenerateRandomID();
	void ChangeProtocol(Protocol protocol);
	std::uint16_t CalculateChecksum();
	void ChangeLength(std::uint16_t additionalLength);
	IPHeader(std::uint16_t additionalLength, unsigned char typeOfService, std::uint16_t flagOffset, unsigned char ttl, Protocol protocol, std::uint32_t src_addr, std::uint32_t dst_addr);
	IPHeader();


};