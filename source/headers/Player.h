#ifndef PLAYER_H
#define PLAYER_H

#include "../headers/Global.h"
#include "../headers/AnimatedSprite.h"

class Graphics;

class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, float x, float y);
	void Draw(Graphics &graphics);
	void Update(float elapsedTime);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void StopMoving();

	virtual void AnimationDone(std::string animation);
	virtual void SetupAnimations();

	void HandleTileCollisions(std::vector<Rectangle> &others);

	const float GetX() const;
	const float GetY() const;

private:
	float _dx, _dy;
	Direction _facing;
	bool _grounded;
};

#endif
