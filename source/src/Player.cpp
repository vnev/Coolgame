#include "../headers/Player.h"
#include "../headers/Graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100),
	_dx(0), _dy(0), _facing(RIGHT), _grounded(false)
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

const float Player::GetX() const {
	return this->_x;
}

const float Player::GetY() const {
	return this->_y;
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

void Player::HandleTileCollisions(std::vector<Rectangle> &others) {
	for (int i = 0; i < others.size(); i++) {
		sides::Side collisionSide = Sprite::GetCollisionSide(others[i]);
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->_y = others[i].GetBottom() + 1;
				this->_dy = 0;
				break;
			case sides::BOTTOM:
				this->_y = others[i].GetTop() - this->_boundingBox.GetHeight() - 1;
				this->_dy = 0;
				this->_grounded = true;
				break;
			case sides::LEFT:
				this->_x = others[i].GetRight() + 1;
				break;
			case sides::RIGHT:
				this->_y = others[i].GetLeft() - this->_boundingBox.GetWidth() - 1;
				break;
			}
		}
	}
}

void Player::Update(float elapsedTime) {
	if (this->_dy <= player_constants::GRAVITY_CAP) {
		this->_dy += player_constants::GRAVITY * elapsedTime;
	}

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;
	AnimatedSprite::Update(elapsedTime);
}

void Player::Draw(Graphics &graphics) {
	AnimatedSprite::Draw(graphics, this->_x, this->_y);
}





