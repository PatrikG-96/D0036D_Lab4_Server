#pragma once
//#include "Server.h"
//#include <iostream>
//#include "GameLogic.h"
#include <WinSock2.h>
#include <iostream>
#include "Protocol.h"

#ifndef SERVER_H
#define SERVER_H

class Server;

class Decider
{

private:

	class Server* server;
	//GameLogic logic;

private:

	//void changeMessage(char buffer);
	void join_msg(SOCKET sock, char buffer[]);
	//void leaveMessage(char buffer);

public:

	Decider();
	Decider(Server*);
	void decide(SOCKET sock, char buffer[]);

};

#endif