#include "GameLogic.h"


GameLogic::GameLogic()
{
	cout << "asd" << endl;
}

bool GameLogic::pos_occupied(int x, int y)
{
	if (x < -100 || x > 100 || y < -100 || y > 100)
	{
		return false;
	}

	if (players.size() > 0)
	{
		for (vector<Player>::iterator itr = players.begin(); itr != players.end(); ++itr)
		{
			if (itr->pos.x == x && itr->pos.y == y)
			{
				return true;
			}
		}
	}
	return false;
}

void GameLogic::add_player(int id, int x, int y, char name[32])
{
	struct Player newPlayer;
	newPlayer.id = id;
	newPlayer.pos.x = x;
	newPlayer.pos.y = y;
	strcpy_s(newPlayer.name, name);

	players.push_back(newPlayer);
}

bool GameLogic::move_player(int id, int x, int y)
{
	if (!pos_occupied(x, y) && players.size() > 0)
	{
		for (vector<Player>::iterator itr = players.begin(); itr != players.end(); ++itr)
		{
			if (itr->id == id)
			{
				itr->pos.x = x;
				itr->pos.y = y;
				return true;
			}
		}
	}

	return false;
	
}

bool GameLogic::remove_player(int id)
{
	for (vector<Player>::iterator itr = players.begin(); itr != players.end(); ++itr)
	{
		if (itr->id == id)
		{
			players.erase(itr);
			return true;
		}
	}
	return false;
}

Player GameLogic::getPlayer(int index)
{
	return players.at(index);
}

int GameLogic::assign_id()
{
	int i = 1;
	for (vector<Player>::iterator itr = players.begin(); itr != players.end(); ++itr)
	{
		if (itr->id == i)
		{
			i++;
		}
		else
		{
			break;
		}
	}

	return i;
}

int GameLogic::size()
{
	return players.size();
}


