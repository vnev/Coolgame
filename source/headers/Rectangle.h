#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../headers/Global.h"

class Rectangle {
public:
	Rectangle() {}
	Rectangle(int x, int y, int width, int height) :
		_x(x), _y(y), _width(width), _height(height) {}

	const int GetCenterX() const { return this->_x + (this->_width / 2); }
	const int GetCenterY() const { return this->_y + (this->_height / 2); }
	const int GetLeft() const { return _x; }
	const int GetRight() const { return _x + this->_width; }
	const int GetTop() const { return this->_y; }
	const int GetBottom() const { return this->_y + this->_height; }

	const int GetWidth() const { return this->_width; }
	const int GetHeight() const { return this->_height; }

	const int GetSide(const sides::Side side) const {
		return
				side == sides::LEFT ? this->GetLeft() 	 :
				side == sides::RIGHT ? this->GetRight() 	 :
				side == sides::TOP ? this->GetTop() 		 :
				side == sides::BOTTOM ? this->GetBottom() :
				sides::NONE;
	}

	const bool CollidesWith(const Rectangle &other) const {
		return
				this->GetRight() >= other.GetLeft() &&
				this->GetLeft() <= other.GetRight() &&
				this->GetTop() <= other.GetBottom() &&
				this->GetBottom() >= other.GetTop();
	}

	const bool IsValidRectangle() const {
		return (this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
	}

private:
	int _x, _y, _width, _height;
};


#endif
