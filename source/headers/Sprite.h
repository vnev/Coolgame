#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

#include "../headers/Rectangle.h"
#include "../headers/Global.h"

class Graphics;

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath,
			int sourceX, int sourceY,
			int width, int height,
			float posX, float posY);
	virtual ~Sprite();
	virtual void Update();
	void Draw(Graphics &graphics, int x, int y);

	const Rectangle GetBoundingBox() const;
	const sides::Side GetCollisionSide(Rectangle &other) const;

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	float _x, _y;
	Rectangle _boundingBox;
};


#endif
