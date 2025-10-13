#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

template <typename T = float>
class Vector2D
{
private:
	T x, y;
public:

	Vector2D(T X, T Y) {
		x = X;
		y = Y;
	}

	Vector2D() {
		x = 0;
		y = 0;
	}

	//Vector2D operator=(const Vector2D& vector) const {
	//	Vector2D r;
	//	r.x = vector.x;
	//	r.y = vector.y;
	//	return r;
	//}

	Vector2D operator+(const Vector2D& vector) const{
		Vector2D r;
		r.x = this->x + vector.x;
		r.y = this->y + vector.y;
		return r;
	}

	Vector2D operator+=(const Vector2D& vector) const {
		Vector2D r;
		r.x += this->x + vector.x;
		r.y += this->y + vector.y;
		return r;
	}

	Vector2D operator-(const Vector2D& vector) const {
		Vector2D r;
		r.x = this->x - vector.x;
		r.y = this->y - vector.y;
		return r;
	}

	Vector2D operator*(const Vector2D& vector) const {
		Vector2D r;
		r.x = this->x * vector.x;
		r.y = this->y * vector.y;
		return r;
	}

	Vector2D operator*(const double num) const {
		Vector2D r;
		r.x = this->x * num;
		r.y = this->y * num;
		return r;
	}

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		return out << '{' << v.x << ", " << v.y << '}';
	}

	T GetX() const{
		return this->x;
	}

	T GetY() const{
		return this->y;
	}
	using Point2D = Vector2D<T>;
};

template <typename T = float>
using Point2D = Vector2D<T>;

#endif
