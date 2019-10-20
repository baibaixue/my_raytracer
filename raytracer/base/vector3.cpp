#include"base/header.h"
#include"base/mathf.h"
#include"vector3.h"

namespace rt
{
	const Vector3 Vector3::zero = Vector3(0.f, 0.f, 0.f);
	const Vector3 Vector3::one = Vector3(1.f, 1.f, 1.f);
	const Vector3 Vector3::front = Vector3(0.f, 0.f, 1.f);
	const Vector3 Vector3::back = Vector3(0.f, 0.f, -1.f);
	const Vector3 Vector3::up = Vector3(0.f, 1.f, 0.f);
	const Vector3 Vector3::down = Vector3(0.f, -1.f, 0.f);
	const Vector3 Vector3::left = Vector3(-1.f, 0.f, 0.f);
	const Vector3 Vector3::right = Vector3(1.f, 0.f, 0.f);

	Vector3::Vector3(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z)
	{
	}

	Vector3::Vector3(const Vector3& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	float Vector3::Length()const 
	{
		return sqrt(x * x + y * y + z * z);
	}

	float Vector3::SqrtLength()const
	{
		return (x * x + y * y + z * z);
	}

	const Vector3 Vector3::Normalize()const
	{
		float len = 1.f / Length();
		return Vector3(x*len, y*len, z*len);
	}

	const Vector3 Vector3::Negate()const
	{
		return Vector3(-z, -y, -z);
	}

	const Vector3 Vector3::Add(const Vector3& v)const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	const Vector3 Vector3::Subtract(const Vector3& v)const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	const Vector3 Vector3::Mulitiply(float f)const
	{
		return Vector3(x*f, y*f, z*f);
	}

	const Vector3 Vector3::Cross(const Vector3& v)const
	{
		return Vector3(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
	}

	const Vector3 Vector3::Divide(float f)const
	{
		return Vector3(x*(1.f / f), y*(1.f / f), z*(1.f / f));
	}

	float  Vector3::Dot(const Vector3& v)const
	{
		return x * v.x + y * v.y + z * v.z;
	}
}