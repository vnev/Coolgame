#include <SDL2/SDL.h>

#include "Level.h"
#include "Graphics.h"

Level::Level() {}

Level::Level(Graphics &graphics, std::string mapName, Vector2 spawn) :
		_mapName(mapName),
		_spawnPoint(spawn),
		_size(Vector2())
{
	this->LoadMap(graphics, mapName);
}

Level::~Level() {}

void Level::LoadMap(Graphics &graphics, std::string mapName) {
	this->_background = SDL_CreateTextureFromSurface(graphics.GetRenderer(),
			graphics.LoadImage("content/backgrounds/bkBlue.png"));
	this->_size = Vector2(1280, 960);
}

void Level::Update(float elapsedTime) {

}

void Level::Draw(Graphics &graphics) {
	SDL_Rect sourceRect = { 0, 0, 64, 64 };
	SDL_Rect destRect;

	for (int x = 0; x < this->_size.x / 64; x++) {
		for (int y = 0; y < this->_size.y / 64; y++) {
			destRect.x = x * 64;
			destRect.y = y * 64;
			destRect.w = 64;
			destRect.h = 64;
			graphics.DrawSurface(this->_background, &sourceRect, &destRect);
		}
	}
}
