#include "IPHeader.hpp"

IPHeader::IPHeader(std::uint16_t additionalLength, unsigned char typeOfService, std::uint16_t flagOffset, unsigned char ttl, Protocol protocol, std::uint32_t src_addr, std::uint32_t dst_addr)
{
	memset(this, 0, sizeof(IPHeader));
	this->IHL = 5;
	this->version = 4;
	this->typeOfService = typeOfService;
	this->totalLength = htons(sizeof(IPHeader) + additionalLength);
	this->flagOffset = flagOffset;
	this->ttl = ttl;
	this->protocol = protocol;
	this->src_addr = src_addr;
	this->dst_addr = dst_addr;
}

int IPHeader::GenerateRandomID()
{
	this->identification = (rand() % USHRT_MAX) + 1; // Generate Random Number Between 1 and unsigned short max
	return this->identification;
}

void IPHeader::ChangeLength(std::uint16_t additionalLength)
{
	this->totalLength = htons(sizeof(IPHeader) + additionalLength);
}

void IPHeader::ChangeProtocol(Protocol protocol)
{
	this->protocol = protocol;
}

std::uint16_t IPHeader::CalculateChecksum()
{
	unsigned short* buf = (unsigned short*)this;
	int nwords = sizeof(IPHeader) / 2;

	unsigned long sum;
	for (sum = 0; nwords > 0; nwords--)
	{
		sum += *buf++;
		while ((sum >> 16)>0) sum = (sum >> 16) + (sum & 0xffff);
	}

	sum = ~sum;

	this->header_checksum = (std::uint16_t)sum;

	return (std::uint16_t)sum;
}
