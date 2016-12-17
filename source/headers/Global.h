#ifndef GLOBAL_H
#define GLOBAL_H

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side GetOppositeSide(Side side) {
		return
				side == TOP ? BOTTOM :
				side == BOTTOM ? TOP :
				side == LEFT ? RIGHT :
				side == RIGHT ? LEFT :
				NONE;
	}
}

namespace globals {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const float SPRITE_SCALE = 2.0f;
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2 {
	int x, y;

	Vector2(int _x, int _y) : x(_x), y(_y) {}
	Vector2() : x(0), y(0) {}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif
