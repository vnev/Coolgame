#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>
#include <string>
#include <vector>

#include "Sprite.h"
#include "Global.h"

class Graphics;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string filePath, int sourceX,
					int sourceY, int width, int height,
					float posX, float posY, float timeToUpdate);
	void PlayAnimation(std::string animation, bool once = false);
	void Update(int elapsedTime);
	void Draw(Graphics &graphics, int x, int y);
	virtual void SetupAnimations();

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void AddAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
	void ResetAnimations();
	void StopAnimation();
	void SetVisible(bool visible);
	virtual void AnimationDone(std::string animation);

private:
	std::map<std::string, std::vector<SDL_Rect> > _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
};

#endif