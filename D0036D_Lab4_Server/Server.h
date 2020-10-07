#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

#define MAX_CLIENTS 8
#define MAX_PORT 65536

class Server
{

private:

	SOCKET master_socket = INVALID_SOCKET;
	SOCKET client_sockets[MAX_CLIENTS];
	struct sockaddr_in addr;

public:

	Server(short);
	void start();

};

