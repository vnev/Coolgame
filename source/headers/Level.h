#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "Global.h"

class Graphics;
class SDL_Texture;

class Level {
public:
	Level();
	Level(Graphics &graphics, std::string mapName, Vector2 spawnPoint);
	~Level();
	void Update(float elapsedTime);
	void Draw(Graphics &graphics);

private:
	std::string _mapName;
	Vector2 _spawnPoint, _size;
	SDL_Texture* _background;

	void LoadMap(Graphics &graphics, std::string mapName);
};


#endif
