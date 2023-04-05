#pragma once
#include <math.h>
#define PI 3.141592

struct vector2
{
	static vector2 up;
	static vector2 right;

	static vector2 one;
	static vector2 zero;
	static vector2 two;

	float x;
	float y;

	vector2()
		: x(0.0f)
		, y(0.0f)
	{
	}
	vector2(float x, float y)
		: x(x)
		, y(y)
	{
	}
	vector2(int x, int y)
		: x(x)
		, y(y)
	{
	}
	vector2(const vector2&) = default;
	vector2& operator=(const vector2&) = default;

	vector2(vector2&&) = default;
	vector2& operator=(vector2&&) = default;

	vector2 operator- ()
	{
		return vector2(-x, -y);
	}
	vector2 operator+(const vector2& other)
	{
		vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}
	vector2 operator-(const vector2& other)
	{
		vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}
	vector2 operator*(const vector2& other)
	{
		vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}
	vector2 operator*(const float ratio)
	{
		vector2 temp;
		temp.x = x * ratio;
		temp.y = y * ratio;

		return temp;
	}
	vector2 operator/(const float ratio)
	{
		vector2 temp;
		temp.x = x / ratio;
		temp.y = y / ratio;

		return temp;
	}
	void operator+=(const vector2& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(const vector2& other)
	{
		x *= other.x;
		y *= other.y;
	}
	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}
	bool operator==(const vector2& other)
	{
		return (x == other.x && y == other.y);
	}

	void operator-=(const float& value)
	{
		x -= value;
		y -= value;
	}

	void clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float length()
	{
		return sqrtf(x * x + y * y);
	}

	vector2& normalize()
	{
		float len = length();
		x /= len;
		y /= len;

		return *this;
	}
};

namespace BP::math
{
	inline static vector2 rotate(vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		vector.normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) + vector.y * cosf(radian);

		return vector2(x, y);
	}

	inline static float dot(vector2& v1, vector2& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	inline static float cross(vector2& v1, vector2& v2)
	{
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
}