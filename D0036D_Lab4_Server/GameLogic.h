#pragma once
#include <vector>
#include "Protocol.h"
#include <iostream>

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
	void add_player(int id, int x, int y, char[]);
	bool move_player(int id, int x, int y);
	bool remove_player(int id);
	int size();
	int assign_id();
	Player getPlayer(int index);

};

