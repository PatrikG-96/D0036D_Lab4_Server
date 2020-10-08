#include "Decider.h"
#include "Server.h"

using namespace std;

Decider::Decider(Server *serv)
{
	this->server = serv;
	//logic = GameLogic();
}

Decider::Decider()
{
	cout << "asd" << endl;
}

void Decider::join_msg(SOCKET sock, char buffer[])
{
	JoinMessage* j = (JoinMessage*)buffer;
	
	struct HeaderGame header;
	header.id = 1;
	header.length = sizeof(header);
	header.seq_no = 1;
	header.type = Join;

	server->send_msg(sock, (char*)&header, sizeof(header));



}

void Decider::decide(SOCKET sock, char buffer[])
{
	HeaderGame* h = (HeaderGame*)buffer;

	switch (h->type)
	{
	case Join:
		cout << "Join message recieved" << endl;
		join_msg(sock, buffer);
		break;
	case Leave:
		break;
	case Change:
		break;

	default:
		break;
	}
}

//void Decider::joinMessage(char buffer)
//{
//	JoinMessage* jmsg = (JoinMessage*)buffer;
//
//
//}