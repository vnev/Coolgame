#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void GameLoop();
	void Draw(Graphics &graphics);
	void Update(float elapsed);

	Player _player;
};



#endif
