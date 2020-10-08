#pragma once

#define MAXNAMELEN	32

enum ObjectDesc {
	Human,
	NonHuman,
	Vehicle,
	StaticObject
};

enum ObjectForm {
	Cube,
	Sphere,
	Pyramid,
	Cone
};

struct Coordinate {
	int x;
	int y;
};

enum MessageTypeGame {
	Join,
	Leave,
	Change,
	Event,
	TextMessage
};


struct HeaderGame {
	unsigned int length;
	unsigned int seq_no;
	unsigned int id;
	MessageTypeGame type;
};

struct JoinMessage {
	HeaderGame header;
	ObjectDesc desc;
	ObjectForm form;
	char name[MAXNAMELEN];
};

struct LeaveMsg {
	HeaderGame header;
};

enum ChangeType {
	NewPlayer,
	PlayerLeave,
	NewPlayerPosition
};

struct ChangeMessage {
	HeaderGame header;
	ChangeType type;
};

struct NewPlayerMessage {
	ChangeMessage msg;
	ObjectDesc desc;
	ObjectForm form;
	char name[MAXNAMELEN];
};

struct PlayerLeaveMessage {
	ChangeMessage msg;
};

struct NewPlayerPositionMessage {
	ChangeMessage msg;
	Coordinate pos;
	Coordinate dir;
};

enum EventType {
	Move
};

struct EventMessage {
	HeaderGame header;
	EventType type;
};

struct MoveEvent {
	EventMessage msg;
	Coordinate pos;
	Coordinate dir;
};

struct TextMessage {
	HeaderGame header;
	char	text[1];
};

struct Player {
	int id;
	Coordinate pos;
	ObjectForm form;
};