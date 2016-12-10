#ifndef TILE_H
#define TILE_H

#include "Global.h"

struct SDL_Texture;
class Graphics;

class Tile {
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 mapPosition);
	void Update(float elapsedTime);
	void Draw(Graphics &graphics);
private:
	SDL_Texture* _tileset;
	Vector2 _size, _tilesetPosition, _mapPosition;
};

#endif
