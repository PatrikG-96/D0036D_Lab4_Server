#include "GameLogic.h"


GameLogic::GameLogic()
{
	
}

bool GameLogic::pos_occupied(int x, int y)
{
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

void GameLogic::add_player(int id, int x, int y, ObjectForm form)
{
	struct Player newPlayer;
	newPlayer.id = id;
	newPlayer.pos.x = x;
	newPlayer.pos.y = y;
	newPlayer.form = form;

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


