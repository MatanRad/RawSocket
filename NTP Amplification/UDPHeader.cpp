#include "UDPHeader.hpp"

UDPHeader::UDPHeader(std::uint16_t sourcePort, std::uint16_t destPort, std::uint16_t dataLength)
{
	memset(this, 0, sizeof(UDPHeader));
	this->sourcePort = htons(sourcePort);
	this->destPort = htons(destPort);
	this->length = htons(dataLength + sizeof(UDPHeader));
}

void UDPHeader::ChangeDataLength(std::uint16_t dataLength)
{
	this->length = htons(dataLength + sizeof(UDPHeader));
}

std::uint16_t UDPHeader::CalculateChecksum(IPHeader ip, unsigned char * data, size_t dataLength)
{
	std::uint32_t sum = 0;
	std::uint16_t* current = (std::uint16_t*)(&(ip.src_addr));
	size_t i;

	for (i = 0; i < 4; i++) sum += current[i];
	sum += (std::uint16_t)ip.protocol;

	current = (std::uint16_t*)(&(ip.totalLength));
	for (i = 0; i < 2; i++) sum += current[i];


	current = (std::uint16_t*)this;
	for (i = 0; i < sizeof(UDPHeader); i++) sum += current[i];

	current = (std::uint16_t*)data;
	for (i = 0; i < (dataLength / 2); i++) sum += current[i];


	if (dataLength % 2 != 0)
	{
		char* c = (char*)current[i];
		std::uint16_t in = *c;
		sum += in<<16;
	}

	while ((sum >> 16)>0) sum = (sum >> 16) + (sum & 0xffff);
	sum = ~sum;

	this->checksum = sum;
	return (std::uint16_t)sum;
}
