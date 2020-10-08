#include "Server.h"
#include "GameLogic.h"

int main()
{
	Server server = Server(49152);
	server.start();
}