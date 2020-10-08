#pragma once
#include <vector>
#include "Protocol.h"

using namespace std;

class GameLogic
{

private:

	vector<Player> players;
	const int minX = -100;
	const int maxX = 100;
	const int minY = -100;
	const int maxY = 100;

private:

	bool pos_occupied(int x, int y);

public:

	GameLogic();
	void add_player(int id, int x, int y, ObjectForm form);
	bool move_player(int id, int x, int y);
	int size();
	Player getPlayer(int index);

};

