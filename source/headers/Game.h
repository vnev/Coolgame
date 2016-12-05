#ifndef GAME_H
#define GAME_H

#include "Sprite.h"

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void GameLoop();
	void Draw(Graphics &graphics);
	void Update(float elapsed);

	Sprite _player;
};



#endif
