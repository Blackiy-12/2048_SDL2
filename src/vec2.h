#pragma once

template <typename T> class vec2
{
public:
	T x;

	T y;

public:
	vec2() {};

	vec2(T x, T y) : x(x), y(y) {};

	~vec2() {};

	vec2 operator+(vec2 vec)
	{
		return vec2(this->x + vec.x, this->y + vec.y);
	}

	vec2 operator-(vec2 vec)
	{
		return vec2(this->x - vec.x, this->y - vec.y);
	}

	vec2& operator+=(vec2 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	vec2& operator-=(vec2 vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		return *this;
	}

	vec2 operator* (double coif)
	{
		return vec2(this->x * coif, this->y * coif);
	}

	bool operator== (vec2 vec)
	{
		return (this->x == vec.x) && (this->y == vec.y);
	}

	bool operator!= (vec2 vec)
	{
		return (this->x != vec.x) || (this->y != vec.y);
	}

};