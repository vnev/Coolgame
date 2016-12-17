#include <SDL2/SDL.h>

#include "../headers/Graphics.h"
#include "../headers/Tile.h"

Tile::Tile() {}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 mapPosition)
	: _tileset(tileset), _size(size), _tilesetPosition(tilesetPosition),
	  _mapPosition(Vector2(mapPosition.x * globals::SPRITE_SCALE, mapPosition.y * globals::SPRITE_SCALE))
{}

void Tile::Update(float elapsedTime) {}

void Tile::Draw(Graphics &graphics) {
	SDL_Rect destRect = { this->_mapPosition.x, this->_mapPosition.y,
						  static_cast<int>(this->_size.x * globals::SPRITE_SCALE),
						static_cast<int>(this->_size.y * globals::SPRITE_SCALE) };
	SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y,
			this->_size.x, this->_size.y };
	graphics.DrawSurface(this->_tileset, &sourceRect, &destRect);
}

