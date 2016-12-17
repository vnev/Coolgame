#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "../headers/Tile.h"
#include "../headers/Rectangle.h"
#include "../headers/Global.h"

class Graphics;
class SDL_Texture;
class SDL_Rect;
struct Tileset;

class Level {
public:
	Level();
	Level(Graphics &graphics, std::string mapName, Vector2 spawnPoint);
	~Level();
	void Update(float elapsedTime);
	void Draw(Graphics &graphics);

	std::vector<Rectangle> CheckTileCollisions(const Rectangle &other);

private:
	std::string _mapName;
	Vector2 _spawnPoint, _size, _tileSize;
	SDL_Texture* _background;
	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	std::vector<Rectangle> _collisionRects;

	void LoadMap(Graphics &graphics, std::string mapName);
};

struct Tileset {
	SDL_Texture* Texture;
	int FirstGid;

	Tileset() { FirstGid = -1; }

	Tileset(SDL_Texture* texture, int FirstGid) {
		this->Texture = texture;
		this->FirstGid = FirstGid;
	}
};

#endif
