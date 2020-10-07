#include "Server.h"


using namespace std;

Server::Server(short port)
{
	// Temporary windows code
	//-----------------------------------------------
	
	WSAData wsaData;

	if (WSAStartup(0x202, &wsaData))
	{
		cout << "WSAStartup failed with error: " << WSAGetLastError() << endl;
		return;
	}

	//-----------------------------------------------

	addr.sin_family = AF_INET;
	addr.sin_addr = in4addr_any;

	master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (master_socket == INVALID_SOCKET)
	{
		cout << "Creating socket failed with error: " << WSAGetLastError() << endl;
		return;
	}

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		client_sockets[i] = INVALID_SOCKET;
	}

	bool bound = false;

	for (int i = port; i < MAX_PORT; i++)
	{
		addr.sin_port = i;

		if (bind(master_socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			cout << "Binding to port: '" << i << "' failed. Trying next port." << endl;
			closesocket(master_socket);
			continue;
		}

		if (listen(master_socket, 3) == SOCKET_ERROR)
		{
			cout << "Listening to port: '" << i << "' failed. Trying next port." << endl;
			closesocket(master_socket);
			continue;
		}

		cout << "Socket successfully bound to port: '" << i << "'." << endl;
		bound = true;
		break;
	}
	
	if (!bound)
	{
		cout << "Server startup failed: 'Unable to bind to any port'." << endl;
		return;
	}

}

void Server::start()
{

	fd_set readSet;

	while (1)
	{
		FD_ZERO(&readSet);

		FD_SET(master_socket, &readSet);

		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (client_sockets[i] != INVALID_SOCKET)
			{
				FD_SET(client_sockets[i], &readSet);
			}
		}

		int select_res = select(NULL, &readSet, NULL, NULL, NULL);

		if (select_res == SOCKET_ERROR)
		{
			cout << "select() failed with error: " << WSAGetLastError() << endl;
			closesocket(master_socket);
			WSACleanup();
			return;
		}

		// If master socket is set, it means we have a pending connection to resolve
		if (FD_ISSET(master_socket, &readSet))
		{
			// Create a new socket and assign the connection recieved to this socket.
			SOCKET newSocket;
			if ((newSocket = accept(master_socket, (sockaddr*)&addr, (socklen_t*)sizeof(addr))) == INVALID_SOCKET)
			{
				cout << "Accepting connection failed." << endl;
			}
			else // If accept didn't fail, add it to an empty spot in the client_sockets array
			{
				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (client_sockets[i] == INVALID_SOCKET)
					{
						client_sockets[i] = newSocket;
						break;
					}
				}
			}
		}
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			SOCKET sock_desc = client_sockets[i];
			if (FD_ISSET(sock_desc, &readSet))
			{

			}
		}

	}
}