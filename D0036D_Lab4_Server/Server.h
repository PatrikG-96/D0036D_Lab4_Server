#pragma once


#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

#include "Protocol.h"

#ifndef DECIDER_H
#define DECIDER_H

#define MAX_CLIENTS 8
#define MAX_PORT 65536

class Decider;


class Server
{

private:

	SOCKET master_socket = INVALID_SOCKET;
	SOCKET client_sockets[MAX_CLIENTS];
	struct sockaddr_in addr;
	socklen_t addrlen;
	Decider* decider;

public:

	Server(int);
	~Server();
	void start();
	void send_msg(SOCKET, char*, int);
	void send_to_all(char*, int, SOCKET)

};

#endif