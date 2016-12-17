#include "../headers/Sprite.h"
#include "../headers/Graphics.h"
#include "../headers/Global.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY) : _x(posX), _y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(filePath));
	if (this->_spriteSheet == NULL) {
		printf("Error: Could not load image %s\n", filePath.c_str());
	}
}


Sprite::~Sprite() {
}

void Sprite::Draw(Graphics &graphics, int x, int y) {
	SDL_Rect destRect = { x, y,
						  static_cast<int>(this->_sourceRect.w * globals::SPRITE_SCALE),
						  static_cast<int>(this->_sourceRect.h * globals::SPRITE_SCALE) };
	graphics.DrawSurface(this->_spriteSheet, &this->_sourceRect, &destRect);
}

void Sprite::Update() {

}
