#include "Player.h"
#include "Graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100)
{
	graphics.LoadImage("content/sprites/MyChar.png");
	this->SetupAnimations();
	this->PlayAnimation("RunRight");
}

void Player::SetupAnimations() {
		this->AddAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2());
		this->AddAnimation(3, 0, 16, "RunRight", 16, 16, Vector2());
		this->AddAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2());
		this->AddAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2());
}

void Player::AnimationDone(std::string currentAnimation) {

}

void Player::MoveLeft() {
	this->_dx = -player_constants::WALK_SPEED;
	this->PlayAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::MoveRight() {
	this->_dx = player_constants::WALK_SPEED;
	this->PlayAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::MoveUp() {
	this->_dy = -player_constants::WALK_SPEED;
	this->PlayAnimation("RunUp");
	this->_facing = UP;
}

void Player::MoveDown() {
	this->_dy = player_constants::WALK_SPEED;
	this->PlayAnimation("RunDown");
	this->_facing = DOWN;
}

void Player::StopMoving() {
	this->_dx = 	this->_dy = 0;
	this->PlayAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::Update(float elapsedTime) {
	this->_x += this->_dx * elapsedTime;
	AnimatedSprite::Update(elapsedTime);
}

void Player::Draw(Graphics &graphics) {
	AnimatedSprite::Draw(graphics, this->_x, this->_y);
}





