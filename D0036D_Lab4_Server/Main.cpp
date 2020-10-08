#include "Server.h"

int main()
{
	Server server = Server(49152);
	server.start();
}