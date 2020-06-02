#include"plane.h"
#include"ray/IntersectResult.h"

namespace rt
{
	Plane::Plane(const Vector3& _normal,const Vector3& _position, float _d)
		:normal(_normal)
		,position(_position)
		,d(_d)
	{}

	Plane::Plane(const Plane& _plane)
		:normal(_plane.normal)
		,position(_plane.position)
		,d(_plane.d)
	{}

	IntersectResult Plane::intersect(Ray3& _ray)	//判断光线和平面是否有交点
	{
		float a = _ray.direction.Dot(normal);
		if (a >= 0)
		{
			return IntersectResult::noHit();
		}

		float b = normal.Dot(_ray.origin.Subtract(position));
		IntersectResult result = IntersectResult::noHit();
		result.is_hit = true;
		result.material = material;
		result.distance = -b/ a;
		result.position = _ray.GetPoint(result.distance);
		result.normal = normal;
		return result;
	}

	void Plane::move_location(const Vector3& vec)
	{
		position = position.Add(vec);
		return;
	}

	void Plane::turn_location(const float& pitch, const float& yaw)
	{
		printf("1\n");
		float x = normal.x;
		float y = normal.y;
		float z = normal.z;
		normal.x = x * rt::Mathf::Cos(pitch * rt::Mathf::deg2rad) - z * rt::Mathf::Sin(pitch * rt::Mathf::deg2rad);
		normal.z = x * rt::Mathf::Sin(pitch * rt::Mathf::deg2rad) + z * rt::Mathf::Cos(pitch * rt::Mathf::deg2rad);
		normal.y = y;
		x = normal.x;
		y = normal.y;
		z = normal.z;
		normal.y = y * rt::Mathf::Cos(yaw * rt::Mathf::deg2rad) - z * rt::Mathf::Sin(yaw * rt::Mathf::deg2rad);
		normal.z = y * rt::Mathf::Sin(yaw * rt::Mathf::deg2rad) + z * rt::Mathf::Cos(yaw * rt::Mathf::deg2rad);
		normal.x = x;
		float px = position.x;
		float py = position.y;
		float pz = position.z;
		position.x = px * rt::Mathf::Cos(pitch * rt::Mathf::deg2rad) - pz * rt::Mathf::Sin(pitch * rt::Mathf::deg2rad);
		position.z = px * rt::Mathf::Sin(pitch * rt::Mathf::deg2rad) + pz * rt::Mathf::Cos(pitch * rt::Mathf::deg2rad);
		position.y = py;
		px = position.x;
		py = position.y;
		pz = position.z;
		position.y = py * rt::Mathf::Cos(yaw * rt::Mathf::deg2rad) - pz * rt::Mathf::Sin(yaw * rt::Mathf::deg2rad);
		position.z = py * rt::Mathf::Sin(yaw * rt::Mathf::deg2rad) + pz * rt::Mathf::Cos(yaw * rt::Mathf::deg2rad);
		position.x = px;
		return;
	}

	Plane::~Plane() {};
}