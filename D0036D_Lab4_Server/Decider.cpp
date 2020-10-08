#include "Decider.h"
#include "Server.h"

using namespace std;

Decider::Decider(Server *serv)
{
	this->server = serv;
}

Decider::Decider()
{
	cout << "asd" << endl;
}

void Decider::join_msg(SOCKET sock, char buffer[])
{
	JoinMessage* j = (JoinMessage*)buffer;

	if (j->header.id != 0 || j->header.seq_no != 0)
	{
		cout << "Recieved join message with ID: '" << j->header.id << "', and seq_no: '" << j->header.seq_no << "'. Expected 0." << endl;
		return;
	}

	int id = gl.assign_id();
	
	struct HeaderGame header;
	header.id = id;
	header.length = sizeof(header);
	header.seq_no = 0;
	header.type = Join;

	server->send_msg(sock, (char*)&header, sizeof(header));

	for (int i = 0; i < gl.size(); i++)
	{
		struct Player p = gl.getPlayer(i);
		struct NewPlayerMessage npm;
		npm.msg.header.id = p.id;
		npm.msg.header.length = sizeof(npm);
		npm.msg.header.seq_no = 0;
		npm.msg.header.type = Change;
		npm.msg.type = NewPlayer;
		strcpy_s(npm.name, p.name);
		server->send_msg(sock, (char*)&npm, sizeof(npm));

	}

	gl.add_player(id, -100, -100, j->name);

	cout << "after adding: " << gl.size() << endl;

	struct NewPlayerMessage npm;
	npm.msg.header.id = id;
	npm.msg.header.length = sizeof(npm);
	npm.msg.header.seq_no = 0;
	npm.msg.header.type = Change;
	npm.msg.type = NewPlayer;
	strcpy_s(npm.name, j->name);

	server->send_to_all((char*)&npm, sizeof(npm), sock);
}

void Decider::event_msg(SOCKET sock, char buffer[])
{
	EventMessage* em = (EventMessage*)buffer;

	switch (em->type)
	{
	case Move:
	{
		MoveEvent* me = (MoveEvent*)buffer;

		int id = me->msg.header.id;
		int x = me->pos.x;
		int y = me->pos.y;

		if (gl.move_player(id, x, y))
		{
			cout << "should move player" << endl;
			struct NewPlayerPositionMessage nppm;
			nppm.msg.header.id = id;
			nppm.msg.header.length = sizeof(nppm);
			nppm.msg.header.seq_no = me->msg.header.seq_no;
			nppm.msg.header.type = Change;
			nppm.msg.type = NewPlayerPosition;
			nppm.pos.x = x;
			nppm.pos.y = y;
			server->send_to_all((char*)&nppm, sizeof(nppm));
		}
	}
		break;
	default:
		break;
	}
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
	case Event:
		cout << "Event message recieved" << endl;
		event_msg(sock, buffer);
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