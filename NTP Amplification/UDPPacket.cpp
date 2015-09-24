#include "UDPPacket.hpp"

void UDPPacket::Init(unsigned char TypeOfService, std::uint16_t identification, std::uint16_t flagOffset, unsigned char ttl, std::uint32_t srcAddr, std::uint32_t dstAddr, std::uint16_t srcPort, std::uint16_t dstPort, unsigned char* data, std::uint16_t dataLength)
{
	unsigned char* buffer = (unsigned char*)malloc(sizeof(IPHeader) + sizeof(UDPHeader) + dataLength);
	ip = (IPHeader*)buffer;
	*ip = IPHeader(dataLength + sizeof(UDPHeader), TypeOfService, flagOffset, ttl, IPHeader::Protocol::UDP, srcAddr, dstAddr);
	if (identification == 0) identification = ip->GenerateRandomID();
	else ip->identification = identification;

	ip->CalculateChecksum();

	udp = (UDPHeader*)(buffer + sizeof(IPHeader));
	*udp = UDPHeader(srcPort, dstPort, dataLength);
	udp->CalculateChecksum(*ip, data, dataLength);

	this->data = (buffer + sizeof(IPHeader) + sizeof(UDPHeader));
	this->dataLength = dataLength;
	strcpy_s((char*)this->data, dataLength, (char*)data);
}

std::uint16_t UDPPacket::GetPacketLength()
{
	return sizeof(IPHeader) + sizeof(UDPHeader) + dataLength;
}

UDPPacket::UDPPacket(unsigned char TypeOfService, std::uint16_t identification, std::uint16_t flagOffset, unsigned char ttl, char* srcAddr, char* dstAddr, std::uint16_t srcPort, std::uint16_t dstPort, unsigned char* data, std::uint16_t dataLength)
{
	Init(TypeOfService, identification, flagOffset, ttl, inet_addr(srcAddr), inet_addr(dstAddr), srcPort, dstPort, data, dataLength);
}

UDPPacket::UDPPacket(unsigned char TypeOfService, std::uint16_t identification, std::uint16_t flagOffset, unsigned char ttl, std::uint32_t srcAddr, std::uint32_t dstAddr, std::uint16_t srcPort, std::uint16_t dstPort, unsigned char* data, std::uint16_t dataLength)
{
	Init(TypeOfService, identification, flagOffset, ttl, srcAddr, dstAddr, srcPort, dstPort, data,dataLength);
}
