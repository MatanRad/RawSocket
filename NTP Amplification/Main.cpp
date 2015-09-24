#include <cstdio>
#include <cstdlib>
#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>
#include "IPHeader.hpp"
#include "UDPPacket.hpp"



void init_winsock()
{
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		exit(1);
	}
}


void main()
{
	std::string srcIP = "192.168.1.23";
	std::string dstIP = "192.168.1.17";

	unsigned short srcPort = 7778;
	unsigned short dstPort = 7777;

	


	int contentsize = 6;

	unsigned char* data = (unsigned char*)malloc(contentsize);

	strcpy_s((char*)data,6, "test!");



	UDPPacket packet = UDPPacket((unsigned char)0, (std::uint16_t)101, (std::uint16_t)0, (unsigned char)128, (char*)srcIP.c_str(), (char*)dstIP.c_str(), (std::uint16_t)srcPort, (std::uint16_t)dstPort, data, (std::uint16_t)contentsize);
	
	


	init_winsock();
	SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	
	int optval = 1;
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof optval);
	
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	
	addr.sin_addr.S_un.S_addr = inet_addr(dstIP.c_str());
	addr.sin_family = AF_INET;
	addr.sin_port = htons(dstPort);
	
	while (true) {
		std::cout << sendto(sock, (char*)&packet, packet.GetPacketLength(), 0, (sockaddr*)(&addr), sizeof(sockaddr_in)) << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	free(data);

	while (1);

}