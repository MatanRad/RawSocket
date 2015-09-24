#pragma once
#include <cstdint>
#include "IPHeader.hpp"

class UDPHeader
{
public:

	std::uint16_t sourcePort;
	std::uint16_t destPort;
	std::uint16_t length;
	std::uint16_t checksum;

	UDPHeader();
	UDPHeader(std::uint16_t sourcePort, std::uint16_t destPort, std::uint16_t dataLength);
	void ChangeDataLength(std::uint16_t dataLength);
	std::uint16_t CalculateChecksum(IPHeader ip, unsigned char* data, size_t dataLength);
};

