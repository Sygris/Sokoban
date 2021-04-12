#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
	: x{x}, y{y}
{
}

Vector2D::~Vector2D()
{
}

Vector2D& Vector2D::Add(const Vector2D& vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vector)
{
	x *= vector.x;
	y *= vector.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vector)
{
	x /= vector.x;
	y /= vector.y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}


Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
	return this->Add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector)
{
	return this->Subtract(vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& vector)
{
	return this->Multiply(vector);
}

Vector2D& Vector2D::operator/=(const Vector2D& vector)
{
	return this->Divide(vector);
}

float Vector2D::Distance(const Vector2D& v) const
{
	return std::sqrtf(pow(v.x - x, 2) + pow(v.y - y, 2));
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vector)
{
	stream << "Vector2D = (" << vector.x << ", " << vector.y << ")";
	return stream;
}
