#ifndef GAME_H
#define GAME_H

#include "../headers/Player.h"
#include "../headers/Level.h"

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
	Level _level;
};



#endif
